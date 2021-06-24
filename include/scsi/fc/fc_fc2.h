<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_FC2_H_
#घोषणा _FC_FC2_H_

/*
 * Fibre Channel Exchanges and Sequences.
 */
#अगर_अघोषित PACKED
#घोषणा PACKED  __attribute__ ((__packed__))
#पूर्ण_अगर /* PACKED */


/*
 * Sequence Status Block.
 * This क्रमmat is set by the FC-FS standard and is sent over the wire.
 * Note that the fields aren't all naturally aligned.
 */
काष्ठा fc_ssb अणु
	__u8	ssb_seq_id;		/* sequence ID */
	__u8	_ssb_resvd;
	__be16	ssb_low_seq_cnt;	/* lowest SEQ_CNT */

	__be16	ssb_high_seq_cnt;	/* highest SEQ_CNT */
	__be16	ssb_s_stat;		/* sequence status flags */

	__be16	ssb_err_seq_cnt;	/* error SEQ_CNT */
	__u8	ssb_fh_cs_ctl;		/* frame header CS_CTL */
	__be16	ssb_fh_ox_id;		/* frame header OX_ID */
	__be16	ssb_rx_id;		/* responder's exchange ID */
	__u8	_ssb_resvd2[2];
पूर्ण PACKED;

/*
 * The SSB should be 17 bytes.  Since it's layout is somewhat strange,
 * we define the size here so that code can ASSERT that the size comes out
 * correct.
 */
#घोषणा FC_SSB_SIZE         17          /* length of fc_ssb क्रम निश्चित */

/*
 * ssb_s_stat - flags from FC-FS-2 T11/1619-D Rev 0.90.
 */
#घोषणा SSB_ST_RESP         (1 << 15)   /* sequence responder */
#घोषणा SSB_ST_ACTIVE       (1 << 14)   /* sequence is active */
#घोषणा SSB_ST_ABNORMAL     (1 << 12)   /* abnormal ending condition */

#घोषणा SSB_ST_REQ_MASK     (3 << 10)   /* ACK, पात sequence condition */
#घोषणा SSB_ST_REQ_CONT     (0 << 10)
#घोषणा SSB_ST_REQ_ABORT    (1 << 10)
#घोषणा SSB_ST_REQ_STOP     (2 << 10)
#घोषणा SSB_ST_REQ_RETRANS  (3 << 10)

#घोषणा SSB_ST_ABTS         (1 << 9)    /* ABTS protocol completed */
#घोषणा SSB_ST_RETRANS      (1 << 8)    /* retransmission completed */
#घोषणा SSB_ST_TIMEOUT      (1 << 7)    /* sequence समयd out by recipient */
#घोषणा SSB_ST_P_RJT        (1 << 6)    /* P_RJT transmitted */

#घोषणा SSB_ST_CLASS_BIT    4           /* class of service field LSB */
#घोषणा SSB_ST_CLASS_MASK   3           /* class of service mask */
#घोषणा SSB_ST_ACK          (1 << 3)    /* ACK (खातापूर्णt or खातापूर्णdt) transmitted */

/*
 * Exchange Status Block.
 * This क्रमmat is set by the FC-FS standard and is sent over the wire.
 * Note that the fields aren't all naturally aligned.
 */
काष्ठा fc_esb अणु
	__u8	esb_cs_ctl;		/* CS_CTL क्रम frame header */
	__be16	esb_ox_id;		/* originator exchange ID */
	__be16	esb_rx_id;		/* responder exchange ID */
	__be32	esb_orig_fid;		/* fabric ID of originator */
	__be32	esb_resp_fid;		/* fabric ID of responder */
	__be32	esb_e_stat;		/* status */
	__u8	_esb_resvd[4];
	__u8	esb_service_params[112]; /* TBD */
	__u8	esb_seq_status[8];	/* sequence statuses, 8 bytes each */
पूर्ण __attribute__((packed));

/*
 * Define expected size क्रम ASSERTs.
 * See comments on FC_SSB_SIZE.
 */
#घोषणा FC_ESB_SIZE         (1 + 5*4 + 112 + 8)     /* expected size */

/*
 * esb_e_stat - flags from FC-FS-2 T11/1619-D Rev 0.90.
 */
#घोषणा ESB_ST_RESP         (1 << 31)   /* responder to exchange */
#घोषणा ESB_ST_SEQ_INIT     (1 << 30)   /* port holds sequence initiative */
#घोषणा ESB_ST_COMPLETE     (1 << 29)   /* exchange is complete */
#घोषणा ESB_ST_ABNORMAL     (1 << 28)   /* abnormal ending condition */
#घोषणा ESB_ST_REC_QUAL     (1 << 26)   /* recovery qualअगरier active */

#घोषणा ESB_ST_ERRP_BIT     24          /* LSB क्रम error policy */
#घोषणा ESB_ST_ERRP_MASK    (3 << 24)   /* mask क्रम error policy */
#घोषणा ESB_ST_ERRP_MULT    (0 << 24)   /* पात, discard multiple sequences */
#घोषणा ESB_ST_ERRP_SING    (1 << 24)   /* पात, discard single sequence */
#घोषणा ESB_ST_ERRP_INF     (2 << 24)   /* process with infinite buffers */
#घोषणा ESB_ST_ERRP_IMM     (3 << 24)   /* discard mult. with immed. retran. */

#घोषणा ESB_ST_OX_ID_INVL   (1 << 23)   /* originator XID invalid */
#घोषणा ESB_ST_RX_ID_INVL   (1 << 22)   /* responder XID invalid */
#घोषणा ESB_ST_PRI_INUSE    (1 << 21)   /* priority / preemption in use */

#पूर्ण_अगर /* _FC_FC2_H_ */
