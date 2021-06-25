<शैली गुरु>
/*
   HIDP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2003-2004 Marcel Holपंचांगann <marcel@holपंचांगann.org>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#समावेश <linux/export.h>
#समावेश <linux/file.h>

#समावेश "hidp.h"

अटल काष्ठा bt_sock_list hidp_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(hidp_sk_list.lock)
पूर्ण;

अटल पूर्णांक hidp_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	BT_DBG("sock %p sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	bt_sock_unlink(&hidp_sk_list, sk);

	sock_orphan(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_hidp_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा hidp_connadd_req ca;
	काष्ठा hidp_conndel_req cd;
	काष्ठा hidp_connlist_req cl;
	काष्ठा hidp_conninfo ci;
	काष्ठा socket *csock;
	काष्ठा socket *isock;
	पूर्णांक err;

	BT_DBG("cmd %x arg %p", cmd, argp);

	चयन (cmd) अणु
	हाल HIDPCONNADD:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&ca, argp, माप(ca)))
			वापस -EFAULT;

		csock = sockfd_lookup(ca.ctrl_sock, &err);
		अगर (!csock)
			वापस err;

		isock = sockfd_lookup(ca.पूर्णांकr_sock, &err);
		अगर (!isock) अणु
			sockfd_put(csock);
			वापस err;
		पूर्ण
		ca.name[माप(ca.name)-1] = 0;

		err = hidp_connection_add(&ca, csock, isock);
		अगर (!err && copy_to_user(argp, &ca, माप(ca)))
			err = -EFAULT;

		sockfd_put(csock);
		sockfd_put(isock);

		वापस err;

	हाल HIDPCONNDEL:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&cd, argp, माप(cd)))
			वापस -EFAULT;

		वापस hidp_connection_del(&cd);

	हाल HIDPGETCONNLIST:
		अगर (copy_from_user(&cl, argp, माप(cl)))
			वापस -EFAULT;

		अगर (cl.cnum <= 0)
			वापस -EINVAL;

		err = hidp_get_connlist(&cl);
		अगर (!err && copy_to_user(argp, &cl, माप(cl)))
			वापस -EFAULT;

		वापस err;

	हाल HIDPGETCONNINFO:
		अगर (copy_from_user(&ci, argp, माप(ci)))
			वापस -EFAULT;

		err = hidp_get_conninfo(&ci);
		अगर (!err && copy_to_user(argp, &ci, माप(ci)))
			वापस -EFAULT;

		वापस err;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hidp_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस करो_hidp_sock_ioctl(sock, cmd, (व्योम __user *)arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_hidp_connadd_req अणु
	पूर्णांक   ctrl_sock;	/* Connected control socket */
	पूर्णांक   पूर्णांकr_sock;	/* Connected पूर्णांकerrupt socket */
	__u16 parser;
	__u16 rd_size;
	compat_uptr_t rd_data;
	__u8  country;
	__u8  subclass;
	__u16 venकरोr;
	__u16 product;
	__u16 version;
	__u32 flags;
	__u32 idle_to;
	अक्षर  name[128];
पूर्ण;

