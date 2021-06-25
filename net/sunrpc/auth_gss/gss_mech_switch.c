<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/*
 *  linux/net/sunrpc/gss_mech_चयन.c
 *
 *  Copyright (c) 2001 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  J. Bruce Fields   <bfields@umich.edu>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/oid_registry.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/sunrpc/gss_asn1.h>
#समावेश <linux/sunrpc/auth_gss.h>
#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश <linux/sunrpc/gss_err.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <trace/events/rpcgss.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर

अटल LIST_HEAD(रेजिस्टरed_mechs);
अटल DEFINE_SPINLOCK(रेजिस्टरed_mechs_lock);

अटल व्योम
gss_mech_मुक्त(काष्ठा gss_api_mech *gm)
अणु
	काष्ठा pf_desc *pf;
	पूर्णांक i;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		pf = &gm->gm_pfs[i];
		अगर (pf->करोमुख्य)
			auth_करोमुख्य_put(pf->करोमुख्य);
		kमुक्त(pf->auth_करोमुख्य_name);
		pf->auth_करोमुख्य_name = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत अक्षर *
make_auth_करोमुख्य_name(अक्षर *name)
अणु
	अटल अक्षर	*prefix = "gss/";
	अक्षर		*new;

	new = kदो_स्मृति(म_माप(name) + म_माप(prefix) + 1, GFP_KERNEL);
	अगर (new) अणु
		म_नकल(new, prefix);
		म_जोड़ो(new, name);
	पूर्ण
	वापस new;
पूर्ण

अटल पूर्णांक
gss_mech_svc_setup(काष्ठा gss_api_mech *gm)
अणु
	काष्ठा auth_करोमुख्य *करोm;
	काष्ठा pf_desc *pf;
	पूर्णांक i, status;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		pf = &gm->gm_pfs[i];
		pf->auth_करोमुख्य_name = make_auth_करोमुख्य_name(pf->name);
		status = -ENOMEM;
		अगर (pf->auth_करोमुख्य_name == शून्य)
			जाओ out;
		करोm = svcauth_gss_रेजिस्टर_pseuकरोflavor(
			pf->pseuकरोflavor, pf->auth_करोमुख्य_name);
		अगर (IS_ERR(करोm)) अणु
			status = PTR_ERR(करोm);
			जाओ out;
		पूर्ण
		pf->करोमुख्य = करोm;
	पूर्ण
	वापस 0;
out:
	gss_mech_मुक्त(gm);
	वापस status;
पूर्ण

/**
 * gss_mech_रेजिस्टर - रेजिस्टर a GSS mechanism
 * @gm: GSS mechanism handle
 *
 * Returns zero अगर successful, or a negative त्रुटि_सं.
 */
पूर्णांक gss_mech_रेजिस्टर(काष्ठा gss_api_mech *gm)
अणु
	पूर्णांक status;

	status = gss_mech_svc_setup(gm);
	अगर (status)
		वापस status;
	spin_lock(&रेजिस्टरed_mechs_lock);
	list_add_rcu(&gm->gm_list, &रेजिस्टरed_mechs);
	spin_unlock(&रेजिस्टरed_mechs_lock);
	dprपूर्णांकk("RPC:       registered gss mechanism %s\n", gm->gm_name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gss_mech_रेजिस्टर);

/**
 * gss_mech_unरेजिस्टर - release a GSS mechanism
 * @gm: GSS mechanism handle
 *
 */
व्योम gss_mech_unरेजिस्टर(काष्ठा gss_api_mech *gm)
अणु
	spin_lock(&रेजिस्टरed_mechs_lock);
	list_del_rcu(&gm->gm_list);
	spin_unlock(&रेजिस्टरed_mechs_lock);
	dprपूर्णांकk("RPC:       unregistered gss mechanism %s\n", gm->gm_name);
	gss_mech_मुक्त(gm);
पूर्ण
EXPORT_SYMBOL_GPL(gss_mech_unरेजिस्टर);

काष्ठा gss_api_mech *gss_mech_get(काष्ठा gss_api_mech *gm)
अणु
	__module_get(gm->gm_owner);
	वापस gm;
पूर्ण
EXPORT_SYMBOL(gss_mech_get);

अटल काष्ठा gss_api_mech *
_gss_mech_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा gss_api_mech	*pos, *gm = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pos, &रेजिस्टरed_mechs, gm_list) अणु
		अगर (0 == म_भेद(name, pos->gm_name)) अणु
			अगर (try_module_get(pos->gm_owner))
				gm = pos;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस gm;

पूर्ण

काष्ठा gss_api_mech * gss_mech_get_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा gss_api_mech *gm = शून्य;

	gm = _gss_mech_get_by_name(name);
	अगर (!gm) अणु
		request_module("rpc-auth-gss-%s", name);
		gm = _gss_mech_get_by_name(name);
	पूर्ण
	वापस gm;
पूर्ण

