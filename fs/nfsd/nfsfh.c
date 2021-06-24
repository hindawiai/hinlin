<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NFS server file handle treaपंचांगent.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 * Portions Copyright (C) 1999 G. Allen Morris III <gam3@acm.org>
 * Extensive reग_लिखो by Neil Brown <neilb@cse.unsw.edu.au> Southern-Spring 1999
 * ... and again Southern-Wपूर्णांकer 2001 to support export_operations
 */

#समावेश <linux/exportfs.h>

#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश "nfsd.h"
#समावेश "vfs.h"
#समावेश "auth.h"
#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY		NFSDDBG_FH


/*
 * our acceptability function.
 * अगर NOSUBTREECHECK, accept anything
 * अगर not, require that we can walk up to exp->ex_dentry
 * करोing some checks on the 'x' bits
 */
अटल पूर्णांक nfsd_acceptable(व्योम *expv, काष्ठा dentry *dentry)
अणु
	काष्ठा svc_export *exp = expv;
	पूर्णांक rv;
	काष्ठा dentry *tdentry;
	काष्ठा dentry *parent;

	अगर (exp->ex_flags & NFSEXP_NOSUBTREECHECK)
		वापस 1;

	tdentry = dget(dentry);
	जबतक (tdentry != exp->ex_path.dentry && !IS_ROOT(tdentry)) अणु
		/* make sure parents give x permission to user */
		पूर्णांक err;
		parent = dget_parent(tdentry);
		err = inode_permission(&init_user_ns,
				       d_inode(parent), MAY_EXEC);
		अगर (err < 0) अणु
			dput(parent);
			अवरोध;
		पूर्ण
		dput(tdentry);
		tdentry = parent;
	पूर्ण
	अगर (tdentry != exp->ex_path.dentry)
		dprपूर्णांकk("nfsd_acceptable failed at %p %pd\n", tdentry, tdentry);
	rv = (tdentry == exp->ex_path.dentry);
	dput(tdentry);
	वापस rv;
पूर्ण

/* Type check. The correct error वापस क्रम type mismatches करोes not seem to be
 * generally agreed upon. SunOS seems to use EISसूची अगर file isn't S_IFREG; a
 * comment in the NFSv3 spec says this is incorrect (implementation notes क्रम
 * the ग_लिखो call).
 */
अटल अंतरभूत __be32
nfsd_mode_check(काष्ठा svc_rqst *rqstp, काष्ठा dentry *dentry,
		umode_t requested)
अणु
	umode_t mode = d_inode(dentry)->i_mode & S_IFMT;

	अगर (requested == 0) /* the caller करोesn't care */
		वापस nfs_ok;
	अगर (mode == requested) अणु
		अगर (mode == S_IFसूची && !d_can_lookup(dentry)) अणु
			WARN_ON_ONCE(1);
			वापस nfserr_notdir;
		पूर्ण
		वापस nfs_ok;
	पूर्ण
	/*
	 * v4 has an error more specअगरic than err_notdir which we should
	 * वापस in preference to err_notdir:
	 */
	अगर (rqstp->rq_vers == 4 && mode == S_IFLNK)
		वापस nfserr_symlink;
	अगर (requested == S_IFसूची)
		वापस nfserr_notdir;
	अगर (mode == S_IFसूची)
		वापस nfserr_isdir;
	वापस nfserr_inval;
पूर्ण

अटल bool nfsd_originating_port_ok(काष्ठा svc_rqst *rqstp, पूर्णांक flags)
अणु
	अगर (flags & NFSEXP_INSECURE_PORT)
		वापस true;
	/* We करोn't require gss requests to use low ports: */
	अगर (rqstp->rq_cred.cr_flavor >= RPC_AUTH_GSS)
		वापस true;
	वापस test_bit(RQ_SECURE, &rqstp->rq_flags);
पूर्ण

अटल __be32 nfsd_setuser_and_check_port(काष्ठा svc_rqst *rqstp,
					  काष्ठा svc_export *exp)
