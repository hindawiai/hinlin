<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * File operations used by nfsd. Some of these have been ripped from
 * other parts of the kernel because they weren't exported, others
 * are partial duplicates with added or changed functionality.
 *
 * Note that several functions dget() the dentry upon which they want
 * to act, most notably those that create directory entries. Response
 * dentry's are dput()'d अगर necessary in the release callback.
 * So अगर you notice code paths that apparently fail to dput() the
 * dentry, करोn't worry--they have been taken care of.
 *
 * Copyright (C) 1995-1999 Olaf Kirch <okir@monad.swb.de>
 * Zerocpy NFS support (C) 2002 Hirokazu Takahashi <taka@valinux.co.jp>
 */

#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/splice.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/namei.h>
#समावेश <linux/delay.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/xattr.h>
#समावेश <linux/jhash.h>
#समावेश <linux/ima.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/security.h>

#अगर_घोषित CONFIG_NFSD_V3
#समावेश "xdr3.h"
#पूर्ण_अगर /* CONFIG_NFSD_V3 */

#अगर_घोषित CONFIG_NFSD_V4
#समावेश "../internal.h"
#समावेश "acl.h"
#समावेश "idmap.h"
#पूर्ण_अगर /* CONFIG_NFSD_V4 */

#समावेश "nfsd.h"
#समावेश "vfs.h"
#समावेश "filecache.h"
#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY		NFSDDBG_खाताOP

/* 
 * Called from nfsd_lookup and encode_dirent. Check अगर we have crossed 
 * a mount poपूर्णांक.
 * Returns -EAGAIN or -ETIMEDOUT leaving *dpp and *expp unchanged,
 *  or nfs_ok having possibly changed *dpp and *expp
 */
पूर्णांक
nfsd_cross_mnt(काष्ठा svc_rqst *rqstp, काष्ठा dentry **dpp, 
		        काष्ठा svc_export **expp)
अणु
	काष्ठा svc_export *exp = *expp, *exp2 = शून्य;
	काष्ठा dentry *dentry = *dpp;
	काष्ठा path path = अणु.mnt = mntget(exp->ex_path.mnt),
			    .dentry = dget(dentry)पूर्ण;
	पूर्णांक err = 0;

	err = follow_करोwn(&path);
	अगर (err < 0)
		जाओ out;
	अगर (path.mnt == exp->ex_path.mnt && path.dentry == dentry &&
	    nfsd_mountpoपूर्णांक(dentry, exp) == 2) अणु
		/* This is only a mountpoपूर्णांक in some other namespace */
		path_put(&path);
		जाओ out;
	पूर्ण

	exp2 = rqst_exp_get_by_name(rqstp, &path);
	अगर (IS_ERR(exp2)) अणु
		err = PTR_ERR(exp2);
		/*
		 * We normally allow NFS clients to जारी
		 * "underneath" a mountpoपूर्णांक that is not exported.
		 * The exception is V4ROOT, where no traversal is ever
		 * allowed without an explicit export of the new
		 * directory.
		 */
		अगर (err == -ENOENT && !(exp->ex_flags & NFSEXP_V4ROOT))
			err = 0;
		path_put(&path);
		जाओ out;
	पूर्ण
	अगर (nfsd_v4client(rqstp) ||
		(exp->ex_flags & NFSEXP_CROSSMOUNT) || EX_NOHIDE(exp2)) अणु
		/* successfully crossed mount poपूर्णांक */
		/*
		 * This is subtle: path.dentry is *not* on path.mnt
		 * at this poपूर्णांक.  The only reason we are safe is that
		 * original mnt is pinned करोwn by exp, so we should
		 * put path *beक्रमe* putting exp
		 */
		*dpp = path.dentry;
		path.dentry = dentry;
		*expp = exp2;
		exp2 = exp;
	पूर्ण
	path_put(&path);
	exp_put(exp2);
out:
	वापस err;
पूर्ण

अटल व्योम follow_to_parent(काष्ठा path *path)
अणु
	काष्ठा dentry *dp;

	जबतक (path->dentry == path->mnt->mnt_root && follow_up(path))
		;
	dp = dget_parent(path->dentry);
	dput(path->dentry);
	path->dentry = dp;
पूर्ण

अटल पूर्णांक nfsd_lookup_parent(काष्ठा svc_rqst *rqstp, काष्ठा dentry *dparent, काष्ठा svc_export **exp, काष्ठा dentry **dentryp)
अणु
	काष्ठा svc_export *exp2;
	काष्ठा path path = अणु.mnt = mntget((*exp)->ex_path.mnt),
			    .dentry = dget(dparent)पूर्ण;

	follow_to_parent(&path);

	exp2 = rqst_exp_parent(rqstp, &path);
	अगर (PTR_ERR(exp2) == -ENOENT) अणु
		*dentryp = dget(dparent);
	पूर्ण अन्यथा अगर (IS_ERR(exp2)) अणु
		path_put(&path);
		वापस PTR_ERR(exp2);
	पूर्ण अन्यथा अणु
		*dentryp = dget(path.dentry);
		exp_put(*exp);
		*exp = exp2;
	पूर्ण
	path_put(&path);
	वापस 0;
पूर्ण

/*
 * For nfsd purposes, we treat V4ROOT exports as though there was an
 * export at *every* directory.
 * We वापस:
 * '1' अगर this dentry *must* be an export poपूर्णांक,
 * '2' अगर it might be, अगर there is really a mount here, and
 * '0' अगर there is no chance of an export poपूर्णांक here.
 */
पूर्णांक nfsd_mountpoपूर्णांक(काष्ठा dentry *dentry, काष्ठा svc_export *exp)
अणु
	अगर (!d_inode(dentry))
		वापस 0;
	अगर (exp->ex_flags & NFSEXP_V4ROOT)
		वापस 1;
	अगर (nfsd4_is_junction(dentry))
		वापस 1;
	अगर (d_mountpoपूर्णांक(dentry))
		/*
		 * Might only be a mountpoपूर्णांक in a dअगरferent namespace,
		 * but we need to check.
		 */
		वापस 2;
	वापस 0;
पूर्ण

__be32
nfsd_lookup_dentry(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		   स्थिर अक्षर *name, अचिन्हित पूर्णांक len,
		   काष्ठा svc_export **exp_ret, काष्ठा dentry **dentry_ret)
अणु
	काष्ठा svc_export	*exp;
	काष्ठा dentry		*dparent;
	काष्ठा dentry		*dentry;
	पूर्णांक			host_err;

	dprपूर्णांकk("nfsd: nfsd_lookup(fh %s, %.*s)\n", SVCFH_fmt(fhp), len,name);

	dparent = fhp->fh_dentry;
	exp = exp_get(fhp->fh_export);

	/* Lookup the name, but करोn't follow links */
	अगर (isकरोtent(name, len)) अणु
		अगर (len==1)
			dentry = dget(dparent);
		अन्यथा अगर (dparent != exp->ex_path.dentry)
			dentry = dget_parent(dparent);
		अन्यथा अगर (!EX_NOHIDE(exp) && !nfsd_v4client(rqstp))
			dentry = dget(dparent); /* .. == . just like at / */
		अन्यथा अणु
			/* checking mountpoपूर्णांक crossing is very dअगरferent when stepping up */
			host_err = nfsd_lookup_parent(rqstp, dparent, &exp, &dentry);
			अगर (host_err)
				जाओ out_nfserr;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * In the nfsd4_खोलो() हाल, this may be held across
		 * subsequent खोलो and delegation acquisition which may
		 * need to take the child's i_mutex:
		 */
		fh_lock_nested(fhp, I_MUTEX_PARENT);
		dentry = lookup_one_len(name, dparent, len);
		host_err = PTR_ERR(dentry);
		अगर (IS_ERR(dentry))
			जाओ out_nfserr;
		अगर (nfsd_mountpoपूर्णांक(dentry, exp)) अणु
			/*
			 * We करोn't need the i_mutex after all.  It's
			 * still possible we could खोलो this (regular
			 * files can be mountpoपूर्णांकs too), but the
			 * i_mutex is just there to prevent नामs of
			 * something that we might be about to delegate,
			 * and a mountpoपूर्णांक won't be नामd:
			 */
			fh_unlock(fhp);
			अगर ((host_err = nfsd_cross_mnt(rqstp, &dentry, &exp))) अणु
				dput(dentry);
				जाओ out_nfserr;
			पूर्ण
		पूर्ण
	पूर्ण
	*dentry_ret = dentry;
	*exp_ret = exp;
	वापस 0;

out_nfserr:
	exp_put(exp);
	वापस nfsत्रुटि_सं(host_err);
पूर्ण

/*
 * Look up one component of a pathname.
 * N.B. After this call _both_ fhp and resfh need an fh_put
 *
 * If the lookup would cross a mountpoपूर्णांक, and the mounted fileप्रणाली
 * is exported to the client with NFSEXP_NOHIDE, then the lookup is
 * accepted as it stands and the mounted directory is
 * वापसed. Otherwise the covered directory is वापसed.
 * NOTE: this mountpoपूर्णांक crossing is not supported properly by all
 *   clients and is explicitly disallowed क्रम NFSv3
 *      NeilBrown <neilb@cse.unsw.edu.au>
 */
__be32
nfsd_lookup(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, स्थिर अक्षर *name,
				अचिन्हित पूर्णांक len, काष्ठा svc_fh *resfh)
अणु
	काष्ठा svc_export	*exp;
	काष्ठा dentry		*dentry;
	__be32 err;

	err = fh_verअगरy(rqstp, fhp, S_IFसूची, NFSD_MAY_EXEC);
	अगर (err)
		वापस err;
	err = nfsd_lookup_dentry(rqstp, fhp, name, len, &exp, &dentry);
	अगर (err)
		वापस err;
	err = check_nfsd_access(exp, rqstp);
	अगर (err)
		जाओ out;
	/*
	 * Note: we compose the file handle now, but as the
	 * dentry may be negative, it may need to be updated.
	 */
	err = fh_compose(resfh, exp, dentry, fhp);
	अगर (!err && d_really_is_negative(dentry))
		err = nfserr_noent;
out:
	dput(dentry);
	exp_put(exp);
	वापस err;
पूर्ण

/*
 * Commit metadata changes to stable storage.
 */
अटल पूर्णांक
commit_inode_metadata(काष्ठा inode *inode)
अणु
	स्थिर काष्ठा export_operations *export_ops = inode->i_sb->s_export_op;

	अगर (export_ops->commit_metadata)
		वापस export_ops->commit_metadata(inode);
	वापस sync_inode_metadata(inode, 1);
पूर्ण

अटल पूर्णांक
commit_metadata(काष्ठा svc_fh *fhp)
अणु
	काष्ठा inode *inode = d_inode(fhp->fh_dentry);

	अगर (!EX_ISSYNC(fhp->fh_export))
		वापस 0;
	वापस commit_inode_metadata(inode);
पूर्ण