काष्ठा gss_api_mech *gss_mech_get_by_OID(काष्ठा rpcsec_gss_oid *obj)
अणु
	काष्ठा gss_api_mech	*pos, *gm = शून्य;
	अक्षर buf[32];

	अगर (sprपूर्णांक_oid(obj->data, obj->len, buf, माप(buf)) < 0)
		वापस शून्य;
	request_module("rpc-auth-gss-%s", buf);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pos, &रेजिस्टरed_mechs, gm_list) अणु
		अगर (obj->len == pos->gm_oid.len) अणु
			अगर (0 == स_भेद(obj->data, pos->gm_oid.data, obj->len)) अणु
				अगर (try_module_get(pos->gm_owner))
					gm = pos;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!gm)
		trace_rpcgss_oid_to_mech(buf);
	वापस gm;
पूर्ण

अटल अंतरभूत पूर्णांक
mech_supports_pseuकरोflavor(काष्ठा gss_api_mech *gm, u32 pseuकरोflavor)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		अगर (gm->gm_pfs[i].pseuकरोflavor == pseuकरोflavor)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा gss_api_mech *_gss_mech_get_by_pseuकरोflavor(u32 pseuकरोflavor)
अणु
	काष्ठा gss_api_mech *gm = शून्य, *pos;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pos, &रेजिस्टरed_mechs, gm_list) अणु
		अगर (!mech_supports_pseuकरोflavor(pos, pseuकरोflavor))
			जारी;
		अगर (try_module_get(pos->gm_owner))
			gm = pos;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस gm;
पूर्ण

काष्ठा gss_api_mech *
gss_mech_get_by_pseuकरोflavor(u32 pseuकरोflavor)
अणु
	काष्ठा gss_api_mech *gm;

	gm = _gss_mech_get_by_pseuकरोflavor(pseuकरोflavor);

	अगर (!gm) अणु
		request_module("rpc-auth-gss-%u", pseuकरोflavor);
		gm = _gss_mech_get_by_pseuकरोflavor(pseuकरोflavor);
	पूर्ण
	वापस gm;
पूर्ण

/**
 * gss_svc_to_pseuकरोflavor - map a GSS service number to a pseuकरोflavor
 * @gm: GSS mechanism handle
 * @qop: GSS quality-of-protection value
 * @service: GSS service value
 *
 * Returns a matching security flavor, or RPC_AUTH_MAXFLAVOR अगर none is found.
 */
rpc_authflavor_t gss_svc_to_pseuकरोflavor(काष्ठा gss_api_mech *gm, u32 qop,
					 u32 service)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		अगर (gm->gm_pfs[i].qop == qop &&
		    gm->gm_pfs[i].service == service) अणु
			वापस gm->gm_pfs[i].pseuकरोflavor;
		पूर्ण
	पूर्ण
	वापस RPC_AUTH_MAXFLAVOR;
पूर्ण

/**
 * gss_mech_info2flavor - look up a pseuकरोflavor given a GSS tuple
 * @info: a GSS mech OID, quality of protection, and service value
 *
 * Returns a matching pseuकरोflavor, or RPC_AUTH_MAXFLAVOR अगर the tuple is
 * not supported.
 */
rpc_authflavor_t gss_mech_info2flavor(काष्ठा rpcsec_gss_info *info)
अणु
	rpc_authflavor_t pseuकरोflavor;
	काष्ठा gss_api_mech *gm;

	gm = gss_mech_get_by_OID(&info->oid);
	अगर (gm == शून्य)
		वापस RPC_AUTH_MAXFLAVOR;

	pseuकरोflavor = gss_svc_to_pseuकरोflavor(gm, info->qop, info->service);

	gss_mech_put(gm);
	वापस pseuकरोflavor;
पूर्ण

/**
 * gss_mech_flavor2info - look up a GSS tuple क्रम a given pseuकरोflavor
 * @pseuकरोflavor: GSS pseuकरोflavor to match
 * @info: rpcsec_gss_info काष्ठाure to fill in
 *
 * Returns zero and fills in "info" अगर pseuकरोflavor matches a
 * supported mechanism.  Otherwise a negative त्रुटि_सं is वापसed.
 */
पूर्णांक gss_mech_flavor2info(rpc_authflavor_t pseuकरोflavor,
			 काष्ठा rpcsec_gss_info *info)
अणु
	काष्ठा gss_api_mech *gm;
	पूर्णांक i;

	gm = gss_mech_get_by_pseuकरोflavor(pseuकरोflavor);
	अगर (gm == शून्य)
		वापस -ENOENT;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		अगर (gm->gm_pfs[i].pseuकरोflavor == pseuकरोflavor) अणु
			स_नकल(info->oid.data, gm->gm_oid.data, gm->gm_oid.len);
			info->oid.len = gm->gm_oid.len;
			info->qop = gm->gm_pfs[i].qop;
			info->service = gm->gm_pfs[i].service;
			gss_mech_put(gm);
			वापस 0;
		पूर्ण
	पूर्ण

	gss_mech_put(gm);
	वापस -ENOENT;
