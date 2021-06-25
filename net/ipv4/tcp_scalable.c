<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Tom Kelly's Scalable TCP
 *
 * See http://www.deneholme.net/tom/scalable/
 *
 * John Heffner <jheffner@sc.edu>
 */

#समावेश <linux/module.h>
#समावेश <net/tcp.h>

/* These factors derived from the recommended values in the aer:
 * .01 and 7/8.
 */
#घोषणा TCP_SCALABLE_AI_CNT	100U
#घोषणा TCP_SCALABLE_MD_SCALE	3

अटल व्योम tcp_scalable_cong_aव्योम(काष्ठा sock *sk, u32 ack, u32 acked)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (!tcp_is_cwnd_limited(sk))
		वापस;

	अगर (tcp_in_slow_start(tp)) अणु
		acked = tcp_slow_start(tp, acked);
		अगर (!acked)
			वापस;
	पूर्ण
	tcp_cong_aव्योम_ai(tp, min(tp->snd_cwnd, TCP_SCALABLE_AI_CNT),
			  acked);
पूर्ण

अटल u32 tcp_scalable_ssthresh(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	वापस max(tp->snd_cwnd - (tp->snd_cwnd>>TCP_SCALABLE_MD_SCALE), 2U);
पूर्ण

अटल काष्ठा tcp_congestion_ops tcp_scalable __पढ़ो_mostly = अणु
	.ssthresh	= tcp_scalable_ssthresh,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.cong_aव्योम	= tcp_scalable_cong_aव्योम,

	.owner		= THIS_MODULE,
	.name		= "scalable",
पूर्ण;

अटल पूर्णांक __init tcp_scalable_रेजिस्टर(व्योम)
अणु
	वापस tcp_रेजिस्टर_congestion_control(&tcp_scalable);
पूर्ण

अटल व्योम __निकास tcp_scalable_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&tcp_scalable);
पूर्ण

module_init(tcp_scalable_रेजिस्टर);
module_निकास(tcp_scalable_unरेजिस्टर);

MODULE_AUTHOR("John Heffner");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Scalable TCP");
