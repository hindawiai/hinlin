<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * XDR support क्रम nfsd
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश "vfs.h"
#समावेश "xdr.h"
#समावेश "auth.h"

/*
 * Mapping of S_IF* types to NFS file types
 */
अटल स्थिर u32 nfs_ftypes[] = अणु
	NFNON,  NFCHR,  NFCHR, NFBAD,
	NFसूची,  NFBAD,  NFBLK, NFBAD,
	NFREG,  NFBAD,  NFLNK, NFBAD,
	NFSOCK, NFBAD,  NFLNK, NFBAD,
पूर्ण;


/*
 * Basic NFSv2 data types (RFC 1094 Section 2.3)
 */

/**
 * svcxdr_encode_stat - Encode an NFSv2 status code
 * @xdr: XDR stream
 * @status: status value to encode
 *
 * Return values:
 *   %false: Send buffer space was exhausted
 *   %true: Success
 */
bool
svcxdr_encode_stat(काष्ठा xdr_stream *xdr, __be32 status)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, माप(status));
	अगर (!p)
		वापस false;
	*p = status;

	वापस true;
पूर्ण

/**
 * svcxdr_decode_fhandle - Decode an NFSv2 file handle
 * @xdr: XDR stream positioned at an encoded NFSv2 FH
 * @fhp: OUT: filled-in server file handle
 *
 * Return values:
 *  %false: The encoded file handle was not valid
 *  %true: @fhp has been initialized
 */
bool
svcxdr_decode_fhandle(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS_FHSIZE);
	अगर (!p)
		वापस false;
	fh_init(fhp, NFS_FHSIZE);
	स_नकल(&fhp->fh_handle.fh_base, p, NFS_FHSIZE);
	fhp->fh_handle.fh_size = NFS_FHSIZE;

	वापस true;
पूर्ण

अटल bool
svcxdr_encode_fhandle(काष्ठा xdr_stream *xdr, स्थिर काष्ठा svc_fh *fhp)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS_FHSIZE);
	अगर (!p)
		वापस false;
	स_नकल(p, &fhp->fh_handle.fh_base, NFS_FHSIZE);

	वापस true;
पूर्ण

अटल __be32 *
encode_समयval(__be32 *p, स्थिर काष्ठा बारpec64 *समय)
अणु
	*p++ = cpu_to_be32((u32)समय->tv_sec);
	अगर (समय->tv_nsec)
		*p++ = cpu_to_be32(समय->tv_nsec / NSEC_PER_USEC);
	अन्यथा
		*p++ = xdr_zero;
	वापस p;
पूर्ण

अटल bool
svcxdr_decode_filename(काष्ठा xdr_stream *xdr, अक्षर **name, अचिन्हित पूर्णांक *len)
अणु
	u32 size, i;
	__be32 *p;
	अक्षर *c;

	अगर (xdr_stream_decode_u32(xdr, &size) < 0)
		वापस false;
	अगर (size == 0 || size > NFS_MAXNAMLEN)
		वापस false;
	p = xdr_अंतरभूत_decode(xdr, size);
	अगर (!p)
		वापस false;

	*len = size;
	*name = (अक्षर *)p;
	क्रम (i = 0, c = *name; i < size; i++, c++)
		अगर (*c == '\0' || *c == '/')
			वापस false;

	वापस true;
पूर्ण

अटल bool
svcxdr_decode_diropargs(काष्ठा xdr_stream *xdr, काष्ठा svc_fh *fhp,
			अक्षर **name, अचिन्हित पूर्णांक *len)
अणु
	वापस svcxdr_decode_fhandle(xdr, fhp) &&
		svcxdr_decode_filename(xdr, name, len);
पूर्ण

