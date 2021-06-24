<शैली गुरु>
/*
 * llc_pdu.c - access to PDU पूर्णांकernals
 *
 * Copyright (c) 1997 by Procom Technology, Inc.
 *		 2001-2003 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#समावेश <linux/netdevice.h>
#समावेश <net/llc_pdu.h>

अटल व्योम llc_pdu_decode_pdu_type(काष्ठा sk_buff *skb, u8 *type);
अटल u8 llc_pdu_get_pf_bit(काष्ठा llc_pdu_sn *pdu);

व्योम llc_pdu_set_cmd_rsp(काष्ठा sk_buff *skb, u8 pdu_type)
अणु
	llc_pdu_un_hdr(skb)->ssap |= pdu_type;
पूर्ण

/**
 *	llc_pdu_set_pf_bit - sets poll/final bit in LLC header
 *	@skb: Frame to set bit in
 *	@bit_value: poll/final bit (0 or 1).
 *
 *	This function sets poll/final bit in LLC header (based on type of PDU).
 *	in I or S pdus, p/f bit is right bit of fourth byte in header. in U
 *	pdus p/f bit is fअगरth bit of third byte.
 */
व्योम llc_pdu_set_pf_bit(काष्ठा sk_buff *skb, u8 bit_value)
अणु
	u8 pdu_type;
	काष्ठा llc_pdu_sn *pdu;

	llc_pdu_decode_pdu_type(skb, &pdu_type);
	pdu = llc_pdu_sn_hdr(skb);

	चयन (pdu_type) अणु
	हाल LLC_PDU_TYPE_I:
	हाल LLC_PDU_TYPE_S:
		pdu->ctrl_2 = (pdu->ctrl_2 & 0xFE) | bit_value;
		अवरोध;
	हाल LLC_PDU_TYPE_U:
		pdu->ctrl_1 |= (pdu->ctrl_1 & 0xEF) | (bit_value << 4);
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	llc_pdu_decode_pf_bit - extracs poll/final bit from LLC header
 *	@skb: input skb that p/f bit must be extracted from it
 *	@pf_bit: poll/final bit (0 or 1)
 *
 *	This function extracts poll/final bit from LLC header (based on type of
 *	PDU). In I or S pdus, p/f bit is right bit of fourth byte in header. In
 *	U pdus p/f bit is fअगरth bit of third byte.
 */
व्योम llc_pdu_decode_pf_bit(काष्ठा sk_buff *skb, u8 *pf_bit)
अणु
	u8 pdu_type;
	काष्ठा llc_pdu_sn *pdu;

	llc_pdu_decode_pdu_type(skb, &pdu_type);
	pdu = llc_pdu_sn_hdr(skb);

	चयन (pdu_type) अणु
	हाल LLC_PDU_TYPE_I:
	हाल LLC_PDU_TYPE_S:
		*pf_bit = pdu->ctrl_2 & LLC_S_PF_BIT_MASK;
		अवरोध;
	हाल LLC_PDU_TYPE_U:
		*pf_bit = (pdu->ctrl_1 & LLC_U_PF_BIT_MASK) >> 4;
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	llc_pdu_init_as_disc_cmd - Builds DISC PDU
 *	@skb: Address of the skb to build
 *	@p_bit: The P bit to set in the PDU
 *
 *	Builds a pdu frame as a DISC command.
 */
व्योम llc_pdu_init_as_disc_cmd(काष्ठा sk_buff *skb, u8 p_bit)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_CMD_DISC;
	pdu->ctrl_1 |= ((p_bit & 1) << 4) & LLC_U_PF_BIT_MASK;
पूर्ण

/**
 *	llc_pdu_init_as_i_cmd - builds I pdu
 *	@skb: Address of the skb to build
 *	@p_bit: The P bit to set in the PDU
 *	@ns: The sequence number of the data PDU
 *	@nr: The seq. number of the expected I PDU from the remote
 *
 *	Builds a pdu frame as an I command.
 */
व्योम llc_pdu_init_as_i_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 ns, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_I;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= (p_bit & LLC_I_PF_BIT_MASK); /* p/f bit */
	pdu->ctrl_1 |= (ns << 1) & 0xFE;   /* set N(S) in bits 2..8 */
	pdu->ctrl_2 |= (nr << 1) & 0xFE;   /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_rej_cmd - builds REJ PDU
 *	@skb: Address of the skb to build
 *	@p_bit: The P bit to set in the PDU
 *	@nr: The seq. number of the expected I PDU from the remote
 *
 *	Builds a pdu frame as a REJ command.
 */
