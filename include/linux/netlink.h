<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NETLINK_H
#घोषणा __LINUX_NETLINK_H


#समावेश <linux/capability.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/export.h>
#समावेश <net/scm.h>
#समावेश <uapi/linux/netlink.h>

काष्ठा net;

व्योम करो_trace_netlink_extack(स्थिर अक्षर *msg);

अटल अंतरभूत काष्ठा nlmsghdr *nlmsg_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा nlmsghdr *)skb->data;
पूर्ण

क्रमागत netlink_skb_flags अणु
	NETLINK_SKB_DST		= 0x8,	/* Dst set in sendto or sendmsg */
पूर्ण;

काष्ठा netlink_skb_parms अणु
	काष्ठा scm_creds	creds;		/* Skb credentials	*/
	__u32			portid;
	__u32			dst_group;
	__u32			flags;
	काष्ठा sock		*sk;
	bool			nsid_is_set;
	पूर्णांक			nsid;
पूर्ण;

#घोषणा NETLINK_CB(skb)		(*(काष्ठा netlink_skb_parms*)&((skb)->cb))
#घोषणा NETLINK_CREDS(skb)	(&NETLINK_CB((skb)).creds)


व्योम netlink_table_grab(व्योम);
व्योम netlink_table_ungrab(व्योम);

#घोषणा NL_CFG_F_NONROOT_RECV	(1 << 0)
#घोषणा NL_CFG_F_NONROOT_SEND	(1 << 1)

/* optional Netlink kernel configuration parameters */
काष्ठा netlink_kernel_cfg अणु
	अचिन्हित पूर्णांक	groups;
	अचिन्हित पूर्णांक	flags;
	व्योम		(*input)(काष्ठा sk_buff *skb);
	काष्ठा mutex	*cb_mutex;
	पूर्णांक		(*bind)(काष्ठा net *net, पूर्णांक group);
	व्योम		(*unbind)(काष्ठा net *net, पूर्णांक group);
	bool		(*compare)(काष्ठा net *net, काष्ठा sock *sk);
पूर्ण;

काष्ठा sock *__netlink_kernel_create(काष्ठा net *net, पूर्णांक unit,
					    काष्ठा module *module,
					    काष्ठा netlink_kernel_cfg *cfg);
अटल अंतरभूत काष्ठा sock *
netlink_kernel_create(काष्ठा net *net, पूर्णांक unit, काष्ठा netlink_kernel_cfg *cfg)
अणु
	वापस __netlink_kernel_create(net, unit, THIS_MODULE, cfg);
पूर्ण

/* this can be increased when necessary - करोn't expose to userland */
#घोषणा NETLINK_MAX_COOKIE_LEN	20

/**
 * काष्ठा netlink_ext_ack - netlink extended ACK report काष्ठा
 * @_msg: message string to report - करोn't access directly, use
 *	%NL_SET_ERR_MSG
 * @bad_attr: attribute with error
 * @policy: policy क्रम a bad attribute
 * @cookie: cookie data to वापस to userspace (क्रम success)
 * @cookie_len: actual cookie data length
 */
काष्ठा netlink_ext_ack अणु
	स्थिर अक्षर *_msg;
	स्थिर काष्ठा nlattr *bad_attr;
	स्थिर काष्ठा nla_policy *policy;
	u8 cookie[NETLINK_MAX_COOKIE_LEN];
	u8 cookie_len;
पूर्ण;

/* Always use this macro, this allows later putting the
 * message पूर्णांकo a separate section or such क्रम things
 * like translation or listing all possible messages.
 * Currently string क्रमmatting is not supported (due
 * to the lack of an output buffer.)
 */
#घोषणा NL_SET_ERR_MSG(extack, msg) करो अणु		\
	अटल स्थिर अक्षर __msg[] = msg;		\
	काष्ठा netlink_ext_ack *__extack = (extack);	\
							\
	करो_trace_netlink_extack(__msg);			\
							\
	अगर (__extack)					\
		__extack->_msg = __msg;			\
पूर्ण जबतक (0)

#घोषणा NL_SET_ERR_MSG_MOD(extack, msg)			\
	NL_SET_ERR_MSG((extack), KBUILD_MODNAME ": " msg)

