<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * XDR support क्रम nfsd/protocol version 3.
 *
 * Copyright (C) 1995, 1996, 1997 Olaf Kirch <okir@monad.swb.de>
 *
 * 2003-08-09 Jamie Lokier: Use htonl() क्रम nanoseconds, not htons()!
 */

#समावेश <linux/namei.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश "xdr3.h"
#समावेश "auth.h"
#समावेश "netns.h"
#समावेश "vfs.h"

/*
 * Force स्थिरruction of an empty post-op attr
 */
अटल स्थिर काष्ठा svc_fh nfs3svc_null_fh = अणु
	.fh_no_wcc	= true,
पूर्ण;

/*
 * समय_delta. अणु1, 0पूर्ण means the server is accurate only
 * to the nearest second.
 */
अटल स्थिर काष्ठा बारpec64 nfs3svc_समय_delta = अणु
	.tv_sec		= 1,
	.tv_nsec	= 0,
पूर्ण;

/*
 * Mapping of S_IF* types to NFS file types
 */
अटल स्थिर u32 nfs3_ftypes[] = अणु
	NF3NON,  NF3FIFO, NF3CHR, NF3BAD,
	NF3सूची,  NF3BAD,  NF3BLK, NF3BAD,
	NF3REG,  NF3BAD,  NF3LNK, NF3BAD,
	NF3SOCK, NF3BAD,  NF3LNK, NF3BAD,
पूर्ण;


/*
 * Basic NFSv3 data types (RFC 1813 Sections 2.5 and 2.6)
 */

अटल __be32 *
encode_nfsसमय3(__be32 *p, स्थिर काष्ठा बारpec64 *समय)
अणु
	*p++ = cpu_to_be32((u32)समय->tv_sec);
	*p++ = cpu_to_be32(समय->tv_nsec);

	वापस p;
पूर्ण

अटल bool
svcxdr_decode_nfsसमय3(काष्ठा xdr_stream *xdr, काष्ठा बारpec64 *समयp)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, XDR_UNIT * 2);
	अगर (!p)
		वापस false;
	समयp->tv_sec = be32_to_cpup(p++);
	समयp->tv_nsec = be32_to_cpup(p);

	वापस true;
पूर्ण

/**
 * svcxdr_decode_nfs_fh3 - Decode an NFSv3 file handle
 * @xdr: XDR stream positioned at an undecoded NFSv3 FH
 * @fhp: OUT: filled-in server file handle
 *
 * Return values:
 *  %false: The encoded file handle was not valid
 *  %true: @fhp has been initialized
 */
bool
svcxdr_decode_nfs_fh3(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp)
अणु
	__be32 *p;
	u32 size;

	अगर (xdr_stream_decode_u32(xdr, &size) < 0)
		वापस false;
	अगर (size == 0 || size > NFS3_FHSIZE)
		वापस false;
	p = xdr_अंतरभूत_decode(xdr, size);
	अगर (!p)
		वापस false;
	fh_init(fhp, NFS3_FHSIZE);
	fhp->fh_handle.fh_size = size;
	स_नकल(&fhp->fh_handle.fh_base, p, size);

	वापस true;
पूर्ण

/**
 * svcxdr_encode_nfsstat3 - Encode an NFSv3 status code
 * @xdr: XDR stream
 * @status: status value to encode
 *
 * Return values:
 *   %false: Send buffer space was exhausted
 *   %true: Success
 */
bool
svcxdr_encode_nfsstat3(काष्ठा xdr_stream *xdr, __be32 status)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, माप(status));
	अगर (!p)
		वापस false;
	*p = status;

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_nfs_fh3(काष्ठा xdr_stream *xdr, स्थिर काष्ठा svc_fh *fhp)
अणु
	u32 size = fhp->fh_handle.fh_size;
	__be32 *p;

	p = xdr_reserve_space(xdr, XDR_UNIT + size);
	अगर (!p)
		वापस false;
	*p++ = cpu_to_be32(size);
	अगर (size)
		p[XDR_QUADLEN(size) - 1] = 0;
	स_नकल(p, &fhp->fh_handle.fh_base, size);

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_post_op_fh3(काष्ठा xdr_stream *xdr, स्थिर काष्ठा svc_fh *fhp)
अणु
	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस false;
	अगर (!svcxdr_encode_nfs_fh3(xdr, fhp))
		वापस false;

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_cookieverf3(काष्ठा xdr_stream *xdr, स्थिर __be32 *verf)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS3_COOKIEVERFSIZE);
	अगर (!p)
		वापस false;
	स_नकल(p, verf, NFS3_COOKIEVERFSIZE);

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_ग_लिखोverf3(काष्ठा xdr_stream *xdr, स्थिर __be32 *verf)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS3_WRITEVERFSIZE);
	अगर (!p)
		वापस false;
	स_नकल(p, verf, NFS3_WRITEVERFSIZE);

	वापस true;
पूर्ण