/*
 * Go over the attributes and take care of the small dअगरferences between
 * NFS semantics and what Linux expects.
 */
अटल व्योम
nfsd_sanitize_attrs(काष्ठा inode *inode, काष्ठा iattr *iap)
अणु
	/* sanitize the mode change */
	अगर (iap->ia_valid & ATTR_MODE) अणु
		iap->ia_mode &= S_IALLUGO;
		iap->ia_mode |= (inode->i_mode & ~S_IALLUGO);
	पूर्ण

	/* Revoke setuid/setgid on chown */
	अगर (!S_ISसूची(inode->i_mode) &&
	    ((iap->ia_valid & ATTR_UID) || (iap->ia_valid & ATTR_GID))) अणु
		iap->ia_valid |= ATTR_KILL_PRIV;
		अगर (iap->ia_valid & ATTR_MODE) अणु
			/* we're setting mode too, just clear the s*id bits */
			iap->ia_mode &= ~S_ISUID;
			अगर (iap->ia_mode & S_IXGRP)
				iap->ia_mode &= ~S_ISGID;
		पूर्ण अन्यथा अणु
			/* set ATTR_KILL_* bits and let VFS handle it */
			iap->ia_valid |= (ATTR_KILL_SUID | ATTR_KILL_SGID);
		पूर्ण
	पूर्ण
पूर्ण

अटल __be32
nfsd_get_ग_लिखो_access(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		काष्ठा iattr *iap)
अणु
	काष्ठा inode *inode = d_inode(fhp->fh_dentry);
	पूर्णांक host_err;

	अगर (iap->ia_size < inode->i_size) अणु
		__be32 err;

		err = nfsd_permission(rqstp, fhp->fh_export, fhp->fh_dentry,
				NFSD_MAY_TRUNC | NFSD_MAY_OWNER_OVERRIDE);
		अगर (err)
			वापस err;
	पूर्ण

	host_err = get_ग_लिखो_access(inode);
	अगर (host_err)
		जाओ out_nfsत्रुटि_सं;

	host_err = locks_verअगरy_truncate(inode, शून्य, iap->ia_size);
	अगर (host_err)
		जाओ out_put_ग_लिखो_access;
	वापस 0;

out_put_ग_लिखो_access:
	put_ग_लिखो_access(inode);
out_nfsत्रुटि_सं:
	वापस nfsत्रुटि_सं(host_err);
पूर्ण

/*
 * Set various file attributes.  After this call fhp needs an fh_put.
 */
__be32
nfsd_setattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, काष्ठा iattr *iap,
	     पूर्णांक check_guard, समय64_t guardसमय)
अणु
	काष्ठा dentry	*dentry;
	काष्ठा inode	*inode;
	पूर्णांक		accmode = NFSD_MAY_SATTR;
	umode_t		ftype = 0;
	__be32		err;
	पूर्णांक		host_err;
	bool		get_ग_लिखो_count;
	bool		size_change = (iap->ia_valid & ATTR_SIZE);

	अगर (iap->ia_valid & ATTR_SIZE) अणु
		accmode |= NFSD_MAY_WRITE|NFSD_MAY_OWNER_OVERRIDE;
		ftype = S_IFREG;
	पूर्ण

	/*
	 * If uबार(2) and मित्रs are called with बार not शून्य, we should
	 * not set NFSD_MAY_WRITE bit. Otherwise fh_verअगरy->nfsd_permission
	 * will वापस EACCES, when the caller's effective UID करोes not match
	 * the owner of the file, and the caller is not privileged. In this
	 * situation, we should वापस EPERM(notअगरy_change will वापस this).
	 */
	अगर (iap->ia_valid & (ATTR_ATIME | ATTR_MTIME)) अणु
		accmode |= NFSD_MAY_OWNER_OVERRIDE;
		अगर (!(iap->ia_valid & (ATTR_ATIME_SET | ATTR_MTIME_SET)))
			accmode |= NFSD_MAY_WRITE;
	पूर्ण

	/* Callers that करो fh_verअगरy should करो the fh_want_ग_लिखो: */
	get_ग_लिखो_count = !fhp->fh_dentry;

	/* Get inode */
	err = fh_verअगरy(rqstp, fhp, ftype, accmode);
	अगर (err)
		वापस err;
	अगर (get_ग_लिखो_count) अणु
		host_err = fh_want_ग_लिखो(fhp);
		अगर (host_err)
			जाओ out;
	पूर्ण

	dentry = fhp->fh_dentry;
	inode = d_inode(dentry);

	/* Ignore any mode updates on symlinks */
	अगर (S_ISLNK(inode->i_mode))
		iap->ia_valid &= ~ATTR_MODE;

	अगर (!iap->ia_valid)
		वापस 0;

	nfsd_sanitize_attrs(inode, iap);

	अगर (check_guard && guardसमय != inode->i_स_समय.tv_sec)
		वापस nfserr_notsync;

	/*
	 * The size हाल is special, it changes the file in addition to the
	 * attributes, and file प्रणालीs करोn't expect it to be mixed with
	 * "random" attribute changes.  We thus split out the size change
	 * पूर्णांकo a separate call to ->setattr, and करो the rest as a separate
	 * setattr call.
	 */
	अगर (size_change) अणु
		err = nfsd_get_ग_लिखो_access(rqstp, fhp, iap);
		अगर (err)
			वापस err;
	पूर्ण

	fh_lock(fhp);
	अगर (size_change) अणु
		/*
		 * RFC5661, Section 18.30.4:
		 *   Changing the size of a file with SETATTR indirectly
		 *   changes the समय_modअगरy and change attributes.
		 *
		 * (and similar क्रम the older RFCs)
		 */
		काष्ठा iattr size_attr = अणु
			.ia_valid	= ATTR_SIZE | ATTR_CTIME | ATTR_MTIME,
			.ia_size	= iap->ia_size,
		पूर्ण;

		host_err = notअगरy_change(&init_user_ns, dentry, &size_attr, शून्य);
		अगर (host_err)
			जाओ out_unlock;
		iap->ia_valid &= ~ATTR_SIZE;

		/*
		 * Aव्योम the additional setattr call below अगर the only other
		 * attribute that the client sends is the mसमय, as we update
		 * it as part of the size change above.
		 */
		अगर ((iap->ia_valid & ~ATTR_MTIME) == 0)
			जाओ out_unlock;
	पूर्ण

	iap->ia_valid |= ATTR_CTIME;
	host_err = notअगरy_change(&init_user_ns, dentry, iap, शून्य);

out_unlock:
	fh_unlock(fhp);
	अगर (size_change)
		put_ग_लिखो_access(inode);
out:
	अगर (!host_err)
		host_err = commit_metadata(fhp);
	वापस nfsत्रुटि_सं(host_err);
पूर्ण

#अगर defined(CONFIG_NFSD_V4)
/*
 * NFS junction inक्रमmation is stored in an extended attribute.
 */
#घोषणा NFSD_JUNCTION_XATTR_NAME	XATTR_TRUSTED_PREFIX "junction.nfs"

/**
 * nfsd4_is_junction - Test अगर an object could be an NFS junction
 *
 * @dentry: object to test
 *
 * Returns 1 अगर "dentry" appears to contain NFS junction inक्रमmation.
 * Otherwise 0 is वापसed.
 */
पूर्णांक nfsd4_is_junction(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (inode == शून्य)
		वापस 0;
	अगर (inode->i_mode & S_IXUGO)
		वापस 0;
	अगर (!(inode->i_mode & S_ISVTX))
		वापस 0;
	अगर (vfs_getxattr(&init_user_ns, dentry, NFSD_JUNCTION_XATTR_NAME,
			 शून्य, 0) <= 0)
		वापस 0;
	वापस 1;
पूर्ण
#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
__be32 nfsd4_set_nfs4_label(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		काष्ठा xdr_netobj *label)
अणु
	__be32 error;
	पूर्णांक host_error;
	काष्ठा dentry *dentry;

	error = fh_verअगरy(rqstp, fhp, 0 /* S_IFREG */, NFSD_MAY_SATTR);
	अगर (error)
		वापस error;

	dentry = fhp->fh_dentry;

	inode_lock(d_inode(dentry));
	host_error = security_inode_setsecctx(dentry, label->data, label->len);
	inode_unlock(d_inode(dentry));
	वापस nfsत्रुटि_सं(host_error);
पूर्ण
#अन्यथा
__be32 nfsd4_set_nfs4_label(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		काष्ठा xdr_netobj *label)
अणु
	वापस nfserr_notsupp;
पूर्ण
#पूर्ण_अगर

__be32 nfsd4_clone_file_range(काष्ठा nfsd_file *nf_src, u64 src_pos,
		काष्ठा nfsd_file *nf_dst, u64 dst_pos, u64 count, bool sync)
अणु
	काष्ठा file *src = nf_src->nf_file;
	काष्ठा file *dst = nf_dst->nf_file;
	loff_t cloned;
	__be32 ret = 0;

	करोwn_ग_लिखो(&nf_dst->nf_rwsem);
	cloned = vfs_clone_file_range(src, src_pos, dst, dst_pos, count, 0);
	अगर (cloned < 0) अणु
		ret = nfsत्रुटि_सं(cloned);
		जाओ out_err;
	पूर्ण
	अगर (count && cloned != count) अणु
		ret = nfsत्रुटि_सं(-EINVAL);
		जाओ out_err;
	पूर्ण
	अगर (sync) अणु
		loff_t dst_end = count ? dst_pos + count - 1 : Lदीर्घ_उच्च;
		पूर्णांक status = vfs_fsync_range(dst, dst_pos, dst_end, 0);

		अगर (!status)
			status = commit_inode_metadata(file_inode(src));
		अगर (status < 0) अणु
			nfsd_reset_boot_verअगरier(net_generic(nf_dst->nf_net,
						 nfsd_net_id));
			ret = nfsत्रुटि_सं(status);
		पूर्ण
	पूर्ण
out_err:
	up_ग_लिखो(&nf_dst->nf_rwsem);
	वापस ret;
पूर्ण

sमाप_प्रकार nfsd_copy_file_range(काष्ठा file *src, u64 src_pos, काष्ठा file *dst,
			     u64 dst_pos, u64 count)
अणु

	/*
	 * Limit copy to 4MB to prevent indefinitely blocking an nfsd
	 * thपढ़ो and client rpc slot.  The choice of 4MB is somewhat
	 * arbitrary.  We might instead base this on r/wsize, or make it
	 * tunable, or use a समय instead of a byte limit, or implement
	 * asynchronous copy.  In theory a client could also recognize a
	 * limit like this and pipeline multiple COPY requests.
	 */
	count = min_t(u64, count, 1 << 22);
	वापस vfs_copy_file_range(src, src_pos, dst, dst_pos, count, 0);
पूर्ण

__be32 nfsd4_vfs_fallocate(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			   काष्ठा file *file, loff_t offset, loff_t len,
			   पूर्णांक flags)
अणु
	पूर्णांक error;

	अगर (!S_ISREG(file_inode(file)->i_mode))
		वापस nfserr_inval;

	error = vfs_fallocate(file, flags, offset, len);
	अगर (!error)
		error = commit_metadata(fhp);

	वापस nfsत्रुटि_सं(error);
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_NFSD_V4) */

