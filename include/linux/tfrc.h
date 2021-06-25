<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _LINUX_TFRC_H_
#घोषणा _LINUX_TFRC_H_
/*
 *  TFRC - Data Structures क्रम the TCP-Friendly Rate Control congestion
 *         control mechanism as specअगरied in RFC 3448.
 *
 *  Copyright (c) 2005 The University of Waikato, Hamilton, New Zealand.
 *  Copyright (c) 2005 Ian McDonald <iam4@cs.waikato.ac.nz>
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *  Copyright (c) 2003 Nils-Erik Mattsson, Joacim Haggmark, Magnus Erixzon
 */
#समावेश <linux/types.h>

/** 	tfrc_rx_info    -    TFRC Receiver Data Structure
 *
 * 	@tfrcrx_x_recv:	receiver estimate of sending rate (3.2.2)
 * 	@tfrcrx_rtt:	round-trip-समय (communicated by sender)
 * 	@tfrcrx_p:	current estimate of loss event rate (3.2.2)
 */
काष्ठा tfrc_rx_info अणु
  	__u32 tfrcrx_x_recv;
	__u32 tfrcrx_rtt;
  	__u32 tfrcrx_p;
पूर्ण;

/** 	tfrc_tx_info    -    TFRC Sender Data Structure
 *
 * 	@tfrctx_x:	computed transmit rate (4.3 (4))
 * 	@tfrctx_x_recv: receiver estimate of send rate (4.3)
 * 	@tfrctx_x_calc:	वापस value of throughput equation (3.1)
 * 	@tfrctx_rtt:	(moving average) estimate of RTT (4.3)
 * 	@tfrctx_p:	current loss event rate (5.4)
 * 	@tfrctx_rto:	estimate of RTO, equals 4*RTT (4.3)
 * 	@tfrctx_ipi:	पूर्णांकer-packet पूर्णांकerval (4.6)
 *
 *  Note: X and X_recv are both मुख्यtained in units of 64 * bytes/second. This
 *        enables a finer resolution of sending rates and aव्योमs problems with
 *        पूर्णांकeger arithmetic; u32 is not sufficient as scaling consumes 6 bits.
 */
काष्ठा tfrc_tx_info अणु
	__u64 tfrctx_x;
	__u64 tfrctx_x_recv;
	__u32 tfrctx_x_calc;
	__u32 tfrctx_rtt;
	__u32 tfrctx_p;
	__u32 tfrctx_rto;
	__u32 tfrctx_ipi;
पूर्ण;

#पूर्ण_अगर /* _LINUX_TFRC_H_ */
