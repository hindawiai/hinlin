<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* xfrm_user.c: User पूर्णांकerface to configure xfrm engine.
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 *
 * Changes:
 *	Mitsuru KANDA @USAGI
 * 	Kazunori MIYAZAWA @USAGI
 * 	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 * 		IPv6 support
 *
 */

#समावेश <linux/crypto.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/pfkeyv2.h>
#समावेश <linux/ipsec.h>
#समावेश <linux/init.h>
#समावेश <linux/security.h>
#समावेश <net/sock.h>
#समावेश <net/xfrm.h>
#समावेश <net/netlink.h>
#समावेश <net/ah.h>
#समावेश <linux/uaccess.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/in6.h>
#पूर्ण_अगर
#समावेश <यंत्र/unaligned.h>

अटल पूर्णांक verअगरy_one_alg(काष्ठा nlattr **attrs, क्रमागत xfrm_attr_type_t type)
अणु
	काष्ठा nlattr *rt = attrs[type];
	काष्ठा xfrm_algo *algp;

	अगर (!rt)
		वापस 0;

	algp = nla_data(rt);
	अगर (nla_len(rt) < (पूर्णांक)xfrm_alg_len(algp))
		वापस -EINVAL;

	चयन (type) अणु
	हाल XFRMA_ALG_AUTH:
	हाल XFRMA_ALG_CRYPT:
	हाल XFRMA_ALG_COMP:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	algp->alg_name[माप(algp->alg_name) - 1] = '\0';
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_auth_trunc(काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_ALG_AUTH_TRUNC];
	काष्ठा xfrm_algo_auth *algp;

	अगर (!rt)
		वापस 0;

	algp = nla_data(rt);
	अगर (nla_len(rt) < (पूर्णांक)xfrm_alg_auth_len(algp))
		वापस -EINVAL;

	algp->alg_name[माप(algp->alg_name) - 1] = '\0';
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_aead(काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_ALG_AEAD];
	काष्ठा xfrm_algo_aead *algp;

	अगर (!rt)
		वापस 0;

	algp = nla_data(rt);
	अगर (nla_len(rt) < (पूर्णांक)aead_len(algp))
		वापस -EINVAL;

	algp->alg_name[माप(algp->alg_name) - 1] = '\0';
	वापस 0;
पूर्ण

अटल व्योम verअगरy_one_addr(काष्ठा nlattr **attrs, क्रमागत xfrm_attr_type_t type,
			   xfrm_address_t **addrp)
