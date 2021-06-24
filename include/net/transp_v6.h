<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TRANSP_V6_H
#घोषणा _TRANSP_V6_H

#समावेश <net/checksum.h>

/* IPv6 transport protocols */
बाह्य काष्ठा proto rawv6_prot;
बाह्य काष्ठा proto udpv6_prot;
बाह्य काष्ठा proto udplitev6_prot;
बाह्य काष्ठा proto tcpv6_prot;
बाह्य काष्ठा proto pingv6_prot;

काष्ठा flowi6;

/* extension headers */
पूर्णांक ipv6_exthdrs_init(व्योम);
व्योम ipv6_exthdrs_निकास(व्योम);
पूर्णांक ipv6_frag_init(व्योम);
व्योम ipv6_frag_निकास(व्योम);

/* transport protocols */
पूर्णांक pingv6_init(व्योम);
व्योम pingv6_निकास(व्योम);
पूर्णांक rawv6_init(व्योम);
व्योम rawv6_निकास(व्योम);
पूर्णांक udpv6_init(व्योम);
व्योम udpv6_निकास(व्योम);
पूर्णांक udplitev6_init(व्योम);
व्योम udplitev6_निकास(व्योम);
पूर्णांक tcpv6_init(व्योम);
व्योम tcpv6_निकास(व्योम);

पूर्णांक udpv6_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक addr_len);

/* this करोes all the common and the specअगरic ctl work */
व्योम ip6_datagram_recv_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
			   काष्ठा sk_buff *skb);
व्योम ip6_datagram_recv_common_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
				  काष्ठा sk_buff *skb);
व्योम ip6_datagram_recv_specअगरic_ctl(काष्ठा sock *sk, काष्ठा msghdr *msg,
				    काष्ठा sk_buff *skb);

पूर्णांक ip6_datagram_send_ctl(काष्ठा net *net, काष्ठा sock *sk, काष्ठा msghdr *msg,
			  काष्ठा flowi6 *fl6, काष्ठा ipcm6_cookie *ipc6);

व्योम __ip6_dgram_sock_seq_show(काष्ठा seq_file *seq, काष्ठा sock *sp,
			       __u16 srcp, __u16 destp, पूर्णांक rqueue, पूर्णांक bucket);
अटल अंतरभूत व्योम
ip6_dgram_sock_seq_show(काष्ठा seq_file *seq, काष्ठा sock *sp, __u16 srcp,
			__u16 destp, पूर्णांक bucket)
अणु
	__ip6_dgram_sock_seq_show(seq, sp, srcp, destp, sk_rmem_alloc_get(sp),
				  bucket);
पूर्ण

#घोषणा LOOPBACK4_IPV6 cpu_to_be32(0x7f000006)

व्योम inet6_destroy_sock(काष्ठा sock *sk);

#घोषणा IPV6_SEQ_DGRAM_HEADER					       \
	"  sl  "						       \
	"local_address                         "		       \
	"remote_address                        "		       \
	"st tx_queue rx_queue tr tm->when retrnsmt"		       \
	"   uid  timeout inode ref pointer drops\n"

#पूर्ण_अगर