#घोषणा NL_SET_BAD_ATTR_POLICY(extack, attr, pol) करो अणु	\
	अगर ((extack)) अणु					\
		(extack)->bad_attr = (attr);		\
		(extack)->policy = (pol);		\
	पूर्ण						\
पूर्ण जबतक (0)

#घोषणा NL_SET_BAD_ATTR(extack, attr) NL_SET_BAD_ATTR_POLICY(extack, attr, शून्य)

#घोषणा NL_SET_ERR_MSG_ATTR_POL(extack, attr, pol, msg) करो अणु	\
	अटल स्थिर अक्षर __msg[] = msg;			\
	काष्ठा netlink_ext_ack *__extack = (extack);		\
								\
	करो_trace_netlink_extack(__msg);				\
								\
	अगर (__extack) अणु						\
		__extack->_msg = __msg;				\
		__extack->bad_attr = (attr);			\
		__extack->policy = (pol);			\
	पूर्ण							\
पूर्ण जबतक (0)

#घोषणा NL_SET_ERR_MSG_ATTR(extack, attr, msg)		\
	NL_SET_ERR_MSG_ATTR_POL(extack, attr, शून्य, msg)

अटल अंतरभूत व्योम nl_set_extack_cookie_u64(काष्ठा netlink_ext_ack *extack,
					    u64 cookie)
अणु
	अगर (!extack)
		वापस;
	स_नकल(extack->cookie, &cookie, माप(cookie));
	extack->cookie_len = माप(cookie);
पूर्ण

अटल अंतरभूत व्योम nl_set_extack_cookie_u32(काष्ठा netlink_ext_ack *extack,
					    u32 cookie)
अणु
	अगर (!extack)
		वापस;
	स_नकल(extack->cookie, &cookie, माप(cookie));
	extack->cookie_len = माप(cookie);
पूर्ण

व्योम netlink_kernel_release(काष्ठा sock *sk);
पूर्णांक __netlink_change_ngroups(काष्ठा sock *sk, अचिन्हित पूर्णांक groups);
पूर्णांक netlink_change_ngroups(काष्ठा sock *sk, अचिन्हित पूर्णांक groups);
व्योम __netlink_clear_multicast_users(काष्ठा sock *sk, अचिन्हित पूर्णांक group);
व्योम netlink_ack(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh, पूर्णांक err,
		 स्थिर काष्ठा netlink_ext_ack *extack);
पूर्णांक netlink_has_listeners(काष्ठा sock *sk, अचिन्हित पूर्णांक group);
bool netlink_strict_get_check(काष्ठा sk_buff *skb);

पूर्णांक netlink_unicast(काष्ठा sock *ssk, काष्ठा sk_buff *skb, __u32 portid, पूर्णांक nonblock);
पूर्णांक netlink_broadcast(काष्ठा sock *ssk, काष्ठा sk_buff *skb, __u32 portid,
		      __u32 group, gfp_t allocation);
पूर्णांक netlink_broadcast_filtered(काष्ठा sock *ssk, काष्ठा sk_buff *skb,
			       __u32 portid, __u32 group, gfp_t allocation,
			       पूर्णांक (*filter)(काष्ठा sock *dsk, काष्ठा sk_buff *skb, व्योम *data),
			       व्योम *filter_data);
पूर्णांक netlink_set_err(काष्ठा sock *ssk, __u32 portid, __u32 group, पूर्णांक code);
पूर्णांक netlink_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक netlink_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);