अटल bool
svcxdr_decode_filename3(काष्ठा xdr_stream *xdr, अक्षर **name, अचिन्हित पूर्णांक *len)
अणु
	u32 size, i;
	__be32 *p;
	अक्षर *c;

	अगर (xdr_stream_decode_u32(xdr, &size) < 0)
		वापस false;
	अगर (size == 0 || size > NFS3_MAXNAMLEN)
		वापस false;
	p = xdr_अंतरभूत_decode(xdr, size);
	अगर (!p)
		वापस false;

	*len = size;
	*name = (अक्षर *)p;
	क्रम (i = 0, c = *name; i < size; i++, c++) अणु
		अगर (*c == '\0' || *c == '/')
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
svcxdr_decode_diropargs3(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp,
			 अक्षर **name, अचिन्हित पूर्णांक *len)
अणु
	वापस svcxdr_decode_nfs_fh3(xdr, fhp) &&
		svcxdr_decode_filename3(xdr, name, len);
पूर्ण

अटल bool
svcxdr_decode_sattr3(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		     काष्ठा iattr *iap)
अणु
	u32 set_it;

	iap->ia_valid = 0;

	अगर (xdr_stream_decode_bool(xdr, &set_it) < 0)
		वापस false;
	अगर (set_it) अणु
		u32 mode;

		अगर (xdr_stream_decode_u32(xdr, &mode) < 0)
			वापस false;
		iap->ia_valid |= ATTR_MODE;
		iap->ia_mode = mode;
	पूर्ण
	अगर (xdr_stream_decode_bool(xdr, &set_it) < 0)
		वापस false;
	अगर (set_it) अणु
		u32 uid;

		अगर (xdr_stream_decode_u32(xdr, &uid) < 0)
			वापस false;
		iap->ia_uid = make_kuid(nfsd_user_namespace(rqstp), uid);
		अगर (uid_valid(iap->ia_uid))
			iap->ia_valid |= ATTR_UID;
	पूर्ण
	अगर (xdr_stream_decode_bool(xdr, &set_it) < 0)
		वापस false;
	अगर (set_it) अणु
		u32 gid;

		अगर (xdr_stream_decode_u32(xdr, &gid) < 0)
			वापस false;
		iap->ia_gid = make_kgid(nfsd_user_namespace(rqstp), gid);
		अगर (gid_valid(iap->ia_gid))
			iap->ia_valid |= ATTR_GID;
	पूर्ण
	अगर (xdr_stream_decode_bool(xdr, &set_it) < 0)
		वापस false;
	अगर (set_it) अणु
		u64 newsize;

		अगर (xdr_stream_decode_u64(xdr, &newsize) < 0)
			वापस false;
		iap->ia_valid |= ATTR_SIZE;
		iap->ia_size = min_t(u64, newsize, NFS_OFFSET_MAX);
	पूर्ण
	अगर (xdr_stream_decode_u32(xdr, &set_it) < 0)
		वापस false;
	चयन (set_it) अणु
	हाल DONT_CHANGE:
		अवरोध;
	हाल SET_TO_SERVER_TIME:
		iap->ia_valid |= ATTR_ATIME;
		अवरोध;
	हाल SET_TO_CLIENT_TIME:
		अगर (!svcxdr_decode_nfsसमय3(xdr, &iap->ia_aसमय))
			वापस false;
		iap->ia_valid |= ATTR_ATIME | ATTR_ATIME_SET;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	अगर (xdr_stream_decode_u32(xdr, &set_it) < 0)
		वापस false;
	चयन (set_it) अणु
	हाल DONT_CHANGE:
		अवरोध;
	हाल SET_TO_SERVER_TIME:
		iap->ia_valid |= ATTR_MTIME;
		अवरोध;
	हाल SET_TO_CLIENT_TIME:
		अगर (!svcxdr_decode_nfsसमय3(xdr, &iap->ia_mसमय))
			वापस false;
		iap->ia_valid |= ATTR_MTIME | ATTR_MTIME_SET;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
svcxdr_decode_sattrguard3(काष्ठा xdr_stream *xdr, काष्ठा nfsd3_sattrargs *args)
अणु
	__be32 *p;
	u32 check;

	अगर (xdr_stream_decode_bool(xdr, &check) < 0)
		वापस false;
	अगर (check) अणु
		p = xdr_अंतरभूत_decode(xdr, XDR_UNIT * 2);
		अगर (!p)
			वापस false;
		args->check_guard = 1;
		args->guardसमय = be32_to_cpup(p);
	पूर्ण अन्यथा
		args->check_guard = 0;

	वापस true;
पूर्ण

अटल bool
svcxdr_decode_specdata3(काष्ठा xdr_stream *xdr, काष्ठा nfsd3_mknodargs *args)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, XDR_UNIT * 2);
	अगर (!p)
		वापस false;
	args->major = be32_to_cpup(p++);
	args->minor = be32_to_cpup(p);

	वापस true;