अटल bool
svcxdr_decode_sattr(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		    काष्ठा iattr *iap)
अणु
	u32 पंचांगp1, पंचांगp2;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, XDR_UNIT * 8);
	अगर (!p)
		वापस false;

	iap->ia_valid = 0;

	/*
	 * Some Sun clients put 0xffff in the mode field when they
	 * mean 0xffffffff.
	 */
	पंचांगp1 = be32_to_cpup(p++);
	अगर (पंचांगp1 != (u32)-1 && पंचांगp1 != 0xffff) अणु
		iap->ia_valid |= ATTR_MODE;
		iap->ia_mode = पंचांगp1;
	पूर्ण

	पंचांगp1 = be32_to_cpup(p++);
	अगर (पंचांगp1 != (u32)-1) अणु
		iap->ia_uid = make_kuid(nfsd_user_namespace(rqstp), पंचांगp1);
		अगर (uid_valid(iap->ia_uid))
			iap->ia_valid |= ATTR_UID;
	पूर्ण

	पंचांगp1 = be32_to_cpup(p++);
	अगर (पंचांगp1 != (u32)-1) अणु
		iap->ia_gid = make_kgid(nfsd_user_namespace(rqstp), पंचांगp1);
		अगर (gid_valid(iap->ia_gid))
			iap->ia_valid |= ATTR_GID;
	पूर्ण

	पंचांगp1 = be32_to_cpup(p++);
	अगर (पंचांगp1 != (u32)-1) अणु
		iap->ia_valid |= ATTR_SIZE;
		iap->ia_size = पंचांगp1;
	पूर्ण

	पंचांगp1 = be32_to_cpup(p++);
	पंचांगp2 = be32_to_cpup(p++);
	अगर (पंचांगp1 != (u32)-1 && पंचांगp2 != (u32)-1) अणु
		iap->ia_valid |= ATTR_ATIME | ATTR_ATIME_SET;
		iap->ia_aसमय.tv_sec = पंचांगp1;
		iap->ia_aसमय.tv_nsec = पंचांगp2 * NSEC_PER_USEC;
	पूर्ण

	पंचांगp1 = be32_to_cpup(p++);
	पंचांगp2 = be32_to_cpup(p++);
	अगर (पंचांगp1 != (u32)-1 && पंचांगp2 != (u32)-1) अणु
		iap->ia_valid |= ATTR_MTIME | ATTR_MTIME_SET;
		iap->ia_mसमय.tv_sec = पंचांगp1;
		iap->ia_mसमय.tv_nsec = पंचांगp2 * NSEC_PER_USEC;
		/*
		 * Passing the invalid value useconds=1000000 क्रम mसमय
		 * is a Sun convention क्रम "set both mसमय and aसमय to
		 * current server समय".  It's needed to make permissions
		 * checks क्रम the "touch" program across v2 mounts to
		 * Solaris and Irix boxes work correctly. See description of
		 * sattr in section 6.1 of "NFS Illustrated" by
		 * Brent Callaghan, Addison-Wesley, ISBN 0-201-32750-5
		 */
		अगर (पंचांगp2 == 1000000)
			iap->ia_valid &= ~(ATTR_ATIME_SET|ATTR_MTIME_SET);
	पूर्ण

	वापस true;
पूर्ण

/**
 * svcxdr_encode_fattr - Encode NFSv2 file attributes
 * @rqstp: Context of a completed RPC transaction
 * @xdr: XDR stream
 * @fhp: File handle to encode
 * @stat: Attributes to encode
 *
 * Return values:
 *   %false: Send buffer space was exhausted
 *   %true: Success
 */
