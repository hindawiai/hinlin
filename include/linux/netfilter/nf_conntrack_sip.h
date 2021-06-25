<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NF_CONNTRACK_SIP_H__
#घोषणा __NF_CONNTRACK_SIP_H__

#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

#घोषणा SIP_PORT	5060
#घोषणा SIP_TIMEOUT	3600

काष्ठा nf_ct_sip_master अणु
	अचिन्हित पूर्णांक	रेजिस्टर_cseq;
	अचिन्हित पूर्णांक	invite_cseq;
	__be16		क्रमced_dport;
पूर्ण;

क्रमागत sip_expectation_classes अणु
	SIP_EXPECT_SIGNALLING,
	SIP_EXPECT_AUDIO,
	SIP_EXPECT_VIDEO,
	SIP_EXPECT_IMAGE,
	__SIP_EXPECT_MAX
पूर्ण;
#घोषणा SIP_EXPECT_MAX	(__SIP_EXPECT_MAX - 1)

काष्ठा sdp_media_type अणु
	स्थिर अक्षर			*name;
	अचिन्हित पूर्णांक			len;
	क्रमागत sip_expectation_classes	class;
पूर्ण;

#घोषणा SDP_MEDIA_TYPE(__name, __class)					\
अणु									\
	.name	= (__name),						\
	.len	= माप(__name) - 1,					\
	.class	= (__class),						\
पूर्ण

काष्ठा sip_handler अणु
	स्थिर अक्षर	*method;
	अचिन्हित पूर्णांक	len;
	पूर्णांक		(*request)(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				   अचिन्हित पूर्णांक dataoff,
				   स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				   अचिन्हित पूर्णांक cseq);
	पूर्णांक		(*response)(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				    अचिन्हित पूर्णांक dataoff,
				    स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				    अचिन्हित पूर्णांक cseq, अचिन्हित पूर्णांक code);
पूर्ण;

#घोषणा SIP_HANDLER(__method, __request, __response)			\
अणु									\
	.method		= (__method),					\
	.len		= माप(__method) - 1,				\
	.request	= (__request),					\
	.response	= (__response),					\
पूर्ण

काष्ठा sip_header अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*cname;
	स्थिर अक्षर	*search;
	अचिन्हित पूर्णांक	len;
	अचिन्हित पूर्णांक	clen;
	अचिन्हित पूर्णांक	slen;
	पूर्णांक		(*match_len)(स्थिर काष्ठा nf_conn *ct,
				     स्थिर अक्षर *dptr, स्थिर अक्षर *limit,
				     पूर्णांक *shअगरt);
पूर्ण;

#घोषणा __SIP_HDR(__name, __cname, __search, __match)			\
अणु									\
	.name		= (__name),					\
	.len		= माप(__name) - 1,				\
	.cname		= (__cname),					\
	.clen		= (__cname) ? माप(__cname) - 1 : 0,		\
	.search		= (__search),					\
	.slen		= (__search) ? माप(__search) - 1 : 0,	\
	.match_len	= (__match),					\
पूर्ण

#घोषणा SIP_HDR(__name, __cname, __search, __match) \
	__SIP_HDR(__name, __cname, __search, __match)

#घोषणा SDP_HDR(__name, __search, __match) \
	__SIP_HDR(__name, शून्य, __search, __match)

क्रमागत sip_header_types अणु
	SIP_HDR_CSEQ,
	SIP_HDR_FROM,
	SIP_HDR_TO,
	SIP_HDR_CONTACT,
	SIP_HDR_VIA_UDP,
	SIP_HDR_VIA_TCP,
	SIP_HDR_EXPIRES,
	SIP_HDR_CONTENT_LENGTH,
	SIP_HDR_CALL_ID,
पूर्ण;

क्रमागत sdp_header_types अणु
	SDP_HDR_UNSPEC,
	SDP_HDR_VERSION,
	SDP_HDR_OWNER,
	SDP_HDR_CONNECTION,
	SDP_HDR_MEDIA,
पूर्ण;