अणु
	पूर्णांक flags = nfsexp_flags(rqstp, exp);

	/* Check अगर the request originated from a secure port. */
	अगर (!nfsd_originating_port_ok(rqstp, flags)) अणु
		RPC_IFDEBUG(अक्षर buf[RPC_MAX_ADDRBUFLEN]);
		dprपूर्णांकk("nfsd: request from insecure port %s!\n",
		        svc_prपूर्णांक_addr(rqstp, buf, माप(buf)));
		वापस nfserr_perm;
	पूर्ण

	/* Set user creds क्रम this exportpoपूर्णांक */
	वापस nfsत्रुटि_सं(nfsd_setuser(rqstp, exp));
पूर्ण

अटल अंतरभूत __be32 check_pseuकरो_root(काष्ठा svc_rqst *rqstp,
	काष्ठा dentry *dentry, काष्ठा svc_export *exp)
अणु
	अगर (!(exp->ex_flags & NFSEXP_V4ROOT))
		वापस nfs_ok;
	/*
	 * v2/v3 clients have no need क्रम the V4ROOT export--they use
	 * the mount protocl instead; also, further V4ROOT checks may be
	 * in v4-specअगरic code, in which हाल v2/v3 clients could bypass
	 * them.
	 */
	अगर (!nfsd_v4client(rqstp))
		वापस nfserr_stale;
	/*
	 * We're exposing only the directories and symlinks that have to be
	 * traversed on the way to real exports:
	 */
	अगर (unlikely(!d_is_dir(dentry) &&
		     !d_is_symlink(dentry)))
		वापस nfserr_stale;
	/*
	 * A pseuकरोroot export gives permission to access only one
	 * single directory; the kernel has to make another upcall
	 * beक्रमe granting access to anything अन्यथा under it:
	 */
	अगर (unlikely(dentry != exp->ex_path.dentry))
		वापस nfserr_stale;
	वापस nfs_ok;
पूर्ण

/*
 * Use the given filehandle to look up the corresponding export and
 * dentry.  On success, the results are used to set fh_export and
 * fh_dentry.
 */