bool
svcxdr_encode_fattr(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		    स्थिर काष्ठा svc_fh *fhp, स्थिर काष्ठा kstat *stat)
अणु
	काष्ठा user_namespace *userns = nfsd_user_namespace(rqstp);
	काष्ठा dentry *dentry = fhp->fh_dentry;
	पूर्णांक type = stat->mode & S_IFMT;
	काष्ठा बारpec64 समय;
	__be32 *p;
	u32 fsid;

	p = xdr_reserve_space(xdr, XDR_UNIT * 17);
	अगर (!p)
		वापस false;

	*p++ = cpu_to_be32(nfs_ftypes[type >> 12]);
	*p++ = cpu_to_be32((u32)stat->mode);
	*p++ = cpu_to_be32((u32)stat->nlink);
	*p++ = cpu_to_be32((u32)from_kuid_munged(userns, stat->uid));
	*p++ = cpu_to_be32((u32)from_kgid_munged(userns, stat->gid));

	अगर (S_ISLNK(type) && stat->size > NFS_MAXPATHLEN)
		*p++ = cpu_to_be32(NFS_MAXPATHLEN);
	अन्यथा
		*p++ = cpu_to_be32((u32) stat->size);
	*p++ = cpu_to_be32((u32) stat->blksize);
	अगर (S_ISCHR(type) || S_ISBLK(type))
		*p++ = cpu_to_be32(new_encode_dev(stat->rdev));
	अन्यथा
		*p++ = cpu_to_be32(0xffffffff);
	*p++ = cpu_to_be32((u32)stat->blocks);

	चयन (fsid_source(fhp)) अणु
	हाल FSIDSOURCE_FSID:
		fsid = (u32)fhp->fh_export->ex_fsid;
		अवरोध;
	हाल FSIDSOURCE_UUID:
		fsid = ((u32 *)fhp->fh_export->ex_uuid)[0];
		fsid ^= ((u32 *)fhp->fh_export->ex_uuid)[1];
		fsid ^= ((u32 *)fhp->fh_export->ex_uuid)[2];
		fsid ^= ((u32 *)fhp->fh_export->ex_uuid)[3];
		अवरोध;
	शेष:
		fsid = new_encode_dev(stat->dev);
		अवरोध;
	पूर्ण
	*p++ = cpu_to_be32(fsid);

	*p++ = cpu_to_be32((u32)stat->ino);
	p = encode_समयval(p, &stat->aसमय);
	समय = stat->mसमय;
	lease_get_mसमय(d_inode(dentry), &समय);
	p = encode_समयval(p, &समय);
	encode_समयval(p, &stat->स_समय);

	वापस true;
पूर्ण

/*
 * XDR decode functions
 */

पूर्णांक
nfssvc_decode_fhandleargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_fhandle *args = rqstp->rq_argp;

	वापस svcxdr_decode_fhandle(xdr, &args->fh);
पूर्ण

पूर्णांक
nfssvc_decode_sattrargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_sattrargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_fhandle(xdr, &args->fh) &&
		svcxdr_decode_sattr(rqstp, xdr, &args->attrs);
पूर्ण

पूर्णांक
nfssvc_decode_diropargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_diropargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_diropargs(xdr, &args->fh, &args->name, &args->len);
पूर्ण

पूर्णांक
nfssvc_decode_पढ़ोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_पढ़ोargs *args = rqstp->rq_argp;
	u32 totalcount;

	अगर (!svcxdr_decode_fhandle(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->offset) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;
	/* totalcount is ignored */
	अगर (xdr_stream_decode_u32(xdr, &totalcount) < 0)
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_decode_ग_लिखोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_ग_लिखोargs *args = rqstp->rq_argp;
	काष्ठा kvec *head = rqstp->rq_arg.head;
	काष्ठा kvec *tail = rqstp->rq_arg.tail;
	u32 beginoffset, totalcount;
	माप_प्रकार reमुख्यing;

	अगर (!svcxdr_decode_fhandle(xdr, &args->fh))
		वापस 0;
	/* beginoffset is ignored */
	अगर (xdr_stream_decode_u32(xdr, &beginoffset) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->offset) < 0)
		वापस 0;
	/* totalcount is ignored */
	अगर (xdr_stream_decode_u32(xdr, &totalcount) < 0)
		वापस 0;

	/* opaque data */
	अगर (xdr_stream_decode_u32(xdr, &args->len) < 0)
		वापस 0;
	अगर (args->len > NFSSVC_MAXBLKSIZE_V2)
		वापस 0;
	reमुख्यing = head->iov_len + rqstp->rq_arg.page_len + tail->iov_len;
	reमुख्यing -= xdr_stream_pos(xdr);
	अगर (reमुख्यing < xdr_align_size(args->len))
		वापस 0;
	args->first.iov_base = xdr->p;
	args->first.iov_len = head->iov_len - xdr_stream_pos(xdr);

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_decode_createargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_createargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_diropargs(xdr, &args->fh,
				       &args->name, &args->len) &&
		svcxdr_decode_sattr(rqstp, xdr, &args->attrs);
