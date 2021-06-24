<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Process version 2 NFS requests.
 *
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/namei.h>

#समावेश "cache.h"
#समावेश "xdr.h"
#समावेश "vfs.h"

#घोषणा NFSDDBG_FACILITY		NFSDDBG_PROC

अटल __be32
nfsd_proc_null(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

/*
 * Get a file's attributes
 * N.B. After this call resp->fh needs an fh_put
 */
अटल __be32
nfsd_proc_getattr(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: GETATTR  %s\n", SVCFH_fmt(&argp->fh));

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
 * N.B. After this call resp->fh needs an fh_put
 */
अटल __be32
nfsd_proc_setattr(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_sattrargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;
	काष्ठा iattr *iap = &argp->attrs;
	काष्ठा svc_fh *fhp;

	dprपूर्णांकk("nfsd: SETATTR  %s, valid=%x, size=%ld\n",
		SVCFH_fmt(&argp->fh),
		argp->attrs.ia_valid, (दीर्घ) argp->attrs.ia_size);

	fhp = fh_copy(&resp->fh, &argp->fh);

	/*
	 * NFSv2 करोes not dअगरferentiate between "set-[ac]time-to-now"
	 * which only requires access, and "set-[ac]time-to-X" which
	 * requires ownership.
	 * So अगर it looks like it might be "set both to the same समय which
	 * is बंद to now", and अगर setattr_prepare fails, then we
	 * convert to "set to now" instead of "set to explicit time"
	 *
	 * We only call setattr_prepare as the last test as technically
	 * it is not an पूर्णांकerface that we should be using.
	 */
#घोषणा BOTH_TIME_SET (ATTR_ATIME_SET | ATTR_MTIME_SET)
#घोषणा	MAX_TOUCH_TIME_ERROR (30*60)
	अगर ((iap->ia_valid & BOTH_TIME_SET) == BOTH_TIME_SET &&
	    iap->ia_mसमय.tv_sec == iap->ia_aसमय.tv_sec) अणु
		/*
		 * Looks probable.
		 *
		 * Now just make sure समय is in the right ballpark.
		 * Solaris, at least, करोesn't seem to care what the समय
		 * request is.  We require it be within 30 minutes of now.
		 */
		समय64_t delta = iap->ia_aसमय.tv_sec - kसमय_get_real_seconds();

		resp->status = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_NOP);
		अगर (resp->status != nfs_ok)
			जाओ out;

		अगर (delta < 0)
			delta = -delta;
		अगर (delta < MAX_TOUCH_TIME_ERROR &&
		    setattr_prepare(&init_user_ns, fhp->fh_dentry, iap) != 0) अणु
			/*
			 * Turn off ATTR_[AM]TIME_SET but leave ATTR_[AM]TIME.
			 * This will cause notअगरy_change to set these बार
			 * to "now"
			 */
			iap->ia_valid &= ~BOTH_TIME_SET;
		पूर्ण
	पूर्ण

	resp->status = nfsd_setattr(rqstp, fhp, iap, 0, (समय64_t)0);
	अगर (resp->status != nfs_ok)
		जाओ out;

	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

/* Obsolete, replaced by MNTPROC_MNT. */
अटल __be32
nfsd_proc_root(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

/*
 * Look up a path name component
 * Note: the dentry in the resp->fh may be negative अगर the file
 * करोesn't exist yet.
 * N.B. After this call resp->fh needs an fh_put
 */
अटल __be32
nfsd_proc_lookup(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_diropargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_diropres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: LOOKUP   %s %.*s\n",
		SVCFH_fmt(&argp->fh), argp->len, argp->name);

	fh_init(&resp->fh, NFS_FHSIZE);
	resp->status = nfsd_lookup(rqstp, &argp->fh, argp->name, argp->len,
				   &resp->fh);
	fh_put(&argp->fh);
	अगर (resp->status != nfs_ok)
		जाओ out;

	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

/*
 * Read a symlink.
 */
अटल __be32
nfsd_proc_पढ़ोlink(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd_पढ़ोlinkres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: READLINK %s\n", SVCFH_fmt(&argp->fh));

	/* Read the symlink. */
	resp->len = NFS_MAXPATHLEN;
	resp->page = *(rqstp->rq_next_page++);
	resp->status = nfsd_पढ़ोlink(rqstp, &argp->fh,
				     page_address(resp->page), &resp->len);

	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Read a portion of a file.
 * N.B. After this call resp->fh needs an fh_put
 */
अटल __be32
nfsd_proc_पढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_पढ़ोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_पढ़ोres *resp = rqstp->rq_resp;
	अचिन्हित पूर्णांक len;
	u32 eof;
	पूर्णांक v;

	dprपूर्णांकk("nfsd: READ    %s %d bytes at %d\n",
		SVCFH_fmt(&argp->fh),
		argp->count, argp->offset);

	argp->count = min_t(u32, argp->count, NFSSVC_MAXBLKSIZE_V2);

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

	/* Obtain buffer poपूर्णांकer क्रम payload. 19 is 1 word क्रम
	 * status, 17 words क्रम fattr, and 1 word क्रम the byte count.
	 */
	svc_reserve_auth(rqstp, (19<<2) + argp->count + 4);

	resp->count = argp->count;
	fh_copy(&resp->fh, &argp->fh);
	resp->status = nfsd_पढ़ो(rqstp, &resp->fh, argp->offset,
				 rqstp->rq_vec, v, &resp->count, &eof);
	अगर (resp->status == nfs_ok)
		resp->status = fh_getattr(&resp->fh, &resp->stat);
	अन्यथा अगर (resp->status == nfserr_jukebox)
		वापस rpc_drop_reply;
	वापस rpc_success;
पूर्ण

/* Reserved */
अटल __be32
nfsd_proc_ग_लिखोcache(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

/*
 * Write data to a file
 * N.B. After this call resp->fh needs an fh_put
 */
अटल __be32
nfsd_proc_ग_लिखो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_ग_लिखोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_attrstat *resp = rqstp->rq_resp;
	अचिन्हित दीर्घ cnt = argp->len;
	अचिन्हित पूर्णांक nvecs;

	dprपूर्णांकk("nfsd: WRITE    %s %d bytes at %d\n",
		SVCFH_fmt(&argp->fh),
		argp->len, argp->offset);

	nvecs = svc_fill_ग_लिखो_vector(rqstp, rqstp->rq_arg.pages,
				      &argp->first, cnt);
	अगर (!nvecs) अणु
		resp->status = nfserr_io;
		जाओ out;
	पूर्ण

	resp->status = nfsd_ग_लिखो(rqstp, fh_copy(&resp->fh, &argp->fh),
				  argp->offset, rqstp->rq_vec, nvecs,
				  &cnt, NFS_DATA_SYNC, शून्य);
	अगर (resp->status == nfs_ok)
		resp->status = fh_getattr(&resp->fh, &resp->stat);
	अन्यथा अगर (resp->status == nfserr_jukebox)
		वापस rpc_drop_reply;
out:
	वापस rpc_success;
पूर्ण

/*
 * CREATE processing is complicated. The keyword here is `overloaded.'
 * The parent directory is kept locked between the check क्रम existence
 * and the actual create() call in compliance with VFS protocols.
 * N.B. After this call _both_ argp->fh and resp->fh need an fh_put
 */
अटल __be32
nfsd_proc_create(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_createargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_diropres *resp = rqstp->rq_resp;
	svc_fh		*dirfhp = &argp->fh;
	svc_fh		*newfhp = &resp->fh;
	काष्ठा iattr	*attr = &argp->attrs;
	काष्ठा inode	*inode;
	काष्ठा dentry	*dchild;
	पूर्णांक		type, mode;
	पूर्णांक		hosterr;
	dev_t		rdev = 0, wanted = new_decode_dev(attr->ia_size);

	dprपूर्णांकk("nfsd: CREATE   %s %.*s\n",
		SVCFH_fmt(dirfhp), argp->len, argp->name);

	/* First verअगरy the parent file handle */
	resp->status = fh_verअगरy(rqstp, dirfhp, S_IFसूची, NFSD_MAY_EXEC);
	अगर (resp->status != nfs_ok)
		जाओ करोne; /* must fh_put dirfhp even on error */

	/* Check क्रम NFSD_MAY_WRITE in nfsd_create अगर necessary */

	resp->status = nfserr_exist;
	अगर (isकरोtent(argp->name, argp->len))
		जाओ करोne;
	hosterr = fh_want_ग_लिखो(dirfhp);
	अगर (hosterr) अणु
		resp->status = nfsत्रुटि_सं(hosterr);
		जाओ करोne;
	पूर्ण

	fh_lock_nested(dirfhp, I_MUTEX_PARENT);
	dchild = lookup_one_len(argp->name, dirfhp->fh_dentry, argp->len);
	अगर (IS_ERR(dchild)) अणु
		resp->status = nfsत्रुटि_सं(PTR_ERR(dchild));
		जाओ out_unlock;
	पूर्ण
	fh_init(newfhp, NFS_FHSIZE);
	resp->status = fh_compose(newfhp, dirfhp->fh_export, dchild, dirfhp);
	अगर (!resp->status && d_really_is_negative(dchild))
		resp->status = nfserr_noent;
	dput(dchild);
	अगर (resp->status) अणु
		अगर (resp->status != nfserr_noent)
			जाओ out_unlock;
		/*
		 * If the new file handle wasn't verified, we can't tell
		 * whether the file exists or not. Time to bail ...
		 */
		resp->status = nfserr_acces;
		अगर (!newfhp->fh_dentry) अणु
			prपूर्णांकk(KERN_WARNING 
				"nfsd_proc_create: file handle not verified\n");
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	inode = d_inode(newfhp->fh_dentry);

	/* Unfudge the mode bits */
	अगर (attr->ia_valid & ATTR_MODE) अणु
		type = attr->ia_mode & S_IFMT;
		mode = attr->ia_mode & ~S_IFMT;
		अगर (!type) अणु
			/* no type, so अगर target exists, assume same as that,
			 * अन्यथा assume a file */
			अगर (inode) अणु
				type = inode->i_mode & S_IFMT;
				चयन(type) अणु
				हाल S_IFCHR:
				हाल S_IFBLK:
					/* reserve rdev क्रम later checking */
					rdev = inode->i_rdev;
					attr->ia_valid |= ATTR_SIZE;

					fallthrough;
				हाल S_IFIFO:
					/* this is probably a permission check..
					 * at least IRIX implements perm checking on
					 *   echo thing > device-special-file-or-pipe
					 * by करोing a CREATE with type==0
					 */
					resp->status = nfsd_permission(rqstp,
								 newfhp->fh_export,
								 newfhp->fh_dentry,
								 NFSD_MAY_WRITE|NFSD_MAY_LOCAL_ACCESS);
					अगर (resp->status && resp->status != nfserr_rofs)
						जाओ out_unlock;
				पूर्ण
			पूर्ण अन्यथा
				type = S_IFREG;
		पूर्ण
	पूर्ण अन्यथा अगर (inode) अणु
		type = inode->i_mode & S_IFMT;
		mode = inode->i_mode & ~S_IFMT;
	पूर्ण अन्यथा अणु
		type = S_IFREG;
		mode = 0;	/* ??? */
	पूर्ण

	attr->ia_valid |= ATTR_MODE;
	attr->ia_mode = mode;

	/* Special treaपंचांगent क्रम non-regular files according to the
	 * gospel of sun micro
	 */
	अगर (type != S_IFREG) अणु
		अगर (type != S_IFBLK && type != S_IFCHR) अणु
			rdev = 0;
		पूर्ण अन्यथा अगर (type == S_IFCHR && !(attr->ia_valid & ATTR_SIZE)) अणु
			/* If you think you've seen the worst, grok this. */
			type = S_IFIFO;
		पूर्ण अन्यथा अणु
			/* Okay, अक्षर or block special */
			अगर (!rdev)
				rdev = wanted;
		पूर्ण

		/* we've used the SIZE inक्रमmation, so discard it */
		attr->ia_valid &= ~ATTR_SIZE;

		/* Make sure the type and device matches */
		resp->status = nfserr_exist;
		अगर (inode && inode_wrong_type(inode, type))
			जाओ out_unlock;
	पूर्ण

	resp->status = nfs_ok;
	अगर (!inode) अणु
		/* File करोesn't exist. Create it and set attrs */
		resp->status = nfsd_create_locked(rqstp, dirfhp, argp->name,
						  argp->len, attr, type, rdev,
						  newfhp);
	पूर्ण अन्यथा अगर (type == S_IFREG) अणु
		dprपूर्णांकk("nfsd:   existing %s, valid=%x, size=%ld\n",
			argp->name, attr->ia_valid, (दीर्घ) attr->ia_size);
		/* File alपढ़ोy exists. We ignore all attributes except
		 * size, so that creat() behaves exactly like
		 * खोलो(..., O_CREAT|O_TRUNC|O_WRONLY).
		 */
		attr->ia_valid &= ATTR_SIZE;
		अगर (attr->ia_valid)
			resp->status = nfsd_setattr(rqstp, newfhp, attr, 0,
						    (समय64_t)0);
	पूर्ण

out_unlock:
	/* We करोn't really need to unlock, as fh_put करोes it. */
	fh_unlock(dirfhp);
	fh_drop_ग_लिखो(dirfhp);
करोne:
	fh_put(dirfhp);
	अगर (resp->status != nfs_ok)
		जाओ out;
	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd_proc_हटाओ(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_diropargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_stat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: REMOVE   %s %.*s\n", SVCFH_fmt(&argp->fh),
		argp->len, argp->name);

	/* Unlink. -SIFसूची means file must not be a directory */
	resp->status = nfsd_unlink(rqstp, &argp->fh, -S_IFसूची,
				   argp->name, argp->len);
	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd_proc_नाम(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_नामargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_stat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: RENAME   %s %.*s -> \n",
		SVCFH_fmt(&argp->ffh), argp->flen, argp->fname);
	dprपूर्णांकk("nfsd:        ->  %s %.*s\n",
		SVCFH_fmt(&argp->tfh), argp->tlen, argp->tname);

	resp->status = nfsd_नाम(rqstp, &argp->ffh, argp->fname, argp->flen,
				   &argp->tfh, argp->tname, argp->tlen);
	fh_put(&argp->ffh);
	fh_put(&argp->tfh);
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd_proc_link(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_linkargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_stat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: LINK     %s ->\n",
		SVCFH_fmt(&argp->ffh));
	dprपूर्णांकk("nfsd:    %s %.*s\n",
		SVCFH_fmt(&argp->tfh),
		argp->tlen,
		argp->tname);

	resp->status = nfsd_link(rqstp, &argp->tfh, argp->tname, argp->tlen,
				 &argp->ffh);
	fh_put(&argp->ffh);
	fh_put(&argp->tfh);
	वापस rpc_success;
पूर्ण

अटल __be32
nfsd_proc_symlink(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_symlinkargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_stat *resp = rqstp->rq_resp;
	काष्ठा svc_fh	newfh;

	अगर (argp->tlen > NFS_MAXPATHLEN) अणु
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

	dprपूर्णांकk("nfsd: SYMLINK  %s %.*s -> %.*s\n",
		SVCFH_fmt(&argp->ffh), argp->flen, argp->fname,
		argp->tlen, argp->tname);

	fh_init(&newfh, NFS_FHSIZE);
	resp->status = nfsd_symlink(rqstp, &argp->ffh, argp->fname, argp->flen,
				    argp->tname, &newfh);

	kमुक्त(argp->tname);
	fh_put(&argp->ffh);
	fh_put(&newfh);
out:
	वापस rpc_success;
पूर्ण

/*
 * Make directory. This operation is not idempotent.
 * N.B. After this call resp->fh needs an fh_put
 */
अटल __be32
nfsd_proc_सूची_गढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_createargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_diropres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: MKDIR    %s %.*s\n", SVCFH_fmt(&argp->fh), argp->len, argp->name);

	अगर (resp->fh.fh_dentry) अणु
		prपूर्णांकk(KERN_WARNING
			"nfsd_proc_mkdir: response already verified??\n");
	पूर्ण

	argp->attrs.ia_valid &= ~ATTR_SIZE;
	fh_init(&resp->fh, NFS_FHSIZE);
	resp->status = nfsd_create(rqstp, &argp->fh, argp->name, argp->len,
				   &argp->attrs, S_IFसूची, 0, &resp->fh);
	fh_put(&argp->fh);
	अगर (resp->status != nfs_ok)
		जाओ out;

	resp->status = fh_getattr(&resp->fh, &resp->stat);
out:
	वापस rpc_success;
पूर्ण

/*
 * Remove a directory
 */
अटल __be32
nfsd_proc_सूची_हटाओ(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_diropargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_stat *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: RMDIR    %s %.*s\n", SVCFH_fmt(&argp->fh), argp->len, argp->name);

	resp->status = nfsd_unlink(rqstp, &argp->fh, S_IFसूची,
				   argp->name, argp->len);
	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

अटल व्योम nfsd_init_dirlist_pages(काष्ठा svc_rqst *rqstp,
				    काष्ठा nfsd_सूची_पढ़ोres *resp,
				    पूर्णांक count)
अणु
	काष्ठा xdr_buf *buf = &resp->dirlist;
	काष्ठा xdr_stream *xdr = &resp->xdr;

	count = min_t(u32, count, PAGE_SIZE);

	स_रखो(buf, 0, माप(*buf));

	/* Reserve room क्रम the शून्य ptr & eof flag (-2 words) */
	buf->buflen = count - माप(__be32) * 2;
	buf->pages = rqstp->rq_next_page;
	rqstp->rq_next_page++;

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
nfsd_proc_सूची_पढ़ो(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_सूची_पढ़ोargs *argp = rqstp->rq_argp;
	काष्ठा nfsd_सूची_पढ़ोres *resp = rqstp->rq_resp;
	loff_t		offset;

	dprपूर्णांकk("nfsd: READDIR  %s %d bytes at %d\n",
		SVCFH_fmt(&argp->fh),		
		argp->count, argp->cookie);

	nfsd_init_dirlist_pages(rqstp, resp, argp->count);

	resp->common.err = nfs_ok;
	resp->cookie_offset = 0;
	offset = argp->cookie;
	resp->status = nfsd_सूची_पढ़ो(rqstp, &argp->fh, &offset,
				    &resp->common, nfssvc_encode_entry);
	nfssvc_encode_nfscookie(resp, offset);

	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

/*
 * Get file प्रणाली info
 */
अटल __be32
nfsd_proc_statfs(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_fhandle *argp = rqstp->rq_argp;
	काष्ठा nfsd_statfsres *resp = rqstp->rq_resp;

	dprपूर्णांकk("nfsd: STATFS   %s\n", SVCFH_fmt(&argp->fh));

	resp->status = nfsd_statfs(rqstp, &argp->fh, &resp->stats,
				   NFSD_MAY_BYPASS_GSS_ON_ROOT);
	fh_put(&argp->fh);
	वापस rpc_success;
पूर्ण

/*
 * NFSv2 Server procedures.
 * Only the results of non-idempotent operations are cached.
 */

#घोषणा ST 1		/* status */
#घोषणा FH 8		/* filehandle */
#घोषणा	AT 18		/* attributes */

अटल स्थिर काष्ठा svc_procedure nfsd_procedures2[18] = अणु
	[NFSPROC_शून्य] = अणु
		.pc_func = nfsd_proc_null,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = 0,
		.pc_name = "NULL",
	पूर्ण,
	[NFSPROC_GETATTR] = अणु
		.pc_func = nfsd_proc_getattr,
		.pc_decode = nfssvc_decode_fhandleargs,
		.pc_encode = nfssvc_encode_attrstatres,
		.pc_release = nfssvc_release_attrstat,
		.pc_argsize = माप(काष्ठा nfsd_fhandle),
		.pc_ressize = माप(काष्ठा nfsd_attrstat),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+AT,
		.pc_name = "GETATTR",
	पूर्ण,
	[NFSPROC_SETATTR] = अणु
		.pc_func = nfsd_proc_setattr,
		.pc_decode = nfssvc_decode_sattrargs,
		.pc_encode = nfssvc_encode_attrstatres,
		.pc_release = nfssvc_release_attrstat,
		.pc_argsize = माप(काष्ठा nfsd_sattrargs),
		.pc_ressize = माप(काष्ठा nfsd_attrstat),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+AT,
		.pc_name = "SETATTR",
	पूर्ण,
	[NFSPROC_ROOT] = अणु
		.pc_func = nfsd_proc_root,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = 0,
		.pc_name = "ROOT",
	पूर्ण,
	[NFSPROC_LOOKUP] = अणु
		.pc_func = nfsd_proc_lookup,
		.pc_decode = nfssvc_decode_diropargs,
		.pc_encode = nfssvc_encode_diropres,
		.pc_release = nfssvc_release_diropres,
		.pc_argsize = माप(काष्ठा nfsd_diropargs),
		.pc_ressize = माप(काष्ठा nfsd_diropres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+FH+AT,
		.pc_name = "LOOKUP",
	पूर्ण,
	[NFSPROC_READLINK] = अणु
		.pc_func = nfsd_proc_पढ़ोlink,
		.pc_decode = nfssvc_decode_fhandleargs,
		.pc_encode = nfssvc_encode_पढ़ोlinkres,
		.pc_argsize = माप(काष्ठा nfsd_fhandle),
		.pc_ressize = माप(काष्ठा nfsd_पढ़ोlinkres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+1+NFS_MAXPATHLEN/4,
		.pc_name = "READLINK",
	पूर्ण,
	[NFSPROC_READ] = अणु
		.pc_func = nfsd_proc_पढ़ो,
		.pc_decode = nfssvc_decode_पढ़ोargs,
		.pc_encode = nfssvc_encode_पढ़ोres,
		.pc_release = nfssvc_release_पढ़ोres,
		.pc_argsize = माप(काष्ठा nfsd_पढ़ोargs),
		.pc_ressize = माप(काष्ठा nfsd_पढ़ोres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+AT+1+NFSSVC_MAXBLKSIZE_V2/4,
		.pc_name = "READ",
	पूर्ण,
	[NFSPROC_WRITECACHE] = अणु
		.pc_func = nfsd_proc_ग_लिखोcache,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = 0,
		.pc_name = "WRITECACHE",
	पूर्ण,
	[NFSPROC_WRITE] = अणु
		.pc_func = nfsd_proc_ग_लिखो,
		.pc_decode = nfssvc_decode_ग_लिखोargs,
		.pc_encode = nfssvc_encode_attrstatres,
		.pc_release = nfssvc_release_attrstat,
		.pc_argsize = माप(काष्ठा nfsd_ग_लिखोargs),
		.pc_ressize = माप(काष्ठा nfsd_attrstat),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+AT,
		.pc_name = "WRITE",
	पूर्ण,
	[NFSPROC_CREATE] = अणु
		.pc_func = nfsd_proc_create,
		.pc_decode = nfssvc_decode_createargs,
		.pc_encode = nfssvc_encode_diropres,
		.pc_release = nfssvc_release_diropres,
		.pc_argsize = माप(काष्ठा nfsd_createargs),
		.pc_ressize = माप(काष्ठा nfsd_diropres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+FH+AT,
		.pc_name = "CREATE",
	पूर्ण,
	[NFSPROC_REMOVE] = अणु
		.pc_func = nfsd_proc_हटाओ,
		.pc_decode = nfssvc_decode_diropargs,
		.pc_encode = nfssvc_encode_statres,
		.pc_argsize = माप(काष्ठा nfsd_diropargs),
		.pc_ressize = माप(काष्ठा nfsd_stat),
		.pc_cachetype = RC_REPLSTAT,
		.pc_xdrressize = ST,
		.pc_name = "REMOVE",
	पूर्ण,
	[NFSPROC_RENAME] = अणु
		.pc_func = nfsd_proc_नाम,
		.pc_decode = nfssvc_decode_नामargs,
		.pc_encode = nfssvc_encode_statres,
		.pc_argsize = माप(काष्ठा nfsd_नामargs),
		.pc_ressize = माप(काष्ठा nfsd_stat),
		.pc_cachetype = RC_REPLSTAT,
		.pc_xdrressize = ST,
		.pc_name = "RENAME",
	पूर्ण,
	[NFSPROC_LINK] = अणु
		.pc_func = nfsd_proc_link,
		.pc_decode = nfssvc_decode_linkargs,
		.pc_encode = nfssvc_encode_statres,
		.pc_argsize = माप(काष्ठा nfsd_linkargs),
		.pc_ressize = माप(काष्ठा nfsd_stat),
		.pc_cachetype = RC_REPLSTAT,
		.pc_xdrressize = ST,
		.pc_name = "LINK",
	पूर्ण,
	[NFSPROC_SYMLINK] = अणु
		.pc_func = nfsd_proc_symlink,
		.pc_decode = nfssvc_decode_symlinkargs,
		.pc_encode = nfssvc_encode_statres,
		.pc_argsize = माप(काष्ठा nfsd_symlinkargs),
		.pc_ressize = माप(काष्ठा nfsd_stat),
		.pc_cachetype = RC_REPLSTAT,
		.pc_xdrressize = ST,
		.pc_name = "SYMLINK",
	पूर्ण,
	[NFSPROC_MKसूची] = अणु
		.pc_func = nfsd_proc_सूची_गढ़ो,
		.pc_decode = nfssvc_decode_createargs,
		.pc_encode = nfssvc_encode_diropres,
		.pc_release = nfssvc_release_diropres,
		.pc_argsize = माप(काष्ठा nfsd_createargs),
		.pc_ressize = माप(काष्ठा nfsd_diropres),
		.pc_cachetype = RC_REPLBUFF,
		.pc_xdrressize = ST+FH+AT,
		.pc_name = "MKDIR",
	पूर्ण,
	[NFSPROC_RMसूची] = अणु
		.pc_func = nfsd_proc_सूची_हटाओ,
		.pc_decode = nfssvc_decode_diropargs,
		.pc_encode = nfssvc_encode_statres,
		.pc_argsize = माप(काष्ठा nfsd_diropargs),
		.pc_ressize = माप(काष्ठा nfsd_stat),
		.pc_cachetype = RC_REPLSTAT,
		.pc_xdrressize = ST,
		.pc_name = "RMDIR",
	पूर्ण,
	[NFSPROC_READसूची] = अणु
		.pc_func = nfsd_proc_सूची_पढ़ो,
		.pc_decode = nfssvc_decode_सूची_पढ़ोargs,
		.pc_encode = nfssvc_encode_सूची_पढ़ोres,
		.pc_argsize = माप(काष्ठा nfsd_सूची_पढ़ोargs),
		.pc_ressize = माप(काष्ठा nfsd_सूची_पढ़ोres),
		.pc_cachetype = RC_NOCACHE,
		.pc_name = "READDIR",
	पूर्ण,
	[NFSPROC_STATFS] = अणु
		.pc_func = nfsd_proc_statfs,
		.pc_decode = nfssvc_decode_fhandleargs,
		.pc_encode = nfssvc_encode_statfsres,
		.pc_argsize = माप(काष्ठा nfsd_fhandle),
		.pc_ressize = माप(काष्ठा nfsd_statfsres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = ST+5,
		.pc_name = "STATFS",
	पूर्ण,
पूर्ण;


अटल अचिन्हित पूर्णांक nfsd_count2[ARRAY_SIZE(nfsd_procedures2)];
स्थिर काष्ठा svc_version nfsd_version2 = अणु
	.vs_vers	= 2,
	.vs_nproc	= 18,
	.vs_proc	= nfsd_procedures2,
	.vs_count	= nfsd_count2,
	.vs_dispatch	= nfsd_dispatch,
	.vs_xdrsize	= NFS2_SVC_XDRSIZE,
पूर्ण;

/*
 * Map त्रुटि_संs to NFS त्रुटि_संs.
 */
__be32
nfsत्रुटि_सं (पूर्णांक त्रुटि_सं)
अणु
	अटल काष्ठा अणु
		__be32	nfserr;
		पूर्णांक	syserr;
	पूर्ण nfs_errtbl[] = अणु
		अणु nfs_ok, 0 पूर्ण,
		अणु nfserr_perm, -EPERM पूर्ण,
		अणु nfserr_noent, -ENOENT पूर्ण,
		अणु nfserr_io, -EIO पूर्ण,
		अणु nfserr_nxio, -ENXIO पूर्ण,
		अणु nfserr_fbig, -E2BIG पूर्ण,
		अणु nfserr_acces, -EACCES पूर्ण,
		अणु nfserr_exist, -EEXIST पूर्ण,
		अणु nfserr_xdev, -EXDEV पूर्ण,
		अणु nfserr_mlink, -EMLINK पूर्ण,
		अणु nfserr_nodev, -ENODEV पूर्ण,
		अणु nfserr_notdir, -ENOTसूची पूर्ण,
		अणु nfserr_isdir, -EISसूची पूर्ण,
		अणु nfserr_inval, -EINVAL पूर्ण,
		अणु nfserr_fbig, -EFBIG पूर्ण,
		अणु nfserr_nospc, -ENOSPC पूर्ण,
		अणु nfserr_rofs, -EROFS पूर्ण,
		अणु nfserr_mlink, -EMLINK पूर्ण,
		अणु nfserr_nametooदीर्घ, -ENAMETOOLONG पूर्ण,
		अणु nfserr_notempty, -ENOTEMPTY पूर्ण,
#अगर_घोषित EDQUOT
		अणु nfserr_dquot, -EDQUOT पूर्ण,
#पूर्ण_अगर
		अणु nfserr_stale, -ESTALE पूर्ण,
		अणु nfserr_jukebox, -ETIMEDOUT पूर्ण,
		अणु nfserr_jukebox, -ERESTARTSYS पूर्ण,
		अणु nfserr_jukebox, -EAGAIN पूर्ण,
		अणु nfserr_jukebox, -EWOULDBLOCK पूर्ण,
		अणु nfserr_jukebox, -ENOMEM पूर्ण,
		अणु nfserr_io, -ETXTBSY पूर्ण,
		अणु nfserr_notsupp, -EOPNOTSUPP पूर्ण,
		अणु nfserr_toosmall, -ETOOSMALL पूर्ण,
		अणु nfserr_serverfault, -ESERVERFAULT पूर्ण,
		अणु nfserr_serverfault, -ENखाता पूर्ण,
		अणु nfserr_io, -EUCLEAN पूर्ण,
		अणु nfserr_perm, -ENOKEY पूर्ण,
	पूर्ण;
	पूर्णांक	i;

	क्रम (i = 0; i < ARRAY_SIZE(nfs_errtbl); i++) अणु
		अगर (nfs_errtbl[i].syserr == त्रुटि_सं)
			वापस nfs_errtbl[i].nfserr;
	पूर्ण
	WARN_ONCE(1, "nfsd: non-standard errno: %d\n", त्रुटि_सं);
	वापस nfserr_io;
पूर्ण

