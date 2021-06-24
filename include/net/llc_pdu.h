<शैली गुरु>
#अगर_अघोषित LLC_PDU_H
#घोषणा LLC_PDU_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 * 		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/अगर_ether.h>

/* Lengths of frame क्रमmats */
#घोषणा LLC_PDU_LEN_I	4       /* header and 2 control bytes */
#घोषणा LLC_PDU_LEN_S	4
#घोषणा LLC_PDU_LEN_U	3       /* header and 1 control byte */
/* Known SAP addresses */
#घोषणा LLC_GLOBAL_SAP	0xFF
#घोषणा LLC_शून्य_SAP	0x00	/* not network-layer visible */
#घोषणा LLC_MGMT_INDIV	0x02	/* station LLC mgmt inभाग addr */
#घोषणा LLC_MGMT_GRP	0x03	/* station LLC mgmt group addr */
#घोषणा LLC_RDE_SAP	0xA6	/* route ... */

/* SAP field bit masks */
#घोषणा LLC_ISO_RESERVED_SAP	0x02
#घोषणा LLC_SAP_GROUP_DSAP	0x01
#घोषणा LLC_SAP_RESP_SSAP	0x01

/* Group/inभागidual DSAP indicator is DSAP field */
#घोषणा LLC_PDU_GROUP_DSAP_MASK    0x01
#घोषणा LLC_PDU_IS_GROUP_DSAP(pdu)      \
	((pdu->dsap & LLC_PDU_GROUP_DSAP_MASK) ? 0 : 1)
#घोषणा LLC_PDU_IS_INDIV_DSAP(pdu)      \
	(!(pdu->dsap & LLC_PDU_GROUP_DSAP_MASK) ? 0 : 1)

/* Command/response PDU indicator in SSAP field */
#घोषणा LLC_PDU_CMD_RSP_MASK	0x01
#घोषणा LLC_PDU_CMD		0
#घोषणा LLC_PDU_RSP		1
#घोषणा LLC_PDU_IS_CMD(pdu)    ((pdu->ssap & LLC_PDU_RSP) ? 0 : 1)
#घोषणा LLC_PDU_IS_RSP(pdu)    ((pdu->ssap & LLC_PDU_RSP) ? 1 : 0)

/* Get PDU type from 2 lowest-order bits of control field first byte */
#घोषणा LLC_PDU_TYPE_I_MASK    0x01	/* 16-bit control field */
#घोषणा LLC_PDU_TYPE_S_MASK    0x03
#घोषणा LLC_PDU_TYPE_U_MASK    0x03	/* 8-bit control field */
#घोषणा LLC_PDU_TYPE_MASK      0x03

#घोषणा LLC_PDU_TYPE_I	0	/* first bit */
#घोषणा LLC_PDU_TYPE_S	1	/* first two bits */
#घोषणा LLC_PDU_TYPE_U	3	/* first two bits */

#घोषणा LLC_PDU_TYPE_IS_I(pdu) \
	((!(pdu->ctrl_1 & LLC_PDU_TYPE_I_MASK)) ? 1 : 0)

#घोषणा LLC_PDU_TYPE_IS_U(pdu) \
	(((pdu->ctrl_1 & LLC_PDU_TYPE_U_MASK) == LLC_PDU_TYPE_U) ? 1 : 0)

#घोषणा LLC_PDU_TYPE_IS_S(pdu) \
	(((pdu->ctrl_1 & LLC_PDU_TYPE_S_MASK) == LLC_PDU_TYPE_S) ? 1 : 0)

/* U-क्रमmat PDU control field masks */
#घोषणा LLC_U_PF_BIT_MASK      0x10	/* P/F bit mask */
#घोषणा LLC_U_PF_IS_1(pdu)     ((pdu->ctrl_1 & LLC_U_PF_BIT_MASK) ? 1 : 0)
#घोषणा LLC_U_PF_IS_0(pdu)     ((!(pdu->ctrl_1 & LLC_U_PF_BIT_MASK)) ? 1 : 0)

#घोषणा LLC_U_PDU_CMD_MASK     0xEC	/* cmd/rsp mask */
#घोषणा LLC_U_PDU_CMD(pdu)     (pdu->ctrl_1 & LLC_U_PDU_CMD_MASK)
#घोषणा LLC_U_PDU_RSP(pdu)     (pdu->ctrl_1 & LLC_U_PDU_CMD_MASK)

#घोषणा LLC_1_PDU_CMD_UI       0x00	/* Type 1 cmds/rsps */
#घोषणा LLC_1_PDU_CMD_XID      0xAC
#घोषणा LLC_1_PDU_CMD_TEST     0xE0