#अगर_घोषित CONFIG_NFSD_V3
/*
 * Check server access rights to a file प्रणाली object
 */
काष्ठा accessmap अणु
	u32		access;
	पूर्णांक		how;
पूर्ण;
अटल काष्ठा accessmap	nfs3_regaccess[] = अणु
    अणु	NFS3_ACCESS_READ,	NFSD_MAY_READ			पूर्ण,
    अणु	NFS3_ACCESS_EXECUTE,	NFSD_MAY_EXEC			पूर्ण,
    अणु	NFS3_ACCESS_MODIFY,	NFSD_MAY_WRITE|NFSD_MAY_TRUNC	पूर्ण,
    अणु	NFS3_ACCESS_EXTEND,	NFSD_MAY_WRITE			पूर्ण,

#अगर_घोषित CONFIG_NFSD_V4
    अणु	NFS4_ACCESS_XAREAD,	NFSD_MAY_READ			पूर्ण,
    अणु	NFS4_ACCESS_XAWRITE,	NFSD_MAY_WRITE			पूर्ण,
    अणु	NFS4_ACCESS_XALIST,	NFSD_MAY_READ			पूर्ण,
#पूर्ण_अगर

    अणु	0,			0				पूर्ण
पूर्ण;

अटल काष्ठा accessmap	nfs3_diraccess[] = अणु
    अणु	NFS3_ACCESS_READ,	NFSD_MAY_READ			पूर्ण,
    अणु	NFS3_ACCESS_LOOKUP,	NFSD_MAY_EXEC			पूर्ण,
    अणु	NFS3_ACCESS_MODIFY,	NFSD_MAY_EXEC|NFSD_MAY_WRITE|NFSD_MAY_TRUNCपूर्ण,
    अणु	NFS3_ACCESS_EXTEND,	NFSD_MAY_EXEC|NFSD_MAY_WRITE	पूर्ण,
    अणु	NFS3_ACCESS_DELETE,	NFSD_MAY_REMOVE			पूर्ण,

#अगर_घोषित CONFIG_NFSD_V4
    अणु	NFS4_ACCESS_XAREAD,	NFSD_MAY_READ			पूर्ण,
    अणु	NFS4_ACCESS_XAWRITE,	NFSD_MAY_WRITE			पूर्ण,
    अणु	NFS4_ACCESS_XALIST,	NFSD_MAY_READ			पूर्ण,
#पूर्ण_अगर

    अणु	0,			0				पूर्ण
पूर्ण;

अटल काष्ठा accessmap	nfs3_anyaccess[] = अणु
	/* Some clients - Solaris 2.6 at least, make an access call
	 * to the server to check क्रम access क्रम things like /dev/null
	 * (which really, the server करोesn't care about).  So
	 * We provide simple access checking क्रम them, looking
	 * मुख्यly at mode bits, and we make sure to ignore पढ़ो-only
	 * fileप्रणाली checks
	 */
    अणु	NFS3_ACCESS_READ,	NFSD_MAY_READ			पूर्ण,
    अणु	NFS3_ACCESS_EXECUTE,	NFSD_MAY_EXEC			पूर्ण,
    अणु	NFS3_ACCESS_MODIFY,	NFSD_MAY_WRITE|NFSD_MAY_LOCAL_ACCESS	पूर्ण,
    अणु	NFS3_ACCESS_EXTEND,	NFSD_MAY_WRITE|NFSD_MAY_LOCAL_ACCESS	पूर्ण,

    अणु	0,			0				पूर्ण
पूर्ण;

__be32
nfsd_access(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, u32 *access, u32 *supported)
अणु
	काष्ठा accessmap	*map;
	काष्ठा svc_export	*export;
	काष्ठा dentry		*dentry;
	u32			query, result = 0, sresult = 0;
	__be32			error;

	error = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_NOP);
	अगर (error)
		जाओ out;

	export = fhp->fh_export;
	dentry = fhp->fh_dentry;

	अगर (d_is_reg(dentry))
		map = nfs3_regaccess;
	अन्यथा अगर (d_is_dir(dentry))
		map = nfs3_diraccess;
	अन्यथा
		map = nfs3_anyaccess;


	query = *access;
	क्रम  (; map->access; map++) अणु
		अगर (map->access & query) अणु
			__be32 err2;

			sresult |= map->access;

			err2 = nfsd_permission(rqstp, export, dentry, map->how);
			चयन (err2) अणु
			हाल nfs_ok:
				result |= map->access;
				अवरोध;
				
			/* the following error codes just mean the access was not allowed,
			 * rather than an error occurred */
			हाल nfserr_rofs:
			हाल nfserr_acces:
			हाल nfserr_perm:
				/* simply करोn't "or" in the access bit. */
				अवरोध;
			शेष:
				error = err2;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	*access = result;
	अगर (supported)
		*supported = sresult;

 out:
	वापस error;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_V3 */

पूर्णांक nfsd_खोलो_अवरोध_lease(काष्ठा inode *inode, पूर्णांक access)
अणु
	अचिन्हित पूर्णांक mode;

	अगर (access & NFSD_MAY_NOT_BREAK_LEASE)
		वापस 0;
	mode = (access & NFSD_MAY_WRITE) ? O_WRONLY : O_RDONLY;
	वापस अवरोध_lease(inode, mode | O_NONBLOCK);
पूर्ण

/*
 * Open an existing file or directory.
 * The may_flags argument indicates the type of खोलो (पढ़ो/ग_लिखो/lock)
 * and additional flags.
 * N.B. After this call fhp needs an fh_put
 */
अटल __be32
__nfsd_खोलो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, umode_t type,
			पूर्णांक may_flags, काष्ठा file **filp)
अणु
	काष्ठा path	path;
	काष्ठा inode	*inode;
	काष्ठा file	*file;
	पूर्णांक		flags = O_RDONLY|O_LARGEखाता;
	__be32		err;
	पूर्णांक		host_err = 0;

	path.mnt = fhp->fh_export->ex_path.mnt;
	path.dentry = fhp->fh_dentry;
	inode = d_inode(path.dentry);

	/* Disallow ग_लिखो access to files with the append-only bit set
	 * or any access when mandatory locking enabled
	 */
	err = nfserr_perm;
	अगर (IS_APPEND(inode) && (may_flags & NFSD_MAY_WRITE))
		जाओ out;
	/*
	 * We must ignore files (but only files) which might have mandatory
	 * locks on them because there is no way to know अगर the accesser has
	 * the lock.
	 */
	अगर (S_ISREG((inode)->i_mode) && mandatory_lock(inode))
		जाओ out;

	अगर (!inode->i_fop)
		जाओ out;

	host_err = nfsd_खोलो_अवरोध_lease(inode, may_flags);
	अगर (host_err) /* NOMEM or WOULDBLOCK */
		जाओ out_nfserr;

	अगर (may_flags & NFSD_MAY_WRITE) अणु
		अगर (may_flags & NFSD_MAY_READ)
			flags = O_RDWR|O_LARGEखाता;
		अन्यथा
			flags = O_WRONLY|O_LARGEखाता;
	पूर्ण

	file = dentry_खोलो(&path, flags, current_cred());
	अगर (IS_ERR(file)) अणु
		host_err = PTR_ERR(file);
		जाओ out_nfserr;
	पूर्ण

	host_err = ima_file_check(file, may_flags);
	अगर (host_err) अणु
		fput(file);
		जाओ out_nfserr;
	पूर्ण

	अगर (may_flags & NFSD_MAY_64BIT_COOKIE)
		file->f_mode |= FMODE_64BITHASH;
	अन्यथा
		file->f_mode |= FMODE_32BITHASH;

	*filp = file;
out_nfserr:
	err = nfsत्रुटि_सं(host_err);
out:
	वापस err;
पूर्ण

__be32
nfsd_खोलो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, umode_t type,
		पूर्णांक may_flags, काष्ठा file **filp)
अणु
	__be32 err;

	validate_process_creds();
	/*
	 * If we get here, then the client has alपढ़ोy करोne an "open",
	 * and (hopefully) checked permission - so allow OWNER_OVERRIDE
	 * in हाल a chmod has now revoked permission.
	 *
	 * Arguably we should also allow the owner override क्रम
	 * directories, but we never have and it करोesn't seem to have
	 * caused anyone a problem.  If we were to change this, note
	 * also that our filldir callbacks would need a variant of
	 * lookup_one_len that करोesn't check permissions.
	 */
	अगर (type == S_IFREG)
		may_flags |= NFSD_MAY_OWNER_OVERRIDE;
	err = fh_verअगरy(rqstp, fhp, type, may_flags);
	अगर (!err)
		err = __nfsd_खोलो(rqstp, fhp, type, may_flags, filp);
	validate_process_creds();
	वापस err;
पूर्ण

__be32
nfsd_खोलो_verअगरied(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, umode_t type,
		पूर्णांक may_flags, काष्ठा file **filp)
अणु
	__be32 err;

	validate_process_creds();
	err = __nfsd_खोलो(rqstp, fhp, type, may_flags, filp);
	validate_process_creds();
	वापस err;
पूर्ण

/*
 * Grab and keep cached pages associated with a file in the svc_rqst
 * so that they can be passed to the network sendmsg/sendpage routines
 * directly. They will be released after the sending has completed.
 */
अटल पूर्णांक
nfsd_splice_actor(काष्ठा pipe_inode_info *pipe, काष्ठा pipe_buffer *buf,
		  काष्ठा splice_desc *sd)
अणु
	काष्ठा svc_rqst *rqstp = sd->u.data;
	काष्ठा page **pp = rqstp->rq_next_page;
	काष्ठा page *page = buf->page;
	माप_प्रकार size;

	size = sd->len;

	अगर (rqstp->rq_res.page_len == 0) अणु
		get_page(page);
		put_page(*rqstp->rq_next_page);
		*(rqstp->rq_next_page++) = page;
		rqstp->rq_res.page_base = buf->offset;
		rqstp->rq_res.page_len = size;
	पूर्ण अन्यथा अगर (page != pp[-1]) अणु
		get_page(page);
		अगर (*rqstp->rq_next_page)
			put_page(*rqstp->rq_next_page);
		*(rqstp->rq_next_page++) = page;
		rqstp->rq_res.page_len += size;
	पूर्ण अन्यथा
		rqstp->rq_res.page_len += size;

	वापस size;
पूर्ण

अटल पूर्णांक nfsd_direct_splice_actor(काष्ठा pipe_inode_info *pipe,
				    काष्ठा splice_desc *sd)
अणु
	वापस __splice_from_pipe(pipe, sd, nfsd_splice_actor);
पूर्ण