पूर्ण

पूर्णांक
nfssvc_decode_नामargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_नामargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_diropargs(xdr, &args->ffh,
				       &args->fname, &args->flen) &&
		svcxdr_decode_diropargs(xdr, &args->tfh,
					&args->tname, &args->tlen);
पूर्ण

पूर्णांक
nfssvc_decode_linkargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_linkargs *args = rqstp->rq_argp;

	वापस svcxdr_decode_fhandle(xdr, &args->ffh) &&
		svcxdr_decode_diropargs(xdr, &args->tfh,
					&args->tname, &args->tlen);
पूर्ण

पूर्णांक
nfssvc_decode_symlinkargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_symlinkargs *args = rqstp->rq_argp;
	काष्ठा kvec *head = rqstp->rq_arg.head;

	अगर (!svcxdr_decode_diropargs(xdr, &args->ffh, &args->fname, &args->flen))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->tlen) < 0)
		वापस 0;
	अगर (args->tlen == 0)
		वापस 0;

	args->first.iov_len = head->iov_len - xdr_stream_pos(xdr);
	args->first.iov_base = xdr_अंतरभूत_decode(xdr, args->tlen);
	अगर (!args->first.iov_base)
		वापस 0;
	वापस svcxdr_decode_sattr(rqstp, xdr, &args->attrs);
पूर्ण

पूर्णांक
nfssvc_decode_सूची_पढ़ोargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_arg_stream;
	काष्ठा nfsd_सूची_पढ़ोargs *args = rqstp->rq_argp;

	अगर (!svcxdr_decode_fhandle(xdr, &args->fh))
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->cookie) < 0)
		वापस 0;
	अगर (xdr_stream_decode_u32(xdr, &args->count) < 0)
		वापस 0;

	वापस 1;
पूर्ण

/*
 * XDR encode functions
 */

पूर्णांक
nfssvc_encode_statres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_stat *resp = rqstp->rq_resp;

	वापस svcxdr_encode_stat(xdr, resp->status);
पूर्ण

पूर्णांक
nfssvc_encode_attrstatres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_fattr(rqstp, xdr, &resp->fh, &resp->stat))
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_encode_diropres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_diropres *resp = rqstp->rq_resp;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_fhandle(xdr, &resp->fh))
			वापस 0;
		अगर (!svcxdr_encode_fattr(rqstp, xdr, &resp->fh, &resp->stat))
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_encode_पढ़ोlinkres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_पढ़ोlinkres *resp = rqstp->rq_resp;
	काष्ठा kvec *head = rqstp->rq_res.head;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (xdr_stream_encode_u32(xdr, resp->len) < 0)
			वापस 0;
		xdr_ग_लिखो_pages(xdr, &resp->page, 0, resp->len);
		अगर (svc_encode_result_payload(rqstp, head->iov_len, resp->len) < 0)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_encode_पढ़ोres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_पढ़ोres *resp = rqstp->rq_resp;
	काष्ठा kvec *head = rqstp->rq_res.head;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		अगर (!svcxdr_encode_fattr(rqstp, xdr, &resp->fh, &resp->stat))
			वापस 0;
		अगर (xdr_stream_encode_u32(xdr, resp->count) < 0)
			वापस 0;
		xdr_ग_लिखो_pages(xdr, resp->pages, rqstp->rq_res.page_base,
				resp->count);
		अगर (svc_encode_result_payload(rqstp, head->iov_len, resp->count) < 0)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_encode_सूची_पढ़ोres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_सूची_पढ़ोres *resp = rqstp->rq_resp;
	काष्ठा xdr_buf *dirlist = &resp->dirlist;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		xdr_ग_लिखो_pages(xdr, dirlist->pages, 0, dirlist->len);
		/* no more entries */
		अगर (xdr_stream_encode_item_असलent(xdr) < 0)
			वापस 0;
		अगर (xdr_stream_encode_bool(xdr, resp->common.err == nfserr_eof) < 0)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक
