<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Process version 3 NFSACL requests.
 *
 * Copyright (C) 2002-2003 Andreas Gruenbacher <agruen@suse.de>
 */

#समावेश "nfsd.h"
/* FIXME: nfsacl.h is a broken header */
#समावेश <linux/nfsacl.h>
#समावेश <linux/gfp.h>
#समावेश "cache.h"
#समावेश "xdr3.h"
#समावेश "vfs.h"

/*
 * शून्य call.
 */
अटल __be32
nfsd3_proc_null(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

/*
 * Get the Access and/or Default ACL of a file.
 */
अटल __be32 nfsd3_proc_getacl(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_getaclargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_getaclres *resp = rqstp->rq_resp;
	काष्ठा posix_acl *acl;
	काष्ठा inode *inode;
	svc_fh *fh;

	fh = fh_copy(&resp->fh, &argp->fh);
	resp->status = fh_verअगरy(rqstp, &resp->fh, 0, NFSD_MAY_NOP);
	अगर (resp->status != nfs_ok)
		जाओ out;

	inode = d_inode(fh->fh_dentry);

	अगर (argp->mask & ~NFS_ACL_MASK) अणु
		resp->status = nfserr_inval;
		जाओ out;
	पूर्ण
	resp->mask = argp->mask;

	अगर (resp->mask & (NFS_ACL|NFS_ACLCNT)) अणु
		acl = get_acl(inode, ACL_TYPE_ACCESS);
		अगर (acl == शून्य) अणु
			/* Solaris वापसs the inode's minimum ACL. */
			acl = posix_acl_from_mode(inode->i_mode, GFP_KERNEL);
		पूर्ण
		अगर (IS_ERR(acl)) अणु
			resp->status = nfsत्रुटि_सं(PTR_ERR(acl));
			जाओ fail;
		पूर्ण
		resp->acl_access = acl;
	पूर्ण
	अगर (resp->mask & (NFS_DFACL|NFS_DFACLCNT)) अणु
		/* Check how Solaris handles requests क्रम the Default ACL
		   of a non-directory! */
		acl = get_acl(inode, ACL_TYPE_DEFAULT);
		अगर (IS_ERR(acl)) अणु
			resp->status = nfsत्रुटि_सं(PTR_ERR(acl));
			जाओ fail;
		पूर्ण
		resp->acl_शेष = acl;
	पूर्ण

	/* resp->acl_अणुaccess,शेषपूर्ण are released in nfs3svc_release_getacl. */
out:
	वापस rpc_success;

fail:
	posix_acl_release(resp->acl_access);
	posix_acl_release(resp->acl_शेष);
	जाओ out;
पूर्ण

/*
 * Set the Access and/or Default ACL of a file.
 */
अटल __be32 nfsd3_proc_setacl(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_setaclargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;
	काष्ठा inode *inode;
	svc_fh *fh;
	पूर्णांक error;

	fh = fh_copy(&resp->fh, &argp->fh);
	resp->status = fh_verअगरy(rqstp, &resp->fh, 0, NFSD_MAY_SATTR);
	अगर (resp->status != nfs_ok)
		जाओ out;

	inode = d_inode(fh->fh_dentry);

	error = fh_want_ग_लिखो(fh);
	अगर (error)
		जाओ out_त्रुटि_सं;

	fh_lock(fh);

	error = set_posix_acl(&init_user_ns, inode, ACL_TYPE_ACCESS,
			      argp->acl_access);
	अगर (error)
		जाओ out_drop_lock;
	error = set_posix_acl(&init_user_ns, inode, ACL_TYPE_DEFAULT,
			      argp->acl_शेष);

out_drop_lock:
	fh_unlock(fh);
	fh_drop_ग_लिखो(fh);
out_त्रुटि_सं:
	resp->status = nfsत्रुटि_सं(error);
out:
	/* argp->acl_अणुaccess,शेषपूर्ण may have been allocated in
	   nfs3svc_decode_setaclargs. */
	posix_acl_release(argp->acl_access);
	posix_acl_release(argp->acl_शेष);
	वापस rpc_success;
पूर्ण

/*
 * XDR decode functions
 */

अटल पूर्णांक nfs3svc_decode_getaclargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_getaclargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->mask) < 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक nfs3svc_decode_setaclargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_setaclargs *argp = rqstp->rq_argp;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &argp->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &argp->mask) < 0)
		वापस 0;
	अगर (argp->mask & ~NFS_ACL_MASK)
		वापस 0;
	अगर (!nfs_stream_decode_acl(xdr, शून्य, (argp->mask & NFS_ACL) ?
				   &argp->acl_access : शून्य))
		वापस 0;
	अगर (!nfs_stream_decode_acl(xdr, शून्य, (argp->mask & NFS_DFACL) ?
				   &argp->acl_शेष : शून्य))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * XDR encode functions
 */