अटल u32 nfsd_eof_on_पढ़ो(काष्ठा file *file, loff_t offset, sमाप_प्रकार len,
		माप_प्रकार expected)
अणु
	अगर (expected != 0 && len == 0)
		वापस 1;
	अगर (offset+len >= i_size_पढ़ो(file_inode(file)))
		वापस 1;
	वापस 0;
पूर्ण

अटल __be32 nfsd_finish_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			       काष्ठा file *file, loff_t offset,
			       अचिन्हित दीर्घ *count, u32 *eof, sमाप_प्रकार host_err)
अणु
	अगर (host_err >= 0) अणु
		nfsd_stats_io_पढ़ो_add(fhp->fh_export, host_err);
		*eof = nfsd_eof_on_पढ़ो(file, offset, host_err, *count);
		*count = host_err;
		fsnotअगरy_access(file);
		trace_nfsd_पढ़ो_io_करोne(rqstp, fhp, offset, *count);
		वापस 0;
	पूर्ण अन्यथा अणु
		trace_nfsd_पढ़ो_err(rqstp, fhp, offset, host_err);
		वापस nfsत्रुटि_सं(host_err);
	पूर्ण
पूर्ण

__be32 nfsd_splice_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			काष्ठा file *file, loff_t offset, अचिन्हित दीर्घ *count,
			u32 *eof)
अणु
	काष्ठा splice_desc sd = अणु
		.len		= 0,
		.total_len	= *count,
		.pos		= offset,
		.u.data		= rqstp,
	पूर्ण;
	sमाप_प्रकार host_err;

	trace_nfsd_पढ़ो_splice(rqstp, fhp, offset, *count);
	rqstp->rq_next_page = rqstp->rq_respages + 1;
	host_err = splice_direct_to_actor(file, &sd, nfsd_direct_splice_actor);
	वापस nfsd_finish_पढ़ो(rqstp, fhp, file, offset, count, eof, host_err);
पूर्ण

__be32 nfsd_पढ़ोv(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		  काष्ठा file *file, loff_t offset,
		  काष्ठा kvec *vec, पूर्णांक vlen, अचिन्हित दीर्घ *count,
		  u32 *eof)
अणु
	काष्ठा iov_iter iter;
	loff_t ppos = offset;
	sमाप_प्रकार host_err;

	trace_nfsd_पढ़ो_vector(rqstp, fhp, offset, *count);
	iov_iter_kvec(&iter, READ, vec, vlen, *count);
	host_err = vfs_iter_पढ़ो(file, &iter, &ppos, 0);
	वापस nfsd_finish_पढ़ो(rqstp, fhp, file, offset, count, eof, host_err);
पूर्ण

/*
 * Gathered ग_लिखोs: If another process is currently writing to the file,
 * there's a high chance this is another nfsd (triggered by a bulk ग_लिखो
 * from a client's biod). Rather than syncing the file with each ग_लिखो
 * request, we sleep क्रम 10 msec.
 *
 * I करोn't know if this roughly approximates C. Juszak's idea of
 * gathered ग_लिखोs, but it's a nice and simple solution (IMHO), and it
 * seems to work:-)
 *
 * Note: we करो this only in the NFSv2 हाल, since v3 and higher have a
 * better tool (separate unstable ग_लिखोs and commits) क्रम solving this
 * problem.
 */
अटल पूर्णांक रुको_क्रम_concurrent_ग_लिखोs(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	अटल ino_t last_ino;
	अटल dev_t last_dev;
	पूर्णांक err = 0;

	अगर (atomic_पढ़ो(&inode->i_ग_लिखोcount) > 1
	    || (last_ino == inode->i_ino && last_dev == inode->i_sb->s_dev)) अणु
		dprपूर्णांकk("nfsd: write defer %d\n", task_pid_nr(current));
		msleep(10);
		dprपूर्णांकk("nfsd: write resume %d\n", task_pid_nr(current));
	पूर्ण

	अगर (inode->i_state & I_सूचीTY) अणु
		dprपूर्णांकk("nfsd: write sync %d\n", task_pid_nr(current));
		err = vfs_fsync(file, 0);
	पूर्ण
	last_ino = inode->i_ino;
	last_dev = inode->i_sb->s_dev;
	वापस err;
पूर्ण

__be32
nfsd_vfs_ग_लिखो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, काष्ठा nfsd_file *nf,
				loff_t offset, काष्ठा kvec *vec, पूर्णांक vlen,
				अचिन्हित दीर्घ *cnt, पूर्णांक stable,
				__be32 *verf)
अणु
	काष्ठा file		*file = nf->nf_file;
	काष्ठा super_block	*sb = file_inode(file)->i_sb;
	काष्ठा svc_export	*exp;
	काष्ठा iov_iter		iter;
	__be32			nfserr;
	पूर्णांक			host_err;
	पूर्णांक			use_wgather;
	loff_t			pos = offset;
	अचिन्हित दीर्घ		exp_op_flags = 0;
	अचिन्हित पूर्णांक		pflags = current->flags;
	rwf_t			flags = 0;
	bool			restore_flags = false;

	trace_nfsd_ग_लिखो_खोलोed(rqstp, fhp, offset, *cnt);

	अगर (sb->s_export_op)
		exp_op_flags = sb->s_export_op->flags;

	अगर (test_bit(RQ_LOCAL, &rqstp->rq_flags) &&
	    !(exp_op_flags & EXPORT_OP_REMOTE_FS)) अणु
		/*
		 * We want throttling in balance_dirty_pages()
		 * and shrink_inactive_list() to only consider
		 * the backingdev we are writing to, so that nfs to
		 * localhost करोesn't cause nfsd to lock up due to all
		 * the client's dirty pages or its congested queue.
		 */
		current->flags |= PF_LOCAL_THROTTLE;
		restore_flags = true;
	पूर्ण

	exp = fhp->fh_export;
	use_wgather = (rqstp->rq_vers == 2) && EX_WGATHER(exp);

	अगर (!EX_ISSYNC(exp))
		stable = NFS_UNSTABLE;

	अगर (stable && !use_wgather)
		flags |= RWF_SYNC;

	iov_iter_kvec(&iter, WRITE, vec, vlen, *cnt);
	अगर (flags & RWF_SYNC) अणु
		करोwn_ग_लिखो(&nf->nf_rwsem);
		host_err = vfs_iter_ग_लिखो(file, &iter, &pos, flags);
		अगर (host_err < 0)
			nfsd_reset_boot_verअगरier(net_generic(SVC_NET(rqstp),
						 nfsd_net_id));
		up_ग_लिखो(&nf->nf_rwsem);
	पूर्ण अन्यथा अणु
		करोwn_पढ़ो(&nf->nf_rwsem);
		अगर (verf)
			nfsd_copy_boot_verअगरier(verf,
					net_generic(SVC_NET(rqstp),
					nfsd_net_id));
		host_err = vfs_iter_ग_लिखो(file, &iter, &pos, flags);
		up_पढ़ो(&nf->nf_rwsem);
	पूर्ण
	अगर (host_err < 0) अणु
		nfsd_reset_boot_verअगरier(net_generic(SVC_NET(rqstp),
					 nfsd_net_id));
		जाओ out_nfserr;
	पूर्ण
	*cnt = host_err;
	nfsd_stats_io_ग_लिखो_add(exp, *cnt);
	fsnotअगरy_modअगरy(file);

	अगर (stable && use_wgather) अणु
		host_err = रुको_क्रम_concurrent_ग_लिखोs(file);
		अगर (host_err < 0)
			nfsd_reset_boot_verअगरier(net_generic(SVC_NET(rqstp),
						 nfsd_net_id));
	पूर्ण

out_nfserr:
	अगर (host_err >= 0) अणु
		trace_nfsd_ग_लिखो_io_करोne(rqstp, fhp, offset, *cnt);
		nfserr = nfs_ok;
	पूर्ण अन्यथा अणु
		trace_nfsd_ग_लिखो_err(rqstp, fhp, offset, host_err);
		nfserr = nfsत्रुटि_सं(host_err);
	पूर्ण
	अगर (restore_flags)
		current_restore_flags(pflags, PF_LOCAL_THROTTLE);
	वापस nfserr;
पूर्ण

/*
 * Read data from a file. count must contain the requested पढ़ो count
 * on entry. On वापस, *count contains the number of bytes actually पढ़ो.
 * N.B. After this call fhp needs an fh_put
 */
__be32 nfsd_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
	loff_t offset, काष्ठा kvec *vec, पूर्णांक vlen, अचिन्हित दीर्घ *count,
	u32 *eof)
अणु
	काष्ठा nfsd_file	*nf;
	काष्ठा file *file;
	__be32 err;

	trace_nfsd_पढ़ो_start(rqstp, fhp, offset, *count);
	err = nfsd_file_acquire(rqstp, fhp, NFSD_MAY_READ, &nf);
	अगर (err)
		वापस err;

	file = nf->nf_file;
	अगर (file->f_op->splice_पढ़ो && test_bit(RQ_SPLICE_OK, &rqstp->rq_flags))
		err = nfsd_splice_पढ़ो(rqstp, fhp, file, offset, count, eof);
	अन्यथा
		err = nfsd_पढ़ोv(rqstp, fhp, file, offset, vec, vlen, count, eof);

	nfsd_file_put(nf);

	trace_nfsd_पढ़ो_करोne(rqstp, fhp, offset, *count);

	वापस err;
पूर्ण

/*
 * Write data to a file.
 * The stable flag requests synchronous ग_लिखोs.
 * N.B. After this call fhp needs an fh_put
 */
__be32
nfsd_ग_लिखो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, loff_t offset,
	   काष्ठा kvec *vec, पूर्णांक vlen, अचिन्हित दीर्घ *cnt, पूर्णांक stable,
	   __be32 *verf)
अणु
	काष्ठा nfsd_file *nf;
	__be32 err;

	trace_nfsd_ग_लिखो_start(rqstp, fhp, offset, *cnt);

	err = nfsd_file_acquire(rqstp, fhp, NFSD_MAY_WRITE, &nf);
	अगर (err)
		जाओ out;

	err = nfsd_vfs_ग_लिखो(rqstp, fhp, nf, offset, vec,
			vlen, cnt, stable, verf);
	nfsd_file_put(nf);
out:
	trace_nfsd_ग_लिखो_करोne(rqstp, fhp, offset, *cnt);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NFSD_V3
/*
 * Commit all pending ग_लिखोs to stable storage.
 *
 * Note: we only guarantee that data that lies within the range specअगरied
 * by the 'offset' and 'count' parameters will be synced.
 *
 * Unक्रमtunately we cannot lock the file to make sure we वापस full WCC
 * data to the client, as locking happens lower करोwn in the fileप्रणाली.
 */
__be32
nfsd_commit(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
               loff_t offset, अचिन्हित दीर्घ count, __be32 *verf)
