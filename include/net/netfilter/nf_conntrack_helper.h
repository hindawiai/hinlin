<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * connection tracking helpers.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- generalize L3 protocol dependent part.
 *
 * Derived from include/linux/netfiter_ipv4/ip_conntrack_helper.h
 */

#अगर_अघोषित _NF_CONNTRACK_HELPER_H
#घोषणा _NF_CONNTRACK_HELPER_H
#समावेश <linux/refcount.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>

#घोषणा NF_NAT_HELPER_PREFIX		"ip_nat_"
#घोषणा NF_NAT_HELPER_NAME(name)	NF_NAT_HELPER_PREFIX name
#घोषणा MODULE_ALIAS_NF_NAT_HELPER(name) \
	MODULE_ALIAS(NF_NAT_HELPER_NAME(name))

काष्ठा module;

क्रमागत nf_ct_helper_flags अणु
	NF_CT_HELPER_F_USERSPACE	= (1 << 0),
	NF_CT_HELPER_F_CONFIGURED	= (1 << 1),
पूर्ण;

#घोषणा NF_CT_HELPER_NAME_LEN	16

काष्ठा nf_conntrack_helper अणु
	काष्ठा hlist_node hnode;	/* Internal use. */

	अक्षर name[NF_CT_HELPER_NAME_LEN]; /* name of the module */
	refcount_t refcnt;
	काष्ठा module *me;		/* poपूर्णांकer to self */
	स्थिर काष्ठा nf_conntrack_expect_policy *expect_policy;

	/* Tuple of things we will help (compared against server response) */
	काष्ठा nf_conntrack_tuple tuple;

	/* Function to call when data passes; वापस verdict, or -1 to
           invalidate. */
	पूर्णांक (*help)(काष्ठा sk_buff *skb,
		    अचिन्हित पूर्णांक protoff,
		    काष्ठा nf_conn *ct,
		    क्रमागत ip_conntrack_info conntrackinfo);

	व्योम (*destroy)(काष्ठा nf_conn *ct);

	पूर्णांक (*from_nlattr)(काष्ठा nlattr *attr, काष्ठा nf_conn *ct);
	पूर्णांक (*to_nlattr)(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct);
	अचिन्हित पूर्णांक expect_class_max;

	अचिन्हित पूर्णांक flags;

	/* For user-space helpers: */
	अचिन्हित पूर्णांक queue_num;
	/* length of userspace निजी data stored in nf_conn_help->data */
	u16 data_len;
	/* name of NAT helper module */
	अक्षर nat_mod_name[NF_CT_HELPER_NAME_LEN];
पूर्ण;

/* Must be kept in sync with the classes defined by helpers */
#घोषणा NF_CT_MAX_EXPECT_CLASSES	4

/* nf_conn feature क्रम connections that have a helper */
काष्ठा nf_conn_help अणु
	/* Helper. अगर any */
	काष्ठा nf_conntrack_helper __rcu *helper;

	काष्ठा hlist_head expectations;

	/* Current number of expected connections */
	u8 expecting[NF_CT_MAX_EXPECT_CLASSES];

	/* निजी helper inक्रमmation. */
	अक्षर data[32] __aligned(8);
पूर्ण;

#घोषणा NF_CT_HELPER_BUILD_BUG_ON(काष्ठाsize) \
	BUILD_BUG_ON((काष्ठाsize) > माप_field(काष्ठा nf_conn_help, data))

काष्ठा nf_conntrack_helper *__nf_conntrack_helper_find(स्थिर अक्षर *name,
						       u16 l3num, u8 protonum);

काष्ठा nf_conntrack_helper *nf_conntrack_helper_try_module_get(स्थिर अक्षर *name,
							       u16 l3num,
							       u8 protonum);
व्योम nf_conntrack_helper_put(काष्ठा nf_conntrack_helper *helper);

व्योम nf_ct_helper_init(काष्ठा nf_conntrack_helper *helper,
		       u16 l3num, u16 protonum, स्थिर अक्षर *name,
		       u16 शेष_port, u16 spec_port, u32 id,
		       स्थिर काष्ठा nf_conntrack_expect_policy *exp_pol,
		       u32 expect_class_max,
		       पूर्णांक (*help)(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				   काष्ठा nf_conn *ct,
				   क्रमागत ip_conntrack_info ctinfo),
		       पूर्णांक (*from_nlattr)(काष्ठा nlattr *attr,
					  काष्ठा nf_conn *ct),
		       काष्ठा module *module);

