<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  NSA Security-Enhanced Linux (SELinux) security module
 *
 *  This file contains the SELinux XFRM hook function implementations.
 *
 *  Authors:  Serge Hallyn <sergeh@us.ibm.com>
 *	      Trent Jaeger <jaegert@us.ibm.com>
 *
 *  Updated: Venkat Yekkirala <vyekkirala@TrustedCS.com>
 *
 *           Granular IPSec Associations क्रम use in MLS environments.
 *
 *  Copyright (C) 2005 International Business Machines Corporation
 *  Copyright (C) 2006 Trusted Computer Solutions, Inc.
 */

/*
 * USAGE:
 * NOTES:
 *   1. Make sure to enable the following options in your kernel config:
 *	CONFIG_SECURITY=y
 *	CONFIG_SECURITY_NETWORK=y
 *	CONFIG_SECURITY_NETWORK_XFRM=y
 *	CONFIG_SECURITY_SELINUX=m/y
 * ISSUES:
 *   1. Caching packets, so they are not dropped during negotiation
 *   2. Emulating a reasonable SO_PEERSEC across machines
 *   3. Testing addition of sk_policy's with security context via setsockopt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/security.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/xfrm.h>
#समावेश <net/xfrm.h>
#समावेश <net/checksum.h>
#समावेश <net/udp.h>
#समावेश <linux/atomic.h>

#समावेश "avc.h"
#समावेश "objsec.h"
#समावेश "xfrm.h"

/* Labeled XFRM instance counter */
atomic_t selinux_xfrm_refcount __पढ़ो_mostly = ATOMIC_INIT(0);

/*
 * Returns true अगर the context is an LSM/SELinux context.
 */
अटल अंतरभूत पूर्णांक selinux_authorizable_ctx(काष्ठा xfrm_sec_ctx *ctx)
अणु
	वापस (ctx &&
		(ctx->ctx_करोi == XFRM_SC_DOI_LSM) &&
		(ctx->ctx_alg == XFRM_SC_ALG_SELINUX));
पूर्ण

/*
 * Returns true अगर the xfrm contains a security blob क्रम SELinux.
 */
अटल अंतरभूत पूर्णांक selinux_authorizable_xfrm(काष्ठा xfrm_state *x)
अणु
	वापस selinux_authorizable_ctx(x->security);
पूर्ण

/*
 * Allocates a xfrm_sec_state and populates it using the supplied security
 * xfrm_user_sec_ctx context.
 */
अटल पूर्णांक selinux_xfrm_alloc_user(काष्ठा xfrm_sec_ctx **ctxp,
				   काष्ठा xfrm_user_sec_ctx *uctx,
				   gfp_t gfp)
अणु
	पूर्णांक rc;
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());
	काष्ठा xfrm_sec_ctx *ctx = शून्य;
	u32 str_len;

	अगर (ctxp == शून्य || uctx == शून्य ||
	    uctx->ctx_करोi != XFRM_SC_DOI_LSM ||
	    uctx->ctx_alg != XFRM_SC_ALG_SELINUX)
		वापस -EINVAL;

	str_len = uctx->ctx_len;
	अगर (str_len >= PAGE_SIZE)
		वापस -ENOMEM;

	ctx = kदो_स्मृति(माप(*ctx) + str_len + 1, gfp);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->ctx_करोi = XFRM_SC_DOI_LSM;
	ctx->ctx_alg = XFRM_SC_ALG_SELINUX;
	ctx->ctx_len = str_len;
	स_नकल(ctx->ctx_str, &uctx[1], str_len);
	ctx->ctx_str[str_len] = '\0';
	rc = security_context_to_sid(&selinux_state, ctx->ctx_str, str_len,
				     &ctx->ctx_sid, gfp);
	अगर (rc)
		जाओ err;

	rc = avc_has_perm(&selinux_state,
			  tsec->sid, ctx->ctx_sid,
			  SECCLASS_ASSOCIATION, ASSOCIATION__SETCONTEXT, शून्य);
	अगर (rc)
		जाओ err;

	*ctxp = ctx;
	atomic_inc(&selinux_xfrm_refcount);
	वापस 0;

err:
	kमुक्त(ctx);
	वापस rc;
पूर्ण

