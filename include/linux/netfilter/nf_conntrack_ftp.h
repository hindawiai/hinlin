<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_FTP_H
#घोषणा _NF_CONNTRACK_FTP_H

#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <uapi/linux/netfilter/nf_conntrack_ftp.h>
#समावेश <uapi/linux/netfilter/nf_conntrack_tuple_common.h>

#घोषणा FTP_PORT	21

#घोषणा NF_CT_FTP_SEQ_PICKUP	(1 << 0)

#घोषणा NUM_SEQ_TO_REMEMBER 2
/* This काष्ठाure exists only once per master */
काष्ठा nf_ct_ftp_master अणु
	/* Valid seq positions क्रम cmd matching after newline */
	u_पूर्णांक32_t seq_aft_nl[IP_CT_सूची_MAX][NUM_SEQ_TO_REMEMBER];
	/* 0 means seq_match_aft_nl not set */
	u_पूर्णांक16_t seq_aft_nl_num[IP_CT_सूची_MAX];
	/* pickup sequence tracking, useful क्रम conntrackd */
	u_पूर्णांक16_t flags[IP_CT_सूची_MAX];
पूर्ण;

/* For NAT to hook in when we find a packet which describes what other
 * connection we should expect. */
बाह्य अचिन्हित पूर्णांक (*nf_nat_ftp_hook)(काष्ठा sk_buff *skb,
				       क्रमागत ip_conntrack_info ctinfo,
				       क्रमागत nf_ct_ftp_type type,
				       अचिन्हित पूर्णांक protoff,
				       अचिन्हित पूर्णांक matchoff,
				       अचिन्हित पूर्णांक matchlen,
				       काष्ठा nf_conntrack_expect *exp);
#पूर्ण_अगर /* _NF_CONNTRACK_FTP_H */
