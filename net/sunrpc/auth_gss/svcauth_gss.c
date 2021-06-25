<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Neil Brown <neilb@cse.unsw.edu.au>
 * J. Bruce Fields <bfields@umich.edu>
 * Andy Adamson <andros@umich.edu>
 * Dug Song <dugsong@monkey.org>
 *
 * RPCSEC_GSS server authentication.
 * This implements RPCSEC_GSS as defined in rfc2203 (rpcsec_gss) and rfc2078
 * (gssapi)
 *
 * The RPCSEC_GSS involves three stages:
 *  1/ context creation
 *  2/ data exchange
 *  3/ context deकाष्ठाion
 *
 * Context creation is handled largely by upcalls to user-space.
 *  In particular, GSS_Accept_sec_context is handled by an upcall
 * Data exchange is handled entirely within the kernel
 *  In particular, GSS_GetMIC, GSS_VerअगरyMIC, GSS_Seal, GSS_Unseal are in-kernel.
 * Context deकाष्ठाion is handled in-kernel
 *  GSS_Delete_sec_context is in-kernel
 *
 * Context creation is initiated by a RPCSEC_GSS_INIT request arriving.
 * The context handle and gss_token are used as a key पूर्णांकo the rpcsec_init cache.
 * The content of this cache includes some of the outमाला_दो of GSS_Accept_sec_context,
 * being major_status, minor_status, context_handle, reply_token.
 * These are sent back to the client.
 * Sequence winकरोw management is handled by the kernel.  The winकरोw size अगर currently
 * a compile समय स्थिरant.
 *
 * When user-space is happy that a context is established, it places an entry
 * in the rpcsec_context cache. The key क्रम this cache is the context_handle.
 * The content includes:
 *   uid/gidlist - क्रम determining access rights
 *   mechanism type
 *   mechanism specअगरic inक्रमmation, such as a key
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/user_namespace.h>

#समावेश <linux/sunrpc/auth_gss.h>
#समावेश <linux/sunrpc/gss_err.h>
#समावेश <linux/sunrpc/svcauth.h>
#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश <linux/sunrpc/cache.h>

#समावेश <trace/events/rpcgss.h>

#समावेश "gss_rpc_upcall.h"


/* The rpcsec_init cache is used क्रम mapping RPCSEC_GSS_अणु,CONT_पूर्णINIT requests
 * पूर्णांकo replies.
 *
 * Key is context handle (\ष अगर empty) and gss_token.
 * Content is major_status minor_status (पूर्णांकegers) context_handle, reply_token.
 *
 */

अटल पूर्णांक netobj_equal(काष्ठा xdr_netobj *a, काष्ठा xdr_netobj *b)
अणु
	वापस a->len == b->len && 0 == स_भेद(a->data, b->data, a->len);
पूर्ण

#घोषणा	RSI_HASHBITS	6
#घोषणा	RSI_HASHMAX	(1<<RSI_HASHBITS)

काष्ठा rsi अणु
	काष्ठा cache_head	h;
	काष्ठा xdr_netobj	in_handle, in_token;
	काष्ठा xdr_netobj	out_handle, out_token;
	पूर्णांक			major_status, minor_status;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

अटल काष्ठा rsi *rsi_update(काष्ठा cache_detail *cd, काष्ठा rsi *new, काष्ठा rsi *old);
अटल काष्ठा rsi *rsi_lookup(काष्ठा cache_detail *cd, काष्ठा rsi *item);

अटल व्योम rsi_मुक्त(काष्ठा rsi *rsii)
अणु
	kमुक्त(rsii->in_handle.data);
	kमुक्त(rsii->in_token.data);
	kमुक्त(rsii->out_handle.data);
	kमुक्त(rsii->out_token.data);
पूर्ण

अटल व्योम rsi_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा rsi *rsii = container_of(head, काष्ठा rsi, rcu_head);

	rsi_मुक्त(rsii);
	kमुक्त(rsii);
पूर्ण

अटल व्योम rsi_put(काष्ठा kref *ref)
अणु
	काष्ठा rsi *rsii = container_of(ref, काष्ठा rsi, h.ref);

	call_rcu(&rsii->rcu_head, rsi_मुक्त_rcu);
पूर्ण

अटल अंतरभूत पूर्णांक rsi_hash(काष्ठा rsi *item)
अणु
	वापस hash_mem(item->in_handle.data, item->in_handle.len, RSI_HASHBITS)
	     ^ hash_mem(item->in_token.data, item->in_token.len, RSI_HASHBITS);
पूर्ण

अटल पूर्णांक rsi_match(काष्ठा cache_head *a, काष्ठा cache_head *b)
अणु
	काष्ठा rsi *item = container_of(a, काष्ठा rsi, h);
	काष्ठा rsi *पंचांगp = container_of(b, काष्ठा rsi, h);
	वापस netobj_equal(&item->in_handle, &पंचांगp->in_handle) &&
	       netobj_equal(&item->in_token, &पंचांगp->in_token);
पूर्ण

अटल पूर्णांक dup_to_netobj(काष्ठा xdr_netobj *dst, अक्षर *src, पूर्णांक len)
अणु
	dst->len = len;
	dst->data = (len ? kmemdup(src, len, GFP_KERNEL) : शून्य);
	अगर (len && !dst->data)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dup_netobj(काष्ठा xdr_netobj *dst, काष्ठा xdr_netobj *src)
अणु
	वापस dup_to_netobj(dst, src->data, src->len);
पूर्ण