पूर्णांक nf_conntrack_helper_रेजिस्टर(काष्ठा nf_conntrack_helper *);
व्योम nf_conntrack_helper_unरेजिस्टर(काष्ठा nf_conntrack_helper *);

पूर्णांक nf_conntrack_helpers_रेजिस्टर(काष्ठा nf_conntrack_helper *, अचिन्हित पूर्णांक);
व्योम nf_conntrack_helpers_unरेजिस्टर(काष्ठा nf_conntrack_helper *,
				     अचिन्हित पूर्णांक);

काष्ठा nf_conn_help *nf_ct_helper_ext_add(काष्ठा nf_conn *ct, gfp_t gfp);

पूर्णांक __nf_ct_try_assign_helper(काष्ठा nf_conn *ct, काष्ठा nf_conn *पंचांगpl,
			      gfp_t flags);

व्योम nf_ct_helper_destroy(काष्ठा nf_conn *ct);

अटल अंतरभूत काष्ठा nf_conn_help *nfct_help(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस nf_ct_ext_find(ct, NF_CT_EXT_HELPER);
पूर्ण

अटल अंतरभूत व्योम *nfct_help_data(स्थिर काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_conn_help *help;

	help = nf_ct_ext_find(ct, NF_CT_EXT_HELPER);

	वापस (व्योम *)help->data;
पूर्ण

व्योम nf_conntrack_helper_pernet_init(काष्ठा net *net);

पूर्णांक nf_conntrack_helper_init(व्योम);
व्योम nf_conntrack_helper_fini(व्योम);

पूर्णांक nf_conntrack_broadcast_help(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
				क्रमागत ip_conntrack_info ctinfo,
				अचिन्हित पूर्णांक समयout);

काष्ठा nf_ct_helper_expectfn अणु
	काष्ठा list_head head;
	स्थिर अक्षर *name;
	व्योम (*expectfn)(काष्ठा nf_conn *ct, काष्ठा nf_conntrack_expect *exp);
पूर्ण;

__म_लिखो(3,4)
व्योम nf_ct_helper_log(काष्ठा sk_buff *skb, स्थिर काष्ठा nf_conn *ct,
		      स्थिर अक्षर *fmt, ...);

व्योम nf_ct_helper_expectfn_रेजिस्टर(काष्ठा nf_ct_helper_expectfn *n);
व्योम nf_ct_helper_expectfn_unरेजिस्टर(काष्ठा nf_ct_helper_expectfn *n);
काष्ठा nf_ct_helper_expectfn *
nf_ct_helper_expectfn_find_by_name(स्थिर अक्षर *name);
काष्ठा nf_ct_helper_expectfn *
nf_ct_helper_expectfn_find_by_symbol(स्थिर व्योम *symbol);

बाह्य काष्ठा hlist_head *nf_ct_helper_hash;
बाह्य अचिन्हित पूर्णांक nf_ct_helper_hsize;

काष्ठा nf_conntrack_nat_helper अणु
	काष्ठा list_head list;
	अक्षर mod_name[NF_CT_HELPER_NAME_LEN];	/* module name */
	काष्ठा module *module;			/* poपूर्णांकer to self */
पूर्ण;

#घोषणा NF_CT_NAT_HELPER_INIT(name) \
	अणु \
	.mod_name = NF_NAT_HELPER_NAME(name), \
	.module = THIS_MODULE \
	पूर्ण

व्योम nf_nat_helper_रेजिस्टर(काष्ठा nf_conntrack_nat_helper *nat);
व्योम nf_nat_helper_unरेजिस्टर(काष्ठा nf_conntrack_nat_helper *nat);
पूर्णांक nf_nat_helper_try_module_get(स्थिर अक्षर *name, u16 l3num,
				 u8 protonum);
व्योम nf_nat_helper_put(काष्ठा nf_conntrack_helper *helper);
#पूर्ण_अगर /*_NF_CONNTRACK_HELPER_H*/
