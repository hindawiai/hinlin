<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IPv4 support क्रम nf_conntrack.
 *
 * 23 Mar 2004: Yasuyuki Kozakai @ USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- move L3 protocol dependent part from include/linux/netfilter_ipv4/
 *	  ip_conntarck.h
 */

#अगर_अघोषित _NF_CONNTRACK_IPV4_H
#घोषणा _NF_CONNTRACK_IPV4_H

बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_tcp;
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_udp;
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_icmp;
#अगर_घोषित CONFIG_NF_CT_PROTO_DCCP
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_dccp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_SCTP
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_sctp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_UDPLITE
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_udplite;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CT_PROTO_GRE
बाह्य स्थिर काष्ठा nf_conntrack_l4proto nf_conntrack_l4proto_gre;
#पूर्ण_अगर

#पूर्ण_अगर /*_NF_CONNTRACK_IPV4_H*/
