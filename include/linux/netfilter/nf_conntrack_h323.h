<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_H323_H
#घोषणा _NF_CONNTRACK_H323_H

#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/netfilter/nf_conntrack_h323_asn1.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <uapi/linux/netfilter/nf_conntrack_tuple_common.h>

#घोषणा RAS_PORT 1719
#घोषणा Q931_PORT 1720
#घोषणा H323_RTP_CHANNEL_MAX 4	/* Audio, video, FAX and other */

/* This काष्ठाure exists only once per master */
काष्ठा nf_ct_h323_master अणु

	/* Original and NATed Q.931 or H.245 संकेत ports */
	__be16 sig_port[IP_CT_सूची_MAX];

	/* Original and NATed RTP ports */
	__be16 rtp_port[H323_RTP_CHANNEL_MAX][IP_CT_सूची_MAX];

	जोड़ अणु
		/* RAS connection समयout */
		u_पूर्णांक32_t समयout;

		/* Next TPKT length (क्रम separate TPKT header and data) */
		u_पूर्णांक16_t tpkt_len[IP_CT_सूची_MAX];
	पूर्ण;
पूर्ण;

पूर्णांक get_h225_addr(काष्ठा nf_conn *ct, अचिन्हित अक्षर *data,
		  TransportAddress *taddr, जोड़ nf_inet_addr *addr,
		  __be16 *port);
व्योम nf_conntrack_h245_expect(काष्ठा nf_conn *new,
			      काष्ठा nf_conntrack_expect *this);
व्योम nf_conntrack_q931_expect(काष्ठा nf_conn *new,
			      काष्ठा nf_conntrack_expect *this);
बाह्य पूर्णांक (*set_h245_addr_hook) (काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				  अचिन्हित अक्षर **data, पूर्णांक dataoff,
				  H245_TransportAddress *taddr,
				  जोड़ nf_inet_addr *addr,
				  __be16 port);
बाह्य पूर्णांक (*set_h225_addr_hook) (काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				  अचिन्हित अक्षर **data, पूर्णांक dataoff,
				  TransportAddress *taddr,
				  जोड़ nf_inet_addr *addr,
				  __be16 port);
बाह्य पूर्णांक (*set_sig_addr_hook) (काष्ठा sk_buff *skb,
				 काष्ठा nf_conn *ct,
				 क्रमागत ip_conntrack_info ctinfo,
				 अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
				 TransportAddress *taddr, पूर्णांक count);
बाह्य पूर्णांक (*set_ras_addr_hook) (काष्ठा sk_buff *skb,
				 काष्ठा nf_conn *ct,
				 क्रमागत ip_conntrack_info ctinfo,
				 अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
				 TransportAddress *taddr, पूर्णांक count);
बाह्य पूर्णांक (*nat_rtp_rtcp_hook) (काष्ठा sk_buff *skb,
				 काष्ठा nf_conn *ct,
				 क्रमागत ip_conntrack_info ctinfo,
				 अचिन्हित पूर्णांक protoff, अचिन्हित अक्षर **data,
				 पूर्णांक dataoff,
				 H245_TransportAddress *taddr,
				 __be16 port, __be16 rtp_port,
				 काष्ठा nf_conntrack_expect *rtp_exp,
				 काष्ठा nf_conntrack_expect *rtcp_exp);
बाह्य पूर्णांक (*nat_t120_hook) (काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			     क्रमागत ip_conntrack_info ctinfo,
			     अचिन्हित पूर्णांक protoff,
			     अचिन्हित अक्षर **data, पूर्णांक dataoff,
			     H245_TransportAddress *taddr, __be16 port,
			     काष्ठा nf_conntrack_expect *exp);
बाह्य पूर्णांक (*nat_h245_hook) (काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			     क्रमागत ip_conntrack_info ctinfo,
			     अचिन्हित पूर्णांक protoff,
			     अचिन्हित अक्षर **data, पूर्णांक dataoff,
			     TransportAddress *taddr, __be16 port,
			     काष्ठा nf_conntrack_expect *exp);
बाह्य पूर्णांक (*nat_callक्रमwarding_hook) (काष्ठा sk_buff *skb,
				       काष्ठा nf_conn *ct,
				       क्रमागत ip_conntrack_info ctinfo,
				       अचिन्हित पूर्णांक protoff,
				       अचिन्हित अक्षर **data, पूर्णांक dataoff,
				       TransportAddress *taddr,
				       __be16 port,
				       काष्ठा nf_conntrack_expect *exp);
बाह्य पूर्णांक (*nat_q931_hook) (काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			     क्रमागत ip_conntrack_info ctinfo,
			     अचिन्हित पूर्णांक protoff,
			     अचिन्हित अक्षर **data, TransportAddress *taddr,
			     पूर्णांक idx, __be16 port,
			     काष्ठा nf_conntrack_expect *exp);

#पूर्ण_अगर