अटल __be32 nfsd_set_fh_dentry(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp)
अणु
	काष्ठा knfsd_fh	*fh = &fhp->fh_handle;
	काष्ठा fid *fid = शून्य, sfid;
	काष्ठा svc_export *exp;
	काष्ठा dentry *dentry;
	पूर्णांक fileid_type;
	पूर्णांक data_left = fh->fh_size/4;
	__be32 error;

	error = nfserr_stale;
	अगर (rqstp->rq_vers > 2)
		error = nfserr_badhandle;
	अगर (rqstp->rq_vers == 4 && fh->fh_size == 0)
		वापस nfserr_nofilehandle;

	अगर (fh->fh_version == 1) अणु
		पूर्णांक len;

		अगर (--data_left < 0)
			वापस error;
		अगर (fh->fh_auth_type != 0)
			वापस error;
		len = key_len(fh->fh_fsid_type) / 4;
		अगर (len == 0)
			वापस error;
		अगर  (fh->fh_fsid_type == FSID_MAJOR_MINOR) अणु
			/* deprecated, convert to type 3 */
			len = key_len(FSID_ENCODE_DEV)/4;
			fh->fh_fsid_type = FSID_ENCODE_DEV;
			/*
			 * काष्ठा knfsd_fh uses host-endian fields, which are
			 * someबार used to hold net-endian values. This
			 * confuses sparse, so we must use __क्रमce here to
			 * keep it from complaining.
			 */
			fh->fh_fsid[0] = new_encode_dev(MKDEV(ntohl((__क्रमce __be32)fh->fh_fsid[0]),
							ntohl((__क्रमce __be32)fh->fh_fsid[1])));
			fh->fh_fsid[1] = fh->fh_fsid[2];
		पूर्ण
		data_left -= len;
		अगर (data_left < 0)
			वापस error;
		exp = rqst_exp_find(rqstp, fh->fh_fsid_type, fh->fh_fsid);
		fid = (काष्ठा fid *)(fh->fh_fsid + len);
	पूर्ण अन्यथा अणु
		__u32 tfh[2];
		dev_t xdev;
		ino_t xino;

		अगर (fh->fh_size != NFS_FHSIZE)
			वापस error;
		/* assume old filehandle क्रमmat */
		xdev = old_decode_dev(fh->ofh_xdev);
		xino = u32_to_ino_t(fh->ofh_xino);
		mk_fsid(FSID_DEV, tfh, xdev, xino, 0, शून्य);
		exp = rqst_exp_find(rqstp, FSID_DEV, tfh);
	पूर्ण

	error = nfserr_stale;
	अगर (IS_ERR(exp)) अणु
		trace_nfsd_set_fh_dentry_badexport(rqstp, fhp, PTR_ERR(exp));

		अगर (PTR_ERR(exp) == -ENOENT)
			वापस error;

		वापस nfsत्रुटि_सं(PTR_ERR(exp));
	पूर्ण

	अगर (exp->ex_flags & NFSEXP_NOSUBTREECHECK) अणु
		/* Elevate privileges so that the lack of 'r' or 'x'
		 * permission on some parent directory will
		 * not stop exportfs_decode_fh from being able
		 * to reconnect a directory पूर्णांकo the dentry cache.
		 * The same problem can affect "SUBTREECHECK" exports,
		 * but as nfsd_acceptable depends on correct
		 * access control settings being in effect, we cannot
		 * fix that हाल easily.
		 */
		काष्ठा cred *new = prepare_creds();
		अगर (!new) अणु
			error =  nfsत्रुटि_सं(-ENOMEM);
			जाओ out;
		पूर्ण
		new->cap_effective =
			cap_उठाओ_nfsd_set(new->cap_effective,
					   new->cap_permitted);
		put_cred(override_creds(new));
		put_cred(new);
	पूर्ण अन्यथा अणु
		error = nfsd_setuser_and_check_port(rqstp, exp);
		अगर (error)
			जाओ out;
	पूर्ण

	/*
	 * Look up the dentry using the NFS file handle.
	 */
	error = nfserr_stale;
	अगर (rqstp->rq_vers > 2)
		error = nfserr_badhandle;

	अगर (fh->fh_version != 1) अणु
		sfid.i32.ino = fh->ofh_ino;
		sfid.i32.gen = fh->ofh_generation;
		sfid.i32.parent_ino = fh->ofh_dirino;
		fid = &sfid;
		data_left = 3;
		अगर (fh->ofh_dirino == 0)
			fileid_type = खाताID_INO32_GEN;
		अन्यथा
			fileid_type = खाताID_INO32_GEN_PARENT;
	पूर्ण अन्यथा
		fileid_type = fh->fh_fileid_type;

	अगर (fileid_type == खाताID_ROOT)
		dentry = dget(exp->ex_path.dentry);
	अन्यथा अणु
		dentry = exportfs_decode_fh_raw(exp->ex_path.mnt, fid,
						data_left, fileid_type,
						nfsd_acceptable, exp);
		अगर (IS_ERR_OR_शून्य(dentry)) अणु
			trace_nfsd_set_fh_dentry_badhandle(rqstp, fhp,
					dentry ?  PTR_ERR(dentry) : -ESTALE);
			चयन (PTR_ERR(dentry)) अणु
			हाल -ENOMEM:
			हाल -ETIMEDOUT:
				अवरोध;
			शेष:
				dentry = ERR_PTR(-ESTALE);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (dentry == शून्य)
		जाओ out;
	अगर (IS_ERR(dentry)) अणु
		अगर (PTR_ERR(dentry) != -EINVAL)
			error = nfsत्रुटि_सं(PTR_ERR(dentry));
		जाओ out;
	पूर्ण

	अगर (d_is_dir(dentry) &&
			(dentry->d_flags & DCACHE_DISCONNECTED)) अणु
		prपूर्णांकk("nfsd: find_fh_dentry returned a DISCONNECTED directory: %pd2\n",
				dentry);
	पूर्ण

	fhp->fh_dentry = dentry;
	fhp->fh_export = exp;

	चयन (rqstp->rq_vers) अणु
	हाल 4:
		अगर (dentry->d_sb->s_export_op->flags & EXPORT_OP_NOATOMIC_ATTR)
			fhp->fh_no_atomic_attr = true;
		अवरोध;
	हाल 3:
		अगर (dentry->d_sb->s_export_op->flags & EXPORT_OP_NOWCC)
			fhp->fh_no_wcc = true;
		अवरोध;
	हाल 2:
		fhp->fh_no_wcc = true;
	पूर्ण

	वापस 0;
out:
	exp_put(exp);
	वापस error;
पूर्ण

