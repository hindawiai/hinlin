<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _UDP4_IMPL_H
#घोषणा _UDP4_IMPL_H
#समावेश <net/udp.h>
#समावेश <net/udplite.h>
#समावेश <net/protocol.h>
#समावेश <net/inet_common.h>

पूर्णांक __udp4_lib_rcv(काष्ठा sk_buff *, काष्ठा udp_table *, पूर्णांक);
पूर्णांक __udp4_lib_err(काष्ठा sk_buff *, u32, काष्ठा udp_table *);

पूर्णांक udp_v4_get_port(काष्ठा sock *sk, अचिन्हित लघु snum);
व्योम udp_v4_rehash(काष्ठा sock *sk);

पूर्णांक udp_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname, sockptr_t optval,
		   अचिन्हित पूर्णांक optlen);
पूर्णांक udp_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
		   अक्षर __user *optval, पूर्णांक __user *optlen);

पूर्णांक udp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len, पूर्णांक noblock,
		पूर्णांक flags, पूर्णांक *addr_len);
पूर्णांक udp_sendpage(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset, माप_प्रकार size,
		 पूर्णांक flags);
व्योम udp_destroy_sock(काष्ठा sock *sk);

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक udp4_seq_show(काष्ठा seq_file *seq, व्योम *v);
#पूर्ण_अगर
#पूर्ण_अगर	/* _UDP4_IMPL_H */
