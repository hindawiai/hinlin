<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * net busy poll support
 * Copyright(c) 2013 Intel Corporation.
 *
 * Author: Eliezer Tamir
 *
 * Contact Inक्रमmation:
 * e1000-devel Mailing List <e1000-devel@lists.sourceक्रमge.net>
 */

#अगर_अघोषित _LINUX_NET_BUSY_POLL_H
#घोषणा _LINUX_NET_BUSY_POLL_H

#समावेश <linux/netdevice.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <net/ip.h>

/*		0 - Reserved to indicate value not set
 *     1..NR_CPUS - Reserved क्रम sender_cpu
 *  NR_CPUS+1..~0 - Region available क्रम NAPI IDs
 */
#घोषणा MIN_NAPI_ID ((अचिन्हित पूर्णांक)(NR_CPUS + 1))

#घोषणा BUSY_POLL_BUDGET 8

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL

काष्ठा napi_काष्ठा;
बाह्य अचिन्हित पूर्णांक sysctl_net_busy_पढ़ो __पढ़ो_mostly;
बाह्य अचिन्हित पूर्णांक sysctl_net_busy_poll __पढ़ो_mostly;

अटल अंतरभूत bool net_busy_loop_on(व्योम)
अणु
	वापस sysctl_net_busy_poll;
पूर्ण

अटल अंतरभूत bool sk_can_busy_loop(स्थिर काष्ठा sock *sk)
अणु
	वापस sk->sk_ll_usec && !संकेत_pending(current);
पूर्ण

bool sk_busy_loop_end(व्योम *p, अचिन्हित दीर्घ start_समय);

व्योम napi_busy_loop(अचिन्हित पूर्णांक napi_id,
		    bool (*loop_end)(व्योम *, अचिन्हित दीर्घ),
		    व्योम *loop_end_arg, bool prefer_busy_poll, u16 budget);

#अन्यथा /* CONFIG_NET_RX_BUSY_POLL */
अटल अंतरभूत अचिन्हित दीर्घ net_busy_loop_on(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool sk_can_busy_loop(काष्ठा sock *sk)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_NET_RX_BUSY_POLL */

अटल अंतरभूत अचिन्हित दीर्घ busy_loop_current_समय(व्योम)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	वापस (अचिन्हित दीर्घ)(local_घड़ी() >> 10);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/* in poll/select we use the global sysctl_net_ll_poll value */
अटल अंतरभूत bool busy_loop_समयout(अचिन्हित दीर्घ start_समय)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित दीर्घ bp_usec = READ_ONCE(sysctl_net_busy_poll);

	अगर (bp_usec) अणु
		अचिन्हित दीर्घ end_समय = start_समय + bp_usec;
		अचिन्हित दीर्घ now = busy_loop_current_समय();

		वापस समय_after(now, end_समय);
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल अंतरभूत bool sk_busy_loop_समयout(काष्ठा sock *sk,
					अचिन्हित दीर्घ start_समय)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित दीर्घ bp_usec = READ_ONCE(sk->sk_ll_usec);

	अगर (bp_usec) अणु
		अचिन्हित दीर्घ end_समय = start_समय + bp_usec;
		अचिन्हित दीर्घ now = busy_loop_current_समय();

		वापस समय_after(now, end_समय);
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल अंतरभूत व्योम sk_busy_loop(काष्ठा sock *sk, पूर्णांक nonblock)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अचिन्हित पूर्णांक napi_id = READ_ONCE(sk->sk_napi_id);

	अगर (napi_id >= MIN_NAPI_ID)
		napi_busy_loop(napi_id, nonblock ? शून्य : sk_busy_loop_end, sk,
			       READ_ONCE(sk->sk_prefer_busy_poll),
			       READ_ONCE(sk->sk_busy_poll_budget) ?: BUSY_POLL_BUDGET);
#पूर्ण_अगर
पूर्ण

/* used in the NIC receive handler to mark the skb */
अटल अंतरभूत व्योम skb_mark_napi_id(काष्ठा sk_buff *skb,
				    काष्ठा napi_काष्ठा *napi)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	/* If the skb was alपढ़ोy marked with a valid NAPI ID, aव्योम overwriting
	 * it.
	 */
	अगर (skb->napi_id < MIN_NAPI_ID)
		skb->napi_id = napi->napi_id;
#पूर्ण_अगर
पूर्ण

/* used in the protocol hanlder to propagate the napi_id to the socket */
अटल अंतरभूत व्योम sk_mark_napi_id(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	WRITE_ONCE(sk->sk_napi_id, skb->napi_id);
#पूर्ण_अगर
	sk_rx_queue_set(sk, skb);
पूर्ण

अटल अंतरभूत व्योम __sk_mark_napi_id_once(काष्ठा sock *sk, अचिन्हित पूर्णांक napi_id)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	अगर (!READ_ONCE(sk->sk_napi_id))
		WRITE_ONCE(sk->sk_napi_id, napi_id);
#पूर्ण_अगर
पूर्ण

/* variant used क्रम unconnected sockets */
अटल अंतरभूत व्योम sk_mark_napi_id_once(काष्ठा sock *sk,
					स्थिर काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	__sk_mark_napi_id_once(sk, skb->napi_id);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sk_mark_napi_id_once_xdp(काष्ठा sock *sk,
					    स्थिर काष्ठा xdp_buff *xdp)
अणु
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	__sk_mark_napi_id_once(sk, xdp->rxq->napi_id);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _LINUX_NET_BUSY_POLL_H */