/**
 * fh_verअगरy - filehandle lookup and access checking
 * @rqstp: poपूर्णांकer to current rpc request
 * @fhp: filehandle to be verअगरied
 * @type: expected type of object poपूर्णांकed to by filehandle
 * @access: type of access needed to object
 *
 * Look up a dentry from the on-the-wire filehandle, check the client's
 * access to the export, and set the current task's credentials.
 *
 * Regardless of success or failure of fh_verअगरy(), fh_put() should be
 * called on @fhp when the caller is finished with the filehandle.
 *
 * fh_verअगरy() may be called multiple बार on a given filehandle, क्रम
 * example, when processing an NFSv4 compound.  The first call will look
 * up a dentry using the on-the-wire filehandle.  Subsequent calls will
 * skip the lookup and just perक्रमm the other checks and possibly change
 * the current task's credentials.
 *
 * @type specअगरies the type of object expected using one of the S_IF*
 * स्थिरants defined in include/linux/स्थिति.स.  The caller may use zero
 * to indicate that it करोesn't care, or a negative पूर्णांकeger to indicate
 * that it expects something not of the given type.
 *
 * @access is क्रमmed from the NFSD_MAY_* स्थिरants defined in
 * fs/nfsd/vfs.h.
 */
__be32
fh_verअगरy(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp, umode_t type, पूर्णांक access)
अणु
	काष्ठा svc_export *exp = शून्य;
	काष्ठा dentry	*dentry;
	__be32		error;

	dprपूर्णांकk("nfsd: fh_verify(%s)\n", SVCFH_fmt(fhp));

	अगर (!fhp->fh_dentry) अणु
		error = nfsd_set_fh_dentry(rqstp, fhp);
		अगर (error)
			जाओ out;
	पूर्ण
	dentry = fhp->fh_dentry;
	exp = fhp->fh_export;
	/*
	 * We still have to करो all these permission checks, even when
	 * fh_dentry is alपढ़ोy set:
	 * 	- fh_verअगरy may be called multiple बार with dअगरferent
	 * 	  "access" arguments (e.g. nfsd_proc_create calls
	 * 	  fh_verअगरy(...,NFSD_MAY_EXEC) first, then later (in
	 * 	  nfsd_create) calls fh_verअगरy(...,NFSD_MAY_CREATE).
	 *	- in the NFSv4 हाल, the filehandle may have been filled
	 *	  in by fh_compose, and given a dentry, but further
	 *	  compound operations perक्रमmed with that filehandle
	 *	  still need permissions checks.  In the worst हाल, a
	 *	  mountpoपूर्णांक crossing may have changed the export
	 *	  options, and we may now need to use a dअगरferent uid
	 *	  (क्रम example, अगर dअगरferent id-squashing options are in
	 *	  effect on the new fileप्रणाली).
	 */
	error = check_pseuकरो_root(rqstp, dentry, exp);
	अगर (error)
		जाओ out;

	error = nfsd_setuser_and_check_port(rqstp, exp);
	अगर (error)
		जाओ out;

	error = nfsd_mode_check(rqstp, dentry, type);
	अगर (error)
		जाओ out;

	/*
	 * pseuकरोflavor restrictions are not enक्रमced on NLM,
	 * which clients भवly always use auth_sys क्रम,
	 * even जबतक using RPCSEC_GSS क्रम NFS.
	 */
	अगर (access & NFSD_MAY_LOCK || access & NFSD_MAY_BYPASS_GSS)
		जाओ skip_pseuकरोflavor_check;
	/*
	 * Clients may expect to be able to use auth_sys during mount,
	 * even अगर they use gss क्रम everything अन्यथा; see section 2.3.2
	 * of rfc 2623.
	 */
	अगर (access & NFSD_MAY_BYPASS_GSS_ON_ROOT
			&& exp->ex_path.dentry == dentry)
		जाओ skip_pseuकरोflavor_check;

	error = check_nfsd_access(exp, rqstp);
	अगर (error)
		जाओ out;

skip_pseuकरोflavor_check:
	/* Finally, check access permissions. */
	error = nfsd_permission(rqstp, exp, dentry, access);

	अगर (error) अणु
		dprपूर्णांकk("fh_verify: %pd2 permission failure, "
			"acc=%x, error=%d\n",
			dentry,
			access, ntohl(error));
	पूर्ण