काष्ठा nf_nat_sip_hooks अणु
	अचिन्हित पूर्णांक (*msg)(काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक protoff,
			    अचिन्हित पूर्णांक dataoff,
			    स्थिर अक्षर **dptr,
			    अचिन्हित पूर्णांक *datalen);

	व्योम (*seq_adjust)(काष्ठा sk_buff *skb,
			   अचिन्हित पूर्णांक protoff, s16 off);

	अचिन्हित पूर्णांक (*expect)(काष्ठा sk_buff *skb,
			       अचिन्हित पूर्णांक protoff,
			       अचिन्हित पूर्णांक dataoff,
			       स्थिर अक्षर **dptr,
			       अचिन्हित पूर्णांक *datalen,
			       काष्ठा nf_conntrack_expect *exp,
			       अचिन्हित पूर्णांक matchoff,
			       अचिन्हित पूर्णांक matchlen);

	अचिन्हित पूर्णांक (*sdp_addr)(काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक protoff,
				 अचिन्हित पूर्णांक dataoff,
				 स्थिर अक्षर **dptr,
				 अचिन्हित पूर्णांक *datalen,
				 अचिन्हित पूर्णांक sdpoff,
				 क्रमागत sdp_header_types type,
				 क्रमागत sdp_header_types term,
				 स्थिर जोड़ nf_inet_addr *addr);

	अचिन्हित पूर्णांक (*sdp_port)(काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक protoff,
				 अचिन्हित पूर्णांक dataoff,
				 स्थिर अक्षर **dptr,
				 अचिन्हित पूर्णांक *datalen,
				 अचिन्हित पूर्णांक matchoff,
				 अचिन्हित पूर्णांक matchlen,
				 u_पूर्णांक16_t port);

	अचिन्हित पूर्णांक (*sdp_session)(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक protoff,
				    अचिन्हित पूर्णांक dataoff,
				    स्थिर अक्षर **dptr,
				    अचिन्हित पूर्णांक *datalen,
				    अचिन्हित पूर्णांक sdpoff,
				    स्थिर जोड़ nf_inet_addr *addr);

	अचिन्हित पूर्णांक (*sdp_media)(काष्ठा sk_buff *skb,
				  अचिन्हित पूर्णांक protoff,
				  अचिन्हित पूर्णांक dataoff,
				  स्थिर अक्षर **dptr,
				  अचिन्हित पूर्णांक *datalen,
				  काष्ठा nf_conntrack_expect *rtp_exp,
				  काष्ठा nf_conntrack_expect *rtcp_exp,
				  अचिन्हित पूर्णांक mediaoff,
				  अचिन्हित पूर्णांक medialen,
				  जोड़ nf_inet_addr *rtp_addr);
पूर्ण;
बाह्य स्थिर काष्ठा nf_nat_sip_hooks *nf_nat_sip_hooks;

पूर्णांक ct_sip_parse_request(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			 अचिन्हित पूर्णांक datalen, अचिन्हित पूर्णांक *matchoff,
			 अचिन्हित पूर्णांक *matchlen, जोड़ nf_inet_addr *addr,
			 __be16 *port);
पूर्णांक ct_sip_get_header(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		      अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
		      क्रमागत sip_header_types type, अचिन्हित पूर्णांक *matchoff,
		      अचिन्हित पूर्णांक *matchlen);
पूर्णांक ct_sip_parse_header_uri(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			    अचिन्हित पूर्णांक *dataoff, अचिन्हित पूर्णांक datalen,
			    क्रमागत sip_header_types type, पूर्णांक *in_header,
			    अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen,
			    जोड़ nf_inet_addr *addr, __be16 *port);
पूर्णांक ct_sip_parse_address_param(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			       अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			       स्थिर अक्षर *name, अचिन्हित पूर्णांक *matchoff,
			       अचिन्हित पूर्णांक *matchlen, जोड़ nf_inet_addr *addr,
			       bool delim);
पूर्णांक ct_sip_parse_numerical_param(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
				 अचिन्हित पूर्णांक off, अचिन्हित पूर्णांक datalen,
				 स्थिर अक्षर *name, अचिन्हित पूर्णांक *matchoff,
				 अचिन्हित पूर्णांक *matchen, अचिन्हित पूर्णांक *val);

पूर्णांक ct_sip_get_sdp_header(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			  अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			  क्रमागत sdp_header_types type,
			  क्रमागत sdp_header_types term,
			  अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen);

#पूर्ण_अगर /* __NF_CONNTRACK_SIP_H__ */
