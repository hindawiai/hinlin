<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2007
 * Authors:	Peter Tiedemann (ptiedem@de.ibm.com)
 *
 * 	MPC additions:
 *		Belinda Thompson (belindat@us.ibm.com)
 *		Andy Richter (richtera@us.ibm.com)
 */

#अगर_अघोषित _CTC_MPC_H_
#घोषणा _CTC_MPC_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश "fsm.h"

/*
 * MPC बाह्यal पूर्णांकerface
 * Note that ctc_mpc_xyz are called with a lock on ................
 */

/*  port_number is the mpc device 0, 1, 2 etc mpc2 is port_number 2 */

/*  passive खोलो  Just रुको क्रम XID2 exchange */
बाह्य पूर्णांक ctc_mpc_alloc_channel(पूर्णांक port,
		व्योम (*callback)(पूर्णांक port_num, पूर्णांक max_ग_लिखो_size));
/* active खोलो  Alloc then send XID2 */
बाह्य व्योम ctc_mpc_establish_connectivity(पूर्णांक port,
		व्योम (*callback)(पूर्णांक port_num, पूर्णांक rc, पूर्णांक max_ग_लिखो_size));

बाह्य व्योम ctc_mpc_dealloc_ch(पूर्णांक port);
बाह्य व्योम ctc_mpc_flow_control(पूर्णांक port, पूर्णांक flowc);

/*
 * other MPC Group prototypes and काष्ठाures
 */

#घोषणा ETH_P_SNA_DIX	0x80D5

/*
 * Declaration of an XID2
 *
 */
#घोषणा ALLZEROS 0x0000000000000000

#घोषणा XID_FM2		0x20
#घोषणा XID2_0		0x00
#घोषणा XID2_7		0x07
#घोषणा XID2_WRITE_SIDE 0x04
#घोषणा XID2_READ_SIDE	0x05

काष्ठा xid2 अणु
	__u8	xid2_type_id;
	__u8	xid2_len;
	__u32	xid2_adj_id;
	__u8	xid2_rlen;
	__u8	xid2_resv1;
	__u8	xid2_flag1;
	__u8	xid2_fmtt;
	__u8	xid2_flag4;
	__u16	xid2_resv2;
	__u8	xid2_tgnum;
	__u32	xid2_sender_id;
	__u8	xid2_flag2;
	__u8	xid2_option;
	अक्षर  xid2_resv3[8];
	__u16	xid2_resv4;
	__u8	xid2_dlc_type;
	__u16	xid2_resv5;
	__u8	xid2_mpc_flag;
	__u8	xid2_resv6;
	__u16	xid2_buf_len;
	अक्षर xid2_buffer[255 - (13 * माप(__u8) +
				2 * माप(__u32) +
				4 * माप(__u16) +
				8 * माप(अक्षर))];
पूर्ण __attribute__ ((packed));

#घोषणा XID2_LENGTH  (माप(काष्ठा xid2))

काष्ठा th_header अणु
	__u8	th_seg;
	__u8	th_ch_flag;
#घोषणा TH_HAS_PDU	0xf0
#घोषणा TH_IS_XID	0x01
#घोषणा TH_SWEEP_REQ	0xfe
#घोषणा TH_SWEEP_RESP	0xff
	__u8	th_blk_flag;
#घोषणा TH_DATA_IS_XID	0x80
#घोषणा TH_RETRY	0x40
#घोषणा TH_DISCONTACT	0xc0
#घोषणा TH_SEG_BLK	0x20
#घोषणा TH_LAST_SEG	0x10
#घोषणा TH_PDU_PART	0x08
	__u8	th_is_xid;	/* is 0x01 अगर this is XID  */
	__u32	th_seq_num;
पूर्ण __attribute__ ((packed));

काष्ठा th_adकरोn अणु
	__u32	th_last_seq;
	__u32	th_resvd;
पूर्ण __attribute__ ((packed));

काष्ठा th_sweep अणु
	काष्ठा th_header th;
	काष्ठा th_adकरोn sw;
पूर्ण __attribute__ ((packed));

#घोषणा TH_HEADER_LENGTH (माप(काष्ठा th_header))
#घोषणा TH_SWEEP_LENGTH (माप(काष्ठा th_sweep))

#घोषणा PDU_LAST	0x80
#घोषणा PDU_CNTL	0x40
#घोषणा PDU_FIRST	0x20

काष्ठा pdu अणु
	__u32	pdu_offset;
	__u8	pdu_flag;
	__u8	pdu_proto;   /*  0x01 is APPN SNA  */
	__u16	pdu_seq;
पूर्ण __attribute__ ((packed));

#घोषणा PDU_HEADER_LENGTH  (माप(काष्ठा pdu))

काष्ठा qllc अणु
	__u8	qllc_address;
