<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_LWTUNNEL_H
#घोषणा __NET_LWTUNNEL_H 1

#समावेश <linux/lwtunnel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/route.h>

#घोषणा LWTUNNEL_HASH_BITS   7
#घोषणा LWTUNNEL_HASH_SIZE   (1 << LWTUNNEL_HASH_BITS)

/* lw tunnel state flags */
#घोषणा LWTUNNEL_STATE_OUTPUT_REसूचीECT	BIT(0)
#घोषणा LWTUNNEL_STATE_INPUT_REसूचीECT	BIT(1)
#घोषणा LWTUNNEL_STATE_XMIT_REसूचीECT	BIT(2)

क्रमागत अणु
	LWTUNNEL_XMIT_DONE,
	LWTUNNEL_XMIT_CONTINUE,
पूर्ण;


काष्ठा lwtunnel_state अणु
	__u16		type;
	__u16		flags;
	__u16		headroom;
	atomic_t	refcnt;
	पूर्णांक		(*orig_output)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक		(*orig_input)(काष्ठा sk_buff *);
	काष्ठा		rcu_head rcu;
	__u8            data[];
पूर्ण;

काष्ठा lwtunnel_encap_ops अणु
	पूर्णांक (*build_state)(काष्ठा net *net, काष्ठा nlattr *encap,
			   अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			   काष्ठा lwtunnel_state **ts,
			   काष्ठा netlink_ext_ack *extack);
	व्योम (*destroy_state)(काष्ठा lwtunnel_state *lws);
	पूर्णांक (*output)(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक (*input)(काष्ठा sk_buff *skb);
	पूर्णांक (*fill_encap)(काष्ठा sk_buff *skb,
			  काष्ठा lwtunnel_state *lwtstate);
	पूर्णांक (*get_encap_size)(काष्ठा lwtunnel_state *lwtstate);
	पूर्णांक (*cmp_encap)(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b);
	पूर्णांक (*xmit)(काष्ठा sk_buff *skb);

	काष्ठा module *owner;
पूर्ण;

#अगर_घोषित CONFIG_LWTUNNEL
व्योम lwtstate_मुक्त(काष्ठा lwtunnel_state *lws);

अटल अंतरभूत काष्ठा lwtunnel_state *
lwtstate_get(काष्ठा lwtunnel_state *lws)
अणु
	अगर (lws)
		atomic_inc(&lws->refcnt);

	वापस lws;
पूर्ण

अटल अंतरभूत व्योम lwtstate_put(काष्ठा lwtunnel_state *lws)
अणु
	अगर (!lws)
		वापस;

	अगर (atomic_dec_and_test(&lws->refcnt))
		lwtstate_मुक्त(lws);
पूर्ण

अटल अंतरभूत bool lwtunnel_output_redirect(काष्ठा lwtunnel_state *lwtstate)
अणु
	अगर (lwtstate && (lwtstate->flags & LWTUNNEL_STATE_OUTPUT_REसूचीECT))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool lwtunnel_input_redirect(काष्ठा lwtunnel_state *lwtstate)
अणु
	अगर (lwtstate && (lwtstate->flags & LWTUNNEL_STATE_INPUT_REसूचीECT))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool lwtunnel_xmit_redirect(काष्ठा lwtunnel_state *lwtstate)
अणु
	अगर (lwtstate && (lwtstate->flags & LWTUNNEL_STATE_XMIT_REसूचीECT))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक lwtunnel_headroom(काष्ठा lwtunnel_state *lwtstate,
					     अचिन्हित पूर्णांक mtu)
अणु
	अगर ((lwtunnel_xmit_redirect(lwtstate) ||
	     lwtunnel_output_redirect(lwtstate)) && lwtstate->headroom < mtu)
		वापस lwtstate->headroom;

	वापस 0;
पूर्ण

पूर्णांक lwtunnel_encap_add_ops(स्थिर काष्ठा lwtunnel_encap_ops *op,
			   अचिन्हित पूर्णांक num);
पूर्णांक lwtunnel_encap_del_ops(स्थिर काष्ठा lwtunnel_encap_ops *op,
			   अचिन्हित पूर्णांक num);
पूर्णांक lwtunnel_valid_encap_type(u16 encap_type,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक lwtunnel_valid_encap_type_attr(काष्ठा nlattr *attr, पूर्णांक len,
				   काष्ठा netlink_ext_ack *extack);
पूर्णांक lwtunnel_build_state(काष्ठा net *net, u16 encap_type,
			 काष्ठा nlattr *encap,
			 अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			 काष्ठा lwtunnel_state **lws,
			 काष्ठा netlink_ext_ack *extack);
पूर्णांक lwtunnel_fill_encap(काष्ठा sk_buff *skb, काष्ठा lwtunnel_state *lwtstate,
			पूर्णांक encap_attr, पूर्णांक encap_type_attr);
पूर्णांक lwtunnel_get_encap_size(काष्ठा lwtunnel_state *lwtstate);
काष्ठा lwtunnel_state *lwtunnel_state_alloc(पूर्णांक hdr_len);
पूर्णांक lwtunnel_cmp_encap(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b);
पूर्णांक lwtunnel_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
पूर्णांक lwtunnel_input(काष्ठा sk_buff *skb);
पूर्णांक lwtunnel_xmit(काष्ठा sk_buff *skb);
पूर्णांक bpf_lwt_push_ip_encap(काष्ठा sk_buff *skb, व्योम *hdr, u32 len,
			  bool ingress);

अटल अंतरभूत व्योम lwtunnel_set_redirect(काष्ठा dst_entry *dst)
अणु
	अगर (lwtunnel_output_redirect(dst->lwtstate)) अणु
		dst->lwtstate->orig_output = dst->output;
		dst->output = lwtunnel_output;
	पूर्ण
	अगर (lwtunnel_input_redirect(dst->lwtstate)) अणु
		dst->lwtstate->orig_input = dst->input;
		dst->input = lwtunnel_input;
	पूर्ण
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम lwtstate_मुक्त(काष्ठा lwtunnel_state *lws)
अणु
पूर्ण

अटल अंतरभूत काष्ठा lwtunnel_state *
lwtstate_get(काष्ठा lwtunnel_state *lws)
अणु
	वापस lws;
पूर्ण

अटल अंतरभूत व्योम lwtstate_put(काष्ठा lwtunnel_state *lws)
अणु
पूर्ण

अटल अंतरभूत bool lwtunnel_output_redirect(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool lwtunnel_input_redirect(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool lwtunnel_xmit_redirect(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम lwtunnel_set_redirect(काष्ठा dst_entry *dst)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक lwtunnel_headroom(काष्ठा lwtunnel_state *lwtstate,
					     अचिन्हित पूर्णांक mtu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_encap_add_ops(स्थिर काष्ठा lwtunnel_encap_ops *op,
					 अचिन्हित पूर्णांक num)
अणु
	वापस -EOPNOTSUPP;

पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_encap_del_ops(स्थिर काष्ठा lwtunnel_encap_ops *op,
					 अचिन्हित पूर्णांक num)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_valid_encap_type(u16 encap_type,
					    काष्ठा netlink_ext_ack *extack)
अणु
	NL_SET_ERR_MSG(extack, "CONFIG_LWTUNNEL is not enabled in this kernel");
	वापस -EOPNOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक lwtunnel_valid_encap_type_attr(काष्ठा nlattr *attr, पूर्णांक len,
						 काष्ठा netlink_ext_ack *extack)
अणु
	/* वापस 0 since we are not walking attr looking क्रम
	 * RTA_ENCAP_TYPE attribute on nexthops.
	 */
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_build_state(काष्ठा net *net, u16 encap_type,
				       काष्ठा nlattr *encap,
				       अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
				       काष्ठा lwtunnel_state **lws,
				       काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_fill_encap(काष्ठा sk_buff *skb,
				      काष्ठा lwtunnel_state *lwtstate,
				      पूर्णांक encap_attr, पूर्णांक encap_type_attr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_get_encap_size(काष्ठा lwtunnel_state *lwtstate)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा lwtunnel_state *lwtunnel_state_alloc(पूर्णांक hdr_len)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_cmp_encap(काष्ठा lwtunnel_state *a,
				     काष्ठा lwtunnel_state *b)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_input(काष्ठा sk_buff *skb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक lwtunnel_xmit(काष्ठा sk_buff *skb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर /* CONFIG_LWTUNNEL */

#घोषणा MODULE_ALIAS_RTNL_LWT(encap_type) MODULE_ALIAS("rtnl-lwt-" __stringअगरy(encap_type))

#पूर्ण_अगर /* __NET_LWTUNNEL_H */