पूर्ण

अटल bool
svcxdr_decode_devicedata3(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			  काष्ठा nfsd3_mknodargs *args)
अणु
	वापस svcxdr_decode_sattr3(rqstp, xdr, &args->attrs) &&
		svcxdr_decode_specdata3(xdr, args);
पूर्ण

अटल bool
svcxdr_encode_fattr3(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		     स्थिर काष्ठा svc_fh *fhp, स्थिर काष्ठा kstat *stat)
अणु
	काष्ठा user_namespace *userns = nfsd_user_namespace(rqstp);
	__be32 *p;
	u64 fsid;

	p = xdr_reserve_space(xdr, XDR_UNIT * 21);
	अगर (!p)
		वापस false;

	*p++ = cpu_to_be32(nfs3_ftypes[(stat->mode & S_IFMT) >> 12]);
	*p++ = cpu_to_be32((u32)(stat->mode & S_IALLUGO));
	*p++ = cpu_to_be32((u32)stat->nlink);
	*p++ = cpu_to_be32((u32)from_kuid_munged(userns, stat->uid));
	*p++ = cpu_to_be32((u32)from_kgid_munged(userns, stat->gid));
	अगर (S_ISLNK(stat->mode) && stat->size > NFS3_MAXPATHLEN)
		p = xdr_encode_hyper(p, (u64)NFS3_MAXPATHLEN);
	अन्यथा
		p = xdr_encode_hyper(p, (u64)stat->size);

	/* used */
	p = xdr_encode_hyper(p, ((u64)stat->blocks) << 9);

	/* rdev */
	*p++ = cpu_to_be32((u32)MAJOR(stat->rdev));
	*p++ = cpu_to_be32((u32)MINOR(stat->rdev));

	चयन(fsid_source(fhp)) अणु
	हाल FSIDSOURCE_FSID:
		fsid = (u64)fhp->fh_export->ex_fsid;
		अवरोध;
	हाल FSIDSOURCE_UUID:
		fsid = ((u64 *)fhp->fh_export->ex_uuid)[0];
		fsid ^= ((u64 *)fhp->fh_export->ex_uuid)[1];
		अवरोध;
	शेष:
		fsid = (u64)huge_encode_dev(fhp->fh_dentry->d_sb->s_dev);
	पूर्ण
	p = xdr_encode_hyper(p, fsid);

	/* fileid */
	p = xdr_encode_hyper(p, stat->ino);

	p = encode_nfsसमय3(p, &stat->aसमय);
	p = encode_nfsसमय3(p, &stat->mसमय);
	encode_nfsसमय3(p, &stat->स_समय);

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_wcc_attr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा svc_fh *fhp)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, XDR_UNIT * 6);
	अगर (!p)
		वापस false;
	p = xdr_encode_hyper(p, (u64)fhp->fh_pre_size);
	p = encode_nfsसमय3(p, &fhp->fh_pre_mसमय);
	encode_nfsसमय3(p, &fhp->fh_pre_स_समय);

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_pre_op_attr(काष्ठा xdr_stream *xdr, स्थिर काष्ठा svc_fh *fhp)
अणु
	अगर (!fhp->fh_pre_saved) अणु
		अगर (xdr_stream_encode_item_असलent(xdr) < 0)
			वापस false;
		वापस true;
	पूर्ण

	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस false;
	वापस svcxdr_encode_wcc_attr(xdr, fhp);
पूर्ण

/**
 * svcxdr_encode_post_op_attr - Encode NFSv3 post-op attributes
 * @rqstp: Context of a completed RPC transaction
 * @xdr: XDR stream
 * @fhp: File handle to encode
 *
 * Return values:
 *   %false: Send buffer space was exhausted
 *   %true: Success
 */
bool
svcxdr_encode_post_op_attr(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
			   स्थिर काष्ठा svc_fh *fhp)
अणु
	काष्ठा dentry *dentry = fhp->fh_dentry;
	काष्ठा kstat stat;

	/*
	 * The inode may be शून्य अगर the call failed because of a
	 * stale file handle. In this हाल, no attributes are
	 * वापसed.
	 */
	अगर (fhp->fh_no_wcc || !dentry || !d_really_is_positive(dentry))
		जाओ no_post_op_attrs;
	अगर (fh_getattr(fhp, &stat) != nfs_ok)
		जाओ no_post_op_attrs;

	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस false;
	lease_get_mसमय(d_inode(dentry), &stat.mसमय);
	अगर (!svcxdr_encode_fattr3(rqstp, xdr, fhp, &stat))
		वापस false;

	वापस true;

no_post_op_attrs:
	वापस xdr_stream_encode_item_असलent(xdr) > 0;
पूर्ण

/*
 * Encode weak cache consistency data
 */