out:
	अगर (error == nfserr_stale)
		nfsd_stats_fh_stale_inc(exp);
	वापस error;
पूर्ण


/*
 * Compose a file handle क्रम an NFS reply.
 *
 * Note that when first composed, the dentry may not yet have
 * an inode.  In this हाल a call to fh_update should be made
 * beक्रमe the fh goes out on the wire ...
 */
अटल व्योम _fh_update(काष्ठा svc_fh *fhp, काष्ठा svc_export *exp,
		काष्ठा dentry *dentry)
अणु
	अगर (dentry != exp->ex_path.dentry) अणु
		काष्ठा fid *fid = (काष्ठा fid *)
			(fhp->fh_handle.fh_fsid + fhp->fh_handle.fh_size/4 - 1);
		पूर्णांक maxsize = (fhp->fh_maxsize - fhp->fh_handle.fh_size)/4;
		पूर्णांक subtreecheck = !(exp->ex_flags & NFSEXP_NOSUBTREECHECK);

		fhp->fh_handle.fh_fileid_type =
			exportfs_encode_fh(dentry, fid, &maxsize, subtreecheck);
		fhp->fh_handle.fh_size += maxsize * 4;
	पूर्ण अन्यथा अणु
		fhp->fh_handle.fh_fileid_type = खाताID_ROOT;
	पूर्ण
पूर्ण

/*
 * क्रम composing old style file handles
 */
अटल अंतरभूत व्योम _fh_update_old(काष्ठा dentry *dentry,
				  काष्ठा svc_export *exp,
				  काष्ठा knfsd_fh *fh)
अणु
	fh->ofh_ino = ino_t_to_u32(d_inode(dentry)->i_ino);
	fh->ofh_generation = d_inode(dentry)->i_generation;
	अगर (d_is_dir(dentry) ||
	    (exp->ex_flags & NFSEXP_NOSUBTREECHECK))
		fh->ofh_dirino = 0;
पूर्ण

अटल bool is_root_export(काष्ठा svc_export *exp)
अणु
	वापस exp->ex_path.dentry == exp->ex_path.dentry->d_sb->s_root;
पूर्ण

अटल काष्ठा super_block *exp_sb(काष्ठा svc_export *exp)
अणु
	वापस exp->ex_path.dentry->d_sb;
पूर्ण

अटल bool fsid_type_ok_क्रम_exp(u8 fsid_type, काष्ठा svc_export *exp)
अणु
	चयन (fsid_type) अणु
	हाल FSID_DEV:
		अगर (!old_valid_dev(exp_sb(exp)->s_dev))
			वापस false;
		fallthrough;
	हाल FSID_MAJOR_MINOR:
	हाल FSID_ENCODE_DEV:
		वापस exp_sb(exp)->s_type->fs_flags & FS_REQUIRES_DEV;
	हाल FSID_NUM:
		वापस exp->ex_flags & NFSEXP_FSID;
	हाल FSID_UUID8:
	हाल FSID_UUID16:
		अगर (!is_root_export(exp))
			वापस false;
		fallthrough;
	हाल FSID_UUID4_INUM:
	हाल FSID_UUID16_INUM:
		वापस exp->ex_uuid != शून्य;
	पूर्ण
	वापस true;
पूर्ण


अटल व्योम set_version_and_fsid_type(काष्ठा svc_fh *fhp, काष्ठा svc_export *exp, काष्ठा svc_fh *ref_fh)
अणु
	u8 version;
	u8 fsid_type;