अणु
	काष्ठा nlattr *rt = attrs[type];

	अगर (rt && addrp)
		*addrp = nla_data(rt);
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_sec_ctx_len(काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_SEC_CTX];
	काष्ठा xfrm_user_sec_ctx *uctx;

	अगर (!rt)
		वापस 0;

	uctx = nla_data(rt);
	अगर (uctx->len > nla_len(rt) ||
	    uctx->len != (माप(काष्ठा xfrm_user_sec_ctx) + uctx->ctx_len))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक verअगरy_replay(काष्ठा xfrm_usersa_info *p,
				काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_REPLAY_ESN_VAL];
	काष्ठा xfrm_replay_state_esn *rs;

	अगर (!rt)
		वापस (p->flags & XFRM_STATE_ESN) ? -EINVAL : 0;

	rs = nla_data(rt);

	अगर (rs->bmp_len > XFRMA_REPLAY_ESN_MAX / माप(rs->bmp[0]) / 8)
		वापस -EINVAL;

	अगर (nla_len(rt) < (पूर्णांक)xfrm_replay_state_esn_len(rs) &&
	    nla_len(rt) != माप(*rs))
		वापस -EINVAL;

	/* As only ESP and AH support ESN feature. */
	अगर ((p->id.proto != IPPROTO_ESP) && (p->id.proto != IPPROTO_AH))
		वापस -EINVAL;

	अगर (p->replay_winकरोw != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_newsa_info(काष्ठा xfrm_usersa_info *p,
			     काष्ठा nlattr **attrs)
अणु
	पूर्णांक err;

	err = -EINVAL;
	चयन (p->family) अणु
	हाल AF_INET:
		अवरोध;

	हाल AF_INET6:
#अगर IS_ENABLED(CONFIG_IPV6)
		अवरोध;
#अन्यथा
		err = -EAFNOSUPPORT;
		जाओ out;
#पूर्ण_अगर

	शेष:
		जाओ out;
	पूर्ण

	चयन (p->sel.family) अणु
	हाल AF_UNSPEC:
		अवरोध;

	हाल AF_INET:
		अगर (p->sel.prefixlen_d > 32 || p->sel.prefixlen_s > 32)
			जाओ out;

		अवरोध;

	हाल AF_INET6:
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (p->sel.prefixlen_d > 128 || p->sel.prefixlen_s > 128)
			जाओ out;

		अवरोध;
#अन्यथा
		err = -EAFNOSUPPORT;
		जाओ out;
#पूर्ण_अगर

	शेष:
		जाओ out;
	पूर्ण

	err = -EINVAL;
	चयन (p->id.proto) अणु
	हाल IPPROTO_AH:
		अगर ((!attrs[XFRMA_ALG_AUTH]	&&
		     !attrs[XFRMA_ALG_AUTH_TRUNC]) ||
		    attrs[XFRMA_ALG_AEAD]	||
		    attrs[XFRMA_ALG_CRYPT]	||
		    attrs[XFRMA_ALG_COMP]	||
		    attrs[XFRMA_TFCPAD])
			जाओ out;
		अवरोध;

	हाल IPPROTO_ESP:
		अगर (attrs[XFRMA_ALG_COMP])
			जाओ out;
		अगर (!attrs[XFRMA_ALG_AUTH] &&
		    !attrs[XFRMA_ALG_AUTH_TRUNC] &&
		    !attrs[XFRMA_ALG_CRYPT] &&
		    !attrs[XFRMA_ALG_AEAD])
			जाओ out;
		अगर ((attrs[XFRMA_ALG_AUTH] ||
		     attrs[XFRMA_ALG_AUTH_TRUNC] ||
		     attrs[XFRMA_ALG_CRYPT]) &&
		    attrs[XFRMA_ALG_AEAD])
			जाओ out;
		अगर (attrs[XFRMA_TFCPAD] &&
		    p->mode != XFRM_MODE_TUNNEL)
			जाओ out;
		अवरोध;

	हाल IPPROTO_COMP:
		अगर (!attrs[XFRMA_ALG_COMP]	||
		    attrs[XFRMA_ALG_AEAD]	||
		    attrs[XFRMA_ALG_AUTH]	||
		    attrs[XFRMA_ALG_AUTH_TRUNC]	||
		    attrs[XFRMA_ALG_CRYPT]	||
		    attrs[XFRMA_TFCPAD]		||
		    (ntohl(p->id.spi) >= 0x10000))
			जाओ out;
		अवरोध;

#अगर IS_ENABLED(CONFIG_IPV6)
	हाल IPPROTO_DSTOPTS:
	हाल IPPROTO_ROUTING:
		अगर (attrs[XFRMA_ALG_COMP]	||
		    attrs[XFRMA_ALG_AUTH]	||
		    attrs[XFRMA_ALG_AUTH_TRUNC]	||
		    attrs[XFRMA_ALG_AEAD]	||
		    attrs[XFRMA_ALG_CRYPT]	||
		    attrs[XFRMA_ENCAP]		||
		    attrs[XFRMA_SEC_CTX]	||
		    attrs[XFRMA_TFCPAD]		||
		    !attrs[XFRMA_COADDR])
			जाओ out;
		अवरोध;
#पूर्ण_अगर

	शेष:
		जाओ out;
	पूर्ण

	अगर ((err = verअगरy_aead(attrs)))
		जाओ out;
	अगर ((err = verअगरy_auth_trunc(attrs)))
		जाओ out;
	अगर ((err = verअगरy_one_alg(attrs, XFRMA_ALG_AUTH)))
		जाओ out;
	अगर ((err = verअगरy_one_alg(attrs, XFRMA_ALG_CRYPT)))
		जाओ out;
	अगर ((err = verअगरy_one_alg(attrs, XFRMA_ALG_COMP)))
		जाओ out;
	अगर ((err = verअगरy_sec_ctx_len(attrs)))
		जाओ out;
	अगर ((err = verअगरy_replay(p, attrs)))
		जाओ out;

	err = -EINVAL;
	चयन (p->mode) अणु
	हाल XFRM_MODE_TRANSPORT:
	हाल XFRM_MODE_TUNNEL:
	हाल XFRM_MODE_ROUTEOPTIMIZATION:
	हाल XFRM_MODE_BEET:
		अवरोध;

	शेष:
		जाओ out;
	पूर्ण

	err = 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक attach_one_algo(काष्ठा xfrm_algo **algpp, u8 *props,
			   काष्ठा xfrm_algo_desc *(*get_byname)(स्थिर अक्षर *, पूर्णांक),
			   काष्ठा nlattr *rta)
अणु
	काष्ठा xfrm_algo *p, *ualg;
	काष्ठा xfrm_algo_desc *algo;

	अगर (!rta)
		वापस 0;

	ualg = nla_data(rta);

	algo = get_byname(ualg->alg_name, 1);
	अगर (!algo)
		वापस -ENOSYS;
	*props = algo->desc.sadb_alg_id;

	p = kmemdup(ualg, xfrm_alg_len(ualg), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	म_नकल(p->alg_name, algo->name);
	*algpp = p;
	वापस 0;
पूर्ण

अटल पूर्णांक attach_crypt(काष्ठा xfrm_state *x, काष्ठा nlattr *rta)
अणु
	काष्ठा xfrm_algo *p, *ualg;
	काष्ठा xfrm_algo_desc *algo;

	अगर (!rta)
		वापस 0;

	ualg = nla_data(rta);

	algo = xfrm_ealg_get_byname(ualg->alg_name, 1);
	अगर (!algo)
		वापस -ENOSYS;
	x->props.ealgo = algo->desc.sadb_alg_id;

	p = kmemdup(ualg, xfrm_alg_len(ualg), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	म_नकल(p->alg_name, algo->name);
	x->ealg = p;
	x->geniv = algo->uinfo.encr.geniv;
	वापस 0;
पूर्ण

अटल पूर्णांक attach_auth(काष्ठा xfrm_algo_auth **algpp, u8 *props,
		       काष्ठा nlattr *rta)
अणु
	काष्ठा xfrm_algo *ualg;
	काष्ठा xfrm_algo_auth *p;
	काष्ठा xfrm_algo_desc *algo;

	अगर (!rta)
		वापस 0;

	ualg = nla_data(rta);

	algo = xfrm_aalg_get_byname(ualg->alg_name, 1);
	अगर (!algo)
		वापस -ENOSYS;
	*props = algo->desc.sadb_alg_id;

	p = kदो_स्मृति(माप(*p) + (ualg->alg_key_len + 7) / 8, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	म_नकल(p->alg_name, algo->name);
	p->alg_key_len = ualg->alg_key_len;
	p->alg_trunc_len = algo->uinfo.auth.icv_truncbits;
	स_नकल(p->alg_key, ualg->alg_key, (ualg->alg_key_len + 7) / 8);

	*algpp = p;
	वापस 0;
पूर्ण

अटल पूर्णांक attach_auth_trunc(काष्ठा xfrm_algo_auth **algpp, u8 *props,
			     काष्ठा nlattr *rta)
अणु
	काष्ठा xfrm_algo_auth *p, *ualg;
	काष्ठा xfrm_algo_desc *algo;

	अगर (!rta)
		वापस 0;

	ualg = nla_data(rta);

	algo = xfrm_aalg_get_byname(ualg->alg_name, 1);
	अगर (!algo)
		वापस -ENOSYS;
	अगर (ualg->alg_trunc_len > algo->uinfo.auth.icv_fullbits)
		वापस -EINVAL;
	*props = algo->desc.sadb_alg_id;

	p = kmemdup(ualg, xfrm_alg_auth_len(ualg), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	म_नकल(p->alg_name, algo->name);
	अगर (!p->alg_trunc_len)
		p->alg_trunc_len = algo->uinfo.auth.icv_truncbits;

	*algpp = p;
	वापस 0;
पूर्ण

अटल पूर्णांक attach_aead(काष्ठा xfrm_state *x, काष्ठा nlattr *rta)
अणु
	काष्ठा xfrm_algo_aead *p, *ualg;
	काष्ठा xfrm_algo_desc *algo;

	अगर (!rta)
		वापस 0;

	ualg = nla_data(rta);

	algo = xfrm_aead_get_byname(ualg->alg_name, ualg->alg_icv_len, 1);
	अगर (!algo)
		वापस -ENOSYS;
	x->props.ealgo = algo->desc.sadb_alg_id;

	p = kmemdup(ualg, aead_len(ualg), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	म_नकल(p->alg_name, algo->name);
	x->aead = p;
	x->geniv = algo->uinfo.aead.geniv;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfrm_replay_verअगरy_len(काष्ठा xfrm_replay_state_esn *replay_esn,
					 काष्ठा nlattr *rp)
अणु
	काष्ठा xfrm_replay_state_esn *up;
	अचिन्हित पूर्णांक ulen;

	अगर (!replay_esn || !rp)
		वापस 0;

	up = nla_data(rp);
	ulen = xfrm_replay_state_esn_len(up);

	/* Check the overall length and the पूर्णांकernal biपंचांगap length to aव्योम
	 * potential overflow. */
	अगर (nla_len(rp) < (पूर्णांक)ulen ||
	    xfrm_replay_state_esn_len(replay_esn) != ulen ||
	    replay_esn->bmp_len != up->bmp_len)
		वापस -EINVAL;

	अगर (up->replay_winकरोw > up->bmp_len * माप(__u32) * 8)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_alloc_replay_state_esn(काष्ठा xfrm_replay_state_esn **replay_esn,
				       काष्ठा xfrm_replay_state_esn **preplay_esn,
				       काष्ठा nlattr *rta)
अणु
	काष्ठा xfrm_replay_state_esn *p, *pp, *up;
	अचिन्हित पूर्णांक klen, ulen;

	अगर (!rta)
		वापस 0;

	up = nla_data(rta);
	klen = xfrm_replay_state_esn_len(up);
	ulen = nla_len(rta) >= (पूर्णांक)klen ? klen : माप(*up);

	p = kzalloc(klen, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pp = kzalloc(klen, GFP_KERNEL);
	अगर (!pp) अणु
		kमुक्त(p);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(p, up, ulen);
	स_नकल(pp, up, ulen);

	*replay_esn = p;
	*preplay_esn = pp;

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_user_sec_ctx_size(काष्ठा xfrm_sec_ctx *xfrm_ctx)
अणु
	अचिन्हित पूर्णांक len = 0;

	अगर (xfrm_ctx) अणु
		len += माप(काष्ठा xfrm_user_sec_ctx);
		len += xfrm_ctx->ctx_len;
	पूर्ण
	वापस len;
पूर्ण

अटल व्योम copy_from_user_state(काष्ठा xfrm_state *x, काष्ठा xfrm_usersa_info *p)
अणु
	स_नकल(&x->id, &p->id, माप(x->id));
	स_नकल(&x->sel, &p->sel, माप(x->sel));
	स_नकल(&x->lft, &p->lft, माप(x->lft));
	x->props.mode = p->mode;
	x->props.replay_winकरोw = min_t(अचिन्हित पूर्णांक, p->replay_winकरोw,
					माप(x->replay.biपंचांगap) * 8);
	x->props.reqid = p->reqid;
	x->props.family = p->family;
	स_नकल(&x->props.saddr, &p->saddr, माप(x->props.saddr));
	x->props.flags = p->flags;

	अगर (!x->sel.family && !(p->flags & XFRM_STATE_AF_UNSPEC))
		x->sel.family = p->family;
पूर्ण

/*
 * someday when pfkey also has support, we could have the code
 * somehow made shareable and move it to xfrm_state.c - JHS
 *
*/
अटल व्योम xfrm_update_ae_params(काष्ठा xfrm_state *x, काष्ठा nlattr **attrs,
				  पूर्णांक update_esn)
अणु
	काष्ठा nlattr *rp = attrs[XFRMA_REPLAY_VAL];
	काष्ठा nlattr *re = update_esn ? attrs[XFRMA_REPLAY_ESN_VAL] : शून्य;
	काष्ठा nlattr *lt = attrs[XFRMA_LTIME_VAL];
	काष्ठा nlattr *et = attrs[XFRMA_ETIMER_THRESH];
	काष्ठा nlattr *rt = attrs[XFRMA_REPLAY_THRESH];

	अगर (re) अणु
		काष्ठा xfrm_replay_state_esn *replay_esn;
		replay_esn = nla_data(re);
		स_नकल(x->replay_esn, replay_esn,
		       xfrm_replay_state_esn_len(replay_esn));
		स_नकल(x->preplay_esn, replay_esn,
		       xfrm_replay_state_esn_len(replay_esn));
	पूर्ण

	अगर (rp) अणु
		काष्ठा xfrm_replay_state *replay;
		replay = nla_data(rp);
		स_नकल(&x->replay, replay, माप(*replay));
		स_नकल(&x->preplay, replay, माप(*replay));
	पूर्ण

	अगर (lt) अणु
		काष्ठा xfrm_lअगरeसमय_cur *lसमय;
		lसमय = nla_data(lt);
		x->curlft.bytes = lसमय->bytes;
		x->curlft.packets = lसमय->packets;
		x->curlft.add_समय = lसमय->add_समय;
		x->curlft.use_समय = lसमय->use_समय;
	पूर्ण

	अगर (et)
		x->replay_maxage = nla_get_u32(et);

	अगर (rt)
		x->replay_maxdअगरf = nla_get_u32(rt);
पूर्ण

अटल व्योम xfrm_smark_init(काष्ठा nlattr **attrs, काष्ठा xfrm_mark *m)
अणु
	अगर (attrs[XFRMA_SET_MARK]) अणु
		m->v = nla_get_u32(attrs[XFRMA_SET_MARK]);
		अगर (attrs[XFRMA_SET_MARK_MASK])
			m->m = nla_get_u32(attrs[XFRMA_SET_MARK_MASK]);
		अन्यथा
			m->m = 0xffffffff;
	पूर्ण अन्यथा अणु
		m->v = m->m = 0;
	पूर्ण
पूर्ण

अटल काष्ठा xfrm_state *xfrm_state_स्थिरruct(काष्ठा net *net,
					       काष्ठा xfrm_usersa_info *p,
					       काष्ठा nlattr **attrs,
					       पूर्णांक *errp)
अणु
	काष्ठा xfrm_state *x = xfrm_state_alloc(net);
	पूर्णांक err = -ENOMEM;

	अगर (!x)
		जाओ error_no_put;

	copy_from_user_state(x, p);

	अगर (attrs[XFRMA_SA_EXTRA_FLAGS])
		x->props.extra_flags = nla_get_u32(attrs[XFRMA_SA_EXTRA_FLAGS]);

	अगर ((err = attach_aead(x, attrs[XFRMA_ALG_AEAD])))
		जाओ error;
	अगर ((err = attach_auth_trunc(&x->aalg, &x->props.aalgo,
				     attrs[XFRMA_ALG_AUTH_TRUNC])))
		जाओ error;
	अगर (!x->props.aalgo) अणु
		अगर ((err = attach_auth(&x->aalg, &x->props.aalgo,
				       attrs[XFRMA_ALG_AUTH])))
			जाओ error;
	पूर्ण
	अगर ((err = attach_crypt(x, attrs[XFRMA_ALG_CRYPT])))
		जाओ error;
	अगर ((err = attach_one_algo(&x->calg, &x->props.calgo,
				   xfrm_calg_get_byname,
				   attrs[XFRMA_ALG_COMP])))
		जाओ error;

	अगर (attrs[XFRMA_ENCAP]) अणु
		x->encap = kmemdup(nla_data(attrs[XFRMA_ENCAP]),
				   माप(*x->encap), GFP_KERNEL);
		अगर (x->encap == शून्य)
			जाओ error;
	पूर्ण

	अगर (attrs[XFRMA_TFCPAD])
		x->tfcpad = nla_get_u32(attrs[XFRMA_TFCPAD]);

	अगर (attrs[XFRMA_COADDR]) अणु
		x->coaddr = kmemdup(nla_data(attrs[XFRMA_COADDR]),
				    माप(*x->coaddr), GFP_KERNEL);
		अगर (x->coaddr == शून्य)
			जाओ error;
	पूर्ण

	xfrm_mark_get(attrs, &x->mark);

	xfrm_smark_init(attrs, &x->props.smark);

	अगर (attrs[XFRMA_IF_ID])
		x->अगर_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	err = __xfrm_init_state(x, false, attrs[XFRMA_OFFLOAD_DEV]);
	अगर (err)
		जाओ error;

	अगर (attrs[XFRMA_SEC_CTX]) अणु
		err = security_xfrm_state_alloc(x,
						nla_data(attrs[XFRMA_SEC_CTX]));
		अगर (err)
			जाओ error;
	पूर्ण

	अगर ((err = xfrm_alloc_replay_state_esn(&x->replay_esn, &x->preplay_esn,
					       attrs[XFRMA_REPLAY_ESN_VAL])))
		जाओ error;

	x->km.seq = p->seq;
	x->replay_maxdअगरf = net->xfrm.sysctl_aevent_rseqth;
	/* sysctl_xfrm_aevent_eसमय is in 100ms units */
	x->replay_maxage = (net->xfrm.sysctl_aevent_eसमय*HZ)/XFRM_AE_ETH_M;

	अगर ((err = xfrm_init_replay(x)))
		जाओ error;

	/* override शेष values from above */
	xfrm_update_ae_params(x, attrs, 0);

	/* configure the hardware अगर offload is requested */
	अगर (attrs[XFRMA_OFFLOAD_DEV]) अणु
		err = xfrm_dev_state_add(net, x,
					 nla_data(attrs[XFRMA_OFFLOAD_DEV]));
		अगर (err)
			जाओ error;
	पूर्ण

	वापस x;

error:
	x->km.state = XFRM_STATE_DEAD;
	xfrm_state_put(x);
error_no_put:
	*errp = err;
	वापस शून्य;
पूर्ण

अटल पूर्णांक xfrm_add_sa(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_usersa_info *p = nlmsg_data(nlh);
	काष्ठा xfrm_state *x;
	पूर्णांक err;
	काष्ठा km_event c;

	err = verअगरy_newsa_info(p, attrs);
	अगर (err)
		वापस err;

	x = xfrm_state_स्थिरruct(net, p, attrs, &err);
	अगर (!x)
		वापस err;

	xfrm_state_hold(x);
	अगर (nlh->nlmsg_type == XFRM_MSG_NEWSA)
		err = xfrm_state_add(x);
	अन्यथा
		err = xfrm_state_update(x);

	xfrm_audit_state_add(x, err ? 0 : 1, true);

	अगर (err < 0) अणु
		x->km.state = XFRM_STATE_DEAD;
		xfrm_dev_state_delete(x);
		__xfrm_state_put(x);
		जाओ out;
	पूर्ण

	अगर (x->km.state == XFRM_STATE_VOID)
		x->km.state = XFRM_STATE_VALID;

	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.event = nlh->nlmsg_type;

	km_state_notअगरy(x, &c);
out:
	xfrm_state_put(x);
	वापस err;
पूर्ण

अटल काष्ठा xfrm_state *xfrm_user_state_lookup(काष्ठा net *net,
						 काष्ठा xfrm_usersa_id *p,
						 काष्ठा nlattr **attrs,
						 पूर्णांक *errp)
अणु
	काष्ठा xfrm_state *x = शून्य;
	काष्ठा xfrm_mark m;
	पूर्णांक err;
	u32 mark = xfrm_mark_get(attrs, &m);

	अगर (xfrm_id_proto_match(p->proto, IPSEC_PROTO_ANY)) अणु
		err = -ESRCH;
		x = xfrm_state_lookup(net, mark, &p->daddr, p->spi, p->proto, p->family);
	पूर्ण अन्यथा अणु
		xfrm_address_t *saddr = शून्य;

		verअगरy_one_addr(attrs, XFRMA_SRCADDR, &saddr);
		अगर (!saddr) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		err = -ESRCH;
		x = xfrm_state_lookup_byaddr(net, mark,
					     &p->daddr, saddr,
					     p->proto, p->family);
	पूर्ण

 out:
	अगर (!x && errp)
		*errp = err;
	वापस x;
पूर्ण

अटल पूर्णांक xfrm_del_sa(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_state *x;
	पूर्णांक err = -ESRCH;
	काष्ठा km_event c;
	काष्ठा xfrm_usersa_id *p = nlmsg_data(nlh);

	x = xfrm_user_state_lookup(net, p, attrs, &err);
	अगर (x == शून्य)
		वापस err;

	अगर ((err = security_xfrm_state_delete(x)) != 0)
		जाओ out;

	अगर (xfrm_state_kern(x)) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण

	err = xfrm_state_delete(x);

	अगर (err < 0)
		जाओ out;

	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.event = nlh->nlmsg_type;
	km_state_notअगरy(x, &c);

out:
	xfrm_audit_state_delete(x, err ? 0 : 1, true);
	xfrm_state_put(x);
	वापस err;
पूर्ण

अटल व्योम copy_to_user_state(काष्ठा xfrm_state *x, काष्ठा xfrm_usersa_info *p)
अणु
	स_रखो(p, 0, माप(*p));
	स_नकल(&p->id, &x->id, माप(p->id));
	स_नकल(&p->sel, &x->sel, माप(p->sel));
	स_नकल(&p->lft, &x->lft, माप(p->lft));
	स_नकल(&p->curlft, &x->curlft, माप(p->curlft));
	put_unaligned(x->stats.replay_winकरोw, &p->stats.replay_winकरोw);
	put_unaligned(x->stats.replay, &p->stats.replay);
	put_unaligned(x->stats.पूर्णांकegrity_failed, &p->stats.पूर्णांकegrity_failed);
	स_नकल(&p->saddr, &x->props.saddr, माप(p->saddr));
	p->mode = x->props.mode;
	p->replay_winकरोw = x->props.replay_winकरोw;
	p->reqid = x->props.reqid;
	p->family = x->props.family;
	p->flags = x->props.flags;
	p->seq = x->km.seq;
पूर्ण

काष्ठा xfrm_dump_info अणु
	काष्ठा sk_buff *in_skb;
	काष्ठा sk_buff *out_skb;
	u32 nlmsg_seq;
	u16 nlmsg_flags;
पूर्ण;

अटल पूर्णांक copy_sec_ctx(काष्ठा xfrm_sec_ctx *s, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_user_sec_ctx *uctx;
	काष्ठा nlattr *attr;
	पूर्णांक ctx_size = माप(*uctx) + s->ctx_len;

	attr = nla_reserve(skb, XFRMA_SEC_CTX, ctx_size);
	अगर (attr == शून्य)
		वापस -EMSGSIZE;

	uctx = nla_data(attr);
	uctx->exttype = XFRMA_SEC_CTX;
	uctx->len = ctx_size;
	uctx->ctx_करोi = s->ctx_करोi;
	uctx->ctx_alg = s->ctx_alg;
	uctx->ctx_len = s->ctx_len;
	स_नकल(uctx + 1, s->ctx_str, s->ctx_len);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_user_offload(काष्ठा xfrm_state_offload *xso, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_user_offload *xuo;
	काष्ठा nlattr *attr;

	attr = nla_reserve(skb, XFRMA_OFFLOAD_DEV, माप(*xuo));
	अगर (attr == शून्य)
		वापस -EMSGSIZE;

	xuo = nla_data(attr);
	स_रखो(xuo, 0, माप(*xuo));
	xuo->अगरindex = xso->dev->अगरindex;
	xuo->flags = xso->flags;

	वापस 0;
पूर्ण

अटल bool xfrm_redact(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_SECURITY) &&
		security_locked_करोwn(LOCKDOWN_XFRM_SECRET);
पूर्ण

अटल पूर्णांक copy_to_user_auth(काष्ठा xfrm_algo_auth *auth, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_algo *algo;
	काष्ठा xfrm_algo_auth *ap;
	काष्ठा nlattr *nla;
	bool redact_secret = xfrm_redact();

	nla = nla_reserve(skb, XFRMA_ALG_AUTH,
			  माप(*algo) + (auth->alg_key_len + 7) / 8);
	अगर (!nla)
		वापस -EMSGSIZE;
	algo = nla_data(nla);
	म_नकलन(algo->alg_name, auth->alg_name, माप(algo->alg_name));

	अगर (redact_secret && auth->alg_key_len)
		स_रखो(algo->alg_key, 0, (auth->alg_key_len + 7) / 8);
	अन्यथा
		स_नकल(algo->alg_key, auth->alg_key,
		       (auth->alg_key_len + 7) / 8);
	algo->alg_key_len = auth->alg_key_len;

	nla = nla_reserve(skb, XFRMA_ALG_AUTH_TRUNC, xfrm_alg_auth_len(auth));
	अगर (!nla)
		वापस -EMSGSIZE;
	ap = nla_data(nla);
	स_नकल(ap, auth, माप(काष्ठा xfrm_algo_auth));
	अगर (redact_secret && auth->alg_key_len)
		स_रखो(ap->alg_key, 0, (auth->alg_key_len + 7) / 8);
	अन्यथा
		स_नकल(ap->alg_key, auth->alg_key,
		       (auth->alg_key_len + 7) / 8);
	वापस 0;
पूर्ण

अटल पूर्णांक copy_to_user_aead(काष्ठा xfrm_algo_aead *aead, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla = nla_reserve(skb, XFRMA_ALG_AEAD, aead_len(aead));
	काष्ठा xfrm_algo_aead *ap;
	bool redact_secret = xfrm_redact();

	अगर (!nla)
		वापस -EMSGSIZE;

	ap = nla_data(nla);
	स_नकल(ap, aead, माप(*aead));

	अगर (redact_secret && aead->alg_key_len)
		स_रखो(ap->alg_key, 0, (aead->alg_key_len + 7) / 8);
	अन्यथा
		स_नकल(ap->alg_key, aead->alg_key,
		       (aead->alg_key_len + 7) / 8);
	वापस 0;
पूर्ण

अटल पूर्णांक copy_to_user_ealg(काष्ठा xfrm_algo *ealg, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_algo *ap;
	bool redact_secret = xfrm_redact();
	काष्ठा nlattr *nla = nla_reserve(skb, XFRMA_ALG_CRYPT,
					 xfrm_alg_len(ealg));
	अगर (!nla)
		वापस -EMSGSIZE;

	ap = nla_data(nla);
	स_नकल(ap, ealg, माप(*ealg));

	अगर (redact_secret && ealg->alg_key_len)
		स_रखो(ap->alg_key, 0, (ealg->alg_key_len + 7) / 8);
	अन्यथा
		स_नकल(ap->alg_key, ealg->alg_key,
		       (ealg->alg_key_len + 7) / 8);

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_smark_put(काष्ठा sk_buff *skb, काष्ठा xfrm_mark *m)
अणु
	पूर्णांक ret = 0;

	अगर (m->v | m->m) अणु
		ret = nla_put_u32(skb, XFRMA_SET_MARK, m->v);
		अगर (!ret)
			ret = nla_put_u32(skb, XFRMA_SET_MARK_MASK, m->m);
	पूर्ण
	वापस ret;
पूर्ण

/* Don't change this without updating xfrm_sa_len! */
अटल पूर्णांक copy_to_user_state_extra(काष्ठा xfrm_state *x,
				    काष्ठा xfrm_usersa_info *p,
				    काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = 0;

	copy_to_user_state(x, p);

	अगर (x->props.extra_flags) अणु
		ret = nla_put_u32(skb, XFRMA_SA_EXTRA_FLAGS,
				  x->props.extra_flags);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (x->coaddr) अणु
		ret = nla_put(skb, XFRMA_COADDR, माप(*x->coaddr), x->coaddr);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->lastused) अणु
		ret = nla_put_u64_64bit(skb, XFRMA_LASTUSED, x->lastused,
					XFRMA_PAD);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->aead) अणु
		ret = copy_to_user_aead(x->aead, skb);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->aalg) अणु
		ret = copy_to_user_auth(x->aalg, skb);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->ealg) अणु
		ret = copy_to_user_ealg(x->ealg, skb);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->calg) अणु
		ret = nla_put(skb, XFRMA_ALG_COMP, माप(*(x->calg)), x->calg);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->encap) अणु
		ret = nla_put(skb, XFRMA_ENCAP, माप(*x->encap), x->encap);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->tfcpad) अणु
		ret = nla_put_u32(skb, XFRMA_TFCPAD, x->tfcpad);
		अगर (ret)
			जाओ out;
	पूर्ण
	ret = xfrm_mark_put(skb, &x->mark);
	अगर (ret)
		जाओ out;

	ret = xfrm_smark_put(skb, &x->props.smark);
	अगर (ret)
		जाओ out;

	अगर (x->replay_esn)
		ret = nla_put(skb, XFRMA_REPLAY_ESN_VAL,
			      xfrm_replay_state_esn_len(x->replay_esn),
			      x->replay_esn);
	अन्यथा
		ret = nla_put(skb, XFRMA_REPLAY_VAL, माप(x->replay),
			      &x->replay);
	अगर (ret)
		जाओ out;
	अगर(x->xso.dev)
		ret = copy_user_offload(&x->xso, skb);
	अगर (ret)
		जाओ out;
	अगर (x->अगर_id) अणु
		ret = nla_put_u32(skb, XFRMA_IF_ID, x->अगर_id);
		अगर (ret)
			जाओ out;
	पूर्ण
	अगर (x->security)
		ret = copy_sec_ctx(x->security, skb);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक dump_one_state(काष्ठा xfrm_state *x, पूर्णांक count, व्योम *ptr)
अणु
	काष्ठा xfrm_dump_info *sp = ptr;
	काष्ठा sk_buff *in_skb = sp->in_skb;
	काष्ठा sk_buff *skb = sp->out_skb;
	काष्ठा xfrm_translator *xtr;
	काष्ठा xfrm_usersa_info *p;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put(skb, NETLINK_CB(in_skb).portid, sp->nlmsg_seq,
			XFRM_MSG_NEWSA, माप(*p), sp->nlmsg_flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	p = nlmsg_data(nlh);

	err = copy_to_user_state_extra(x, p, skb);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण
	nlmsg_end(skb, nlh);

	xtr = xfrm_get_translator();
	अगर (xtr) अणु
		err = xtr->alloc_compat(skb, nlh);

		xfrm_put_translator(xtr);
		अगर (err) अणु
			nlmsg_cancel(skb, nlh);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_dump_sa_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा xfrm_state_walk *walk = (काष्ठा xfrm_state_walk *) &cb->args[1];
	काष्ठा sock *sk = cb->skb->sk;
	काष्ठा net *net = sock_net(sk);

	अगर (cb->args[0])
		xfrm_state_walk_करोne(walk, net);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_dump_sa(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_state_walk *walk = (काष्ठा xfrm_state_walk *) &cb->args[1];
	काष्ठा xfrm_dump_info info;

	BUILD_BUG_ON(माप(काष्ठा xfrm_state_walk) >
		     माप(cb->args) - माप(cb->args[0]));

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nlmsg_seq = cb->nlh->nlmsg_seq;
	info.nlmsg_flags = NLM_F_MULTI;

	अगर (!cb->args[0]) अणु
		काष्ठा nlattr *attrs[XFRMA_MAX+1];
		काष्ठा xfrm_address_filter *filter = शून्य;
		u8 proto = 0;
		पूर्णांक err;

		err = nlmsg_parse_deprecated(cb->nlh, 0, attrs, XFRMA_MAX,
					     xfrma_policy, cb->extack);
		अगर (err < 0)
			वापस err;

		अगर (attrs[XFRMA_ADDRESS_FILTER]) अणु
			filter = kmemdup(nla_data(attrs[XFRMA_ADDRESS_FILTER]),
					 माप(*filter), GFP_KERNEL);
			अगर (filter == शून्य)
				वापस -ENOMEM;
		पूर्ण

		अगर (attrs[XFRMA_PROTO])
			proto = nla_get_u8(attrs[XFRMA_PROTO]);

		xfrm_state_walk_init(walk, proto, filter);
		cb->args[0] = 1;
	पूर्ण

	(व्योम) xfrm_state_walk(net, walk, dump_one_state, &info);

	वापस skb->len;
पूर्ण

अटल काष्ठा sk_buff *xfrm_state_netlink(काष्ठा sk_buff *in_skb,
					  काष्ठा xfrm_state *x, u32 seq)
अणु
	काष्ठा xfrm_dump_info info;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nlmsg_seq = seq;
	info.nlmsg_flags = 0;

	err = dump_one_state(x, 0, &info);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण

	वापस skb;
पूर्ण

/* A wrapper क्रम nlmsg_multicast() checking that nlsk is still available.
 * Must be called with RCU पढ़ो lock.
 */
अटल अंतरभूत पूर्णांक xfrm_nlmsg_multicast(काष्ठा net *net, काष्ठा sk_buff *skb,
				       u32 pid, अचिन्हित पूर्णांक group)
अणु
	काष्ठा sock *nlsk = rcu_dereference(net->xfrm.nlsk);
	काष्ठा xfrm_translator *xtr;

	अगर (!nlsk) अणु
		kमुक्त_skb(skb);
		वापस -EPIPE;
	पूर्ण

	xtr = xfrm_get_translator();
	अगर (xtr) अणु
		पूर्णांक err = xtr->alloc_compat(skb, nlmsg_hdr(skb));

		xfrm_put_translator(xtr);
		अगर (err) अणु
			kमुक्त_skb(skb);
			वापस err;
		पूर्ण
	पूर्ण

	वापस nlmsg_multicast(nlsk, skb, pid, group, GFP_ATOMIC);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_spdinfo_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(4)
	       + nla_total_size(माप(काष्ठा xfrmu_spdinfo))
	       + nla_total_size(माप(काष्ठा xfrmu_spdhinfo))
	       + nla_total_size(माप(काष्ठा xfrmu_spdhthresh))
	       + nla_total_size(माप(काष्ठा xfrmu_spdhthresh));
पूर्ण

अटल पूर्णांक build_spdinfo(काष्ठा sk_buff *skb, काष्ठा net *net,
			 u32 portid, u32 seq, u32 flags)
अणु
	काष्ठा xfrmk_spdinfo si;
	काष्ठा xfrmu_spdinfo spc;
	काष्ठा xfrmu_spdhinfo sph;
	काष्ठा xfrmu_spdhthresh spt4, spt6;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;
	u32 *f;
	अचिन्हित lseq;

	nlh = nlmsg_put(skb, portid, seq, XFRM_MSG_NEWSPDINFO, माप(u32), 0);
	अगर (nlh == शून्य) /* shouldn't really happen ... */
		वापस -EMSGSIZE;

	f = nlmsg_data(nlh);
	*f = flags;
	xfrm_spd_getinfo(net, &si);
	spc.incnt = si.incnt;
	spc.outcnt = si.outcnt;
	spc.fwdcnt = si.fwdcnt;
	spc.inscnt = si.inscnt;
	spc.outscnt = si.outscnt;
	spc.fwdscnt = si.fwdscnt;
	sph.spdhcnt = si.spdhcnt;
	sph.spdhmcnt = si.spdhmcnt;

	करो अणु
		lseq = पढ़ो_seqbegin(&net->xfrm.policy_hthresh.lock);

		spt4.lbits = net->xfrm.policy_hthresh.lbits4;
		spt4.rbits = net->xfrm.policy_hthresh.rbits4;
		spt6.lbits = net->xfrm.policy_hthresh.lbits6;
		spt6.rbits = net->xfrm.policy_hthresh.rbits6;
	पूर्ण जबतक (पढ़ो_seqretry(&net->xfrm.policy_hthresh.lock, lseq));

	err = nla_put(skb, XFRMA_SPD_INFO, माप(spc), &spc);
	अगर (!err)
		err = nla_put(skb, XFRMA_SPD_HINFO, माप(sph), &sph);
	अगर (!err)
		err = nla_put(skb, XFRMA_SPD_IPV4_HTHRESH, माप(spt4), &spt4);
	अगर (!err)
		err = nla_put(skb, XFRMA_SPD_IPV6_HTHRESH, माप(spt6), &spt6);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_set_spdinfo(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			    काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrmu_spdhthresh *thresh4 = शून्य;
	काष्ठा xfrmu_spdhthresh *thresh6 = शून्य;

	/* selector prefixlen thresholds to hash policies */
	अगर (attrs[XFRMA_SPD_IPV4_HTHRESH]) अणु
		काष्ठा nlattr *rta = attrs[XFRMA_SPD_IPV4_HTHRESH];

		अगर (nla_len(rta) < माप(*thresh4))
			वापस -EINVAL;
		thresh4 = nla_data(rta);
		अगर (thresh4->lbits > 32 || thresh4->rbits > 32)
			वापस -EINVAL;
	पूर्ण
	अगर (attrs[XFRMA_SPD_IPV6_HTHRESH]) अणु
		काष्ठा nlattr *rta = attrs[XFRMA_SPD_IPV6_HTHRESH];

		अगर (nla_len(rta) < माप(*thresh6))
			वापस -EINVAL;
		thresh6 = nla_data(rta);
		अगर (thresh6->lbits > 128 || thresh6->rbits > 128)
			वापस -EINVAL;
	पूर्ण

	अगर (thresh4 || thresh6) अणु
		ग_लिखो_seqlock(&net->xfrm.policy_hthresh.lock);
		अगर (thresh4) अणु
			net->xfrm.policy_hthresh.lbits4 = thresh4->lbits;
			net->xfrm.policy_hthresh.rbits4 = thresh4->rbits;
		पूर्ण
		अगर (thresh6) अणु
			net->xfrm.policy_hthresh.lbits6 = thresh6->lbits;
			net->xfrm.policy_hthresh.rbits6 = thresh6->rbits;
		पूर्ण
		ग_लिखो_sequnlock(&net->xfrm.policy_hthresh.lock);

		xfrm_policy_hash_rebuild(net);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_get_spdinfo(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा sk_buff *r_skb;
	u32 *flags = nlmsg_data(nlh);
	u32 sportid = NETLINK_CB(skb).portid;
	u32 seq = nlh->nlmsg_seq;
	पूर्णांक err;

	r_skb = nlmsg_new(xfrm_spdinfo_msgsize(), GFP_ATOMIC);
	अगर (r_skb == शून्य)
		वापस -ENOMEM;

	err = build_spdinfo(r_skb, net, sportid, seq, *flags);
	BUG_ON(err < 0);

	वापस nlmsg_unicast(net->xfrm.nlsk, r_skb, sportid);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_sadinfo_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(4)
	       + nla_total_size(माप(काष्ठा xfrmu_sadhinfo))
	       + nla_total_size(4); /* XFRMA_SAD_CNT */
पूर्ण

अटल पूर्णांक build_sadinfo(काष्ठा sk_buff *skb, काष्ठा net *net,
			 u32 portid, u32 seq, u32 flags)
अणु
	काष्ठा xfrmk_sadinfo si;
	काष्ठा xfrmu_sadhinfo sh;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;
	u32 *f;

	nlh = nlmsg_put(skb, portid, seq, XFRM_MSG_NEWSADINFO, माप(u32), 0);
	अगर (nlh == शून्य) /* shouldn't really happen ... */
		वापस -EMSGSIZE;

	f = nlmsg_data(nlh);
	*f = flags;
	xfrm_sad_getinfo(net, &si);

	sh.sadhmcnt = si.sadhmcnt;
	sh.sadhcnt = si.sadhcnt;

	err = nla_put_u32(skb, XFRMA_SAD_CNT, si.sadcnt);
	अगर (!err)
		err = nla_put(skb, XFRMA_SAD_HINFO, माप(sh), &sh);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_get_sadinfo(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा sk_buff *r_skb;
	u32 *flags = nlmsg_data(nlh);
	u32 sportid = NETLINK_CB(skb).portid;
	u32 seq = nlh->nlmsg_seq;
	पूर्णांक err;

	r_skb = nlmsg_new(xfrm_sadinfo_msgsize(), GFP_ATOMIC);
	अगर (r_skb == शून्य)
		वापस -ENOMEM;

	err = build_sadinfo(r_skb, net, sportid, seq, *flags);
	BUG_ON(err < 0);

	वापस nlmsg_unicast(net->xfrm.nlsk, r_skb, sportid);
पूर्ण

अटल पूर्णांक xfrm_get_sa(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_usersa_id *p = nlmsg_data(nlh);
	काष्ठा xfrm_state *x;
	काष्ठा sk_buff *resp_skb;
	पूर्णांक err = -ESRCH;

	x = xfrm_user_state_lookup(net, p, attrs, &err);
	अगर (x == शून्य)
		जाओ out_noput;

	resp_skb = xfrm_state_netlink(skb, x, nlh->nlmsg_seq);
	अगर (IS_ERR(resp_skb)) अणु
		err = PTR_ERR(resp_skb);
	पूर्ण अन्यथा अणु
		err = nlmsg_unicast(net->xfrm.nlsk, resp_skb, NETLINK_CB(skb).portid);
	पूर्ण
	xfrm_state_put(x);
out_noput:
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_alloc_userspi(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_state *x;
	काष्ठा xfrm_userspi_info *p;
	काष्ठा xfrm_translator *xtr;
	काष्ठा sk_buff *resp_skb;
	xfrm_address_t *daddr;
	पूर्णांक family;
	पूर्णांक err;
	u32 mark;
	काष्ठा xfrm_mark m;
	u32 अगर_id = 0;

	p = nlmsg_data(nlh);
	err = verअगरy_spi_info(p->info.id.proto, p->min, p->max);
	अगर (err)
		जाओ out_noput;

	family = p->info.family;
	daddr = &p->info.id.daddr;

	x = शून्य;

	mark = xfrm_mark_get(attrs, &m);

	अगर (attrs[XFRMA_IF_ID])
		अगर_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	अगर (p->info.seq) अणु
		x = xfrm_find_acq_byseq(net, mark, p->info.seq);
		अगर (x && !xfrm_addr_equal(&x->id.daddr, daddr, family)) अणु
			xfrm_state_put(x);
			x = शून्य;
		पूर्ण
	पूर्ण

	अगर (!x)
		x = xfrm_find_acq(net, &m, p->info.mode, p->info.reqid,
				  अगर_id, p->info.id.proto, daddr,
				  &p->info.saddr, 1,
				  family);
	err = -ENOENT;
	अगर (x == शून्य)
		जाओ out_noput;

	err = xfrm_alloc_spi(x, p->min, p->max);
	अगर (err)
		जाओ out;

	resp_skb = xfrm_state_netlink(skb, x, nlh->nlmsg_seq);
	अगर (IS_ERR(resp_skb)) अणु
		err = PTR_ERR(resp_skb);
		जाओ out;
	पूर्ण

	xtr = xfrm_get_translator();
	अगर (xtr) अणु
		err = xtr->alloc_compat(skb, nlmsg_hdr(skb));

		xfrm_put_translator(xtr);
		अगर (err) अणु
			kमुक्त_skb(resp_skb);
			जाओ out;
		पूर्ण
	पूर्ण

	err = nlmsg_unicast(net->xfrm.nlsk, resp_skb, NETLINK_CB(skb).portid);

out:
	xfrm_state_put(x);
out_noput:
	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_policy_dir(u8 dir)
अणु
	चयन (dir) अणु
	हाल XFRM_POLICY_IN:
	हाल XFRM_POLICY_OUT:
	हाल XFRM_POLICY_FWD:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_policy_type(u8 type)
अणु
	चयन (type) अणु
	हाल XFRM_POLICY_TYPE_MAIN:
#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	हाल XFRM_POLICY_TYPE_SUB:
#पूर्ण_अगर
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_newpolicy_info(काष्ठा xfrm_userpolicy_info *p)
अणु
	पूर्णांक ret;

	चयन (p->share) अणु
	हाल XFRM_SHARE_ANY:
	हाल XFRM_SHARE_SESSION:
	हाल XFRM_SHARE_USER:
	हाल XFRM_SHARE_UNIQUE:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (p->action) अणु
	हाल XFRM_POLICY_ALLOW:
	हाल XFRM_POLICY_BLOCK:
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (p->sel.family) अणु
	हाल AF_INET:
		अगर (p->sel.prefixlen_d > 32 || p->sel.prefixlen_s > 32)
			वापस -EINVAL;

		अवरोध;

	हाल AF_INET6:
#अगर IS_ENABLED(CONFIG_IPV6)
		अगर (p->sel.prefixlen_d > 128 || p->sel.prefixlen_s > 128)
			वापस -EINVAL;

		अवरोध;
#अन्यथा
		वापस  -EAFNOSUPPORT;
#पूर्ण_अगर

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = verअगरy_policy_dir(p->dir);
	अगर (ret)
		वापस ret;
	अगर (p->index && (xfrm_policy_id2dir(p->index) != p->dir))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक copy_from_user_sec_ctx(काष्ठा xfrm_policy *pol, काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_SEC_CTX];
	काष्ठा xfrm_user_sec_ctx *uctx;

	अगर (!rt)
		वापस 0;

	uctx = nla_data(rt);
	वापस security_xfrm_policy_alloc(&pol->security, uctx, GFP_KERNEL);
पूर्ण

अटल व्योम copy_ढाँचाs(काष्ठा xfrm_policy *xp, काष्ठा xfrm_user_पंचांगpl *ut,
			   पूर्णांक nr)
अणु
	पूर्णांक i;

	xp->xfrm_nr = nr;
	क्रम (i = 0; i < nr; i++, ut++) अणु
		काष्ठा xfrm_पंचांगpl *t = &xp->xfrm_vec[i];

		स_नकल(&t->id, &ut->id, माप(काष्ठा xfrm_id));
		स_नकल(&t->saddr, &ut->saddr,
		       माप(xfrm_address_t));
		t->reqid = ut->reqid;
		t->mode = ut->mode;
		t->share = ut->share;
		t->optional = ut->optional;
		t->aalgos = ut->aalgos;
		t->ealgos = ut->ealgos;
		t->calgos = ut->calgos;
		/* If all masks are ~0, then we allow all algorithms. */
		t->allalgs = !~(t->aalgos & t->ealgos & t->calgos);
		t->encap_family = ut->family;
	पूर्ण
पूर्ण

अटल पूर्णांक validate_पंचांगpl(पूर्णांक nr, काष्ठा xfrm_user_पंचांगpl *ut, u16 family)
अणु
	u16 prev_family;
	पूर्णांक i;

	अगर (nr > XFRM_MAX_DEPTH)
		वापस -EINVAL;

	prev_family = family;

	क्रम (i = 0; i < nr; i++) अणु
		/* We never validated the ut->family value, so many
		 * applications simply leave it at zero.  The check was
		 * never made and ut->family was ignored because all
		 * ढाँचाs could be assumed to have the same family as
		 * the policy itself.  Now that we will have ipv4-in-ipv6
		 * and ipv6-in-ipv4 tunnels, this is no दीर्घer true.
		 */
		अगर (!ut[i].family)
			ut[i].family = family;

		चयन (ut[i].mode) अणु
		हाल XFRM_MODE_TUNNEL:
		हाल XFRM_MODE_BEET:
			अवरोध;
		शेष:
			अगर (ut[i].family != prev_family)
				वापस -EINVAL;
			अवरोध;
		पूर्ण
		अगर (ut[i].mode >= XFRM_MODE_MAX)
			वापस -EINVAL;

		prev_family = ut[i].family;

		चयन (ut[i].family) अणु
		हाल AF_INET:
			अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
		हाल AF_INET6:
			अवरोध;
#पूर्ण_अगर
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (!xfrm_id_proto_valid(ut[i].id.proto))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक copy_from_user_पंचांगpl(काष्ठा xfrm_policy *pol, काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_TMPL];

	अगर (!rt) अणु
		pol->xfrm_nr = 0;
	पूर्ण अन्यथा अणु
		काष्ठा xfrm_user_पंचांगpl *uपंचांगpl = nla_data(rt);
		पूर्णांक nr = nla_len(rt) / माप(*uपंचांगpl);
		पूर्णांक err;

		err = validate_पंचांगpl(nr, uपंचांगpl, pol->family);
		अगर (err)
			वापस err;

		copy_ढाँचाs(pol, uपंचांगpl, nr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक copy_from_user_policy_type(u8 *tp, काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_POLICY_TYPE];
	काष्ठा xfrm_userpolicy_type *upt;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	पूर्णांक err;

	अगर (rt) अणु
		upt = nla_data(rt);
		type = upt->type;
	पूर्ण

	err = verअगरy_policy_type(type);
	अगर (err)
		वापस err;

	*tp = type;
	वापस 0;
पूर्ण

अटल व्योम copy_from_user_policy(काष्ठा xfrm_policy *xp, काष्ठा xfrm_userpolicy_info *p)
अणु
	xp->priority = p->priority;
	xp->index = p->index;
	स_नकल(&xp->selector, &p->sel, माप(xp->selector));
	स_नकल(&xp->lft, &p->lft, माप(xp->lft));
	xp->action = p->action;
	xp->flags = p->flags;
	xp->family = p->sel.family;
	/* XXX xp->share = p->share; */
पूर्ण

अटल व्योम copy_to_user_policy(काष्ठा xfrm_policy *xp, काष्ठा xfrm_userpolicy_info *p, पूर्णांक dir)
अणु
	स_रखो(p, 0, माप(*p));
	स_नकल(&p->sel, &xp->selector, माप(p->sel));
	स_नकल(&p->lft, &xp->lft, माप(p->lft));
	स_नकल(&p->curlft, &xp->curlft, माप(p->curlft));
	p->priority = xp->priority;
	p->index = xp->index;
	p->sel.family = xp->family;
	p->dir = dir;
	p->action = xp->action;
	p->flags = xp->flags;
	p->share = XFRM_SHARE_ANY; /* XXX xp->share */
पूर्ण

अटल काष्ठा xfrm_policy *xfrm_policy_स्थिरruct(काष्ठा net *net, काष्ठा xfrm_userpolicy_info *p, काष्ठा nlattr **attrs, पूर्णांक *errp)
अणु
	काष्ठा xfrm_policy *xp = xfrm_policy_alloc(net, GFP_KERNEL);
	पूर्णांक err;

	अगर (!xp) अणु
		*errp = -ENOMEM;
		वापस शून्य;
	पूर्ण

	copy_from_user_policy(xp, p);

	err = copy_from_user_policy_type(&xp->type, attrs);
	अगर (err)
		जाओ error;

	अगर (!(err = copy_from_user_पंचांगpl(xp, attrs)))
		err = copy_from_user_sec_ctx(xp, attrs);
	अगर (err)
		जाओ error;

	xfrm_mark_get(attrs, &xp->mark);

	अगर (attrs[XFRMA_IF_ID])
		xp->अगर_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	वापस xp;
 error:
	*errp = err;
	xp->walk.dead = 1;
	xfrm_policy_destroy(xp);
	वापस शून्य;
पूर्ण

अटल पूर्णांक xfrm_add_policy(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_userpolicy_info *p = nlmsg_data(nlh);
	काष्ठा xfrm_policy *xp;
	काष्ठा km_event c;
	पूर्णांक err;
	पूर्णांक excl;

	err = verअगरy_newpolicy_info(p);
	अगर (err)
		वापस err;
	err = verअगरy_sec_ctx_len(attrs);
	अगर (err)
		वापस err;

	xp = xfrm_policy_स्थिरruct(net, p, attrs, &err);
	अगर (!xp)
		वापस err;

	/* shouldn't excl be based on nlh flags??
	 * Aha! this is anti-netlink really i.e  more pfkey derived
	 * in netlink excl is a flag and you wouldn't need
	 * a type XFRM_MSG_UPDPOLICY - JHS */
	excl = nlh->nlmsg_type == XFRM_MSG_NEWPOLICY;
	err = xfrm_policy_insert(p->dir, xp, excl);
	xfrm_audit_policy_add(xp, err ? 0 : 1, true);

	अगर (err) अणु
		security_xfrm_policy_मुक्त(xp->security);
		kमुक्त(xp);
		वापस err;
	पूर्ण

	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	km_policy_notअगरy(xp, p->dir, &c);

	xfrm_pol_put(xp);

	वापस 0;
पूर्ण

अटल पूर्णांक copy_to_user_पंचांगpl(काष्ठा xfrm_policy *xp, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_user_पंचांगpl vec[XFRM_MAX_DEPTH];
	पूर्णांक i;

	अगर (xp->xfrm_nr == 0)
		वापस 0;

	क्रम (i = 0; i < xp->xfrm_nr; i++) अणु
		काष्ठा xfrm_user_पंचांगpl *up = &vec[i];
		काष्ठा xfrm_पंचांगpl *kp = &xp->xfrm_vec[i];

		स_रखो(up, 0, माप(*up));
		स_नकल(&up->id, &kp->id, माप(up->id));
		up->family = kp->encap_family;
		स_नकल(&up->saddr, &kp->saddr, माप(up->saddr));
		up->reqid = kp->reqid;
		up->mode = kp->mode;
		up->share = kp->share;
		up->optional = kp->optional;
		up->aalgos = kp->aalgos;
		up->ealgos = kp->ealgos;
		up->calgos = kp->calgos;
	पूर्ण

	वापस nla_put(skb, XFRMA_TMPL,
		       माप(काष्ठा xfrm_user_पंचांगpl) * xp->xfrm_nr, vec);
पूर्ण

अटल अंतरभूत पूर्णांक copy_to_user_state_sec_ctx(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	अगर (x->security) अणु
		वापस copy_sec_ctx(x->security, skb);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक copy_to_user_sec_ctx(काष्ठा xfrm_policy *xp, काष्ठा sk_buff *skb)
अणु
	अगर (xp->security)
		वापस copy_sec_ctx(xp->security, skb);
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक userpolicy_type_attrsize(व्योम)
अणु
#अगर_घोषित CONFIG_XFRM_SUB_POLICY
	वापस nla_total_size(माप(काष्ठा xfrm_userpolicy_type));
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_XFRM_SUB_POLICY
अटल पूर्णांक copy_to_user_policy_type(u8 type, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_userpolicy_type upt;

	/* Sadly there are two holes in काष्ठा xfrm_userpolicy_type */
	स_रखो(&upt, 0, माप(upt));
	upt.type = type;

	वापस nla_put(skb, XFRMA_POLICY_TYPE, माप(upt), &upt);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक copy_to_user_policy_type(u8 type, काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dump_one_policy(काष्ठा xfrm_policy *xp, पूर्णांक dir, पूर्णांक count, व्योम *ptr)
अणु
	काष्ठा xfrm_dump_info *sp = ptr;
	काष्ठा xfrm_userpolicy_info *p;
	काष्ठा sk_buff *in_skb = sp->in_skb;
	काष्ठा sk_buff *skb = sp->out_skb;
	काष्ठा xfrm_translator *xtr;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put(skb, NETLINK_CB(in_skb).portid, sp->nlmsg_seq,
			XFRM_MSG_NEWPOLICY, माप(*p), sp->nlmsg_flags);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	p = nlmsg_data(nlh);
	copy_to_user_policy(xp, p, dir);
	err = copy_to_user_पंचांगpl(xp, skb);
	अगर (!err)
		err = copy_to_user_sec_ctx(xp, skb);
	अगर (!err)
		err = copy_to_user_policy_type(xp->type, skb);
	अगर (!err)
		err = xfrm_mark_put(skb, &xp->mark);
	अगर (!err)
		err = xfrm_अगर_id_put(skb, xp->अगर_id);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण
	nlmsg_end(skb, nlh);

	xtr = xfrm_get_translator();
	अगर (xtr) अणु
		err = xtr->alloc_compat(skb, nlh);

		xfrm_put_translator(xtr);
		अगर (err) अणु
			nlmsg_cancel(skb, nlh);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_dump_policy_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा xfrm_policy_walk *walk = (काष्ठा xfrm_policy_walk *)cb->args;
	काष्ठा net *net = sock_net(cb->skb->sk);

	xfrm_policy_walk_करोne(walk, net);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_dump_policy_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा xfrm_policy_walk *walk = (काष्ठा xfrm_policy_walk *)cb->args;

	BUILD_BUG_ON(माप(*walk) > माप(cb->args));

	xfrm_policy_walk_init(walk, XFRM_POLICY_TYPE_ANY);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_dump_policy(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_policy_walk *walk = (काष्ठा xfrm_policy_walk *)cb->args;
	काष्ठा xfrm_dump_info info;

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nlmsg_seq = cb->nlh->nlmsg_seq;
	info.nlmsg_flags = NLM_F_MULTI;

	(व्योम) xfrm_policy_walk(net, walk, dump_one_policy, &info);

	वापस skb->len;
पूर्ण

अटल काष्ठा sk_buff *xfrm_policy_netlink(काष्ठा sk_buff *in_skb,
					  काष्ठा xfrm_policy *xp,
					  पूर्णांक dir, u32 seq)
अणु
	काष्ठा xfrm_dump_info info;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nlmsg_seq = seq;
	info.nlmsg_flags = 0;

	err = dump_one_policy(xp, dir, 0, &info);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(err);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक xfrm_get_policy(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_policy *xp;
	काष्ठा xfrm_userpolicy_id *p;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	पूर्णांक err;
	काष्ठा km_event c;
	पूर्णांक delete;
	काष्ठा xfrm_mark m;
	u32 अगर_id = 0;

	p = nlmsg_data(nlh);
	delete = nlh->nlmsg_type == XFRM_MSG_DELPOLICY;

	err = copy_from_user_policy_type(&type, attrs);
	अगर (err)
		वापस err;

	err = verअगरy_policy_dir(p->dir);
	अगर (err)
		वापस err;

	अगर (attrs[XFRMA_IF_ID])
		अगर_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	xfrm_mark_get(attrs, &m);

	अगर (p->index)
		xp = xfrm_policy_byid(net, &m, अगर_id, type, p->dir,
				      p->index, delete, &err);
	अन्यथा अणु
		काष्ठा nlattr *rt = attrs[XFRMA_SEC_CTX];
		काष्ठा xfrm_sec_ctx *ctx;

		err = verअगरy_sec_ctx_len(attrs);
		अगर (err)
			वापस err;

		ctx = शून्य;
		अगर (rt) अणु
			काष्ठा xfrm_user_sec_ctx *uctx = nla_data(rt);

			err = security_xfrm_policy_alloc(&ctx, uctx, GFP_KERNEL);
			अगर (err)
				वापस err;
		पूर्ण
		xp = xfrm_policy_bysel_ctx(net, &m, अगर_id, type, p->dir,
					   &p->sel, ctx, delete, &err);
		security_xfrm_policy_मुक्त(ctx);
	पूर्ण
	अगर (xp == शून्य)
		वापस -ENOENT;

	अगर (!delete) अणु
		काष्ठा sk_buff *resp_skb;

		resp_skb = xfrm_policy_netlink(skb, xp, p->dir, nlh->nlmsg_seq);
		अगर (IS_ERR(resp_skb)) अणु
			err = PTR_ERR(resp_skb);
		पूर्ण अन्यथा अणु
			err = nlmsg_unicast(net->xfrm.nlsk, resp_skb,
					    NETLINK_CB(skb).portid);
		पूर्ण
	पूर्ण अन्यथा अणु
		xfrm_audit_policy_delete(xp, err ? 0 : 1, true);

		अगर (err != 0)
			जाओ out;

		c.data.byid = p->index;
		c.event = nlh->nlmsg_type;
		c.seq = nlh->nlmsg_seq;
		c.portid = nlh->nlmsg_pid;
		km_policy_notअगरy(xp, p->dir, &c);
	पूर्ण

out:
	xfrm_pol_put(xp);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_flush_sa(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा km_event c;
	काष्ठा xfrm_usersa_flush *p = nlmsg_data(nlh);
	पूर्णांक err;

	err = xfrm_state_flush(net, p->proto, true, false);
	अगर (err) अणु
		अगर (err == -ESRCH) /* empty table */
			वापस 0;
		वापस err;
	पूर्ण
	c.data.proto = p->proto;
	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.net = net;
	km_state_notअगरy(शून्य, &c);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_aevent_msgsize(काष्ठा xfrm_state *x)
अणु
	अचिन्हित पूर्णांक replay_size = x->replay_esn ?
			      xfrm_replay_state_esn_len(x->replay_esn) :
			      माप(काष्ठा xfrm_replay_state);

	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_aevent_id))
	       + nla_total_size(replay_size)
	       + nla_total_size_64bit(माप(काष्ठा xfrm_lअगरeसमय_cur))
	       + nla_total_size(माप(काष्ठा xfrm_mark))
	       + nla_total_size(4) /* XFRM_AE_RTHR */
	       + nla_total_size(4); /* XFRM_AE_ETHR */
पूर्ण

अटल पूर्णांक build_aevent(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा xfrm_aevent_id *id;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put(skb, c->portid, c->seq, XFRM_MSG_NEWAE, माप(*id), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	id = nlmsg_data(nlh);
	स_रखो(&id->sa_id, 0, माप(id->sa_id));
	स_नकल(&id->sa_id.daddr, &x->id.daddr, माप(x->id.daddr));
	id->sa_id.spi = x->id.spi;
	id->sa_id.family = x->props.family;
	id->sa_id.proto = x->id.proto;
	स_नकल(&id->saddr, &x->props.saddr, माप(x->props.saddr));
	id->reqid = x->props.reqid;
	id->flags = c->data.aevent;

	अगर (x->replay_esn) अणु
		err = nla_put(skb, XFRMA_REPLAY_ESN_VAL,
			      xfrm_replay_state_esn_len(x->replay_esn),
			      x->replay_esn);
	पूर्ण अन्यथा अणु
		err = nla_put(skb, XFRMA_REPLAY_VAL, माप(x->replay),
			      &x->replay);
	पूर्ण
	अगर (err)
		जाओ out_cancel;
	err = nla_put_64bit(skb, XFRMA_LTIME_VAL, माप(x->curlft), &x->curlft,
			    XFRMA_PAD);
	अगर (err)
		जाओ out_cancel;

	अगर (id->flags & XFRM_AE_RTHR) अणु
		err = nla_put_u32(skb, XFRMA_REPLAY_THRESH, x->replay_maxdअगरf);
		अगर (err)
			जाओ out_cancel;
	पूर्ण
	अगर (id->flags & XFRM_AE_ETHR) अणु
		err = nla_put_u32(skb, XFRMA_ETIMER_THRESH,
				  x->replay_maxage * 10 / HZ);
		अगर (err)
			जाओ out_cancel;
	पूर्ण
	err = xfrm_mark_put(skb, &x->mark);
	अगर (err)
		जाओ out_cancel;

	err = xfrm_अगर_id_put(skb, x->अगर_id);
	अगर (err)
		जाओ out_cancel;

	nlmsg_end(skb, nlh);
	वापस 0;

out_cancel:
	nlmsg_cancel(skb, nlh);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_get_ae(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_state *x;
	काष्ठा sk_buff *r_skb;
	पूर्णांक err;
	काष्ठा km_event c;
	u32 mark;
	काष्ठा xfrm_mark m;
	काष्ठा xfrm_aevent_id *p = nlmsg_data(nlh);
	काष्ठा xfrm_usersa_id *id = &p->sa_id;

	mark = xfrm_mark_get(attrs, &m);

	x = xfrm_state_lookup(net, mark, &id->daddr, id->spi, id->proto, id->family);
	अगर (x == शून्य)
		वापस -ESRCH;

	r_skb = nlmsg_new(xfrm_aevent_msgsize(x), GFP_ATOMIC);
	अगर (r_skb == शून्य) अणु
		xfrm_state_put(x);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * XXX: is this lock really needed - none of the other
	 * माला_लो lock (the concern is things getting updated
	 * जबतक we are still पढ़ोing) - jhs
	*/
	spin_lock_bh(&x->lock);
	c.data.aevent = p->flags;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;

	err = build_aevent(r_skb, x, &c);
	BUG_ON(err < 0);

	err = nlmsg_unicast(net->xfrm.nlsk, r_skb, NETLINK_CB(skb).portid);
	spin_unlock_bh(&x->lock);
	xfrm_state_put(x);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_new_ae(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_state *x;
	काष्ठा km_event c;
	पूर्णांक err = -EINVAL;
	u32 mark = 0;
	काष्ठा xfrm_mark m;
	काष्ठा xfrm_aevent_id *p = nlmsg_data(nlh);
	काष्ठा nlattr *rp = attrs[XFRMA_REPLAY_VAL];
	काष्ठा nlattr *re = attrs[XFRMA_REPLAY_ESN_VAL];
	काष्ठा nlattr *lt = attrs[XFRMA_LTIME_VAL];
	काष्ठा nlattr *et = attrs[XFRMA_ETIMER_THRESH];
	काष्ठा nlattr *rt = attrs[XFRMA_REPLAY_THRESH];

	अगर (!lt && !rp && !re && !et && !rt)
		वापस err;

	/* pedantic mode - thou shalt sayeth replaceth */
	अगर (!(nlh->nlmsg_flags&NLM_F_REPLACE))
		वापस err;

	mark = xfrm_mark_get(attrs, &m);

	x = xfrm_state_lookup(net, mark, &p->sa_id.daddr, p->sa_id.spi, p->sa_id.proto, p->sa_id.family);
	अगर (x == शून्य)
		वापस -ESRCH;

	अगर (x->km.state != XFRM_STATE_VALID)
		जाओ out;

	err = xfrm_replay_verअगरy_len(x->replay_esn, re);
	अगर (err)
		जाओ out;

	spin_lock_bh(&x->lock);
	xfrm_update_ae_params(x, attrs, 1);
	spin_unlock_bh(&x->lock);

	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.data.aevent = XFRM_AE_CU;
	km_state_notअगरy(x, &c);
	err = 0;
out:
	xfrm_state_put(x);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_flush_policy(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा km_event c;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	पूर्णांक err;

	err = copy_from_user_policy_type(&type, attrs);
	अगर (err)
		वापस err;

	err = xfrm_policy_flush(net, type, true);
	अगर (err) अणु
		अगर (err == -ESRCH) /* empty table */
			वापस 0;
		वापस err;
	पूर्ण

	c.data.type = type;
	c.event = nlh->nlmsg_type;
	c.seq = nlh->nlmsg_seq;
	c.portid = nlh->nlmsg_pid;
	c.net = net;
	km_policy_notअगरy(शून्य, 0, &c);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_add_pol_expire(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_policy *xp;
	काष्ठा xfrm_user_polexpire *up = nlmsg_data(nlh);
	काष्ठा xfrm_userpolicy_info *p = &up->pol;
	u8 type = XFRM_POLICY_TYPE_MAIN;
	पूर्णांक err = -ENOENT;
	काष्ठा xfrm_mark m;
	u32 अगर_id = 0;

	err = copy_from_user_policy_type(&type, attrs);
	अगर (err)
		वापस err;

	err = verअगरy_policy_dir(p->dir);
	अगर (err)
		वापस err;

	अगर (attrs[XFRMA_IF_ID])
		अगर_id = nla_get_u32(attrs[XFRMA_IF_ID]);

	xfrm_mark_get(attrs, &m);

	अगर (p->index)
		xp = xfrm_policy_byid(net, &m, अगर_id, type, p->dir, p->index,
				      0, &err);
	अन्यथा अणु
		काष्ठा nlattr *rt = attrs[XFRMA_SEC_CTX];
		काष्ठा xfrm_sec_ctx *ctx;

		err = verअगरy_sec_ctx_len(attrs);
		अगर (err)
			वापस err;

		ctx = शून्य;
		अगर (rt) अणु
			काष्ठा xfrm_user_sec_ctx *uctx = nla_data(rt);

			err = security_xfrm_policy_alloc(&ctx, uctx, GFP_KERNEL);
			अगर (err)
				वापस err;
		पूर्ण
		xp = xfrm_policy_bysel_ctx(net, &m, अगर_id, type, p->dir,
					   &p->sel, ctx, 0, &err);
		security_xfrm_policy_मुक्त(ctx);
	पूर्ण
	अगर (xp == शून्य)
		वापस -ENOENT;

	अगर (unlikely(xp->walk.dead))
		जाओ out;

	err = 0;
	अगर (up->hard) अणु
		xfrm_policy_delete(xp, p->dir);
		xfrm_audit_policy_delete(xp, 1, true);
	पूर्ण
	km_policy_expired(xp, p->dir, up->hard, nlh->nlmsg_pid);

out:
	xfrm_pol_put(xp);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_add_sa_expire(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_state *x;
	पूर्णांक err;
	काष्ठा xfrm_user_expire *ue = nlmsg_data(nlh);
	काष्ठा xfrm_usersa_info *p = &ue->state;
	काष्ठा xfrm_mark m;
	u32 mark = xfrm_mark_get(attrs, &m);

	x = xfrm_state_lookup(net, mark, &p->id.daddr, p->id.spi, p->id.proto, p->family);

	err = -ENOENT;
	अगर (x == शून्य)
		वापस err;

	spin_lock_bh(&x->lock);
	err = -EINVAL;
	अगर (x->km.state != XFRM_STATE_VALID)
		जाओ out;
	km_state_expired(x, ue->hard, nlh->nlmsg_pid);

	अगर (ue->hard) अणु
		__xfrm_state_delete(x);
		xfrm_audit_state_delete(x, 1, true);
	पूर्ण
	err = 0;
out:
	spin_unlock_bh(&x->lock);
	xfrm_state_put(x);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_add_acquire(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
		काष्ठा nlattr **attrs)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_policy *xp;
	काष्ठा xfrm_user_पंचांगpl *ut;
	पूर्णांक i;
	काष्ठा nlattr *rt = attrs[XFRMA_TMPL];
	काष्ठा xfrm_mark mark;

	काष्ठा xfrm_user_acquire *ua = nlmsg_data(nlh);
	काष्ठा xfrm_state *x = xfrm_state_alloc(net);
	पूर्णांक err = -ENOMEM;

	अगर (!x)
		जाओ nomem;

	xfrm_mark_get(attrs, &mark);

	err = verअगरy_newpolicy_info(&ua->policy);
	अगर (err)
		जाओ मुक्त_state;
	err = verअगरy_sec_ctx_len(attrs);
	अगर (err)
		जाओ मुक्त_state;

	/*   build an XP */
	xp = xfrm_policy_स्थिरruct(net, &ua->policy, attrs, &err);
	अगर (!xp)
		जाओ मुक्त_state;

	स_नकल(&x->id, &ua->id, माप(ua->id));
	स_नकल(&x->props.saddr, &ua->saddr, माप(ua->saddr));
	स_नकल(&x->sel, &ua->sel, माप(ua->sel));
	xp->mark.m = x->mark.m = mark.m;
	xp->mark.v = x->mark.v = mark.v;
	ut = nla_data(rt);
	/* extract the ढाँचाs and क्रम each call km_key */
	क्रम (i = 0; i < xp->xfrm_nr; i++, ut++) अणु
		काष्ठा xfrm_पंचांगpl *t = &xp->xfrm_vec[i];
		स_नकल(&x->id, &t->id, माप(x->id));
		x->props.mode = t->mode;
		x->props.reqid = t->reqid;
		x->props.family = ut->family;
		t->aalgos = ua->aalgos;
		t->ealgos = ua->ealgos;
		t->calgos = ua->calgos;
		err = km_query(x, t, xp);

	पूर्ण

	xfrm_state_मुक्त(x);
	kमुक्त(xp);

	वापस 0;

मुक्त_state:
	xfrm_state_मुक्त(x);
nomem:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_XFRM_MIGRATE
अटल पूर्णांक copy_from_user_migrate(काष्ठा xfrm_migrate *ma,
				  काष्ठा xfrm_kmaddress *k,
				  काष्ठा nlattr **attrs, पूर्णांक *num)
अणु
	काष्ठा nlattr *rt = attrs[XFRMA_MIGRATE];
	काष्ठा xfrm_user_migrate *um;
	पूर्णांक i, num_migrate;

	अगर (k != शून्य) अणु
		काष्ठा xfrm_user_kmaddress *uk;

		uk = nla_data(attrs[XFRMA_KMADDRESS]);
		स_नकल(&k->local, &uk->local, माप(k->local));
		स_नकल(&k->remote, &uk->remote, माप(k->remote));
		k->family = uk->family;
		k->reserved = uk->reserved;
	पूर्ण

	um = nla_data(rt);
	num_migrate = nla_len(rt) / माप(*um);

	अगर (num_migrate <= 0 || num_migrate > XFRM_MAX_DEPTH)
		वापस -EINVAL;

	क्रम (i = 0; i < num_migrate; i++, um++, ma++) अणु
		स_नकल(&ma->old_daddr, &um->old_daddr, माप(ma->old_daddr));
		स_नकल(&ma->old_saddr, &um->old_saddr, माप(ma->old_saddr));
		स_नकल(&ma->new_daddr, &um->new_daddr, माप(ma->new_daddr));
		स_नकल(&ma->new_saddr, &um->new_saddr, माप(ma->new_saddr));

		ma->proto = um->proto;
		ma->mode = um->mode;
		ma->reqid = um->reqid;

		ma->old_family = um->old_family;
		ma->new_family = um->new_family;
	पूर्ण

	*num = i;
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_करो_migrate(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			   काष्ठा nlattr **attrs)
अणु
	काष्ठा xfrm_userpolicy_id *pi = nlmsg_data(nlh);
	काष्ठा xfrm_migrate m[XFRM_MAX_DEPTH];
	काष्ठा xfrm_kmaddress km, *kmp;
	u8 type;
	पूर्णांक err;
	पूर्णांक n = 0;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा xfrm_encap_पंचांगpl  *encap = शून्य;

	अगर (attrs[XFRMA_MIGRATE] == शून्य)
		वापस -EINVAL;

	kmp = attrs[XFRMA_KMADDRESS] ? &km : शून्य;

	err = copy_from_user_policy_type(&type, attrs);
	अगर (err)
		वापस err;

	err = copy_from_user_migrate((काष्ठा xfrm_migrate *)m, kmp, attrs, &n);
	अगर (err)
		वापस err;

	अगर (!n)
		वापस 0;

	अगर (attrs[XFRMA_ENCAP]) अणु
		encap = kmemdup(nla_data(attrs[XFRMA_ENCAP]),
				माप(*encap), GFP_KERNEL);
		अगर (!encap)
			वापस -ENOMEM;
	पूर्ण

	err = xfrm_migrate(&pi->sel, pi->dir, type, m, n, kmp, net, encap);

	kमुक्त(encap);

	वापस err;
पूर्ण
#अन्यथा
अटल पूर्णांक xfrm_करो_migrate(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			   काष्ठा nlattr **attrs)
अणु
	वापस -ENOPROTOOPT;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_XFRM_MIGRATE
अटल पूर्णांक copy_to_user_migrate(स्थिर काष्ठा xfrm_migrate *m, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_user_migrate um;

	स_रखो(&um, 0, माप(um));
	um.proto = m->proto;
	um.mode = m->mode;
	um.reqid = m->reqid;
	um.old_family = m->old_family;
	स_नकल(&um.old_daddr, &m->old_daddr, माप(um.old_daddr));
	स_नकल(&um.old_saddr, &m->old_saddr, माप(um.old_saddr));
	um.new_family = m->new_family;
	स_नकल(&um.new_daddr, &m->new_daddr, माप(um.new_daddr));
	स_नकल(&um.new_saddr, &m->new_saddr, माप(um.new_saddr));

	वापस nla_put(skb, XFRMA_MIGRATE, माप(um), &um);
पूर्ण

अटल पूर्णांक copy_to_user_kmaddress(स्थिर काष्ठा xfrm_kmaddress *k, काष्ठा sk_buff *skb)
अणु
	काष्ठा xfrm_user_kmaddress uk;

	स_रखो(&uk, 0, माप(uk));
	uk.family = k->family;
	uk.reserved = k->reserved;
	स_नकल(&uk.local, &k->local, माप(uk.local));
	स_नकल(&uk.remote, &k->remote, माप(uk.remote));

	वापस nla_put(skb, XFRMA_KMADDRESS, माप(uk), &uk);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_migrate_msgsize(पूर्णांक num_migrate, पूर्णांक with_kma,
						पूर्णांक with_encp)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_userpolicy_id))
	      + (with_kma ? nla_total_size(माप(काष्ठा xfrm_kmaddress)) : 0)
	      + (with_encp ? nla_total_size(माप(काष्ठा xfrm_encap_पंचांगpl)) : 0)
	      + nla_total_size(माप(काष्ठा xfrm_user_migrate) * num_migrate)
	      + userpolicy_type_attrsize();
पूर्ण

अटल पूर्णांक build_migrate(काष्ठा sk_buff *skb, स्थिर काष्ठा xfrm_migrate *m,
			 पूर्णांक num_migrate, स्थिर काष्ठा xfrm_kmaddress *k,
			 स्थिर काष्ठा xfrm_selector *sel,
			 स्थिर काष्ठा xfrm_encap_पंचांगpl *encap, u8 dir, u8 type)
अणु
	स्थिर काष्ठा xfrm_migrate *mp;
	काष्ठा xfrm_userpolicy_id *pol_id;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक i, err;

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_MIGRATE, माप(*pol_id), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	pol_id = nlmsg_data(nlh);
	/* copy data from selector, dir, and type to the pol_id */
	स_रखो(pol_id, 0, माप(*pol_id));
	स_नकल(&pol_id->sel, sel, माप(pol_id->sel));
	pol_id->dir = dir;

	अगर (k != शून्य) अणु
		err = copy_to_user_kmaddress(k, skb);
		अगर (err)
			जाओ out_cancel;
	पूर्ण
	अगर (encap) अणु
		err = nla_put(skb, XFRMA_ENCAP, माप(*encap), encap);
		अगर (err)
			जाओ out_cancel;
	पूर्ण
	err = copy_to_user_policy_type(type, skb);
	अगर (err)
		जाओ out_cancel;
	क्रम (i = 0, mp = m ; i < num_migrate; i++, mp++) अणु
		err = copy_to_user_migrate(mp, skb);
		अगर (err)
			जाओ out_cancel;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;

out_cancel:
	nlmsg_cancel(skb, nlh);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_send_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
			     स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_migrate,
			     स्थिर काष्ठा xfrm_kmaddress *k,
			     स्थिर काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	काष्ठा net *net = &init_net;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(xfrm_migrate_msgsize(num_migrate, !!k, !!encap),
			GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	/* build migrate */
	err = build_migrate(skb, m, num_migrate, k, sel, encap, dir, type);
	BUG_ON(err < 0);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_MIGRATE);
पूर्ण
#अन्यथा
अटल पूर्णांक xfrm_send_migrate(स्थिर काष्ठा xfrm_selector *sel, u8 dir, u8 type,
			     स्थिर काष्ठा xfrm_migrate *m, पूर्णांक num_migrate,
			     स्थिर काष्ठा xfrm_kmaddress *k,
			     स्थिर काष्ठा xfrm_encap_पंचांगpl *encap)
अणु
	वापस -ENOPROTOOPT;
पूर्ण
#पूर्ण_अगर

#घोषणा XMSGSIZE(type) माप(काष्ठा type)

स्थिर पूर्णांक xfrm_msg_min[XFRM_NR_MSGTYPES] = अणु
	[XFRM_MSG_NEWSA       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_info),
	[XFRM_MSG_DELSA       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_id),
	[XFRM_MSG_GETSA       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_id),
	[XFRM_MSG_NEWPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_info),
	[XFRM_MSG_DELPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_id),
	[XFRM_MSG_GETPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_id),
	[XFRM_MSG_ALLOCSPI    - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userspi_info),
	[XFRM_MSG_ACQUIRE     - XFRM_MSG_BASE] = XMSGSIZE(xfrm_user_acquire),
	[XFRM_MSG_EXPIRE      - XFRM_MSG_BASE] = XMSGSIZE(xfrm_user_expire),
	[XFRM_MSG_UPDPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_info),
	[XFRM_MSG_UPDSA       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_info),
	[XFRM_MSG_POLEXPIRE   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_user_polexpire),
	[XFRM_MSG_FLUSHSA     - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_flush),
	[XFRM_MSG_FLUSHPOLICY - XFRM_MSG_BASE] = 0,
	[XFRM_MSG_NEWAE       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_aevent_id),
	[XFRM_MSG_GETAE       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_aevent_id),
	[XFRM_MSG_REPORT      - XFRM_MSG_BASE] = XMSGSIZE(xfrm_user_report),
	[XFRM_MSG_MIGRATE     - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_id),
	[XFRM_MSG_GETSADINFO  - XFRM_MSG_BASE] = माप(u32),
	[XFRM_MSG_NEWSPDINFO  - XFRM_MSG_BASE] = माप(u32),
	[XFRM_MSG_GETSPDINFO  - XFRM_MSG_BASE] = माप(u32),
पूर्ण;
EXPORT_SYMBOL_GPL(xfrm_msg_min);

#अघोषित XMSGSIZE

स्थिर काष्ठा nla_policy xfrma_policy[XFRMA_MAX+1] = अणु
	[XFRMA_SA]		= अणु .len = माप(काष्ठा xfrm_usersa_info)पूर्ण,
	[XFRMA_POLICY]		= अणु .len = माप(काष्ठा xfrm_userpolicy_info)पूर्ण,
	[XFRMA_LASTUSED]	= अणु .type = NLA_U64पूर्ण,
	[XFRMA_ALG_AUTH_TRUNC]	= अणु .len = माप(काष्ठा xfrm_algo_auth)पूर्ण,
	[XFRMA_ALG_AEAD]	= अणु .len = माप(काष्ठा xfrm_algo_aead) पूर्ण,
	[XFRMA_ALG_AUTH]	= अणु .len = माप(काष्ठा xfrm_algo) पूर्ण,
	[XFRMA_ALG_CRYPT]	= अणु .len = माप(काष्ठा xfrm_algo) पूर्ण,
	[XFRMA_ALG_COMP]	= अणु .len = माप(काष्ठा xfrm_algo) पूर्ण,
	[XFRMA_ENCAP]		= अणु .len = माप(काष्ठा xfrm_encap_पंचांगpl) पूर्ण,
	[XFRMA_TMPL]		= अणु .len = माप(काष्ठा xfrm_user_पंचांगpl) पूर्ण,
	[XFRMA_SEC_CTX]		= अणु .len = माप(काष्ठा xfrm_sec_ctx) पूर्ण,
	[XFRMA_LTIME_VAL]	= अणु .len = माप(काष्ठा xfrm_lअगरeसमय_cur) पूर्ण,
	[XFRMA_REPLAY_VAL]	= अणु .len = माप(काष्ठा xfrm_replay_state) पूर्ण,
	[XFRMA_REPLAY_THRESH]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_ETIMER_THRESH]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_SRCADDR]		= अणु .len = माप(xfrm_address_t) पूर्ण,
	[XFRMA_COADDR]		= अणु .len = माप(xfrm_address_t) पूर्ण,
	[XFRMA_POLICY_TYPE]	= अणु .len = माप(काष्ठा xfrm_userpolicy_type)पूर्ण,
	[XFRMA_MIGRATE]		= अणु .len = माप(काष्ठा xfrm_user_migrate) पूर्ण,
	[XFRMA_KMADDRESS]	= अणु .len = माप(काष्ठा xfrm_user_kmaddress) पूर्ण,
	[XFRMA_MARK]		= अणु .len = माप(काष्ठा xfrm_mark) पूर्ण,
	[XFRMA_TFCPAD]		= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_REPLAY_ESN_VAL]	= अणु .len = माप(काष्ठा xfrm_replay_state_esn) पूर्ण,
	[XFRMA_SA_EXTRA_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_PROTO]		= अणु .type = NLA_U8 पूर्ण,
	[XFRMA_ADDRESS_FILTER]	= अणु .len = माप(काष्ठा xfrm_address_filter) पूर्ण,
	[XFRMA_OFFLOAD_DEV]	= अणु .len = माप(काष्ठा xfrm_user_offload) पूर्ण,
	[XFRMA_SET_MARK]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_SET_MARK_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_IF_ID]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(xfrma_policy);

अटल स्थिर काष्ठा nla_policy xfrma_spd_policy[XFRMA_SPD_MAX+1] = अणु
	[XFRMA_SPD_IPV4_HTHRESH] = अणु .len = माप(काष्ठा xfrmu_spdhthresh) पूर्ण,
	[XFRMA_SPD_IPV6_HTHRESH] = अणु .len = माप(काष्ठा xfrmu_spdhthresh) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा xfrm_link अणु
	पूर्णांक (*करोit)(काष्ठा sk_buff *, काष्ठा nlmsghdr *, काष्ठा nlattr **);
	पूर्णांक (*start)(काष्ठा netlink_callback *);
	पूर्णांक (*dump)(काष्ठा sk_buff *, काष्ठा netlink_callback *);
	पूर्णांक (*करोne)(काष्ठा netlink_callback *);
	स्थिर काष्ठा nla_policy *nla_pol;
	पूर्णांक nla_max;
पूर्ण xfrm_dispatch[XFRM_NR_MSGTYPES] = अणु
	[XFRM_MSG_NEWSA       - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_sa        पूर्ण,
	[XFRM_MSG_DELSA       - XFRM_MSG_BASE] = अणु .करोit = xfrm_del_sa        पूर्ण,
	[XFRM_MSG_GETSA       - XFRM_MSG_BASE] = अणु .करोit = xfrm_get_sa,
						   .dump = xfrm_dump_sa,
						   .करोne = xfrm_dump_sa_करोne  पूर्ण,
	[XFRM_MSG_NEWPOLICY   - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_policy    पूर्ण,
	[XFRM_MSG_DELPOLICY   - XFRM_MSG_BASE] = अणु .करोit = xfrm_get_policy    पूर्ण,
	[XFRM_MSG_GETPOLICY   - XFRM_MSG_BASE] = अणु .करोit = xfrm_get_policy,
						   .start = xfrm_dump_policy_start,
						   .dump = xfrm_dump_policy,
						   .करोne = xfrm_dump_policy_करोne पूर्ण,
	[XFRM_MSG_ALLOCSPI    - XFRM_MSG_BASE] = अणु .करोit = xfrm_alloc_userspi पूर्ण,
	[XFRM_MSG_ACQUIRE     - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_acquire   पूर्ण,
	[XFRM_MSG_EXPIRE      - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_sa_expire पूर्ण,
	[XFRM_MSG_UPDPOLICY   - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_policy    पूर्ण,
	[XFRM_MSG_UPDSA       - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_sa        पूर्ण,
	[XFRM_MSG_POLEXPIRE   - XFRM_MSG_BASE] = अणु .करोit = xfrm_add_pol_expireपूर्ण,
	[XFRM_MSG_FLUSHSA     - XFRM_MSG_BASE] = अणु .करोit = xfrm_flush_sa      पूर्ण,
	[XFRM_MSG_FLUSHPOLICY - XFRM_MSG_BASE] = अणु .करोit = xfrm_flush_policy  पूर्ण,
	[XFRM_MSG_NEWAE       - XFRM_MSG_BASE] = अणु .करोit = xfrm_new_ae  पूर्ण,
	[XFRM_MSG_GETAE       - XFRM_MSG_BASE] = अणु .करोit = xfrm_get_ae  पूर्ण,
	[XFRM_MSG_MIGRATE     - XFRM_MSG_BASE] = अणु .करोit = xfrm_करो_migrate    पूर्ण,
	[XFRM_MSG_GETSADINFO  - XFRM_MSG_BASE] = अणु .करोit = xfrm_get_sadinfo   पूर्ण,
	[XFRM_MSG_NEWSPDINFO  - XFRM_MSG_BASE] = अणु .करोit = xfrm_set_spdinfo,
						   .nla_pol = xfrma_spd_policy,
						   .nla_max = XFRMA_SPD_MAX पूर्ण,
	[XFRM_MSG_GETSPDINFO  - XFRM_MSG_BASE] = अणु .करोit = xfrm_get_spdinfo   पूर्ण,
पूर्ण;

अटल पूर्णांक xfrm_user_rcv_msg(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *attrs[XFRMA_MAX+1];
	स्थिर काष्ठा xfrm_link *link;
	काष्ठा nlmsghdr *nlh64 = शून्य;
	पूर्णांक type, err;

	type = nlh->nlmsg_type;
	अगर (type > XFRM_MSG_MAX)
		वापस -EINVAL;

	type -= XFRM_MSG_BASE;
	link = &xfrm_dispatch[type];

	/* All operations require privileges, even GET */
	अगर (!netlink_net_capable(skb, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (in_compat_syscall()) अणु
		काष्ठा xfrm_translator *xtr = xfrm_get_translator();

		अगर (!xtr)
			वापस -EOPNOTSUPP;

		nlh64 = xtr->rcv_msg_compat(nlh, link->nla_max,
					    link->nla_pol, extack);
		xfrm_put_translator(xtr);
		अगर (IS_ERR(nlh64))
			वापस PTR_ERR(nlh64);
		अगर (nlh64)
			nlh = nlh64;
	पूर्ण

	अगर ((type == (XFRM_MSG_GETSA - XFRM_MSG_BASE) ||
	     type == (XFRM_MSG_GETPOLICY - XFRM_MSG_BASE)) &&
	    (nlh->nlmsg_flags & NLM_F_DUMP)) अणु
		काष्ठा netlink_dump_control c = अणु
			.start = link->start,
			.dump = link->dump,
			.करोne = link->करोne,
		पूर्ण;

		अगर (link->dump == शून्य) अणु
			err = -EINVAL;
			जाओ err;
		पूर्ण

		err = netlink_dump_start(net->xfrm.nlsk, skb, nlh, &c);
		जाओ err;
	पूर्ण

	err = nlmsg_parse_deprecated(nlh, xfrm_msg_min[type], attrs,
				     link->nla_max ? : XFRMA_MAX,
				     link->nla_pol ? : xfrma_policy, extack);
	अगर (err < 0)
		जाओ err;

	अगर (link->करोit == शून्य) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = link->करोit(skb, nlh, attrs);

err:
	kvमुक्त(nlh64);
	वापस err;
पूर्ण

अटल व्योम xfrm_netlink_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = sock_net(skb->sk);

	mutex_lock(&net->xfrm.xfrm_cfg_mutex);
	netlink_rcv_skb(skb, &xfrm_user_rcv_msg);
	mutex_unlock(&net->xfrm.xfrm_cfg_mutex);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_expire_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_user_expire))
	       + nla_total_size(माप(काष्ठा xfrm_mark));
पूर्ण

अटल पूर्णांक build_expire(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा xfrm_user_expire *ue;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put(skb, c->portid, 0, XFRM_MSG_EXPIRE, माप(*ue), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ue = nlmsg_data(nlh);
	copy_to_user_state(x, &ue->state);
	ue->hard = (c->data.hard != 0) ? 1 : 0;
	/* clear the padding bytes */
	स_रखो(&ue->hard + 1, 0, माप(*ue) - दुरत्वend(typeof(*ue), hard));

	err = xfrm_mark_put(skb, &x->mark);
	अगर (err)
		वापस err;

	err = xfrm_अगर_id_put(skb, x->अगर_id);
	अगर (err)
		वापस err;

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_exp_state_notअगरy(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा sk_buff *skb;

	skb = nlmsg_new(xfrm_expire_msgsize(), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	अगर (build_expire(skb, x, c) < 0) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_EXPIRE);
पूर्ण

अटल पूर्णांक xfrm_aevent_state_notअगरy(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(xfrm_aevent_msgsize(x), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	err = build_aevent(skb, x, c);
	BUG_ON(err < 0);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_AEVENTS);
पूर्ण

अटल पूर्णांक xfrm_notअगरy_sa_flush(स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = c->net;
	काष्ठा xfrm_usersa_flush *p;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	पूर्णांक len = NLMSG_ALIGN(माप(काष्ठा xfrm_usersa_flush));

	skb = nlmsg_new(len, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, XFRM_MSG_FLUSHSA, माप(*p), 0);
	अगर (nlh == शून्य) अणु
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण

	p = nlmsg_data(nlh);
	p->proto = c->data.proto;

	nlmsg_end(skb, nlh);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_SA);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_sa_len(काष्ठा xfrm_state *x)
अणु
	अचिन्हित पूर्णांक l = 0;
	अगर (x->aead)
		l += nla_total_size(aead_len(x->aead));
	अगर (x->aalg) अणु
		l += nla_total_size(माप(काष्ठा xfrm_algo) +
				    (x->aalg->alg_key_len + 7) / 8);
		l += nla_total_size(xfrm_alg_auth_len(x->aalg));
	पूर्ण
	अगर (x->ealg)
		l += nla_total_size(xfrm_alg_len(x->ealg));
	अगर (x->calg)
		l += nla_total_size(माप(*x->calg));
	अगर (x->encap)
		l += nla_total_size(माप(*x->encap));
	अगर (x->tfcpad)
		l += nla_total_size(माप(x->tfcpad));
	अगर (x->replay_esn)
		l += nla_total_size(xfrm_replay_state_esn_len(x->replay_esn));
	अन्यथा
		l += nla_total_size(माप(काष्ठा xfrm_replay_state));
	अगर (x->security)
		l += nla_total_size(माप(काष्ठा xfrm_user_sec_ctx) +
				    x->security->ctx_len);
	अगर (x->coaddr)
		l += nla_total_size(माप(*x->coaddr));
	अगर (x->props.extra_flags)
		l += nla_total_size(माप(x->props.extra_flags));
	अगर (x->xso.dev)
		 l += nla_total_size(माप(x->xso));
	अगर (x->props.smark.v | x->props.smark.m) अणु
		l += nla_total_size(माप(x->props.smark.v));
		l += nla_total_size(माप(x->props.smark.m));
	पूर्ण
	अगर (x->अगर_id)
		l += nla_total_size(माप(x->अगर_id));

	/* Must count x->lastused as it may become non-zero behind our back. */
	l += nla_total_size_64bit(माप(u64));

	वापस l;
पूर्ण

अटल पूर्णांक xfrm_notअगरy_sa(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा xfrm_usersa_info *p;
	काष्ठा xfrm_usersa_id *id;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len = xfrm_sa_len(x);
	अचिन्हित पूर्णांक headlen;
	पूर्णांक err;

	headlen = माप(*p);
	अगर (c->event == XFRM_MSG_DELSA) अणु
		len += nla_total_size(headlen);
		headlen = माप(*id);
		len += nla_total_size(माप(काष्ठा xfrm_mark));
	पूर्ण
	len += NLMSG_ALIGN(headlen);

	skb = nlmsg_new(len, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, c->event, headlen, 0);
	err = -EMSGSIZE;
	अगर (nlh == शून्य)
		जाओ out_मुक्त_skb;

	p = nlmsg_data(nlh);
	अगर (c->event == XFRM_MSG_DELSA) अणु
		काष्ठा nlattr *attr;

		id = nlmsg_data(nlh);
		स_रखो(id, 0, माप(*id));
		स_नकल(&id->daddr, &x->id.daddr, माप(id->daddr));
		id->spi = x->id.spi;
		id->family = x->props.family;
		id->proto = x->id.proto;

		attr = nla_reserve(skb, XFRMA_SA, माप(*p));
		err = -EMSGSIZE;
		अगर (attr == शून्य)
			जाओ out_मुक्त_skb;

		p = nla_data(attr);
	पूर्ण
	err = copy_to_user_state_extra(x, p, skb);
	अगर (err)
		जाओ out_मुक्त_skb;

	nlmsg_end(skb, nlh);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_SA);

out_मुक्त_skb:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_send_state_notअगरy(काष्ठा xfrm_state *x, स्थिर काष्ठा km_event *c)
अणु

	चयन (c->event) अणु
	हाल XFRM_MSG_EXPIRE:
		वापस xfrm_exp_state_notअगरy(x, c);
	हाल XFRM_MSG_NEWAE:
		वापस xfrm_aevent_state_notअगरy(x, c);
	हाल XFRM_MSG_DELSA:
	हाल XFRM_MSG_UPDSA:
	हाल XFRM_MSG_NEWSA:
		वापस xfrm_notअगरy_sa(x, c);
	हाल XFRM_MSG_FLUSHSA:
		वापस xfrm_notअगरy_sa_flush(c);
	शेष:
		prपूर्णांकk(KERN_NOTICE "xfrm_user: Unknown SA event %d\n",
		       c->event);
		अवरोध;
	पूर्ण

	वापस 0;

पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_acquire_msgsize(काष्ठा xfrm_state *x,
						काष्ठा xfrm_policy *xp)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_user_acquire))
	       + nla_total_size(माप(काष्ठा xfrm_user_पंचांगpl) * xp->xfrm_nr)
	       + nla_total_size(माप(काष्ठा xfrm_mark))
	       + nla_total_size(xfrm_user_sec_ctx_size(x->security))
	       + userpolicy_type_attrsize();
पूर्ण

अटल पूर्णांक build_acquire(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			 काष्ठा xfrm_पंचांगpl *xt, काष्ठा xfrm_policy *xp)
अणु
	__u32 seq = xfrm_get_acqseq();
	काष्ठा xfrm_user_acquire *ua;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_ACQUIRE, माप(*ua), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ua = nlmsg_data(nlh);
	स_नकल(&ua->id, &x->id, माप(ua->id));
	स_नकल(&ua->saddr, &x->props.saddr, माप(ua->saddr));
	स_नकल(&ua->sel, &x->sel, माप(ua->sel));
	copy_to_user_policy(xp, &ua->policy, XFRM_POLICY_OUT);
	ua->aalgos = xt->aalgos;
	ua->ealgos = xt->ealgos;
	ua->calgos = xt->calgos;
	ua->seq = x->km.seq = seq;

	err = copy_to_user_पंचांगpl(xp, skb);
	अगर (!err)
		err = copy_to_user_state_sec_ctx(x, skb);
	अगर (!err)
		err = copy_to_user_policy_type(xp->type, skb);
	अगर (!err)
		err = xfrm_mark_put(skb, &xp->mark);
	अगर (!err)
		err = xfrm_अगर_id_put(skb, xp->अगर_id);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_send_acquire(काष्ठा xfrm_state *x, काष्ठा xfrm_पंचांगpl *xt,
			     काष्ठा xfrm_policy *xp)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(xfrm_acquire_msgsize(x, xp), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	err = build_acquire(skb, x, xt, xp);
	BUG_ON(err < 0);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_ACQUIRE);
पूर्ण

/* User gives us xfrm_user_policy_info followed by an array of 0
 * or more ढाँचाs.
 */
अटल काष्ठा xfrm_policy *xfrm_compile_policy(काष्ठा sock *sk, पूर्णांक opt,
					       u8 *data, पूर्णांक len, पूर्णांक *dir)
अणु
	काष्ठा net *net = sock_net(sk);
	काष्ठा xfrm_userpolicy_info *p = (काष्ठा xfrm_userpolicy_info *)data;
	काष्ठा xfrm_user_पंचांगpl *ut = (काष्ठा xfrm_user_पंचांगpl *) (p + 1);
	काष्ठा xfrm_policy *xp;
	पूर्णांक nr;

	चयन (sk->sk_family) अणु
	हाल AF_INET:
		अगर (opt != IP_XFRM_POLICY) अणु
			*dir = -EOPNOTSUPP;
			वापस शून्य;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (opt != IPV6_XFRM_POLICY) अणु
			*dir = -EOPNOTSUPP;
			वापस शून्य;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		*dir = -EINVAL;
		वापस शून्य;
	पूर्ण

	*dir = -EINVAL;

	अगर (len < माप(*p) ||
	    verअगरy_newpolicy_info(p))
		वापस शून्य;

	nr = ((len - माप(*p)) / माप(*ut));
	अगर (validate_पंचांगpl(nr, ut, p->sel.family))
		वापस शून्य;

	अगर (p->dir > XFRM_POLICY_OUT)
		वापस शून्य;

	xp = xfrm_policy_alloc(net, GFP_ATOMIC);
	अगर (xp == शून्य) अणु
		*dir = -ENOBUFS;
		वापस शून्य;
	पूर्ण

	copy_from_user_policy(xp, p);
	xp->type = XFRM_POLICY_TYPE_MAIN;
	copy_ढाँचाs(xp, ut, nr);

	*dir = p->dir;

	वापस xp;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_polexpire_msgsize(काष्ठा xfrm_policy *xp)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_user_polexpire))
	       + nla_total_size(माप(काष्ठा xfrm_user_पंचांगpl) * xp->xfrm_nr)
	       + nla_total_size(xfrm_user_sec_ctx_size(xp->security))
	       + nla_total_size(माप(काष्ठा xfrm_mark))
	       + userpolicy_type_attrsize();
पूर्ण

अटल पूर्णांक build_polexpire(काष्ठा sk_buff *skb, काष्ठा xfrm_policy *xp,
			   पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा xfrm_user_polexpire *upe;
	पूर्णांक hard = c->data.hard;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	nlh = nlmsg_put(skb, c->portid, 0, XFRM_MSG_POLEXPIRE, माप(*upe), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	upe = nlmsg_data(nlh);
	copy_to_user_policy(xp, &upe->pol, dir);
	err = copy_to_user_पंचांगpl(xp, skb);
	अगर (!err)
		err = copy_to_user_sec_ctx(xp, skb);
	अगर (!err)
		err = copy_to_user_policy_type(xp->type, skb);
	अगर (!err)
		err = xfrm_mark_put(skb, &xp->mark);
	अगर (!err)
		err = xfrm_अगर_id_put(skb, xp->अगर_id);
	अगर (err) अणु
		nlmsg_cancel(skb, nlh);
		वापस err;
	पूर्ण
	upe->hard = !!hard;

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_exp_policy_notअगरy(काष्ठा xfrm_policy *xp, पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = xp_net(xp);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(xfrm_polexpire_msgsize(xp), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	err = build_polexpire(skb, xp, dir, c);
	BUG_ON(err < 0);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_EXPIRE);
पूर्ण

अटल पूर्णांक xfrm_notअगरy_policy(काष्ठा xfrm_policy *xp, पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु
	अचिन्हित पूर्णांक len = nla_total_size(माप(काष्ठा xfrm_user_पंचांगpl) * xp->xfrm_nr);
	काष्ठा net *net = xp_net(xp);
	काष्ठा xfrm_userpolicy_info *p;
	काष्ठा xfrm_userpolicy_id *id;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक headlen;
	पूर्णांक err;

	headlen = माप(*p);
	अगर (c->event == XFRM_MSG_DELPOLICY) अणु
		len += nla_total_size(headlen);
		headlen = माप(*id);
	पूर्ण
	len += userpolicy_type_attrsize();
	len += nla_total_size(माप(काष्ठा xfrm_mark));
	len += NLMSG_ALIGN(headlen);

	skb = nlmsg_new(len, GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, c->event, headlen, 0);
	err = -EMSGSIZE;
	अगर (nlh == शून्य)
		जाओ out_मुक्त_skb;

	p = nlmsg_data(nlh);
	अगर (c->event == XFRM_MSG_DELPOLICY) अणु
		काष्ठा nlattr *attr;

		id = nlmsg_data(nlh);
		स_रखो(id, 0, माप(*id));
		id->dir = dir;
		अगर (c->data.byid)
			id->index = xp->index;
		अन्यथा
			स_नकल(&id->sel, &xp->selector, माप(id->sel));

		attr = nla_reserve(skb, XFRMA_POLICY, माप(*p));
		err = -EMSGSIZE;
		अगर (attr == शून्य)
			जाओ out_मुक्त_skb;

		p = nla_data(attr);
	पूर्ण

	copy_to_user_policy(xp, p, dir);
	err = copy_to_user_पंचांगpl(xp, skb);
	अगर (!err)
		err = copy_to_user_policy_type(xp->type, skb);
	अगर (!err)
		err = xfrm_mark_put(skb, &xp->mark);
	अगर (!err)
		err = xfrm_अगर_id_put(skb, xp->अगर_id);
	अगर (err)
		जाओ out_मुक्त_skb;

	nlmsg_end(skb, nlh);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_POLICY);

out_मुक्त_skb:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_notअगरy_policy_flush(स्थिर काष्ठा km_event *c)
अणु
	काष्ठा net *net = c->net;
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(userpolicy_type_attrsize(), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	nlh = nlmsg_put(skb, c->portid, c->seq, XFRM_MSG_FLUSHPOLICY, 0, 0);
	err = -EMSGSIZE;
	अगर (nlh == शून्य)
		जाओ out_मुक्त_skb;
	err = copy_to_user_policy_type(c->data.type, skb);
	अगर (err)
		जाओ out_मुक्त_skb;

	nlmsg_end(skb, nlh);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_POLICY);

out_मुक्त_skb:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक xfrm_send_policy_notअगरy(काष्ठा xfrm_policy *xp, पूर्णांक dir, स्थिर काष्ठा km_event *c)
अणु

	चयन (c->event) अणु
	हाल XFRM_MSG_NEWPOLICY:
	हाल XFRM_MSG_UPDPOLICY:
	हाल XFRM_MSG_DELPOLICY:
		वापस xfrm_notअगरy_policy(xp, dir, c);
	हाल XFRM_MSG_FLUSHPOLICY:
		वापस xfrm_notअगरy_policy_flush(c);
	हाल XFRM_MSG_POLEXPIRE:
		वापस xfrm_exp_policy_notअगरy(xp, dir, c);
	शेष:
		prपूर्णांकk(KERN_NOTICE "xfrm_user: Unknown Policy event %d\n",
		       c->event);
	पूर्ण

	वापस 0;

पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_report_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_user_report));
पूर्ण

अटल पूर्णांक build_report(काष्ठा sk_buff *skb, u8 proto,
			काष्ठा xfrm_selector *sel, xfrm_address_t *addr)
अणु
	काष्ठा xfrm_user_report *ur;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_REPORT, माप(*ur), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	ur = nlmsg_data(nlh);
	ur->proto = proto;
	स_नकल(&ur->sel, sel, माप(ur->sel));

	अगर (addr) अणु
		पूर्णांक err = nla_put(skb, XFRMA_COADDR, माप(*addr), addr);
		अगर (err) अणु
			nlmsg_cancel(skb, nlh);
			वापस err;
		पूर्ण
	पूर्ण
	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_send_report(काष्ठा net *net, u8 proto,
			    काष्ठा xfrm_selector *sel, xfrm_address_t *addr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = nlmsg_new(xfrm_report_msgsize(), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	err = build_report(skb, proto, sel, addr);
	BUG_ON(err < 0);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_REPORT);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xfrm_mapping_msgsize(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा xfrm_user_mapping));
पूर्ण

अटल पूर्णांक build_mapping(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x,
			 xfrm_address_t *new_saddr, __be16 new_sport)
अणु
	काष्ठा xfrm_user_mapping *um;
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put(skb, 0, 0, XFRM_MSG_MAPPING, माप(*um), 0);
	अगर (nlh == शून्य)
		वापस -EMSGSIZE;

	um = nlmsg_data(nlh);

	स_नकल(&um->id.daddr, &x->id.daddr, माप(um->id.daddr));
	um->id.spi = x->id.spi;
	um->id.family = x->props.family;
	um->id.proto = x->id.proto;
	स_नकल(&um->new_saddr, new_saddr, माप(um->new_saddr));
	स_नकल(&um->old_saddr, &x->props.saddr, माप(um->old_saddr));
	um->new_sport = new_sport;
	um->old_sport = x->encap->encap_sport;
	um->reqid = x->props.reqid;

	nlmsg_end(skb, nlh);
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_send_mapping(काष्ठा xfrm_state *x, xfrm_address_t *ipaddr,
			     __be16 sport)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (x->id.proto != IPPROTO_ESP)
		वापस -EINVAL;

	अगर (!x->encap)
		वापस -EINVAL;

	skb = nlmsg_new(xfrm_mapping_msgsize(), GFP_ATOMIC);
	अगर (skb == शून्य)
		वापस -ENOMEM;

	err = build_mapping(skb, x, ipaddr, sport);
	BUG_ON(err < 0);

	वापस xfrm_nlmsg_multicast(net, skb, 0, XFRMNLGRP_MAPPING);
पूर्ण

अटल bool xfrm_is_alive(स्थिर काष्ठा km_event *c)
अणु
	वापस (bool)xfrm_acquire_is_on(c->net);
पूर्ण

अटल काष्ठा xfrm_mgr netlink_mgr = अणु
	.notअगरy		= xfrm_send_state_notअगरy,
	.acquire	= xfrm_send_acquire,
	.compile_policy	= xfrm_compile_policy,
	.notअगरy_policy	= xfrm_send_policy_notअगरy,
	.report		= xfrm_send_report,
	.migrate	= xfrm_send_migrate,
	.new_mapping	= xfrm_send_mapping,
	.is_alive	= xfrm_is_alive,
पूर्ण;

अटल पूर्णांक __net_init xfrm_user_net_init(काष्ठा net *net)
अणु
	काष्ठा sock *nlsk;
	काष्ठा netlink_kernel_cfg cfg = अणु
		.groups	= XFRMNLGRP_MAX,
		.input	= xfrm_netlink_rcv,
	पूर्ण;

	nlsk = netlink_kernel_create(net, NETLINK_XFRM, &cfg);
	अगर (nlsk == शून्य)
		वापस -ENOMEM;
	net->xfrm.nlsk_stash = nlsk; /* Don't set to शून्य */
	rcu_assign_poपूर्णांकer(net->xfrm.nlsk, nlsk);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास xfrm_user_net_pre_निकास(काष्ठा net *net)
अणु
	RCU_INIT_POINTER(net->xfrm.nlsk, शून्य);
पूर्ण

अटल व्योम __net_निकास xfrm_user_net_निकास(काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;

	list_क्रम_each_entry(net, net_निकास_list, निकास_list)
		netlink_kernel_release(net->xfrm.nlsk_stash);
पूर्ण

अटल काष्ठा pernet_operations xfrm_user_net_ops = अणु
	.init	    = xfrm_user_net_init,
	.pre_निकास   = xfrm_user_net_pre_निकास,
	.निकास_batch = xfrm_user_net_निकास,
पूर्ण;

अटल पूर्णांक __init xfrm_user_init(व्योम)
अणु
	पूर्णांक rv;

	prपूर्णांकk(KERN_INFO "Initializing XFRM netlink socket\n");

	rv = रेजिस्टर_pernet_subsys(&xfrm_user_net_ops);
	अगर (rv < 0)
		वापस rv;
	rv = xfrm_रेजिस्टर_km(&netlink_mgr);
	अगर (rv < 0)
		unरेजिस्टर_pernet_subsys(&xfrm_user_net_ops);
	वापस rv;
पूर्ण

अटल व्योम __निकास xfrm_user_निकास(व्योम)
अणु
	xfrm_unरेजिस्टर_km(&netlink_mgr);
	unरेजिस्टर_pernet_subsys(&xfrm_user_net_ops);
पूर्ण

module_init(xfrm_user_init);
module_निकास(xfrm_user_निकास);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NET_PF_PROTO(PF_NETLINK, NETLINK_XFRM);
