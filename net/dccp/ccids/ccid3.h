<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 2005-7 The University of Waikato, Hamilton, New Zealand.
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *
 *  An implementation of the DCCP protocol
 *
 *  This code has been developed by the University of Waikato WAND
 *  research group. For further inक्रमmation please see https://www.wand.net.nz/
 *  or e-mail Ian McDonald - ian.mcकरोnald@jandi.co.nz
 *
 *  This code also uses code from Lulea University, rereleased as GPL by its
 *  authors:
 *  Copyright (c) 2003 Nils-Erik Mattsson, Joacim Haggmark, Magnus Erixzon
 *
 *  Changes to meet Linux coding standards, to make it meet latest ccid3 draft
 *  and to make it work as a loadable module in the DCCP stack written by
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>.
 *
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */
#अगर_अघोषित _DCCP_CCID3_H_
#घोषणा _DCCP_CCID3_H_

#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/tfrc.h>
#समावेश "lib/tfrc.h"
#समावेश "../ccid.h"

/* Two seconds as per RFC 5348, 4.2 */
#घोषणा TFRC_INITIAL_TIMEOUT	   (2 * USEC_PER_SEC)

/* Parameter t_mbi from [RFC 3448, 4.3]: backoff पूर्णांकerval in seconds */
#घोषणा TFRC_T_MBI		   64

/*
 * The t_delta parameter (RFC 5348, 8.3): delays of less than %USEC_PER_MSEC are
 * rounded करोwn to 0, since sk_reset_समयr() here uses millisecond granularity.
 * Hence we can use a स्थिरant t_delta = %USEC_PER_MSEC when HZ >= 500. A coarse
 * resolution of HZ < 500 means that the error is below one समयr tick (t_gran)
 * when using the स्थिरant t_delta  =  t_gran / 2  =  %USEC_PER_SEC / (2 * HZ).
 */
#अगर (HZ >= 500)
# define TFRC_T_DELTA		   USEC_PER_MSEC
#अन्यथा
# define TFRC_T_DELTA		   (USEC_PER_SEC / (2 * HZ))
#पूर्ण_अगर

क्रमागत ccid3_options अणु
	TFRC_OPT_LOSS_EVENT_RATE = 192,
	TFRC_OPT_LOSS_INTERVALS	 = 193,
	TFRC_OPT_RECEIVE_RATE	 = 194,
पूर्ण;

/* TFRC sender states */
क्रमागत ccid3_hc_tx_states अणु
	TFRC_SSTATE_NO_SENT = 1,
	TFRC_SSTATE_NO_FBACK,
	TFRC_SSTATE_FBACK,
पूर्ण;

/**
 * काष्ठा ccid3_hc_tx_sock - CCID3 sender half-connection socket
 * @tx_x:		  Current sending rate in 64 * bytes per second
 * @tx_x_recv:		  Receive rate in 64 * bytes per second
 * @tx_x_calc:		  Calculated rate in bytes per second
 * @tx_rtt:		  Estimate of current round trip समय in usecs
 * @tx_p:		  Current loss event rate (0-1) scaled by 1000000
 * @tx_s:		  Packet size in bytes
 * @tx_t_rto:		  Nofeedback Timer setting in usecs
 * @tx_t_ipi:		  Interpacket (send) पूर्णांकerval (RFC 3448, 4.6) in usecs
 * @tx_state:		  Sender state, one of %ccid3_hc_tx_states
 * @tx_last_win_count:	  Last winकरोw counter sent
 * @tx_t_last_win_count:  Timestamp of earliest packet
 *			  with last_win_count value sent
 * @tx_no_feedback_समयr: Handle to no feedback समयr
 * @tx_t_ld:		  Time last द्विगुनd during slow start
 * @tx_t_nom:		  Nominal send समय of next packet
 * @tx_hist:		  Packet history
 */
काष्ठा ccid3_hc_tx_sock अणु
	u64				tx_x;
	u64				tx_x_recv;
	u32				tx_x_calc;
	u32				tx_rtt;
	u32				tx_p;
	u32				tx_t_rto;
	u32				tx_t_ipi;
	u16				tx_s;
	क्रमागत ccid3_hc_tx_states		tx_state:8;
	u8				tx_last_win_count;
	kसमय_प्रकार				tx_t_last_win_count;
	काष्ठा समयr_list		tx_no_feedback_समयr;
	काष्ठा sock			*sk;
	kसमय_प्रकार				tx_t_ld;
	kसमय_प्रकार				tx_t_nom;
	काष्ठा tfrc_tx_hist_entry	*tx_hist;
पूर्ण;

अटल अंतरभूत काष्ठा ccid3_hc_tx_sock *ccid3_hc_tx_sk(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_tx_sock *hctx = ccid_priv(dccp_sk(sk)->dccps_hc_tx_ccid);
	BUG_ON(hctx == शून्य);
	वापस hctx;
पूर्ण

/* TFRC receiver states */
क्रमागत ccid3_hc_rx_states अणु
	TFRC_RSTATE_NO_DATA = 1,
	TFRC_RSTATE_DATA,
पूर्ण;

/**
 * काष्ठा ccid3_hc_rx_sock - CCID3 receiver half-connection socket
 * @rx_last_counter:	     Tracks winकरोw counter (RFC 4342, 8.1)
 * @rx_state:		     Receiver state, one of %ccid3_hc_rx_states
 * @rx_bytes_recv:	     Total sum of DCCP payload bytes
 * @rx_x_recv:		     Receiver estimate of send rate (RFC 3448, sec. 4.3)
 * @rx_rtt:		     Receiver estimate of RTT
 * @rx_tstamp_last_feedback: Time at which last feedback was sent
 * @rx_hist:		     Packet history (loss detection + RTT sampling)
 * @rx_li_hist:		     Loss Interval database
 * @rx_s:		     Received packet size in bytes
 * @rx_pinv:		     Inverse of Loss Event Rate (RFC 4342, sec. 8.5)
 */
काष्ठा ccid3_hc_rx_sock अणु
	u8				rx_last_counter:4;
	क्रमागत ccid3_hc_rx_states		rx_state:8;
	u32				rx_bytes_recv;
	u32				rx_x_recv;
	u32				rx_rtt;
	kसमय_प्रकार				rx_tstamp_last_feedback;
	काष्ठा tfrc_rx_hist		rx_hist;
	काष्ठा tfrc_loss_hist		rx_li_hist;
	u16				rx_s;
#घोषणा rx_pinv				rx_li_hist.i_mean
पूर्ण;

अटल अंतरभूत काष्ठा ccid3_hc_rx_sock *ccid3_hc_rx_sk(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा ccid3_hc_rx_sock *hcrx = ccid_priv(dccp_sk(sk)->dccps_hc_rx_ccid);
	BUG_ON(hcrx == शून्य);
	वापस hcrx;
पूर्ण

#पूर्ण_अगर /* _DCCP_CCID3_H_ */
