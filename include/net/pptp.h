<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_PPTP_H
#घोषणा _NET_PPTP_H

#घोषणा PPP_LCP_ECHOREQ 0x09
#घोषणा PPP_LCP_ECHOREP 0x0A
#घोषणा SC_RCV_BITS     (SC_RCV_B7_1|SC_RCV_B7_0|SC_RCV_ODDP|SC_RCV_EVNP)

#घोषणा MISSING_WINDOW 20
#घोषणा WRAPPED(curseq, lastseq)\
	((((curseq) & 0xffffff00) == 0) &&\
	(((lastseq) & 0xffffff00) == 0xffffff00))

#घोषणा PPTP_HEADER_OVERHEAD (2+माप(काष्ठा pptp_gre_header))
काष्ठा pptp_gre_header अणु
	काष्ठा gre_base_hdr gre_hd;
	__be16 payload_len;
	__be16 call_id;
	__be32 seq;
	__be32 ack;
पूर्ण __packed;


#पूर्ण_अगर