अणु
	काष्ठा nfsd_file	*nf;
	loff_t			end = Lदीर्घ_उच्च;
	__be32			err = nfserr_inval;

	अगर (offset < 0)
		जाओ out;
	अगर (count != 0) अणु
		end = offset + (loff_t)count - 1;
		अगर (end < offset)
			जाओ out;
	पूर्ण

	err = nfsd_file_acquire(rqstp, fhp,
			NFSD_MAY_WRITE|NFSD_MAY_NOT_BREAK_LEASE, &nf);
	अगर (err)
		जाओ out;
	अगर (EX_ISSYNC(fhp->fh_export)) अणु
		पूर्णांक err2;

		करोwn_ग_लिखो(&nf->nf_rwsem);
		err2 = vfs_fsync_range(nf->nf_file, offset, end, 0);
		चयन (err2) अणु
		हाल 0:
			nfsd_copy_boot_verअगरier(verf, net_generic(nf->nf_net,
						nfsd_net_id));
			अवरोध;
		हाल -EINVAL:
			err = nfserr_notsupp;
			अवरोध;
		शेष:
			err = nfsत्रुटि_सं(err2);
			nfsd_reset_boot_verअगरier(net_generic(nf->nf_net,
						 nfsd_net_id));
		पूर्ण
		up_ग_लिखो(&nf->nf_rwsem);
	पूर्ण अन्यथा
		nfsd_copy_boot_verअगरier(verf, net_generic(nf->nf_net,
					nfsd_net_id));

	nfsd_file_put(nf);
out:
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_V3 */

अटल __be32
nfsd_create_setattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *resfhp,
			काष्ठा iattr *iap)
अणु
	/*
	 * Mode has alपढ़ोy been set earlier in create:
	 */
	iap->ia_valid &= ~ATTR_MODE;
	/*
	 * Setting uid/gid works only क्रम root.  Irix appears to
	 * send aदीर्घ the gid on create when it tries to implement
	 * setgid directories via NFS:
	 */
	अगर (!uid_eq(current_fsuid(), GLOBAL_ROOT_UID))
		iap->ia_valid &= ~(ATTR_UID|ATTR_GID);
	अगर (iap->ia_valid)
		वापस nfsd_setattr(rqstp, resfhp, iap, 0, (समय64_t)0);
	/* Callers expect file metadata to be committed here */
	वापस nfsत्रुटि_सं(commit_metadata(resfhp));
पूर्ण

/* HPUX client someबार creates a file in mode 000, and sets size to 0.
 * setting size to 0 may fail क्रम some specअगरic file प्रणालीs by the permission
 * checking which requires WRITE permission but the mode is 000.
 * we ignore the resizing(to 0) on the just new created file, since the size is
 * 0 after file created.
 *
 * call this only after vfs_create() is called.
 * */
अटल व्योम
nfsd_check_ignore_resizing(काष्ठा iattr *iap)
अणु
	अगर ((iap->ia_valid & ATTR_SIZE) && (iap->ia_size == 0))
		iap->ia_valid &= ~ATTR_SIZE;
पूर्ण

/* The parent directory should alपढ़ोy be locked: */
__be32
nfsd_create_locked(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		अक्षर *fname, पूर्णांक flen, काष्ठा iattr *iap,
		पूर्णांक type, dev_t rdev, काष्ठा svc_fh *resfhp)
अणु
	काष्ठा dentry	*dentry, *dchild;
	काष्ठा inode	*dirp;
	__be32		err;
	__be32		err2;
	पूर्णांक		host_err;

	dentry = fhp->fh_dentry;
	dirp = d_inode(dentry);

	dchild = dget(resfhp->fh_dentry);
	अगर (!fhp->fh_locked) अणु
		WARN_ONCE(1, "nfsd_create: parent %pd2 not locked!\n",
				dentry);
		err = nfserr_io;
		जाओ out;
	पूर्ण

	err = nfsd_permission(rqstp, fhp->fh_export, dentry, NFSD_MAY_CREATE);
	अगर (err)
		जाओ out;

	अगर (!(iap->ia_valid & ATTR_MODE))
		iap->ia_mode = 0;
	iap->ia_mode = (iap->ia_mode & S_IALLUGO) | type;

	अगर (!IS_POSIXACL(dirp))
		iap->ia_mode &= ~current_umask();

	err = 0;
	host_err = 0;
	चयन (type) अणु
	हाल S_IFREG:
		host_err = vfs_create(&init_user_ns, dirp, dchild, iap->ia_mode, true);
		अगर (!host_err)
			nfsd_check_ignore_resizing(iap);
		अवरोध;
	हाल S_IFसूची:
		host_err = vfs_सूची_गढ़ो(&init_user_ns, dirp, dchild, iap->ia_mode);
		अगर (!host_err && unlikely(d_unhashed(dchild))) अणु
			काष्ठा dentry *d;
			d = lookup_one_len(dchild->d_name.name,
					   dchild->d_parent,
					   dchild->d_name.len);
			अगर (IS_ERR(d)) अणु
				host_err = PTR_ERR(d);
				अवरोध;
			पूर्ण
			अगर (unlikely(d_is_negative(d))) अणु
				dput(d);
				err = nfserr_serverfault;
				जाओ out;
			पूर्ण
			dput(resfhp->fh_dentry);
			resfhp->fh_dentry = dget(d);
			err = fh_update(resfhp);
			dput(dchild);
			dchild = d;
			अगर (err)
				जाओ out;
		पूर्ण
		अवरोध;
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFIFO:
	हाल S_IFSOCK:
		host_err = vfs_mknod(&init_user_ns, dirp, dchild,
				     iap->ia_mode, rdev);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "nfsd: bad file type %o in nfsd_create\n",
		       type);
		host_err = -EINVAL;
	पूर्ण
	अगर (host_err < 0)
		जाओ out_nfserr;

	err = nfsd_create_setattr(rqstp, resfhp, iap);

	/*
	 * nfsd_create_setattr alपढ़ोy committed the child.  Transactional
	 * fileप्रणालीs had a chance to commit changes क्रम both parent and
	 * child simultaneously making the following commit_metadata a
	 * noop.
	 */
	err2 = nfsत्रुटि_सं(commit_metadata(fhp));
	अगर (err2)
		err = err2;
	/*
	 * Update the file handle to get the new inode info.
	 */
	अगर (!err)
		err = fh_update(resfhp);
out:
	dput(dchild);
	वापस err;

out_nfserr:
	err = nfsत्रुटि_सं(host_err);
	जाओ out;
पूर्ण

/*
 * Create a fileप्रणाली object (regular, directory, special).
 * Note that the parent directory is left locked.
 *
 * N.B. Every call to nfsd_create needs an fh_put क्रम _both_ fhp and resfhp
 */
__be32
nfsd_create(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		अक्षर *fname, पूर्णांक flen, काष्ठा iattr *iap,
		पूर्णांक type, dev_t rdev, काष्ठा svc_fh *resfhp)
अणु
	काष्ठा dentry	*dentry, *dchild = शून्य;
	__be32		err;
	पूर्णांक		host_err;

	अगर (isकरोtent(fname, flen))
		वापस nfserr_exist;

	err = fh_verअगरy(rqstp, fhp, S_IFसूची, NFSD_MAY_NOP);
	अगर (err)
		वापस err;

	dentry = fhp->fh_dentry;

	host_err = fh_want_ग_लिखो(fhp);
	अगर (host_err)
		वापस nfsत्रुटि_सं(host_err);

	fh_lock_nested(fhp, I_MUTEX_PARENT);
	dchild = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(dchild);
	अगर (IS_ERR(dchild))
		वापस nfsत्रुटि_सं(host_err);
	err = fh_compose(resfhp, fhp->fh_export, dchild, fhp);
	/*
	 * We unconditionally drop our ref to dchild as fh_compose will have
	 * alपढ़ोy grabbed its own ref क्रम it.
	 */
	dput(dchild);
	अगर (err)
		वापस err;
	वापस nfsd_create_locked(rqstp, fhp, fname, flen, iap, type,
					rdev, resfhp);
पूर्ण

#अगर_घोषित CONFIG_NFSD_V3

/*
 * NFSv3 and NFSv4 version of nfsd_create
 */
__be32
करो_nfsd_create(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		अक्षर *fname, पूर्णांक flen, काष्ठा iattr *iap,
		काष्ठा svc_fh *resfhp, पूर्णांक createmode, u32 *verअगरier,
	        bool *truncp, bool *created)