#घोषणा LLC_2_PDU_CMD_SABME    0x6C	/* Type 2 cmds/rsps */
#घोषणा LLC_2_PDU_CMD_DISC     0x40
#घोषणा LLC_2_PDU_RSP_UA       0x60
#घोषणा LLC_2_PDU_RSP_DM       0x0C
#घोषणा LLC_2_PDU_RSP_FRMR     0x84

/* Type 1 operations */

/* XID inक्रमmation field bit masks */

/* LLC क्रमmat identअगरier (byte 1) */
#घोषणा LLC_XID_FMT_ID		0x81	/* first byte must be this */

/* LLC types/classes identअगरier (byte 2) */
#घोषणा LLC_XID_CLASS_ZEROS_MASK	0xE0	/* these must be zeros */
#घोषणा LLC_XID_CLASS_MASK		0x1F	/* AND with byte to get below */

#घोषणा LLC_XID_शून्य_CLASS_1	0x01	/* अगर शून्य LSAP...use these */
#घोषणा LLC_XID_शून्य_CLASS_2	0x03
#घोषणा LLC_XID_शून्य_CLASS_3	0x05
#घोषणा LLC_XID_शून्य_CLASS_4	0x07

#घोषणा LLC_XID_Nशून्य_TYPE_1	0x01	/* अगर non-शून्य LSAP...use these */
#घोषणा LLC_XID_Nशून्य_TYPE_2	0x02
#घोषणा LLC_XID_Nशून्य_TYPE_3	0x04
#घोषणा LLC_XID_Nशून्य_TYPE_1_2	0x03
#घोषणा LLC_XID_Nशून्य_TYPE_1_3	0x05
#घोषणा LLC_XID_Nशून्य_TYPE_2_3	0x06
#घोषणा LLC_XID_Nशून्य_ALL		0x07

/* Sender Receive Winकरोw (byte 3) */
#घोषणा LLC_XID_RW_MASK	0xFE	/* AND with value to get below */

#घोषणा LLC_XID_MIN_RW	0x02	/* lowest-order bit always zero */

/* Type 2 operations */

#घोषणा LLC_2_SEQ_NBR_MODULO   ((u8) 128)

/* I-PDU masks ('ctrl' is I-PDU control word) */
#घोषणा LLC_I_GET_NS(pdu)     (u8)((pdu->ctrl_1 & 0xFE) >> 1)
#घोषणा LLC_I_GET_NR(pdu)     (u8)((pdu->ctrl_2 & 0xFE) >> 1)

#घोषणा LLC_I_PF_BIT_MASK      0x01

#घोषणा LLC_I_PF_IS_0(pdu)     ((!(pdu->ctrl_2 & LLC_I_PF_BIT_MASK)) ? 1 : 0)
#घोषणा LLC_I_PF_IS_1(pdu)     ((pdu->ctrl_2 & LLC_I_PF_BIT_MASK) ? 1 : 0)

/* S-PDU supervisory commands and responses */

#घोषणा LLC_S_PDU_CMD_MASK     0x0C
#घोषणा LLC_S_PDU_CMD(pdu)     (pdu->ctrl_1 & LLC_S_PDU_CMD_MASK)
#घोषणा LLC_S_PDU_RSP(pdu)     (pdu->ctrl_1 & LLC_S_PDU_CMD_MASK)

#घोषणा LLC_2_PDU_CMD_RR       0x00	/* rx पढ़ोy cmd */
#घोषणा LLC_2_PDU_RSP_RR       0x00	/* rx पढ़ोy rsp */
#घोषणा LLC_2_PDU_CMD_REJ      0x08	/* reject PDU cmd */
#घोषणा LLC_2_PDU_RSP_REJ      0x08	/* reject PDU rsp */
#घोषणा LLC_2_PDU_CMD_RNR      0x04	/* rx not पढ़ोy cmd */
#घोषणा LLC_2_PDU_RSP_RNR      0x04	/* rx not पढ़ोy rsp */

#घोषणा LLC_S_PF_BIT_MASK      0x01
#घोषणा LLC_S_PF_IS_0(pdu)     ((!(pdu->ctrl_2 & LLC_S_PF_BIT_MASK)) ? 1 : 0)
#घोषणा LLC_S_PF_IS_1(pdu)     ((pdu->ctrl_2 & LLC_S_PF_BIT_MASK) ? 1 : 0)

