<शैली गुरु>
/*
   CMTP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2002-2003 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

#समावेश <linux/types.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/poll.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/file.h>
#समावेश <linux/compat.h>
#समावेश <linux/gfp.h>
#समावेश <linux/uaccess.h>
#समावेश <net/sock.h>

#समावेश <linux/isdn/capilli.h>


#समावेश "cmtp.h"

अटल काष्ठा bt_sock_list cmtp_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(cmtp_sk_list.lock)
पूर्ण;

अटल पूर्णांक cmtp_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	BT_DBG("sock %p sk %p", sock, sk);

	अगर (!sk)
		वापस 0;

	bt_sock_unlink(&cmtp_sk_list, sk);

	sock_orphan(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_cmtp_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, व्योम __user *argp)
अणु
	काष्ठा cmtp_connadd_req ca;
	काष्ठा cmtp_conndel_req cd;
	काष्ठा cmtp_connlist_req cl;
	काष्ठा cmtp_conninfo ci;
	काष्ठा socket *nsock;
	पूर्णांक err;

	BT_DBG("cmd %x arg %p", cmd, argp);

	चयन (cmd) अणु
	हाल CMTPCONNADD:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&ca, argp, माप(ca)))
			वापस -EFAULT;

		nsock = sockfd_lookup(ca.sock, &err);
		अगर (!nsock)
			वापस err;

		अगर (nsock->sk->sk_state != BT_CONNECTED) अणु
			sockfd_put(nsock);
			वापस -EBADFD;
		पूर्ण

		err = cmtp_add_connection(&ca, nsock);
		अगर (!err) अणु
			अगर (copy_to_user(argp, &ca, माप(ca)))
				err = -EFAULT;
		पूर्ण अन्यथा
			sockfd_put(nsock);

		वापस err;

	हाल CMTPCONNDEL:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;

		अगर (copy_from_user(&cd, argp, माप(cd)))
			वापस -EFAULT;

		वापस cmtp_del_connection(&cd);

	हाल CMTPGETCONNLIST:
		अगर (copy_from_user(&cl, argp, माप(cl)))
			वापस -EFAULT;

		अगर (cl.cnum <= 0)
			वापस -EINVAL;

		err = cmtp_get_connlist(&cl);
		अगर (!err && copy_to_user(argp, &cl, माप(cl)))
			वापस -EFAULT;

		वापस err;

	हाल CMTPGETCONNINFO:
		अगर (copy_from_user(&ci, argp, माप(ci)))
			वापस -EFAULT;

		err = cmtp_get_conninfo(&ci);
		अगर (!err && copy_to_user(argp, &ci, माप(ci)))
			वापस -EFAULT;

		वापस err;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cmtp_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस करो_cmtp_sock_ioctl(sock, cmd, (व्योम __user *)arg);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक cmtp_sock_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = compat_ptr(arg);
	अगर (cmd == CMTPGETCONNLIST) अणु
		काष्ठा cmtp_connlist_req cl;
		u32 __user *p = argp;
		u32 uci;
		पूर्णांक err;

		अगर (get_user(cl.cnum, p) || get_user(uci, p + 1))
			वापस -EFAULT;

		cl.ci = compat_ptr(uci);

		अगर (cl.cnum <= 0)
			वापस -EINVAL;

		err = cmtp_get_connlist(&cl);

		अगर (!err && put_user(cl.cnum, p))
			err = -EFAULT;

		वापस err;
	पूर्ण

	वापस करो_cmtp_sock_ioctl(sock, cmd, argp);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा proto_ops cmtp_sock_ops = अणु
	.family		= PF_BLUETOOTH,
	.owner		= THIS_MODULE,
	.release	= cmtp_sock_release,
	.ioctl		= cmtp_sock_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= cmtp_sock_compat_ioctl,
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

अटल काष्ठा proto cmtp_proto = अणु
	.name		= "CMTP",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा bt_sock)
पूर्ण;

अटल पूर्णांक cmtp_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			    पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	BT_DBG("sock %p", sock);

	अगर (sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_BLUETOOTH, GFP_ATOMIC, &cmtp_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);

	sock->ops = &cmtp_sock_ops;

	sock->state = SS_UNCONNECTED;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = protocol;
	sk->sk_state    = BT_OPEN;

	bt_sock_link(&cmtp_sk_list, sk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family cmtp_sock_family_ops = अणु
	.family	= PF_BLUETOOTH,
	.owner	= THIS_MODULE,
	.create	= cmtp_sock_create
पूर्ण;

पूर्णांक cmtp_init_sockets(व्योम)
अणु
	पूर्णांक err;

	err = proto_रेजिस्टर(&cmtp_proto, 0);
	अगर (err < 0)
		वापस err;

	err = bt_sock_रेजिस्टर(BTPROTO_CMTP, &cmtp_sock_family_ops);
	अगर (err < 0) अणु
		BT_ERR("Can't register CMTP socket");
		जाओ error;
	पूर्ण

	err = bt_procfs_init(&init_net, "cmtp", &cmtp_sk_list, शून्य);
	अगर (err < 0) अणु
		BT_ERR("Failed to create CMTP proc file");
		bt_sock_unरेजिस्टर(BTPROTO_HIDP);
		जाओ error;
	पूर्ण

	BT_INFO("CMTP socket layer initialized");

	वापस 0;

error:
	proto_unरेजिस्टर(&cmtp_proto);
	वापस err;
पूर्ण

व्योम cmtp_cleanup_sockets(व्योम)
अणु
	bt_procfs_cleanup(&init_net, "cmtp");
	bt_sock_unरेजिस्टर(BTPROTO_CMTP);
	proto_unरेजिस्टर(&cmtp_proto);
पूर्ण
