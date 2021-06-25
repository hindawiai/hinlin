<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions and Declarations क्रम tuple.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- generalize L3 protocol dependent part.
 *
 * Derived from include/linux/netfiter_ipv4/ip_conntrack_tuple.h
 */

#अगर_अघोषित _NF_CONNTRACK_TUPLE_H
#घोषणा _NF_CONNTRACK_TUPLE_H

#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <linux/list_nulls.h>

/* A `tuple' is a काष्ठाure containing the inक्रमmation to uniquely
  identअगरy a connection.  ie. अगर two packets have the same tuple, they
  are in the same connection; अगर not, they are not.

  We भागide the काष्ठाure aदीर्घ "manipulatable" and
  "non-manipulatable" lines, क्रम the benefit of the NAT code.
*/

#घोषणा NF_CT_TUPLE_L3SIZE	ARRAY_SIZE(((जोड़ nf_inet_addr *)शून्य)->all)

/* The manipulable part of the tuple. */
काष्ठा nf_conntrack_man अणु
	जोड़ nf_inet_addr u3;
	जोड़ nf_conntrack_man_proto u;
	/* Layer 3 protocol */
	u_पूर्णांक16_t l3num;
पूर्ण;

/* This contains the inक्रमmation to distinguish a connection. */
काष्ठा nf_conntrack_tuple अणु
	काष्ठा nf_conntrack_man src;

	/* These are the parts of the tuple which are fixed. */
	काष्ठा अणु
		जोड़ nf_inet_addr u3;
		जोड़ अणु
			/* Add other protocols here. */
			__be16 all;

			काष्ठा अणु
				__be16 port;
			पूर्ण tcp;
			काष्ठा अणु
				__be16 port;
			पूर्ण udp;
			काष्ठा अणु
				u_पूर्णांक8_t type, code;
			पूर्ण icmp;
			काष्ठा अणु
				__be16 port;
			पूर्ण dccp;
			काष्ठा अणु
				__be16 port;
			पूर्ण sctp;
			काष्ठा अणु
				__be16 key;
			पूर्ण gre;
		पूर्ण u;

		/* The protocol. */
		u_पूर्णांक8_t protonum;

		/* The direction (क्रम tuplehash) */
		u_पूर्णांक8_t dir;
	पूर्ण dst;
पूर्ण;

काष्ठा nf_conntrack_tuple_mask अणु
	काष्ठा अणु
		जोड़ nf_inet_addr u3;
		जोड़ nf_conntrack_man_proto u;
	पूर्ण src;
पूर्ण;

अटल अंतरभूत व्योम nf_ct_dump_tuple_ip(स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk("tuple %p: %u %pI4:%hu -> %pI4:%hu\n",
	       t, t->dst.protonum,
	       &t->src.u3.ip, ntohs(t->src.u.all),
	       &t->dst.u3.ip, ntohs(t->dst.u.all));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम nf_ct_dump_tuple_ipv6(स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
#अगर_घोषित DEBUG
	prपूर्णांकk("tuple %p: %u %pI6 %hu -> %pI6 %hu\n",
	       t, t->dst.protonum,
	       t->src.u3.all, ntohs(t->src.u.all),
	       t->dst.u3.all, ntohs(t->dst.u.all));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम nf_ct_dump_tuple(स्थिर काष्ठा nf_conntrack_tuple *t)
अणु
	चयन (t->src.l3num) अणु
	हाल AF_INET:
		nf_ct_dump_tuple_ip(t);
		अवरोध;
	हाल AF_INET6:
		nf_ct_dump_tuple_ipv6(t);
		अवरोध;
	पूर्ण
पूर्ण

/* If we're the first tuple, it's the original dir. */
#घोषणा NF_CT_सूचीECTION(h)						\
	((क्रमागत ip_conntrack_dir)(h)->tuple.dst.dir)

/* Connections have two entries in the hash table: one क्रम each way */
काष्ठा nf_conntrack_tuple_hash अणु
	काष्ठा hlist_nulls_node hnnode;
	काष्ठा nf_conntrack_tuple tuple;
पूर्ण;

अटल अंतरभूत bool __nf_ct_tuple_src_equal(स्थिर काष्ठा nf_conntrack_tuple *t1,
					   स्थिर काष्ठा nf_conntrack_tuple *t2)
अणु
	वापस (nf_inet_addr_cmp(&t1->src.u3, &t2->src.u3) &&
		t1->src.u.all == t2->src.u.all &&
		t1->src.l3num == t2->src.l3num);
पूर्ण

अटल अंतरभूत bool __nf_ct_tuple_dst_equal(स्थिर काष्ठा nf_conntrack_tuple *t1,
					   स्थिर काष्ठा nf_conntrack_tuple *t2)
अणु
	वापस (nf_inet_addr_cmp(&t1->dst.u3, &t2->dst.u3) &&
		t1->dst.u.all == t2->dst.u.all &&
		t1->dst.protonum == t2->dst.protonum);
पूर्ण

अटल अंतरभूत bool nf_ct_tuple_equal(स्थिर काष्ठा nf_conntrack_tuple *t1,
				     स्थिर काष्ठा nf_conntrack_tuple *t2)
अणु
	वापस __nf_ct_tuple_src_equal(t1, t2) &&
	       __nf_ct_tuple_dst_equal(t1, t2);
पूर्ण

अटल अंतरभूत bool
nf_ct_tuple_mask_equal(स्थिर काष्ठा nf_conntrack_tuple_mask *m1,
		       स्थिर काष्ठा nf_conntrack_tuple_mask *m2)
अणु
	वापस (nf_inet_addr_cmp(&m1->src.u3, &m2->src.u3) &&
		m1->src.u.all == m2->src.u.all);
पूर्ण

अटल अंतरभूत bool
nf_ct_tuple_src_mask_cmp(स्थिर काष्ठा nf_conntrack_tuple *t1,
			 स्थिर काष्ठा nf_conntrack_tuple *t2,
			 स्थिर काष्ठा nf_conntrack_tuple_mask *mask)
अणु
	पूर्णांक count;

	क्रम (count = 0; count < NF_CT_TUPLE_L3SIZE; count++) अणु
		अगर ((t1->src.u3.all[count] ^ t2->src.u3.all[count]) &
		    mask->src.u3.all[count])
			वापस false;
	पूर्ण

	अगर ((t1->src.u.all ^ t2->src.u.all) & mask->src.u.all)
		वापस false;

	अगर (t1->src.l3num != t2->src.l3num ||
	    t1->dst.protonum != t2->dst.protonum)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool
nf_ct_tuple_mask_cmp(स्थिर काष्ठा nf_conntrack_tuple *t,
		     स्थिर काष्ठा nf_conntrack_tuple *tuple,
		     स्थिर काष्ठा nf_conntrack_tuple_mask *mask)
अणु
	वापस nf_ct_tuple_src_mask_cmp(t, tuple, mask) &&
	       __nf_ct_tuple_dst_equal(t, tuple);
पूर्ण

#पूर्ण_अगर /* _NF_CONNTRACK_TUPLE_H */