#घोषणा PDU_SUPV_GET_Nr(pdu)   ((pdu->ctrl_2 & 0xFE) >> 1)
#घोषणा PDU_GET_NEXT_Vr(sn)    (((sn) + 1) & ~LLC_2_SEQ_NBR_MODULO)

/* FRMR inक्रमmation field macros */

#घोषणा FRMR_INFO_LENGTH       5	/* 5 bytes of inक्रमmation */

/*
 * info is poपूर्णांकer to FRMR info field काष्ठाure; 'rej_ctrl' is byte poपूर्णांकer
 * (अगर U-PDU) or word poपूर्णांकer to rejected PDU control field
 */
#घोषणा FRMR_INFO_SET_REJ_CNTRL(info,rej_ctrl) \
	info->rej_pdu_ctrl = ((*((u8 *) rej_ctrl) & \
				LLC_PDU_TYPE_U) != LLC_PDU_TYPE_U ? \
				(u16)*((u16 *) rej_ctrl) : \
				(((u16) *((u8 *) rej_ctrl)) & 0x00FF))

/*
 * Info is poपूर्णांकer to FRMR info field काष्ठाure; 'vs' is a byte containing
 * send state variable value in low-order 7 bits (insure the lowest-order
 * bit reमुख्यs zero (0))
 */
#घोषणा FRMR_INFO_SET_Vs(info,vs) (info->curr_ssv = (((u8) vs) << 1))
#घोषणा FRMR_INFO_SET_Vr(info,vr) (info->curr_rsv = (((u8) vr) << 1))

/*
 * Info is poपूर्णांकer to FRMR info field काष्ठाure; 'cr' is a byte containing
 * the C/R bit value in the low-order bit
 */
#घोषणा FRMR_INFO_SET_C_R_BIT(info, cr)  (info->curr_rsv |= (((u8) cr) & 0x01))

/*
 * In the reमुख्यing five macros, 'info' is poपूर्णांकer to FRMR info field
 * काष्ठाure; 'ind' is a byte containing the bit value to set in the
 * lowest-order bit)
 */
#घोषणा FRMR_INFO_SET_INVALID_PDU_CTRL_IND(info, ind) \
       (info->ind_bits = ((info->ind_bits & 0xFE) | (((u8) ind) & 0x01)))

#घोषणा FRMR_INFO_SET_INVALID_PDU_INFO_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xFD) | (((u8) ind) & 0x02)))

#घोषणा FRMR_INFO_SET_PDU_INFO_2LONG_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xFB) | (((u8) ind) & 0x04)))

#घोषणा FRMR_INFO_SET_PDU_INVALID_Nr_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xF7) | (((u8) ind) & 0x08)))

#घोषणा FRMR_INFO_SET_PDU_INVALID_Ns_IND(info, ind) \
       (info->ind_bits = ( (info->ind_bits & 0xEF) | (((u8) ind) & 0x10)))

/* Sequence-numbered PDU क्रमmat (4 bytes in length) */
काष्ठा llc_pdu_sn अणु
	u8 dsap;
	u8 ssap;
	u8 ctrl_1;
	u8 ctrl_2;
पूर्ण __packed;

अटल अंतरभूत काष्ठा llc_pdu_sn *llc_pdu_sn_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा llc_pdu_sn *)skb_network_header(skb);
पूर्ण

/* Un-numbered PDU क्रमmat (3 bytes in length) */
काष्ठा llc_pdu_un अणु
	u8 dsap;
	u8 ssap;
	u8 ctrl_1;
पूर्ण __packed;

अटल अंतरभूत काष्ठा llc_pdu_un *llc_pdu_un_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा llc_pdu_un *)skb_network_header(skb);
पूर्ण

/**
 *	llc_pdu_header_init - initializes pdu header
 *	@skb: input skb that header must be set पूर्णांकo it.
 *	@type: type of PDU (U, I or S).
 *	@ssap: source sap.
 *	@dsap: destination sap.
 *	@cr: command/response bit (0 or 1).
 *
 *	This function sets DSAP, SSAP and command/Response bit in LLC header.
 */
अटल अंतरभूत व्योम llc_pdu_header_init(काष्ठा sk_buff *skb, u8 type,
				       u8 ssap, u8 dsap, u8 cr)
अणु
	स्थिर पूर्णांक hlen = type == LLC_PDU_TYPE_U ? 3 : 4;
	काष्ठा llc_pdu_un *pdu;

	skb_push(skb, hlen);
	skb_reset_network_header(skb);
	pdu = llc_pdu_un_hdr(skb);
	pdu->dsap = dsap;
	pdu->ssap = ssap;
	pdu->ssap |= cr;
