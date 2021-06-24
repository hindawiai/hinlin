<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * connection tracking expectations.
 */

#अगर_अघोषित _NF_CONNTRACK_EXPECT_H
#घोषणा _NF_CONNTRACK_EXPECT_H

#समावेश <linux/refcount.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

बाह्य अचिन्हित पूर्णांक nf_ct_expect_hsize;
बाह्य अचिन्हित पूर्णांक nf_ct_expect_max;
बाह्य काष्ठा hlist_head *nf_ct_expect_hash;

काष्ठा nf_conntrack_expect अणु
	/* Conntrack expectation list member */
	काष्ठा hlist_node lnode;

	/* Hash member */
	काष्ठा hlist_node hnode;

	/* We expect this tuple, with the following mask */
	काष्ठा nf_conntrack_tuple tuple;
	काष्ठा nf_conntrack_tuple_mask mask;

	/* Function to call after setup and insertion */
	व्योम (*expectfn)(काष्ठा nf_conn *new,
			 काष्ठा nf_conntrack_expect *this);

	/* Helper to assign to new connection */
	काष्ठा nf_conntrack_helper *helper;

	/* The conntrack of the master connection */
	काष्ठा nf_conn *master;

	/* Timer function; deletes the expectation. */
	काष्ठा समयr_list समयout;

	/* Usage count. */
	refcount_t use;

	/* Flags */
	अचिन्हित पूर्णांक flags;

	/* Expectation class */
	अचिन्हित पूर्णांक class;

#अगर IS_ENABLED(CONFIG_NF_NAT)
	जोड़ nf_inet_addr saved_addr;
	/* This is the original per-proto part, used to map the
	 * expected connection the way the recipient expects. */
	जोड़ nf_conntrack_man_proto saved_proto;
	/* Direction relative to the master connection. */
	क्रमागत ip_conntrack_dir dir;
#पूर्ण_अगर

	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत काष्ठा net *nf_ct_exp_net(काष्ठा nf_conntrack_expect *exp)
अणु
	वापस nf_ct_net(exp->master);
पूर्ण

#घोषणा NF_CT_EXP_POLICY_NAME_LEN	16

काष्ठा nf_conntrack_expect_policy अणु
	अचिन्हित पूर्णांक	max_expected;
	अचिन्हित पूर्णांक	समयout;
	अक्षर		name[NF_CT_EXP_POLICY_NAME_LEN];
पूर्ण;

#घोषणा NF_CT_EXPECT_CLASS_DEFAULT	0
#घोषणा NF_CT_EXPECT_MAX_CNT		255

/* Allow to reuse expectations with the same tuples from dअगरferent master
 * conntracks.
 */
#घोषणा NF_CT_EXP_F_SKIP_MASTER	0x1

पूर्णांक nf_conntrack_expect_pernet_init(काष्ठा net *net);
व्योम nf_conntrack_expect_pernet_fini(काष्ठा net *net);

पूर्णांक nf_conntrack_expect_init(व्योम);
व्योम nf_conntrack_expect_fini(व्योम);

काष्ठा nf_conntrack_expect *
__nf_ct_expect_find(काष्ठा net *net,
		    स्थिर काष्ठा nf_conntrack_zone *zone,
		    स्थिर काष्ठा nf_conntrack_tuple *tuple);

काष्ठा nf_conntrack_expect *
nf_ct_expect_find_get(काष्ठा net *net,
		      स्थिर काष्ठा nf_conntrack_zone *zone,
		      स्थिर काष्ठा nf_conntrack_tuple *tuple);

काष्ठा nf_conntrack_expect *
nf_ct_find_expectation(काष्ठा net *net,
		       स्थिर काष्ठा nf_conntrack_zone *zone,
		       स्थिर काष्ठा nf_conntrack_tuple *tuple);

व्योम nf_ct_unlink_expect_report(काष्ठा nf_conntrack_expect *exp,
				u32 portid, पूर्णांक report);
अटल अंतरभूत व्योम nf_ct_unlink_expect(काष्ठा nf_conntrack_expect *exp)
अणु
	nf_ct_unlink_expect_report(exp, 0, 0);
पूर्ण

व्योम nf_ct_हटाओ_expectations(काष्ठा nf_conn *ct);
व्योम nf_ct_unexpect_related(काष्ठा nf_conntrack_expect *exp);
bool nf_ct_हटाओ_expect(काष्ठा nf_conntrack_expect *exp);

व्योम nf_ct_expect_iterate_destroy(bool (*iter)(काष्ठा nf_conntrack_expect *e, व्योम *data), व्योम *data);
व्योम nf_ct_expect_iterate_net(काष्ठा net *net,
			      bool (*iter)(काष्ठा nf_conntrack_expect *e, व्योम *data),
                              व्योम *data, u32 portid, पूर्णांक report);

/* Allocate space क्रम an expectation: this is mandatory beक्रमe calling
   nf_ct_expect_related.  You will have to call put afterwards. */
काष्ठा nf_conntrack_expect *nf_ct_expect_alloc(काष्ठा nf_conn *me);
व्योम nf_ct_expect_init(काष्ठा nf_conntrack_expect *, अचिन्हित पूर्णांक, u_पूर्णांक8_t,
		       स्थिर जोड़ nf_inet_addr *,
		       स्थिर जोड़ nf_inet_addr *,
		       u_पूर्णांक8_t, स्थिर __be16 *, स्थिर __be16 *);
व्योम nf_ct_expect_put(काष्ठा nf_conntrack_expect *exp);
पूर्णांक nf_ct_expect_related_report(काष्ठा nf_conntrack_expect *expect,
				u32 portid, पूर्णांक report, अचिन्हित पूर्णांक flags);
अटल अंतरभूत पूर्णांक nf_ct_expect_related(काष्ठा nf_conntrack_expect *expect,
				       अचिन्हित पूर्णांक flags)
अणु
	वापस nf_ct_expect_related_report(expect, 0, 0, flags);
पूर्ण

#पूर्ण_अगर /*_NF_CONNTRACK_EXPECT_H*/