व्योम llc_pdu_init_as_rej_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_S;
	pdu->ctrl_1 |= LLC_2_PDU_CMD_REJ;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= p_bit & LLC_S_PF_BIT_MASK;
	pdu->ctrl_1 &= 0x0F;    /* setting bits 5..8 to zero(reserved) */
	pdu->ctrl_2 |= (nr << 1) & 0xFE; /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_rnr_cmd - builds RNR pdu
 *	@skb: Address of the skb to build
 *	@p_bit: The P bit to set in the PDU
 *	@nr: The seq. number of the expected I PDU from the remote
 *
 *	Builds a pdu frame as an RNR command.
 */
व्योम llc_pdu_init_as_rnr_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_S;
	pdu->ctrl_1 |= LLC_2_PDU_CMD_RNR;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= p_bit & LLC_S_PF_BIT_MASK;
	pdu->ctrl_1 &= 0x0F;    /* setting bits 5..8 to zero(reserved) */
	pdu->ctrl_2 |= (nr << 1) & 0xFE; /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_rr_cmd - Builds RR pdu
 *	@skb: Address of the skb to build
 *	@p_bit: The P bit to set in the PDU
 *	@nr: The seq. number of the expected I PDU from the remote
 *
 *	Builds a pdu frame as an RR command.
 */