/*
 * Free the xfrm_sec_ctx काष्ठाure.
 */
अटल व्योम selinux_xfrm_मुक्त(काष्ठा xfrm_sec_ctx *ctx)
अणु
	अगर (!ctx)
		वापस;

	atomic_dec(&selinux_xfrm_refcount);
	kमुक्त(ctx);
पूर्ण

/*
 * Authorize the deletion of a labeled SA or policy rule.
 */
अटल पूर्णांक selinux_xfrm_delete(काष्ठा xfrm_sec_ctx *ctx)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());

	अगर (!ctx)
		वापस 0;

	वापस avc_has_perm(&selinux_state,
			    tsec->sid, ctx->ctx_sid,
			    SECCLASS_ASSOCIATION, ASSOCIATION__SETCONTEXT,
			    शून्य);
पूर्ण

/*
 * LSM hook implementation that authorizes that a flow can use a xfrm policy
 * rule.
 */
पूर्णांक selinux_xfrm_policy_lookup(काष्ठा xfrm_sec_ctx *ctx, u32 fl_secid, u8 dir)
अणु
	पूर्णांक rc;

	/* All flows should be treated as polmatch'ing an otherwise applicable
	 * "non-labeled" policy. This would prevent inadvertent "leaks". */
	अगर (!ctx)
		वापस 0;

	/* Context sid is either set to label or ANY_ASSOC */
	अगर (!selinux_authorizable_ctx(ctx))
		वापस -EINVAL;

	rc = avc_has_perm(&selinux_state,
			  fl_secid, ctx->ctx_sid,
			  SECCLASS_ASSOCIATION, ASSOCIATION__POLMATCH, शून्य);
	वापस (rc == -EACCES ? -ESRCH : rc);
पूर्ण

/*
 * LSM hook implementation that authorizes that a state matches
 * the given policy, flow combo.
 */
पूर्णांक selinux_xfrm_state_pol_flow_match(काष्ठा xfrm_state *x,
				      काष्ठा xfrm_policy *xp,
				      स्थिर काष्ठा flowi_common *flic)
अणु
	u32 state_sid;
	u32 flic_sid;

	अगर (!xp->security)
		अगर (x->security)
			/* unlabeled policy and labeled SA can't match */
			वापस 0;
		अन्यथा
			/* unlabeled policy and unlabeled SA match all flows */
			वापस 1;
	अन्यथा
		अगर (!x->security)
			/* unlabeled SA and labeled policy can't match */
			वापस 0;
		अन्यथा
			अगर (!selinux_authorizable_xfrm(x))
				/* Not a SELinux-labeled SA */
				वापस 0;

	state_sid = x->security->ctx_sid;
	flic_sid = flic->flowic_secid;

	अगर (flic_sid != state_sid)
		वापस 0;

	/* We करोn't need a separate SA Vs. policy polmatch check since the SA
	 * is now of the same label as the flow and a flow Vs. policy polmatch
	 * check had alपढ़ोy happened in selinux_xfrm_policy_lookup() above. */
	वापस (avc_has_perm(&selinux_state, flic_sid, state_sid,
			     SECCLASS_ASSOCIATION, ASSOCIATION__SENDTO,
			     शून्य) ? 0 : 1);
पूर्ण

