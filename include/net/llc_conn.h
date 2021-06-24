<शैली गुरु>
#अगर_अघोषित LLC_CONN_H
#घोषणा LLC_CONN_H
/*
 * Copyright (c) 1997 by Procom Technology, Inc.
 * 		 2001, 2002 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#समावेश <linux/समयr.h>
#समावेश <net/llc_अगर.h>
#समावेश <net/sock.h>
#समावेश <linux/llc.h>

#घोषणा LLC_EVENT                1
#घोषणा LLC_PACKET               2

#घोषणा LLC2_P_TIME               2
#घोषणा LLC2_ACK_TIME             1
#घोषणा LLC2_REJ_TIME             3
#घोषणा LLC2_BUSY_TIME            3

काष्ठा llc_समयr अणु
	काष्ठा समयr_list समयr;
	अचिन्हित दीर्घ	  expire;	/* समयr expire समय */
पूर्ण;

काष्ठा llc_sock अणु
	/* काष्ठा sock must be the first member of llc_sock */
	काष्ठा sock	    sk;
	काष्ठा sockaddr_llc addr;		/* address sock is bound to */
	u8		    state;		/* state of connection */
	काष्ठा llc_sap	    *sap;		/* poपूर्णांकer to parent SAP */
	काष्ठा llc_addr	    laddr;		/* lsap/mac pair */
	काष्ठा llc_addr	    daddr;		/* dsap/mac pair */
	काष्ठा net_device   *dev;		/* device to send to remote */
	u32		    copied_seq;		/* head of yet unपढ़ो data */
	u8		    retry_count;	/* number of retries */
	u8		    ack_must_be_send;
	u8		    first_pdu_Ns;
	u8		    npta;
	काष्ठा llc_समयr    ack_समयr;
	काष्ठा llc_समयr    pf_cycle_समयr;
	काष्ठा llc_समयr    rej_sent_समयr;
	काष्ठा llc_समयr    busy_state_समयr;	/* ind busy clr at remote LLC */
	u8		    vS;			/* seq# next in-seq I-PDU tx'd*/
	u8		    vR;			/* seq# next in-seq I-PDU rx'd*/
	u32		    n2;			/* max nbr re-tx's क्रम समयout*/
	u32		    n1;			/* max nbr octets in I PDU */
	u8		    k;			/* tx winकरोw size; max = 127 */
	u8		    rw;			/* rx winकरोw size; max = 127 */
	u8		    p_flag;		/* state flags */
	u8		    f_flag;
	u8		    s_flag;
	u8		    data_flag;
	u8		    remote_busy_flag;
	u8		    cause_flag;
	काष्ठा sk_buff_head pdu_unack_q;	/* PUDs sent/रुकोing ack */
	u16		    link;		/* network layer link number */
	u8		    X;			/* a temporary variable */
	u8		    ack_pf;		/* this flag indicates what is
						   the P-bit of acknowledge */
	u8		    failed_data_req; /* recognize that alपढ़ोy exist a
						failed llc_data_req_handler
						(tx_buffer_full or unacceptable
						state */
	u8		    dec_step;
	u8		    inc_cntr;
	u8		    dec_cntr;
	u8		    connect_step;
	u8		    last_nr;	   /* NR of last pdu received */
	u32		    rx_pdu_hdr;	   /* used क्रम saving header of last pdu
					      received and caused sending FRMR.
					      Used क्रम resending FRMR */
	u32		    cmsg_flags;
	काष्ठा hlist_node   dev_hash_node;
पूर्ण;

अटल अंतरभूत काष्ठा llc_sock *llc_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा llc_sock *)sk;
पूर्ण

अटल __अंतरभूत__ व्योम llc_set_backlog_type(काष्ठा sk_buff *skb, अक्षर type)
अणु
	skb->cb[माप(skb->cb) - 1] = type;
पूर्ण

अटल __अंतरभूत__ अक्षर llc_backlog_type(काष्ठा sk_buff *skb)
अणु
	वापस skb->cb[माप(skb->cb) - 1];
पूर्ण

काष्ठा sock *llc_sk_alloc(काष्ठा net *net, पूर्णांक family, gfp_t priority,
			  काष्ठा proto *prot, पूर्णांक kern);
व्योम llc_sk_stop_all_समयrs(काष्ठा sock *sk, bool sync);
व्योम llc_sk_मुक्त(काष्ठा sock *sk);

व्योम llc_sk_reset(काष्ठा sock *sk);

/* Access to a connection */
पूर्णांक llc_conn_state_process(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम llc_conn_send_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम llc_conn_rtn_pdu(काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम llc_conn_resend_i_pdu_as_cmd(काष्ठा sock *sk, u8 nr, u8 first_p_bit);
व्योम llc_conn_resend_i_pdu_as_rsp(काष्ठा sock *sk, u8 nr, u8 first_f_bit);
पूर्णांक llc_conn_हटाओ_acked_pdus(काष्ठा sock *conn, u8 nr, u16 *how_many_unacked);
काष्ठा sock *llc_lookup_established(काष्ठा llc_sap *sap, काष्ठा llc_addr *daddr,
				    काष्ठा llc_addr *laddr);
व्योम llc_sap_add_socket(काष्ठा llc_sap *sap, काष्ठा sock *sk);
व्योम llc_sap_हटाओ_socket(काष्ठा llc_sap *sap, काष्ठा sock *sk);

u8 llc_data_accept_state(u8 state);
व्योम llc_build_offset_table(व्योम);
#पूर्ण_अगर /* LLC_CONN_H */