अटल पूर्णांक hidp_sock_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक err;

	अगर (cmd == HIDPGETCONNLIST) अणु
		काष्ठा hidp_connlist_req cl;
		u32 __user *p = argp;
		u32 uci;

		अगर (get_user(cl.cnum, p) || get_user(uci, p + 1))
			वापस -EFAULT;

		cl.ci = compat_ptr(uci);

		अगर (cl.cnum <= 0)
			वापस -EINVAL;

		err = hidp_get_connlist(&cl);

		अगर (!err && put_user(cl.cnum, p))
			err = -EFAULT;

		वापस err;
	पूर्ण अन्यथा अगर (cmd == HIDPCONNADD) अणु
		काष्ठा compat_hidp_connadd_req ca32;
		काष्ठा hidp_connadd_req ca;
		काष्ठा socket *csock;
		काष्ठा socket *isock;

		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&ca32, (व्योम __user *) arg, माप(ca32)))
			वापस -EFAULT;

		ca.ctrl_sock = ca32.ctrl_sock;
		ca.पूर्णांकr_sock = ca32.पूर्णांकr_sock;
		ca.parser = ca32.parser;
		ca.rd_size = ca32.rd_size;
		ca.rd_data = compat_ptr(ca32.rd_data);
		ca.country = ca32.country;
		ca.subclass = ca32.subclass;
		ca.venकरोr = ca32.venकरोr;
		ca.product = ca32.product;
		ca.version = ca32.version;
		ca.flags = ca32.flags;
		ca.idle_to = ca32.idle_to;
		ca32.name[माप(ca32.name) - 1] = '\0';
		स_नकल(ca.name, ca32.name, 128);

		csock = sockfd_lookup(ca.ctrl_sock, &err);
		अगर (!csock)
			वापस err;

		isock = sockfd_lookup(ca.पूर्णांकr_sock, &err);
		अगर (!isock) अणु
			sockfd_put(csock);
			वापस err;
		पूर्ण

		err = hidp_connection_add(&ca, csock, isock);
		अगर (!err && copy_to_user(argp, &ca32, माप(ca32)))
			err = -EFAULT;

		sockfd_put(csock);
		sockfd_put(isock);

		वापस err;
	पूर्ण

	वापस hidp_sock_ioctl(sock, cmd, arg);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा proto_ops hidp_sock_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= hidp_sock_release,
	.ioctl		= hidp_sock_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= hidp_sock_compat_ioctl,
#पूर्ण_अगर
	.bind		= sock_no_bind,
	.getname	= sock_no_getname,
	.sendmsg	= sock_no_sendmsg,
	.recvmsg	= sock_no_recvmsg,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.connect	= sock_no_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.mmap		= sock_no_mmap
पूर्ण;

अटल काष्ठा proto hidp_proto = अणु
	.name		= "HIDP",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा bt_sock)
पूर्ण;

अटल पूर्णांक hidp_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			    पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	BT_DBG("sock %p", sock);

	अगर (sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_BLUETOOTH, GFP_ATOMIC, &hidp_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);

	sock->ops = &hidp_sock_ops;

	sock->state = SS_UNCONNECTED;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = protocol;
	sk->sk_state	= BT_OPEN;

	bt_sock_link(&hidp_sk_list, sk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family hidp_sock_family_ops = अणु
	.family	= PF_BLUETOOTH,
	.owner	= THIS_MODULE,
	.create	= hidp_sock_create
पूर्ण;

पूर्णांक __init hidp_init_sockets(व्योम)
अणु
	पूर्णांक err;

	err = proto_रेजिस्टर(&hidp_proto, 0);
	अगर (err < 0)
		वापस err;

	err = bt_sock_रेजिस्टर(BTPROTO_HIDP, &hidp_sock_family_ops);
	अगर (err < 0) अणु
		BT_ERR("Can't register HIDP socket");
		जाओ error;
	पूर्ण

	err = bt_procfs_init(&init_net, "hidp", &hidp_sk_list, शून्य);
	अगर (err < 0) अणु
		BT_ERR("Failed to create HIDP proc file");
		bt_sock_unरेजिस्टर(BTPROTO_HIDP);
		जाओ error;
	पूर्ण

	BT_INFO("HIDP socket layer initialized");

	वापस 0;

error:
	proto_unरेजिस्टर(&hidp_proto);
	वापस err;
पूर्ण

व्योम __निकास hidp_cleanup_sockets(व्योम)
अणु
	bt_procfs_cleanup(&init_net, "hidp");
	bt_sock_unरेजिस्टर(BTPROTO_HIDP);
	proto_unरेजिस्टर(&hidp_proto);
पूर्ण