अटल u32 selinux_xfrm_skb_sid_egress(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा xfrm_state *x;

	अगर (dst == शून्य)
		वापस SECSID_शून्य;
	x = dst->xfrm;
	अगर (x == शून्य || !selinux_authorizable_xfrm(x))
		वापस SECSID_शून्य;

	वापस x->security->ctx_sid;
पूर्ण

अटल पूर्णांक selinux_xfrm_skb_sid_ingress(काष्ठा sk_buff *skb,
					u32 *sid, पूर्णांक ckall)
अणु
	u32 sid_session = SECSID_शून्य;
	काष्ठा sec_path *sp = skb_sec_path(skb);

	अगर (sp) अणु
		पूर्णांक i;

		क्रम (i = sp->len - 1; i >= 0; i--) अणु
			काष्ठा xfrm_state *x = sp->xvec[i];
			अगर (selinux_authorizable_xfrm(x)) अणु
				काष्ठा xfrm_sec_ctx *ctx = x->security;

				अगर (sid_session == SECSID_शून्य) अणु
					sid_session = ctx->ctx_sid;
					अगर (!ckall)
						जाओ out;
				पूर्ण अन्यथा अगर (sid_session != ctx->ctx_sid) अणु
					*sid = SECSID_शून्य;
					वापस -EINVAL;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

out:
	*sid = sid_session;
	वापस 0;
पूर्ण

/*
 * LSM hook implementation that checks and/or वापसs the xfrm sid क्रम the
 * incoming packet.
 */
पूर्णांक selinux_xfrm_decode_session(काष्ठा sk_buff *skb, u32 *sid, पूर्णांक ckall)
अणु
	अगर (skb == शून्य) अणु
		*sid = SECSID_शून्य;
		वापस 0;
	पूर्ण
	वापस selinux_xfrm_skb_sid_ingress(skb, sid, ckall);
पूर्ण

पूर्णांक selinux_xfrm_skb_sid(काष्ठा sk_buff *skb, u32 *sid)
अणु
	पूर्णांक rc;

	rc = selinux_xfrm_skb_sid_ingress(skb, sid, 0);
	अगर (rc == 0 && *sid == SECSID_शून्य)
		*sid = selinux_xfrm_skb_sid_egress(skb);

	वापस rc;
पूर्ण

/*
 * LSM hook implementation that allocs and transfers uctx spec to xfrm_policy.
 */
पूर्णांक selinux_xfrm_policy_alloc(काष्ठा xfrm_sec_ctx **ctxp,
			      काष्ठा xfrm_user_sec_ctx *uctx,
			      gfp_t gfp)
अणु
	वापस selinux_xfrm_alloc_user(ctxp, uctx, gfp);
पूर्ण

/*
 * LSM hook implementation that copies security data काष्ठाure from old to new
 * क्रम policy cloning.
 */
पूर्णांक selinux_xfrm_policy_clone(काष्ठा xfrm_sec_ctx *old_ctx,
			      काष्ठा xfrm_sec_ctx **new_ctxp)
अणु
	काष्ठा xfrm_sec_ctx *new_ctx;

	अगर (!old_ctx)
		वापस 0;

	new_ctx = kmemdup(old_ctx, माप(*old_ctx) + old_ctx->ctx_len,
			  GFP_ATOMIC);
	अगर (!new_ctx)
		वापस -ENOMEM;
	atomic_inc(&selinux_xfrm_refcount);
	*new_ctxp = new_ctx;

	वापस 0;
पूर्ण

/*
 * LSM hook implementation that मुक्तs xfrm_sec_ctx security inक्रमmation.
 */
व्योम selinux_xfrm_policy_मुक्त(काष्ठा xfrm_sec_ctx *ctx)
अणु
	selinux_xfrm_मुक्त(ctx);
पूर्ण

/*
 * LSM hook implementation that authorizes deletion of labeled policies.
 */
पूर्णांक selinux_xfrm_policy_delete(काष्ठा xfrm_sec_ctx *ctx)
अणु
	वापस selinux_xfrm_delete(ctx);
पूर्ण

/*
 * LSM hook implementation that allocates a xfrm_sec_state, populates it using
 * the supplied security context, and assigns it to the xfrm_state.
 */
पूर्णांक selinux_xfrm_state_alloc(काष्ठा xfrm_state *x,
			     काष्ठा xfrm_user_sec_ctx *uctx)
अणु
	वापस selinux_xfrm_alloc_user(&x->security, uctx, GFP_KERNEL);
पूर्ण

/*
 * LSM hook implementation that allocates a xfrm_sec_state and populates based
 * on a secid.
 */
पूर्णांक selinux_xfrm_state_alloc_acquire(काष्ठा xfrm_state *x,
				     काष्ठा xfrm_sec_ctx *polsec, u32 secid)
अणु
	पूर्णांक rc;
	काष्ठा xfrm_sec_ctx *ctx;
	अक्षर *ctx_str = शून्य;
	पूर्णांक str_len;

	अगर (!polsec)
		वापस 0;

	अगर (secid == 0)
		वापस -EINVAL;

	rc = security_sid_to_context(&selinux_state, secid, &ctx_str,
				     &str_len);
	अगर (rc)
		वापस rc;

	ctx = kदो_स्मृति(माप(*ctx) + str_len, GFP_ATOMIC);
	अगर (!ctx) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	ctx->ctx_करोi = XFRM_SC_DOI_LSM;
	ctx->ctx_alg = XFRM_SC_ALG_SELINUX;
	ctx->ctx_sid = secid;
	ctx->ctx_len = str_len;
	स_नकल(ctx->ctx_str, ctx_str, str_len);

	x->security = ctx;
	atomic_inc(&selinux_xfrm_refcount);
out:
	kमुक्त(ctx_str);
	वापस rc;
पूर्ण

/*
 * LSM hook implementation that मुक्तs xfrm_state security inक्रमmation.
 */
व्योम selinux_xfrm_state_मुक्त(काष्ठा xfrm_state *x)
अणु
	selinux_xfrm_मुक्त(x->security);
पूर्ण

/*
 * LSM hook implementation that authorizes deletion of labeled SAs.
 */
पूर्णांक selinux_xfrm_state_delete(काष्ठा xfrm_state *x)
अणु
	वापस selinux_xfrm_delete(x->security);
पूर्ण

/*
 * LSM hook that controls access to unlabelled packets.  If
 * a xfrm_state is authorizable (defined by macro) then it was
 * alपढ़ोy authorized by the IPSec process.  If not, then
 * we need to check क्रम unlabelled access since this may not have
 * gone thru the IPSec process.
 */
पूर्णांक selinux_xfrm_sock_rcv_skb(u32 sk_sid, काष्ठा sk_buff *skb,
			      काष्ठा common_audit_data *ad)
अणु
	पूर्णांक i;
	काष्ठा sec_path *sp = skb_sec_path(skb);
	u32 peer_sid = SECINITSID_UNLABELED;

	अगर (sp) अणु
		क्रम (i = 0; i < sp->len; i++) अणु
			काष्ठा xfrm_state *x = sp->xvec[i];

			अगर (x && selinux_authorizable_xfrm(x)) अणु
				काष्ठा xfrm_sec_ctx *ctx = x->security;
				peer_sid = ctx->ctx_sid;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* This check even when there's no association involved is पूर्णांकended,
	 * according to Trent Jaeger, to make sure a process can't engage in
	 * non-IPsec communication unless explicitly allowed by policy. */
	वापस avc_has_perm(&selinux_state,
			    sk_sid, peer_sid,
			    SECCLASS_ASSOCIATION, ASSOCIATION__RECVFROM, ad);
पूर्ण

/*
 * POSTROUTE_LAST hook's XFRM processing:
 * If we have no security association, then we need to determine
 * whether the socket is allowed to send to an unlabelled destination.
 * If we करो have a authorizable security association, then it has alपढ़ोy been
 * checked in the selinux_xfrm_state_pol_flow_match hook above.
 */
पूर्णांक selinux_xfrm_postroute_last(u32 sk_sid, काष्ठा sk_buff *skb,
				काष्ठा common_audit_data *ad, u8 proto)
अणु
	काष्ठा dst_entry *dst;

	चयन (proto) अणु
	हाल IPPROTO_AH:
	हाल IPPROTO_ESP:
	हाल IPPROTO_COMP:
		/* We should have alपढ़ोy seen this packet once beक्रमe it
		 * underwent xfrm(s). No need to subject it to the unlabeled
		 * check. */
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	dst = skb_dst(skb);
	अगर (dst) अणु
		काष्ठा dst_entry *iter;

		क्रम (iter = dst; iter != शून्य; iter = xfrm_dst_child(iter)) अणु
			काष्ठा xfrm_state *x = iter->xfrm;

			अगर (x && selinux_authorizable_xfrm(x))
				वापस 0;
		पूर्ण
	पूर्ण

	/* This check even when there's no association involved is पूर्णांकended,
	 * according to Trent Jaeger, to make sure a process can't engage in
	 * non-IPsec communication unless explicitly allowed by policy. */
	वापस avc_has_perm(&selinux_state, sk_sid, SECINITSID_UNLABELED,
			    SECCLASS_ASSOCIATION, ASSOCIATION__SENDTO, ad);
पूर्ण
