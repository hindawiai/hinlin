<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * TCP Vegas congestion control पूर्णांकerface
 */
#अगर_अघोषित __TCP_VEGAS_H
#घोषणा __TCP_VEGAS_H 1

/* Vegas variables */
काष्ठा vegas अणु
	u32	beg_snd_nxt;	/* right edge during last RTT */
	u32	beg_snd_una;	/* left edge  during last RTT */
	u32	beg_snd_cwnd;	/* saves the size of the cwnd */
	u8	करोing_vegas_now;/* अगर true, करो vegas क्रम this RTT */
	u16	cntRTT;		/* # of RTTs measured within last RTT */
	u32	minRTT;		/* min of RTTs measured within last RTT (in usec) */
	u32	baseRTT;	/* the min of all Vegas RTT measurements seen (in usec) */
पूर्ण;

व्योम tcp_vegas_init(काष्ठा sock *sk);
व्योम tcp_vegas_state(काष्ठा sock *sk, u8 ca_state);
व्योम tcp_vegas_pkts_acked(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample);
व्योम tcp_vegas_cwnd_event(काष्ठा sock *sk, क्रमागत tcp_ca_event event);
माप_प्रकार tcp_vegas_get_info(काष्ठा sock *sk, u32 ext, पूर्णांक *attr,
			  जोड़ tcp_cc_info *info);

#पूर्ण_अगर	/* __TCP_VEGAS_H */