अटल bool
svcxdr_encode_wcc_data(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		       स्थिर काष्ठा svc_fh *fhp)
अणु
	काष्ठा dentry *dentry = fhp->fh_dentry;

	अगर (!dentry || !d_really_is_positive(dentry) || !fhp->fh_post_saved)
		जाओ neither;

	/* beक्रमe */
	अगर (!svcxdr_encode_pre_op_attr(xdr, fhp))
		वापस false;

	/* after */
	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस false;
	अगर (!svcxdr_encode_fattr3(rqstp, xdr, fhp, &fhp->fh_post_attr))
		वापस false;

	वापस true;

neither:
	अगर (xdr_stream_encode_item_असलent(xdr) < 0)
		वापस false;
	अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, fhp))
		वापस false;

	वापस true;
पूर्ण

अटल bool fs_supports_change_attribute(काष्ठा super_block *sb)
अणु
	वापस sb->s_flags & SB_I_VERSION || sb->s_export_op->fetch_iversion;
पूर्ण

/*
 * Fill in the pre_op attr क्रम the wcc data
 */
व्योम fill_pre_wcc(काष्ठा svc_fh *fhp)
अणु
	काष्ठा inode    *inode;
	काष्ठा kstat	stat;
	bool v4 = (fhp->fh_maxsize == NFS4_FHSIZE);

	अगर (fhp->fh_no_wcc || fhp->fh_pre_saved)
		वापस;
	inode = d_inode(fhp->fh_dentry);
	अगर (fs_supports_change_attribute(inode->i_sb) || !v4) अणु
		__be32 err = fh_getattr(fhp, &stat);

		अगर (err) अणु
			/* Grab the बार from inode anyway */
			stat.mसमय = inode->i_mसमय;
			stat.स_समय = inode->i_स_समय;
			stat.size  = inode->i_size;
		पूर्ण
		fhp->fh_pre_mसमय = stat.mसमय;
		fhp->fh_pre_स_समय = stat.स_समय;
		fhp->fh_pre_size  = stat.size;
	पूर्ण
	अगर (v4)
		fhp->fh_pre_change = nfsd4_change_attribute(&stat, inode);

	fhp->fh_pre_saved = true;
पूर्ण

/*
 * Fill in the post_op attr क्रम the wcc data
 */
व्योम fill_post_wcc(काष्ठा svc_fh *fhp)
अणु
	bool v4 = (fhp->fh_maxsize == NFS4_FHSIZE);
	काष्ठा inode *inode = d_inode(fhp->fh_dentry);

	अगर (fhp->fh_no_wcc)
		वापस;

	अगर (fhp->fh_post_saved)
		prपूर्णांकk("nfsd: inode locked twice during operation.\n");

	fhp->fh_post_saved = true;

	अगर (fs_supports_change_attribute(inode->i_sb) || !v4) अणु
		__be32 err = fh_getattr(fhp, &fhp->fh_post_attr);

		अगर (err) अणु
			fhp->fh_post_saved = false;
			fhp->fh_post_attr.स_समय = inode->i_स_समय;
		पूर्ण
	पूर्ण
	अगर (v4)
		fhp->fh_post_change =
			nfsd4_change_attribute(&fhp->fh_post_attr, inode);
पूर्ण

/*
 * XDR decode functions
 */

पूर्णांक
nfs3svc_decode_fhandleargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_fhandle *args = rqstp->rq_argp;

	वापस svcxdr_decode_nfs_fh3(xdr, &args->fh);
पूर्ण

पूर्णांक
nfs3svc_decode_sattrargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_sattrargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_nfs_fh3(xdr, &args->fh) &&
		svcxdr_decode_sattr3(rqstp, xdr, &args->attrs) &&
		svcxdr_decode_sattrguard3(xdr, args);
पूर्ण

पूर्णांक
nfs3svc_decode_diropargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_diropargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_diropargs3(xdr, &args->fh, &args->name, &args->len);
पूर्ण

पूर्णांक
nfs3svc_decode_accessargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_accessargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->access) < 0)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_पढ़ोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_पढ़ोargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u64(xdr, &args->offset) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_ग_लिखोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_ग_लिखोargs *args = rqstp->rq_argp;
	u32 max_blocksize = svc_max_payload(rqstp);
	काष्ठा kvec *head = rqstp->rq_arg.head;
	काष्ठा kvec *tail = rqstp->rq_arg.tail;
	माप_प्रकार reमुख्यing;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u64(xdr, &args->offset) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->stable) < 0)
		वापस 0;

	/* opaque data */
	अगर (xdr_stream_decode_u32(xdr, &args->len) < 0)
		वापस 0;

	/* request sanity */
	अगर (args->count != args->len)
		वापस 0;
	reमुख्यing = head->iov_len + rqstp->rq_arg.page_len + tail->iov_len;
	reमुख्यing -= xdr_stream_pos(xdr);
	अगर (reमुख्यing < xdr_align_size(args->len))
		वापस 0;
	अगर (args->count > max_blocksize) अणु
		args->count = max_blocksize;
		args->len = max_blocksize;
	पूर्ण

	args->first.iov_base = xdr->p;
	args->first.iov_len = head->iov_len - xdr_stream_pos(xdr);

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_createargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_createargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_diropargs3(xdr, &args->fh, &args->name, &args->len))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->createmode) < 0)
		वापस 0;
	चयन (args->createmode) अणु
	हाल NFS3_CREATE_UNCHECKED:
	हाल NFS3_CREATE_GUARDED:
		वापस svcxdr_decode_sattr3(rqstp, xdr, &args->attrs);
	हाल NFS3_CREATE_EXCLUSIVE:
		args->verf = xdr_अंतरभूत_decode(xdr, NFS3_CREATEVERFSIZE);
		अगर (!args->verf)
			वापस 0;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_सूची_गढ़ोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_createargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_diropargs3(xdr, &args->fh,
					&args->name, &args->len) &&
		svcxdr_decode_sattr3(rqstp, xdr, &args->attrs);