पूर्ण

u32
gss_pseuकरोflavor_to_service(काष्ठा gss_api_mech *gm, u32 pseuकरोflavor)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		अगर (gm->gm_pfs[i].pseuकरोflavor == pseuकरोflavor)
			वापस gm->gm_pfs[i].service;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(gss_pseuकरोflavor_to_service);

bool
gss_pseuकरोflavor_to_datatouch(काष्ठा gss_api_mech *gm, u32 pseuकरोflavor)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		अगर (gm->gm_pfs[i].pseuकरोflavor == pseuकरोflavor)
			वापस gm->gm_pfs[i].datatouch;
	पूर्ण
	वापस false;
पूर्ण

अक्षर *
gss_service_to_auth_करोमुख्य_name(काष्ठा gss_api_mech *gm, u32 service)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gm->gm_pf_num; i++) अणु
		अगर (gm->gm_pfs[i].service == service)
			वापस gm->gm_pfs[i].auth_करोमुख्य_name;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम
gss_mech_put(काष्ठा gss_api_mech * gm)
अणु
	अगर (gm)
		module_put(gm->gm_owner);
पूर्ण
EXPORT_SYMBOL(gss_mech_put);

/* The mech could probably be determined from the token instead, but it's just
 * as easy क्रम now to pass it in. */
पूर्णांक
gss_import_sec_context(स्थिर व्योम *input_token, माप_प्रकार bufsize,
		       काष्ठा gss_api_mech	*mech,
		       काष्ठा gss_ctx		**ctx_id,
		       समय64_t			*endसमय,
		       gfp_t gfp_mask)
अणु
	अगर (!(*ctx_id = kzalloc(माप(**ctx_id), gfp_mask)))
		वापस -ENOMEM;
	(*ctx_id)->mech_type = gss_mech_get(mech);

	वापस mech->gm_ops->gss_import_sec_context(input_token, bufsize,
						*ctx_id, endसमय, gfp_mask);
पूर्ण

/* gss_get_mic: compute a mic over message and वापस mic_token. */

u32
gss_get_mic(काष्ठा gss_ctx	*context_handle,
	    काष्ठा xdr_buf	*message,
	    काष्ठा xdr_netobj	*mic_token)
अणु
	 वापस context_handle->mech_type->gm_ops
		->gss_get_mic(context_handle,
			      message,
			      mic_token);
पूर्ण

/* gss_verअगरy_mic: check whether the provided mic_token verअगरies message. */

u32
gss_verअगरy_mic(काष्ठा gss_ctx		*context_handle,
	       काष्ठा xdr_buf		*message,
	       काष्ठा xdr_netobj	*mic_token)
अणु
	वापस context_handle->mech_type->gm_ops
		->gss_verअगरy_mic(context_handle,
				 message,
				 mic_token);
पूर्ण

/*
 * This function is called from both the client and server code.
 * Each makes guarantees about how much "slack" space is available
 * क्रम the underlying function in "buf"'s head and tail जबतक
 * perक्रमming the wrap.
 *
 * The client and server code allocate RPC_MAX_AUTH_SIZE extra
 * space in both the head and tail which is available क्रम use by
 * the wrap function.
 *
 * Underlying functions should verअगरy they करो not use more than
 * RPC_MAX_AUTH_SIZE of extra space in either the head or tail
 * when perक्रमming the wrap.
 */
u32
gss_wrap(काष्ठा gss_ctx	*ctx_id,
	 पूर्णांक		offset,
	 काष्ठा xdr_buf	*buf,
	 काष्ठा page	**inpages)
अणु
	वापस ctx_id->mech_type->gm_ops
		->gss_wrap(ctx_id, offset, buf, inpages);
पूर्ण

u32
gss_unwrap(काष्ठा gss_ctx	*ctx_id,
	   पूर्णांक			offset,
	   पूर्णांक			len,
	   काष्ठा xdr_buf	*buf)
अणु
	वापस ctx_id->mech_type->gm_ops
		->gss_unwrap(ctx_id, offset, len, buf);
पूर्ण


/* gss_delete_sec_context: मुक्त all resources associated with context_handle.
 * Note this dअगरfers from the RFC 2744-specअगरied prototype in that we करोn't
 * bother वापसing an output token, since it would never be used anyway. */

u32
gss_delete_sec_context(काष्ठा gss_ctx	**context_handle)
अणु
	dprपूर्णांकk("RPC:       gss_delete_sec_context deleting %p\n",
			*context_handle);

	अगर (!*context_handle)
		वापस GSS_S_NO_CONTEXT;
	अगर ((*context_handle)->पूर्णांकernal_ctx_id)
		(*context_handle)->mech_type->gm_ops
			->gss_delete_sec_context((*context_handle)
							->पूर्णांकernal_ctx_id);
	gss_mech_put((*context_handle)->mech_type);
	kमुक्त(*context_handle);
	*context_handle=शून्य;
	वापस GSS_S_COMPLETE;
पूर्ण