अटल व्योम rsi_init(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा rsi *new = container_of(cnew, काष्ठा rsi, h);
	काष्ठा rsi *item = container_of(citem, काष्ठा rsi, h);

	new->out_handle.data = शून्य;
	new->out_handle.len = 0;
	new->out_token.data = शून्य;
	new->out_token.len = 0;
	new->in_handle.len = item->in_handle.len;
	item->in_handle.len = 0;
	new->in_token.len = item->in_token.len;
	item->in_token.len = 0;
	new->in_handle.data = item->in_handle.data;
	item->in_handle.data = शून्य;
	new->in_token.data = item->in_token.data;
	item->in_token.data = शून्य;
पूर्ण

अटल व्योम update_rsi(काष्ठा cache_head *cnew, काष्ठा cache_head *citem)
अणु
	काष्ठा rsi *new = container_of(cnew, काष्ठा rsi, h);
	काष्ठा rsi *item = container_of(citem, काष्ठा rsi, h);

	BUG_ON(new->out_handle.data || new->out_token.data);
	new->out_handle.len = item->out_handle.len;
	item->out_handle.len = 0;
	new->out_token.len = item->out_token.len;
	item->out_token.len = 0;
	new->out_handle.data = item->out_handle.data;
	item->out_handle.data = शून्य;
	new->out_token.data = item->out_token.data;
	item->out_token.data = शून्य;

	new->major_status = item->major_status;
	new->minor_status = item->minor_status;
पूर्ण

अटल काष्ठा cache_head *rsi_alloc(व्योम)
अणु
	काष्ठा rsi *rsii = kदो_स्मृति(माप(*rsii), GFP_KERNEL);
	अगर (rsii)
		वापस &rsii->h;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक rsi_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस sunrpc_cache_pipe_upcall_समयout(cd, h);
पूर्ण

अटल व्योम rsi_request(काष्ठा cache_detail *cd,
		       काष्ठा cache_head *h,
		       अक्षर **bpp, पूर्णांक *blen)
अणु
	काष्ठा rsi *rsii = container_of(h, काष्ठा rsi, h);

	qword_addhex(bpp, blen, rsii->in_handle.data, rsii->in_handle.len);
	qword_addhex(bpp, blen, rsii->in_token.data, rsii->in_token.len);
	(*bpp)[-1] = '\n';
पूर्ण

अटल पूर्णांक rsi_parse(काष्ठा cache_detail *cd,
		    अक्षर *mesg, पूर्णांक mlen)
अणु
	/* context token expiry major minor context token */
	अक्षर *buf = mesg;
	अक्षर *ep;
	पूर्णांक len;
	काष्ठा rsi rsii, *rsip = शून्य;
	समय64_t expiry;
	पूर्णांक status = -EINVAL;

	स_रखो(&rsii, 0, माप(rsii));
	/* handle */
	len = qword_get(&mesg, buf, mlen);
	अगर (len < 0)
		जाओ out;
	status = -ENOMEM;
	अगर (dup_to_netobj(&rsii.in_handle, buf, len))
		जाओ out;

	/* token */
	len = qword_get(&mesg, buf, mlen);
	status = -EINVAL;
	अगर (len < 0)
		जाओ out;
	status = -ENOMEM;
	अगर (dup_to_netobj(&rsii.in_token, buf, len))
		जाओ out;

	rsip = rsi_lookup(cd, &rsii);
	अगर (!rsip)
		जाओ out;

	rsii.h.flags = 0;
	/* expiry */
	expiry = get_expiry(&mesg);
	status = -EINVAL;
	अगर (expiry == 0)
		जाओ out;

	/* major/minor */
	len = qword_get(&mesg, buf, mlen);
	अगर (len <= 0)
		जाओ out;
	rsii.major_status = simple_म_से_अदीर्घ(buf, &ep, 10);
	अगर (*ep)
		जाओ out;
	len = qword_get(&mesg, buf, mlen);
	अगर (len <= 0)
		जाओ out;
	rsii.minor_status = simple_म_से_अदीर्घ(buf, &ep, 10);
	अगर (*ep)
		जाओ out;

	/* out_handle */
	len = qword_get(&mesg, buf, mlen);
	अगर (len < 0)
		जाओ out;
	status = -ENOMEM;
	अगर (dup_to_netobj(&rsii.out_handle, buf, len))
		जाओ out;

	/* out_token */
	len = qword_get(&mesg, buf, mlen);
	status = -EINVAL;
	अगर (len < 0)
		जाओ out;
	status = -ENOMEM;
	अगर (dup_to_netobj(&rsii.out_token, buf, len))
		जाओ out;
	rsii.h.expiry_समय = expiry;
	rsip = rsi_update(cd, &rsii, rsip);
	status = 0;
out:
	rsi_मुक्त(&rsii);
	अगर (rsip)
		cache_put(&rsip->h, cd);
	अन्यथा
		status = -ENOMEM;
	वापस status;
पूर्ण

अटल स्थिर काष्ठा cache_detail rsi_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= RSI_HASHMAX,
	.name           = "auth.rpcsec.init",
	.cache_put      = rsi_put,
	.cache_upcall	= rsi_upcall,
	.cache_request  = rsi_request,
	.cache_parse    = rsi_parse,
	.match		= rsi_match,
	.init		= rsi_init,
	.update		= update_rsi,
	.alloc		= rsi_alloc,
पूर्ण;

अटल काष्ठा rsi *rsi_lookup(काष्ठा cache_detail *cd, काष्ठा rsi *item)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = rsi_hash(item);

	ch = sunrpc_cache_lookup_rcu(cd, &item->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा rsi, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा rsi *rsi_update(काष्ठा cache_detail *cd, काष्ठा rsi *new, काष्ठा rsi *old)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = rsi_hash(new);

	ch = sunrpc_cache_update(cd, &new->h,
				 &old->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा rsi, h);
	अन्यथा
		वापस शून्य;
पूर्ण


/*
 * The rpcsec_context cache is used to store a context that is
 * used in data exchange.
 * The key is a context handle. The content is:
 *  uid, gidlist, mechanism, service-set, mech-specअगरic-data
 */

#घोषणा	RSC_HASHBITS	10
#घोषणा	RSC_HASHMAX	(1<<RSC_HASHBITS)

#घोषणा GSS_SEQ_WIN	128

काष्ठा gss_svc_seq_data अणु
	/* highest seq number seen so far: */
	u32			sd_max;
	/* क्रम i such that sd_max-GSS_SEQ_WIN < i <= sd_max, the i-th bit of
	 * sd_win is nonzero अगरf sequence number i has been seen alपढ़ोy: */
	अचिन्हित दीर्घ		sd_win[GSS_SEQ_WIN/BITS_PER_LONG];
	spinlock_t		sd_lock;
पूर्ण;

काष्ठा rsc अणु
	काष्ठा cache_head	h;
	काष्ठा xdr_netobj	handle;
	काष्ठा svc_cred		cred;
	काष्ठा gss_svc_seq_data	seqdata;
	काष्ठा gss_ctx		*mechctx;
	काष्ठा rcu_head		rcu_head;
पूर्ण;

अटल काष्ठा rsc *rsc_update(काष्ठा cache_detail *cd, काष्ठा rsc *new, काष्ठा rsc *old);
अटल काष्ठा rsc *rsc_lookup(काष्ठा cache_detail *cd, काष्ठा rsc *item);

अटल व्योम rsc_मुक्त(काष्ठा rsc *rsci)
अणु
	kमुक्त(rsci->handle.data);
	अगर (rsci->mechctx)
		gss_delete_sec_context(&rsci->mechctx);
	मुक्त_svc_cred(&rsci->cred);
पूर्ण

अटल व्योम rsc_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा rsc *rsci = container_of(head, काष्ठा rsc, rcu_head);

	kमुक्त(rsci->handle.data);
	kमुक्त(rsci);
पूर्ण

अटल व्योम rsc_put(काष्ठा kref *ref)
अणु
	काष्ठा rsc *rsci = container_of(ref, काष्ठा rsc, h.ref);

	अगर (rsci->mechctx)
		gss_delete_sec_context(&rsci->mechctx);
	मुक्त_svc_cred(&rsci->cred);
	call_rcu(&rsci->rcu_head, rsc_मुक्त_rcu);
पूर्ण

अटल अंतरभूत पूर्णांक
rsc_hash(काष्ठा rsc *rsci)
अणु
	वापस hash_mem(rsci->handle.data, rsci->handle.len, RSC_HASHBITS);
पूर्ण

अटल पूर्णांक
rsc_match(काष्ठा cache_head *a, काष्ठा cache_head *b)
अणु
	काष्ठा rsc *new = container_of(a, काष्ठा rsc, h);
	काष्ठा rsc *पंचांगp = container_of(b, काष्ठा rsc, h);

	वापस netobj_equal(&new->handle, &पंचांगp->handle);
पूर्ण

अटल व्योम
rsc_init(काष्ठा cache_head *cnew, काष्ठा cache_head *cपंचांगp)
अणु
	काष्ठा rsc *new = container_of(cnew, काष्ठा rsc, h);
	काष्ठा rsc *पंचांगp = container_of(cपंचांगp, काष्ठा rsc, h);

	new->handle.len = पंचांगp->handle.len;
	पंचांगp->handle.len = 0;
	new->handle.data = पंचांगp->handle.data;
	पंचांगp->handle.data = शून्य;
	new->mechctx = शून्य;
	init_svc_cred(&new->cred);
पूर्ण

अटल व्योम
update_rsc(काष्ठा cache_head *cnew, काष्ठा cache_head *cपंचांगp)
अणु
	काष्ठा rsc *new = container_of(cnew, काष्ठा rsc, h);
	काष्ठा rsc *पंचांगp = container_of(cपंचांगp, काष्ठा rsc, h);

	new->mechctx = पंचांगp->mechctx;
	पंचांगp->mechctx = शून्य;
	स_रखो(&new->seqdata, 0, माप(new->seqdata));
	spin_lock_init(&new->seqdata.sd_lock);
	new->cred = पंचांगp->cred;
	init_svc_cred(&पंचांगp->cred);
पूर्ण

अटल काष्ठा cache_head *
rsc_alloc(व्योम)
अणु
	काष्ठा rsc *rsci = kदो_स्मृति(माप(*rsci), GFP_KERNEL);
	अगर (rsci)
		वापस &rsci->h;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल पूर्णांक rsc_upcall(काष्ठा cache_detail *cd, काष्ठा cache_head *h)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक rsc_parse(काष्ठा cache_detail *cd,
		     अक्षर *mesg, पूर्णांक mlen)
अणु
	/* contexthandle expiry [ uid gid N <n gids> mechname ...mechdata... ] */
	अक्षर *buf = mesg;
	पूर्णांक id;
	पूर्णांक len, rv;
	काष्ठा rsc rsci, *rscp = शून्य;
	समय64_t expiry;
	पूर्णांक status = -EINVAL;
	काष्ठा gss_api_mech *gm = शून्य;

	स_रखो(&rsci, 0, माप(rsci));
	/* context handle */
	len = qword_get(&mesg, buf, mlen);
	अगर (len < 0) जाओ out;
	status = -ENOMEM;
	अगर (dup_to_netobj(&rsci.handle, buf, len))
		जाओ out;

	rsci.h.flags = 0;
	/* expiry */
	expiry = get_expiry(&mesg);
	status = -EINVAL;
	अगर (expiry == 0)
		जाओ out;

	rscp = rsc_lookup(cd, &rsci);
	अगर (!rscp)
		जाओ out;

	/* uid, or NEGATIVE */
	rv = get_पूर्णांक(&mesg, &id);
	अगर (rv == -EINVAL)
		जाओ out;
	अगर (rv == -ENOENT)
		set_bit(CACHE_NEGATIVE, &rsci.h.flags);
	अन्यथा अणु
		पूर्णांक N, i;

		/*
		 * NOTE: we skip uid_valid()/gid_valid() checks here:
		 * instead, * -1 id's are later mapped to the
		 * (export-specअगरic) anonymous id by nfsd_setuser.
		 *
		 * (But supplementary gid's get no such special
		 * treaपंचांगent so are checked क्रम validity here.)
		 */
		/* uid */
		rsci.cred.cr_uid = make_kuid(current_user_ns(), id);

		/* gid */
		अगर (get_पूर्णांक(&mesg, &id))
			जाओ out;
		rsci.cred.cr_gid = make_kgid(current_user_ns(), id);

		/* number of additional gid's */
		अगर (get_पूर्णांक(&mesg, &N))
			जाओ out;
		अगर (N < 0 || N > NGROUPS_MAX)
			जाओ out;
		status = -ENOMEM;
		rsci.cred.cr_group_info = groups_alloc(N);
		अगर (rsci.cred.cr_group_info == शून्य)
			जाओ out;

		/* gid's */
		status = -EINVAL;
		क्रम (i=0; i<N; i++) अणु
			kgid_t kgid;
			अगर (get_पूर्णांक(&mesg, &id))
				जाओ out;
			kgid = make_kgid(current_user_ns(), id);
			अगर (!gid_valid(kgid))
				जाओ out;
			rsci.cred.cr_group_info->gid[i] = kgid;
		पूर्ण
		groups_sort(rsci.cred.cr_group_info);

		/* mech name */
		len = qword_get(&mesg, buf, mlen);
		अगर (len < 0)
			जाओ out;
		gm = rsci.cred.cr_gss_mech = gss_mech_get_by_name(buf);
		status = -EOPNOTSUPP;
		अगर (!gm)
			जाओ out;

		status = -EINVAL;
		/* mech-specअगरic data: */
		len = qword_get(&mesg, buf, mlen);
		अगर (len < 0)
			जाओ out;
		status = gss_import_sec_context(buf, len, gm, &rsci.mechctx,
						शून्य, GFP_KERNEL);
		अगर (status)
			जाओ out;

		/* get client name */
		len = qword_get(&mesg, buf, mlen);
		अगर (len > 0) अणु
			rsci.cred.cr_principal = kstrdup(buf, GFP_KERNEL);
			अगर (!rsci.cred.cr_principal) अणु
				status = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण
	rsci.h.expiry_समय = expiry;
	rscp = rsc_update(cd, &rsci, rscp);
	status = 0;
out:
	rsc_मुक्त(&rsci);
	अगर (rscp)
		cache_put(&rscp->h, cd);
	अन्यथा
		status = -ENOMEM;
	वापस status;
पूर्ण

अटल स्थिर काष्ठा cache_detail rsc_cache_ढाँचा = अणु
	.owner		= THIS_MODULE,
	.hash_size	= RSC_HASHMAX,
	.name		= "auth.rpcsec.context",
	.cache_put	= rsc_put,
	.cache_upcall	= rsc_upcall,
	.cache_parse	= rsc_parse,
	.match		= rsc_match,
	.init		= rsc_init,
	.update		= update_rsc,
	.alloc		= rsc_alloc,
पूर्ण;

अटल काष्ठा rsc *rsc_lookup(काष्ठा cache_detail *cd, काष्ठा rsc *item)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = rsc_hash(item);

	ch = sunrpc_cache_lookup_rcu(cd, &item->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा rsc, h);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा rsc *rsc_update(काष्ठा cache_detail *cd, काष्ठा rsc *new, काष्ठा rsc *old)
अणु
	काष्ठा cache_head *ch;
	पूर्णांक hash = rsc_hash(new);

	ch = sunrpc_cache_update(cd, &new->h,
				 &old->h, hash);
	अगर (ch)
		वापस container_of(ch, काष्ठा rsc, h);
	अन्यथा
		वापस शून्य;
पूर्ण


अटल काष्ठा rsc *
gss_svc_searchbyctx(काष्ठा cache_detail *cd, काष्ठा xdr_netobj *handle)
अणु
	काष्ठा rsc rsci;
	काष्ठा rsc *found;

	स_रखो(&rsci, 0, माप(rsci));
	अगर (dup_to_netobj(&rsci.handle, handle->data, handle->len))
		वापस शून्य;
	found = rsc_lookup(cd, &rsci);
	rsc_मुक्त(&rsci);
	अगर (!found)
		वापस शून्य;
	अगर (cache_check(cd, &found->h, शून्य))
		वापस शून्य;
	वापस found;
पूर्ण

/**
 * gss_check_seq_num - GSS sequence number winकरोw check
 * @rqstp: RPC Call to use when reporting errors
 * @rsci: cached GSS context state (updated on वापस)
 * @seq_num: sequence number to check
 *
 * Implements sequence number algorithm as specअगरied in
 * RFC 2203, Section 5.3.3.1. "Context Management".
 *
 * Return values:
 *   %true: @rqstp's GSS sequence number is inside the winकरोw
 *   %false: @rqstp's GSS sequence number is outside the winकरोw
 */
अटल bool gss_check_seq_num(स्थिर काष्ठा svc_rqst *rqstp, काष्ठा rsc *rsci,
			      u32 seq_num)
अणु
	काष्ठा gss_svc_seq_data *sd = &rsci->seqdata;
	bool result = false;

	spin_lock(&sd->sd_lock);
	अगर (seq_num > sd->sd_max) अणु
		अगर (seq_num >= sd->sd_max + GSS_SEQ_WIN) अणु
			स_रखो(sd->sd_win, 0, माप(sd->sd_win));
			sd->sd_max = seq_num;
		पूर्ण अन्यथा जबतक (sd->sd_max < seq_num) अणु
			sd->sd_max++;
			__clear_bit(sd->sd_max % GSS_SEQ_WIN, sd->sd_win);
		पूर्ण
		__set_bit(seq_num % GSS_SEQ_WIN, sd->sd_win);
		जाओ ok;
	पूर्ण अन्यथा अगर (seq_num <= sd->sd_max - GSS_SEQ_WIN) अणु
		जाओ toolow;
	पूर्ण
	अगर (__test_and_set_bit(seq_num % GSS_SEQ_WIN, sd->sd_win))
		जाओ alपढ़ोyseen;

ok:
	result = true;
out:
	spin_unlock(&sd->sd_lock);
	वापस result;

toolow:
	trace_rpcgss_svc_seqno_low(rqstp, seq_num,
				   sd->sd_max - GSS_SEQ_WIN,
				   sd->sd_max);
	जाओ out;
alपढ़ोyseen:
	trace_rpcgss_svc_seqno_seen(rqstp, seq_num);
	जाओ out;
पूर्ण

अटल अंतरभूत u32 round_up_to_quad(u32 i)
अणु
	वापस (i + 3 ) & ~3;
पूर्ण

अटल अंतरभूत पूर्णांक
svc_safe_getnetobj(काष्ठा kvec *argv, काष्ठा xdr_netobj *o)
अणु
	पूर्णांक l;

	अगर (argv->iov_len < 4)
		वापस -1;
	o->len = svc_getnl(argv);
	l = round_up_to_quad(o->len);
	अगर (argv->iov_len < l)
		वापस -1;
	o->data = argv->iov_base;
	argv->iov_base += l;
	argv->iov_len -= l;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
svc_safe_putnetobj(काष्ठा kvec *resv, काष्ठा xdr_netobj *o)
अणु
	u8 *p;

	अगर (resv->iov_len + 4 > PAGE_SIZE)
		वापस -1;
	svc_putnl(resv, o->len);
	p = resv->iov_base + resv->iov_len;
	resv->iov_len += round_up_to_quad(o->len);
	अगर (resv->iov_len > PAGE_SIZE)
		वापस -1;
	स_नकल(p, o->data, o->len);
	स_रखो(p + o->len, 0, round_up_to_quad(o->len) - o->len);
	वापस 0;
पूर्ण

/*
 * Verअगरy the checksum on the header and वापस SVC_OK on success.
 * Otherwise, वापस SVC_DROP (in the हाल of a bad sequence number)
 * or वापस SVC_DENIED and indicate error in authp.
 */
अटल पूर्णांक
gss_verअगरy_header(काष्ठा svc_rqst *rqstp, काष्ठा rsc *rsci,
		  __be32 *rpcstart, काष्ठा rpc_gss_wire_cred *gc, __be32 *authp)
अणु
	काष्ठा gss_ctx		*ctx_id = rsci->mechctx;
	काष्ठा xdr_buf		rpchdr;
	काष्ठा xdr_netobj	checksum;
	u32			flavor = 0;
	काष्ठा kvec		*argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec		iov;

	/* data to compute the checksum over: */
	iov.iov_base = rpcstart;
	iov.iov_len = (u8 *)argv->iov_base - (u8 *)rpcstart;
	xdr_buf_from_iov(&iov, &rpchdr);

	*authp = rpc_autherr_badverf;
	अगर (argv->iov_len < 4)
		वापस SVC_DENIED;
	flavor = svc_getnl(argv);
	अगर (flavor != RPC_AUTH_GSS)
		वापस SVC_DENIED;
	अगर (svc_safe_getnetobj(argv, &checksum))
		वापस SVC_DENIED;

	अगर (rqstp->rq_deferred) /* skip verअगरication of revisited request */
		वापस SVC_OK;
	अगर (gss_verअगरy_mic(ctx_id, &rpchdr, &checksum) != GSS_S_COMPLETE) अणु
		*authp = rpcsec_gsserr_credproblem;
		वापस SVC_DENIED;
	पूर्ण

	अगर (gc->gc_seq > MAXSEQ) अणु
		trace_rpcgss_svc_seqno_large(rqstp, gc->gc_seq);
		*authp = rpcsec_gsserr_ctxproblem;
		वापस SVC_DENIED;
	पूर्ण
	अगर (!gss_check_seq_num(rqstp, rsci, gc->gc_seq))
		वापस SVC_DROP;
	वापस SVC_OK;
पूर्ण

अटल पूर्णांक
gss_ग_लिखो_null_verf(काष्ठा svc_rqst *rqstp)
अणु
	__be32     *p;

	svc_putnl(rqstp->rq_res.head, RPC_AUTH_शून्य);
	p = rqstp->rq_res.head->iov_base + rqstp->rq_res.head->iov_len;
	/* करोn't really need to check अगर head->iov_len > PAGE_SIZE ... */
	*p++ = 0;
	अगर (!xdr_ressize_check(rqstp, p))
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक
gss_ग_लिखो_verf(काष्ठा svc_rqst *rqstp, काष्ठा gss_ctx *ctx_id, u32 seq)
अणु
	__be32			*xdr_seq;
	u32			maj_stat;
	काष्ठा xdr_buf		verf_data;
	काष्ठा xdr_netobj	mic;
	__be32			*p;
	काष्ठा kvec		iov;
	पूर्णांक err = -1;

	svc_putnl(rqstp->rq_res.head, RPC_AUTH_GSS);
	xdr_seq = kदो_स्मृति(4, GFP_KERNEL);
	अगर (!xdr_seq)
		वापस -1;
	*xdr_seq = htonl(seq);

	iov.iov_base = xdr_seq;
	iov.iov_len = 4;
	xdr_buf_from_iov(&iov, &verf_data);
	p = rqstp->rq_res.head->iov_base + rqstp->rq_res.head->iov_len;
	mic.data = (u8 *)(p + 1);
	maj_stat = gss_get_mic(ctx_id, &verf_data, &mic);
	अगर (maj_stat != GSS_S_COMPLETE)
		जाओ out;
	*p++ = htonl(mic.len);
	स_रखो((u8 *)p + mic.len, 0, round_up_to_quad(mic.len) - mic.len);
	p += XDR_QUADLEN(mic.len);
	अगर (!xdr_ressize_check(rqstp, p))
		जाओ out;
	err = 0;
out:
	kमुक्त(xdr_seq);
	वापस err;
पूर्ण

काष्ठा gss_करोमुख्य अणु
	काष्ठा auth_करोमुख्य	h;
	u32			pseuकरोflavor;
पूर्ण;

अटल काष्ठा auth_करोमुख्य *
find_gss_auth_करोमुख्य(काष्ठा gss_ctx *ctx, u32 svc)
अणु
	अक्षर *name;

	name = gss_service_to_auth_करोमुख्य_name(ctx->mech_type, svc);
	अगर (!name)
		वापस शून्य;
	वापस auth_करोमुख्य_find(name);
पूर्ण

अटल काष्ठा auth_ops svcauthops_gss;

u32 svcauth_gss_flavor(काष्ठा auth_करोमुख्य *करोm)
अणु
	काष्ठा gss_करोमुख्य *gd = container_of(करोm, काष्ठा gss_करोमुख्य, h);

	वापस gd->pseuकरोflavor;
पूर्ण

EXPORT_SYMBOL_GPL(svcauth_gss_flavor);

काष्ठा auth_करोमुख्य *
svcauth_gss_रेजिस्टर_pseuकरोflavor(u32 pseuकरोflavor, अक्षर * name)
अणु
	काष्ठा gss_करोमुख्य	*new;
	काष्ठा auth_करोमुख्य	*test;
	पूर्णांक			stat = -ENOMEM;

	new = kदो_स्मृति(माप(*new), GFP_KERNEL);
	अगर (!new)
		जाओ out;
	kref_init(&new->h.ref);
	new->h.name = kstrdup(name, GFP_KERNEL);
	अगर (!new->h.name)
		जाओ out_मुक्त_करोm;
	new->h.flavour = &svcauthops_gss;
	new->pseuकरोflavor = pseuकरोflavor;

	test = auth_करोमुख्य_lookup(name, &new->h);
	अगर (test != &new->h) अणु
		pr_warn("svc: duplicate registration of gss pseudo flavour %s.\n",
			name);
		stat = -EADDRINUSE;
		auth_करोमुख्य_put(test);
		जाओ out_मुक्त_name;
	पूर्ण
	वापस test;

out_मुक्त_name:
	kमुक्त(new->h.name);
out_मुक्त_करोm:
	kमुक्त(new);
out:
	वापस ERR_PTR(stat);
पूर्ण
EXPORT_SYMBOL_GPL(svcauth_gss_रेजिस्टर_pseuकरोflavor);

अटल अंतरभूत पूर्णांक
पढ़ो_u32_from_xdr_buf(काष्ठा xdr_buf *buf, पूर्णांक base, u32 *obj)
अणु
	__be32  raw;
	पूर्णांक     status;

	status = पढ़ो_bytes_from_xdr_buf(buf, base, &raw, माप(*obj));
	अगर (status)
		वापस status;
	*obj = ntohl(raw);
	वापस 0;
पूर्ण

/* It would be nice अगर this bit of code could be shared with the client.
 * Obstacles:
 *	The client shouldn't दो_स्मृति(), would have to pass in own memory.
 *	The server uses base of head iovec as पढ़ो poपूर्णांकer, जबतक the
 *	client uses separate poपूर्णांकer. */
अटल पूर्णांक
unwrap_पूर्णांकeg_data(काष्ठा svc_rqst *rqstp, काष्ठा xdr_buf *buf, u32 seq, काष्ठा gss_ctx *ctx)
अणु
	u32 पूर्णांकeg_len, rseqno, maj_stat;
	पूर्णांक stat = -EINVAL;
	काष्ठा xdr_netobj mic;
	काष्ठा xdr_buf पूर्णांकeg_buf;

	mic.data = शून्य;

	/* NFS READ normally uses splice to send data in-place. However
	 * the data in cache can change after the reply's MIC is computed
	 * but beक्रमe the RPC reply is sent. To prevent the client from
	 * rejecting the server-computed MIC in this somewhat rare हाल,
	 * करो not use splice with the GSS पूर्णांकegrity service.
	 */
	clear_bit(RQ_SPLICE_OK, &rqstp->rq_flags);

	/* Did we alपढ़ोy verअगरy the signature on the original pass through? */
	अगर (rqstp->rq_deferred)
		वापस 0;

	पूर्णांकeg_len = svc_getnl(&buf->head[0]);
	अगर (पूर्णांकeg_len & 3)
		जाओ unwrap_failed;
	अगर (पूर्णांकeg_len > buf->len)
		जाओ unwrap_failed;
	अगर (xdr_buf_subsegment(buf, &पूर्णांकeg_buf, 0, पूर्णांकeg_len))
		जाओ unwrap_failed;

	/* copy out mic... */
	अगर (पढ़ो_u32_from_xdr_buf(buf, पूर्णांकeg_len, &mic.len))
		जाओ unwrap_failed;
	अगर (mic.len > RPC_MAX_AUTH_SIZE)
		जाओ unwrap_failed;
	mic.data = kदो_स्मृति(mic.len, GFP_KERNEL);
	अगर (!mic.data)
		जाओ unwrap_failed;
	अगर (पढ़ो_bytes_from_xdr_buf(buf, पूर्णांकeg_len + 4, mic.data, mic.len))
		जाओ unwrap_failed;
	maj_stat = gss_verअगरy_mic(ctx, &पूर्णांकeg_buf, &mic);
	अगर (maj_stat != GSS_S_COMPLETE)
		जाओ bad_mic;
	rseqno = svc_getnl(&buf->head[0]);
	अगर (rseqno != seq)
		जाओ bad_seqno;
	/* trim off the mic and padding at the end beक्रमe वापसing */
	xdr_buf_trim(buf, round_up_to_quad(mic.len) + 4);
	stat = 0;
out:
	kमुक्त(mic.data);
	वापस stat;

unwrap_failed:
	trace_rpcgss_svc_unwrap_failed(rqstp);
	जाओ out;
bad_seqno:
	trace_rpcgss_svc_seqno_bad(rqstp, seq, rseqno);
	जाओ out;
bad_mic:
	trace_rpcgss_svc_mic(rqstp, maj_stat);
	जाओ out;
पूर्ण

अटल अंतरभूत पूर्णांक
total_buf_len(काष्ठा xdr_buf *buf)
अणु
	वापस buf->head[0].iov_len + buf->page_len + buf->tail[0].iov_len;
पूर्ण

अटल व्योम
fix_priv_head(काष्ठा xdr_buf *buf, पूर्णांक pad)
अणु
	अगर (buf->page_len == 0) अणु
		/* We need to adjust head and buf->len in tandem in this
		 * हाल to make svc_defer() work--it finds the original
		 * buffer start using buf->len - buf->head[0].iov_len. */
		buf->head[0].iov_len -= pad;
	पूर्ण
पूर्ण

अटल पूर्णांक
unwrap_priv_data(काष्ठा svc_rqst *rqstp, काष्ठा xdr_buf *buf, u32 seq, काष्ठा gss_ctx *ctx)
अणु
	u32 priv_len, maj_stat;
	पूर्णांक pad, reमुख्यing_len, offset;
	u32 rseqno;

	clear_bit(RQ_SPLICE_OK, &rqstp->rq_flags);

	priv_len = svc_getnl(&buf->head[0]);
	अगर (rqstp->rq_deferred) अणु
		/* Alपढ़ोy decrypted last समय through! The sequence number
		 * check at out_seq is unnecessary but harmless: */
		जाओ out_seq;
	पूर्ण
	/* buf->len is the number of bytes from the original start of the
	 * request to the end, where head[0].iov_len is just the bytes
	 * not yet पढ़ो from the head, so these two values are dअगरferent: */
	reमुख्यing_len = total_buf_len(buf);
	अगर (priv_len > reमुख्यing_len)
		जाओ unwrap_failed;
	pad = reमुख्यing_len - priv_len;
	buf->len -= pad;
	fix_priv_head(buf, pad);

	maj_stat = gss_unwrap(ctx, 0, priv_len, buf);
	pad = priv_len - buf->len;
	/* The upper layers assume the buffer is aligned on 4-byte boundaries.
	 * In the krb5p हाल, at least, the data ends up offset, so we need to
	 * move it around. */
	/* XXX: This is very inefficient.  It would be better to either करो
	 * this जबतक we encrypt, or maybe in the receive code, अगर we can peak
	 * ahead and work out the service and mechanism there. */
	offset = xdr_pad_size(buf->head[0].iov_len);
	अगर (offset) अणु
		buf->buflen = RPCSVC_MAXPAYLOAD;
		xdr_shअगरt_buf(buf, offset);
		fix_priv_head(buf, pad);
	पूर्ण
	अगर (maj_stat != GSS_S_COMPLETE)
		जाओ bad_unwrap;
out_seq:
	rseqno = svc_getnl(&buf->head[0]);
	अगर (rseqno != seq)
		जाओ bad_seqno;
	वापस 0;

unwrap_failed:
	trace_rpcgss_svc_unwrap_failed(rqstp);
	वापस -EINVAL;
bad_seqno:
	trace_rpcgss_svc_seqno_bad(rqstp, seq, rseqno);
	वापस -EINVAL;
bad_unwrap:
	trace_rpcgss_svc_unwrap(rqstp, maj_stat);
	वापस -EINVAL;
पूर्ण

काष्ठा gss_svc_data अणु
	/* decoded gss client cred: */
	काष्ठा rpc_gss_wire_cred	clcred;
	/* save a poपूर्णांकer to the beginning of the encoded verअगरier,
	 * क्रम use in encryption/checksumming in svcauth_gss_release: */
	__be32				*verf_start;
	काष्ठा rsc			*rsci;
पूर्ण;

अटल पूर्णांक
svcauth_gss_set_client(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा gss_svc_data *svcdata = rqstp->rq_auth_data;
	काष्ठा rsc *rsci = svcdata->rsci;
	काष्ठा rpc_gss_wire_cred *gc = &svcdata->clcred;
	पूर्णांक stat;

	/*
	 * A gss export can be specअगरied either by:
	 * 	export	*(sec=krb5,rw)
	 * or by
	 * 	export gss/krb5(rw)
	 * The latter is deprecated; but क्रम backwards compatibility reasons
	 * the nfsd code will still fall back on trying it अगर the क्रमmer
	 * करोesn't work; so we try to make both available to nfsd, below.
	 */
	rqstp->rq_gssclient = find_gss_auth_करोमुख्य(rsci->mechctx, gc->gc_svc);
	अगर (rqstp->rq_gssclient == शून्य)
		वापस SVC_DENIED;
	stat = svcauth_unix_set_client(rqstp);
	अगर (stat == SVC_DROP || stat == SVC_CLOSE)
		वापस stat;
	वापस SVC_OK;
पूर्ण

अटल अंतरभूत पूर्णांक
gss_ग_लिखो_init_verf(काष्ठा cache_detail *cd, काष्ठा svc_rqst *rqstp,
		काष्ठा xdr_netobj *out_handle, पूर्णांक *major_status)
अणु
	काष्ठा rsc *rsci;
	पूर्णांक        rc;

	अगर (*major_status != GSS_S_COMPLETE)
		वापस gss_ग_लिखो_null_verf(rqstp);
	rsci = gss_svc_searchbyctx(cd, out_handle);
	अगर (rsci == शून्य) अणु
		*major_status = GSS_S_NO_CONTEXT;
		वापस gss_ग_लिखो_null_verf(rqstp);
	पूर्ण
	rc = gss_ग_लिखो_verf(rqstp, rsci->mechctx, GSS_SEQ_WIN);
	cache_put(&rsci->h, cd);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक
gss_पढ़ो_common_verf(काष्ठा rpc_gss_wire_cred *gc,
		     काष्ठा kvec *argv, __be32 *authp,
		     काष्ठा xdr_netobj *in_handle)
अणु
	/* Read the verअगरier; should be शून्य: */
	*authp = rpc_autherr_badverf;
	अगर (argv->iov_len < 2 * 4)
		वापस SVC_DENIED;
	अगर (svc_getnl(argv) != RPC_AUTH_शून्य)
		वापस SVC_DENIED;
	अगर (svc_getnl(argv) != 0)
		वापस SVC_DENIED;
	/* Martial context handle and token क्रम upcall: */
	*authp = rpc_autherr_badcred;
	अगर (gc->gc_proc == RPC_GSS_PROC_INIT && gc->gc_ctx.len != 0)
		वापस SVC_DENIED;
	अगर (dup_netobj(in_handle, &gc->gc_ctx))
		वापस SVC_CLOSE;
	*authp = rpc_autherr_badverf;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
gss_पढ़ो_verf(काष्ठा rpc_gss_wire_cred *gc,
	      काष्ठा kvec *argv, __be32 *authp,
	      काष्ठा xdr_netobj *in_handle,
	      काष्ठा xdr_netobj *in_token)
अणु
	काष्ठा xdr_netobj पंचांगpobj;
	पूर्णांक res;

	res = gss_पढ़ो_common_verf(gc, argv, authp, in_handle);
	अगर (res)
		वापस res;

	अगर (svc_safe_getnetobj(argv, &पंचांगpobj)) अणु
		kमुक्त(in_handle->data);
		वापस SVC_DENIED;
	पूर्ण
	अगर (dup_netobj(in_token, &पंचांगpobj)) अणु
		kमुक्त(in_handle->data);
		वापस SVC_CLOSE;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gss_मुक्त_in_token_pages(काष्ठा gssp_in_token *in_token)
अणु
	u32 inlen;
	पूर्णांक i;

	i = 0;
	inlen = in_token->page_len;
	जबतक (inlen) अणु
		अगर (in_token->pages[i])
			put_page(in_token->pages[i]);
		inlen -= inlen > PAGE_SIZE ? PAGE_SIZE : inlen;
	पूर्ण

	kमुक्त(in_token->pages);
	in_token->pages = शून्य;
पूर्ण

अटल पूर्णांक gss_पढ़ो_proxy_verf(काष्ठा svc_rqst *rqstp,
			       काष्ठा rpc_gss_wire_cred *gc, __be32 *authp,
			       काष्ठा xdr_netobj *in_handle,
			       काष्ठा gssp_in_token *in_token)
अणु
	काष्ठा kvec *argv = &rqstp->rq_arg.head[0];
	अचिन्हित पूर्णांक length, pgto_offs, pgfrom_offs;
	पूर्णांक pages, i, res, pgto, pgfrom;
	माप_प्रकार inlen, to_offs, from_offs;

	res = gss_पढ़ो_common_verf(gc, argv, authp, in_handle);
	अगर (res)
		वापस res;

	inlen = svc_getnl(argv);
	अगर (inlen > (argv->iov_len + rqstp->rq_arg.page_len))
		वापस SVC_DENIED;

	pages = DIV_ROUND_UP(inlen, PAGE_SIZE);
	in_token->pages = kसुस्मृति(pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!in_token->pages)
		वापस SVC_DENIED;
	in_token->page_base = 0;
	in_token->page_len = inlen;
	क्रम (i = 0; i < pages; i++) अणु
		in_token->pages[i] = alloc_page(GFP_KERNEL);
		अगर (!in_token->pages[i]) अणु
			gss_मुक्त_in_token_pages(in_token);
			वापस SVC_DENIED;
		पूर्ण
	पूर्ण

	length = min_t(अचिन्हित पूर्णांक, inlen, argv->iov_len);
	स_नकल(page_address(in_token->pages[0]), argv->iov_base, length);
	inlen -= length;

	to_offs = length;
	from_offs = rqstp->rq_arg.page_base;
	जबतक (inlen) अणु
		pgto = to_offs >> PAGE_SHIFT;
		pgfrom = from_offs >> PAGE_SHIFT;
		pgto_offs = to_offs & ~PAGE_MASK;
		pgfrom_offs = from_offs & ~PAGE_MASK;

		length = min_t(अचिन्हित पूर्णांक, inlen,
			 min_t(अचिन्हित पूर्णांक, PAGE_SIZE - pgto_offs,
			       PAGE_SIZE - pgfrom_offs));
		स_नकल(page_address(in_token->pages[pgto]) + pgto_offs,
		       page_address(rqstp->rq_arg.pages[pgfrom]) + pgfrom_offs,
		       length);

		to_offs += length;
		from_offs += length;
		inlen -= length;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
gss_ग_लिखो_resv(काष्ठा kvec *resv, माप_प्रकार size_limit,
	       काष्ठा xdr_netobj *out_handle, काष्ठा xdr_netobj *out_token,
	       पूर्णांक major_status, पूर्णांक minor_status)
अणु
	अगर (resv->iov_len + 4 > size_limit)
		वापस -1;
	svc_putnl(resv, RPC_SUCCESS);
	अगर (svc_safe_putnetobj(resv, out_handle))
		वापस -1;
	अगर (resv->iov_len + 3 * 4 > size_limit)
		वापस -1;
	svc_putnl(resv, major_status);
	svc_putnl(resv, minor_status);
	svc_putnl(resv, GSS_SEQ_WIN);
	अगर (svc_safe_putnetobj(resv, out_token))
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Having पढ़ो the cred alपढ़ोy and found we're in the context
 * initiation हाल, पढ़ो the verअगरier and initiate (or check the results
 * of) upcalls to userspace क्रम help with context initiation.  If
 * the upcall results are available, ग_लिखो the verअगरier and result.
 * Otherwise, drop the request pending an answer to the upcall.
 */
अटल पूर्णांक svcauth_gss_legacy_init(काष्ठा svc_rqst *rqstp,
			काष्ठा rpc_gss_wire_cred *gc, __be32 *authp)
अणु
	काष्ठा kvec *argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec *resv = &rqstp->rq_res.head[0];
	काष्ठा rsi *rsip, rsikey;
	पूर्णांक ret;
	काष्ठा sunrpc_net *sn = net_generic(SVC_NET(rqstp), sunrpc_net_id);

	स_रखो(&rsikey, 0, माप(rsikey));
	ret = gss_पढ़ो_verf(gc, argv, authp,
			    &rsikey.in_handle, &rsikey.in_token);
	अगर (ret)
		वापस ret;

	/* Perक्रमm upcall, or find upcall result: */
	rsip = rsi_lookup(sn->rsi_cache, &rsikey);
	rsi_मुक्त(&rsikey);
	अगर (!rsip)
		वापस SVC_CLOSE;
	अगर (cache_check(sn->rsi_cache, &rsip->h, &rqstp->rq_chandle) < 0)
		/* No upcall result: */
		वापस SVC_CLOSE;

	ret = SVC_CLOSE;
	/* Got an answer to the upcall; use it: */
	अगर (gss_ग_लिखो_init_verf(sn->rsc_cache, rqstp,
				&rsip->out_handle, &rsip->major_status))
		जाओ out;
	अगर (gss_ग_लिखो_resv(resv, PAGE_SIZE,
			   &rsip->out_handle, &rsip->out_token,
			   rsip->major_status, rsip->minor_status))
		जाओ out;

	ret = SVC_COMPLETE;
out:
	cache_put(&rsip->h, sn->rsi_cache);
	वापस ret;
पूर्ण

अटल पूर्णांक gss_proxy_save_rsc(काष्ठा cache_detail *cd,
				काष्ठा gssp_upcall_data *ud,
				uपूर्णांक64_t *handle)
अणु
	काष्ठा rsc rsci, *rscp = शून्य;
	अटल atomic64_t ctxhctr;
	दीर्घ दीर्घ ctxh;
	काष्ठा gss_api_mech *gm = शून्य;
	समय64_t expiry;
	पूर्णांक status = -EINVAL;

	स_रखो(&rsci, 0, माप(rsci));
	/* context handle */
	status = -ENOMEM;
	/* the handle needs to be just a unique id,
	 * use a अटल counter */
	ctxh = atomic64_inc_वापस(&ctxhctr);

	/* make a copy क्रम the caller */
	*handle = ctxh;

	/* make a copy क्रम the rsc cache */
	अगर (dup_to_netobj(&rsci.handle, (अक्षर *)handle, माप(uपूर्णांक64_t)))
		जाओ out;
	rscp = rsc_lookup(cd, &rsci);
	अगर (!rscp)
		जाओ out;

	/* creds */
	अगर (!ud->found_creds) अणु
		/* userspace seem buggy, we should always get at least a
		 * mapping to nobody */
		जाओ out;
	पूर्ण अन्यथा अणु
		काष्ठा बारpec64 boot;

		/* steal creds */
		rsci.cred = ud->creds;
		स_रखो(&ud->creds, 0, माप(काष्ठा svc_cred));

		status = -EOPNOTSUPP;
		/* get mech handle from OID */
		gm = gss_mech_get_by_OID(&ud->mech_oid);
		अगर (!gm)
			जाओ out;
		rsci.cred.cr_gss_mech = gm;

		status = -EINVAL;
		/* mech-specअगरic data: */
		status = gss_import_sec_context(ud->out_handle.data,
						ud->out_handle.len,
						gm, &rsci.mechctx,
						&expiry, GFP_KERNEL);
		अगर (status)
			जाओ out;

		getbootसमय64(&boot);
		expiry -= boot.tv_sec;
	पूर्ण

	rsci.h.expiry_समय = expiry;
	rscp = rsc_update(cd, &rsci, rscp);
	status = 0;
out:
	rsc_मुक्त(&rsci);
	अगर (rscp)
		cache_put(&rscp->h, cd);
	अन्यथा
		status = -ENOMEM;
	वापस status;
पूर्ण

अटल पूर्णांक svcauth_gss_proxy_init(काष्ठा svc_rqst *rqstp,
			काष्ठा rpc_gss_wire_cred *gc, __be32 *authp)
अणु
	काष्ठा kvec *resv = &rqstp->rq_res.head[0];
	काष्ठा xdr_netobj cli_handle;
	काष्ठा gssp_upcall_data ud;
	uपूर्णांक64_t handle;
	पूर्णांक status;
	पूर्णांक ret;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	स_रखो(&ud, 0, माप(ud));
	ret = gss_पढ़ो_proxy_verf(rqstp, gc, authp,
				  &ud.in_handle, &ud.in_token);
	अगर (ret)
		वापस ret;

	ret = SVC_CLOSE;

	/* Perक्रमm synchronous upcall to gss-proxy */
	status = gssp_accept_sec_context_upcall(net, &ud);
	अगर (status)
		जाओ out;

	trace_rpcgss_svc_accept_upcall(rqstp, ud.major_status, ud.minor_status);

	चयन (ud.major_status) अणु
	हाल GSS_S_CONTINUE_NEEDED:
		cli_handle = ud.out_handle;
		अवरोध;
	हाल GSS_S_COMPLETE:
		status = gss_proxy_save_rsc(sn->rsc_cache, &ud, &handle);
		अगर (status)
			जाओ out;
		cli_handle.data = (u8 *)&handle;
		cli_handle.len = माप(handle);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	/* Got an answer to the upcall; use it: */
	अगर (gss_ग_लिखो_init_verf(sn->rsc_cache, rqstp,
				&cli_handle, &ud.major_status))
		जाओ out;
	अगर (gss_ग_लिखो_resv(resv, PAGE_SIZE,
			   &cli_handle, &ud.out_token,
			   ud.major_status, ud.minor_status))
		जाओ out;

	ret = SVC_COMPLETE;
out:
	gss_मुक्त_in_token_pages(&ud.in_token);
	gssp_मुक्त_upcall_data(&ud);
	वापस ret;
पूर्ण

/*
 * Try to set the sn->use_gss_proxy variable to a new value. We only allow
 * it to be changed अगर it's currently undefined (-1). If it's any other value
 * then वापस -EBUSY unless the type wouldn't have changed anyway.
 */
अटल पूर्णांक set_gss_proxy(काष्ठा net *net, पूर्णांक type)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	पूर्णांक ret;

	WARN_ON_ONCE(type != 0 && type != 1);
	ret = cmpxchg(&sn->use_gss_proxy, -1, type);
	अगर (ret != -1 && ret != type)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल bool use_gss_proxy(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	/* If use_gss_proxy is still undefined, then try to disable it */
	अगर (sn->use_gss_proxy == -1)
		set_gss_proxy(net, 0);
	वापस sn->use_gss_proxy;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS

अटल sमाप_प्रकार ग_लिखो_gssp(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा net *net = PDE_DATA(file_inode(file));
	अक्षर tbuf[20];
	अचिन्हित दीर्घ i;
	पूर्णांक res;

	अगर (*ppos || count > माप(tbuf)-1)
		वापस -EINVAL;
	अगर (copy_from_user(tbuf, buf, count))
		वापस -EFAULT;

	tbuf[count] = 0;
	res = kम_से_अदीर्घ(tbuf, 0, &i);
	अगर (res)
		वापस res;
	अगर (i != 1)
		वापस -EINVAL;
	res = set_gssp_clnt(net);
	अगर (res)
		वापस res;
	res = set_gss_proxy(net, 1);
	अगर (res)
		वापस res;
	वापस count;
पूर्ण

अटल sमाप_प्रकार पढ़ो_gssp(काष्ठा file *file, अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा net *net = PDE_DATA(file_inode(file));
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	अचिन्हित दीर्घ p = *ppos;
	अक्षर tbuf[10];
	माप_प्रकार len;

	snम_लिखो(tbuf, माप(tbuf), "%d\n", sn->use_gss_proxy);
	len = म_माप(tbuf);
	अगर (p >= len)
		वापस 0;
	len -= p;
	अगर (len > count)
		len = count;
	अगर (copy_to_user(buf, (व्योम *)(tbuf+p), len))
		वापस -EFAULT;
	*ppos += len;
	वापस len;
पूर्ण

अटल स्थिर काष्ठा proc_ops use_gss_proxy_proc_ops = अणु
	.proc_खोलो	= nonseekable_खोलो,
	.proc_ग_लिखो	= ग_लिखो_gssp,
	.proc_पढ़ो	= पढ़ो_gssp,
पूर्ण;

अटल पूर्णांक create_use_gss_proxy_proc_entry(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा proc_dir_entry **p = &sn->use_gssp_proc;

	sn->use_gss_proxy = -1;
	*p = proc_create_data("use-gss-proxy", S_IFREG | 0600,
			      sn->proc_net_rpc,
			      &use_gss_proxy_proc_ops, net);
	अगर (!*p)
		वापस -ENOMEM;
	init_gssp_clnt(sn);
	वापस 0;
पूर्ण

अटल व्योम destroy_use_gss_proxy_proc_entry(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	अगर (sn->use_gssp_proc) अणु
		हटाओ_proc_entry("use-gss-proxy", sn->proc_net_rpc);
		clear_gssp_clnt(sn);
	पूर्ण
पूर्ण
#अन्यथा /* CONFIG_PROC_FS */

अटल पूर्णांक create_use_gss_proxy_proc_entry(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल व्योम destroy_use_gss_proxy_proc_entry(काष्ठा net *net) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 * Accept an rpcsec packet.
 * If context establishment, punt to user space
 * If data exchange, verअगरy/decrypt
 * If context deकाष्ठाion, handle here
 * In the context establishment and deकाष्ठाion हाल we encode
 * response here and वापस SVC_COMPLETE.
 */
अटल पूर्णांक
svcauth_gss_accept(काष्ठा svc_rqst *rqstp, __be32 *authp)
अणु
	काष्ठा kvec	*argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec	*resv = &rqstp->rq_res.head[0];
	u32		crlen;
	काष्ठा gss_svc_data *svcdata = rqstp->rq_auth_data;
	काष्ठा rpc_gss_wire_cred *gc;
	काष्ठा rsc	*rsci = शून्य;
	__be32		*rpcstart;
	__be32		*reject_stat = resv->iov_base + resv->iov_len;
	पूर्णांक		ret;
	काष्ठा sunrpc_net *sn = net_generic(SVC_NET(rqstp), sunrpc_net_id);

	*authp = rpc_autherr_badcred;
	अगर (!svcdata)
		svcdata = kदो_स्मृति(माप(*svcdata), GFP_KERNEL);
	अगर (!svcdata)
		जाओ auth_err;
	rqstp->rq_auth_data = svcdata;
	svcdata->verf_start = शून्य;
	svcdata->rsci = शून्य;
	gc = &svcdata->clcred;

	/* start of rpc packet is 7 u32's back from here:
	 * xid direction rpcversion prog vers proc flavour
	 */
	rpcstart = argv->iov_base;
	rpcstart -= 7;

	/* credential is:
	 *   version(==1), proc(0,1,2,3), seq, service (1,2,3), handle
	 * at least 5 u32s, and is preceded by length, so that makes 6.
	 */

	अगर (argv->iov_len < 5 * 4)
		जाओ auth_err;
	crlen = svc_getnl(argv);
	अगर (svc_getnl(argv) != RPC_GSS_VERSION)
		जाओ auth_err;
	gc->gc_proc = svc_getnl(argv);
	gc->gc_seq = svc_getnl(argv);
	gc->gc_svc = svc_getnl(argv);
	अगर (svc_safe_getnetobj(argv, &gc->gc_ctx))
		जाओ auth_err;
	अगर (crlen != round_up_to_quad(gc->gc_ctx.len) + 5 * 4)
		जाओ auth_err;

	अगर ((gc->gc_proc != RPC_GSS_PROC_DATA) && (rqstp->rq_proc != 0))
		जाओ auth_err;

	*authp = rpc_autherr_badverf;
	चयन (gc->gc_proc) अणु
	हाल RPC_GSS_PROC_INIT:
	हाल RPC_GSS_PROC_CONTINUE_INIT:
		अगर (use_gss_proxy(SVC_NET(rqstp)))
			वापस svcauth_gss_proxy_init(rqstp, gc, authp);
		अन्यथा
			वापस svcauth_gss_legacy_init(rqstp, gc, authp);
	हाल RPC_GSS_PROC_DATA:
	हाल RPC_GSS_PROC_DESTROY:
		/* Look up the context, and check the verअगरier: */
		*authp = rpcsec_gsserr_credproblem;
		rsci = gss_svc_searchbyctx(sn->rsc_cache, &gc->gc_ctx);
		अगर (!rsci)
			जाओ auth_err;
		चयन (gss_verअगरy_header(rqstp, rsci, rpcstart, gc, authp)) अणु
		हाल SVC_OK:
			अवरोध;
		हाल SVC_DENIED:
			जाओ auth_err;
		हाल SVC_DROP:
			जाओ drop;
		पूर्ण
		अवरोध;
	शेष:
		*authp = rpc_autherr_rejectedcred;
		जाओ auth_err;
	पूर्ण

	/* now act upon the command: */
	चयन (gc->gc_proc) अणु
	हाल RPC_GSS_PROC_DESTROY:
		अगर (gss_ग_लिखो_verf(rqstp, rsci->mechctx, gc->gc_seq))
			जाओ auth_err;
		/* Delete the entry from the cache_list and call cache_put */
		sunrpc_cache_unhash(sn->rsc_cache, &rsci->h);
		अगर (resv->iov_len + 4 > PAGE_SIZE)
			जाओ drop;
		svc_putnl(resv, RPC_SUCCESS);
		जाओ complete;
	हाल RPC_GSS_PROC_DATA:
		*authp = rpcsec_gsserr_ctxproblem;
		svcdata->verf_start = resv->iov_base + resv->iov_len;
		अगर (gss_ग_लिखो_verf(rqstp, rsci->mechctx, gc->gc_seq))
			जाओ auth_err;
		rqstp->rq_cred = rsci->cred;
		get_group_info(rsci->cred.cr_group_info);
		*authp = rpc_autherr_badcred;
		चयन (gc->gc_svc) अणु
		हाल RPC_GSS_SVC_NONE:
			अवरोध;
		हाल RPC_GSS_SVC_INTEGRITY:
			/* placeholders क्रम length and seq. number: */
			svc_putnl(resv, 0);
			svc_putnl(resv, 0);
			अगर (unwrap_पूर्णांकeg_data(rqstp, &rqstp->rq_arg,
					gc->gc_seq, rsci->mechctx))
				जाओ garbage_args;
			rqstp->rq_auth_slack = RPC_MAX_AUTH_SIZE;
			अवरोध;
		हाल RPC_GSS_SVC_PRIVACY:
			/* placeholders क्रम length and seq. number: */
			svc_putnl(resv, 0);
			svc_putnl(resv, 0);
			अगर (unwrap_priv_data(rqstp, &rqstp->rq_arg,
					gc->gc_seq, rsci->mechctx))
				जाओ garbage_args;
			rqstp->rq_auth_slack = RPC_MAX_AUTH_SIZE * 2;
			अवरोध;
		शेष:
			जाओ auth_err;
		पूर्ण
		svcdata->rsci = rsci;
		cache_get(&rsci->h);
		rqstp->rq_cred.cr_flavor = gss_svc_to_pseuकरोflavor(
					rsci->mechctx->mech_type,
					GSS_C_QOP_DEFAULT,
					gc->gc_svc);
		ret = SVC_OK;
		trace_rpcgss_svc_authenticate(rqstp, gc);
		जाओ out;
	पूर्ण
garbage_args:
	ret = SVC_GARBAGE;
	जाओ out;
auth_err:
	/* Restore ग_लिखो poपूर्णांकer to its original value: */
	xdr_ressize_check(rqstp, reject_stat);
	ret = SVC_DENIED;
	जाओ out;
complete:
	ret = SVC_COMPLETE;
	जाओ out;
drop:
	ret = SVC_CLOSE;
out:
	अगर (rsci)
		cache_put(&rsci->h, sn->rsc_cache);
	वापस ret;
पूर्ण

अटल __be32 *
svcauth_gss_prepare_to_wrap(काष्ठा xdr_buf *resbuf, काष्ठा gss_svc_data *gsd)
अणु
	__be32 *p;
	u32 verf_len;

	p = gsd->verf_start;
	gsd->verf_start = शून्य;

	/* If the reply stat is nonzero, करोn't wrap: */
	अगर (*(p-1) != rpc_success)
		वापस शून्य;
	/* Skip the verअगरier: */
	p += 1;
	verf_len = ntohl(*p++);
	p += XDR_QUADLEN(verf_len);
	/* move accept_stat to right place: */
	स_नकल(p, p + 2, 4);
	/* Also करोn't wrap अगर the accept stat is nonzero: */
	अगर (*p != rpc_success) अणु
		resbuf->head[0].iov_len -= 2 * 4;
		वापस शून्य;
	पूर्ण
	p++;
	वापस p;
पूर्ण

अटल अंतरभूत पूर्णांक
svcauth_gss_wrap_resp_पूर्णांकeg(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा gss_svc_data *gsd = (काष्ठा gss_svc_data *)rqstp->rq_auth_data;
	काष्ठा rpc_gss_wire_cred *gc = &gsd->clcred;
	काष्ठा xdr_buf *resbuf = &rqstp->rq_res;
	काष्ठा xdr_buf पूर्णांकeg_buf;
	काष्ठा xdr_netobj mic;
	काष्ठा kvec *resv;
	__be32 *p;
	पूर्णांक पूर्णांकeg_offset, पूर्णांकeg_len;
	पूर्णांक stat = -EINVAL;

	p = svcauth_gss_prepare_to_wrap(resbuf, gsd);
	अगर (p == शून्य)
		जाओ out;
	पूर्णांकeg_offset = (u8 *)(p + 1) - (u8 *)resbuf->head[0].iov_base;
	पूर्णांकeg_len = resbuf->len - पूर्णांकeg_offset;
	अगर (पूर्णांकeg_len & 3)
		जाओ out;
	*p++ = htonl(पूर्णांकeg_len);
	*p++ = htonl(gc->gc_seq);
	अगर (xdr_buf_subsegment(resbuf, &पूर्णांकeg_buf, पूर्णांकeg_offset, पूर्णांकeg_len)) अणु
		WARN_ON_ONCE(1);
		जाओ out_err;
	पूर्ण
	अगर (resbuf->tail[0].iov_base == शून्य) अणु
		अगर (resbuf->head[0].iov_len + RPC_MAX_AUTH_SIZE > PAGE_SIZE)
			जाओ out_err;
		resbuf->tail[0].iov_base = resbuf->head[0].iov_base
						+ resbuf->head[0].iov_len;
		resbuf->tail[0].iov_len = 0;
	पूर्ण
	resv = &resbuf->tail[0];
	mic.data = (u8 *)resv->iov_base + resv->iov_len + 4;
	अगर (gss_get_mic(gsd->rsci->mechctx, &पूर्णांकeg_buf, &mic))
		जाओ out_err;
	svc_putnl(resv, mic.len);
	स_रखो(mic.data + mic.len, 0,
			round_up_to_quad(mic.len) - mic.len);
	resv->iov_len += XDR_QUADLEN(mic.len) << 2;
	/* not strictly required: */
	resbuf->len += XDR_QUADLEN(mic.len) << 2;
	अगर (resv->iov_len > PAGE_SIZE)
		जाओ out_err;
out:
	stat = 0;
out_err:
	वापस stat;
पूर्ण

अटल अंतरभूत पूर्णांक
svcauth_gss_wrap_resp_priv(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा gss_svc_data *gsd = (काष्ठा gss_svc_data *)rqstp->rq_auth_data;
	काष्ठा rpc_gss_wire_cred *gc = &gsd->clcred;
	काष्ठा xdr_buf *resbuf = &rqstp->rq_res;
	काष्ठा page **inpages = शून्य;
	__be32 *p, *len;
	पूर्णांक offset;
	पूर्णांक pad;

	p = svcauth_gss_prepare_to_wrap(resbuf, gsd);
	अगर (p == शून्य)
		वापस 0;
	len = p++;
	offset = (u8 *)p - (u8 *)resbuf->head[0].iov_base;
	*p++ = htonl(gc->gc_seq);
	inpages = resbuf->pages;
	/* XXX: Would be better to ग_लिखो some xdr helper functions क्रम
	 * nfsअणु2,3,4पूर्णxdr.c that place the data right, instead of copying: */

	/*
	 * If there is currently tail data, make sure there is
	 * room क्रम the head, tail, and 2 * RPC_MAX_AUTH_SIZE in
	 * the page, and move the current tail data such that
	 * there is RPC_MAX_AUTH_SIZE slack space available in
	 * both the head and tail.
	 */
	अगर (resbuf->tail[0].iov_base) अणु
		अगर (resbuf->tail[0].iov_base >=
			resbuf->head[0].iov_base + PAGE_SIZE)
			वापस -EINVAL;
		अगर (resbuf->tail[0].iov_base < resbuf->head[0].iov_base)
			वापस -EINVAL;
		अगर (resbuf->tail[0].iov_len + resbuf->head[0].iov_len
				+ 2 * RPC_MAX_AUTH_SIZE > PAGE_SIZE)
			वापस -ENOMEM;
		स_हटाओ(resbuf->tail[0].iov_base + RPC_MAX_AUTH_SIZE,
			resbuf->tail[0].iov_base,
			resbuf->tail[0].iov_len);
		resbuf->tail[0].iov_base += RPC_MAX_AUTH_SIZE;
	पूर्ण
	/*
	 * If there is no current tail data, make sure there is
	 * room क्रम the head data, and 2 * RPC_MAX_AUTH_SIZE in the
	 * allotted page, and set up tail inक्रमmation such that there
	 * is RPC_MAX_AUTH_SIZE slack space available in both the
	 * head and tail.
	 */
	अगर (resbuf->tail[0].iov_base == शून्य) अणु
		अगर (resbuf->head[0].iov_len + 2*RPC_MAX_AUTH_SIZE > PAGE_SIZE)
			वापस -ENOMEM;
		resbuf->tail[0].iov_base = resbuf->head[0].iov_base
			+ resbuf->head[0].iov_len + RPC_MAX_AUTH_SIZE;
		resbuf->tail[0].iov_len = 0;
	पूर्ण
	अगर (gss_wrap(gsd->rsci->mechctx, offset, resbuf, inpages))
		वापस -ENOMEM;
	*len = htonl(resbuf->len - offset);
	pad = 3 - ((resbuf->len - offset - 1)&3);
	p = (__be32 *)(resbuf->tail[0].iov_base + resbuf->tail[0].iov_len);
	स_रखो(p, 0, pad);
	resbuf->tail[0].iov_len += pad;
	resbuf->len += pad;
	वापस 0;
पूर्ण

अटल पूर्णांक
svcauth_gss_release(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा gss_svc_data *gsd = (काष्ठा gss_svc_data *)rqstp->rq_auth_data;
	काष्ठा rpc_gss_wire_cred *gc;
	काष्ठा xdr_buf *resbuf = &rqstp->rq_res;
	पूर्णांक stat = -EINVAL;
	काष्ठा sunrpc_net *sn = net_generic(SVC_NET(rqstp), sunrpc_net_id);

	अगर (!gsd)
		जाओ out;
	gc = &gsd->clcred;
	अगर (gc->gc_proc != RPC_GSS_PROC_DATA)
		जाओ out;
	/* Release can be called twice, but we only wrap once. */
	अगर (gsd->verf_start == शून्य)
		जाओ out;
	/* normally not set till svc_send, but we need it here: */
	/* XXX: what क्रम?  Do we mess it up the moment we call svc_putu32
	 * or whatever? */
	resbuf->len = total_buf_len(resbuf);
	चयन (gc->gc_svc) अणु
	हाल RPC_GSS_SVC_NONE:
		अवरोध;
	हाल RPC_GSS_SVC_INTEGRITY:
		stat = svcauth_gss_wrap_resp_पूर्णांकeg(rqstp);
		अगर (stat)
			जाओ out_err;
		अवरोध;
	हाल RPC_GSS_SVC_PRIVACY:
		stat = svcauth_gss_wrap_resp_priv(rqstp);
		अगर (stat)
			जाओ out_err;
		अवरोध;
	/*
	 * For any other gc_svc value, svcauth_gss_accept() alपढ़ोy set
	 * the auth_error appropriately; just fall through:
	 */
	पूर्ण

out:
	stat = 0;
out_err:
	अगर (rqstp->rq_client)
		auth_करोमुख्य_put(rqstp->rq_client);
	rqstp->rq_client = शून्य;
	अगर (rqstp->rq_gssclient)
		auth_करोमुख्य_put(rqstp->rq_gssclient);
	rqstp->rq_gssclient = शून्य;
	अगर (rqstp->rq_cred.cr_group_info)
		put_group_info(rqstp->rq_cred.cr_group_info);
	rqstp->rq_cred.cr_group_info = शून्य;
	अगर (gsd && gsd->rsci) अणु
		cache_put(&gsd->rsci->h, sn->rsc_cache);
		gsd->rsci = शून्य;
	पूर्ण
	वापस stat;
पूर्ण

अटल व्योम
svcauth_gss_करोमुख्य_release_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा auth_करोमुख्य *करोm = container_of(head, काष्ठा auth_करोमुख्य, rcu_head);
	काष्ठा gss_करोमुख्य *gd = container_of(करोm, काष्ठा gss_करोमुख्य, h);

	kमुक्त(करोm->name);
	kमुक्त(gd);
पूर्ण

अटल व्योम
svcauth_gss_करोमुख्य_release(काष्ठा auth_करोमुख्य *करोm)
अणु
	call_rcu(&करोm->rcu_head, svcauth_gss_करोमुख्य_release_rcu);
पूर्ण

अटल काष्ठा auth_ops svcauthops_gss = अणु
	.name		= "rpcsec_gss",
	.owner		= THIS_MODULE,
	.flavour	= RPC_AUTH_GSS,
	.accept		= svcauth_gss_accept,
	.release	= svcauth_gss_release,
	.करोमुख्य_release = svcauth_gss_करोमुख्य_release,
	.set_client	= svcauth_gss_set_client,
पूर्ण;

अटल पूर्णांक rsi_cache_create_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd;
	पूर्णांक err;

	cd = cache_create_net(&rsi_cache_ढाँचा, net);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);
	err = cache_रेजिस्टर_net(cd, net);
	अगर (err) अणु
		cache_destroy_net(cd, net);
		वापस err;
	पूर्ण
	sn->rsi_cache = cd;
	वापस 0;
पूर्ण

अटल व्योम rsi_cache_destroy_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd = sn->rsi_cache;

	sn->rsi_cache = शून्य;
	cache_purge(cd);
	cache_unरेजिस्टर_net(cd, net);
	cache_destroy_net(cd, net);
पूर्ण

अटल पूर्णांक rsc_cache_create_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd;
	पूर्णांक err;

	cd = cache_create_net(&rsc_cache_ढाँचा, net);
	अगर (IS_ERR(cd))
		वापस PTR_ERR(cd);
	err = cache_रेजिस्टर_net(cd, net);
	अगर (err) अणु
		cache_destroy_net(cd, net);
		वापस err;
	पूर्ण
	sn->rsc_cache = cd;
	वापस 0;
पूर्ण

अटल व्योम rsc_cache_destroy_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा cache_detail *cd = sn->rsc_cache;

	sn->rsc_cache = शून्य;
	cache_purge(cd);
	cache_unरेजिस्टर_net(cd, net);
	cache_destroy_net(cd, net);
पूर्ण

पूर्णांक
gss_svc_init_net(काष्ठा net *net)
अणु
	पूर्णांक rv;

	rv = rsc_cache_create_net(net);
	अगर (rv)
		वापस rv;
	rv = rsi_cache_create_net(net);
	अगर (rv)
		जाओ out1;
	rv = create_use_gss_proxy_proc_entry(net);
	अगर (rv)
		जाओ out2;
	वापस 0;
out2:
	destroy_use_gss_proxy_proc_entry(net);
out1:
	rsc_cache_destroy_net(net);
	वापस rv;
पूर्ण

व्योम
gss_svc_shutकरोwn_net(काष्ठा net *net)
अणु
	destroy_use_gss_proxy_proc_entry(net);
	rsi_cache_destroy_net(net);
	rsc_cache_destroy_net(net);
पूर्ण

पूर्णांक
gss_svc_init(व्योम)
अणु
	वापस svc_auth_रेजिस्टर(RPC_AUTH_GSS, &svcauthops_gss);
पूर्ण

व्योम
gss_svc_shutकरोwn(व्योम)
अणु
	svc_auth_unरेजिस्टर(RPC_AUTH_GSS);
पूर्ण