पूर्ण

पूर्णांक
nfs3svc_decode_symlinkargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_symlinkargs *args = rqstp->rq_argp;
	काष्ठा kvec *head = rqstp->rq_arg.head;
	काष्ठा kvec *tail = rqstp->rq_arg.tail;
	माप_प्रकार reमुख्यing;

	अगर (!svcxdr_decode_diropargs3(xdr, &args->ffh, &args->fname, &args->flen))
		वापस 0;
	अगर (!svcxdr_decode_sattr3(rqstp, xdr, &args->attrs))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->tlen) < 0)
		वापस 0;

	/* request sanity */
	reमुख्यing = head->iov_len + rqstp->rq_arg.page_len + tail->iov_len;
	reमुख्यing -= xdr_stream_pos(xdr);
	अगर (reमुख्यing < xdr_align_size(args->tlen))
		वापस 0;

	args->first.iov_base = xdr->p;
	args->first.iov_len = head->iov_len - xdr_stream_pos(xdr);

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_mknodargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_mknodargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_diropargs3(xdr, &args->fh, &args->name, &args->len))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->ftype) < 0)
		वापस 0;
	चयन (args->ftype) अणु
	हाल NF3CHR:
	हाल NF3BLK:
		वापस svcxdr_decode_devicedata3(rqstp, xdr, args);
	हाल NF3SOCK:
	हाल NF3FIFO:
		वापस svcxdr_decode_sattr3(rqstp, xdr, &args->attrs);
	हाल NF3REG:
	हाल NF3सूची:
	हाल NF3LNK:
		/* Valid XDR but illegal file types */
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_नामargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_नामargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_diropargs3(xdr, &args->ffh,
					&args->fname, &args->flen) &&
		svcxdr_decode_diropargs3(xdr, &args->tfh,
					 &args->tname, &args->tlen);
पूर्ण

पूर्णांक
nfs3svc_decode_linkargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_linkargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_nfs_fh3(xdr, &args->ffh) &&
		svcxdr_decode_diropargs3(xdr, &args->tfh,
					 &args->tname, &args->tlen);
पूर्ण

