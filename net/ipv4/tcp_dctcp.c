<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* DataCenter TCP (DCTCP) congestion control.
 *
 * http://simula.stanक्रमd.edu/~alizade/Site/DCTCP.hपंचांगl
 *
 * This is an implementation of DCTCP over Reno, an enhancement to the
 * TCP congestion control algorithm deचिन्हित क्रम data centers. DCTCP
 * leverages Explicit Congestion Notअगरication (ECN) in the network to
 * provide multi-bit feedback to the end hosts. DCTCP's goal is to meet
 * the following three data center transport requirements:
 *
 *  - High burst tolerance (incast due to partition/aggregate)
 *  - Low latency (लघु flows, queries)
 *  - High throughput (continuous data updates, large file transfers)
 *    with commodity shallow buffered चयनes
 *
 * The algorithm is described in detail in the following two papers:
 *
 * 1) Mohammad Alizadeh, Albert Greenberg, David A. Maltz, Jitendra Padhye,
 *    Parveen Patel, Balaji Prabhakar, Sudipta Sengupta, and Murari Sridharan:
 *      "Data Center TCP (DCTCP)", Data Center Networks session
 *      Proc. ACM SIGCOMM, New Delhi, 2010.
 *   http://simula.stanक्रमd.edu/~alizade/Site/DCTCP_files/dctcp-final.pdf
 *
 * 2) Mohammad Alizadeh, Adel Javanmard, and Balaji Prabhakar:
 *      "Analysis of DCTCP: Stability, Convergence, and Fairness"
 *      Proc. ACM SIGMETRICS, San Jose, 2011.
 *   http://simula.stanक्रमd.edu/~alizade/Site/DCTCP_files/dctcp_analysis-full.pdf
 *
 * Initial prototype from Abdul Kabbani, Masato Yasuda and Mohammad Alizadeh.
 *
 * Authors:
 *
 *	Daniel Borkmann <dborkman@redhat.com>
 *	Florian Westphal <fw@म_माप.de>
 *	Glenn Judd <glenn.judd@morganstanley.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <net/tcp.h>
#समावेश <linux/inet_diag.h>
#समावेश "tcp_dctcp.h"

#घोषणा DCTCP_MAX_ALPHA	1024U

काष्ठा dctcp अणु
	u32 old_delivered;
	u32 old_delivered_ce;
	u32 prior_rcv_nxt;
	u32 dctcp_alpha;
	u32 next_seq;
	u32 ce_state;
	u32 loss_cwnd;
पूर्ण;

अटल अचिन्हित पूर्णांक dctcp_shअगरt_g __पढ़ो_mostly = 4; /* g = 1/2^4 */
module_param(dctcp_shअगरt_g, uपूर्णांक, 0644);
MODULE_PARM_DESC(dctcp_shअगरt_g, "parameter g for updating dctcp_alpha");

अटल अचिन्हित पूर्णांक dctcp_alpha_on_init __पढ़ो_mostly = DCTCP_MAX_ALPHA;
module_param(dctcp_alpha_on_init, uपूर्णांक, 0644);
MODULE_PARM_DESC(dctcp_alpha_on_init, "parameter for initial alpha value");

अटल काष्ठा tcp_congestion_ops dctcp_reno;

अटल व्योम dctcp_reset(स्थिर काष्ठा tcp_sock *tp, काष्ठा dctcp *ca)
अणु
	ca->next_seq = tp->snd_nxt;

	ca->old_delivered = tp->delivered;
	ca->old_delivered_ce = tp->delivered_ce;
पूर्ण

