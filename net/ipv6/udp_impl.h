<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UDP6_IMPL_H
#घोषणा _UDP6_IMPL_H
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <net/protocol.h>
#समावेश <net/addrconf.h>
#समावेश <net/inet_common.h>
#समावेश <net/transp_v6.h>

पूर्णांक __udp6_lib_rcv(काष्ठा sk_buff *, काष्ठा udp_table *, पूर्णांक);
पूर्णांक __udp6_lib_err(काष्ठा sk_buff *, काष्ठा inet6_skb_parm *, u8, u8, पूर्णांक,
		   __be32, काष्ठा udp_table *);

पूर्णांक udp_v6_get_port(काष्ठा sock *sk, अचिन्हित लघु snum);
व्योम udp_v6_rehash(काष्ठा sock *sk);

पूर्णांक udpv6_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		     अक्षर __user *optval, पूर्णांक __user *optlen);
पूर्णांक udpv6_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		     अचिन्हित पूर्णांक optlen);
पूर्णांक udpv6_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len);
पूर्णांक udpv6_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक noblock,
		  पूर्णांक flags, पूर्णांक *addr_len);
व्योम udpv6_destroy_sock(काष्ठा sock *sk);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक udp6_seq_show(काष्ठा seq_file *seq, व्योम *v);
#पूर्ण_अगर
#पूर्ण_अगर	/* _UDP6_IMPL_H */