पूर्णांक
nfs3svc_decode_सूची_पढ़ोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_सूची_पढ़ोargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u64(xdr, &args->cookie) < 0)
		वापस 0;
	args->verf = xdr_अंतरभूत_decode(xdr, NFS3_COOKIEVERFSIZE);
	अगर (!args->verf)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_सूची_पढ़ोplusargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_सूची_पढ़ोargs *args = rqstp->rq_argp;
	u32 dircount;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u64(xdr, &args->cookie) < 0)
		वापस 0;
	args->verf = xdr_अंतरभूत_decode(xdr, NFS3_COOKIEVERFSIZE);
	अगर (!args->verf)
		वापस 0;
	/* dircount is ignored */
	अगर (xdr_stream_decode_u32(xdr, &dircount) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक
nfs3svc_decode_commitargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd3_commitargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_nfs_fh3(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u64(xdr, &args->offset) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;

	वापस 1;
पूर्ण

/*
 * XDR encode functions
 */

/* GETATTR */
पूर्णांक
nfs3svc_encode_getattrres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		lease_get_mसमय(d_inode(resp->fh.fh_dentry), &resp->stat.mसमय);
		अगर (!svcxdr_encode_fattr3(rqstp, xdr, &resp->fh, &resp->stat))
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

/* SETATTR, REMOVE, RMसूची */
पूर्णांक
nfs3svc_encode_wccstat(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	वापस svcxdr_encode_nfsstat3(xdr, resp->status) &&
		svcxdr_encode_wcc_data(rqstp, xdr, &resp->fh);
पूर्ण

/* LOOKUP */
पूर्णांक nfs3svc_encode_lookupres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_diropres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_nfs_fh3(xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->dirfh))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->dirfh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* ACCESS */
पूर्णांक
nfs3svc_encode_accessres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_accessres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->access) < 0)
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* READLINK */
पूर्णांक
nfs3svc_encode_पढ़ोlinkres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_पढ़ोlinkres *resp = rqstp->rq_resp;
	काष्ठा kvec *head = rqstp->rq_res.head;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->len) < 0)
			वापस 0;
		xdr_ग_लिखो_pages(xdr, resp->pages, 0, resp->len);
		अगर (svc_encode_result_payload(rqstp, head->iov_len, resp->len) < 0)
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* READ */
पूर्णांक
nfs3svc_encode_पढ़ोres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_पढ़ोres *resp = rqstp->rq_resp;
	काष्ठा kvec *head = rqstp->rq_res.head;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->count) < 0)
			वापस 0;
		अगर (xdr_stream_encode_bool(xdr, resp->eof) < 0)
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->count) < 0)
			वापस 0;
		xdr_ग_लिखो_pages(xdr, resp->pages, rqstp->rq_res.page_base,
				resp->count);
		अगर (svc_encode_result_payload(rqstp, head->iov_len, resp->count) < 0)
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* WRITE */
पूर्णांक
nfs3svc_encode_ग_लिखोres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_ग_लिखोres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_wcc_data(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->count) < 0)
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->committed) < 0)
			वापस 0;
		अगर (!svcxdr_encode_ग_लिखोverf3(xdr, resp->verf))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_wcc_data(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* CREATE, MKसूची, SYMLINK, MKNOD */
पूर्णांक
nfs3svc_encode_createres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_diropres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_fh3(xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_wcc_data(rqstp, xdr, &resp->dirfh))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_wcc_data(rqstp, xdr, &resp->dirfh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* RENAME */
पूर्णांक
nfs3svc_encode_नामres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_नामres *resp = rqstp->rq_resp;

	वापस svcxdr_encode_nfsstat3(xdr, resp->status) &&
		svcxdr_encode_wcc_data(rqstp, xdr, &resp->ffh) &&
		svcxdr_encode_wcc_data(rqstp, xdr, &resp->tfh);
पूर्ण

/* LINK */
पूर्णांक
nfs3svc_encode_linkres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_linkres *resp = rqstp->rq_resp;

	वापस svcxdr_encode_nfsstat3(xdr, resp->status) &&
		svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh) &&
		svcxdr_encode_wcc_data(rqstp, xdr, &resp->tfh);
पूर्ण

/* READसूची */
पूर्णांक
nfs3svc_encode_सूची_पढ़ोres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_सूची_पढ़ोres *resp = rqstp->rq_resp;
	काष्ठा xdr_buf *dirlist = &resp->dirlist;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_cookieverf3(xdr, resp->verf))
			वापस 0;
		xdr_ग_लिखो_pages(xdr, dirlist->pages, 0, dirlist->len);
		/* no more entries */
		अगर (xdr_stream_encode_item_असलent(xdr) < 0)
			वापस 0;
		अगर (xdr_stream_encode_bool(xdr, resp->common.err == nfserr_eof) < 0)
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल __be32
compose_entry_fh(काष्ठा nfsd3_सूची_पढ़ोres *cd, काष्ठा svc_fh *fhp,
		 स्थिर अक्षर *name, पूर्णांक namlen, u64 ino)
अणु
	काष्ठा svc_export	*exp;
	काष्ठा dentry		*dparent, *dchild;
	__be32 rv = nfserr_noent;

	dparent = cd->fh.fh_dentry;
	exp  = cd->fh.fh_export;

	अगर (isकरोtent(name, namlen)) अणु
		अगर (namlen == 2) अणु
			dchild = dget_parent(dparent);
			/*
			 * Don't return filehandle for ".." if we're at
			 * the fileप्रणाली or export root:
			 */
			अगर (dchild == dparent)
				जाओ out;
			अगर (dparent == exp->ex_path.dentry)
				जाओ out;
		पूर्ण अन्यथा
			dchild = dget(dparent);
	पूर्ण अन्यथा
		dchild = lookup_positive_unlocked(name, dparent, namlen);
	अगर (IS_ERR(dchild))
		वापस rv;
	अगर (d_mountpoपूर्णांक(dchild))
		जाओ out;
	अगर (dchild->d_inode->i_ino != ino)
		जाओ out;
	rv = fh_compose(fhp, exp, dchild, &cd->fh);
out:
	dput(dchild);
	वापस rv;
पूर्ण

/**
 * nfs3svc_encode_cookie3 - Encode a directory offset cookie
 * @resp: सूची_पढ़ो result context
 * @offset: offset cookie to encode
 *
 * The buffer space क्रम the offset cookie has alपढ़ोy been reserved
 * by svcxdr_encode_entry3_common().
 */
