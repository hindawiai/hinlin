<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/** -*- linux-c -*- ***********************************************************
 * Linux PPP over X/Ethernet (PPPoX/PPPoE) Sockets
 *
 * PPPoX --- Generic PPP encapsulation socket family
 * PPPoE --- PPP over Ethernet (RFC 2516)
 *
 * Version:	0.5.2
 *
 * Author:	Michal Ostrowski <mostrows@speakeasy.net>
 *
 * 051000 :	Initialization cleanup
 *
 * License:
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compat.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/net.h>
#समावेश <linux/init.h>
#समावेश <linux/अगर_pppox.h>
#समावेश <linux/ppp_defs.h>
#समावेश <linux/ppp-ioctl.h>
#समावेश <linux/ppp_channel.h>
#समावेश <linux/kmod.h>

#समावेश <net/sock.h>

#समावेश <linux/uaccess.h>

अटल स्थिर काष्ठा pppox_proto *pppox_protos[PX_MAX_PROTO + 1];

पूर्णांक रेजिस्टर_pppox_proto(पूर्णांक proto_num, स्थिर काष्ठा pppox_proto *pp)
अणु
	अगर (proto_num < 0 || proto_num > PX_MAX_PROTO)
		वापस -EINVAL;
	अगर (pppox_protos[proto_num])
		वापस -EALREADY;
	pppox_protos[proto_num] = pp;
	वापस 0;
पूर्ण

व्योम unरेजिस्टर_pppox_proto(पूर्णांक proto_num)
अणु
	अगर (proto_num >= 0 && proto_num <= PX_MAX_PROTO)
		pppox_protos[proto_num] = शून्य;
पूर्ण

व्योम pppox_unbind_sock(काष्ठा sock *sk)
अणु
	/* Clear connection to ppp device, अगर attached. */

	अगर (sk->sk_state & (PPPOX_BOUND | PPPOX_CONNECTED)) अणु
		ppp_unरेजिस्टर_channel(&pppox_sk(sk)->chan);
		sk->sk_state = PPPOX_DEAD;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(रेजिस्टर_pppox_proto);
EXPORT_SYMBOL(unरेजिस्टर_pppox_proto);
EXPORT_SYMBOL(pppox_unbind_sock);

पूर्णांक pppox_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा pppox_sock *po = pppox_sk(sk);
	पूर्णांक rc;

	lock_sock(sk);

	चयन (cmd) अणु
	हाल PPPIOCGCHAN: अणु
		पूर्णांक index;
		rc = -ENOTCONN;
		अगर (!(sk->sk_state & PPPOX_CONNECTED))
			अवरोध;

		rc = -EINVAL;
		index = ppp_channel_index(&po->chan);
		अगर (put_user(index , (पूर्णांक __user *) arg))
			अवरोध;

		rc = 0;
		sk->sk_state |= PPPOX_BOUND;
		अवरोध;
	पूर्ण
	शेष:
		rc = pppox_protos[sk->sk_protocol]->ioctl ?
			pppox_protos[sk->sk_protocol]->ioctl(sock, cmd, arg) : -ENOTTY;
	पूर्ण

	release_sock(sk);
	वापस rc;
पूर्ण

EXPORT_SYMBOL(pppox_ioctl);

#अगर_घोषित CONFIG_COMPAT
पूर्णांक pppox_compat_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (cmd == PPPOEIOCSFWD32)
		cmd = PPPOEIOCSFWD;

	वापस pppox_ioctl(sock, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण

EXPORT_SYMBOL(pppox_compat_ioctl);
#पूर्ण_अगर

अटल पूर्णांक pppox_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			पूर्णांक kern)
अणु
	पूर्णांक rc = -EPROTOTYPE;

	अगर (protocol < 0 || protocol > PX_MAX_PROTO)
		जाओ out;

	rc = -EPROTONOSUPPORT;
	अगर (!pppox_protos[protocol])
		request_module("net-pf-%d-proto-%d", PF_PPPOX, protocol);
	अगर (!pppox_protos[protocol] ||
	    !try_module_get(pppox_protos[protocol]->owner))
		जाओ out;

	rc = pppox_protos[protocol]->create(net, sock, kern);

	module_put(pppox_protos[protocol]->owner);
out:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_proto_family pppox_proto_family = अणु
	.family	= PF_PPPOX,
	.create	= pppox_create,
	.owner	= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init pppox_init(व्योम)
अणु
	वापस sock_रेजिस्टर(&pppox_proto_family);
पूर्ण

अटल व्योम __निकास pppox_निकास(व्योम)
अणु
	sock_unरेजिस्टर(PF_PPPOX);
पूर्ण

module_init(pppox_init);
module_निकास(pppox_निकास);

MODULE_AUTHOR("Michal Ostrowski <mostrows@speakeasy.net>");
MODULE_DESCRIPTION("PPP over Ethernet driver (generic socket layer)");
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_PPPOX);
