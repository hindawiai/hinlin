<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_ESPINTCP_H
#घोषणा _NET_ESPINTCP_H

#समावेश <net/strparser.h>
#समावेश <linux/skmsg.h>

व्योम __init espपूर्णांकcp_init(व्योम);

पूर्णांक espपूर्णांकcp_push_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक espपूर्णांकcp_queue_out(काष्ठा sock *sk, काष्ठा sk_buff *skb);
bool tcp_is_ulp_esp(काष्ठा sock *sk);

काष्ठा espपूर्णांकcp_msg अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_msg skmsg;
	पूर्णांक offset;
	पूर्णांक len;
पूर्ण;

काष्ठा espपूर्णांकcp_ctx अणु
	काष्ठा strparser strp;
	काष्ठा sk_buff_head ike_queue;
	काष्ठा sk_buff_head out_queue;
	काष्ठा espपूर्णांकcp_msg partial;
	व्योम (*saved_data_पढ़ोy)(काष्ठा sock *sk);
	व्योम (*saved_ग_लिखो_space)(काष्ठा sock *sk);
	व्योम (*saved_deकाष्ठा)(काष्ठा sock *sk);
	काष्ठा work_काष्ठा work;
	bool tx_running;
पूर्ण;

अटल अंतरभूत काष्ठा espपूर्णांकcp_ctx *espपूर्णांकcp_अ_लोtx(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	/* RCU is only needed क्रम diag */
	वापस (__क्रमce व्योम *)icsk->icsk_ulp_data;
पूर्ण
#पूर्ण_अगर
