<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Process version 2 NFSACL requests.
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

#घोषणा NFSDDBG_FACILITY		NFSDDBG_PROC

/*
 * शून्य call.
 */
अटल __be32
nfsacld_proc_null(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

/*
 * Get the Access and/or Default ACL of a file.
 */
अटल __be32 nfsacld_proc_getacl(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_getaclargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_getaclres *resp = rqstp->rq_resp;
	काष्ठा posix_acl *acl;
	काष्ठा inode *inode;
	svc_fh *fh;

	dprपूर्णांकk("nfsd: GETACL(2acl)   %s\n", SVCFH_fmt(&argp->fh));

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

	resp->status = fh_getattr(fh, &resp->stat);
	अगर (resp->status != nfs_ok)
		जाओ out;

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

	/* resp->acl_अणुaccess,शेषपूर्ण are released in nfssvc_release_getacl. */
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
अटल __be32 nfsacld_proc_setacl(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_setaclargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;
	काष्ठा inode *inode;
	svc_fh *fh;
	पूर्णांक error;

	dprपूर्णांकk("nfsd: SETACL(2acl)   %s\n", SVCFH_fmt(&argp->fh));

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
	अगर (error)
		जाओ out_drop_lock;

	fh_unlock(fh);

	fh_drop_ग_लिखो(fh);

	resp->status = fh_getattr(fh, &resp->stat);

out:
	/* argp->acl_अणुaccess,शेषपूर्ण may have been allocated in
	   nfssvc_decode_setaclargs. */
	posix_acl_release(argp->acl_access);
	posix_acl_release(argp->acl_शेष);
	वापस rpc_success;

out_drop_lock:
	fh_unlock(fh);
	fh_drop_ग_लिखो(fh);
out_त्रुटि_सं:
	resp->status = nfsत्रुटि_सं(error);
	जाओ out;
पूर्ण

/*
 * Check file attributes
 */
अटल __be32 nfsacld_proc_getattr(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: GETATTR  %s\n", SVCFH_fmt(&argp->fh));

	fh_copy(&resp->fh, &argp->fh);
	resp->status = fh_verअगरy(rqstp, &resp->fh, 0, NFSD_MAY_NOP);
	अगर (resp->status != nfs_ok)
		जाओ out;
	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

/*
 * Check file access
 */
अटल __be32 nfsacld_proc_access(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_accessargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_accessres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: ACCESS(2acl)   %s 0x%x\n",
			SVCFH_fmt(&argp->fh),
			argp->access);

	fh_copy(&resp->fh, &argp->fh);
	resp->access = argp->access;
	resp->status = nfsd_access(rqstp, &resp->fh, &resp->access, शून्य);
	अगर (resp->status != nfs_ok)
		जाओ out;
	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

/*
 * XDR decode functions
 */

अटल पूर्णांक nfsaclsvc_decode_getaclargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_getaclargs *argp = rqstp->rq_argp;

	अगर (!svcxdr_decode_fhandle(xdr, &argp->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &argp->mask) < 0)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक nfsaclsvc_decode_setaclargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_setaclargs *argp = rqstp->rq_argp;

	अगर (!svcxdr_decode_fhandle(xdr, &argp->fh))
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

अटल पूर्णांक nfsaclsvc_decode_accessargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_accessargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_fhandle(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->access) < 0)
		वापस 0;

	वापस 1;
पूर्ण

/*
 * XDR encode functions
 */

/* GETACL */
अटल पूर्णांक nfsaclsvc_encode_getaclres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_getaclres *resp = rqstp->rq_resp;
	काष्ठा dentry *dentry = resp->fh.fh_dentry;
	काष्ठा inode *inode;
	पूर्णांक w;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;

	अगर (dentry == शून्य || d_really_is_negative(dentry))
		वापस 1;
	inode = d_inode(dentry);

	अगर (!svcxdr_encode_fattr(rqstp, xdr, &resp->fh, &resp->stat))
		वापस 0;
	अगर (xdr_stream_encode_u32(xdr, resp->mask) < 0)
		वापस 0;

	rqstp->rq_res.page_len = w = nfsacl_size(
		(resp->mask & NFS_ACL)   ? resp->acl_access  : शून्य,
		(resp->mask & NFS_DFACL) ? resp->acl_शेष : शून्य);
	जबतक (w > 0) अणु
		अगर (!*(rqstp->rq_next_page++))
			वापस 1;
		w -= PAGE_SIZE;
	पूर्ण

	अगर (!nfs_stream_encode_acl(xdr, inode, resp->acl_access,
				   resp->mask & NFS_ACL, 0))
		वापस 0;
	अगर (!nfs_stream_encode_acl(xdr, inode, resp->acl_शेष,
				   resp->mask & NFS_DFACL, NFS_ACL_DEFAULT))
		वापस 0;

	वापस 1;
पूर्ण

/* ACCESS */
अटल पूर्णांक nfsaclsvc_encode_accessres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_accessres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_fattr(rqstp, xdr, &resp->fh, &resp->stat))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->access) < 0)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * XDR release functions
 */
