<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/gss_api.h
 *
 * Somewhat simplअगरied version of the gss api.
 *
 * Dug Song <dugsong@monkey.org>
 * Andy Adamson <andros@umich.edu>
 * Bruce Fields <bfields@umich.edu>
 * Copyright (c) 2000 The Regents of the University of Michigan
 */

#अगर_अघोषित _LINUX_SUNRPC_GSS_API_H
#घोषणा _LINUX_SUNRPC_GSS_API_H

#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/uपन.स>

/* The mechanism-independent gss-api context: */
काष्ठा gss_ctx अणु
	काष्ठा gss_api_mech	*mech_type;
	व्योम			*पूर्णांकernal_ctx_id;
	अचिन्हित पूर्णांक		slack, align;
पूर्ण;

#घोषणा GSS_C_NO_BUFFER		((काष्ठा xdr_netobj) 0)
#घोषणा GSS_C_NO_CONTEXT	((काष्ठा gss_ctx *) 0)
#घोषणा GSS_C_QOP_DEFAULT	(0)

/*XXX  arbitrary length - is this set somewhere? */
#घोषणा GSS_OID_MAX_LEN 32
काष्ठा rpcsec_gss_oid अणु
	अचिन्हित पूर्णांक	len;
	u8		data[GSS_OID_MAX_LEN];
पूर्ण;

/* From RFC 3530 */
काष्ठा rpcsec_gss_info अणु
	काष्ठा rpcsec_gss_oid	oid;
	u32			qop;
	u32			service;
पूर्ण;

/* gss-api prototypes; note that these are somewhat simplअगरied versions of
 * the prototypes specअगरied in RFC 2744. */
पूर्णांक gss_import_sec_context(
		स्थिर व्योम*		input_token,
		माप_प्रकार			bufsize,
		काष्ठा gss_api_mech	*mech,
		काष्ठा gss_ctx		**ctx_id,
		समय64_t		*endसमय,
		gfp_t			gfp_mask);
u32 gss_get_mic(
		काष्ठा gss_ctx		*ctx_id,
		काष्ठा xdr_buf		*message,
		काष्ठा xdr_netobj	*mic_token);
u32 gss_verअगरy_mic(
		काष्ठा gss_ctx		*ctx_id,
		काष्ठा xdr_buf		*message,
		काष्ठा xdr_netobj	*mic_token);
u32 gss_wrap(
		काष्ठा gss_ctx		*ctx_id,
		पूर्णांक			offset,
		काष्ठा xdr_buf		*outbuf,
		काष्ठा page		**inpages);
u32 gss_unwrap(
		काष्ठा gss_ctx		*ctx_id,
		पूर्णांक			offset,
		पूर्णांक			len,
		काष्ठा xdr_buf		*inbuf);
u32 gss_delete_sec_context(
		काष्ठा gss_ctx		**ctx_id);

rpc_authflavor_t gss_svc_to_pseuकरोflavor(काष्ठा gss_api_mech *, u32 qop,
					u32 service);
u32 gss_pseuकरोflavor_to_service(काष्ठा gss_api_mech *, u32 pseuकरोflavor);
bool gss_pseuकरोflavor_to_datatouch(काष्ठा gss_api_mech *, u32 pseuकरोflavor);
अक्षर *gss_service_to_auth_करोमुख्य_name(काष्ठा gss_api_mech *, u32 service);

काष्ठा pf_desc अणु
	u32	pseuकरोflavor;
	u32	qop;
	u32	service;
	अक्षर	*name;
	अक्षर	*auth_करोमुख्य_name;
	काष्ठा auth_करोमुख्य *करोमुख्य;
	bool	datatouch;
पूर्ण;

/* Dअगरferent mechanisms (e.g., krb5 or spkm3) may implement gss-api, and
 * mechanisms may be dynamically रेजिस्टरed or unरेजिस्टरed by modules. */

/* Each mechanism is described by the following काष्ठा: */
काष्ठा gss_api_mech अणु
	काष्ठा list_head	gm_list;
	काष्ठा module		*gm_owner;
	काष्ठा rpcsec_gss_oid	gm_oid;
	अक्षर			*gm_name;
	स्थिर काष्ठा gss_api_ops *gm_ops;
	/* pseuकरोflavors supported by this mechanism: */
	पूर्णांक			gm_pf_num;
	काष्ठा pf_desc *	gm_pfs;
	/* Should the following be a callback operation instead? */
	स्थिर अक्षर		*gm_upcall_enctypes;
पूर्ण;

/* and must provide the following operations: */
काष्ठा gss_api_ops अणु
	पूर्णांक (*gss_import_sec_context)(
			स्थिर व्योम		*input_token,
			माप_प्रकार			bufsize,
			काष्ठा gss_ctx		*ctx_id,
			समय64_t		*endसमय,
			gfp_t			gfp_mask);
	u32 (*gss_get_mic)(
			काष्ठा gss_ctx		*ctx_id,
			काष्ठा xdr_buf		*message,
			काष्ठा xdr_netobj	*mic_token);
	u32 (*gss_verअगरy_mic)(
			काष्ठा gss_ctx		*ctx_id,
			काष्ठा xdr_buf		*message,
			काष्ठा xdr_netobj	*mic_token);
	u32 (*gss_wrap)(
			काष्ठा gss_ctx		*ctx_id,
			पूर्णांक			offset,
			काष्ठा xdr_buf		*outbuf,
			काष्ठा page		**inpages);
	u32 (*gss_unwrap)(
			काष्ठा gss_ctx		*ctx_id,
			पूर्णांक			offset,
			पूर्णांक			len,
			काष्ठा xdr_buf		*buf);
	व्योम (*gss_delete_sec_context)(
			व्योम			*पूर्णांकernal_ctx_id);
पूर्ण;

पूर्णांक gss_mech_रेजिस्टर(काष्ठा gss_api_mech *);
व्योम gss_mech_unरेजिस्टर(काष्ठा gss_api_mech *);

/* वापसs a mechanism descriptor given an OID, and increments the mechanism's
 * reference count. */
काष्ठा gss_api_mech * gss_mech_get_by_OID(काष्ठा rpcsec_gss_oid *);

/* Given a GSS security tuple, look up a pseuकरोflavor */
rpc_authflavor_t gss_mech_info2flavor(काष्ठा rpcsec_gss_info *);

/* Given a pseuकरोflavor, look up a GSS security tuple */
पूर्णांक gss_mech_flavor2info(rpc_authflavor_t, काष्ठा rpcsec_gss_info *);

/* Returns a reference to a mechanism, given a name like "krb5" etc. */
काष्ठा gss_api_mech *gss_mech_get_by_name(स्थिर अक्षर *);

/* Similar, but get by pseuकरोflavor. */
काष्ठा gss_api_mech *gss_mech_get_by_pseuकरोflavor(u32);

काष्ठा gss_api_mech * gss_mech_get(काष्ठा gss_api_mech *);

/* For every successful gss_mech_get or gss_mech_get_by_* call there must be a
 * corresponding call to gss_mech_put. */
व्योम gss_mech_put(काष्ठा gss_api_mech *);

#पूर्ण_अगर /* _LINUX_SUNRPC_GSS_API_H */