/* finegrained unicast helpers: */
काष्ठा sock *netlink_माला_लोockbyfilp(काष्ठा file *filp);
पूर्णांक netlink_attachskb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		      दीर्घ *समयo, काष्ठा sock *ssk);
व्योम netlink_detachskb(काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक netlink_sendskb(काष्ठा sock *sk, काष्ठा sk_buff *skb);

अटल अंतरभूत काष्ठा sk_buff *
netlink_skb_clone(काष्ठा sk_buff *skb, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff *nskb;

	nskb = skb_clone(skb, gfp_mask);
	अगर (!nskb)
		वापस शून्य;

	/* This is a large skb, set deकाष्ठाor callback to release head */
	अगर (is_vदो_स्मृति_addr(skb->head))
		nskb->deकाष्ठाor = skb->deकाष्ठाor;

	वापस nskb;
पूर्ण

/*
 *	skb should fit one page. This choice is good क्रम headerless दो_स्मृति.
 *	But we should limit to 8K so that userspace करोes not have to
 *	use enormous buffer sizes on recvmsg() calls just to aव्योम
 *	MSG_TRUNC when PAGE_SIZE is very large.
 */
#अगर PAGE_SIZE < 8192UL
#घोषणा NLMSG_GOODSIZE	SKB_WITH_OVERHEAD(PAGE_SIZE)
#अन्यथा
#घोषणा NLMSG_GOODSIZE	SKB_WITH_OVERHEAD(8192UL)
#पूर्ण_अगर

#घोषणा NLMSG_DEFAULT_SIZE (NLMSG_GOODSIZE - NLMSG_HDRLEN)


काष्ठा netlink_callback अणु
	काष्ठा sk_buff		*skb;
	स्थिर काष्ठा nlmsghdr	*nlh;
	पूर्णांक			(*dump)(काष्ठा sk_buff * skb,
					काष्ठा netlink_callback *cb);
	पूर्णांक			(*करोne)(काष्ठा netlink_callback *cb);
	व्योम			*data;
	/* the module that dump function beदीर्घ to */
	काष्ठा module		*module;
	काष्ठा netlink_ext_ack	*extack;
	u16			family;
	u16			answer_flags;
	u32			min_dump_alloc;
	अचिन्हित पूर्णांक		prev_seq, seq;
	bool			strict_check;
	जोड़ अणु
		u8		ctx[48];

		/* args is deprecated. Cast a काष्ठा over ctx instead
		 * क्रम proper type safety.
		 */
		दीर्घ		args[6];
	पूर्ण;
पूर्ण;

काष्ठा netlink_notअगरy अणु
	काष्ठा net *net;
	u32 portid;
	पूर्णांक protocol;
पूर्ण;

काष्ठा nlmsghdr *
__nlmsg_put(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक type, पूर्णांक len, पूर्णांक flags);

काष्ठा netlink_dump_control अणु
	पूर्णांक (*start)(काष्ठा netlink_callback *);
	पूर्णांक (*dump)(काष्ठा sk_buff *skb, काष्ठा netlink_callback *);
	पूर्णांक (*करोne)(काष्ठा netlink_callback *);
	व्योम *data;
	काष्ठा module *module;
	u32 min_dump_alloc;
पूर्ण;

पूर्णांक __netlink_dump_start(काष्ठा sock *ssk, काष्ठा sk_buff *skb,
				स्थिर काष्ठा nlmsghdr *nlh,
				काष्ठा netlink_dump_control *control);
अटल अंतरभूत पूर्णांक netlink_dump_start(काष्ठा sock *ssk, काष्ठा sk_buff *skb,
				     स्थिर काष्ठा nlmsghdr *nlh,
				     काष्ठा netlink_dump_control *control)
अणु
	अगर (!control->module)
		control->module = THIS_MODULE;

	वापस __netlink_dump_start(ssk, skb, nlh, control);
पूर्ण

काष्ठा netlink_tap अणु
	काष्ठा net_device *dev;
	काष्ठा module *module;
	काष्ठा list_head list;
पूर्ण;

पूर्णांक netlink_add_tap(काष्ठा netlink_tap *nt);
पूर्णांक netlink_हटाओ_tap(काष्ठा netlink_tap *nt);

bool __netlink_ns_capable(स्थिर काष्ठा netlink_skb_parms *nsp,
			  काष्ठा user_namespace *ns, पूर्णांक cap);
bool netlink_ns_capable(स्थिर काष्ठा sk_buff *skb,
			काष्ठा user_namespace *ns, पूर्णांक cap);
bool netlink_capable(स्थिर काष्ठा sk_buff *skb, पूर्णांक cap);
bool netlink_net_capable(स्थिर काष्ठा sk_buff *skb, पूर्णांक cap);

#पूर्ण_अगर	/* __LINUX_NETLINK_H */