अणु
	काष्ठा dentry	*dentry, *dchild = शून्य;
	काष्ठा inode	*dirp;
	__be32		err;
	पूर्णांक		host_err;
	__u32		v_mसमय=0, v_aसमय=0;

	err = nfserr_perm;
	अगर (!flen)
		जाओ out;
	err = nfserr_exist;
	अगर (isकरोtent(fname, flen))
		जाओ out;
	अगर (!(iap->ia_valid & ATTR_MODE))
		iap->ia_mode = 0;
	err = fh_verअगरy(rqstp, fhp, S_IFसूची, NFSD_MAY_EXEC);
	अगर (err)
		जाओ out;

	dentry = fhp->fh_dentry;
	dirp = d_inode(dentry);

	host_err = fh_want_ग_लिखो(fhp);
	अगर (host_err)
		जाओ out_nfserr;

	fh_lock_nested(fhp, I_MUTEX_PARENT);

	/*
	 * Compose the response file handle.
	 */
	dchild = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(dchild);
	अगर (IS_ERR(dchild))
		जाओ out_nfserr;

	/* If file करोesn't exist, check क्रम permissions to create one */
	अगर (d_really_is_negative(dchild)) अणु
		err = fh_verअगरy(rqstp, fhp, S_IFसूची, NFSD_MAY_CREATE);
		अगर (err)
			जाओ out;
	पूर्ण

	err = fh_compose(resfhp, fhp->fh_export, dchild, fhp);
	अगर (err)
		जाओ out;

	अगर (nfsd_create_is_exclusive(createmode)) अणु
		/* solaris7 माला_लो confused (bugid 4218508) अगर these have
		 * the high bit set, so just clear the high bits. If this is
		 * ever changed to use dअगरferent attrs क्रम storing the
		 * verअगरier, then करो_खोलो_lookup() will also need to be fixed
		 * accordingly.
		 */
		v_mसमय = verअगरier[0]&0x7fffffff;
		v_aसमय = verअगरier[1]&0x7fffffff;
	पूर्ण
	
	अगर (d_really_is_positive(dchild)) अणु
		err = 0;

		चयन (createmode) अणु
		हाल NFS3_CREATE_UNCHECKED:
			अगर (! d_is_reg(dchild))
				जाओ out;
			अन्यथा अगर (truncp) अणु
				/* in nfsv4, we need to treat this हाल a little
				 * dअगरferently.  we करोn't want to truncate the
				 * file now; this would be wrong अगर the OPEN
				 * fails क्रम some other reason.  furthermore,
				 * अगर the size is nonzero, we should ignore it
				 * according to spec!
				 */
				*truncp = (iap->ia_valid & ATTR_SIZE) && !iap->ia_size;
			पूर्ण
			अन्यथा अणु
				iap->ia_valid &= ATTR_SIZE;
				जाओ set_attr;
			पूर्ण
			अवरोध;
		हाल NFS3_CREATE_EXCLUSIVE:
			अगर (   d_inode(dchild)->i_mसमय.tv_sec == v_mसमय
			    && d_inode(dchild)->i_aसमय.tv_sec == v_aसमय
			    && d_inode(dchild)->i_size  == 0 ) अणु
				अगर (created)
					*created = true;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल NFS4_CREATE_EXCLUSIVE4_1:
			अगर (   d_inode(dchild)->i_mसमय.tv_sec == v_mसमय
			    && d_inode(dchild)->i_aसमय.tv_sec == v_aसमय
			    && d_inode(dchild)->i_size  == 0 ) अणु
				अगर (created)
					*created = true;
				जाओ set_attr;
			पूर्ण
			fallthrough;
		हाल NFS3_CREATE_GUARDED:
			err = nfserr_exist;
		पूर्ण
		fh_drop_ग_लिखो(fhp);
		जाओ out;
	पूर्ण

	अगर (!IS_POSIXACL(dirp))
		iap->ia_mode &= ~current_umask();

	host_err = vfs_create(&init_user_ns, dirp, dchild, iap->ia_mode, true);
	अगर (host_err < 0) अणु
		fh_drop_ग_लिखो(fhp);
		जाओ out_nfserr;
	पूर्ण
	अगर (created)
		*created = true;

	nfsd_check_ignore_resizing(iap);

	अगर (nfsd_create_is_exclusive(createmode)) अणु
		/* Cram the verअगरier पूर्णांकo aसमय/mसमय */
		iap->ia_valid = ATTR_MTIME|ATTR_ATIME
			| ATTR_MTIME_SET|ATTR_ATIME_SET;
		/* XXX someone who knows this better please fix it क्रम nsec */ 
		iap->ia_mसमय.tv_sec = v_mसमय;
		iap->ia_aसमय.tv_sec = v_aसमय;
		iap->ia_mसमय.tv_nsec = 0;
		iap->ia_aसमय.tv_nsec = 0;
	पूर्ण

 set_attr:
	err = nfsd_create_setattr(rqstp, resfhp, iap);

	/*
	 * nfsd_create_setattr alपढ़ोy committed the child
	 * (and possibly also the parent).
	 */
	अगर (!err)
		err = nfsत्रुटि_सं(commit_metadata(fhp));

	/*
	 * Update the filehandle to get the new inode info.
	 */
	अगर (!err)
		err = fh_update(resfhp);

 out:
	fh_unlock(fhp);
	अगर (dchild && !IS_ERR(dchild))
		dput(dchild);
	fh_drop_ग_लिखो(fhp);
 	वापस err;
 
 out_nfserr:
	err = nfsत्रुटि_सं(host_err);
	जाओ out;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_V3 */

/*
 * Read a symlink. On entry, *lenp must contain the maximum path length that
 * fits पूर्णांकo the buffer. On वापस, it contains the true length.
 * N.B. After this call fhp needs an fh_put
 */
__be32
nfsd_पढ़ोlink(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, अक्षर *buf, पूर्णांक *lenp)
अणु
	__be32		err;
	स्थिर अक्षर *link;
	काष्ठा path path;
	DEFINE_DELAYED_CALL(करोne);
	पूर्णांक len;

	err = fh_verअगरy(rqstp, fhp, S_IFLNK, NFSD_MAY_NOP);
	अगर (unlikely(err))
		वापस err;

	path.mnt = fhp->fh_export->ex_path.mnt;
	path.dentry = fhp->fh_dentry;

	अगर (unlikely(!d_is_symlink(path.dentry)))
		वापस nfserr_inval;

	touch_aसमय(&path);

	link = vfs_get_link(path.dentry, &करोne);
	अगर (IS_ERR(link))
		वापस nfsत्रुटि_सं(PTR_ERR(link));

	len = म_माप(link);
	अगर (len < *lenp)
		*lenp = len;
	स_नकल(buf, link, *lenp);
	करो_delayed_call(&करोne);
	वापस 0;
पूर्ण

/*
 * Create a symlink and look up its inode
 * N.B. After this call _both_ fhp and resfhp need an fh_put
 */
__be32
nfsd_symlink(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
				अक्षर *fname, पूर्णांक flen,
				अक्षर *path,
				काष्ठा svc_fh *resfhp)
अणु
	काष्ठा dentry	*dentry, *dnew;
	__be32		err, cerr;
	पूर्णांक		host_err;

	err = nfserr_noent;
	अगर (!flen || path[0] == '\0')
		जाओ out;
	err = nfserr_exist;
	अगर (isकरोtent(fname, flen))
		जाओ out;

	err = fh_verअगरy(rqstp, fhp, S_IFसूची, NFSD_MAY_CREATE);
	अगर (err)
		जाओ out;

	host_err = fh_want_ग_लिखो(fhp);
	अगर (host_err)
		जाओ out_nfserr;

	fh_lock(fhp);
	dentry = fhp->fh_dentry;
	dnew = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(dnew);
	अगर (IS_ERR(dnew))
		जाओ out_nfserr;

	host_err = vfs_symlink(&init_user_ns, d_inode(dentry), dnew, path);
	err = nfsत्रुटि_सं(host_err);
	अगर (!err)
		err = nfsत्रुटि_सं(commit_metadata(fhp));
	fh_unlock(fhp);

	fh_drop_ग_लिखो(fhp);

	cerr = fh_compose(resfhp, fhp->fh_export, dnew, fhp);
	dput(dnew);
	अगर (err==0) err = cerr;
out:
	वापस err;

out_nfserr:
	err = nfsत्रुटि_सं(host_err);
	जाओ out;
पूर्ण

/*
 * Create a hardlink
 * N.B. After this call _both_ ffhp and tfhp need an fh_put
 */
__be32
nfsd_link(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *ffhp,
				अक्षर *name, पूर्णांक len, काष्ठा svc_fh *tfhp)
अणु
	काष्ठा dentry	*ddir, *dnew, *करोld;
	काष्ठा inode	*dirp;
	__be32		err;
	पूर्णांक		host_err;

	err = fh_verअगरy(rqstp, ffhp, S_IFसूची, NFSD_MAY_CREATE);
	अगर (err)
		जाओ out;
	err = fh_verअगरy(rqstp, tfhp, 0, NFSD_MAY_NOP);
	अगर (err)
		जाओ out;
	err = nfserr_isdir;
	अगर (d_is_dir(tfhp->fh_dentry))
		जाओ out;
	err = nfserr_perm;
	अगर (!len)
		जाओ out;
	err = nfserr_exist;
	अगर (isकरोtent(name, len))
		जाओ out;

	host_err = fh_want_ग_लिखो(tfhp);
	अगर (host_err) अणु
		err = nfsत्रुटि_सं(host_err);
		जाओ out;
	पूर्ण

	fh_lock_nested(ffhp, I_MUTEX_PARENT);
	ddir = ffhp->fh_dentry;
	dirp = d_inode(ddir);

	dnew = lookup_one_len(name, ddir, len);
	host_err = PTR_ERR(dnew);
	अगर (IS_ERR(dnew))
		जाओ out_nfserr;

	करोld = tfhp->fh_dentry;

	err = nfserr_noent;
	अगर (d_really_is_negative(करोld))
		जाओ out_dput;
	host_err = vfs_link(करोld, &init_user_ns, dirp, dnew, शून्य);
	अगर (!host_err) अणु
		err = nfsत्रुटि_सं(commit_metadata(ffhp));
		अगर (!err)
			err = nfsत्रुटि_सं(commit_metadata(tfhp));
	पूर्ण अन्यथा अणु
		अगर (host_err == -EXDEV && rqstp->rq_vers == 2)
			err = nfserr_acces;
		अन्यथा
			err = nfsत्रुटि_सं(host_err);
	पूर्ण
out_dput:
	dput(dnew);
out_unlock:
	fh_unlock(ffhp);
	fh_drop_ग_लिखो(tfhp);
out:
	वापस err;

out_nfserr:
	err = nfsत्रुटि_सं(host_err);
	जाओ out_unlock;
पूर्ण

