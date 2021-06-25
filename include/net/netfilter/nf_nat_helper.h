<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_NAT_HELPER_H
#घोषणा _NF_NAT_HELPER_H
/* NAT protocol helper routines. */

#समावेश <linux/skbuff.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

/* These वापस true or false. */
bool __nf_nat_mangle_tcp_packet(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक protoff, अचिन्हित पूर्णांक match_offset,
				अचिन्हित पूर्णांक match_len, स्थिर अक्षर *rep_buffer,
				अचिन्हित पूर्णांक rep_len, bool adjust);

अटल अंतरभूत bool nf_nat_mangle_tcp_packet(काष्ठा sk_buff *skb,
					    काष्ठा nf_conn *ct,
					    क्रमागत ip_conntrack_info ctinfo,
					    अचिन्हित पूर्णांक protoff,
					    अचिन्हित पूर्णांक match_offset,
					    अचिन्हित पूर्णांक match_len,
					    स्थिर अक्षर *rep_buffer,
					    अचिन्हित पूर्णांक rep_len)
अणु
	वापस __nf_nat_mangle_tcp_packet(skb, ct, ctinfo, protoff,
					  match_offset, match_len,
					  rep_buffer, rep_len, true);
पूर्ण

bool nf_nat_mangle_udp_packet(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			      क्रमागत ip_conntrack_info ctinfo,
			      अचिन्हित पूर्णांक protoff, अचिन्हित पूर्णांक match_offset,
			      अचिन्हित पूर्णांक match_len, स्थिर अक्षर *rep_buffer,
			      अचिन्हित पूर्णांक rep_len);

/* Setup NAT on this expected conntrack so it follows master, but goes
 * to port ct->master->saved_proto. */
व्योम nf_nat_follow_master(काष्ठा nf_conn *ct, काष्ठा nf_conntrack_expect *this);

#पूर्ण_अगर
