<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _NET_DN_NSP_H
#घोषणा _NET_DN_NSP_H
/******************************************************************************
    (c) 1995-1998 E.M. Serrat		emserrat@geocities.com
    
*******************************************************************************/
/* dn_nsp.c functions prototyping */

व्योम dn_nsp_send_data_ack(काष्ठा sock *sk);
व्योम dn_nsp_send_oth_ack(काष्ठा sock *sk);
व्योम dn_send_conn_ack(काष्ठा sock *sk);
व्योम dn_send_conn_conf(काष्ठा sock *sk, gfp_t gfp);
व्योम dn_nsp_send_disc(काष्ठा sock *sk, अचिन्हित अक्षर type,
		      अचिन्हित लघु reason, gfp_t gfp);
व्योम dn_nsp_वापस_disc(काष्ठा sk_buff *skb, अचिन्हित अक्षर type,
			अचिन्हित लघु reason);
व्योम dn_nsp_send_link(काष्ठा sock *sk, अचिन्हित अक्षर lsflags, अक्षर fcval);
व्योम dn_nsp_send_conninit(काष्ठा sock *sk, अचिन्हित अक्षर flags);

व्योम dn_nsp_output(काष्ठा sock *sk);
पूर्णांक dn_nsp_check_xmit_queue(काष्ठा sock *sk, काष्ठा sk_buff *skb,
			    काष्ठा sk_buff_head *q, अचिन्हित लघु acknum);
व्योम dn_nsp_queue_xmit(काष्ठा sock *sk, काष्ठा sk_buff *skb, gfp_t gfp,
		       पूर्णांक oob);
अचिन्हित दीर्घ dn_nsp_persist(काष्ठा sock *sk);
पूर्णांक dn_nsp_xmit_समयout(काष्ठा sock *sk);

पूर्णांक dn_nsp_rx(काष्ठा sk_buff *);
पूर्णांक dn_nsp_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

काष्ठा sk_buff *dn_alloc_skb(काष्ठा sock *sk, पूर्णांक size, gfp_t pri);
काष्ठा sk_buff *dn_alloc_send_skb(काष्ठा sock *sk, माप_प्रकार *size, पूर्णांक noblock,
				  दीर्घ समयo, पूर्णांक *err);

#घोषणा NSP_REASON_OK 0		/* No error */
#घोषणा NSP_REASON_NR 1		/* No resources */
#घोषणा NSP_REASON_UN 2		/* Unrecognised node name */
#घोषणा NSP_REASON_SD 3		/* Node shutting करोwn */
#घोषणा NSP_REASON_ID 4		/* Invalid destination end user */
#घोषणा NSP_REASON_ER 5		/* End user lacks resources */
#घोषणा NSP_REASON_OB 6		/* Object too busy */
#घोषणा NSP_REASON_US 7		/* Unspecअगरied error */
#घोषणा NSP_REASON_TP 8		/* Third-Party पात */
#घोषणा NSP_REASON_EA 9		/* End user has पातed the link */
#घोषणा NSP_REASON_IF 10	/* Invalid node name क्रमmat */
#घोषणा NSP_REASON_LS 11	/* Local node shutकरोwn */
#घोषणा NSP_REASON_LL 32	/* Node lacks logical-link resources */
#घोषणा NSP_REASON_LE 33	/* End user lacks logical-link resources */
#घोषणा NSP_REASON_UR 34	/* Unacceptable RQSTRID or PASSWORD field */
#घोषणा NSP_REASON_UA 36	/* Unacceptable ACCOUNT field */
#घोषणा NSP_REASON_TM 38	/* End user समयd out logical link */
#घोषणा NSP_REASON_NU 39	/* Node unreachable */
#घोषणा NSP_REASON_NL 41	/* No-link message */
#घोषणा NSP_REASON_DC 42	/* Disconnect confirm */
#घोषणा NSP_REASON_IO 43	/* Image data field overflow */

#घोषणा NSP_DISCINIT 0x38
#घोषणा NSP_DISCCONF 0x48

/*------------------------- NSP - messages ------------------------------*/
/* Data Messages */
/*---------------*/

/* Data Messages    (data segment/पूर्णांकerrupt/link service)               */

काष्ठा nsp_data_seg_msg अणु
	__u8   msgflg;
	__le16 dstaddr;
	__le16 srcaddr;