#घोषणा QLLC_REQ	0xFF
#घोषणा QLLC_RESP	0x00
	__u8	qllc_commands;
#घोषणा QLLC_DISCONNECT 0x53
#घोषणा QLLC_UNSEQACK	0x73
#घोषणा QLLC_SETMODE	0x93
#घोषणा QLLC_EXCHID	0xBF
पूर्ण __attribute__ ((packed));


/*
 * Definition of one MPC group
 */

#घोषणा MAX_MPCGCHAN		10
#घोषणा MPC_XID_TIMEOUT_VALUE	10000
#घोषणा MPC_CHANNEL_ADD		0
#घोषणा MPC_CHANNEL_REMOVE	1
#घोषणा MPC_CHANNEL_ATTN	2
#घोषणा XSIDE	1
#घोषणा YSIDE	0

काष्ठा mpcg_info अणु
	काष्ठा sk_buff	*skb;
	काष्ठा channel	*ch;
	काष्ठा xid2	*xid;
	काष्ठा th_sweep	*sweep;
	काष्ठा th_header *th;
पूर्ण;

काष्ठा mpc_group अणु
	काष्ठा tasklet_काष्ठा mpc_tasklet;
	काष्ठा tasklet_काष्ठा mpc_tasklet2;
	पूर्णांक	changed_side;
	पूर्णांक	saved_state;
	पूर्णांक	channels_terminating;
	पूर्णांक	out_of_sequence;
	पूर्णांक	flow_off_called;
	पूर्णांक	port_num;
	पूर्णांक	port_persist;
	पूर्णांक	alloc_called;
	__u32	xid2_adj_id;
	__u8	xid2_tgnum;
	__u32	xid2_sender_id;
	पूर्णांक	num_channel_paths;
	पूर्णांक	active_channels[2];
	__u16	group_max_buflen;
	पूर्णांक	outstanding_xid2;
	पूर्णांक	outstanding_xid7;
	पूर्णांक	outstanding_xid7_p2;
	पूर्णांक	sweep_req_pend_num;
	पूर्णांक	sweep_rsp_pend_num;
	काष्ठा sk_buff	*xid_skb;
	अक्षर		*xid_skb_data;
	काष्ठा th_header *xid_th;
	काष्ठा xid2	*xid;
	अक्षर		*xid_id;
	काष्ठा th_header *rcvd_xid_th;
	काष्ठा sk_buff	*rcvd_xid_skb;
	अक्षर		*rcvd_xid_data;
	__u8		in_sweep;
	__u8		roll;
	काष्ठा xid2	*saved_xid2;
	व्योम 		(*allochanfunc)(पूर्णांक, पूर्णांक);
	पूर्णांक		allocchan_callback_retries;
	व्योम 		(*estconnfunc)(पूर्णांक, पूर्णांक, पूर्णांक);
	पूर्णांक		estconn_callback_retries;
	पूर्णांक		estconn_called;
	पूर्णांक		xidnogood;
	पूर्णांक		send_qllc_disc;
	fsm_समयr	समयr;
	fsm_instance	*fsm; /* group xid fsm */
पूर्ण;

#अगर_घोषित DEBUGDATA
व्योम ctcmpc_dumpit(अक्षर *buf, पूर्णांक len);
#अन्यथा
अटल अंतरभूत व्योम ctcmpc_dumpit(अक्षर *buf, पूर्णांक len)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित DEBUGDATA
/*
 * Dump header and first 16 bytes of an sk_buff क्रम debugging purposes.
 *
 * skb	 The काष्ठा sk_buff to dump.
 * offset Offset relative to skb-data, where to start the dump.
 */
व्योम ctcmpc_dump_skb(काष्ठा sk_buff *skb, पूर्णांक offset);
#अन्यथा
अटल अंतरभूत व्योम ctcmpc_dump_skb(काष्ठा sk_buff *skb, पूर्णांक offset)
अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ctcmpc_dump32(अक्षर *buf, पूर्णांक len)
अणु
	अगर (len < 32)
		ctcmpc_dumpit(buf, len);
	अन्यथा
		ctcmpc_dumpit(buf, 32);
पूर्ण

व्योम ctcm_ccw_check_rc(काष्ठा channel *, पूर्णांक, अक्षर *);
व्योम mpc_group_पढ़ोy(अचिन्हित दीर्घ adev);
व्योम mpc_channel_action(काष्ठा channel *ch, पूर्णांक direction, पूर्णांक action);
व्योम mpc_action_send_discontact(अचिन्हित दीर्घ thischan);
व्योम mpc_action_discontact(fsm_instance *fi, पूर्णांक event, व्योम *arg);
व्योम ctcmpc_bh(अचिन्हित दीर्घ thischan);
#पूर्ण_अगर
/* --- This is the END my मित्र --- */