व्योम nfs3svc_encode_cookie3(काष्ठा nfsd3_सूची_पढ़ोres *resp, u64 offset)
अणु
	__be64 cookie = cpu_to_be64(offset);

	अगर (!resp->cookie_offset)
		वापस;
	ग_लिखो_bytes_to_xdr_buf(&resp->dirlist, resp->cookie_offset, &cookie,
			       माप(cookie));
	resp->cookie_offset = 0;
पूर्ण

अटल bool
svcxdr_encode_entry3_common(काष्ठा nfsd3_सूची_पढ़ोres *resp, स्थिर अक्षर *name,
			    पूर्णांक namlen, loff_t offset, u64 ino)
अणु
	काष्ठा xdr_buf *dirlist = &resp->dirlist;
	काष्ठा xdr_stream *xdr = &resp->xdr;

	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस false;
	/* fileid */
	अगर (xdr_stream_encode_u64(xdr, ino) < 0)
		वापस false;
	/* name */
	अगर (xdr_stream_encode_opaque(xdr, name, min(namlen, NFS3_MAXNAMLEN)) < 0)
		वापस false;
	/* cookie */
	resp->cookie_offset = dirlist->len;
	अगर (xdr_stream_encode_u64(xdr, NFS_OFFSET_MAX) < 0)
		वापस false;

	वापस true;
पूर्ण

/**
 * nfs3svc_encode_entry3 - encode one NFSv3 READसूची entry
 * @data: directory context
 * @name: name of the object to be encoded
 * @namlen: length of that name, in bytes
 * @offset: the offset of the previous entry
 * @ino: the fileid of this entry
 * @d_type: unused
 *
 * Return values:
 *   %0: Entry was successfully encoded.
 *   %-EINVAL: An encoding problem occured, secondary status code in resp->common.err
 *
 * On निकास, the following fields are updated:
 *   - resp->xdr
 *   - resp->common.err
 *   - resp->cookie_offset
 */
पूर्णांक nfs3svc_encode_entry3(व्योम *data, स्थिर अक्षर *name, पूर्णांक namlen,
			  loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा सूची_पढ़ो_cd *ccd = data;
	काष्ठा nfsd3_सूची_पढ़ोres *resp = container_of(ccd,
						     काष्ठा nfsd3_सूची_पढ़ोres,
						     common);
	अचिन्हित पूर्णांक starting_length = resp->dirlist.len;

	/* The offset cookie क्रम the previous entry */
	nfs3svc_encode_cookie3(resp, offset);

	अगर (!svcxdr_encode_entry3_common(resp, name, namlen, offset, ino))
		जाओ out_toosmall;

	xdr_commit_encode(&resp->xdr);
	resp->common.err = nfs_ok;
	वापस 0;

out_toosmall:
	resp->cookie_offset = 0;
	resp->common.err = nfserr_toosmall;
	resp->dirlist.len = starting_length;
	वापस -EINVAL;
पूर्ण

अटल bool
svcxdr_encode_entry3_plus(काष्ठा nfsd3_सूची_पढ़ोres *resp, स्थिर अक्षर *name,
			  पूर्णांक namlen, u64 ino)
अणु
	काष्ठा xdr_stream *xdr = &resp->xdr;
	काष्ठा svc_fh *fhp = &resp->scratch;
	bool result;

	result = false;
	fh_init(fhp, NFS3_FHSIZE);
	अगर (compose_entry_fh(resp, fhp, name, namlen, ino) != nfs_ok)
		जाओ out_noattrs;

	अगर (!svcxdr_encode_post_op_attr(resp->rqstp, xdr, fhp))
		जाओ out;
	अगर (!svcxdr_encode_post_op_fh3(xdr, fhp))
		जाओ out;
	result = true;

out:
	fh_put(fhp);
	वापस result;

out_noattrs:
	अगर (xdr_stream_encode_item_असलent(xdr) < 0)
		वापस false;
	अगर (xdr_stream_encode_item_असलent(xdr) < 0)
		वापस false;
	वापस true;
पूर्ण

/**
 * nfs3svc_encode_entryplus3 - encode one NFSv3 READसूचीPLUS entry
 * @data: directory context
 * @name: name of the object to be encoded
 * @namlen: length of that name, in bytes
 * @offset: the offset of the previous entry
 * @ino: the fileid of this entry
 * @d_type: unused
 *
 * Return values:
 *   %0: Entry was successfully encoded.
 *   %-EINVAL: An encoding problem occured, secondary status code in resp->common.err
 *
 * On निकास, the following fields are updated:
 *   - resp->xdr
 *   - resp->common.err
 *   - resp->cookie_offset
 */
पूर्णांक nfs3svc_encode_entryplus3(व्योम *data, स्थिर अक्षर *name, पूर्णांक namlen,
			      loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा सूची_पढ़ो_cd *ccd = data;
	काष्ठा nfsd3_सूची_पढ़ोres *resp = container_of(ccd,
						     काष्ठा nfsd3_सूची_पढ़ोres,
						     common);
	अचिन्हित पूर्णांक starting_length = resp->dirlist.len;

	/* The offset cookie क्रम the previous entry */
	nfs3svc_encode_cookie3(resp, offset);

	अगर (!svcxdr_encode_entry3_common(resp, name, namlen, offset, ino))
		जाओ out_toosmall;
	अगर (!svcxdr_encode_entry3_plus(resp, name, namlen, ino))
		जाओ out_toosmall;

	xdr_commit_encode(&resp->xdr);
	resp->common.err = nfs_ok;
	वापस 0;

out_toosmall:
	resp->cookie_offset = 0;
	resp->common.err = nfserr_toosmall;
	resp->dirlist.len = starting_length;
	वापस -EINVAL;
पूर्ण

अटल bool
svcxdr_encode_fsstat3resok(काष्ठा xdr_stream *xdr,
			   स्थिर काष्ठा nfsd3_fsstatres *resp)
अणु
	स्थिर काष्ठा kstatfs *s = &resp->stats;
	u64 bs = s->f_bsize;
	__be32 *p;

	p = xdr_reserve_space(xdr, XDR_UNIT * 13);
	अगर (!p)
		वापस false;
	p = xdr_encode_hyper(p, bs * s->f_blocks);	/* total bytes */
	p = xdr_encode_hyper(p, bs * s->f_bमुक्त);	/* मुक्त bytes */
	p = xdr_encode_hyper(p, bs * s->f_bavail);	/* user available bytes */
	p = xdr_encode_hyper(p, s->f_files);		/* total inodes */
	p = xdr_encode_hyper(p, s->f_fमुक्त);		/* मुक्त inodes */
	p = xdr_encode_hyper(p, s->f_fमुक्त);		/* user available inodes */
	*p = cpu_to_be32(resp->invarsec);		/* mean unchanged समय */

	वापस true;
पूर्ण

/* FSSTAT */
पूर्णांक
nfs3svc_encode_fsstatres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_fsstatres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &nfs3svc_null_fh))
			वापस 0;
		अगर (!svcxdr_encode_fsstat3resok(xdr, resp))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &nfs3svc_null_fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल bool
