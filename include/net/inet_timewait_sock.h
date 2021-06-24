<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम a generic INET TIMEWAIT sock
 *
 *		From code originally in net/tcp.h
 */
#अगर_अघोषित _INET_TIMEWAIT_SOCK_
#घोषणा _INET_TIMEWAIT_SOCK_

#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <net/inet_sock.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/समयरुको_sock.h>

#समावेश <linux/atomic.h>

काष्ठा inet_bind_bucket;

/*
 * This is a TIME_WAIT sock. It works around the memory consumption
 * problems of sockets in such a state on heavily loaded servers, but
 * without violating the protocol specअगरication.
 */
काष्ठा inet_समयरुको_sock अणु
	/*
	 * Now काष्ठा sock also uses sock_common, so please just
	 * करोn't add nothing beक्रमe this first member (__tw_common) --acme
	 */
	काष्ठा sock_common	__tw_common;
#घोषणा tw_family		__tw_common.skc_family
#घोषणा tw_state		__tw_common.skc_state
#घोषणा tw_reuse		__tw_common.skc_reuse
#घोषणा tw_reuseport		__tw_common.skc_reuseport
#घोषणा tw_ipv6only		__tw_common.skc_ipv6only
#घोषणा tw_bound_dev_अगर		__tw_common.skc_bound_dev_अगर
#घोषणा tw_node			__tw_common.skc_nulls_node
#घोषणा tw_bind_node		__tw_common.skc_bind_node
#घोषणा tw_refcnt		__tw_common.skc_refcnt
#घोषणा tw_hash			__tw_common.skc_hash
#घोषणा tw_prot			__tw_common.skc_prot
#घोषणा tw_net			__tw_common.skc_net
#घोषणा tw_daddr        	__tw_common.skc_daddr
#घोषणा tw_v6_daddr		__tw_common.skc_v6_daddr
#घोषणा tw_rcv_saddr    	__tw_common.skc_rcv_saddr
#घोषणा tw_v6_rcv_saddr    	__tw_common.skc_v6_rcv_saddr
#घोषणा tw_dport		__tw_common.skc_dport
#घोषणा tw_num			__tw_common.skc_num
#घोषणा tw_cookie		__tw_common.skc_cookie
#घोषणा tw_dr			__tw_common.skc_tw_dr

	__u32			tw_mark;
	अस्थिर अचिन्हित अक्षर	tw_substate;
	अचिन्हित अक्षर		tw_rcv_wscale;

	/* Socket demultiplex comparisons on incoming packets. */
	/* these three are in inet_sock */
	__be16			tw_sport;
	/* And these are ours. */
	अचिन्हित पूर्णांक		tw_समाप्त		: 1,
				tw_transparent  : 1,
				tw_flowlabel	: 20,
				tw_pad		: 2,	/* 2 bits hole */
				tw_tos		: 8;
	u32			tw_txhash;
	u32			tw_priority;
	काष्ठा समयr_list	tw_समयr;
	काष्ठा inet_bind_bucket	*tw_tb;
पूर्ण;
#घोषणा tw_tclass tw_tos

अटल अंतरभूत काष्ठा inet_समयरुको_sock *inet_twsk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा inet_समयरुको_sock *)sk;
पूर्ण

व्योम inet_twsk_मुक्त(काष्ठा inet_समयरुको_sock *tw);
व्योम inet_twsk_put(काष्ठा inet_समयरुको_sock *tw);

व्योम inet_twsk_bind_unhash(काष्ठा inet_समयरुको_sock *tw,
			   काष्ठा inet_hashinfo *hashinfo);

काष्ठा inet_समयरुको_sock *inet_twsk_alloc(स्थिर काष्ठा sock *sk,
					   काष्ठा inet_समयरुको_death_row *dr,
					   स्थिर पूर्णांक state);

व्योम inet_twsk_hashdance(काष्ठा inet_समयरुको_sock *tw, काष्ठा sock *sk,
			 काष्ठा inet_hashinfo *hashinfo);

व्योम __inet_twsk_schedule(काष्ठा inet_समयरुको_sock *tw, पूर्णांक समयo,
			  bool rearm);

अटल अंतरभूत व्योम inet_twsk_schedule(काष्ठा inet_समयरुको_sock *tw, पूर्णांक समयo)
अणु
	__inet_twsk_schedule(tw, समयo, false);
पूर्ण

अटल अंतरभूत व्योम inet_twsk_reschedule(काष्ठा inet_समयरुको_sock *tw, पूर्णांक समयo)
अणु
	__inet_twsk_schedule(tw, समयo, true);
पूर्ण

व्योम inet_twsk_deschedule_put(काष्ठा inet_समयरुको_sock *tw);

व्योम inet_twsk_purge(काष्ठा inet_hashinfo *hashinfo, पूर्णांक family);

अटल अंतरभूत
काष्ठा net *twsk_net(स्थिर काष्ठा inet_समयरुको_sock *twsk)
अणु
	वापस पढ़ो_pnet(&twsk->tw_net);
पूर्ण

अटल अंतरभूत
व्योम twsk_net_set(काष्ठा inet_समयरुको_sock *twsk, काष्ठा net *net)
अणु
	ग_लिखो_pnet(&twsk->tw_net, net);
पूर्ण
#पूर्ण_अगर	/* _INET_TIMEWAIT_SOCK_ */