अटल व्योम
nfsd_बंद_cached_files(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर (inode && S_ISREG(inode->i_mode))
		nfsd_file_बंद_inode_sync(inode);
पूर्ण

अटल bool
nfsd_has_cached_files(काष्ठा dentry *dentry)
अणु
	bool		ret = false;
	काष्ठा inode *inode = d_inode(dentry);

	अगर (inode && S_ISREG(inode->i_mode))
		ret = nfsd_file_is_cached(inode);
	वापस ret;
पूर्ण

/*
 * Rename a file
 * N.B. After this call _both_ ffhp and tfhp need an fh_put
 */
__be32
nfsd_नाम(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *ffhp, अक्षर *fname, पूर्णांक flen,
			    काष्ठा svc_fh *tfhp, अक्षर *tname, पूर्णांक tlen)
अणु
	काष्ठा dentry	*fdentry, *tdentry, *odentry, *ndentry, *trap;
	काष्ठा inode	*fdir, *tdir;
	__be32		err;
	पूर्णांक		host_err;
	bool		बंद_cached = false;

	err = fh_verअगरy(rqstp, ffhp, S_IFसूची, NFSD_MAY_REMOVE);
	अगर (err)
		जाओ out;
	err = fh_verअगरy(rqstp, tfhp, S_IFसूची, NFSD_MAY_CREATE);
	अगर (err)
		जाओ out;

	fdentry = ffhp->fh_dentry;
	fdir = d_inode(fdentry);

	tdentry = tfhp->fh_dentry;
	tdir = d_inode(tdentry);

	err = nfserr_perm;
	अगर (!flen || isकरोtent(fname, flen) || !tlen || isकरोtent(tname, tlen))
		जाओ out;

retry:
	host_err = fh_want_ग_लिखो(ffhp);
	अगर (host_err) अणु
		err = nfsत्रुटि_सं(host_err);
		जाओ out;
	पूर्ण

	/* cannot use fh_lock as we need deadlock protective ordering
	 * so करो it by hand */
	trap = lock_नाम(tdentry, fdentry);
	ffhp->fh_locked = tfhp->fh_locked = true;
	fill_pre_wcc(ffhp);
	fill_pre_wcc(tfhp);

	odentry = lookup_one_len(fname, fdentry, flen);
	host_err = PTR_ERR(odentry);
	अगर (IS_ERR(odentry))
		जाओ out_nfserr;

	host_err = -ENOENT;
	अगर (d_really_is_negative(odentry))
		जाओ out_dput_old;
	host_err = -EINVAL;
	अगर (odentry == trap)
		जाओ out_dput_old;

	ndentry = lookup_one_len(tname, tdentry, tlen);
	host_err = PTR_ERR(ndentry);
	अगर (IS_ERR(ndentry))
		जाओ out_dput_old;
	host_err = -ENOTEMPTY;
	अगर (ndentry == trap)
		जाओ out_dput_new;

	host_err = -EXDEV;
	अगर (ffhp->fh_export->ex_path.mnt != tfhp->fh_export->ex_path.mnt)
		जाओ out_dput_new;
	अगर (ffhp->fh_export->ex_path.dentry != tfhp->fh_export->ex_path.dentry)
		जाओ out_dput_new;

	अगर ((ndentry->d_sb->s_export_op->flags & EXPORT_OP_CLOSE_BEFORE_UNLINK) &&
	    nfsd_has_cached_files(ndentry)) अणु
		बंद_cached = true;
		जाओ out_dput_old;
	पूर्ण अन्यथा अणु
		काष्ठा नामdata rd = अणु
			.old_mnt_userns	= &init_user_ns,
			.old_dir	= fdir,
			.old_dentry	= odentry,
			.new_mnt_userns	= &init_user_ns,
			.new_dir	= tdir,
			.new_dentry	= ndentry,
		पूर्ण;
		host_err = vfs_नाम(&rd);
		अगर (!host_err) अणु
			host_err = commit_metadata(tfhp);
			अगर (!host_err)
				host_err = commit_metadata(ffhp);
		पूर्ण
	पूर्ण
 out_dput_new:
	dput(ndentry);
 out_dput_old:
	dput(odentry);
 out_nfserr:
	err = nfsत्रुटि_सं(host_err);
	/*
	 * We cannot rely on fh_unlock on the two filehandles,
	 * as that would करो the wrong thing अगर the two directories
	 * were the same, so again we करो it by hand.
	 */
	अगर (!बंद_cached) अणु
		fill_post_wcc(ffhp);
		fill_post_wcc(tfhp);
	पूर्ण
	unlock_नाम(tdentry, fdentry);
	ffhp->fh_locked = tfhp->fh_locked = false;
	fh_drop_ग_लिखो(ffhp);

	/*
	 * If the target dentry has cached खोलो files, then we need to try to
	 * बंद them prior to करोing the नाम. Flushing delayed fput
	 * shouldn't be करोne with locks held however, so we delay it until this
	 * poपूर्णांक and then reattempt the whole shebang.
	 */
	अगर (बंद_cached) अणु
		बंद_cached = false;
		nfsd_बंद_cached_files(ndentry);
		dput(ndentry);
		जाओ retry;
	पूर्ण
out:
	वापस err;
पूर्ण

/*
 * Unlink a file or directory
 * N.B. After this call fhp needs an fh_put
 */
__be32
nfsd_unlink(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, पूर्णांक type,
				अक्षर *fname, पूर्णांक flen)
अणु
	काष्ठा dentry	*dentry, *rdentry;
	काष्ठा inode	*dirp;
	__be32		err;
	पूर्णांक		host_err;

	err = nfserr_acces;
	अगर (!flen || isकरोtent(fname, flen))
		जाओ out;
	err = fh_verअगरy(rqstp, fhp, S_IFसूची, NFSD_MAY_REMOVE);
	अगर (err)
		जाओ out;

	host_err = fh_want_ग_लिखो(fhp);
	अगर (host_err)
		जाओ out_nfserr;

	fh_lock_nested(fhp, I_MUTEX_PARENT);
	dentry = fhp->fh_dentry;
	dirp = d_inode(dentry);

	rdentry = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(rdentry);
	अगर (IS_ERR(rdentry))
		जाओ out_drop_ग_लिखो;

	अगर (d_really_is_negative(rdentry)) अणु
		dput(rdentry);
		host_err = -ENOENT;
		जाओ out_drop_ग_लिखो;
	पूर्ण

	अगर (!type)
		type = d_inode(rdentry)->i_mode & S_IFMT;

	अगर (type != S_IFसूची) अणु
		अगर (rdentry->d_sb->s_export_op->flags & EXPORT_OP_CLOSE_BEFORE_UNLINK)
			nfsd_बंद_cached_files(rdentry);
		host_err = vfs_unlink(&init_user_ns, dirp, rdentry, शून्य);
	पूर्ण अन्यथा अणु
		host_err = vfs_सूची_हटाओ(&init_user_ns, dirp, rdentry);
	पूर्ण

	अगर (!host_err)
		host_err = commit_metadata(fhp);
	dput(rdentry);

out_drop_ग_लिखो:
	fh_drop_ग_लिखो(fhp);
out_nfserr:
	अगर (host_err == -EBUSY) अणु
		/* name is mounted-on. There is no perfect
		 * error status.
		 */
		अगर (nfsd_v4client(rqstp))
			err = nfserr_file_खोलो;
		अन्यथा
			err = nfserr_acces;
	पूर्ण अन्यथा अणु
		err = nfsत्रुटि_सं(host_err);
	पूर्ण
out:
	वापस err;
पूर्ण

/*
 * We करो this buffering because we must not call back पूर्णांकo the file
 * प्रणाली's ->lookup() method from the filldir callback. That may well
 * deadlock a number of file प्रणालीs.
 *
 * This is based heavily on the implementation of same in XFS.
 */
काष्ठा buffered_dirent अणु
	u64		ino;
	loff_t		offset;
	पूर्णांक		namlen;
	अचिन्हित पूर्णांक	d_type;
	अक्षर		name[];
पूर्ण;

काष्ठा सूची_पढ़ो_data अणु
	काष्ठा dir_context ctx;
	अक्षर		*dirent;
	माप_प्रकार		used;
	पूर्णांक		full;
पूर्ण;

अटल पूर्णांक nfsd_buffered_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
				 पूर्णांक namlen, loff_t offset, u64 ino,
				 अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा सूची_पढ़ो_data *buf =
		container_of(ctx, काष्ठा सूची_पढ़ो_data, ctx);
	काष्ठा buffered_dirent *de = (व्योम *)(buf->dirent + buf->used);
	अचिन्हित पूर्णांक reclen;

	reclen = ALIGN(माप(काष्ठा buffered_dirent) + namlen, माप(u64));
	अगर (buf->used + reclen > PAGE_SIZE) अणु
		buf->full = 1;
		वापस -EINVAL;
	पूर्ण

	de->namlen = namlen;
	de->offset = offset;
	de->ino = ino;
	de->d_type = d_type;
	स_नकल(de->name, name, namlen);
	buf->used += reclen;

	वापस 0;
पूर्ण

अटल __be32 nfsd_buffered_सूची_पढ़ो(काष्ठा file *file, काष्ठा svc_fh *fhp,
				    nfsd_filldir_t func, काष्ठा सूची_पढ़ो_cd *cdp,
				    loff_t *offsetp)
अणु
	काष्ठा buffered_dirent *de;
	पूर्णांक host_err;
	पूर्णांक size;
	loff_t offset;
	काष्ठा सूची_पढ़ो_data buf = अणु
		.ctx.actor = nfsd_buffered_filldir,
		.dirent = (व्योम *)__get_मुक्त_page(GFP_KERNEL)
	पूर्ण;

	अगर (!buf.dirent)
		वापस nfsत्रुटि_सं(-ENOMEM);

	offset = *offsetp;

	जबतक (1) अणु
		अचिन्हित पूर्णांक reclen;

		cdp->err = nfserr_eof; /* will be cleared on successful पढ़ो */
		buf.used = 0;
		buf.full = 0;

		host_err = iterate_dir(file, &buf.ctx);
		अगर (buf.full)
			host_err = 0;

		अगर (host_err < 0)
			अवरोध;

		size = buf.used;

		अगर (!size)
			अवरोध;

		de = (काष्ठा buffered_dirent *)buf.dirent;
		जबतक (size > 0) अणु
			offset = de->offset;

			अगर (func(cdp, de->name, de->namlen, de->offset,
				 de->ino, de->d_type))
				अवरोध;

			अगर (cdp->err != nfs_ok)
				अवरोध;

			trace_nfsd_dirent(fhp, de->ino, de->name, de->namlen);

			reclen = ALIGN(माप(*de) + de->namlen,
				       माप(u64));
			size -= reclen;
			de = (काष्ठा buffered_dirent *)((अक्षर *)de + reclen);
		पूर्ण
		अगर (size > 0) /* We bailed out early */
			अवरोध;

		offset = vfs_llseek(file, 0, प्रस्तुत_से);
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)(buf.dirent));

	अगर (host_err)
		वापस nfsत्रुटि_सं(host_err);

	*offsetp = offset;
	वापस cdp->err;
पूर्ण

/*
 * Read entries from a directory.
 * The  NFSv3/4 verअगरier we ignore क्रम now.
 */
__be32
nfsd_सूची_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, loff_t *offsetp, 
	     काष्ठा सूची_पढ़ो_cd *cdp, nfsd_filldir_t func)
अणु
	__be32		err;
	काष्ठा file	*file;
	loff_t		offset = *offsetp;
	पूर्णांक             may_flags = NFSD_MAY_READ;

	/* NFSv2 only supports 32 bit cookies */
	अगर (rqstp->rq_vers > 2)
		may_flags |= NFSD_MAY_64BIT_COOKIE;

	err = nfsd_खोलो(rqstp, fhp, S_IFसूची, may_flags, &file);
	अगर (err)
		जाओ out;

	offset = vfs_llseek(file, offset, शुरू_से);
	अगर (offset < 0) अणु
		err = nfsत्रुटि_सं((पूर्णांक)offset);
		जाओ out_बंद;
	पूर्ण

	err = nfsd_buffered_सूची_पढ़ो(file, fhp, func, cdp, offsetp);

	अगर (err == nfserr_eof || err == nfserr_toosmall)
		err = nfs_ok; /* can still be found in ->err */
out_बंद:
	fput(file);
out:
	वापस err;
पूर्ण

/*
 * Get file प्रणाली stats
 * N.B. After this call fhp needs an fh_put
 */
__be32
nfsd_statfs(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, काष्ठा kstatfs *stat, पूर्णांक access)
अणु
	__be32 err;

	err = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_NOP | access);
	अगर (!err) अणु
		काष्ठा path path = अणु
			.mnt	= fhp->fh_export->ex_path.mnt,
			.dentry	= fhp->fh_dentry,
		पूर्ण;
		अगर (vfs_statfs(&path, stat))
			err = nfserr_io;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक exp_rकरोnly(काष्ठा svc_rqst *rqstp, काष्ठा svc_export *exp)
अणु
	वापस nfsexp_flags(rqstp, exp) & NFSEXP_READONLY;
पूर्ण

#अगर_घोषित CONFIG_NFSD_V4
/*
 * Helper function to translate error numbers. In the हाल of xattr operations,
 * some error codes need to be translated outside of the standard translations.
 *
 * ENODATA needs to be translated to nfserr_noxattr.
 * E2BIG to nfserr_xattr2big.
 *
 * Additionally, vfs_listxattr can वापस -दुस्फल. This means that the
 * file has too many extended attributes to retrieve inside an
 * XATTR_LIST_MAX sized buffer. This is a bug in the xattr implementation:
 * fileप्रणालीs will allow the adding of extended attributes until they hit
 * their own पूर्णांकernal limit. This limit may be larger than XATTR_LIST_MAX.
 * So, at that poपूर्णांक, the attributes are present and valid, but can't
 * be retrieved using listxattr, since the upper level xattr code enक्रमces
 * the XATTR_LIST_MAX limit.
 *
 * This bug means that we need to deal with listxattr वापसing -दुस्फल. The
 * best mapping is to वापस TOOSMALL.
 */