svcxdr_encode_fsinfo3resok(काष्ठा xdr_stream *xdr,
			   स्थिर काष्ठा nfsd3_fsinक्रमes *resp)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, XDR_UNIT * 12);
	अगर (!p)
		वापस false;
	*p++ = cpu_to_be32(resp->f_rपंचांगax);
	*p++ = cpu_to_be32(resp->f_rtpref);
	*p++ = cpu_to_be32(resp->f_rपंचांगult);
	*p++ = cpu_to_be32(resp->f_wपंचांगax);
	*p++ = cpu_to_be32(resp->f_wtpref);
	*p++ = cpu_to_be32(resp->f_wपंचांगult);
	*p++ = cpu_to_be32(resp->f_dtpref);
	p = xdr_encode_hyper(p, resp->f_maxfilesize);
	p = encode_nfsसमय3(p, &nfs3svc_समय_delta);
	*p = cpu_to_be32(resp->f_properties);

	वापस true;
पूर्ण

/* FSINFO */
पूर्णांक
nfs3svc_encode_fsinक्रमes(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_fsinक्रमes *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &nfs3svc_null_fh))
			वापस 0;
		अगर (!svcxdr_encode_fsinfo3resok(xdr, resp))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &nfs3svc_null_fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल bool
svcxdr_encode_pathconf3resok(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfsd3_pathconfres *resp)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, XDR_UNIT * 6);
	अगर (!p)
		वापस false;
	*p++ = cpu_to_be32(resp->p_link_max);
	*p++ = cpu_to_be32(resp->p_name_max);
	p = xdr_encode_bool(p, resp->p_no_trunc);
	p = xdr_encode_bool(p, resp->p_chown_restricted);
	p = xdr_encode_bool(p, resp->p_हाल_insensitive);
	xdr_encode_bool(p, resp->p_हाल_preserving);

	वापस true;
पूर्ण

/* PATHCONF */
पूर्णांक
nfs3svc_encode_pathconfres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_pathconfres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &nfs3svc_null_fh))
			वापस 0;
		अगर (!svcxdr_encode_pathconf3resok(xdr, resp))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_post_op_attr(rqstp, xdr, &nfs3svc_null_fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* COMMIT */
पूर्णांक
nfs3svc_encode_commitres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd3_commitres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_nfsstat3(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_wcc_data(rqstp, xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_ग_लिखोverf3(xdr, resp->verf))
			वापस 0;
		अवरोध;
	शेष:
		अगर (!svcxdr_encode_wcc_data(rqstp, xdr, &resp->fh))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * XDR release functions
 */
व्योम
nfs3svc_release_fhandle(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
पूर्ण

व्योम
nfs3svc_release_fhandle2(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_fhandle_pair *resp = rqstp->rq_resp;

	fh_put(&resp->fh1);
	fh_put(&resp->fh2);
पूर्ण