nfssvc_encode_statfsres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा xdr_stream *xdr = &rqstp->rq_res_stream;
	काष्ठा nfsd_statfsres *resp = rqstp->rq_resp;
	काष्ठा kstatfs	*stat = &resp->stats;

	अगर (!svcxdr_encode_stat(xdr, resp->status))
		वापस 0;
	चयन (resp->status) अणु
	हाल nfs_ok:
		p = xdr_reserve_space(xdr, XDR_UNIT * 5);
		अगर (!p)
			वापस 0;
		*p++ = cpu_to_be32(NFSSVC_MAXBLKSIZE_V2);
		*p++ = cpu_to_be32(stat->f_bsize);
		*p++ = cpu_to_be32(stat->f_blocks);
		*p++ = cpu_to_be32(stat->f_bमुक्त);
		*p = cpu_to_be32(stat->f_bavail);
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * nfssvc_encode_nfscookie - Encode a directory offset cookie
 * @resp: सूची_पढ़ो result context
 * @offset: offset cookie to encode
 *
 * The buffer space क्रम the offset cookie has alपढ़ोy been reserved
 * by svcxdr_encode_entry_common().
 */
व्योम nfssvc_encode_nfscookie(काष्ठा nfsd_सूची_पढ़ोres *resp, u32 offset)
अणु
	__be32 cookie = cpu_to_be32(offset);

	अगर (!resp->cookie_offset)
		वापस;

	ग_लिखो_bytes_to_xdr_buf(&resp->dirlist, resp->cookie_offset, &cookie,
			       माप(cookie));
	resp->cookie_offset = 0;
पूर्ण

अटल bool
svcxdr_encode_entry_common(काष्ठा nfsd_सूची_पढ़ोres *resp, स्थिर अक्षर *name,
			   पूर्णांक namlen, loff_t offset, u64 ino)
अणु
	काष्ठा xdr_buf *dirlist = &resp->dirlist;
	काष्ठा xdr_stream *xdr = &resp->xdr;

	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस false;
	/* fileid */
	अगर (xdr_stream_encode_u32(xdr, (u32)ino) < 0)
		वापस false;
	/* name */
	अगर (xdr_stream_encode_opaque(xdr, name, min(namlen, NFS2_MAXNAMLEN)) < 0)
		वापस false;
	/* cookie */
	resp->cookie_offset = dirlist->len;
	अगर (xdr_stream_encode_u32(xdr, ~0U) < 0)
		वापस false;

	वापस true;
पूर्ण

/**
 * nfssvc_encode_entry - encode one NFSv2 READसूची entry
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
पूर्णांक nfssvc_encode_entry(व्योम *data, स्थिर अक्षर *name, पूर्णांक namlen,
			loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा सूची_पढ़ो_cd *ccd = data;
	काष्ठा nfsd_सूची_पढ़ोres *resp = container_of(ccd,
						    काष्ठा nfsd_सूची_पढ़ोres,
						    common);
	अचिन्हित पूर्णांक starting_length = resp->dirlist.len;

	/* The offset cookie क्रम the previous entry */
	nfssvc_encode_nfscookie(resp, offset);

	अगर (!svcxdr_encode_entry_common(resp, name, namlen, offset, ino))
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

/*
 * XDR release functions
 */
व्योम nfssvc_release_attrstat(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
पूर्ण

व्योम nfssvc_release_diropres(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_diropres *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
पूर्ण

व्योम nfssvc_release_पढ़ोres(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_पढ़ोres *resp = rqstp->rq_resp;

	fh_put(&resp->fh);
पूर्ण