अटल __be32
nfsd_xattr_त्रुटि_सं(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल -ENODATA:
		वापस nfserr_noxattr;
	हाल -E2BIG:
		वापस nfserr_xattr2big;
	हाल -दुस्फल:
		वापस nfserr_toosmall;
	पूर्ण
	वापस nfsत्रुटि_सं(err);
पूर्ण

/*
 * Retrieve the specअगरied user extended attribute. To aव्योम always
 * having to allocate the maximum size (since we are not getting
 * a maximum size from the RPC), करो a probe + alloc. Hold a पढ़ोer
 * lock on i_rwsem to prevent the extended attribute from changing
 * size जबतक we're करोing this.
 */
__be32
nfsd_getxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, अक्षर *name,
	      व्योम **bufp, पूर्णांक *lenp)
अणु
	sमाप_प्रकार len;
	__be32 err;
	अक्षर *buf;
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;

	err = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_READ);
	अगर (err)
		वापस err;

	err = nfs_ok;
	dentry = fhp->fh_dentry;
	inode = d_inode(dentry);

	inode_lock_shared(inode);

	len = vfs_getxattr(&init_user_ns, dentry, name, शून्य, 0);

	/*
	 * Zero-length attribute, just वापस.
	 */
	अगर (len == 0) अणु
		*bufp = शून्य;
		*lenp = 0;
		जाओ out;
	पूर्ण

	अगर (len < 0) अणु
		err = nfsd_xattr_त्रुटि_सं(len);
		जाओ out;
	पूर्ण

	अगर (len > *lenp) अणु
		err = nfserr_toosmall;
		जाओ out;
	पूर्ण

	buf = kvदो_स्मृति(len, GFP_KERNEL | GFP_NOFS);
	अगर (buf == शून्य) अणु
		err = nfserr_jukebox;
		जाओ out;
	पूर्ण

	len = vfs_getxattr(&init_user_ns, dentry, name, buf, len);
	अगर (len <= 0) अणु
		kvमुक्त(buf);
		buf = शून्य;
		err = nfsd_xattr_त्रुटि_सं(len);
	पूर्ण

	*lenp = len;
	*bufp = buf;

out:
	inode_unlock_shared(inode);

	वापस err;
पूर्ण

/*
 * Retrieve the xattr names. Since we can't know how many are
 * user extended attributes, we must get all attributes here,
 * and have the XDR encode filter out the "user." ones.
 *
 * While this could always just allocate an XATTR_LIST_MAX
 * buffer, that's a waste, so करो a probe + allocate. To
 * aव्योम any changes between the probe and allocate, wrap
 * this in inode_lock.
 */
__be32
nfsd_listxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, अक्षर **bufp,
	       पूर्णांक *lenp)
अणु
	sमाप_प्रकार len;
	__be32 err;
	अक्षर *buf;
	काष्ठा inode *inode;
	काष्ठा dentry *dentry;

	err = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_READ);
	अगर (err)
		वापस err;

	dentry = fhp->fh_dentry;
	inode = d_inode(dentry);
	*lenp = 0;

	inode_lock_shared(inode);

	len = vfs_listxattr(dentry, शून्य, 0);
	अगर (len <= 0) अणु
		err = nfsd_xattr_त्रुटि_सं(len);
		जाओ out;
	पूर्ण

	अगर (len > XATTR_LIST_MAX) अणु
		err = nfserr_xattr2big;
		जाओ out;
	पूर्ण

	/*
	 * We're holding i_rwsem - use GFP_NOFS.
	 */
	buf = kvदो_स्मृति(len, GFP_KERNEL | GFP_NOFS);
	अगर (buf == शून्य) अणु
		err = nfserr_jukebox;
		जाओ out;
	पूर्ण

	len = vfs_listxattr(dentry, buf, len);
	अगर (len <= 0) अणु
		kvमुक्त(buf);
		err = nfsd_xattr_त्रुटि_सं(len);
		जाओ out;
	पूर्ण

	*lenp = len;
	*bufp = buf;

	err = nfs_ok;
out:
	inode_unlock_shared(inode);

	वापस err;
पूर्ण

/*
 * Removexattr and setxattr need to call fh_lock to both lock the inode
 * and set the change attribute. Since the top-level vfs_हटाओxattr
 * and vfs_setxattr calls alपढ़ोy करो their own inode_lock calls, call
 * the _locked variant. Pass in a शून्य poपूर्णांकer क्रम delegated_inode,
 * and let the client deal with NFS4ERR_DELAY (same as with e.g.
 * setattr and हटाओ).
 */
__be32
nfsd_हटाओxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, अक्षर *name)
अणु
	__be32 err;
	पूर्णांक ret;

	err = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_WRITE);
	अगर (err)
		वापस err;

	ret = fh_want_ग_लिखो(fhp);
	अगर (ret)
		वापस nfsत्रुटि_सं(ret);

	fh_lock(fhp);

	ret = __vfs_हटाओxattr_locked(&init_user_ns, fhp->fh_dentry,
				       name, शून्य);

	fh_unlock(fhp);
	fh_drop_ग_लिखो(fhp);

	वापस nfsd_xattr_त्रुटि_सं(ret);
पूर्ण

__be32
nfsd_setxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, अक्षर *name,
	      व्योम *buf, u32 len, u32 flags)
अणु
	__be32 err;
	पूर्णांक ret;

	err = fh_verअगरy(rqstp, fhp, 0, NFSD_MAY_WRITE);
	अगर (err)
		वापस err;

	ret = fh_want_ग_लिखो(fhp);
	अगर (ret)
		वापस nfsत्रुटि_सं(ret);
	fh_lock(fhp);

	ret = __vfs_setxattr_locked(&init_user_ns, fhp->fh_dentry, name, buf,
				    len, flags, शून्य);

	fh_unlock(fhp);
	fh_drop_ग_लिखो(fhp);

	वापस nfsd_xattr_त्रुटि_सं(ret);
पूर्ण
#पूर्ण_अगर

/*
 * Check क्रम a user's access permissions to this inode.
 */
__be32
nfsd_permission(काष्ठा svc_rqst *rqstp, काष्ठा svc_export *exp,
					काष्ठा dentry *dentry, पूर्णांक acc)
अणु
	काष्ठा inode	*inode = d_inode(dentry);
	पूर्णांक		err;

	अगर ((acc & NFSD_MAY_MASK) == NFSD_MAY_NOP)
		वापस 0;
#अगर 0
	dprपूर्णांकk("nfsd: permission 0x%x%s%s%s%s%s%s%s mode 0%o%s%s%s\n",
		acc,
		(acc & NFSD_MAY_READ)?	" read"  : "",
		(acc & NFSD_MAY_WRITE)?	" write" : "",
		(acc & NFSD_MAY_EXEC)?	" exec"  : "",
		(acc & NFSD_MAY_SATTR)?	" sattr" : "",
		(acc & NFSD_MAY_TRUNC)?	" trunc" : "",
		(acc & NFSD_MAY_LOCK)?	" lock"  : "",
		(acc & NFSD_MAY_OWNER_OVERRIDE)? " owneroverride" : "",
		inode->i_mode,
		IS_IMMUTABLE(inode)?	" immut" : "",
		IS_APPEND(inode)?	" append" : "",
		__mnt_is_पढ़ोonly(exp->ex_path.mnt)?	" ro" : "");
	dprपूर्णांकk("      owner %d/%d user %d/%d\n",
		inode->i_uid, inode->i_gid, current_fsuid(), current_fsgid());
#पूर्ण_अगर

	/* Normally we reject any ग_लिखो/sattr etc access on a पढ़ो-only file
	 * प्रणाली.  But अगर it is IRIX करोing check on ग_लिखो-access क्रम a 
	 * device special file, we ignore rofs.
	 */
	अगर (!(acc & NFSD_MAY_LOCAL_ACCESS))
		अगर (acc & (NFSD_MAY_WRITE | NFSD_MAY_SATTR | NFSD_MAY_TRUNC)) अणु
			अगर (exp_rकरोnly(rqstp, exp) ||
			    __mnt_is_पढ़ोonly(exp->ex_path.mnt))
				वापस nfserr_rofs;
			अगर (/* (acc & NFSD_MAY_WRITE) && */ IS_IMMUTABLE(inode))
				वापस nfserr_perm;
		पूर्ण
	अगर ((acc & NFSD_MAY_TRUNC) && IS_APPEND(inode))
		वापस nfserr_perm;

	अगर (acc & NFSD_MAY_LOCK) अणु
		/* If we cannot rely on authentication in NLM requests,
		 * just allow locks, otherwise require पढ़ो permission, or
		 * ownership
		 */
		अगर (exp->ex_flags & NFSEXP_NOAUTHNLM)
			वापस 0;
		अन्यथा
			acc = NFSD_MAY_READ | NFSD_MAY_OWNER_OVERRIDE;
	पूर्ण
	/*
	 * The file owner always माला_लो access permission क्रम accesses that
	 * would normally be checked at खोलो समय. This is to make
	 * file access work even when the client has करोne a fchmod(fd, 0).
	 *
	 * However, `cp foo bar' should fail nevertheless when bar is
	 * पढ़ोonly. A sensible way to करो this might be to reject all
	 * attempts to truncate a पढ़ो-only file, because a creat() call
	 * always implies file truncation.
	 * ... but this isn't really fair.  A process may reasonably call
	 * ftruncate on an खोलो file descriptor on a file with perm 000.
	 * We must trust the client to करो permission checking - using "ACCESS"
	 * with NFSv3.
	 */
	अगर ((acc & NFSD_MAY_OWNER_OVERRIDE) &&
	    uid_eq(inode->i_uid, current_fsuid()))
		वापस 0;

	/* This assumes  NFSD_MAY_अणुREAD,WRITE,EXECपूर्ण == MAY_अणुREAD,WRITE,EXECपूर्ण */
	err = inode_permission(&init_user_ns, inode,
			       acc & (MAY_READ | MAY_WRITE | MAY_EXEC));

	/* Allow पढ़ो access to binaries even when mode 111 */
	अगर (err == -EACCES && S_ISREG(inode->i_mode) &&
	     (acc == (NFSD_MAY_READ | NFSD_MAY_OWNER_OVERRIDE) ||
	      acc == (NFSD_MAY_READ | NFSD_MAY_READ_IF_EXEC)))
		err = inode_permission(&init_user_ns, inode, MAY_EXEC);

	वापस err? nfsत्रुटि_सं(err) : 0;
पूर्ण
