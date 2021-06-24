<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFNETLINK_H
#घोषणा _NFNETLINK_H

#समावेश <linux/netlink.h>
#समावेश <linux/capability.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/netfilter/nfnetlink.h>

काष्ठा nfnl_info अणु
	काष्ठा net		*net;
	काष्ठा sock		*sk;
	स्थिर काष्ठा nlmsghdr	*nlh;
	काष्ठा netlink_ext_ack	*extack;
पूर्ण;

क्रमागत nfnl_callback_type अणु
	NFNL_CB_UNSPEC	= 0,
	NFNL_CB_MUTEX,
	NFNL_CB_RCU,
	NFNL_CB_BATCH,
पूर्ण;

काष्ठा nfnl_callback अणु
	पूर्णांक (*call)(काष्ठा sk_buff *skb, स्थिर काष्ठा nfnl_info *info,
		    स्थिर काष्ठा nlattr * स्थिर cda[]);
	स्थिर काष्ठा nla_policy	*policy;
	क्रमागत nfnl_callback_type	type;
	__u16			attr_count;
पूर्ण;

क्रमागत nfnl_पात_action अणु
	NFNL_ABORT_NONE		= 0,
	NFNL_ABORT_AUTOLOAD,
	NFNL_ABORT_VALIDATE,
पूर्ण;

काष्ठा nfnetlink_subप्रणाली अणु
	स्थिर अक्षर *name;
	__u8 subsys_id;			/* nfnetlink subप्रणाली ID */
	__u8 cb_count;			/* number of callbacks */
	स्थिर काष्ठा nfnl_callback *cb;	/* callback क्रम inभागidual types */
	काष्ठा module *owner;
	पूर्णांक (*commit)(काष्ठा net *net, काष्ठा sk_buff *skb);
	पूर्णांक (*पात)(काष्ठा net *net, काष्ठा sk_buff *skb,
		     क्रमागत nfnl_पात_action action);
	व्योम (*cleanup)(काष्ठा net *net);
	bool (*valid_genid)(काष्ठा net *net, u32 genid);
पूर्ण;

पूर्णांक nfnetlink_subsys_रेजिस्टर(स्थिर काष्ठा nfnetlink_subप्रणाली *n);
पूर्णांक nfnetlink_subsys_unरेजिस्टर(स्थिर काष्ठा nfnetlink_subप्रणाली *n);

पूर्णांक nfnetlink_has_listeners(काष्ठा net *net, अचिन्हित पूर्णांक group);
पूर्णांक nfnetlink_send(काष्ठा sk_buff *skb, काष्ठा net *net, u32 portid,
		   अचिन्हित पूर्णांक group, पूर्णांक echo, gfp_t flags);
पूर्णांक nfnetlink_set_err(काष्ठा net *net, u32 portid, u32 group, पूर्णांक error);
पूर्णांक nfnetlink_unicast(काष्ठा sk_buff *skb, काष्ठा net *net, u32 portid);
व्योम nfnetlink_broadcast(काष्ठा net *net, काष्ठा sk_buff *skb, __u32 portid,
			 __u32 group, gfp_t allocation);

अटल अंतरभूत u16 nfnl_msg_type(u8 subsys, u8 msg_type)
अणु
	वापस subsys << 8 | msg_type;
पूर्ण

अटल अंतरभूत व्योम nfnl_fill_hdr(काष्ठा nlmsghdr *nlh, u8 family, u8 version,
				 __be16 res_id)
अणु
	काष्ठा nfgenmsg *nfmsg;

	nfmsg = nlmsg_data(nlh);
	nfmsg->nfgen_family = family;
	nfmsg->version = version;
	nfmsg->res_id = res_id;
पूर्ण

अटल अंतरभूत काष्ठा nlmsghdr *nfnl_msg_put(काष्ठा sk_buff *skb, u32 portid,
					    u32 seq, पूर्णांक type, पूर्णांक flags,
					    u8 family, u8 version,
					    __be16 res_id)
अणु
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, portid, seq, type, माप(काष्ठा nfgenmsg), flags);
	अगर (!nlh)
		वापस शून्य;

	nfnl_fill_hdr(nlh, family, version, res_id);

	वापस nlh;
पूर्ण

व्योम nfnl_lock(__u8 subsys_id);
व्योम nfnl_unlock(__u8 subsys_id);
#अगर_घोषित CONFIG_PROVE_LOCKING
bool lockdep_nfnl_is_held(__u8 subsys_id);
#अन्यथा
अटल अंतरभूत bool lockdep_nfnl_is_held(__u8 subsys_id)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROVE_LOCKING */

#घोषणा MODULE_ALIAS_NFNL_SUBSYS(subsys) \
	MODULE_ALIAS("nfnetlink-subsys-" __stringअगरy(subsys))

#पूर्ण_अगर	/* _NFNETLINK_H */
