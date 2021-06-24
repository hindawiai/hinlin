<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_DN_FIB_H
#घोषणा _NET_DN_FIB_H

#समावेश <linux/netlink.h>
#समावेश <linux/refcount.h>

बाह्य स्थिर काष्ठा nla_policy rपंचांग_dn_policy[];

काष्ठा dn_fib_res अणु
	काष्ठा fib_rule *r;
	काष्ठा dn_fib_info *fi;
	अचिन्हित अक्षर prefixlen;
	अचिन्हित अक्षर nh_sel;
	अचिन्हित अक्षर type;
	अचिन्हित अक्षर scope;
पूर्ण;

काष्ठा dn_fib_nh अणु
	काष्ठा net_device	*nh_dev;
	अचिन्हित पूर्णांक		nh_flags;
	अचिन्हित अक्षर		nh_scope;
	पूर्णांक			nh_weight;
	पूर्णांक			nh_घातer;
	पूर्णांक			nh_oअगर;
	__le16			nh_gw;
पूर्ण;

काष्ठा dn_fib_info अणु
	काष्ठा dn_fib_info	*fib_next;
	काष्ठा dn_fib_info	*fib_prev;
	पूर्णांक 			fib_treeref;
	refcount_t		fib_clntref;
	पूर्णांक			fib_dead;
	अचिन्हित पूर्णांक		fib_flags;
	पूर्णांक			fib_protocol;
	__le16			fib_prefsrc;
	__u32			fib_priority;
	__u32			fib_metrics[RTAX_MAX];
	पूर्णांक			fib_nhs;
	पूर्णांक			fib_घातer;
	काष्ठा dn_fib_nh	fib_nh[0];
#घोषणा dn_fib_dev		fib_nh[0].nh_dev
पूर्ण;


#घोषणा DN_FIB_RES_RESET(res)	((res).nh_sel = 0)
#घोषणा DN_FIB_RES_NH(res)	((res).fi->fib_nh[(res).nh_sel])

#घोषणा DN_FIB_RES_PREFSRC(res)	((res).fi->fib_prefsrc ? : __dn_fib_res_prefsrc(&res))
#घोषणा DN_FIB_RES_GW(res)	(DN_FIB_RES_NH(res).nh_gw)
#घोषणा DN_FIB_RES_DEV(res)	(DN_FIB_RES_NH(res).nh_dev)
#घोषणा DN_FIB_RES_OIF(res)	(DN_FIB_RES_NH(res).nh_oअगर)

प्रकार काष्ठा अणु
	__le16	datum;
पूर्ण dn_fib_key_t;

प्रकार काष्ठा अणु
	__le16	datum;
पूर्ण dn_fib_hash_t;

प्रकार काष्ठा अणु
	__u16	datum;
पूर्ण dn_fib_idx_t;

काष्ठा dn_fib_node अणु
	काष्ठा dn_fib_node *fn_next;
	काष्ठा dn_fib_info *fn_info;
#घोषणा DN_FIB_INFO(f) ((f)->fn_info)
	dn_fib_key_t	fn_key;
	u8		fn_type;
	u8		fn_scope;
	u8		fn_state;
पूर्ण;


काष्ठा dn_fib_table अणु
	काष्ठा hlist_node hlist;
	u32 n;

	पूर्णांक (*insert)(काष्ठा dn_fib_table *t, काष्ठा rपंचांगsg *r, 
			काष्ठा nlattr *attrs[], काष्ठा nlmsghdr *n,
			काष्ठा netlink_skb_parms *req);
	पूर्णांक (*delete)(काष्ठा dn_fib_table *t, काष्ठा rपंचांगsg *r,
			काष्ठा nlattr *attrs[], काष्ठा nlmsghdr *n,
			काष्ठा netlink_skb_parms *req);
	पूर्णांक (*lookup)(काष्ठा dn_fib_table *t, स्थिर काष्ठा flowidn *fld,
			काष्ठा dn_fib_res *res);
	पूर्णांक (*flush)(काष्ठा dn_fib_table *t);
	पूर्णांक (*dump)(काष्ठा dn_fib_table *t, काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

	अचिन्हित अक्षर data[];
पूर्ण;

#अगर_घोषित CONFIG_DECNET_ROUTER
/*
 * dn_fib.c
 */
व्योम dn_fib_init(व्योम);
व्योम dn_fib_cleanup(व्योम);

पूर्णांक dn_fib_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
काष्ठा dn_fib_info *dn_fib_create_info(स्थिर काष्ठा rपंचांगsg *r,
				       काष्ठा nlattr *attrs[],
				       स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक *errp);
पूर्णांक dn_fib_semantic_match(पूर्णांक type, काष्ठा dn_fib_info *fi,
			  स्थिर काष्ठा flowidn *fld, काष्ठा dn_fib_res *res);
व्योम dn_fib_release_info(काष्ठा dn_fib_info *fi);
व्योम dn_fib_flush(व्योम);
व्योम dn_fib_select_multipath(स्थिर काष्ठा flowidn *fld, काष्ठा dn_fib_res *res);

/*
 * dn_tables.c
 */
काष्ठा dn_fib_table *dn_fib_get_table(u32 n, पूर्णांक creat);
काष्ठा dn_fib_table *dn_fib_empty_table(व्योम);
व्योम dn_fib_table_init(व्योम);
व्योम dn_fib_table_cleanup(व्योम);

/*
 * dn_rules.c
 */
व्योम dn_fib_rules_init(व्योम);
व्योम dn_fib_rules_cleanup(व्योम);
अचिन्हित पूर्णांक dnet_addr_type(__le16 addr);
पूर्णांक dn_fib_lookup(काष्ठा flowidn *fld, काष्ठा dn_fib_res *res);

पूर्णांक dn_fib_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb);

व्योम dn_fib_मुक्त_info(काष्ठा dn_fib_info *fi);

अटल अंतरभूत व्योम dn_fib_info_put(काष्ठा dn_fib_info *fi)
अणु
	अगर (refcount_dec_and_test(&fi->fib_clntref))
		dn_fib_मुक्त_info(fi);
पूर्ण

अटल अंतरभूत व्योम dn_fib_res_put(काष्ठा dn_fib_res *res)
अणु
	अगर (res->fi)
		dn_fib_info_put(res->fi);
	अगर (res->r)
		fib_rule_put(res->r);
पूर्ण

#अन्यथा /* Endnode */

#घोषणा dn_fib_init()  करो अणु पूर्ण जबतक(0)
#घोषणा dn_fib_cleanup() करो अणु पूर्ण जबतक(0)

#घोषणा dn_fib_lookup(fl, res) (-ESRCH)
#घोषणा dn_fib_info_put(fi) करो अणु पूर्ण जबतक(0)
#घोषणा dn_fib_select_multipath(fl, res) करो अणु पूर्ण जबतक(0)
#घोषणा dn_fib_rules_policy(saddr,res,flags) (0)
#घोषणा dn_fib_res_put(res) करो अणु पूर्ण जबतक(0)

#पूर्ण_अगर /* CONFIG_DECNET_ROUTER */

अटल अंतरभूत __le16 dnet_make_mask(पूर्णांक n)
अणु
	अगर (n)
		वापस cpu_to_le16(~((1 << (16 - n)) - 1));
	वापस cpu_to_le16(0);
पूर्ण

#पूर्ण_अगर /* _NET_DN_FIB_H */