व्योम llc_pdu_init_as_rr_cmd(काष्ठा sk_buff *skb, u8 p_bit, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_S;
	pdu->ctrl_1 |= LLC_2_PDU_CMD_RR;
	pdu->ctrl_2  = p_bit & LLC_S_PF_BIT_MASK;
	pdu->ctrl_1 &= 0x0F;    /* setting bits 5..8 to zero(reserved) */
	pdu->ctrl_2 |= (nr << 1) & 0xFE; /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_sabme_cmd - builds SABME pdu
 *	@skb: Address of the skb to build
 *	@p_bit: The P bit to set in the PDU
 *
 *	Builds a pdu frame as an SABME command.
 */
व्योम llc_pdu_init_as_sabme_cmd(काष्ठा sk_buff *skb, u8 p_bit)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_CMD_SABME;
	pdu->ctrl_1 |= ((p_bit & 1) << 4) & LLC_U_PF_BIT_MASK;
पूर्ण

/**
 *	llc_pdu_init_as_dm_rsp - builds DM response pdu
 *	@skb: Address of the skb to build
 *	@f_bit: The F bit to set in the PDU
 *
 *	Builds a pdu frame as a DM response.
 */
व्योम llc_pdu_init_as_dm_rsp(काष्ठा sk_buff *skb, u8 f_bit)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_DM;
	pdu->ctrl_1 |= ((f_bit & 1) << 4) & LLC_U_PF_BIT_MASK;
पूर्ण

/**
 *	llc_pdu_init_as_frmr_rsp - builds FRMR response PDU
 *	@skb: Address of the frame to build
 *	@prev_pdu: The rejected PDU frame
 *	@f_bit: The F bit to set in the PDU
 *	@vs: tx state vari value क्रम the data link conn at the rejecting LLC
 *	@vr: rx state var value क्रम the data link conn at the rejecting LLC
 *	@vzyxw: completely described in the IEEE Std 802.2 करोcument (Pg 55)
 *
 *	Builds a pdu frame as a FRMR response.
 */
व्योम llc_pdu_init_as_frmr_rsp(काष्ठा sk_buff *skb, काष्ठा llc_pdu_sn *prev_pdu,
			      u8 f_bit, u8 vs, u8 vr, u8 vzyxw)
अणु
	काष्ठा llc_frmr_info *frmr_info;
	u8 prev_pf = 0;
	u8 *ctrl;
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_FRMR;
	pdu->ctrl_1 |= ((f_bit & 1) << 4) & LLC_U_PF_BIT_MASK;

	frmr_info = (काष्ठा llc_frmr_info *)&pdu->ctrl_2;
	ctrl = (u8 *)&prev_pdu->ctrl_1;
	FRMR_INFO_SET_REJ_CNTRL(frmr_info,ctrl);
	FRMR_INFO_SET_Vs(frmr_info, vs);
	FRMR_INFO_SET_Vr(frmr_info, vr);
	prev_pf = llc_pdu_get_pf_bit(prev_pdu);
	FRMR_INFO_SET_C_R_BIT(frmr_info, prev_pf);
	FRMR_INFO_SET_INVALID_PDU_CTRL_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_INVALID_PDU_INFO_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_PDU_INFO_2LONG_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_PDU_INVALID_Nr_IND(frmr_info, vzyxw);
	FRMR_INFO_SET_PDU_INVALID_Ns_IND(frmr_info, vzyxw);
	skb_put(skb, माप(काष्ठा llc_frmr_info));
पूर्ण

/**
 *	llc_pdu_init_as_rr_rsp - builds RR response pdu
 *	@skb: Address of the skb to build
 *	@f_bit: The F bit to set in the PDU
 *	@nr: The seq. number of the expected data PDU from the remote
 *
 *	Builds a pdu frame as an RR response.
 */
व्योम llc_pdu_init_as_rr_rsp(काष्ठा sk_buff *skb, u8 f_bit, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_S;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_RR;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= f_bit & LLC_S_PF_BIT_MASK;
	pdu->ctrl_1 &= 0x0F;    /* setting bits 5..8 to zero(reserved) */
	pdu->ctrl_2 |= (nr << 1) & 0xFE;  /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_rej_rsp - builds REJ response pdu
 *	@skb: Address of the skb to build
 *	@f_bit: The F bit to set in the PDU
 *	@nr: The seq. number of the expected data PDU from the remote
 *
 *	Builds a pdu frame as a REJ response.
 */
व्योम llc_pdu_init_as_rej_rsp(काष्ठा sk_buff *skb, u8 f_bit, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_S;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_REJ;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= f_bit & LLC_S_PF_BIT_MASK;
	pdu->ctrl_1 &= 0x0F;    /* setting bits 5..8 to zero(reserved) */
	pdu->ctrl_2 |= (nr << 1) & 0xFE;  /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_rnr_rsp - builds RNR response pdu
 *	@skb: Address of the frame to build
 *	@f_bit: The F bit to set in the PDU
 *	@nr: The seq. number of the expected data PDU from the remote
 *
 *	Builds a pdu frame as an RNR response.
 */
व्योम llc_pdu_init_as_rnr_rsp(काष्ठा sk_buff *skb, u8 f_bit, u8 nr)
अणु
	काष्ठा llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_S;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_RNR;
	pdu->ctrl_2  = 0;
	pdu->ctrl_2 |= f_bit & LLC_S_PF_BIT_MASK;
	pdu->ctrl_1 &= 0x0F;    /* setting bits 5..8 to zero(reserved) */
	pdu->ctrl_2 |= (nr << 1) & 0xFE;  /* set N(R) in bits 10..16 */
पूर्ण

/**
 *	llc_pdu_init_as_ua_rsp - builds UA response pdu
 *	@skb: Address of the frame to build
 *	@f_bit: The F bit to set in the PDU
 *
 *	Builds a pdu frame as a UA response.
 */
व्योम llc_pdu_init_as_ua_rsp(काष्ठा sk_buff *skb, u8 f_bit)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	pdu->ctrl_1  = LLC_PDU_TYPE_U;
	pdu->ctrl_1 |= LLC_2_PDU_RSP_UA;
	pdu->ctrl_1 |= ((f_bit & 1) << 4) & LLC_U_PF_BIT_MASK;
पूर्ण

/**
 *	llc_pdu_decode_pdu_type - designates PDU type
 *	@skb: input skb that type of it must be designated.
 *	@type: type of PDU (output argument).
 *
 *	This function designates type of PDU (I, S or U).
 */
अटल व्योम llc_pdu_decode_pdu_type(काष्ठा sk_buff *skb, u8 *type)
अणु
	काष्ठा llc_pdu_un *pdu = llc_pdu_un_hdr(skb);

	अगर (pdu->ctrl_1 & 1) अणु
		अगर ((pdu->ctrl_1 & LLC_PDU_TYPE_U) == LLC_PDU_TYPE_U)
			*type = LLC_PDU_TYPE_U;
		अन्यथा
			*type = LLC_PDU_TYPE_S;
	पूर्ण अन्यथा
		*type = LLC_PDU_TYPE_I;
पूर्ण

/**
 *	llc_pdu_get_pf_bit - extracts p/f bit of input PDU
 *	@pdu: poपूर्णांकer to LLC header.
 *
 *	This function extracts p/f bit of input PDU. at first examines type of
 *	PDU and then extracts p/f bit. Returns the p/f bit.
 */
अटल u8 llc_pdu_get_pf_bit(काष्ठा llc_pdu_sn *pdu)
अणु
	u8 pdu_type;
	u8 pf_bit = 0;

	अगर (pdu->ctrl_1 & 1) अणु
		अगर ((pdu->ctrl_1 & LLC_PDU_TYPE_U) == LLC_PDU_TYPE_U)
			pdu_type = LLC_PDU_TYPE_U;
		अन्यथा
			pdu_type = LLC_PDU_TYPE_S;
	पूर्ण अन्यथा
		pdu_type = LLC_PDU_TYPE_I;
	चयन (pdu_type) अणु
	हाल LLC_PDU_TYPE_I:
	हाल LLC_PDU_TYPE_S:
		pf_bit = pdu->ctrl_2 & LLC_S_PF_BIT_MASK;
		अवरोध;
	हाल LLC_PDU_TYPE_U:
		pf_bit = (pdu->ctrl_1 & LLC_U_PF_BIT_MASK) >> 4;
		अवरोध;
	पूर्ण
	वापस pf_bit;
पूर्ण
