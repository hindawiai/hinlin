<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SELinux support क्रम the XFRM LSM hooks
 *
 * Author : Trent Jaeger, <jaegert@us.ibm.com>
 * Updated : Venkat Yekkirala, <vyekkirala@TrustedCS.com>
 */
#अगर_अघोषित _SELINUX_XFRM_H_
#घोषणा _SELINUX_XFRM_H_

#समावेश <net/flow.h>

पूर्णांक selinux_xfrm_policy_alloc(काष्ठा xfrm_sec_ctx **ctxp,
			      काष्ठा xfrm_user_sec_ctx *uctx,
			      gfp_t gfp);
पूर्णांक selinux_xfrm_policy_clone(काष्ठा xfrm_sec_ctx *old_ctx,
			      काष्ठा xfrm_sec_ctx **new_ctxp);
व्योम selinux_xfrm_policy_मुक्त(काष्ठा xfrm_sec_ctx *ctx);
पूर्णांक selinux_xfrm_policy_delete(काष्ठा xfrm_sec_ctx *ctx);
पूर्णांक selinux_xfrm_state_alloc(काष्ठा xfrm_state *x,
			     काष्ठा xfrm_user_sec_ctx *uctx);
पूर्णांक selinux_xfrm_state_alloc_acquire(काष्ठा xfrm_state *x,
				     काष्ठा xfrm_sec_ctx *polsec, u32 secid);
व्योम selinux_xfrm_state_मुक्त(काष्ठा xfrm_state *x);
पूर्णांक selinux_xfrm_state_delete(काष्ठा xfrm_state *x);
पूर्णांक selinux_xfrm_policy_lookup(काष्ठा xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir);
पूर्णांक selinux_xfrm_state_pol_flow_match(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_policy *xp,
				      स्थिर काष्ठा flowi_common *flic);

#अगर_घोषित CONFIG_SECURITY_NETWORK_XFRM
बाह्य atomic_t selinux_xfrm_refcount;

अटल अंतरभूत पूर्णांक selinux_xfrm_enabled(व्योम)
अणु
	वापस (atomic_पढ़ो(&selinux_xfrm_refcount) > 0);
पूर्ण

पूर्णांक selinux_xfrm_sock_rcv_skb(u32 sk_sid, काष्ठा sk_buff *skb,
			      काष्ठा common_audit_data *ad);
पूर्णांक selinux_xfrm_postroute_last(u32 sk_sid, काष्ठा sk_buff *skb,
				काष्ठा common_audit_data *ad, u8 proto);
पूर्णांक selinux_xfrm_decode_session(काष्ठा sk_buff *skb, u32 *sid, पूर्णांक ckall);
पूर्णांक selinux_xfrm_skb_sid(काष्ठा sk_buff *skb, u32 *sid);

अटल अंतरभूत व्योम selinux_xfrm_notअगरy_policyload(व्योम)
अणु
	काष्ठा net *net;

	करोwn_पढ़ो(&net_rwsem);
	क्रम_each_net(net)
		rt_genid_bump_all(net);
	up_पढ़ो(&net_rwsem);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक selinux_xfrm_enabled(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक selinux_xfrm_sock_rcv_skb(u32 sk_sid, काष्ठा sk_buff *skb,
					    काष्ठा common_audit_data *ad)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक selinux_xfrm_postroute_last(u32 sk_sid, काष्ठा sk_buff *skb,
					      काष्ठा common_audit_data *ad,
					      u8 proto)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक selinux_xfrm_decode_session(काष्ठा sk_buff *skb, u32 *sid,
					      पूर्णांक ckall)
अणु
	*sid = SECSID_शून्य;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम selinux_xfrm_notअगरy_policyload(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक selinux_xfrm_skb_sid(काष्ठा sk_buff *skb, u32 *sid)
अणु
	*sid = SECSID_शून्य;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _SELINUX_XFRM_H_ */