पूर्ण __packed;

काष्ठा nsp_data_opt_msg अणु
	__le16 acknum;
	__le16 segnum;
	__le16 lsflgs;
पूर्ण __packed;

काष्ठा nsp_data_opt_msg1 अणु
	__le16 acknum;
	__le16 segnum;
पूर्ण __packed;


/* Acknowledgment Message (data/other data)                             */
काष्ठा nsp_data_ack_msg अणु
	__u8   msgflg;
	__le16 dstaddr;
	__le16 srcaddr;
	__le16 acknum;
पूर्ण __packed;

/* Connect Acknowledgment Message */
काष्ठा  nsp_conn_ack_msg अणु
	__u8 msgflg;
	__le16 dstaddr;
पूर्ण __packed;


/* Connect Initiate/Retransmit Initiate/Connect Confirm */
काष्ठा  nsp_conn_init_msg अणु
	__u8   msgflg;
#घोषणा NSP_CI      0x18            /* Connect Initiate     */
#घोषणा NSP_RCI     0x68            /* Retrans. Conn Init   */
	__le16 dstaddr;
	__le16 srcaddr;
	__u8   services;
#घोषणा NSP_FC_NONE   0x00            /* Flow Control None    */
#घोषणा NSP_FC_SRC    0x04            /* Seg Req. Count       */
#घोषणा NSP_FC_SCMC   0x08            /* Sess. Control Mess   */
#घोषणा NSP_FC_MASK   0x0c            /* FC type mask         */
	__u8   info;
	__le16 segsize;
पूर्ण __packed;

/* Disconnect Initiate/Disconnect Confirm */
काष्ठा  nsp_disconn_init_msg अणु
	__u8   msgflg;
	__le16 dstaddr;
	__le16 srcaddr;
	__le16 reason;
पूर्ण __packed;



काष्ठा  srcobj_fmt अणु
	__u8   क्रमmat;
	__u8   task;
	__le16 grpcode;
	__le16 usrcode;
	__u8   dlen;
पूर्ण __packed;

/*
 * A collection of functions क्रम manipulating the sequence
 * numbers used in NSP. Similar in operation to the functions
 * of the same name in TCP.
 */
अटल __अंतरभूत__ पूर्णांक dn_beक्रमe(__u16 seq1, __u16 seq2)
अणु
        seq1 &= 0x0fff;
        seq2 &= 0x0fff;

        वापस (पूर्णांक)((seq1 - seq2) & 0x0fff) > 2048;
पूर्ण


अटल __अंतरभूत__ पूर्णांक dn_after(__u16 seq1, __u16 seq2)
अणु
        seq1 &= 0x0fff;
        seq2 &= 0x0fff;

        वापस (पूर्णांक)((seq2 - seq1) & 0x0fff) > 2048;
पूर्ण

अटल __अंतरभूत__ पूर्णांक dn_equal(__u16 seq1, __u16 seq2)
अणु
        वापस ((seq1 ^ seq2) & 0x0fff) == 0;
पूर्ण

अटल __अंतरभूत__ पूर्णांक dn_beक्रमe_or_equal(__u16 seq1, __u16 seq2)
अणु
	वापस (dn_beक्रमe(seq1, seq2) || dn_equal(seq1, seq2));
पूर्ण

अटल __अंतरभूत__ व्योम seq_add(__u16 *seq, __u16 off)
अणु
        (*seq) += off;
        (*seq) &= 0x0fff;
पूर्ण

अटल __अंतरभूत__ पूर्णांक seq_next(__u16 seq1, __u16 seq2)
अणु
	वापस dn_equal(seq1 + 1, seq2);
पूर्ण

/*
 * Can we delay the ack ?
 */
अटल __अंतरभूत__ पूर्णांक sendack(__u16 seq)
अणु
        वापस (पूर्णांक)((seq & 0x1000) ? 0 : 1);
पूर्ण

/*
 * Is socket congested ?
 */
अटल __अंतरभूत__ पूर्णांक dn_congested(काष्ठा sock *sk)
अणु
        वापस atomic_पढ़ो(&sk->sk_rmem_alloc) > (sk->sk_rcvbuf >> 1);
पूर्ण

#घोषणा DN_MAX_NSP_DATA_HEADER (11)

#पूर्ण_अगर /* _NET_DN_NSP_H */