/* GETACL */
अटल पूर्णांक nfs3svc_encode_getaclres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_getaclres *resp = rqstp->rq_resp;
	काष्ठा dentry *dentry = resp->fh.fh_dentry;
	काष्ठा kvec *head = rqstp->rq_res.head;
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक base;
	पूर्णांक n;
	पूर्णांक w;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->mask) < 0)
			वापस 0;

		base = (अक्षर *)xdr->p - (अक्षर *)head->iov_base;

		rqstp->rq_res.page_len = w = nfsacl_size(
			(resp->mask & NFS_ACL)   ? resp->acl_access  : शून्य,
			(resp->mask & NFS_DFACL) ? resp->acl_शेष : शून्य);
		जबतक (w > 0) अणु
			अगर (!*(rqstp->rq_next_page++))
				वापस 0;
			w -= PAGE_SIZE;
		पूर्ण

		n = nfsacl_encode(&rqstp->rq_res, base, inode,
				  resp->acl_access,
				  resp->mask & NFS_ACL, 0);
		अगर (n > 0)
			n = nfsacl_encode(&rqstp->rq_res, base + n, inode,
					  resp->acl_शेष,
					  resp->mask & NFS_DFACL,
					  NFS_ACL_DEFAULT);
		अगर (n <= 0)
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* SETACL */
अटल पूर्णांक nfs3svc_encode_setaclres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	वापस svcxdr_encode_nfsstat3(xdr, resp->status) &&
		svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh);
पूर्ण

/*
 * XDR release functions
 */
अटल व्योम nfs3svc_release_getacl(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_getaclres *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
	posix_acl_release(resp->acl_access);
	posix_acl_release(resp->acl_शेष);
पूर्ण

काष्ठा nfsd3_व्योमargs अणु पूर्णांक dummy; पूर्ण;

#घोषणा ST 1		/* status*/
#घोषणा AT 21		/* attributes */
#घोषणा pAT (1+AT)	/* post attributes - conditional */
#घोषणा ACL (1+NFS_ACL_MAX_ENTRIES*3)  /* Access Control List */

अटल स्थिर काष्ठा svc_procedure nfsd_acl_procedures3[3] = अणु
	[ACLPROC3_शून्य] = अणु
		.pc_func = nfsd3_proc_null,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST,
		.pc_name = "NULL",
	पूर्ण,
	[ACLPROC3_GETACL] = अणु
		.pc_func = nfsd3_proc_getacl,
		.pc_decode = nfs3svc_decode_getaclargs,
		.pc_encode = nfs3svc_encode_getaclres,
		.pc_release = nfs3svc_release_getacl,
		.pc_argsize = माप(काष्ठा nfsd3_getaclargs),
		.pc_ressize = माप(काष्ठा nfsd3_getaclres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+1+2*(1+ACL),
		.pc_name = "GETACL",
	पूर्ण,
	[ACLPROC3_SETACL] = अणु
		.pc_func = nfsd3_proc_setacl,
		.pc_decode = nfs3svc_decode_setaclargs,
		.pc_encode = nfs3svc_encode_setaclres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_setaclargs),
		.pc_ressize = माप(काष्ठा nfsd3_attrstat),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT,
		.pc_name = "SETACL",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nfsd_acl_count3[ARRAY_SIZE(nfsd_acl_procedures3)];
स्थिर काष्ठा svc_version nfsd_acl_version3 = अणु
	.vs_vers	= 3,
	.vs_nproc	= 3,
	.vs_proc	= nfsd_acl_procedures3,
	.vs_count	= nfsd_acl_count3,
	.vs_dispatch	= nfsd_dispatch,
	.vs_xdrsize	= NFS3_SVC_XDRSIZE,
पूर्ण;

