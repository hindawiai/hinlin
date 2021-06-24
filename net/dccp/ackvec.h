<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _ACKVEC_H
#घोषणा _ACKVEC_H
/*
 *  net/dccp/ackvec.h
 *
 *  An implementation of Ack Vectors क्रम the DCCP protocol
 *  Copyright (c) 2007 University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@mandriva.com>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/types.h>

/*
 * Ack Vector buffer space is अटल, in multiples of %DCCP_SINGLE_OPT_MAXLEN,
 * the maximum size of a single Ack Vector. Setting %DCCPAV_NUM_ACKVECS to 1
 * will be sufficient क्रम most हालs of low Ack Ratios, using a value of 2 gives
 * more headroom अगर Ack Ratio is higher or when the sender acknowledges slowly.
 * The maximum value is bounded by the u16 types क्रम indices and functions.
 */
#घोषणा DCCPAV_NUM_ACKVECS	2
#घोषणा DCCPAV_MAX_ACKVEC_LEN	(DCCP_SINGLE_OPT_MAXLEN * DCCPAV_NUM_ACKVECS)

/* Estimated minimum average Ack Vector length - used क्रम updating MPS */
#घोषणा DCCPAV_MIN_OPTLEN	16

/* Threshold क्रम coping with large bursts of losses */
#घोषणा DCCPAV_BURST_THRESH	(DCCPAV_MAX_ACKVEC_LEN / 8)

क्रमागत dccp_ackvec_states अणु
	DCCPAV_RECEIVED =	0x00,
	DCCPAV_ECN_MARKED =	0x40,
	DCCPAV_RESERVED =	0x80,
	DCCPAV_NOT_RECEIVED =	0xC0
पूर्ण;
#घोषणा DCCPAV_MAX_RUNLEN	0x3F

अटल अंतरभूत u8 dccp_ackvec_runlen(स्थिर u8 *cell)
अणु
	वापस *cell & DCCPAV_MAX_RUNLEN;
पूर्ण

अटल अंतरभूत u8 dccp_ackvec_state(स्थिर u8 *cell)
अणु
	वापस *cell & ~DCCPAV_MAX_RUNLEN;
पूर्ण

/**
 * काष्ठा dccp_ackvec - Ack Vector मुख्य data काष्ठाure
 *
 * This implements a fixed-size circular buffer within an array and is largely
 * based on Appendix A of RFC 4340.
 *
 * @av_buf:	   circular buffer storage area
 * @av_buf_head:   head index; begin of live portion in @av_buf
 * @av_buf_tail:   tail index; first index _after_ the live portion in @av_buf
 * @av_buf_ackno:  highest seqno of acknowledgeable packet recorded in @av_buf
 * @av_tail_ackno: lowest  seqno of acknowledgeable packet recorded in @av_buf
 * @av_buf_nonce:  ECN nonce sums, each covering subsequent segments of up to
 *		   %DCCP_SINGLE_OPT_MAXLEN cells in the live portion of @av_buf
 * @av_overflow:   अगर 1 then buf_head == buf_tail indicates buffer wraparound
 * @av_records:	   list of %dccp_ackvec_record (Ack Vectors sent previously)
 */
काष्ठा dccp_ackvec अणु
	u8			av_buf[DCCPAV_MAX_ACKVEC_LEN];
	u16			av_buf_head;
	u16			av_buf_tail;
	u64			av_buf_ackno:48;
	u64			av_tail_ackno:48;
	bool			av_buf_nonce[DCCPAV_NUM_ACKVECS];
	u8			av_overflow:1;
	काष्ठा list_head	av_records;
पूर्ण;

/**
 * काष्ठा dccp_ackvec_record - Records inक्रमmation about sent Ack Vectors
 *
 * These list entries define the additional inक्रमmation which the HC-Receiver
 * keeps about recently-sent Ack Vectors; again refer to RFC 4340, Appendix A.
 *
 * @avr_node:	    the list node in @av_records
 * @avr_ack_seqno:  sequence number of the packet the Ack Vector was sent on
 * @avr_ack_ackno:  the Ack number that this record/Ack Vector refers to
 * @avr_ack_ptr:    poपूर्णांकer पूर्णांकo @av_buf where this record starts
 * @avr_ack_runlen: run length of @avr_ack_ptr at the समय of sending
 * @avr_ack_nonce:  the sum of @av_buf_nonce's at the समय this record was sent
 *
 * The list as a whole is sorted in descending order by @avr_ack_seqno.
 */
काष्ठा dccp_ackvec_record अणु
	काष्ठा list_head avr_node;
	u64		 avr_ack_seqno:48;
	u64		 avr_ack_ackno:48;
	u16		 avr_ack_ptr;
	u8		 avr_ack_runlen;
	u8		 avr_ack_nonce:1;
पूर्ण;

पूर्णांक dccp_ackvec_init(व्योम);
व्योम dccp_ackvec_निकास(व्योम);

काष्ठा dccp_ackvec *dccp_ackvec_alloc(स्थिर gfp_t priority);
व्योम dccp_ackvec_मुक्त(काष्ठा dccp_ackvec *av);

व्योम dccp_ackvec_input(काष्ठा dccp_ackvec *av, काष्ठा sk_buff *skb);
पूर्णांक dccp_ackvec_update_records(काष्ठा dccp_ackvec *av, u64 seq, u8 sum);
व्योम dccp_ackvec_clear_state(काष्ठा dccp_ackvec *av, स्थिर u64 ackno);
u16 dccp_ackvec_buflen(स्थिर काष्ठा dccp_ackvec *av);

अटल अंतरभूत bool dccp_ackvec_is_empty(स्थिर काष्ठा dccp_ackvec *av)
अणु
	वापस av->av_overflow == 0 && av->av_buf_head == av->av_buf_tail;
पूर्ण

/**
 * काष्ठा dccp_ackvec_parsed  -  Record offsets of Ack Vectors in skb
 * @vec:	start of vector (offset पूर्णांकo skb)
 * @len:	length of @vec
 * @nonce:	whether @vec had an ECN nonce of 0 or 1
 * @node:	FIFO - arranged in descending order of ack_ackno
 *
 * This काष्ठाure is used by CCIDs to access Ack Vectors in a received skb.
 */
काष्ठा dccp_ackvec_parsed अणु
	u8		 *vec,
			 len,
			 nonce:1;
	काष्ठा list_head node;
पूर्ण;

पूर्णांक dccp_ackvec_parsed_add(काष्ठा list_head *head, u8 *vec, u8 len, u8 nonce);
व्योम dccp_ackvec_parsed_cleanup(काष्ठा list_head *parsed_chunks);
#पूर्ण_अगर /* _ACKVEC_H */