अटल व्योम nfsaclsvc_release_getacl(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_getaclres *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
	posix_acl_release(resp->acl_access);
	posix_acl_release(resp->acl_शेष);
पूर्ण

अटल व्योम nfsaclsvc_release_access(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_accessres *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
पूर्ण

काष्ठा nfsd3_व्योमargs अणु पूर्णांक dummy; पूर्ण;

#घोषणा ST 1		/* status*/
#घोषणा AT 21		/* attributes */
#घोषणा pAT (1+AT)	/* post attributes - conditional */
#घोषणा ACL (1+NFS_ACL_MAX_ENTRIES*3)  /* Access Control List */

अटल स्थिर काष्ठा svc_procedure nfsd_acl_procedures2[5] = अणु
	[ACLPROC2_शून्य] = अणु
		.pc_func = nfsacld_proc_null,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST,
		.pc_name = "NULL",
	पूर्ण,
	[ACLPROC2_GETACL] = अणु
		.pc_func = nfsacld_proc_getacl,
		.pc_decode = nfsaclsvc_decode_getaclargs,
		.pc_encode = nfsaclsvc_encode_getaclres,
		.pc_release = nfsaclsvc_release_getacl,
		.pc_argsize = माप(काष्ठा nfsd3_getaclargs),
		.pc_ressize = माप(काष्ठा nfsd3_getaclres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+1+2*(1+ACL),
		.pc_name = "GETACL",
	पूर्ण,
	[ACLPROC2_SETACL] = अणु
		.pc_func = nfsacld_proc_setacl,
		.pc_decode = nfsaclsvc_decode_setaclargs,
		.pc_encode = nfssvc_encode_attrstatres,
		.pc_release = nfssvc_release_attrstat,
		.pc_argsize = माप(काष्ठा nfsd3_setaclargs),
		.pc_ressize = माप(काष्ठा nfsd_attrstat),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+AT,
		.pc_name = "SETACL",
	पूर्ण,
	[ACLPROC2_GETATTR] = अणु
		.pc_func = nfsacld_proc_getattr,
		.pc_decode = nfssvc_decode_fhandleargs,
		.pc_encode = nfssvc_encode_attrstatres,
		.pc_release = nfssvc_release_attrstat,
		.pc_argsize = माप(काष्ठा nfsd_fhandle),
		.pc_ressize = माप(काष्ठा nfsd_attrstat),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+AT,
		.pc_name = "GETATTR",
	पूर्ण,
	[ACLPROC2_ACCESS] = अणु
		.pc_func = nfsacld_proc_access,
		.pc_decode = nfsaclsvc_decode_accessargs,
		.pc_encode = nfsaclsvc_encode_accessres,
		.pc_release = nfsaclsvc_release_access,
		.pc_argsize = माप(काष्ठा nfsd3_accessargs),
		.pc_ressize = माप(काष्ठा nfsd3_accessres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+AT+1,
		.pc_name = "SETATTR",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nfsd_acl_count2[ARRAY_SIZE(nfsd_acl_procedures2)];
स्थिर काष्ठा svc_version nfsd_acl_version2 = अणु
	.vs_vers	= 2,
	.vs_nproc	= 5,
	.vs_proc	= nfsd_acl_procedures2,
	.vs_count	= nfsd_acl_count2,
	.vs_dispatch	= nfsd_dispatch,
	.vs_xdrsize	= NFS3_SVC_XDRSIZE,
पूर्ण;