पूर्ण

/**
 *	llc_pdu_decode_sa - extracs source address (MAC) of input frame
 *	@skb: input skb that source address must be extracted from it.
 *	@sa: poपूर्णांकer to source address (6 byte array).
 *
 *	This function extracts source address(MAC) of input frame.
 */
अटल अंतरभूत व्योम llc_pdu_decode_sa(काष्ठा sk_buff *skb, u8 *sa)
अणु
	अगर (skb->protocol == htons(ETH_P_802_2))
		स_नकल(sa, eth_hdr(skb)->h_source, ETH_ALEN);
पूर्ण

/**
 *	llc_pdu_decode_da - extracts dest address of input frame
 *	@skb: input skb that destination address must be extracted from it
 *	@sa: poपूर्णांकer to destination address (6 byte array).
 *
 *	This function extracts destination address(MAC) of input frame.
 */
अटल अंतरभूत व्योम llc_pdu_decode_da(काष्ठा sk_buff *skb, u8 *da)
अणु
	अगर (skb->protocol == htons(ETH_P_802_2))
		स_नकल(da, eth_hdr(skb)->h_dest, ETH_ALEN);
पूर्ण

/**
 *	llc_pdu_decode_ssap - extracts source SAP of input frame
 *	@skb: input skb that source SAP must be extracted from it.
 *	@ssap: source SAP (output argument).
 *
 *	This function extracts source SAP of input frame. Right bit of SSAP is
 *	command/response bit.
 */
अटल अंतरभूत व्योम llc_pdu_decode_ssap(काष्ठा sk_buff *skb, u8 *ssap)
अणु
	*ssap = llc_pdu_un_hdr(skb)->ssap & 0xFE;
पूर्ण

/**
 *	llc_pdu_decode_dsap - extracts dest SAP of input frame
 *	@skb: input skb that destination SAP must be extracted from it.
 *	@dsap: destination SAP (output argument).
 *
 *	This function extracts destination SAP of input frame. right bit of
 *	DSAP designates inभागidual/group SAP.
 */
अटल अंतरभूत व्योम llc_pdu_decode_dsap(काष्ठा sk_buff *skb, u8 *dsap)
अणु
	*dsap = llc_pdu_un_hdr(skb)->dsap & 0xFE;
पूर्ण

/**
 *	llc_pdu_init_as_ui_cmd - sets LLC header as UI PDU
 *	@skb: input skb that header must be set पूर्णांकo it.
 *
 *	This function sets third byte of LLC header as a UI PDU.
 */
