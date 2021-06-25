<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CONNTRACK_PROTO_GRE_H
#घोषणा _CONNTRACK_PROTO_GRE_H
#समावेश <यंत्र/byteorder.h>
#समावेश <net/gre.h>
#समावेश <net/pptp.h>

काष्ठा nf_ct_gre अणु
	अचिन्हित पूर्णांक stream_समयout;
	अचिन्हित पूर्णांक समयout;
पूर्ण;

#समावेश <net/netfilter/nf_conntrack_tuple.h>

काष्ठा nf_conn;

/* काष्ठाure क्रम original <-> reply keymap */
काष्ठा nf_ct_gre_keymap अणु
	काष्ठा list_head list;
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा rcu_head rcu;
पूर्ण;

/* add new tuple->key_reply pair to keymap */
पूर्णांक nf_ct_gre_keymap_add(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_dir dir,
			 काष्ठा nf_conntrack_tuple *t);

व्योम nf_ct_gre_keymap_flush(काष्ठा net *net);
/* delete keymap entries */
व्योम nf_ct_gre_keymap_destroy(काष्ठा nf_conn *ct);

bool gre_pkt_to_tuple(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक dataoff,
		      काष्ठा net *net, काष्ठा nf_conntrack_tuple *tuple);
#पूर्ण_अगर /* _CONNTRACK_PROTO_GRE_H */