अटल व्योम dctcp_init(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर ((tp->ecn_flags & TCP_ECN_OK) ||
	    (sk->sk_state == TCP_LISTEN ||
	     sk->sk_state == TCP_CLOSE)) अणु
		काष्ठा dctcp *ca = inet_csk_ca(sk);

		ca->prior_rcv_nxt = tp->rcv_nxt;

		ca->dctcp_alpha = min(dctcp_alpha_on_init, DCTCP_MAX_ALPHA);

		ca->loss_cwnd = 0;
		ca->ce_state = 0;

		dctcp_reset(tp, ca);
		वापस;
	पूर्ण

	/* No ECN support? Fall back to Reno. Also need to clear
	 * ECT from sk since it is set during 3WHS क्रम DCTCP.
	 */
	inet_csk(sk)->icsk_ca_ops = &dctcp_reno;
	INET_ECN_करोntxmit(sk);
पूर्ण

अटल u32 dctcp_ssthresh(काष्ठा sock *sk)
अणु
	काष्ठा dctcp *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ca->loss_cwnd = tp->snd_cwnd;
	वापस max(tp->snd_cwnd - ((tp->snd_cwnd * ca->dctcp_alpha) >> 11U), 2U);
पूर्ण

अटल व्योम dctcp_update_alpha(काष्ठा sock *sk, u32 flags)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा dctcp *ca = inet_csk_ca(sk);

	/* Expired RTT */
	अगर (!beक्रमe(tp->snd_una, ca->next_seq)) अणु
		u32 delivered_ce = tp->delivered_ce - ca->old_delivered_ce;
		u32 alpha = ca->dctcp_alpha;

		/* alpha = (1 - g) * alpha + g * F */

		alpha -= min_not_zero(alpha, alpha >> dctcp_shअगरt_g);
		अगर (delivered_ce) अणु
			u32 delivered = tp->delivered - ca->old_delivered;

			/* If dctcp_shअगरt_g == 1, a 32bit value would overflow
			 * after 8 M packets.
			 */
			delivered_ce <<= (10 - dctcp_shअगरt_g);
			delivered_ce /= max(1U, delivered);

			alpha = min(alpha + delivered_ce, DCTCP_MAX_ALPHA);
		पूर्ण
		/* dctcp_alpha can be पढ़ो from dctcp_get_info() without
		 * synchro, so we ask compiler to not use dctcp_alpha
		 * as a temporary variable in prior operations.
		 */
		WRITE_ONCE(ca->dctcp_alpha, alpha);
		dctcp_reset(tp, ca);
	पूर्ण
पूर्ण

अटल व्योम dctcp_react_to_loss(काष्ठा sock *sk)
अणु
	काष्ठा dctcp *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ca->loss_cwnd = tp->snd_cwnd;
	tp->snd_ssthresh = max(tp->snd_cwnd >> 1U, 2U);
पूर्ण

अटल व्योम dctcp_state(काष्ठा sock *sk, u8 new_state)
अणु
	अगर (new_state == TCP_CA_Recovery &&
	    new_state != inet_csk(sk)->icsk_ca_state)
		dctcp_react_to_loss(sk);
	/* We handle RTO in dctcp_cwnd_event to ensure that we perक्रमm only
	 * one loss-adjusपंचांगent per RTT.
	 */
पूर्ण

अटल व्योम dctcp_cwnd_event(काष्ठा sock *sk, क्रमागत tcp_ca_event ev)
अणु
	काष्ठा dctcp *ca = inet_csk_ca(sk);

	चयन (ev) अणु
	हाल CA_EVENT_ECN_IS_CE:
	हाल CA_EVENT_ECN_NO_CE:
		dctcp_ece_ack_update(sk, ev, &ca->prior_rcv_nxt, &ca->ce_state);
		अवरोध;
	हाल CA_EVENT_LOSS:
		dctcp_react_to_loss(sk);
		अवरोध;
	शेष:
		/* Don't care क्रम the rest. */
		अवरोध;
	पूर्ण
पूर्ण

अटल माप_प्रकार dctcp_get_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
			     जोड़ tcp_cc_info *info)
अणु
	स्थिर काष्ठा dctcp *ca = inet_csk_ca(sk);
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* Fill it also in हाल of VEGASINFO due to req काष्ठा limits.
	 * We can still correctly retrieve it later.
	 */
	अगर (ext & (1 << (INET_DIAG_DCTCPINFO - 1)) ||
	    ext & (1 << (INET_DIAG_VEGASINFO - 1))) अणु
		स_रखो(&info->dctcp, 0, माप(info->dctcp));
		अगर (inet_csk(sk)->icsk_ca_ops != &dctcp_reno) अणु
			info->dctcp.dctcp_enabled = 1;
			info->dctcp.dctcp_ce_state = (u16) ca->ce_state;
			info->dctcp.dctcp_alpha = ca->dctcp_alpha;
			info->dctcp.dctcp_ab_ecn = tp->mss_cache *
						   (tp->delivered_ce - ca->old_delivered_ce);
			info->dctcp.dctcp_ab_tot = tp->mss_cache *
						   (tp->delivered - ca->old_delivered);
		पूर्ण

		*attr = INET_DIAG_DCTCPINFO;
		वापस माप(info->dctcp);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 dctcp_cwnd_unकरो(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा dctcp *ca = inet_csk_ca(sk);

	वापस max(tcp_sk(sk)->snd_cwnd, ca->loss_cwnd);
पूर्ण

अटल काष्ठा tcp_congestion_ops dctcp __पढ़ो_mostly = अणु
	.init		= dctcp_init,
	.in_ack_event   = dctcp_update_alpha,
	.cwnd_event	= dctcp_cwnd_event,
	.ssthresh	= dctcp_ssthresh,
	.cong_aव्योम	= tcp_reno_cong_aव्योम,
	.unकरो_cwnd	= dctcp_cwnd_unकरो,
	.set_state	= dctcp_state,
	.get_info	= dctcp_get_info,
	.flags		= TCP_CONG_NEEDS_ECN,
	.owner		= THIS_MODULE,
	.name		= "dctcp",
पूर्ण;

अटल काष्ठा tcp_congestion_ops dctcp_reno __पढ़ो_mostly = अणु
	.ssthresh	= tcp_reno_ssthresh,
	.cong_aव्योम	= tcp_reno_cong_aव्योम,
	.unकरो_cwnd	= tcp_reno_unकरो_cwnd,
	.get_info	= dctcp_get_info,
	.owner		= THIS_MODULE,
	.name		= "dctcp-reno",
पूर्ण;

अटल पूर्णांक __init dctcp_रेजिस्टर(व्योम)
अणु
	BUILD_BUG_ON(माप(काष्ठा dctcp) > ICSK_CA_PRIV_SIZE);
	वापस tcp_रेजिस्टर_congestion_control(&dctcp);
पूर्ण

अटल व्योम __निकास dctcp_unरेजिस्टर(व्योम)
अणु
	tcp_unरेजिस्टर_congestion_control(&dctcp);
पूर्ण

module_init(dctcp_रेजिस्टर);
module_निकास(dctcp_unरेजिस्टर);

MODULE_AUTHOR("Daniel Borkmann <dborkman@redhat.com>");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_AUTHOR("Glenn Judd <glenn.judd@morganstanley.com>");

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DataCenter TCP (DCTCP)");