retry:
	version = 1;
	अगर (ref_fh && ref_fh->fh_export == exp) अणु
		version = ref_fh->fh_handle.fh_version;
		fsid_type = ref_fh->fh_handle.fh_fsid_type;

		ref_fh = शून्य;

		चयन (version) अणु
		हाल 0xca:
			fsid_type = FSID_DEV;
			अवरोध;
		हाल 1:
			अवरोध;
		शेष:
			जाओ retry;
		पूर्ण

		/*
		 * As the fsid -> fileप्रणाली mapping was guided by
		 * user-space, there is no guarantee that the fileप्रणाली
		 * actually supports that fsid type. If it करोesn't we
		 * loop around again without ref_fh set.
		 */
		अगर (!fsid_type_ok_क्रम_exp(fsid_type, exp))
			जाओ retry;
	पूर्ण अन्यथा अगर (exp->ex_flags & NFSEXP_FSID) अणु
		fsid_type = FSID_NUM;
	पूर्ण अन्यथा अगर (exp->ex_uuid) अणु
		अगर (fhp->fh_maxsize >= 64) अणु
			अगर (is_root_export(exp))
				fsid_type = FSID_UUID16;
			अन्यथा
				fsid_type = FSID_UUID16_INUM;
		पूर्ण अन्यथा अणु
			अगर (is_root_export(exp))
				fsid_type = FSID_UUID8;
			अन्यथा
				fsid_type = FSID_UUID4_INUM;
		पूर्ण
	पूर्ण अन्यथा अगर (!old_valid_dev(exp_sb(exp)->s_dev))
		/* क्रम newer device numbers, we must use a newer fsid क्रमmat */
		fsid_type = FSID_ENCODE_DEV;
	अन्यथा
		fsid_type = FSID_DEV;
	fhp->fh_handle.fh_version = version;
	अगर (version)
		fhp->fh_handle.fh_fsid_type = fsid_type;
पूर्ण

__be32
fh_compose(काष्ठा svc_fh *fhp, काष्ठा svc_export *exp, काष्ठा dentry *dentry,
	   काष्ठा svc_fh *ref_fh)
अणु
	/* ref_fh is a reference file handle.
	 * अगर it is non-null and क्रम the same fileप्रणाली, then we should compose
	 * a filehandle which is of the same version, where possible.
	 * Currently, that means that अगर ref_fh->fh_handle.fh_version == 0xca
	 * Then create a 32byte filehandle using nfs_fhbase_old
	 *
	 */

	काष्ठा inode * inode = d_inode(dentry);
	dev_t ex_dev = exp_sb(exp)->s_dev;

	dprपूर्णांकk("nfsd: fh_compose(exp %02x:%02x/%ld %pd2, ino=%ld)\n",
		MAJOR(ex_dev), MINOR(ex_dev),
		(दीर्घ) d_inode(exp->ex_path.dentry)->i_ino,
		dentry,
		(inode ? inode->i_ino : 0));

	/* Choose filehandle version and fsid type based on
	 * the reference filehandle (अगर it is in the same export)
	 * or the export options.
	 */
	set_version_and_fsid_type(fhp, exp, ref_fh);

	/* If we have a ref_fh, then copy the fh_no_wcc setting from it. */
	fhp->fh_no_wcc = ref_fh ? ref_fh->fh_no_wcc : false;

	अगर (ref_fh == fhp)
		fh_put(ref_fh);

	अगर (fhp->fh_locked || fhp->fh_dentry) अणु
		prपूर्णांकk(KERN_ERR "fh_compose: fh %pd2 not initialized!\n",
		       dentry);
	पूर्ण
	अगर (fhp->fh_maxsize < NFS_FHSIZE)
		prपूर्णांकk(KERN_ERR "fh_compose: called with maxsize %d! %pd2\n",
		       fhp->fh_maxsize,
		       dentry);

	fhp->fh_dentry = dget(dentry); /* our पूर्णांकernal copy */
	fhp->fh_export = exp_get(exp);

	अगर (fhp->fh_handle.fh_version == 0xca) अणु
		/* old style filehandle please */
		स_रखो(&fhp->fh_handle.fh_base, 0, NFS_FHSIZE);
		fhp->fh_handle.fh_size = NFS_FHSIZE;
		fhp->fh_handle.ofh_dcookie = 0xfeebbaca;
		fhp->fh_handle.ofh_dev =  old_encode_dev(ex_dev);
		fhp->fh_handle.ofh_xdev = fhp->fh_handle.ofh_dev;
		fhp->fh_handle.ofh_xino =
			ino_t_to_u32(d_inode(exp->ex_path.dentry)->i_ino);
		fhp->fh_handle.ofh_dirino = ino_t_to_u32(parent_ino(dentry));
		अगर (inode)
			_fh_update_old(dentry, exp, &fhp->fh_handle);
	पूर्ण अन्यथा अणु
		fhp->fh_handle.fh_size =
			key_len(fhp->fh_handle.fh_fsid_type) + 4;
		fhp->fh_handle.fh_auth_type = 0;

		mk_fsid(fhp->fh_handle.fh_fsid_type,
			fhp->fh_handle.fh_fsid,
			ex_dev,
			d_inode(exp->ex_path.dentry)->i_ino,
			exp->ex_fsid, exp->ex_uuid);

		अगर (inode)
			_fh_update(fhp, exp, dentry);
		अगर (fhp->fh_handle.fh_fileid_type == खाताID_INVALID) अणु
			fh_put(fhp);
			वापस nfserr_opnotsupp;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Update file handle inक्रमmation after changing a dentry.
 * This is only called by nfsd_create, nfsd_create_v3 and nfsd_proc_create
 */
