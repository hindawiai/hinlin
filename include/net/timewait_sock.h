<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NET		Generic infraकाष्ठाure क्रम Network protocols.
 *
 * Authors:	Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */
#अगर_अघोषित _TIMEWAIT_SOCK_H
#घोषणा _TIMEWAIT_SOCK_H

#समावेश <linux/slab.h>
#समावेश <linux/bug.h>
#समावेश <net/sock.h>

काष्ठा समयरुको_sock_ops अणु
	काष्ठा kmem_cache	*twsk_slab;
	अक्षर		*twsk_slab_name;
	अचिन्हित पूर्णांक	twsk_obj_size;
	पूर्णांक		(*twsk_unique)(काष्ठा sock *sk,
				       काष्ठा sock *sktw, व्योम *twp);
	व्योम		(*twsk_deकाष्ठाor)(काष्ठा sock *sk);
पूर्ण;

अटल अंतरभूत पूर्णांक twsk_unique(काष्ठा sock *sk, काष्ठा sock *sktw, व्योम *twp)
अणु
	अगर (sk->sk_prot->twsk_prot->twsk_unique != शून्य)
		वापस sk->sk_prot->twsk_prot->twsk_unique(sk, sktw, twp);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम twsk_deकाष्ठाor(काष्ठा sock *sk)
अणु
	अगर (sk->sk_prot->twsk_prot->twsk_deकाष्ठाor != शून्य)
		sk->sk_prot->twsk_prot->twsk_deकाष्ठाor(sk);
पूर्ण

#पूर्ण_अगर /* _TIMEWAIT_SOCK_H */