अटल अंतरभूत व्योम llc_pdu_init_as_ui_cmd(काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_1_PDU_CMD_UI;
पूर्ण

/**
 *	llc_pdu_init_as_test_cmd - sets PDU as TEST
 *	@skb - Address of the skb to build
 *
 * 	Sets a PDU as TEST
 */
अटल अंतरभूत व्योम llc_pdu_init_as_test_cmd(काष्ठा sk_buff *skb)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_1_PDU_CMD_TEST;
	pdu->ctrl_1 |= LLC_U_PF_BIT_MASK;
पूर्ण

/**
 *	llc_pdu_init_as_test_rsp - build TEST response PDU
 *	@skb: Address of the skb to build
 *	@ev_skb: The received TEST command PDU frame
 *
 *	Builds a pdu frame as a TEST response.
 */
अटल अंतरभूत व्योम llc_pdu_init_as_test_rsp(काष्ठा sk_buff *skb,
					    काष्ठा sk_buff *ev_skb)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_1_PDU_CMD_TEST;
	pdu->ctrl_1 |= LLC_U_PF_BIT_MASK;
	अगर (ev_skb->protocol == htons(ETH_P_802_2)) अणु
		काष्ठा llc_pdu_un *ev_pdu = llc_pdu_un_hdr(ev_skb);
		पूर्णांक dsize;

		dsize = ntohs(eth_hdr(ev_skb)->h_proto) - 3;
		स_नकल(((u8 *)pdu) + 3, ((u8 *)ev_pdu) + 3, dsize);
		skb_put(skb, dsize);
	पूर्ण
पूर्ण

/* LLC Type 1 XID command/response inक्रमmation fields क्रमmat */
काष्ठा llc_xid_info अणु
	u8 fmt_id;	/* always 0x81 क्रम LLC */
	u8 type;	/* dअगरferent अगर शून्य/non-शून्य LSAP */
	u8 rw;		/* sender receive winकरोw */
पूर्ण __packed;

/**
 *	llc_pdu_init_as_xid_cmd - sets bytes 3, 4 & 5 of LLC header as XID
 *	@skb: input skb that header must be set पूर्णांकo it.
 *
 *	This function sets third,fourth,fअगरth and sixth bytes of LLC header as
 *	a XID PDU.
 */
अटल अंतरभूत व्योम llc_pdu_init_as_xid_cmd(काष्ठा sk_buff *skb,
					   u8 svcs_supported, u8 rx_winकरोw)
अणु
	काष्ठा llc_xid_info *xid_info;
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1	 = LLC_PDU_TYPE_U;
	pdu->ctrl_1	|= LLC_1_PDU_CMD_XID;
	pdu->ctrl_1	|= LLC_U_PF_BIT_MASK;
	xid_info	 = (काष्ठा llc_xid_info *)(((u8 *)&pdu->ctrl_1) + 1);
	xid_info->fmt_id = LLC_XID_FMT_ID;	/* 0x81 */
	xid_info->type	 = svcs_supported;
	xid_info->rw	 = rx_winकरोw << 1;	/* size of receive winकरोw */
	skb_put(skb, माप(काष्ठा llc_xid_info));
पूर्ण

/**
 *	llc_pdu_init_as_xid_rsp - builds XID response PDU
 *	@skb: Address of the skb to build
 *	@svcs_supported: The class of the LLC (I or II)
 *	@rx_winकरोw: The size of the receive winकरोw of the LLC
 *
 *	Builds a pdu frame as an XID response.
 */
अटल अंतरभूत व्योम llc_pdu_init_as_xid_rsp(काष्ठा sk_buff *skb,
					   u8 svcs_supported, u8 rx_winकरोw)
अणु
	काष्ठा llc_xid_info *xid_info;
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1	 = LLC_PDU_TYPE_U;
	pdu->ctrl_1	|= LLC_1_PDU_CMD_XID;
	pdu->ctrl_1	|= LLC_U_PF_BIT_MASK;

	xid_info	 = (काष्ठा llc_xid_info *)(((u8 *)&pdu->ctrl_1) + 1);
	xid_info->fmt_id = LLC_XID_FMT_ID;
	xid_info->type	 = svcs_supported;
	xid_info->rw	 = rx_winकरोw << 1;
	skb_put(skb, माप(काष्ठा llc_xid_info));
पूर्ण

/* LLC Type 2 FRMR response inक्रमmation field क्रमmat */
काष्ठा llc_frmr_info अणु
	u16 rej_pdu_ctrl;	/* bits 1-8 अगर U-PDU */
	u8  curr_ssv;		/* current send state variable val */
	u8  curr_rsv;		/* current receive state variable */
	u8  ind_bits;		/* indicator bits set with macro */
पूर्ण __packed;

व्योम llc_pdu_set_cmd_rsp(काष्ठा sk_buff *skb, u8 type);
व्योम llc_pdu_set_pf_bit(काष्ठा sk_buff *skb, u8 bit_value);
व्योम llc_pdu_decode_pf_bit(काष्ठा sk_buff *skb, u8 *pf_bit);
व्योम llc_pdu_init_as_disc_cmd(काष्ठा sk_buff *skb, u8 p_bit);
व्योम llc_pdu_init_as_i_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 ns, u8 nr);
व्योम llc_pdu_init_as_rej_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 nr);
व्योम llc_pdu_init_as_rnr_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 nr);
व्योम llc_pdu_init_as_rr_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 nr);
व्योम llc_pdu_init_as_sabme_cmd(काष्ठा sk_buff *skb, u8 p_bit);
व्योम llc_pdu_init_as_dm_rsp(काष्ठा sk_buff *skb, u8 f_bit);
व्योम llc_pdu_init_as_frmr_rsp(काष्ठा sk_buff *skb, काष्ठा llc_pdu_sn *prev_pdu,
			      u8 f_bit, u8 vs, u8 vr, u8 vzyxw);
व्योम llc_pdu_init_as_rr_rsp(काष्ठा sk_buff *skb, u8 f_bit, u8 nr);
व्योम llc_pdu_init_as_rej_rsp(काष्ठा sk_buff *skb, u8 f_bit, u8 nr);
व्योम llc_pdu_init_as_rnr_rsp(काष्ठा sk_buff *skb, u8 f_bit, u8 nr);
व्योम llc_pdu_init_as_ua_rsp(काष्ठा sk_buff *skb, u8 f_bit);
#पूर्ण_अगर /* LLC_PDU_H */
