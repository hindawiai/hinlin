<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Process version 3 NFS requests.
 *
 * Copyright (C) 1996, 1997, 1998 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/fs.h>
#समावेश <linux/ext2_fs.h>
#समावेश <linux/magic.h>

#समावेश "cache.h"
#समावेश "xdr3.h"
#समावेश "vfs.h"

#घोषणा NFSDDBG_FACILITY		NFSDDBG_PROC

अटल पूर्णांक	nfs3_ftypes[] = अणु
	0,			/* NF3NON */
	S_IFREG,		/* NF3REG */
	S_IFसूची,		/* NF3सूची */
	S_IFBLK,		/* NF3BLK */
	S_IFCHR,		/* NF3CHR */
	S_IFLNK,		/* NF3LNK */
	S_IFSOCK,		/* NF3SOCK */
	S_IFIFO,		/* NF3FIFO */
पूर्ण;

/*
 * शून्य call.
 */
अटल __be32
nfsd3_proc_null(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

/*
 * Get a file's attributes
 */
अटल __be32
nfsd3_proc_getattr(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: GETATTR(3)  %s\n",
		SVCFH_fmt(&argp->fh));

	fh_copy(&resp->fh, &argp->fh);
	resp->status = fh_verअगरy(rqstp, &resp->fh, 0,
				 NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_ROOT);
	अगर (resp->status != nfs_ok)
		जाओ out;

	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

/*
 * Set a file's attributes
 */
अटल __be32
nfsd3_proc_setattr(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_sattrargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: SETATTR(3)  %s\n",
				SVCFH_fmt(&argp->fh));

	fh_copy(&resp->fh, &argp->fh);
	resp->status = nfsd_setattr(rqstp, &resp->fh, &argp->attrs,
				    argp->check_guard, argp->guardसमय);
	वापस rpc_success;
पूर्ण

/*
 * Look up a path name component
 */
अटल __be32
nfsd3_proc_lookup(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_diropargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_diropres  *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: LOOKUP(3)   %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	fh_copy(&resp->dirfh, &argp->fh);
	fh_init(&resp->fh, NFS3_FHSIZE);

	resp->status = nfsd_lookup(rqstp, &resp->dirfh,
				   argp->name, argp->len,
				   &resp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Check file access
 */
अटल __be32
nfsd3_proc_access(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_accessargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_accessres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: ACCESS(3)   %s 0x%x\n",
				SVCFH_fmt(&argp->fh),
				argp->access);

	fh_copy(&resp->fh, &argp->fh);
	resp->access = argp->access;
	resp->status = nfsd_access(rqstp, &resp->fh, &resp->access, शून्य);
	वापस rpc_success;
पूर्ण

/*
 * Read a symlink.
 */
अटल __be32
nfsd3_proc_पढ़ोlink(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd3_पढ़ोlinkres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: READLINK(3) %s\n", SVCFH_fmt(&argp->fh));

	/* Read the symlink. */
	fh_copy(&resp->fh, &argp->fh);
	resp->len = NFS3_MAXPATHLEN;
	resp->pages = rqstp->rq_next_page++;
	resp->status = nfsd_पढ़ोlink(rqstp, &resp->fh,
				     page_address(*resp->pages), &resp->len);
	वापस rpc_success;
पूर्ण

/*
 * Read a portion of a file.
 */
अटल __be32
nfsd3_proc_पढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_पढ़ोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_पढ़ोres *resp = rqstp->rq_resp;
	u32 max_blocksize = svc_max_payload(rqstp);
	अचिन्हित पूर्णांक len;
	पूर्णांक v;

	argp->count = min_t(u32, argp->count, max_blocksize);

	dprपूर्णांकk("nfsd: READ(3) %s %lu bytes at %Lu\n",
				SVCFH_fmt(&argp->fh),
				(अचिन्हित दीर्घ) argp->count,
				(अचिन्हित दीर्घ दीर्घ) argp->offset);

	v = 0;
	len = argp->count;
	resp->pages = rqstp->rq_next_page;
	जबतक (len > 0) अणु
		काष्ठा page *page = *(rqstp->rq_next_page++);

		rqstp->rq_vec[v].iov_base = page_address(page);
		rqstp->rq_vec[v].iov_len = min_t(अचिन्हित पूर्णांक, len, PAGE_SIZE);
		len -= rqstp->rq_vec[v].iov_len;
		v++;
	पूर्ण

	/* Obtain buffer poपूर्णांकer क्रम payload.
	 * 1 (status) + 22 (post_op_attr) + 1 (count) + 1 (eof)
	 * + 1 (xdr opaque byte count) = 26
	 */
	resp->count = argp->count;
	svc_reserve_auth(rqstp, ((1 + NFS3_POST_OP_ATTR_WORDS + 3)<<2) + resp->count +4);

	fh_copy(&resp->fh, &argp->fh);
	resp->status = nfsd_पढ़ो(rqstp, &resp->fh, argp->offset,
				 rqstp->rq_vec, v, &resp->count, &resp->eof);
	वापस rpc_success;
पूर्ण

/*
 * Write data to a file
 */
अटल __be32
nfsd3_proc_ग_लिखो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_ग_लिखोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_ग_लिखोres *resp = rqstp->rq_resp;
	अचिन्हित दीर्घ cnt = argp->len;
	अचिन्हित पूर्णांक nvecs;

	dprपूर्णांकk("nfsd: WRITE(3)    %s %d bytes at %Lu%s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				(अचिन्हित दीर्घ दीर्घ) argp->offset,
				argp->stable? " stable" : "");

	fh_copy(&resp->fh, &argp->fh);
	resp->committed = argp->stable;
	nvecs = svc_fill_ग_लिखो_vector(rqstp, rqstp->rq_arg.pages,
				      &argp->first, cnt);
	अगर (!nvecs) अणु
		resp->status = nfserr_io;
		जाओ out;
	पूर्ण
	resp->status = nfsd_ग_लिखो(rqstp, &resp->fh, argp->offset,
				  rqstp->rq_vec, nvecs, &cnt,
				  resp->committed, resp->verf);
	resp->count = cnt;
out:
	वापस rpc_success;
पूर्ण

/*
 * With NFSv3, CREATE processing is a lot easier than with NFSv2.
 * At least in theory; we'll see how it fares in practice when the
 * first reports about SunOS compatibility problems start to pour in...
 */
अटल __be32
nfsd3_proc_create(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_createargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_diropres *resp = rqstp->rq_resp;
	svc_fh		*dirfhp, *newfhp = शून्य;
	काष्ठा iattr	*attr;

	dprपूर्णांकk("nfsd: CREATE(3)   %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	dirfhp = fh_copy(&resp->dirfh, &argp->fh);
	newfhp = fh_init(&resp->fh, NFS3_FHSIZE);
	attr   = &argp->attrs;

	/* Unfudge the mode bits */
	attr->ia_mode &= ~S_IFMT;
	अगर (!(attr->ia_valid & ATTR_MODE)) अणु 
		attr->ia_valid |= ATTR_MODE;
		attr->ia_mode = S_IFREG;
	पूर्ण अन्यथा अणु
		attr->ia_mode = (attr->ia_mode & ~S_IFMT) | S_IFREG;
	पूर्ण

	/* Now create the file and set attributes */
	resp->status = करो_nfsd_create(rqstp, dirfhp, argp->name, argp->len,
				      attr, newfhp, argp->createmode,
				      (u32 *)argp->verf, शून्य, शून्य);
	वापस rpc_success;
पूर्ण

/*
 * Make directory. This operation is not idempotent.
 */
अटल __be32
nfsd3_proc_सूची_गढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_createargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_diropres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: MKDIR(3)    %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	argp->attrs.ia_valid &= ~ATTR_SIZE;
	fh_copy(&resp->dirfh, &argp->fh);
	fh_init(&resp->fh, NFS3_FHSIZE);
	resp->status = nfsd_create(rqstp, &resp->dirfh, argp->name, argp->len,
				   &argp->attrs, S_IFसूची, 0, &resp->fh);
	fh_unlock(&resp->dirfh);
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd3_proc_symlink(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_symlinkargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_diropres *resp = rqstp->rq_resp;

	अगर (argp->tlen == 0) अणु
		resp->status = nfserr_inval;
		जाओ out;
	पूर्ण
	अगर (argp->tlen > NFS3_MAXPATHLEN) अणु
		resp->status = nfserr_nametooदीर्घ;
		जाओ out;
	पूर्ण

	argp->tname = svc_fill_symlink_pathname(rqstp, &argp->first,
						page_address(rqstp->rq_arg.pages[0]),
						argp->tlen);
	अगर (IS_ERR(argp->tname)) अणु
		resp->status = nfsत्रुटि_सं(PTR_ERR(argp->tname));
		जाओ out;
	पूर्ण

	dprपूर्णांकk("nfsd: SYMLINK(3)  %s %.*s -> %.*s\n",
				SVCFH_fmt(&argp->ffh),
				argp->flen, argp->fname,
				argp->tlen, argp->tname);

	fh_copy(&resp->dirfh, &argp->ffh);
	fh_init(&resp->fh, NFS3_FHSIZE);
	resp->status = nfsd_symlink(rqstp, &resp->dirfh, argp->fname,
				    argp->flen, argp->tname, &resp->fh);
	kमुक्त(argp->tname);
out:
	वापस rpc_success;
पूर्ण

/*
 * Make socket/fअगरo/device.
 */
अटल __be32
nfsd3_proc_mknod(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_mknodargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_diropres  *resp = rqstp->rq_resp;
	पूर्णांक type;
	dev_t	rdev = 0;

	dprपूर्णांकk("nfsd: MKNOD(3)    %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	fh_copy(&resp->dirfh, &argp->fh);
	fh_init(&resp->fh, NFS3_FHSIZE);

	अगर (argp->ftype == NF3CHR || argp->ftype == NF3BLK) अणु
		rdev = MKDEV(argp->major, argp->minor);
		अगर (MAJOR(rdev) != argp->major ||
		    MINOR(rdev) != argp->minor) अणु
			resp->status = nfserr_inval;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (argp->ftype != NF3SOCK && argp->ftype != NF3FIFO) अणु
		resp->status = nfserr_badtype;
		जाओ out;
	पूर्ण

	type = nfs3_ftypes[argp->ftype];
	resp->status = nfsd_create(rqstp, &resp->dirfh, argp->name, argp->len,
				   &argp->attrs, type, rdev, &resp->fh);
	fh_unlock(&resp->dirfh);
out:
	वापस rpc_success;
पूर्ण

/*
 * Remove file/fअगरo/socket etc.
 */
अटल __be32
nfsd3_proc_हटाओ(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_diropargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: REMOVE(3)   %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	/* Unlink. -S_IFसूची means file must not be a directory */
	fh_copy(&resp->fh, &argp->fh);
	resp->status = nfsd_unlink(rqstp, &resp->fh, -S_IFसूची,
				   argp->name, argp->len);
	fh_unlock(&resp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Remove a directory
 */
अटल __be32
nfsd3_proc_सूची_हटाओ(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_diropargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_attrstat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: RMDIR(3)    %s %.*s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				argp->name);

	fh_copy(&resp->fh, &argp->fh);
	resp->status = nfsd_unlink(rqstp, &resp->fh, S_IFसूची,
				   argp->name, argp->len);
	fh_unlock(&resp->fh);
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd3_proc_नाम(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_नामargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_नामres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: RENAME(3)   %s %.*s ->\n",
				SVCFH_fmt(&argp->ffh),
				argp->flen,
				argp->fname);
	dprपूर्णांकk("nfsd: -> %s %.*s\n",
				SVCFH_fmt(&argp->tfh),
				argp->tlen,
				argp->tname);

	fh_copy(&resp->ffh, &argp->ffh);
	fh_copy(&resp->tfh, &argp->tfh);
	resp->status = nfsd_नाम(rqstp, &resp->ffh, argp->fname, argp->flen,
				   &resp->tfh, argp->tname, argp->tlen);
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd3_proc_link(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_linkargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_linkres  *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: LINK(3)     %s ->\n",
				SVCFH_fmt(&argp->ffh));
	dprपूर्णांकk("nfsd:   -> %s %.*s\n",
				SVCFH_fmt(&argp->tfh),
				argp->tlen,
				argp->tname);

	fh_copy(&resp->fh,  &argp->ffh);
	fh_copy(&resp->tfh, &argp->tfh);
	resp->status = nfsd_link(rqstp, &resp->tfh, argp->tname, argp->tlen,
				 &resp->fh);
	वापस rpc_success;
पूर्ण

अटल व्योम nfsd3_init_dirlist_pages(काष्ठा svc_rqst *rqstp,
				     काष्ठा nfsd3_सूची_पढ़ोres *resp,
				     पूर्णांक count)
अणु
	काष्ठा xdr_buf *buf = &resp->dirlist;
	काष्ठा xdr_stream *xdr = &resp->xdr;

	count = min_t(u32, count, svc_max_payload(rqstp));

	स_रखो(buf, 0, माप(*buf));

	/* Reserve room क्रम the शून्य ptr & eof flag (-2 words) */
	buf->buflen = count - XDR_UNIT * 2;
	buf->pages = rqstp->rq_next_page;
	जबतक (count > 0) अणु
		rqstp->rq_next_page++;
		count -= PAGE_SIZE;
	पूर्ण

	/* This is xdr_init_encode(), but it assumes that
	 * the head kvec has alपढ़ोy been consumed. */
	xdr_set_scratch_buffer(xdr, शून्य, 0);
	xdr->buf = buf;
	xdr->page_ptr = buf->pages;
	xdr->iov = शून्य;
	xdr->p = page_address(*buf->pages);
	xdr->end = xdr->p + (PAGE_SIZE >> 2);
	xdr->rqst = शून्य;
पूर्ण

/*
 * Read a portion of a directory.
 */
अटल __be32
nfsd3_proc_सूची_पढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_सूची_पढ़ोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_सूची_पढ़ोres  *resp = rqstp->rq_resp;
	loff_t		offset;

	dprपूर्णांकk("nfsd: READDIR(3)  %s %d bytes at %d\n",
				SVCFH_fmt(&argp->fh),
				argp->count, (u32) argp->cookie);

	nfsd3_init_dirlist_pages(rqstp, resp, argp->count);

	fh_copy(&resp->fh, &argp->fh);
	resp->common.err = nfs_ok;
	resp->cookie_offset = 0;
	resp->rqstp = rqstp;
	offset = argp->cookie;
	resp->status = nfsd_सूची_पढ़ो(rqstp, &resp->fh, &offset,
				    &resp->common, nfs3svc_encode_entry3);
	स_नकल(resp->verf, argp->verf, 8);
	nfs3svc_encode_cookie3(resp, offset);

	/* Recycle only pages that were part of the reply */
	rqstp->rq_next_page = resp->xdr.page_ptr + 1;

	वापस rpc_success;
पूर्ण

/*
 * Read a portion of a directory, including file handles and attrs.
 * For now, we choose to ignore the dircount parameter.
 */
अटल __be32
nfsd3_proc_सूची_पढ़ोplus(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_सूची_पढ़ोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_सूची_पढ़ोres  *resp = rqstp->rq_resp;
	loff_t	offset;

	dprपूर्णांकk("nfsd: READDIR+(3) %s %d bytes at %d\n",
				SVCFH_fmt(&argp->fh),
				argp->count, (u32) argp->cookie);

	nfsd3_init_dirlist_pages(rqstp, resp, argp->count);

	fh_copy(&resp->fh, &argp->fh);
	resp->common.err = nfs_ok;
	resp->cookie_offset = 0;
	resp->rqstp = rqstp;
	offset = argp->cookie;

	resp->status = fh_verअगरy(rqstp, &resp->fh, S_IFसूची, NFSD_MAY_NOP);
	अगर (resp->status != nfs_ok)
		जाओ out;

	अगर (resp->fh.fh_export->ex_flags & NFSEXP_NOREADसूचीPLUS) अणु
		resp->status = nfserr_notsupp;
		जाओ out;
	पूर्ण

	resp->status = nfsd_सूची_पढ़ो(rqstp, &resp->fh, &offset,
				    &resp->common, nfs3svc_encode_entryplus3);
	स_नकल(resp->verf, argp->verf, 8);
	nfs3svc_encode_cookie3(resp, offset);

	/* Recycle only pages that were part of the reply */
	rqstp->rq_next_page = resp->xdr.page_ptr + 1;

out:
	वापस rpc_success;
पूर्ण

/*
 * Get file प्रणाली stats
 */
अटल __be32
nfsd3_proc_fsstat(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd3_fsstatres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: FSSTAT(3)   %s\n",
				SVCFH_fmt(&argp->fh));

	resp->status = nfsd_statfs(rqstp, &argp->fh, &resp->stats, 0);
	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Get file प्रणाली info
 */
अटल __be32
nfsd3_proc_fsinfo(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd3_fsinक्रमes *resp = rqstp->rq_resp;
	u32	max_blocksize = svc_max_payload(rqstp);

	dprपूर्णांकk("nfsd: FSINFO(3)   %s\n",
				SVCFH_fmt(&argp->fh));

	resp->f_rपंचांगax  = max_blocksize;
	resp->f_rtpref = max_blocksize;
	resp->f_rपंचांगult = PAGE_SIZE;
	resp->f_wपंचांगax  = max_blocksize;
	resp->f_wtpref = max_blocksize;
	resp->f_wपंचांगult = PAGE_SIZE;
	resp->f_dtpref = max_blocksize;
	resp->f_maxfilesize = ~(u32) 0;
	resp->f_properties = NFS3_FSF_DEFAULT;

	resp->status = fh_verअगरy(rqstp, &argp->fh, 0,
				 NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_ROOT);

	/* Check special features of the file प्रणाली. May request
	 * dअगरferent पढ़ो/ग_लिखो sizes क्रम file प्रणालीs known to have
	 * problems with large blocks */
	अगर (resp->status == nfs_ok) अणु
		काष्ठा super_block *sb = argp->fh.fh_dentry->d_sb;

		/* Note that we करोn't care for remote fs's here */
		अगर (sb->s_magic == MSDOS_SUPER_MAGIC) अणु
			resp->f_properties = NFS3_FSF_BILLYBOY;
		पूर्ण
		resp->f_maxfilesize = sb->s_maxbytes;
	पूर्ण

	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Get pathconf info क्रम the specअगरied file
 */
अटल __be32
nfsd3_proc_pathconf(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd3_pathconfres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: PATHCONF(3) %s\n",
				SVCFH_fmt(&argp->fh));

	/* Set शेष pathconf */
	resp->p_link_max = 255;		/* at least */
	resp->p_name_max = 255;		/* at least */
	resp->p_no_trunc = 0;
	resp->p_chown_restricted = 1;
	resp->p_हाल_insensitive = 0;
	resp->p_हाल_preserving = 1;

	resp->status = fh_verअगरy(rqstp, &argp->fh, 0, NFSD_MAY_NOP);

	अगर (resp->status == nfs_ok) अणु
		काष्ठा super_block *sb = argp->fh.fh_dentry->d_sb;

		/* Note that we करोn't care for remote fs's here */
		चयन (sb->s_magic) अणु
		हाल EXT2_SUPER_MAGIC:
			resp->p_link_max = EXT2_LINK_MAX;
			resp->p_name_max = EXT2_NAME_LEN;
			अवरोध;
		हाल MSDOS_SUPER_MAGIC:
			resp->p_हाल_insensitive = 1;
			resp->p_हाल_preserving  = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Commit a file (range) to stable storage.
 */
अटल __be32
nfsd3_proc_commit(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd3_commitargs *argp = rqstp->rq_argp;
	काष्ठा nfsd3_commitres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: COMMIT(3)   %s %u@%Lu\n",
				SVCFH_fmt(&argp->fh),
				argp->count,
				(अचिन्हित दीर्घ दीर्घ) argp->offset);

	अगर (argp->offset > NFS_OFFSET_MAX) अणु
		resp->status = nfserr_inval;
		जाओ out;
	पूर्ण

	fh_copy(&resp->fh, &argp->fh);
	resp->status = nfsd_commit(rqstp, &resp->fh, argp->offset,
				   argp->count, resp->verf);
out:
	वापस rpc_success;
पूर्ण


/*
 * NFSv3 Server procedures.
 * Only the results of non-idempotent operations are cached.
 */
#घोषणा nfs3svc_encode_attrstatres	nfs3svc_encode_attrstat
#घोषणा nfs3svc_encode_wccstatres	nfs3svc_encode_wccstat
#घोषणा nfsd3_सूची_गढ़ोargs			nfsd3_createargs
#घोषणा nfsd3_सूची_पढ़ोplusargs		nfsd3_सूची_पढ़ोargs
#घोषणा nfsd3_fhandleargs		nfsd_fhandle
#घोषणा nfsd3_attrstatres		nfsd3_attrstat
#घोषणा nfsd3_wccstatres		nfsd3_attrstat
#घोषणा nfsd3_createres			nfsd3_diropres

#घोषणा ST 1		/* status*/
#घोषणा FH 17		/* filehandle with length */
#घोषणा AT 21		/* attributes */
#घोषणा pAT (1+AT)	/* post attributes - conditional */
#घोषणा WC (7+pAT)	/* WCC attributes */

अटल स्थिर काष्ठा svc_procedure nfsd_procedures3[22] = अणु
	[NFS3PROC_शून्य] = अणु
		.pc_func = nfsd3_proc_null,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST,
		.pc_name = "NULL",
	पूर्ण,
	[NFS3PROC_GETATTR] = अणु
		.pc_func = nfsd3_proc_getattr,
		.pc_decode = nfs3svc_decode_fhandleargs,
		.pc_encode = nfs3svc_encode_getattrres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd_fhandle),
		.pc_ressize = माप(काष्ठा nfsd3_attrstatres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+AT,
		.pc_name = "GETATTR",
	पूर्ण,
	[NFS3PROC_SETATTR] = अणु
		.pc_func = nfsd3_proc_setattr,
		.pc_decode = nfs3svc_decode_sattrargs,
		.pc_encode = nfs3svc_encode_wccstatres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_sattrargs),
		.pc_ressize = माप(काष्ठा nfsd3_wccstatres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+WC,
		.pc_name = "SETATTR",
	पूर्ण,
	[NFS3PROC_LOOKUP] = अणु
		.pc_func = nfsd3_proc_lookup,
		.pc_decode = nfs3svc_decode_diropargs,
		.pc_encode = nfs3svc_encode_lookupres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_diropargs),
		.pc_ressize = माप(काष्ठा nfsd3_diropres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+FH+pAT+pAT,
		.pc_name = "LOOKUP",
	पूर्ण,
	[NFS3PROC_ACCESS] = अणु
		.pc_func = nfsd3_proc_access,
		.pc_decode = nfs3svc_decode_accessargs,
		.pc_encode = nfs3svc_encode_accessres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_accessargs),
		.pc_ressize = माप(काष्ठा nfsd3_accessres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT+1,
		.pc_name = "ACCESS",
	पूर्ण,
	[NFS3PROC_READLINK] = अणु
		.pc_func = nfsd3_proc_पढ़ोlink,
		.pc_decode = nfs3svc_decode_fhandleargs,
		.pc_encode = nfs3svc_encode_पढ़ोlinkres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd_fhandle),
		.pc_ressize = माप(काष्ठा nfsd3_पढ़ोlinkres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT+1+NFS3_MAXPATHLEN/4,
		.pc_name = "READLINK",
	पूर्ण,
	[NFS3PROC_READ] = अणु
		.pc_func = nfsd3_proc_पढ़ो,
		.pc_decode = nfs3svc_decode_पढ़ोargs,
		.pc_encode = nfs3svc_encode_पढ़ोres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_पढ़ोargs),
		.pc_ressize = माप(काष्ठा nfsd3_पढ़ोres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT+4+NFSSVC_MAXBLKSIZE/4,
		.pc_name = "READ",
	पूर्ण,
	[NFS3PROC_WRITE] = अणु
		.pc_func = nfsd3_proc_ग_लिखो,
		.pc_decode = nfs3svc_decode_ग_लिखोargs,
		.pc_encode = nfs3svc_encode_ग_लिखोres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_ग_लिखोargs),
		.pc_ressize = माप(काष्ठा nfsd3_ग_लिखोres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+WC+4,
		.pc_name = "WRITE",
	पूर्ण,
	[NFS3PROC_CREATE] = अणु
		.pc_func = nfsd3_proc_create,
		.pc_decode = nfs3svc_decode_createargs,
		.pc_encode = nfs3svc_encode_createres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_createargs),
		.pc_ressize = माप(काष्ठा nfsd3_createres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+(1+FH+pAT)+WC,
		.pc_name = "CREATE",
	पूर्ण,
	[NFS3PROC_MKसूची] = अणु
		.pc_func = nfsd3_proc_सूची_गढ़ो,
		.pc_decode = nfs3svc_decode_सूची_गढ़ोargs,
		.pc_encode = nfs3svc_encode_createres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_सूची_गढ़ोargs),
		.pc_ressize = माप(काष्ठा nfsd3_createres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+(1+FH+pAT)+WC,
		.pc_name = "MKDIR",
	पूर्ण,
	[NFS3PROC_SYMLINK] = अणु
		.pc_func = nfsd3_proc_symlink,
		.pc_decode = nfs3svc_decode_symlinkargs,
		.pc_encode = nfs3svc_encode_createres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_symlinkargs),
		.pc_ressize = माप(काष्ठा nfsd3_createres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+(1+FH+pAT)+WC,
		.pc_name = "SYMLINK",
	पूर्ण,
	[NFS3PROC_MKNOD] = अणु
		.pc_func = nfsd3_proc_mknod,
		.pc_decode = nfs3svc_decode_mknodargs,
		.pc_encode = nfs3svc_encode_createres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_mknodargs),
		.pc_ressize = माप(काष्ठा nfsd3_createres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+(1+FH+pAT)+WC,
		.pc_name = "MKNOD",
	पूर्ण,
	[NFS3PROC_REMOVE] = अणु
		.pc_func = nfsd3_proc_हटाओ,
		.pc_decode = nfs3svc_decode_diropargs,
		.pc_encode = nfs3svc_encode_wccstatres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_diropargs),
		.pc_ressize = माप(काष्ठा nfsd3_wccstatres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+WC,
		.pc_name = "REMOVE",
	पूर्ण,
	[NFS3PROC_RMसूची] = अणु
		.pc_func = nfsd3_proc_सूची_हटाओ,
		.pc_decode = nfs3svc_decode_diropargs,
		.pc_encode = nfs3svc_encode_wccstatres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_diropargs),
		.pc_ressize = माप(काष्ठा nfsd3_wccstatres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+WC,
		.pc_name = "RMDIR",
	पूर्ण,
	[NFS3PROC_RENAME] = अणु
		.pc_func = nfsd3_proc_नाम,
		.pc_decode = nfs3svc_decode_नामargs,
		.pc_encode = nfs3svc_encode_नामres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_नामargs),
		.pc_ressize = माप(काष्ठा nfsd3_नामres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+WC+WC,
		.pc_name = "RENAME",
	पूर्ण,
	[NFS3PROC_LINK] = अणु
		.pc_func = nfsd3_proc_link,
		.pc_decode = nfs3svc_decode_linkargs,
		.pc_encode = nfs3svc_encode_linkres,
		.pc_release = nfs3svc_release_fhandle2,
		.pc_argsize = माप(काष्ठा nfsd3_linkargs),
		.pc_ressize = माप(काष्ठा nfsd3_linkres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+pAT+WC,
		.pc_name = "LINK",
	पूर्ण,
	[NFS3PROC_READसूची] = अणु
		.pc_func = nfsd3_proc_सूची_पढ़ो,
		.pc_decode = nfs3svc_decode_सूची_पढ़ोargs,
		.pc_encode = nfs3svc_encode_सूची_पढ़ोres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_सूची_पढ़ोargs),
		.pc_ressize = माप(काष्ठा nfsd3_सूची_पढ़ोres),
		.pc_cachetype = RC_NOCACHE,
		.pc_name = "READDIR",
	पूर्ण,
	[NFS3PROC_READसूचीPLUS] = अणु
		.pc_func = nfsd3_proc_सूची_पढ़ोplus,
		.pc_decode = nfs3svc_decode_सूची_पढ़ोplusargs,
		.pc_encode = nfs3svc_encode_सूची_पढ़ोres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_सूची_पढ़ोplusargs),
		.pc_ressize = माप(काष्ठा nfsd3_सूची_पढ़ोres),
		.pc_cachetype = RC_NOCACHE,
		.pc_name = "READDIRPLUS",
	पूर्ण,
	[NFS3PROC_FSSTAT] = अणु
		.pc_func = nfsd3_proc_fsstat,
		.pc_decode = nfs3svc_decode_fhandleargs,
		.pc_encode = nfs3svc_encode_fsstatres,
		.pc_argsize = माप(काष्ठा nfsd3_fhandleargs),
		.pc_ressize = माप(काष्ठा nfsd3_fsstatres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT+2*6+1,
		.pc_name = "FSSTAT",
	पूर्ण,
	[NFS3PROC_FSINFO] = अणु
		.pc_func = nfsd3_proc_fsinfo,
		.pc_decode = nfs3svc_decode_fhandleargs,
		.pc_encode = nfs3svc_encode_fsinक्रमes,
		.pc_argsize = माप(काष्ठा nfsd3_fhandleargs),
		.pc_ressize = माप(काष्ठा nfsd3_fsinक्रमes),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT+12,
		.pc_name = "FSINFO",
	पूर्ण,
	[NFS3PROC_PATHCONF] = अणु
		.pc_func = nfsd3_proc_pathconf,
		.pc_decode = nfs3svc_decode_fhandleargs,
		.pc_encode = nfs3svc_encode_pathconfres,
		.pc_argsize = माप(काष्ठा nfsd3_fhandleargs),
		.pc_ressize = माप(काष्ठा nfsd3_pathconfres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+pAT+6,
		.pc_name = "PATHCONF",
	पूर्ण,
	[NFS3PROC_COMMIT] = अणु
		.pc_func = nfsd3_proc_commit,
		.pc_decode = nfs3svc_decode_commitargs,
		.pc_encode = nfs3svc_encode_commitres,
		.pc_release = nfs3svc_release_fhandle,
		.pc_argsize = माप(काष्ठा nfsd3_commitargs),
		.pc_ressize = माप(काष्ठा nfsd3_commitres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+WC+2,
		.pc_name = "COMMIT",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nfsd_count3[ARRAY_SIZE(nfsd_procedures3)];
स्थिर काष्ठा svc_version nfsd_version3 = अणु
	.vs_vers	= 3,
	.vs_nproc	= 22,
	.vs_proc	= nfsd_procedures3,
	.vs_dispatch	= nfsd_dispatch,
	.vs_count	= nfsd_count3,
	.vs_xdrsize	= NFS3_SVC_XDRSIZE,
पूर्ण;
