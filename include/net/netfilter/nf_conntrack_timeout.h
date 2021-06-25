<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NF_CONNTRACK_TIMEOUT_H
#घोषणा _NF_CONNTRACK_TIMEOUT_H

#समावेश <net/net_namespace.h>
#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_conntrack_tuple_common.h>
#समावेश <linux/refcount.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_extend.h>

#घोषणा CTNL_TIMEOUT_NAME_MAX	32

काष्ठा nf_ct_समयout अणु
	__u16			l3num;
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	अक्षर			data[];
पूर्ण;

काष्ठा ctnl_समयout अणु
	काष्ठा list_head	head;
	काष्ठा rcu_head		rcu_head;
	refcount_t		refcnt;
	अक्षर			name[CTNL_TIMEOUT_NAME_MAX];
	काष्ठा nf_ct_समयout	समयout;
पूर्ण;

काष्ठा nf_conn_समयout अणु
	काष्ठा nf_ct_समयout __rcu *समयout;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक *
nf_ct_समयout_data(स्थिर काष्ठा nf_conn_समयout *t)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	काष्ठा nf_ct_समयout *समयout;

	समयout = rcu_dereference(t->समयout);
	अगर (समयout == शून्य)
		वापस शून्य;

	वापस (अचिन्हित पूर्णांक *)समयout->data;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत
काष्ठा nf_conn_समयout *nf_ct_समयout_find(स्थिर काष्ठा nf_conn *ct)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	वापस nf_ct_ext_find(ct, NF_CT_EXT_TIMEOUT);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत
काष्ठा nf_conn_समयout *nf_ct_समयout_ext_add(काष्ठा nf_conn *ct,
					      काष्ठा nf_ct_समयout *समयout,
					      gfp_t gfp)
अणु
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	काष्ठा nf_conn_समयout *समयout_ext;

	समयout_ext = nf_ct_ext_add(ct, NF_CT_EXT_TIMEOUT, gfp);
	अगर (समयout_ext == शून्य)
		वापस शून्य;

	rcu_assign_poपूर्णांकer(समयout_ext->समयout, समयout);

	वापस समयout_ext;
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक *nf_ct_समयout_lookup(स्थिर काष्ठा nf_conn *ct)
अणु
	अचिन्हित पूर्णांक *समयouts = शून्य;
#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
	काष्ठा nf_conn_समयout *समयout_ext;

	समयout_ext = nf_ct_समयout_find(ct);
	अगर (समयout_ext)
		समयouts = nf_ct_समयout_data(समयout_ext);
#पूर्ण_अगर
	वापस समयouts;
पूर्ण

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
पूर्णांक nf_conntrack_समयout_init(व्योम);
व्योम nf_conntrack_समयout_fini(व्योम);
व्योम nf_ct_unसमयout(काष्ठा net *net, काष्ठा nf_ct_समयout *समयout);
पूर्णांक nf_ct_set_समयout(काष्ठा net *net, काष्ठा nf_conn *ct, u8 l3num, u8 l4num,
		      स्थिर अक्षर *समयout_name);
व्योम nf_ct_destroy_समयout(काष्ठा nf_conn *ct);
#अन्यथा
अटल अंतरभूत पूर्णांक nf_conntrack_समयout_init(व्योम)
अणु
        वापस 0;
पूर्ण

अटल अंतरभूत व्योम nf_conntrack_समयout_fini(व्योम)
अणु
        वापस;
पूर्ण

अटल अंतरभूत पूर्णांक nf_ct_set_समयout(काष्ठा net *net, काष्ठा nf_conn *ct,
				    u8 l3num, u8 l4num,
				    स्थिर अक्षर *समयout_name)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम nf_ct_destroy_समयout(काष्ठा nf_conn *ct)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_CONNTRACK_TIMEOUT */

#अगर_घोषित CONFIG_NF_CONNTRACK_TIMEOUT
बाह्य काष्ठा nf_ct_समयout *(*nf_ct_समयout_find_get_hook)(काष्ठा net *net, स्थिर अक्षर *name);
बाह्य व्योम (*nf_ct_समयout_put_hook)(काष्ठा nf_ct_समयout *समयout);
#पूर्ण_अगर

#पूर्ण_अगर /* _NF_CONNTRACK_TIMEOUT_H */