__be32
fh_update(काष्ठा svc_fh *fhp)
अणु
	काष्ठा dentry *dentry;

	अगर (!fhp->fh_dentry)
		जाओ out_bad;

	dentry = fhp->fh_dentry;
	अगर (d_really_is_negative(dentry))
		जाओ out_negative;
	अगर (fhp->fh_handle.fh_version != 1) अणु
		_fh_update_old(dentry, fhp->fh_export, &fhp->fh_handle);
	पूर्ण अन्यथा अणु
		अगर (fhp->fh_handle.fh_fileid_type != खाताID_ROOT)
			वापस 0;

		_fh_update(fhp, fhp->fh_export, dentry);
		अगर (fhp->fh_handle.fh_fileid_type == खाताID_INVALID)
			वापस nfserr_opnotsupp;
	पूर्ण
	वापस 0;
out_bad:
	prपूर्णांकk(KERN_ERR "fh_update: fh not verified!\n");
	वापस nfserr_serverfault;
out_negative:
	prपूर्णांकk(KERN_ERR "fh_update: %pd2 still negative!\n",
		dentry);
	वापस nfserr_serverfault;
पूर्ण

/*
 * Release a file handle.
 */
व्योम
fh_put(काष्ठा svc_fh *fhp)
अणु
	काष्ठा dentry * dentry = fhp->fh_dentry;
	काष्ठा svc_export * exp = fhp->fh_export;
	अगर (dentry) अणु
		fh_unlock(fhp);
		fhp->fh_dentry = शून्य;
		dput(dentry);
		fh_clear_wcc(fhp);
	पूर्ण
	fh_drop_ग_लिखो(fhp);
	अगर (exp) अणु
		exp_put(exp);
		fhp->fh_export = शून्य;
	पूर्ण
	fhp->fh_no_wcc = false;
	वापस;
पूर्ण

/*
 * Shorthand क्रम dprपूर्णांकk()'s
 */
अक्षर * SVCFH_fmt(काष्ठा svc_fh *fhp)
अणु
	काष्ठा knfsd_fh *fh = &fhp->fh_handle;

	अटल अक्षर buf[80];
	प्र_लिखो(buf, "%d: %08x %08x %08x %08x %08x %08x",
		fh->fh_size,
		fh->fh_base.fh_pad[0],
		fh->fh_base.fh_pad[1],
		fh->fh_base.fh_pad[2],
		fh->fh_base.fh_pad[3],
		fh->fh_base.fh_pad[4],
		fh->fh_base.fh_pad[5]);
	वापस buf;
पूर्ण

क्रमागत fsid_source fsid_source(स्थिर काष्ठा svc_fh *fhp)
अणु
	अगर (fhp->fh_handle.fh_version != 1)
		वापस FSIDSOURCE_DEV;
	चयन(fhp->fh_handle.fh_fsid_type) अणु
	हाल FSID_DEV:
	हाल FSID_ENCODE_DEV:
	हाल FSID_MAJOR_MINOR:
		अगर (exp_sb(fhp->fh_export)->s_type->fs_flags & FS_REQUIRES_DEV)
			वापस FSIDSOURCE_DEV;
		अवरोध;
	हाल FSID_NUM:
		अगर (fhp->fh_export->ex_flags & NFSEXP_FSID)
			वापस FSIDSOURCE_FSID;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/* either a UUID type filehandle, or the filehandle करोesn't
	 * match the export.
	 */
	अगर (fhp->fh_export->ex_flags & NFSEXP_FSID)
		वापस FSIDSOURCE_FSID;
	अगर (fhp->fh_export->ex_uuid)
		वापस FSIDSOURCE_UUID;
	वापस FSIDSOURCE_DEV;
पूर्ण
