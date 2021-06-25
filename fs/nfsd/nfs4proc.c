<शैली गुरु>
/*
 *  Server-side procedures क्रम NFSv4.
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson   <andros@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/file.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/nfs_ssc.h>

#समावेश "idmap.h"
#समावेश "cache.h"
#समावेश "xdr4.h"
#समावेश "vfs.h"
#समावेश "current_stateid.h"
#समावेश "netns.h"
#समावेश "acl.h"
#समावेश "pnfs.h"
#समावेश "trace.h"

अटल bool पूर्णांकer_copy_offload_enable;
module_param(पूर्णांकer_copy_offload_enable, bool, 0644);
MODULE_PARM_DESC(पूर्णांकer_copy_offload_enable,
		 "Enable inter server to server copy offload. Default: false");

#अगर_घोषित CONFIG_NFSD_V4_SECURITY_LABEL
#समावेश <linux/security.h>

अटल अंतरभूत व्योम
nfsd4_security_inode_setsecctx(काष्ठा svc_fh *resfh, काष्ठा xdr_netobj *label, u32 *bmval)
अणु
	काष्ठा inode *inode = d_inode(resfh->fh_dentry);
	पूर्णांक status;

	inode_lock(inode);
	status = security_inode_setsecctx(resfh->fh_dentry,
		label->data, label->len);
	inode_unlock(inode);

	अगर (status)
		/*
		 * XXX: We should really fail the whole खोलो, but we may
		 * alपढ़ोy have created a new file, so it may be too
		 * late.  For now this seems the least of evils:
		 */
		bmval[2] &= ~FATTR4_WORD2_SECURITY_LABEL;

	वापस;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
nfsd4_security_inode_setsecctx(काष्ठा svc_fh *resfh, काष्ठा xdr_netobj *label, u32 *bmval)
अणु पूर्ण
#पूर्ण_अगर

#घोषणा NFSDDBG_FACILITY		NFSDDBG_PROC

अटल u32 nfsd_attrmask[] = अणु
	NFSD_WRITEABLE_ATTRS_WORD0,
	NFSD_WRITEABLE_ATTRS_WORD1,
	NFSD_WRITEABLE_ATTRS_WORD2
पूर्ण;

अटल u32 nfsd41_ex_attrmask[] = अणु
	NFSD_SUPPATTR_EXCLCREAT_WORD0,
	NFSD_SUPPATTR_EXCLCREAT_WORD1,
	NFSD_SUPPATTR_EXCLCREAT_WORD2
पूर्ण;

अटल __be32
check_attr_support(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		   u32 *bmval, u32 *writable)
अणु
	काष्ठा dentry *dentry = cstate->current_fh.fh_dentry;
	काष्ठा svc_export *exp = cstate->current_fh.fh_export;

	अगर (!nfsd_attrs_supported(cstate->minorversion, bmval))
		वापस nfserr_attrnotsupp;
	अगर ((bmval[0] & FATTR4_WORD0_ACL) && !IS_POSIXACL(d_inode(dentry)))
		वापस nfserr_attrnotsupp;
	अगर ((bmval[2] & FATTR4_WORD2_SECURITY_LABEL) &&
			!(exp->ex_flags & NFSEXP_SECURITY_LABEL))
		वापस nfserr_attrnotsupp;
	अगर (writable && !bmval_is_subset(bmval, writable))
		वापस nfserr_inval;
	अगर (writable && (bmval[2] & FATTR4_WORD2_MODE_UMASK) &&
			(bmval[1] & FATTR4_WORD1_MODE))
		वापस nfserr_inval;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_check_खोलो_attributes(काष्ठा svc_rqst *rqstp,
	काष्ठा nfsd4_compound_state *cstate, काष्ठा nfsd4_खोलो *खोलो)
अणु
	__be32 status = nfs_ok;

	अगर (खोलो->op_create == NFS4_OPEN_CREATE) अणु
		अगर (खोलो->op_createmode == NFS4_CREATE_UNCHECKED
		    || खोलो->op_createmode == NFS4_CREATE_GUARDED)
			status = check_attr_support(rqstp, cstate,
					खोलो->op_bmval, nfsd_attrmask);
		अन्यथा अगर (खोलो->op_createmode == NFS4_CREATE_EXCLUSIVE4_1)
			status = check_attr_support(rqstp, cstate,
					खोलो->op_bmval, nfsd41_ex_attrmask);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक
is_create_with_attrs(काष्ठा nfsd4_खोलो *खोलो)
अणु
	वापस खोलो->op_create == NFS4_OPEN_CREATE
		&& (खोलो->op_createmode == NFS4_CREATE_UNCHECKED
		    || खोलो->op_createmode == NFS4_CREATE_GUARDED
		    || खोलो->op_createmode == NFS4_CREATE_EXCLUSIVE4_1);
पूर्ण

/*
 * अगर error occurs when setting the acl, just clear the acl bit
 * in the वापसed attr biपंचांगap.
 */
अटल व्योम
करो_set_nfs4_acl(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
		काष्ठा nfs4_acl *acl, u32 *bmval)
अणु
	__be32 status;

	status = nfsd4_set_nfs4_acl(rqstp, fhp, acl);
	अगर (status)
		/*
		 * We should probably fail the whole खोलो at this poपूर्णांक,
		 * but we've already created the file, so it's too late;
		 * So this seems the least of evils:
		 */
		bmval[0] &= ~FATTR4_WORD0_ACL;
पूर्ण

अटल अंतरभूत व्योम
fh_dup2(काष्ठा svc_fh *dst, काष्ठा svc_fh *src)
अणु
	fh_put(dst);
	dget(src->fh_dentry);
	अगर (src->fh_export)
		exp_get(src->fh_export);
	*dst = *src;
पूर्ण

अटल __be32
करो_खोलो_permission(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *current_fh, काष्ठा nfsd4_खोलो *खोलो, पूर्णांक accmode)
अणु
	__be32 status;

	अगर (खोलो->op_truncate &&
		!(खोलो->op_share_access & NFS4_SHARE_ACCESS_WRITE))
		वापस nfserr_inval;

	accmode |= NFSD_MAY_READ_IF_EXEC;

	अगर (खोलो->op_share_access & NFS4_SHARE_ACCESS_READ)
		accmode |= NFSD_MAY_READ;
	अगर (खोलो->op_share_access & NFS4_SHARE_ACCESS_WRITE)
		accmode |= (NFSD_MAY_WRITE | NFSD_MAY_TRUNC);
	अगर (खोलो->op_share_deny & NFS4_SHARE_DENY_READ)
		accmode |= NFSD_MAY_WRITE;

	status = fh_verअगरy(rqstp, current_fh, S_IFREG, accmode);

	वापस status;
पूर्ण

अटल __be32 nfsd_check_obj_isreg(काष्ठा svc_fh *fh)
अणु
	umode_t mode = d_inode(fh->fh_dentry)->i_mode;

	अगर (S_ISREG(mode))
		वापस nfs_ok;
	अगर (S_ISसूची(mode))
		वापस nfserr_isdir;
	/*
	 * Using err_symlink as our catch-all हाल may look odd; but
	 * there's no other obvious error क्रम this हाल in 4.0, and we
	 * happen to know that it will cause the linux v4 client to करो
	 * the right thing on attempts to खोलो something other than a
	 * regular file.
	 */
	वापस nfserr_symlink;
पूर्ण

अटल व्योम nfsd4_set_खोलो_owner_reply_cache(काष्ठा nfsd4_compound_state *cstate, काष्ठा nfsd4_खोलो *खोलो, काष्ठा svc_fh *resfh)
अणु
	अगर (nfsd4_has_session(cstate))
		वापस;
	fh_copy_shallow(&खोलो->op_खोलोowner->oo_owner.so_replay.rp_खोलोfh,
			&resfh->fh_handle);
पूर्ण

अटल __be32
करो_खोलो_lookup(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate, काष्ठा nfsd4_खोलो *खोलो, काष्ठा svc_fh **resfh)
अणु
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	पूर्णांक accmode;
	__be32 status;

	*resfh = kदो_स्मृति(माप(काष्ठा svc_fh), GFP_KERNEL);
	अगर (!*resfh)
		वापस nfserr_jukebox;
	fh_init(*resfh, NFS4_FHSIZE);
	खोलो->op_truncate = false;

	अगर (खोलो->op_create) अणु
		/* FIXME: check session persistence and pnfs flags.
		 * The nfsv4.1 spec requires the following semantics:
		 *
		 * Persistent   | pNFS   | Server REQUIRED | Client Allowed
		 * Reply Cache  | server |                 |
		 * -------------+--------+-----------------+--------------------
		 * no           | no     | EXCLUSIVE4_1    | EXCLUSIVE4_1
		 *              |        |                 | (SHOULD)
		 *              |        | and EXCLUSIVE4  | or EXCLUSIVE4
		 *              |        |                 | (SHOULD NOT)
		 * no           | yes    | EXCLUSIVE4_1    | EXCLUSIVE4_1
		 * yes          | no     | GUARDED4        | GUARDED4
		 * yes          | yes    | GUARDED4        | GUARDED4
		 */

		/*
		 * Note: create modes (UNCHECKED,GUARDED...) are the same
		 * in NFSv4 as in v3 except EXCLUSIVE4_1.
		 */
		current->fs->umask = खोलो->op_umask;
		status = करो_nfsd_create(rqstp, current_fh, खोलो->op_fname,
					खोलो->op_fnamelen, &खोलो->op_iattr,
					*resfh, खोलो->op_createmode,
					(u32 *)खोलो->op_verf.data,
					&खोलो->op_truncate, &खोलो->op_created);
		current->fs->umask = 0;

		अगर (!status && खोलो->op_label.len)
			nfsd4_security_inode_setsecctx(*resfh, &खोलो->op_label, खोलो->op_bmval);

		/*
		 * Following rfc 3530 14.2.16, and rfc 5661 18.16.4
		 * use the वापसed biपंचांगask to indicate which attributes
		 * we used to store the verअगरier:
		 */
		अगर (nfsd_create_is_exclusive(खोलो->op_createmode) && status == 0)
			खोलो->op_bmval[1] |= (FATTR4_WORD1_TIME_ACCESS |
						FATTR4_WORD1_TIME_MODIFY);
	पूर्ण अन्यथा
		/*
		 * Note this may निकास with the parent still locked.
		 * We will hold the lock until nfsd4_खोलो's final
		 * lookup, to prevent नामs or unlinks until we've had
		 * a chance to an acquire a delegation अगर appropriate.
		 */
		status = nfsd_lookup(rqstp, current_fh,
				     खोलो->op_fname, खोलो->op_fnamelen, *resfh);
	अगर (status)
		जाओ out;
	status = nfsd_check_obj_isreg(*resfh);
	अगर (status)
		जाओ out;

	अगर (is_create_with_attrs(खोलो) && खोलो->op_acl != शून्य)
		करो_set_nfs4_acl(rqstp, *resfh, खोलो->op_acl, खोलो->op_bmval);

	nfsd4_set_खोलो_owner_reply_cache(cstate, खोलो, *resfh);
	accmode = NFSD_MAY_NOP;
	अगर (खोलो->op_created ||
			खोलो->op_claim_type == NFS4_OPEN_CLAIM_DELEGATE_CUR)
		accmode |= NFSD_MAY_OWNER_OVERRIDE;
	status = करो_खोलो_permission(rqstp, *resfh, खोलो, accmode);
	set_change_info(&खोलो->op_cinfo, current_fh);
out:
	वापस status;
पूर्ण

अटल __be32
करो_खोलो_fhandle(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate, काष्ठा nfsd4_खोलो *खोलो)
अणु
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	__be32 status;
	पूर्णांक accmode = 0;

	/* We करोn't know the target directory, and thereक्रमe can not
	* set the change info
	*/

	स_रखो(&खोलो->op_cinfo, 0, माप(काष्ठा nfsd4_change_info));

	nfsd4_set_खोलो_owner_reply_cache(cstate, खोलो, current_fh);

	खोलो->op_truncate = (खोलो->op_iattr.ia_valid & ATTR_SIZE) &&
		(खोलो->op_iattr.ia_size == 0);
	/*
	 * In the delegation हाल, the client is telling us about an
	 * खोलो that it *alपढ़ोy* perक्रमmed locally, some समय ago.  We
	 * should let it succeed now अगर possible.
	 *
	 * In the हाल of a CLAIM_FH खोलो, on the other hand, the client
	 * may be counting on us to enक्रमce permissions (the Linux 4.1
	 * client uses this क्रम normal खोलोs, क्रम example).
	 */
	अगर (खोलो->op_claim_type == NFS4_OPEN_CLAIM_DELEG_CUR_FH)
		accmode = NFSD_MAY_OWNER_OVERRIDE;

	status = करो_खोलो_permission(rqstp, current_fh, खोलो, accmode);

	वापस status;
पूर्ण

अटल व्योम
copy_clientid(clientid_t *clid, काष्ठा nfsd4_session *session)
अणु
	काष्ठा nfsd4_sessionid *sid =
			(काष्ठा nfsd4_sessionid *)session->se_sessionid.data;

	clid->cl_boot = sid->clientid.cl_boot;
	clid->cl_id = sid->clientid.cl_id;
पूर्ण

अटल __be32
nfsd4_खोलो(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_खोलो *खोलो = &u->खोलो;
	__be32 status;
	काष्ठा svc_fh *resfh = शून्य;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	bool reclaim = false;

	dprपूर्णांकk("NFSD: nfsd4_open filename %.*s op_openowner %p\n",
		(पूर्णांक)खोलो->op_fnamelen, खोलो->op_fname,
		खोलो->op_खोलोowner);

	/* This check required by spec. */
	अगर (खोलो->op_create && खोलो->op_claim_type != NFS4_OPEN_CLAIM_शून्य)
		वापस nfserr_inval;

	खोलो->op_created = false;
	/*
	 * RFC5661 18.51.3
	 * Beक्रमe RECLAIM_COMPLETE करोne, server should deny new lock
	 */
	अगर (nfsd4_has_session(cstate) &&
	    !test_bit(NFSD4_CLIENT_RECLAIM_COMPLETE, &cstate->clp->cl_flags) &&
	    खोलो->op_claim_type != NFS4_OPEN_CLAIM_PREVIOUS)
		वापस nfserr_grace;

	अगर (nfsd4_has_session(cstate))
		copy_clientid(&खोलो->op_clientid, cstate->session);

	/* check seqid क्रम replay. set nfs4_owner */
	status = nfsd4_process_खोलो1(cstate, खोलो, nn);
	अगर (status == nfserr_replay_me) अणु
		काष्ठा nfs4_replay *rp = &खोलो->op_खोलोowner->oo_owner.so_replay;
		fh_put(&cstate->current_fh);
		fh_copy_shallow(&cstate->current_fh.fh_handle,
				&rp->rp_खोलोfh);
		status = fh_verअगरy(rqstp, &cstate->current_fh, 0, NFSD_MAY_NOP);
		अगर (status)
			dprपूर्णांकk("nfsd4_open: replay failed"
				" restoring previous filehandle\n");
		अन्यथा
			status = nfserr_replay_me;
	पूर्ण
	अगर (status)
		जाओ out;
	अगर (खोलो->op_xdr_error) अणु
		status = खोलो->op_xdr_error;
		जाओ out;
	पूर्ण

	status = nfsd4_check_खोलो_attributes(rqstp, cstate, खोलो);
	अगर (status)
		जाओ out;

	/* Openowner is now set, so sequence id will get bumped.  Now we need
	 * these checks beक्रमe we करो any creates: */
	status = nfserr_grace;
	अगर (खोलोs_in_grace(net) && खोलो->op_claim_type != NFS4_OPEN_CLAIM_PREVIOUS)
		जाओ out;
	status = nfserr_no_grace;
	अगर (!खोलोs_in_grace(net) && खोलो->op_claim_type == NFS4_OPEN_CLAIM_PREVIOUS)
		जाओ out;

	चयन (खोलो->op_claim_type) अणु
		हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
		हाल NFS4_OPEN_CLAIM_शून्य:
			status = करो_खोलो_lookup(rqstp, cstate, खोलो, &resfh);
			अगर (status)
				जाओ out;
			अवरोध;
		हाल NFS4_OPEN_CLAIM_PREVIOUS:
			status = nfs4_check_खोलो_reclaim(cstate->clp);
			अगर (status)
				जाओ out;
			खोलो->op_खोलोowner->oo_flags |= NFS4_OO_CONFIRMED;
			reclaim = true;
			fallthrough;
		हाल NFS4_OPEN_CLAIM_FH:
		हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
			status = करो_खोलो_fhandle(rqstp, cstate, खोलो);
			अगर (status)
				जाओ out;
			resfh = &cstate->current_fh;
			अवरोध;
		हाल NFS4_OPEN_CLAIM_DELEG_PREV_FH:
             	हाल NFS4_OPEN_CLAIM_DELEGATE_PREV:
			dprपूर्णांकk("NFSD: unsupported OPEN claim type %d\n",
				खोलो->op_claim_type);
			status = nfserr_notsupp;
			जाओ out;
		शेष:
			dprपूर्णांकk("NFSD: Invalid OPEN claim type %d\n",
				खोलो->op_claim_type);
			status = nfserr_inval;
			जाओ out;
	पूर्ण
	/*
	 * nfsd4_process_खोलो2() करोes the actual खोलोing of the file.  If
	 * successful, it (1) truncates the file अगर खोलो->op_truncate was
	 * set, (2) sets खोलो->op_stateid, (3) sets खोलो->op_delegation.
	 */
	status = nfsd4_process_खोलो2(rqstp, resfh, खोलो);
	WARN(status && खोलो->op_created,
	     "nfsd4_process_open2 failed to open newly-created file! status=%u\n",
	     be32_to_cpu(status));
	अगर (reclaim && !status)
		nn->somebody_reclaimed = true;
out:
	अगर (resfh && resfh != &cstate->current_fh) अणु
		fh_dup2(&cstate->current_fh, resfh);
		fh_put(resfh);
		kमुक्त(resfh);
	पूर्ण
	nfsd4_cleanup_खोलो_state(cstate, खोलो);
	nfsd4_bump_seqid(cstate, status);
	वापस status;
पूर्ण

/*
 * OPEN is the only seqid-mutating operation whose decoding can fail
 * with a seqid-mutating error (specअगरically, decoding of user names in
 * the attributes).  Thereक्रमe we have to करो some processing to look up
 * the stateowner so that we can bump the seqid.
 */
अटल __be32 nfsd4_खोलो_omfg(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate, काष्ठा nfsd4_op *op)
अणु
	काष्ठा nfsd4_खोलो *खोलो = &op->u.खोलो;

	अगर (!seqid_mutating_err(ntohl(op->status)))
		वापस op->status;
	अगर (nfsd4_has_session(cstate))
		वापस op->status;
	खोलो->op_xdr_error = op->status;
	वापस nfsd4_खोलो(rqstp, cstate, &op->u);
पूर्ण

/*
 * filehandle-manipulating ops.
 */
अटल __be32
nfsd4_getfh(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	    जोड़ nfsd4_op_u *u)
अणु
	u->getfh = &cstate->current_fh;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_putfh(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	    जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_putfh *putfh = &u->putfh;
	__be32 ret;

	fh_put(&cstate->current_fh);
	cstate->current_fh.fh_handle.fh_size = putfh->pf_fhlen;
	स_नकल(&cstate->current_fh.fh_handle.fh_base, putfh->pf_fhval,
	       putfh->pf_fhlen);
	ret = fh_verअगरy(rqstp, &cstate->current_fh, 0, NFSD_MAY_BYPASS_GSS);
#अगर_घोषित CONFIG_NFSD_V4_2_INTER_SSC
	अगर (ret == nfserr_stale && putfh->no_verअगरy) अणु
		SET_FH_FLAG(&cstate->current_fh, NFSD4_FH_FOREIGN);
		ret = 0;
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल __be32
nfsd4_putrootfh(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	__be32 status;

	fh_put(&cstate->current_fh);
	status = exp_pseuकरोroot(rqstp, &cstate->current_fh);
	वापस status;
पूर्ण

अटल __be32
nfsd4_restorefh(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	अगर (!cstate->save_fh.fh_dentry)
		वापस nfserr_restorefh;

	fh_dup2(&cstate->current_fh, &cstate->save_fh);
	अगर (HAS_CSTATE_FLAG(cstate, SAVED_STATE_ID_FLAG)) अणु
		स_नकल(&cstate->current_stateid, &cstate->save_stateid, माप(stateid_t));
		SET_CSTATE_FLAG(cstate, CURRENT_STATE_ID_FLAG);
	पूर्ण
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_savefh(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	fh_dup2(&cstate->save_fh, &cstate->current_fh);
	अगर (HAS_CSTATE_FLAG(cstate, CURRENT_STATE_ID_FLAG)) अणु
		स_नकल(&cstate->save_stateid, &cstate->current_stateid, माप(stateid_t));
		SET_CSTATE_FLAG(cstate, SAVED_STATE_ID_FLAG);
	पूर्ण
	वापस nfs_ok;
पूर्ण

/*
 * misc nfsv4 ops
 */
अटल __be32
nfsd4_access(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_access *access = &u->access;
	u32 access_full;

	access_full = NFS3_ACCESS_FULL;
	अगर (cstate->minorversion >= 2)
		access_full |= NFS4_ACCESS_XALIST | NFS4_ACCESS_XAREAD |
			       NFS4_ACCESS_XAWRITE;

	अगर (access->ac_req_access & ~access_full)
		वापस nfserr_inval;

	access->ac_resp_access = access->ac_req_access;
	वापस nfsd_access(rqstp, &cstate->current_fh, &access->ac_resp_access,
			   &access->ac_supported);
पूर्ण

अटल व्योम gen_boot_verअगरier(nfs4_verअगरier *verअगरier, काष्ठा net *net)
अणु
	__be32 *verf = (__be32 *)verअगरier->data;

	BUILD_BUG_ON(2*माप(*verf) != माप(verअगरier->data));

	nfsd_copy_boot_verअगरier(verf, net_generic(net, nfsd_net_id));
पूर्ण

अटल __be32
nfsd4_commit(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_commit *commit = &u->commit;

	वापस nfsd_commit(rqstp, &cstate->current_fh, commit->co_offset,
			     commit->co_count,
			     (__be32 *)commit->co_verf.data);
पूर्ण

अटल __be32
nfsd4_create(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_create *create = &u->create;
	काष्ठा svc_fh resfh;
	__be32 status;
	dev_t rdev;

	fh_init(&resfh, NFS4_FHSIZE);

	status = fh_verअगरy(rqstp, &cstate->current_fh, S_IFसूची, NFSD_MAY_NOP);
	अगर (status)
		वापस status;

	status = check_attr_support(rqstp, cstate, create->cr_bmval,
				    nfsd_attrmask);
	अगर (status)
		वापस status;

	current->fs->umask = create->cr_umask;
	चयन (create->cr_type) अणु
	हाल NF4LNK:
		status = nfsd_symlink(rqstp, &cstate->current_fh,
				      create->cr_name, create->cr_namelen,
				      create->cr_data, &resfh);
		अवरोध;

	हाल NF4BLK:
		status = nfserr_inval;
		rdev = MKDEV(create->cr_specdata1, create->cr_specdata2);
		अगर (MAJOR(rdev) != create->cr_specdata1 ||
		    MINOR(rdev) != create->cr_specdata2)
			जाओ out_umask;
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFBLK, rdev, &resfh);
		अवरोध;

	हाल NF4CHR:
		status = nfserr_inval;
		rdev = MKDEV(create->cr_specdata1, create->cr_specdata2);
		अगर (MAJOR(rdev) != create->cr_specdata1 ||
		    MINOR(rdev) != create->cr_specdata2)
			जाओ out_umask;
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr,S_IFCHR, rdev, &resfh);
		अवरोध;

	हाल NF4SOCK:
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFSOCK, 0, &resfh);
		अवरोध;

	हाल NF4FIFO:
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFIFO, 0, &resfh);
		अवरोध;

	हाल NF4सूची:
		create->cr_iattr.ia_valid &= ~ATTR_SIZE;
		status = nfsd_create(rqstp, &cstate->current_fh,
				     create->cr_name, create->cr_namelen,
				     &create->cr_iattr, S_IFसूची, 0, &resfh);
		अवरोध;

	शेष:
		status = nfserr_badtype;
	पूर्ण

	अगर (status)
		जाओ out;

	अगर (create->cr_label.len)
		nfsd4_security_inode_setsecctx(&resfh, &create->cr_label, create->cr_bmval);

	अगर (create->cr_acl != शून्य)
		करो_set_nfs4_acl(rqstp, &resfh, create->cr_acl,
				create->cr_bmval);

	fh_unlock(&cstate->current_fh);
	set_change_info(&create->cr_cinfo, &cstate->current_fh);
	fh_dup2(&cstate->current_fh, &resfh);
out:
	fh_put(&resfh);
out_umask:
	current->fs->umask = 0;
	वापस status;
पूर्ण

अटल __be32
nfsd4_getattr(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	      जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_getattr *getattr = &u->getattr;
	__be32 status;

	status = fh_verअगरy(rqstp, &cstate->current_fh, 0, NFSD_MAY_NOP);
	अगर (status)
		वापस status;

	अगर (getattr->ga_bmval[1] & NFSD_WRITEONLY_ATTRS_WORD1)
		वापस nfserr_inval;

	getattr->ga_bmval[0] &= nfsd_suppattrs[cstate->minorversion][0];
	getattr->ga_bmval[1] &= nfsd_suppattrs[cstate->minorversion][1];
	getattr->ga_bmval[2] &= nfsd_suppattrs[cstate->minorversion][2];

	getattr->ga_fhp = &cstate->current_fh;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_link(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_link *link = &u->link;
	__be32 status;

	status = nfsd_link(rqstp, &cstate->current_fh,
			   link->li_name, link->li_namelen, &cstate->save_fh);
	अगर (!status)
		set_change_info(&link->li_cinfo, &cstate->current_fh);
	वापस status;
पूर्ण

अटल __be32 nfsd4_करो_lookupp(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fh)
अणु
	काष्ठा svc_fh पंचांगp_fh;
	__be32 ret;

	fh_init(&पंचांगp_fh, NFS4_FHSIZE);
	ret = exp_pseuकरोroot(rqstp, &पंचांगp_fh);
	अगर (ret)
		वापस ret;
	अगर (पंचांगp_fh.fh_dentry == fh->fh_dentry) अणु
		fh_put(&पंचांगp_fh);
		वापस nfserr_noent;
	पूर्ण
	fh_put(&पंचांगp_fh);
	वापस nfsd_lookup(rqstp, fh, "..", 2, fh);
पूर्ण

अटल __be32
nfsd4_lookupp(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	      जोड़ nfsd4_op_u *u)
अणु
	वापस nfsd4_करो_lookupp(rqstp, &cstate->current_fh);
पूर्ण

अटल __be32
nfsd4_lookup(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	वापस nfsd_lookup(rqstp, &cstate->current_fh,
			   u->lookup.lo_name, u->lookup.lo_len,
			   &cstate->current_fh);
पूर्ण

अटल __be32
nfsd4_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_पढ़ो *पढ़ो = &u->पढ़ो;
	__be32 status;

	पढ़ो->rd_nf = शून्य;
	अगर (पढ़ो->rd_offset >= OFFSET_MAX)
		वापस nfserr_inval;

	trace_nfsd_पढ़ो_start(rqstp, &cstate->current_fh,
			      पढ़ो->rd_offset, पढ़ो->rd_length);

	/*
	 * If we करो a zero copy पढ़ो, then a client will see पढ़ो data
	 * that reflects the state of the file *after* perक्रमming the
	 * following compound.
	 *
	 * To ensure proper ordering, we thereक्रमe turn off zero copy अगर
	 * the client wants us to करो more in this compound:
	 */
	अगर (!nfsd4_last_compound_op(rqstp))
		clear_bit(RQ_SPLICE_OK, &rqstp->rq_flags);

	/* check stateid */
	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					&पढ़ो->rd_stateid, RD_STATE,
					&पढ़ो->rd_nf, शून्य);
	अगर (status) अणु
		dprपूर्णांकk("NFSD: nfsd4_read: couldn't process stateid!\n");
		जाओ out;
	पूर्ण
	status = nfs_ok;
out:
	पढ़ो->rd_rqstp = rqstp;
	पढ़ो->rd_fhp = &cstate->current_fh;
	वापस status;
पूर्ण


अटल व्योम
nfsd4_पढ़ो_release(जोड़ nfsd4_op_u *u)
अणु
	अगर (u->पढ़ो.rd_nf)
		nfsd_file_put(u->पढ़ो.rd_nf);
	trace_nfsd_पढ़ो_करोne(u->पढ़ो.rd_rqstp, u->पढ़ो.rd_fhp,
			     u->पढ़ो.rd_offset, u->पढ़ो.rd_length);
पूर्ण

अटल __be32
nfsd4_सूची_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	      जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_सूची_पढ़ो *सूची_पढ़ो = &u->सूची_पढ़ो;
	u64 cookie = सूची_पढ़ो->rd_cookie;
	अटल स्थिर nfs4_verअगरier zeroverf;

	/* no need to check permission - this will be करोne in nfsd_सूची_पढ़ो() */

	अगर (सूची_पढ़ो->rd_bmval[1] & NFSD_WRITEONLY_ATTRS_WORD1)
		वापस nfserr_inval;

	सूची_पढ़ो->rd_bmval[0] &= nfsd_suppattrs[cstate->minorversion][0];
	सूची_पढ़ो->rd_bmval[1] &= nfsd_suppattrs[cstate->minorversion][1];
	सूची_पढ़ो->rd_bmval[2] &= nfsd_suppattrs[cstate->minorversion][2];

	अगर ((cookie == 1) || (cookie == 2) ||
	    (cookie == 0 && स_भेद(सूची_पढ़ो->rd_verf.data, zeroverf.data, NFS4_VERIFIER_SIZE)))
		वापस nfserr_bad_cookie;

	सूची_पढ़ो->rd_rqstp = rqstp;
	सूची_पढ़ो->rd_fhp = &cstate->current_fh;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_पढ़ोlink(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	       जोड़ nfsd4_op_u *u)
अणु
	u->पढ़ोlink.rl_rqstp = rqstp;
	u->पढ़ोlink.rl_fhp = &cstate->current_fh;
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_हटाओ(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_हटाओ *हटाओ = &u->हटाओ;
	__be32 status;

	अगर (खोलोs_in_grace(SVC_NET(rqstp)))
		वापस nfserr_grace;
	status = nfsd_unlink(rqstp, &cstate->current_fh, 0,
			     हटाओ->rm_name, हटाओ->rm_namelen);
	अगर (!status) अणु
		fh_unlock(&cstate->current_fh);
		set_change_info(&हटाओ->rm_cinfo, &cstate->current_fh);
	पूर्ण
	वापस status;
पूर्ण

अटल __be32
nfsd4_नाम(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_नाम *नाम = &u->नाम;
	__be32 status;

	अगर (खोलोs_in_grace(SVC_NET(rqstp)))
		वापस nfserr_grace;
	status = nfsd_नाम(rqstp, &cstate->save_fh, नाम->rn_sname,
			     नाम->rn_snamelen, &cstate->current_fh,
			     नाम->rn_tname, नाम->rn_tnamelen);
	अगर (status)
		वापस status;
	set_change_info(&नाम->rn_sinfo, &cstate->current_fh);
	set_change_info(&नाम->rn_tinfo, &cstate->save_fh);
	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_secinfo(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	      जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_secinfo *secinfo = &u->secinfo;
	काष्ठा svc_export *exp;
	काष्ठा dentry *dentry;
	__be32 err;

	err = fh_verअगरy(rqstp, &cstate->current_fh, S_IFसूची, NFSD_MAY_EXEC);
	अगर (err)
		वापस err;
	err = nfsd_lookup_dentry(rqstp, &cstate->current_fh,
				    secinfo->si_name, secinfo->si_namelen,
				    &exp, &dentry);
	अगर (err)
		वापस err;
	fh_unlock(&cstate->current_fh);
	अगर (d_really_is_negative(dentry)) अणु
		exp_put(exp);
		err = nfserr_noent;
	पूर्ण अन्यथा
		secinfo->si_exp = exp;
	dput(dentry);
	अगर (cstate->minorversion)
		/* See rfc 5661 section 2.6.3.1.1.8 */
		fh_put(&cstate->current_fh);
	वापस err;
पूर्ण

अटल __be32
nfsd4_secinfo_no_name(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	__be32 err;

	चयन (u->secinfo_no_name.sin_style) अणु
	हाल NFS4_SECINFO_STYLE4_CURRENT_FH:
		अवरोध;
	हाल NFS4_SECINFO_STYLE4_PARENT:
		err = nfsd4_करो_lookupp(rqstp, &cstate->current_fh);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		वापस nfserr_inval;
	पूर्ण

	u->secinfo_no_name.sin_exp = exp_get(cstate->current_fh.fh_export);
	fh_put(&cstate->current_fh);
	वापस nfs_ok;
पूर्ण

अटल व्योम
nfsd4_secinfo_release(जोड़ nfsd4_op_u *u)
अणु
	अगर (u->secinfo.si_exp)
		exp_put(u->secinfo.si_exp);
पूर्ण

अटल व्योम
nfsd4_secinfo_no_name_release(जोड़ nfsd4_op_u *u)
अणु
	अगर (u->secinfo_no_name.sin_exp)
		exp_put(u->secinfo_no_name.sin_exp);
पूर्ण

अटल __be32
nfsd4_setattr(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	      जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_setattr *setattr = &u->setattr;
	__be32 status = nfs_ok;
	पूर्णांक err;

	अगर (setattr->sa_iattr.ia_valid & ATTR_SIZE) अणु
		status = nfs4_preprocess_stateid_op(rqstp, cstate,
				&cstate->current_fh, &setattr->sa_stateid,
				WR_STATE, शून्य, शून्य);
		अगर (status) अणु
			dprपूर्णांकk("NFSD: nfsd4_setattr: couldn't process stateid!\n");
			वापस status;
		पूर्ण
	पूर्ण
	err = fh_want_ग_लिखो(&cstate->current_fh);
	अगर (err)
		वापस nfsत्रुटि_सं(err);
	status = nfs_ok;

	status = check_attr_support(rqstp, cstate, setattr->sa_bmval,
				    nfsd_attrmask);
	अगर (status)
		जाओ out;

	अगर (setattr->sa_acl != शून्य)
		status = nfsd4_set_nfs4_acl(rqstp, &cstate->current_fh,
					    setattr->sa_acl);
	अगर (status)
		जाओ out;
	अगर (setattr->sa_label.len)
		status = nfsd4_set_nfs4_label(rqstp, &cstate->current_fh,
				&setattr->sa_label);
	अगर (status)
		जाओ out;
	status = nfsd_setattr(rqstp, &cstate->current_fh, &setattr->sa_iattr,
				0, (समय64_t)0);
out:
	fh_drop_ग_लिखो(&cstate->current_fh);
	वापस status;
पूर्ण

अटल __be32
nfsd4_ग_लिखो(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	    जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_ग_लिखो *ग_लिखो = &u->ग_लिखो;
	stateid_t *stateid = &ग_लिखो->wr_stateid;
	काष्ठा nfsd_file *nf = शून्य;
	__be32 status = nfs_ok;
	अचिन्हित दीर्घ cnt;
	पूर्णांक nvecs;

	अगर (ग_लिखो->wr_offset >= OFFSET_MAX)
		वापस nfserr_inval;

	cnt = ग_लिखो->wr_buflen;
	trace_nfsd_ग_लिखो_start(rqstp, &cstate->current_fh,
			       ग_लिखो->wr_offset, cnt);
	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
						stateid, WR_STATE, &nf, शून्य);
	अगर (status) अणु
		dprपूर्णांकk("NFSD: nfsd4_write: couldn't process stateid!\n");
		वापस status;
	पूर्ण

	ग_लिखो->wr_how_written = ग_लिखो->wr_stable_how;

	nvecs = svc_fill_ग_लिखो_vector(rqstp, ग_लिखो->wr_payload.pages,
				      ग_लिखो->wr_payload.head, ग_लिखो->wr_buflen);
	WARN_ON_ONCE(nvecs > ARRAY_SIZE(rqstp->rq_vec));

	status = nfsd_vfs_ग_लिखो(rqstp, &cstate->current_fh, nf,
				ग_लिखो->wr_offset, rqstp->rq_vec, nvecs, &cnt,
				ग_लिखो->wr_how_written,
				(__be32 *)ग_लिखो->wr_verअगरier.data);
	nfsd_file_put(nf);

	ग_लिखो->wr_bytes_written = cnt;
	trace_nfsd_ग_लिखो_करोne(rqstp, &cstate->current_fh,
			      ग_लिखो->wr_offset, cnt);
	वापस status;
पूर्ण

अटल __be32
nfsd4_verअगरy_copy(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		  stateid_t *src_stateid, काष्ठा nfsd_file **src,
		  stateid_t *dst_stateid, काष्ठा nfsd_file **dst)
अणु
	__be32 status;

	अगर (!cstate->save_fh.fh_dentry)
		वापस nfserr_nofilehandle;

	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->save_fh,
					    src_stateid, RD_STATE, src, शून्य);
	अगर (status) अणु
		dprपूर्णांकk("NFSD: %s: couldn't process src stateid!\n", __func__);
		जाओ out;
	पूर्ण

	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					    dst_stateid, WR_STATE, dst, शून्य);
	अगर (status) अणु
		dprपूर्णांकk("NFSD: %s: couldn't process dst stateid!\n", __func__);
		जाओ out_put_src;
	पूर्ण

	/* fix up क्रम NFS-specअगरic error code */
	अगर (!S_ISREG(file_inode((*src)->nf_file)->i_mode) ||
	    !S_ISREG(file_inode((*dst)->nf_file)->i_mode)) अणु
		status = nfserr_wrong_type;
		जाओ out_put_dst;
	पूर्ण

out:
	वापस status;
out_put_dst:
	nfsd_file_put(*dst);
out_put_src:
	nfsd_file_put(*src);
	जाओ out;
पूर्ण

अटल __be32
nfsd4_clone(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_clone *clone = &u->clone;
	काष्ठा nfsd_file *src, *dst;
	__be32 status;

	status = nfsd4_verअगरy_copy(rqstp, cstate, &clone->cl_src_stateid, &src,
				   &clone->cl_dst_stateid, &dst);
	अगर (status)
		जाओ out;

	status = nfsd4_clone_file_range(src, clone->cl_src_pos,
			dst, clone->cl_dst_pos, clone->cl_count,
			EX_ISSYNC(cstate->current_fh.fh_export));

	nfsd_file_put(dst);
	nfsd_file_put(src);
out:
	वापस status;
पूर्ण

व्योम nfs4_put_copy(काष्ठा nfsd4_copy *copy)
अणु
	अगर (!refcount_dec_and_test(&copy->refcount))
		वापस;
	kमुक्त(copy);
पूर्ण

अटल bool
check_and_set_stop_copy(काष्ठा nfsd4_copy *copy)
अणु
	bool value;

	spin_lock(&copy->cp_clp->async_lock);
	value = copy->stopped;
	अगर (!copy->stopped)
		copy->stopped = true;
	spin_unlock(&copy->cp_clp->async_lock);
	वापस value;
पूर्ण

अटल व्योम nfsd4_stop_copy(काष्ठा nfsd4_copy *copy)
अणु
	/* only 1 thपढ़ो should stop the copy */
	अगर (!check_and_set_stop_copy(copy))
		kthपढ़ो_stop(copy->copy_task);
	nfs4_put_copy(copy);
पूर्ण

अटल काष्ठा nfsd4_copy *nfsd4_get_copy(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd4_copy *copy = शून्य;

	spin_lock(&clp->async_lock);
	अगर (!list_empty(&clp->async_copies)) अणु
		copy = list_first_entry(&clp->async_copies, काष्ठा nfsd4_copy,
					copies);
		refcount_inc(&copy->refcount);
	पूर्ण
	spin_unlock(&clp->async_lock);
	वापस copy;
पूर्ण

व्योम nfsd4_shutकरोwn_copy(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd4_copy *copy;

	जबतक ((copy = nfsd4_get_copy(clp)) != शून्य)
		nfsd4_stop_copy(copy);
पूर्ण
#अगर_घोषित CONFIG_NFSD_V4_2_INTER_SSC

बाह्य काष्ठा file *nfs42_ssc_खोलो(काष्ठा vfsmount *ss_mnt,
				   काष्ठा nfs_fh *src_fh,
				   nfs4_stateid *stateid);
बाह्य व्योम nfs42_ssc_बंद(काष्ठा file *filep);

बाह्य व्योम nfs_sb_deactive(काष्ठा super_block *sb);

#घोषणा NFSD42_INTERSSC_MOUNTOPS "vers=4.2,addr=%s,sec=sys"

/*
 * Support one copy source server क्रम now.
 */
अटल __be32
nfsd4_पूर्णांकerssc_connect(काष्ठा nl4_server *nss, काष्ठा svc_rqst *rqstp,
		       काष्ठा vfsmount **mount)
अणु
	काष्ठा file_प्रणाली_type *type;
	काष्ठा vfsmount *ss_mnt;
	काष्ठा nfs42_netaddr *naddr;
	काष्ठा sockaddr_storage पंचांगp_addr;
	माप_प्रकार पंचांगp_addrlen, match_netid_len = 3;
	अक्षर *startsep = "", *endsep = "", *match_netid = "tcp";
	अक्षर *ipaddr, *dev_name, *raw_data;
	पूर्णांक len, raw_len;
	__be32 status = nfserr_inval;

	naddr = &nss->u.nl4_addr;
	पंचांगp_addrlen = rpc_uaddr2sockaddr(SVC_NET(rqstp), naddr->addr,
					 naddr->addr_len,
					 (काष्ठा sockaddr *)&पंचांगp_addr,
					 माप(पंचांगp_addr));
	अगर (पंचांगp_addrlen == 0)
		जाओ out_err;

	अगर (पंचांगp_addr.ss_family == AF_INET6) अणु
		startsep = "[";
		endsep = "]";
		match_netid = "tcp6";
		match_netid_len = 4;
	पूर्ण

	अगर (naddr->netid_len != match_netid_len ||
		म_भेदन(naddr->netid, match_netid, naddr->netid_len))
		जाओ out_err;

	/* Conकाष्ठा the raw data क्रम the vfs_kern_mount call */
	len = RPC_MAX_ADDRBUFLEN + 1;
	ipaddr = kzalloc(len, GFP_KERNEL);
	अगर (!ipaddr)
		जाओ out_err;

	rpc_ntop((काष्ठा sockaddr *)&पंचांगp_addr, ipaddr, len);

	/* 2 क्रम ipv6 endsep and startsep. 3 क्रम ":/" and trailing '/0'*/

	raw_len = म_माप(NFSD42_INTERSSC_MOUNTOPS) + म_माप(ipaddr);
	raw_data = kzalloc(raw_len, GFP_KERNEL);
	अगर (!raw_data)
		जाओ out_मुक्त_ipaddr;

	snम_लिखो(raw_data, raw_len, NFSD42_INTERSSC_MOUNTOPS, ipaddr);

	status = nfserr_nodev;
	type = get_fs_type("nfs");
	अगर (!type)
		जाओ out_मुक्त_rawdata;

	/* Set the server:<export> क्रम the vfs_kern_mount call */
	dev_name = kzalloc(len + 5, GFP_KERNEL);
	अगर (!dev_name)
		जाओ out_मुक्त_rawdata;
	snम_लिखो(dev_name, len + 5, "%s%s%s:/", startsep, ipaddr, endsep);

	/* Use an 'internal' mount: SB_KERNMOUNT -> MNT_INTERNAL */
	ss_mnt = vfs_kern_mount(type, SB_KERNMOUNT, dev_name, raw_data);
	module_put(type->owner);
	अगर (IS_ERR(ss_mnt))
		जाओ out_मुक्त_devname;

	status = 0;
	*mount = ss_mnt;

out_मुक्त_devname:
	kमुक्त(dev_name);
out_मुक्त_rawdata:
	kमुक्त(raw_data);
out_मुक्त_ipaddr:
	kमुक्त(ipaddr);
out_err:
	वापस status;
पूर्ण

अटल व्योम
nfsd4_पूर्णांकerssc_disconnect(काष्ठा vfsmount *ss_mnt)
अणु
	nfs_करो_sb_deactive(ss_mnt->mnt_sb);
	mntput(ss_mnt);
पूर्ण

/*
 * Verअगरy COPY destination stateid.
 *
 * Connect to the source server with NFSv4.1.
 * Create the source काष्ठा file क्रम nfsd_copy_range.
 * Called with COPY cstate:
 *    SAVED_FH: source filehandle
 *    CURRENT_FH: destination filehandle
 */
अटल __be32
nfsd4_setup_पूर्णांकer_ssc(काष्ठा svc_rqst *rqstp,
		      काष्ठा nfsd4_compound_state *cstate,
		      काष्ठा nfsd4_copy *copy, काष्ठा vfsmount **mount)
अणु
	काष्ठा svc_fh *s_fh = शून्य;
	stateid_t *s_stid = &copy->cp_src_stateid;
	__be32 status = nfserr_inval;

	/* Verअगरy the destination stateid and set dst काष्ठा file*/
	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					    &copy->cp_dst_stateid,
					    WR_STATE, &copy->nf_dst, शून्य);
	अगर (status)
		जाओ out;

	status = nfsd4_पूर्णांकerssc_connect(&copy->cp_src, rqstp, mount);
	अगर (status)
		जाओ out;

	s_fh = &cstate->save_fh;

	copy->c_fh.size = s_fh->fh_handle.fh_size;
	स_नकल(copy->c_fh.data, &s_fh->fh_handle.fh_base, copy->c_fh.size);
	copy->stateid.seqid = cpu_to_be32(s_stid->si_generation);
	स_नकल(copy->stateid.other, (व्योम *)&s_stid->si_opaque,
	       माप(stateid_opaque_t));

	status = 0;
out:
	वापस status;
पूर्ण

अटल व्योम
nfsd4_cleanup_पूर्णांकer_ssc(काष्ठा vfsmount *ss_mnt, काष्ठा nfsd_file *src,
			काष्ठा nfsd_file *dst)
अणु
	nfs42_ssc_बंद(src->nf_file);
	fput(src->nf_file);
	nfsd_file_put(dst);
	mntput(ss_mnt);
पूर्ण

#अन्यथा /* CONFIG_NFSD_V4_2_INTER_SSC */

अटल __be32
nfsd4_setup_पूर्णांकer_ssc(काष्ठा svc_rqst *rqstp,
		      काष्ठा nfsd4_compound_state *cstate,
		      काष्ठा nfsd4_copy *copy,
		      काष्ठा vfsmount **mount)
अणु
	*mount = शून्य;
	वापस nfserr_inval;
पूर्ण

अटल व्योम
nfsd4_cleanup_पूर्णांकer_ssc(काष्ठा vfsmount *ss_mnt, काष्ठा nfsd_file *src,
			काष्ठा nfsd_file *dst)
अणु
पूर्ण

अटल व्योम
nfsd4_पूर्णांकerssc_disconnect(काष्ठा vfsmount *ss_mnt)
अणु
पूर्ण

अटल काष्ठा file *nfs42_ssc_खोलो(काष्ठा vfsmount *ss_mnt,
				   काष्ठा nfs_fh *src_fh,
				   nfs4_stateid *stateid)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_V4_2_INTER_SSC */

अटल __be32
nfsd4_setup_पूर्णांकra_ssc(काष्ठा svc_rqst *rqstp,
		      काष्ठा nfsd4_compound_state *cstate,
		      काष्ठा nfsd4_copy *copy)
अणु
	वापस nfsd4_verअगरy_copy(rqstp, cstate, &copy->cp_src_stateid,
				 &copy->nf_src, &copy->cp_dst_stateid,
				 &copy->nf_dst);
पूर्ण

अटल व्योम
nfsd4_cleanup_पूर्णांकra_ssc(काष्ठा nfsd_file *src, काष्ठा nfsd_file *dst)
अणु
	nfsd_file_put(src);
	nfsd_file_put(dst);
पूर्ण

अटल व्योम nfsd4_cb_offload_release(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfsd4_copy *copy = container_of(cb, काष्ठा nfsd4_copy, cp_cb);

	nfs4_put_copy(copy);
पूर्ण

अटल पूर्णांक nfsd4_cb_offload_करोne(काष्ठा nfsd4_callback *cb,
				 काष्ठा rpc_task *task)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा nfsd4_callback_ops nfsd4_cb_offload_ops = अणु
	.release = nfsd4_cb_offload_release,
	.करोne = nfsd4_cb_offload_करोne
पूर्ण;

अटल व्योम nfsd4_init_copy_res(काष्ठा nfsd4_copy *copy, bool sync)
अणु
	copy->cp_res.wr_stable_how = NFS_UNSTABLE;
	copy->cp_synchronous = sync;
	gen_boot_verअगरier(&copy->cp_res.wr_verअगरier, copy->cp_clp->net);
पूर्ण

अटल sमाप_प्रकार _nfsd_copy_file_range(काष्ठा nfsd4_copy *copy)
अणु
	sमाप_प्रकार bytes_copied = 0;
	u64 bytes_total = copy->cp_count;
	u64 src_pos = copy->cp_src_pos;
	u64 dst_pos = copy->cp_dst_pos;

	/* See RFC 7862 p.67: */
	अगर (bytes_total == 0)
		bytes_total = ULदीर्घ_उच्च;
	करो अणु
		अगर (kthपढ़ो_should_stop())
			अवरोध;
		bytes_copied = nfsd_copy_file_range(copy->nf_src->nf_file,
				src_pos, copy->nf_dst->nf_file, dst_pos,
				bytes_total);
		अगर (bytes_copied <= 0)
			अवरोध;
		bytes_total -= bytes_copied;
		copy->cp_res.wr_bytes_written += bytes_copied;
		src_pos += bytes_copied;
		dst_pos += bytes_copied;
	पूर्ण जबतक (bytes_total > 0 && !copy->cp_synchronous);
	वापस bytes_copied;
पूर्ण

अटल __be32 nfsd4_करो_copy(काष्ठा nfsd4_copy *copy, bool sync)
अणु
	__be32 status;
	sमाप_प्रकार bytes;

	bytes = _nfsd_copy_file_range(copy);
	/* क्रम async copy, we ignore the error, client can always retry
	 * to get the error
	 */
	अगर (bytes < 0 && !copy->cp_res.wr_bytes_written)
		status = nfsत्रुटि_सं(bytes);
	अन्यथा अणु
		nfsd4_init_copy_res(copy, sync);
		status = nfs_ok;
	पूर्ण

	अगर (!copy->cp_पूर्णांकra) /* Inter server SSC */
		nfsd4_cleanup_पूर्णांकer_ssc(copy->ss_mnt, copy->nf_src,
					copy->nf_dst);
	अन्यथा
		nfsd4_cleanup_पूर्णांकra_ssc(copy->nf_src, copy->nf_dst);

	वापस status;
पूर्ण

अटल व्योम dup_copy_fields(काष्ठा nfsd4_copy *src, काष्ठा nfsd4_copy *dst)
अणु
	dst->cp_src_pos = src->cp_src_pos;
	dst->cp_dst_pos = src->cp_dst_pos;
	dst->cp_count = src->cp_count;
	dst->cp_synchronous = src->cp_synchronous;
	स_नकल(&dst->cp_res, &src->cp_res, माप(src->cp_res));
	स_नकल(&dst->fh, &src->fh, माप(src->fh));
	dst->cp_clp = src->cp_clp;
	dst->nf_dst = nfsd_file_get(src->nf_dst);
	dst->cp_पूर्णांकra = src->cp_पूर्णांकra;
	अगर (src->cp_पूर्णांकra) /* क्रम पूर्णांकer, file_src करोesn't exist yet */
		dst->nf_src = nfsd_file_get(src->nf_src);

	स_नकल(&dst->cp_stateid, &src->cp_stateid, माप(src->cp_stateid));
	स_नकल(&dst->cp_src, &src->cp_src, माप(काष्ठा nl4_server));
	स_नकल(&dst->stateid, &src->stateid, माप(src->stateid));
	स_नकल(&dst->c_fh, &src->c_fh, माप(src->c_fh));
	dst->ss_mnt = src->ss_mnt;
पूर्ण

अटल व्योम cleanup_async_copy(काष्ठा nfsd4_copy *copy)
अणु
	nfs4_मुक्त_copy_state(copy);
	nfsd_file_put(copy->nf_dst);
	अगर (copy->cp_पूर्णांकra)
		nfsd_file_put(copy->nf_src);
	spin_lock(&copy->cp_clp->async_lock);
	list_del(&copy->copies);
	spin_unlock(&copy->cp_clp->async_lock);
	nfs4_put_copy(copy);
पूर्ण

अटल पूर्णांक nfsd4_करो_async_copy(व्योम *data)
अणु
	काष्ठा nfsd4_copy *copy = (काष्ठा nfsd4_copy *)data;
	काष्ठा nfsd4_copy *cb_copy;

	अगर (!copy->cp_पूर्णांकra) अणु /* Inter server SSC */
		copy->nf_src = kzalloc(माप(काष्ठा nfsd_file), GFP_KERNEL);
		अगर (!copy->nf_src) अणु
			copy->nfserr = nfserr_serverfault;
			nfsd4_पूर्णांकerssc_disconnect(copy->ss_mnt);
			जाओ करो_callback;
		पूर्ण
		copy->nf_src->nf_file = nfs42_ssc_खोलो(copy->ss_mnt, &copy->c_fh,
					      &copy->stateid);
		अगर (IS_ERR(copy->nf_src->nf_file)) अणु
			copy->nfserr = nfserr_offload_denied;
			nfsd4_पूर्णांकerssc_disconnect(copy->ss_mnt);
			जाओ करो_callback;
		पूर्ण
	पूर्ण

	copy->nfserr = nfsd4_करो_copy(copy, 0);
करो_callback:
	cb_copy = kzalloc(माप(काष्ठा nfsd4_copy), GFP_KERNEL);
	अगर (!cb_copy)
		जाओ out;
	refcount_set(&cb_copy->refcount, 1);
	स_नकल(&cb_copy->cp_res, &copy->cp_res, माप(copy->cp_res));
	cb_copy->cp_clp = copy->cp_clp;
	cb_copy->nfserr = copy->nfserr;
	स_नकल(&cb_copy->fh, &copy->fh, माप(copy->fh));
	nfsd4_init_cb(&cb_copy->cp_cb, cb_copy->cp_clp,
			&nfsd4_cb_offload_ops, NFSPROC4_CLNT_CB_OFFLOAD);
	nfsd4_run_cb(&cb_copy->cp_cb);
out:
	अगर (!copy->cp_पूर्णांकra)
		kमुक्त(copy->nf_src);
	cleanup_async_copy(copy);
	वापस 0;
पूर्ण

अटल __be32
nfsd4_copy(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_copy *copy = &u->copy;
	__be32 status;
	काष्ठा nfsd4_copy *async_copy = शून्य;

	अगर (!copy->cp_पूर्णांकra) अणु /* Inter server SSC */
		अगर (!पूर्णांकer_copy_offload_enable || copy->cp_synchronous) अणु
			status = nfserr_notsupp;
			जाओ out;
		पूर्ण
		status = nfsd4_setup_पूर्णांकer_ssc(rqstp, cstate, copy,
				&copy->ss_mnt);
		अगर (status)
			वापस nfserr_offload_denied;
	पूर्ण अन्यथा अणु
		status = nfsd4_setup_पूर्णांकra_ssc(rqstp, cstate, copy);
		अगर (status)
			वापस status;
	पूर्ण

	copy->cp_clp = cstate->clp;
	स_नकल(&copy->fh, &cstate->current_fh.fh_handle,
		माप(काष्ठा knfsd_fh));
	अगर (!copy->cp_synchronous) अणु
		काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

		status = nfsत्रुटि_सं(-ENOMEM);
		async_copy = kzalloc(माप(काष्ठा nfsd4_copy), GFP_KERNEL);
		अगर (!async_copy)
			जाओ out_err;
		अगर (!nfs4_init_copy_state(nn, copy))
			जाओ out_err;
		refcount_set(&async_copy->refcount, 1);
		स_नकल(&copy->cp_res.cb_stateid, &copy->cp_stateid.stid,
			माप(copy->cp_res.cb_stateid));
		dup_copy_fields(copy, async_copy);
		async_copy->copy_task = kthपढ़ो_create(nfsd4_करो_async_copy,
				async_copy, "%s", "copy thread");
		अगर (IS_ERR(async_copy->copy_task))
			जाओ out_err;
		spin_lock(&async_copy->cp_clp->async_lock);
		list_add(&async_copy->copies,
				&async_copy->cp_clp->async_copies);
		spin_unlock(&async_copy->cp_clp->async_lock);
		wake_up_process(async_copy->copy_task);
		status = nfs_ok;
	पूर्ण अन्यथा अणु
		status = nfsd4_करो_copy(copy, 1);
	पूर्ण
out:
	वापस status;
out_err:
	अगर (async_copy)
		cleanup_async_copy(async_copy);
	status = nfsत्रुटि_सं(-ENOMEM);
	अगर (!copy->cp_पूर्णांकra)
		nfsd4_पूर्णांकerssc_disconnect(copy->ss_mnt);
	जाओ out;
पूर्ण

काष्ठा nfsd4_copy *
find_async_copy(काष्ठा nfs4_client *clp, stateid_t *stateid)
अणु
	काष्ठा nfsd4_copy *copy;

	spin_lock(&clp->async_lock);
	list_क्रम_each_entry(copy, &clp->async_copies, copies) अणु
		अगर (स_भेद(&copy->cp_stateid.stid, stateid, NFS4_STATEID_SIZE))
			जारी;
		refcount_inc(&copy->refcount);
		spin_unlock(&clp->async_lock);
		वापस copy;
	पूर्ण
	spin_unlock(&clp->async_lock);
	वापस शून्य;
पूर्ण

अटल __be32
nfsd4_offload_cancel(काष्ठा svc_rqst *rqstp,
		     काष्ठा nfsd4_compound_state *cstate,
		     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_offload_status *os = &u->offload_status;
	काष्ठा nfsd4_copy *copy;
	काष्ठा nfs4_client *clp = cstate->clp;

	copy = find_async_copy(clp, &os->stateid);
	अगर (!copy) अणु
		काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

		वापस manage_cpntf_state(nn, &os->stateid, clp, शून्य);
	पूर्ण अन्यथा
		nfsd4_stop_copy(copy);

	वापस nfs_ok;
पूर्ण

अटल __be32
nfsd4_copy_notअगरy(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		  जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_copy_notअगरy *cn = &u->copy_notअगरy;
	__be32 status;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	काष्ठा nfs4_stid *stid;
	काष्ठा nfs4_cpntf_state *cps;
	काष्ठा nfs4_client *clp = cstate->clp;

	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					&cn->cpn_src_stateid, RD_STATE, शून्य,
					&stid);
	अगर (status)
		वापस status;

	cn->cpn_sec = nn->nfsd4_lease;
	cn->cpn_nsec = 0;

	status = nfsत्रुटि_सं(-ENOMEM);
	cps = nfs4_alloc_init_cpntf_state(nn, stid);
	अगर (!cps)
		जाओ out;
	स_नकल(&cn->cpn_cnr_stateid, &cps->cp_stateid.stid, माप(stateid_t));
	स_नकल(&cps->cp_p_stateid, &stid->sc_stateid, माप(stateid_t));
	स_नकल(&cps->cp_p_clid, &clp->cl_clientid, माप(clientid_t));

	/* For now, only वापस one server address in cpn_src, the
	 * address used by the client to connect to this server.
	 */
	cn->cpn_src.nl4_type = NL4_NETADDR;
	status = nfsd4_set_netaddr((काष्ठा sockaddr *)&rqstp->rq_daddr,
				 &cn->cpn_src.u.nl4_addr);
	WARN_ON_ONCE(status);
	अगर (status) अणु
		nfs4_put_cpntf_state(nn, cps);
		जाओ out;
	पूर्ण
out:
	nfs4_put_stid(stid);
	वापस status;
पूर्ण

अटल __be32
nfsd4_fallocate(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		काष्ठा nfsd4_fallocate *fallocate, पूर्णांक flags)
अणु
	__be32 status;
	काष्ठा nfsd_file *nf;

	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					    &fallocate->falloc_stateid,
					    WR_STATE, &nf, शून्य);
	अगर (status != nfs_ok) अणु
		dprपूर्णांकk("NFSD: nfsd4_fallocate: couldn't process stateid!\n");
		वापस status;
	पूर्ण

	status = nfsd4_vfs_fallocate(rqstp, &cstate->current_fh, nf->nf_file,
				     fallocate->falloc_offset,
				     fallocate->falloc_length,
				     flags);
	nfsd_file_put(nf);
	वापस status;
पूर्ण
अटल __be32
nfsd4_offload_status(काष्ठा svc_rqst *rqstp,
		     काष्ठा nfsd4_compound_state *cstate,
		     जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_offload_status *os = &u->offload_status;
	__be32 status = 0;
	काष्ठा nfsd4_copy *copy;
	काष्ठा nfs4_client *clp = cstate->clp;

	copy = find_async_copy(clp, &os->stateid);
	अगर (copy) अणु
		os->count = copy->cp_res.wr_bytes_written;
		nfs4_put_copy(copy);
	पूर्ण अन्यथा
		status = nfserr_bad_stateid;

	वापस status;
पूर्ण

अटल __be32
nfsd4_allocate(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	       जोड़ nfsd4_op_u *u)
अणु
	वापस nfsd4_fallocate(rqstp, cstate, &u->allocate, 0);
पूर्ण

अटल __be32
nfsd4_deallocate(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
		 जोड़ nfsd4_op_u *u)
अणु
	वापस nfsd4_fallocate(rqstp, cstate, &u->deallocate,
			       FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE);
पूर्ण

अटल __be32
nfsd4_seek(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_seek *seek = &u->seek;
	पूर्णांक whence;
	__be32 status;
	काष्ठा nfsd_file *nf;

	status = nfs4_preprocess_stateid_op(rqstp, cstate, &cstate->current_fh,
					    &seek->seek_stateid,
					    RD_STATE, &nf, शून्य);
	अगर (status) अणु
		dprपूर्णांकk("NFSD: nfsd4_seek: couldn't process stateid!\n");
		वापस status;
	पूर्ण

	चयन (seek->seek_whence) अणु
	हाल NFS4_CONTENT_DATA:
		whence = SEEK_DATA;
		अवरोध;
	हाल NFS4_CONTENT_HOLE:
		whence = SEEK_HOLE;
		अवरोध;
	शेष:
		status = nfserr_जोड़_notsupp;
		जाओ out;
	पूर्ण

	/*
	 * Note:  This call करोes change file->f_pos, but nothing in NFSD
	 *        should ever file->f_pos.
	 */
	seek->seek_pos = vfs_llseek(nf->nf_file, seek->seek_offset, whence);
	अगर (seek->seek_pos < 0)
		status = nfsत्रुटि_सं(seek->seek_pos);
	अन्यथा अगर (seek->seek_pos >= i_size_पढ़ो(file_inode(nf->nf_file)))
		seek->seek_eof = true;

out:
	nfsd_file_put(nf);
	वापस status;
पूर्ण

/* This routine never वापसs NFS_OK!  If there are no other errors, it
 * will वापस NFSERR_SAME or NFSERR_NOT_SAME depending on whether the
 * attributes matched.  VERIFY is implemented by mapping NFSERR_SAME
 * to NFS_OK after the call; NVERIFY by mapping NFSERR_NOT_SAME to NFS_OK.
 */
अटल __be32
_nfsd4_verअगरy(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     काष्ठा nfsd4_verअगरy *verअगरy)
अणु
	__be32 *buf, *p;
	पूर्णांक count;
	__be32 status;

	status = fh_verअगरy(rqstp, &cstate->current_fh, 0, NFSD_MAY_NOP);
	अगर (status)
		वापस status;

	status = check_attr_support(rqstp, cstate, verअगरy->ve_bmval, शून्य);
	अगर (status)
		वापस status;

	अगर ((verअगरy->ve_bmval[0] & FATTR4_WORD0_RDATTR_ERROR)
	    || (verअगरy->ve_bmval[1] & NFSD_WRITEONLY_ATTRS_WORD1))
		वापस nfserr_inval;
	अगर (verअगरy->ve_attrlen & 3)
		वापस nfserr_inval;

	/* count in words:
	 *   biपंचांगap_len(1) + biपंचांगap(2) + attr_len(1) = 4
	 */
	count = 4 + (verअगरy->ve_attrlen >> 2);
	buf = kदो_स्मृति(count << 2, GFP_KERNEL);
	अगर (!buf)
		वापस nfserr_jukebox;

	p = buf;
	status = nfsd4_encode_fattr_to_buf(&p, count, &cstate->current_fh,
				    cstate->current_fh.fh_export,
				    cstate->current_fh.fh_dentry,
				    verअगरy->ve_bmval,
				    rqstp, 0);
	/*
	 * If nfsd4_encode_fattr() ran out of space, assume that's because
	 * the attributes are दीर्घer (hence dअगरferent) than those given:
	 */
	अगर (status == nfserr_resource)
		status = nfserr_not_same;
	अगर (status)
		जाओ out_kमुक्त;

	/* skip biपंचांगap */
	p = buf + 1 + ntohl(buf[0]);
	status = nfserr_not_same;
	अगर (ntohl(*p++) != verअगरy->ve_attrlen)
		जाओ out_kमुक्त;
	अगर (!स_भेद(p, verअगरy->ve_attrval, verअगरy->ve_attrlen))
		status = nfserr_same;

out_kमुक्त:
	kमुक्त(buf);
	वापस status;
पूर्ण

अटल __be32
nfsd4_nverअगरy(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	      जोड़ nfsd4_op_u *u)
अणु
	__be32 status;

	status = _nfsd4_verअगरy(rqstp, cstate, &u->verअगरy);
	वापस status == nfserr_not_same ? nfs_ok : status;
पूर्ण

अटल __be32
nfsd4_verअगरy(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	     जोड़ nfsd4_op_u *u)
अणु
	__be32 status;

	status = _nfsd4_verअगरy(rqstp, cstate, &u->nverअगरy);
	वापस status == nfserr_same ? nfs_ok : status;
पूर्ण

#अगर_घोषित CONFIG_NFSD_PNFS
अटल स्थिर काष्ठा nfsd4_layout_ops *
nfsd4_layout_verअगरy(काष्ठा svc_export *exp, अचिन्हित पूर्णांक layout_type)
अणु
	अगर (!exp->ex_layout_types) अणु
		dprपूर्णांकk("%s: export does not support pNFS\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (layout_type >= LAYOUT_TYPE_MAX ||
	    !(exp->ex_layout_types & (1 << layout_type))) अणु
		dprपूर्णांकk("%s: layout type %d not supported\n",
			__func__, layout_type);
		वापस शून्य;
	पूर्ण

	वापस nfsd4_layout_ops[layout_type];
पूर्ण

अटल __be32
nfsd4_getdeviceinfo(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_getdeviceinfo *gdp = &u->getdeviceinfo;
	स्थिर काष्ठा nfsd4_layout_ops *ops;
	काष्ठा nfsd4_deviceid_map *map;
	काष्ठा svc_export *exp;
	__be32 nfserr;

	dprपूर्णांकk("%s: layout_type %u dev_id [0x%llx:0x%x] maxcnt %u\n",
	       __func__,
	       gdp->gd_layout_type,
	       gdp->gd_devid.fsid_idx, gdp->gd_devid.generation,
	       gdp->gd_maxcount);

	map = nfsd4_find_devid_map(gdp->gd_devid.fsid_idx);
	अगर (!map) अणु
		dprपूर्णांकk("%s: couldn't find device ID to export mapping!\n",
			__func__);
		वापस nfserr_noent;
	पूर्ण

	exp = rqst_exp_find(rqstp, map->fsid_type, map->fsid);
	अगर (IS_ERR(exp)) अणु
		dprपूर्णांकk("%s: could not find device id\n", __func__);
		वापस nfserr_noent;
	पूर्ण

	nfserr = nfserr_layoutunavailable;
	ops = nfsd4_layout_verअगरy(exp, gdp->gd_layout_type);
	अगर (!ops)
		जाओ out;

	nfserr = nfs_ok;
	अगर (gdp->gd_maxcount != 0) अणु
		nfserr = ops->proc_getdeviceinfo(exp->ex_path.mnt->mnt_sb,
				rqstp, cstate->clp, gdp);
	पूर्ण

	gdp->gd_notअगरy_types &= ops->notअगरy_types;
out:
	exp_put(exp);
	वापस nfserr;
पूर्ण

अटल व्योम
nfsd4_getdeviceinfo_release(जोड़ nfsd4_op_u *u)
अणु
	kमुक्त(u->getdeviceinfo.gd_device);
पूर्ण

अटल __be32
nfsd4_layoutget(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_layoutget *lgp = &u->layoutget;
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	स्थिर काष्ठा nfsd4_layout_ops *ops;
	काष्ठा nfs4_layout_stateid *ls;
	__be32 nfserr;
	पूर्णांक accmode = NFSD_MAY_READ_IF_EXEC;

	चयन (lgp->lg_seg.iomode) अणु
	हाल IOMODE_READ:
		accmode |= NFSD_MAY_READ;
		अवरोध;
	हाल IOMODE_RW:
		accmode |= NFSD_MAY_READ | NFSD_MAY_WRITE;
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid iomode %d\n",
			__func__, lgp->lg_seg.iomode);
		nfserr = nfserr_badiomode;
		जाओ out;
	पूर्ण

	nfserr = fh_verअगरy(rqstp, current_fh, 0, accmode);
	अगर (nfserr)
		जाओ out;

	nfserr = nfserr_layoutunavailable;
	ops = nfsd4_layout_verअगरy(current_fh->fh_export, lgp->lg_layout_type);
	अगर (!ops)
		जाओ out;

	/*
	 * Verअगरy minlength and range as per RFC5661:
	 *  o  If loga_length is less than loga_minlength,
	 *     the metadata server MUST वापस NFS4ERR_INVAL.
	 *  o  If the sum of loga_offset and loga_minlength exceeds
	 *     NFS4_UINT64_MAX, and loga_minlength is not
	 *     NFS4_UINT64_MAX, the error NFS4ERR_INVAL MUST result.
	 *  o  If the sum of loga_offset and loga_length exceeds
	 *     NFS4_UINT64_MAX, and loga_length is not NFS4_UINT64_MAX,
	 *     the error NFS4ERR_INVAL MUST result.
	 */
	nfserr = nfserr_inval;
	अगर (lgp->lg_seg.length < lgp->lg_minlength ||
	    (lgp->lg_minlength != NFS4_MAX_UINT64 &&
	     lgp->lg_minlength > NFS4_MAX_UINT64 - lgp->lg_seg.offset) ||
	    (lgp->lg_seg.length != NFS4_MAX_UINT64 &&
	     lgp->lg_seg.length > NFS4_MAX_UINT64 - lgp->lg_seg.offset))
		जाओ out;
	अगर (lgp->lg_seg.length == 0)
		जाओ out;

	nfserr = nfsd4_preprocess_layout_stateid(rqstp, cstate, &lgp->lg_sid,
						true, lgp->lg_layout_type, &ls);
	अगर (nfserr) अणु
		trace_nfsd_layout_get_lookup_fail(&lgp->lg_sid);
		जाओ out;
	पूर्ण

	nfserr = nfserr_recallconflict;
	अगर (atomic_पढ़ो(&ls->ls_stid.sc_file->fi_lo_recalls))
		जाओ out_put_stid;

	nfserr = ops->proc_layoutget(d_inode(current_fh->fh_dentry),
				     current_fh, lgp);
	अगर (nfserr)
		जाओ out_put_stid;

	nfserr = nfsd4_insert_layout(lgp, ls);

out_put_stid:
	mutex_unlock(&ls->ls_mutex);
	nfs4_put_stid(&ls->ls_stid);
out:
	वापस nfserr;
पूर्ण

अटल व्योम
nfsd4_layoutget_release(जोड़ nfsd4_op_u *u)
अणु
	kमुक्त(u->layoutget.lg_content);
पूर्ण

अटल __be32
nfsd4_layoutcommit(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_layoutcommit *lcp = &u->layoutcommit;
	स्थिर काष्ठा nfsd4_layout_seg *seg = &lcp->lc_seg;
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	स्थिर काष्ठा nfsd4_layout_ops *ops;
	loff_t new_size = lcp->lc_last_wr + 1;
	काष्ठा inode *inode;
	काष्ठा nfs4_layout_stateid *ls;
	__be32 nfserr;

	nfserr = fh_verअगरy(rqstp, current_fh, 0, NFSD_MAY_WRITE);
	अगर (nfserr)
		जाओ out;

	nfserr = nfserr_layoutunavailable;
	ops = nfsd4_layout_verअगरy(current_fh->fh_export, lcp->lc_layout_type);
	अगर (!ops)
		जाओ out;
	inode = d_inode(current_fh->fh_dentry);

	nfserr = nfserr_inval;
	अगर (new_size <= seg->offset) अणु
		dprपूर्णांकk("pnfsd: last write before layout segment\n");
		जाओ out;
	पूर्ण
	अगर (new_size > seg->offset + seg->length) अणु
		dprपूर्णांकk("pnfsd: last write beyond layout segment\n");
		जाओ out;
	पूर्ण
	अगर (!lcp->lc_newoffset && new_size > i_size_पढ़ो(inode)) अणु
		dprपूर्णांकk("pnfsd: layoutcommit beyond EOF\n");
		जाओ out;
	पूर्ण

	nfserr = nfsd4_preprocess_layout_stateid(rqstp, cstate, &lcp->lc_sid,
						false, lcp->lc_layout_type,
						&ls);
	अगर (nfserr) अणु
		trace_nfsd_layout_commit_lookup_fail(&lcp->lc_sid);
		/* fixup error code as per RFC5661 */
		अगर (nfserr == nfserr_bad_stateid)
			nfserr = nfserr_badlayout;
		जाओ out;
	पूर्ण

	/* LAYOUTCOMMIT करोes not require any serialization */
	mutex_unlock(&ls->ls_mutex);

	अगर (new_size > i_size_पढ़ो(inode)) अणु
		lcp->lc_size_chg = 1;
		lcp->lc_newsize = new_size;
	पूर्ण अन्यथा अणु
		lcp->lc_size_chg = 0;
	पूर्ण

	nfserr = ops->proc_layoutcommit(inode, lcp);
	nfs4_put_stid(&ls->ls_stid);
out:
	वापस nfserr;
पूर्ण

अटल __be32
nfsd4_layoutवापस(काष्ठा svc_rqst *rqstp,
		काष्ठा nfsd4_compound_state *cstate, जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_layoutवापस *lrp = &u->layoutवापस;
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	__be32 nfserr;

	nfserr = fh_verअगरy(rqstp, current_fh, 0, NFSD_MAY_NOP);
	अगर (nfserr)
		जाओ out;

	nfserr = nfserr_layoutunavailable;
	अगर (!nfsd4_layout_verअगरy(current_fh->fh_export, lrp->lr_layout_type))
		जाओ out;

	चयन (lrp->lr_seg.iomode) अणु
	हाल IOMODE_READ:
	हाल IOMODE_RW:
	हाल IOMODE_ANY:
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid iomode %d\n", __func__,
			lrp->lr_seg.iomode);
		nfserr = nfserr_inval;
		जाओ out;
	पूर्ण

	चयन (lrp->lr_वापस_type) अणु
	हाल RETURN_खाता:
		nfserr = nfsd4_वापस_file_layouts(rqstp, cstate, lrp);
		अवरोध;
	हाल RETURN_FSID:
	हाल RETURN_ALL:
		nfserr = nfsd4_वापस_client_layouts(rqstp, cstate, lrp);
		अवरोध;
	शेष:
		dprपूर्णांकk("%s: invalid return_type %d\n", __func__,
			lrp->lr_वापस_type);
		nfserr = nfserr_inval;
		अवरोध;
	पूर्ण
out:
	वापस nfserr;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

अटल __be32
nfsd4_getxattr(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	       जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_getxattr *getxattr = &u->getxattr;

	वापस nfsd_getxattr(rqstp, &cstate->current_fh,
			     getxattr->getxa_name, &getxattr->getxa_buf,
			     &getxattr->getxa_len);
पूर्ण

अटल __be32
nfsd4_setxattr(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_setxattr *setxattr = &u->setxattr;
	__be32 ret;

	अगर (खोलोs_in_grace(SVC_NET(rqstp)))
		वापस nfserr_grace;

	ret = nfsd_setxattr(rqstp, &cstate->current_fh, setxattr->setxa_name,
			    setxattr->setxa_buf, setxattr->setxa_len,
			    setxattr->setxa_flags);

	अगर (!ret)
		set_change_info(&setxattr->setxa_cinfo, &cstate->current_fh);

	वापस ret;
पूर्ण

अटल __be32
nfsd4_listxattrs(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	/*
	 * Get the entire list, then copy out only the user attributes
	 * in the encode function.
	 */
	वापस nfsd_listxattr(rqstp, &cstate->current_fh,
			     &u->listxattrs.lsxa_buf, &u->listxattrs.lsxa_len);
पूर्ण

अटल __be32
nfsd4_हटाओxattr(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_compound_state *cstate,
	   जोड़ nfsd4_op_u *u)
अणु
	काष्ठा nfsd4_हटाओxattr *हटाओxattr = &u->हटाओxattr;
	__be32 ret;

	अगर (खोलोs_in_grace(SVC_NET(rqstp)))
		वापस nfserr_grace;

	ret = nfsd_हटाओxattr(rqstp, &cstate->current_fh,
	    हटाओxattr->rmxa_name);

	अगर (!ret)
		set_change_info(&हटाओxattr->rmxa_cinfo, &cstate->current_fh);

	वापस ret;
पूर्ण

/*
 * शून्य call.
 */
अटल __be32
nfsd4_proc_null(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_success;
पूर्ण

अटल अंतरभूत व्योम nfsd4_increment_op_stats(u32 opnum)
अणु
	अगर (opnum >= FIRST_NFS4_OP && opnum <= LAST_NFS4_OP)
		percpu_counter_inc(&nfsdstats.counter[NFSD_STATS_NFS4_OP(opnum)]);
पूर्ण

अटल स्थिर काष्ठा nfsd4_operation nfsd4_ops[];

अटल स्थिर अक्षर *nfsd4_op_name(अचिन्हित opnum);

/*
 * Enक्रमce NFSv4.1 COMPOUND ordering rules:
 *
 * Also note, enक्रमced अन्यथाwhere:
 *	- SEQUENCE other than as first op results in
 *	  NFS4ERR_SEQUENCE_POS. (Enक्रमced in nfsd4_sequence().)
 *	- BIND_CONN_TO_SESSION must be the only op in its compound.
 *	  (Enक्रमced in nfsd4_bind_conn_to_session().)
 *	- DESTROY_SESSION must be the final operation in a compound, अगर
 *	  sessionid's in SEQUENCE and DESTROY_SESSION are the same.
 *	  (Enक्रमced in nfsd4_destroy_session().)
 */
अटल __be32 nfs41_check_op_ordering(काष्ठा nfsd4_compoundargs *args)
अणु
	काष्ठा nfsd4_op *first_op = &args->ops[0];

	/* These ordering requirements करोn't apply to NFSv4.0: */
	अगर (args->minorversion == 0)
		वापस nfs_ok;
	/* This is weird, but OK, not our problem: */
	अगर (args->opcnt == 0)
		वापस nfs_ok;
	अगर (first_op->status == nfserr_op_illegal)
		वापस nfs_ok;
	अगर (!(nfsd4_ops[first_op->opnum].op_flags & ALLOWED_AS_FIRST_OP))
		वापस nfserr_op_not_in_session;
	अगर (first_op->opnum == OP_SEQUENCE)
		वापस nfs_ok;
	/*
	 * So first_op is something allowed outside a session, like
	 * EXCHANGE_ID; but then it has to be the only op in the
	 * compound:
	 */
	अगर (args->opcnt != 1)
		वापस nfserr_not_only_op;
	वापस nfs_ok;
पूर्ण

स्थिर काष्ठा nfsd4_operation *OPDESC(काष्ठा nfsd4_op *op)
अणु
	वापस &nfsd4_ops[op->opnum];
पूर्ण

bool nfsd4_cache_this_op(काष्ठा nfsd4_op *op)
अणु
	अगर (op->opnum == OP_ILLEGAL)
		वापस false;
	वापस OPDESC(op)->op_flags & OP_CACHEME;
पूर्ण

अटल bool need_wrongsec_check(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा nfsd4_compoundargs *argp = rqstp->rq_argp;
	काष्ठा nfsd4_op *this = &argp->ops[resp->opcnt - 1];
	काष्ठा nfsd4_op *next = &argp->ops[resp->opcnt];
	स्थिर काष्ठा nfsd4_operation *thisd = OPDESC(this);
	स्थिर काष्ठा nfsd4_operation *nextd;

	/*
	 * Most ops check wronsec on our own; only the putfh-like ops
	 * have special rules.
	 */
	अगर (!(thisd->op_flags & OP_IS_PUTFH_LIKE))
		वापस false;
	/*
	 * rfc 5661 2.6.3.1.1.6: करोn't bother erroring out a
	 * put-filehandle operation अगर we're not going to use the
	 * result:
	 */
	अगर (argp->opcnt == resp->opcnt)
		वापस false;
	अगर (next->opnum == OP_ILLEGAL)
		वापस false;
	nextd = OPDESC(next);
	/*
	 * Rest of 2.6.3.1.1: certain operations will वापस WRONGSEC
	 * errors themselves as necessary; others should check क्रम them
	 * now:
	 */
	वापस !(nextd->op_flags & OP_HANDLES_WRONGSEC);
पूर्ण

#अगर_घोषित CONFIG_NFSD_V4_2_INTER_SSC
अटल व्योम
check_अगर_stalefh_allowed(काष्ठा nfsd4_compoundargs *args)
अणु
	काष्ठा nfsd4_op	*op, *current_op = शून्य, *saved_op = शून्य;
	काष्ठा nfsd4_copy *copy;
	काष्ठा nfsd4_putfh *putfh;
	पूर्णांक i;

	/* traverse all operation and अगर it's a COPY compound, mark the
	 * source filehandle to skip verअगरication
	 */
	क्रम (i = 0; i < args->opcnt; i++) अणु
		op = &args->ops[i];
		अगर (op->opnum == OP_PUTFH)
			current_op = op;
		अन्यथा अगर (op->opnum == OP_SAVEFH)
			saved_op = current_op;
		अन्यथा अगर (op->opnum == OP_RESTOREFH)
			current_op = saved_op;
		अन्यथा अगर (op->opnum == OP_COPY) अणु
			copy = (काष्ठा nfsd4_copy *)&op->u;
			अगर (!saved_op) अणु
				op->status = nfserr_nofilehandle;
				वापस;
			पूर्ण
			putfh = (काष्ठा nfsd4_putfh *)&saved_op->u;
			अगर (!copy->cp_पूर्णांकra)
				putfh->no_verअगरy = true;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम
check_अगर_stalefh_allowed(काष्ठा nfsd4_compoundargs *args)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * COMPOUND call.
 */
अटल __be32
nfsd4_proc_compound(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd4_compoundargs *args = rqstp->rq_argp;
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा nfsd4_op	*op;
	काष्ठा nfsd4_compound_state *cstate = &resp->cstate;
	काष्ठा svc_fh *current_fh = &cstate->current_fh;
	काष्ठा svc_fh *save_fh = &cstate->save_fh;
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	__be32		status;

	resp->xdr = &rqstp->rq_res_stream;

	/* reserve space क्रम: NFS status code */
	xdr_reserve_space(resp->xdr, XDR_UNIT);

	resp->tagp = resp->xdr->p;
	/* reserve space क्रम: taglen, tag, and opcnt */
	xdr_reserve_space(resp->xdr, XDR_UNIT * 2 + args->taglen);
	resp->taglen = args->taglen;
	resp->tag = args->tag;
	resp->rqstp = rqstp;
	cstate->minorversion = args->minorversion;
	fh_init(current_fh, NFS4_FHSIZE);
	fh_init(save_fh, NFS4_FHSIZE);
	/*
	 * Don't use the deferral mechanism क्रम NFSv4; compounds make it
	 * too hard to aव्योम non-idempotency problems.
	 */
	clear_bit(RQ_USEDEFERRAL, &rqstp->rq_flags);

	/*
	 * According to RFC3010, this takes precedence over all other errors.
	 */
	status = nfserr_minor_vers_mismatch;
	अगर (nfsd_minorversion(nn, args->minorversion, NFSD_TEST) <= 0)
		जाओ out;
	status = nfserr_resource;
	अगर (args->opcnt > NFSD_MAX_OPS_PER_COMPOUND)
		जाओ out;

	status = nfs41_check_op_ordering(args);
	अगर (status) अणु
		op = &args->ops[0];
		op->status = status;
		resp->opcnt = 1;
		जाओ encode_op;
	पूर्ण
	check_अगर_stalefh_allowed(args);

	rqstp->rq_lease_अवरोधer = (व्योम **)&cstate->clp;

	trace_nfsd_compound(rqstp, args->opcnt);
	जबतक (!status && resp->opcnt < args->opcnt) अणु
		op = &args->ops[resp->opcnt++];

		/*
		 * The XDR decode routines may have pre-set op->status;
		 * क्रम example, अगर there is a miscellaneous XDR error
		 * it will be set to nfserr_bad_xdr.
		 */
		अगर (op->status) अणु
			अगर (op->opnum == OP_OPEN)
				op->status = nfsd4_खोलो_omfg(rqstp, cstate, op);
			जाओ encode_op;
		पूर्ण
		अगर (!current_fh->fh_dentry &&
				!HAS_FH_FLAG(current_fh, NFSD4_FH_FOREIGN)) अणु
			अगर (!(op->opdesc->op_flags & ALLOWED_WITHOUT_FH)) अणु
				op->status = nfserr_nofilehandle;
				जाओ encode_op;
			पूर्ण
		पूर्ण अन्यथा अगर (current_fh->fh_export &&
			   current_fh->fh_export->ex_fslocs.migrated &&
			  !(op->opdesc->op_flags & ALLOWED_ON_ABSENT_FS)) अणु
			op->status = nfserr_moved;
			जाओ encode_op;
		पूर्ण

		fh_clear_wcc(current_fh);

		/* If op is non-idempotent */
		अगर (op->opdesc->op_flags & OP_MODIFIES_SOMETHING) अणु
			/*
			 * Don't execute this op if we couldn't encode a
			 * succesful reply:
			 */
			u32 plen = op->opdesc->op_rsize_bop(rqstp, op);
			/*
			 * Plus अगर there's another operation, make sure
			 * we'll have space to at least encode an error:
			 */
			अगर (resp->opcnt < args->opcnt)
				plen += COMPOUND_ERR_SLACK_SPACE;
			op->status = nfsd4_check_resp_size(resp, plen);
		पूर्ण

		अगर (op->status)
			जाओ encode_op;

		अगर (op->opdesc->op_get_currentstateid)
			op->opdesc->op_get_currentstateid(cstate, &op->u);
		op->status = op->opdesc->op_func(rqstp, cstate, &op->u);

		/* Only from SEQUENCE */
		अगर (cstate->status == nfserr_replay_cache) अणु
			dprपूर्णांकk("%s NFS4.1 replay from cache\n", __func__);
			status = op->status;
			जाओ out;
		पूर्ण
		अगर (!op->status) अणु
			अगर (op->opdesc->op_set_currentstateid)
				op->opdesc->op_set_currentstateid(cstate, &op->u);

			अगर (op->opdesc->op_flags & OP_CLEAR_STATEID)
				clear_current_stateid(cstate);

			अगर (current_fh->fh_export &&
					need_wrongsec_check(rqstp))
				op->status = check_nfsd_access(current_fh->fh_export, rqstp);
		पूर्ण
encode_op:
		अगर (op->status == nfserr_replay_me) अणु
			op->replay = &cstate->replay_owner->so_replay;
			nfsd4_encode_replay(resp->xdr, op);
			status = op->status = op->replay->rp_status;
		पूर्ण अन्यथा अणु
			nfsd4_encode_operation(resp, op);
			status = op->status;
		पूर्ण

		trace_nfsd_compound_status(args->opcnt, resp->opcnt, status,
					   nfsd4_op_name(op->opnum));

		nfsd4_cstate_clear_replay(cstate);
		nfsd4_increment_op_stats(op->opnum);
	पूर्ण

	fh_put(current_fh);
	fh_put(save_fh);
	BUG_ON(cstate->replay_owner);
out:
	cstate->status = status;
	/* Reset deferral mechanism क्रम RPC deferrals */
	set_bit(RQ_USEDEFERRAL, &rqstp->rq_flags);
	वापस rpc_success;
पूर्ण

#घोषणा op_encode_hdr_size		(2)
#घोषणा op_encode_stateid_maxsz		(XDR_QUADLEN(NFS4_STATEID_SIZE))
#घोषणा op_encode_verअगरier_maxsz	(XDR_QUADLEN(NFS4_VERIFIER_SIZE))
#घोषणा op_encode_change_info_maxsz	(5)
#घोषणा nfs4_fattr_biपंचांगap_maxsz		(4)

/* We'll fall back on वापसing no lockowner अगर run out of space: */
#घोषणा op_encode_lockowner_maxsz	(0)
#घोषणा op_encode_lock_denied_maxsz	(8 + op_encode_lockowner_maxsz)

#घोषणा nfs4_owner_maxsz		(1 + XDR_QUADLEN(IDMAP_NAMESZ))

#घोषणा op_encode_ace_maxsz		(3 + nfs4_owner_maxsz)
#घोषणा op_encode_delegation_maxsz	(1 + op_encode_stateid_maxsz + 1 + \
					 op_encode_ace_maxsz)

#घोषणा op_encode_channel_attrs_maxsz	(6 + 1 + 1)

अटल अंतरभूत u32 nfsd4_only_status_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_status_stateid_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_stateid_maxsz)* माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_access_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	/* ac_supported, ac_resp_access */
	वापस (op_encode_hdr_size + 2)* माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_commit_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_verअगरier_maxsz) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_create_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_change_info_maxsz
		+ nfs4_fattr_biपंचांगap_maxsz) * माप(__be32);
पूर्ण

/*
 * Note since this is an idempotent operation we won't insist on failing
 * the op prematurely अगर the estimate is too large.  We may turn off splice
 * पढ़ोs unnecessarily.
 */
अटल अंतरभूत u32 nfsd4_getattr_rsize(काष्ठा svc_rqst *rqstp,
				      काष्ठा nfsd4_op *op)
अणु
	u32 *bmap = op->u.getattr.ga_bmval;
	u32 bmap0 = bmap[0], bmap1 = bmap[1], bmap2 = bmap[2];
	u32 ret = 0;

	अगर (bmap0 & FATTR4_WORD0_ACL)
		वापस svc_max_payload(rqstp);
	अगर (bmap0 & FATTR4_WORD0_FS_LOCATIONS)
		वापस svc_max_payload(rqstp);

	अगर (bmap1 & FATTR4_WORD1_OWNER) अणु
		ret += IDMAP_NAMESZ + 4;
		bmap1 &= ~FATTR4_WORD1_OWNER;
	पूर्ण
	अगर (bmap1 & FATTR4_WORD1_OWNER_GROUP) अणु
		ret += IDMAP_NAMESZ + 4;
		bmap1 &= ~FATTR4_WORD1_OWNER_GROUP;
	पूर्ण
	अगर (bmap0 & FATTR4_WORD0_खाताHANDLE) अणु
		ret += NFS4_FHSIZE + 4;
		bmap0 &= ~FATTR4_WORD0_खाताHANDLE;
	पूर्ण
	अगर (bmap2 & FATTR4_WORD2_SECURITY_LABEL) अणु
		ret += NFS4_MAXLABELLEN + 12;
		bmap2 &= ~FATTR4_WORD2_SECURITY_LABEL;
	पूर्ण
	/*
	 * Largest of reमुख्यing attributes are 16 bytes (e.g.,
	 * supported_attributes)
	 */
	ret += 16 * (hweight32(bmap0) + hweight32(bmap1) + hweight32(bmap2));
	/* biपंचांगask, length */
	ret += 20;
	वापस ret;
पूर्ण

अटल अंतरभूत u32 nfsd4_getfh_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 1) * माप(__be32) + NFS4_FHSIZE;
पूर्ण

अटल अंतरभूत u32 nfsd4_link_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_change_info_maxsz)
		* माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_lock_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_lock_denied_maxsz)
		* माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_खोलो_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_stateid_maxsz
		+ op_encode_change_info_maxsz + 1
		+ nfs4_fattr_biपंचांगap_maxsz
		+ op_encode_delegation_maxsz) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_पढ़ो_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	u32 maxcount = 0, rlen = 0;

	maxcount = svc_max_payload(rqstp);
	rlen = min(op->u.पढ़ो.rd_length, maxcount);

	वापस (op_encode_hdr_size + 2 + XDR_QUADLEN(rlen)) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_पढ़ो_plus_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	u32 maxcount = svc_max_payload(rqstp);
	u32 rlen = min(op->u.पढ़ो.rd_length, maxcount);
	/*
	 * If we detect that the file changed during hole encoding, then we
	 * recover by encoding the reमुख्यing reply as data. This means we need
	 * to set aside enough room to encode two data segments.
	 */
	u32 seg_len = 2 * (1 + 2 + 1);

	वापस (op_encode_hdr_size + 2 + seg_len + XDR_QUADLEN(rlen)) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_सूची_पढ़ो_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	u32 maxcount = 0, rlen = 0;

	maxcount = svc_max_payload(rqstp);
	rlen = min(op->u.सूची_पढ़ो.rd_maxcount, maxcount);

	वापस (op_encode_hdr_size + op_encode_verअगरier_maxsz +
		XDR_QUADLEN(rlen)) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_पढ़ोlink_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 1) * माप(__be32) + PAGE_SIZE;
पूर्ण

अटल अंतरभूत u32 nfsd4_हटाओ_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_change_info_maxsz)
		* माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_नाम_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_change_info_maxsz
		+ op_encode_change_info_maxsz) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_sequence_rsize(काष्ठा svc_rqst *rqstp,
				       काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size
		+ XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + 5) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_test_stateid_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 1 + op->u.test_stateid.ts_num_ids)
		* माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_setattr_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + nfs4_fattr_biपंचांगap_maxsz) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_secinfo_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + RPC_AUTH_MAXFLAVOR *
		(4 + XDR_QUADLEN(GSS_OID_MAX_LEN))) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_setclientid_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 2 + XDR_QUADLEN(NFS4_VERIFIER_SIZE)) *
								माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_ग_लिखो_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 2 + op_encode_verअगरier_maxsz) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_exchange_id_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 2 + 1 + /* eir_clientid, eir_sequenceid */\
		1 + 1 + /* eir_flags, spr_how */\
		4 + /* spo_must_enक्रमce & _allow with biपंचांगap */\
		2 + /*eir_server_owner.so_minor_id */\
		/* eir_server_owner.so_major_id<> */\
		XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + 1 +\
		/* eir_server_scope<> */\
		XDR_QUADLEN(NFS4_OPAQUE_LIMIT) + 1 +\
		1 + /* eir_server_impl_id array length */\
		0 /* ignored eir_server_impl_id contents */) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_bind_conn_to_session_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + \
		XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + /* bctsr_sessid */\
		2 /* bctsr_dir, use_conn_in_rdma_mode */) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_create_session_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + \
		XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN) + /* sessionid */\
		2 + /* csr_sequence, csr_flags */\
		op_encode_channel_attrs_maxsz + \
		op_encode_channel_attrs_maxsz) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_copy_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size +
		1 /* wr_callback */ +
		op_encode_stateid_maxsz /* wr_callback */ +
		2 /* wr_count */ +
		1 /* wr_committed */ +
		op_encode_verअगरier_maxsz +
		1 /* cr_consecutive */ +
		1 /* cr_synchronous */) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_offload_status_rsize(काष्ठा svc_rqst *rqstp,
					     काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size +
		2 /* osr_count */ +
		1 /* osr_complete<1> optional 0 क्रम now */) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_copy_notअगरy_rsize(काष्ठा svc_rqst *rqstp,
					काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size +
		3 /* cnr_lease_समय */ +
		1 /* We support one cnr_source_server */ +
		1 /* cnr_stateid seq */ +
		op_encode_stateid_maxsz /* cnr_stateid */ +
		1 /* num cnr_source_server*/ +
		1 /* nl4_type */ +
		1 /* nl4 size */ +
		XDR_QUADLEN(NFS4_OPAQUE_LIMIT) /*nl4_loc + nl4_loc_sz */)
		* माप(__be32);
पूर्ण

#अगर_घोषित CONFIG_NFSD_PNFS
अटल अंतरभूत u32 nfsd4_getdeviceinfo_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	u32 maxcount = 0, rlen = 0;

	maxcount = svc_max_payload(rqstp);
	rlen = min(op->u.getdeviceinfo.gd_maxcount, maxcount);

	वापस (op_encode_hdr_size +
		1 /* gd_layout_type*/ +
		XDR_QUADLEN(rlen) +
		2 /* gd_notअगरy_types */) * माप(__be32);
पूर्ण

/*
 * At this stage we करोn't really know what layout driver will handle the request,
 * so we need to define an arbitrary upper bound here.
 */
#घोषणा MAX_LAYOUT_SIZE		128
अटल अंतरभूत u32 nfsd4_layoutget_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size +
		1 /* logr_वापस_on_बंद */ +
		op_encode_stateid_maxsz +
		1 /* nr of layouts */ +
		MAX_LAYOUT_SIZE) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_layoutcommit_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size +
		1 /* locr_newsize */ +
		2 /* ns_size */) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_layoutवापस_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size +
		1 /* lrs_stateid */ +
		op_encode_stateid_maxsz) * माप(__be32);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */


अटल अंतरभूत u32 nfsd4_seek_rsize(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + 3) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_getxattr_rsize(काष्ठा svc_rqst *rqstp,
				       काष्ठा nfsd4_op *op)
अणु
	u32 maxcount, rlen;

	maxcount = svc_max_payload(rqstp);
	rlen = min_t(u32, XATTR_SIZE_MAX, maxcount);

	वापस (op_encode_hdr_size + 1 + XDR_QUADLEN(rlen)) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_setxattr_rsize(काष्ठा svc_rqst *rqstp,
				       काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_change_info_maxsz)
		* माप(__be32);
पूर्ण
अटल अंतरभूत u32 nfsd4_listxattrs_rsize(काष्ठा svc_rqst *rqstp,
					 काष्ठा nfsd4_op *op)
अणु
	u32 maxcount, rlen;

	maxcount = svc_max_payload(rqstp);
	rlen = min(op->u.listxattrs.lsxa_maxcount, maxcount);

	वापस (op_encode_hdr_size + 4 + XDR_QUADLEN(rlen)) * माप(__be32);
पूर्ण

अटल अंतरभूत u32 nfsd4_हटाओxattr_rsize(काष्ठा svc_rqst *rqstp,
					  काष्ठा nfsd4_op *op)
अणु
	वापस (op_encode_hdr_size + op_encode_change_info_maxsz)
		* माप(__be32);
पूर्ण


अटल स्थिर काष्ठा nfsd4_operation nfsd4_ops[] = अणु
	[OP_ACCESS] = अणु
		.op_func = nfsd4_access,
		.op_name = "OP_ACCESS",
		.op_rsize_bop = nfsd4_access_rsize,
	पूर्ण,
	[OP_CLOSE] = अणु
		.op_func = nfsd4_बंद,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_CLOSE",
		.op_rsize_bop = nfsd4_status_stateid_rsize,
		.op_get_currentstateid = nfsd4_get_बंदstateid,
		.op_set_currentstateid = nfsd4_set_बंदstateid,
	पूर्ण,
	[OP_COMMIT] = अणु
		.op_func = nfsd4_commit,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_COMMIT",
		.op_rsize_bop = nfsd4_commit_rsize,
	पूर्ण,
	[OP_CREATE] = अणु
		.op_func = nfsd4_create,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME | OP_CLEAR_STATEID,
		.op_name = "OP_CREATE",
		.op_rsize_bop = nfsd4_create_rsize,
	पूर्ण,
	[OP_DELEGRETURN] = अणु
		.op_func = nfsd4_delegवापस,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_DELEGRETURN",
		.op_rsize_bop = nfsd4_only_status_rsize,
		.op_get_currentstateid = nfsd4_get_delegवापसstateid,
	पूर्ण,
	[OP_GETATTR] = अणु
		.op_func = nfsd4_getattr,
		.op_flags = ALLOWED_ON_ABSENT_FS,
		.op_rsize_bop = nfsd4_getattr_rsize,
		.op_name = "OP_GETATTR",
	पूर्ण,
	[OP_GETFH] = अणु
		.op_func = nfsd4_getfh,
		.op_name = "OP_GETFH",
		.op_rsize_bop = nfsd4_getfh_rsize,
	पूर्ण,
	[OP_LINK] = अणु
		.op_func = nfsd4_link,
		.op_flags = ALLOWED_ON_ABSENT_FS | OP_MODIFIES_SOMETHING
				| OP_CACHEME,
		.op_name = "OP_LINK",
		.op_rsize_bop = nfsd4_link_rsize,
	पूर्ण,
	[OP_LOCK] = अणु
		.op_func = nfsd4_lock,
		.op_flags = OP_MODIFIES_SOMETHING |
				OP_NONTRIVIAL_ERROR_ENCODE,
		.op_name = "OP_LOCK",
		.op_rsize_bop = nfsd4_lock_rsize,
		.op_set_currentstateid = nfsd4_set_lockstateid,
	पूर्ण,
	[OP_LOCKT] = अणु
		.op_func = nfsd4_lockt,
		.op_flags = OP_NONTRIVIAL_ERROR_ENCODE,
		.op_name = "OP_LOCKT",
		.op_rsize_bop = nfsd4_lock_rsize,
	पूर्ण,
	[OP_LOCKU] = अणु
		.op_func = nfsd4_locku,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LOCKU",
		.op_rsize_bop = nfsd4_status_stateid_rsize,
		.op_get_currentstateid = nfsd4_get_lockustateid,
	पूर्ण,
	[OP_LOOKUP] = अणु
		.op_func = nfsd4_lookup,
		.op_flags = OP_HANDLES_WRONGSEC | OP_CLEAR_STATEID,
		.op_name = "OP_LOOKUP",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_LOOKUPP] = अणु
		.op_func = nfsd4_lookupp,
		.op_flags = OP_HANDLES_WRONGSEC | OP_CLEAR_STATEID,
		.op_name = "OP_LOOKUPP",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_NVERIFY] = अणु
		.op_func = nfsd4_nverअगरy,
		.op_name = "OP_NVERIFY",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_OPEN] = अणु
		.op_func = nfsd4_खोलो,
		.op_flags = OP_HANDLES_WRONGSEC | OP_MODIFIES_SOMETHING,
		.op_name = "OP_OPEN",
		.op_rsize_bop = nfsd4_खोलो_rsize,
		.op_set_currentstateid = nfsd4_set_खोलोstateid,
	पूर्ण,
	[OP_OPEN_CONFIRM] = अणु
		.op_func = nfsd4_खोलो_confirm,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_OPEN_CONFIRM",
		.op_rsize_bop = nfsd4_status_stateid_rsize,
	पूर्ण,
	[OP_OPEN_DOWNGRADE] = अणु
		.op_func = nfsd4_खोलो_करोwngrade,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_OPEN_DOWNGRADE",
		.op_rsize_bop = nfsd4_status_stateid_rsize,
		.op_get_currentstateid = nfsd4_get_खोलोकरोwngradestateid,
		.op_set_currentstateid = nfsd4_set_खोलोकरोwngradestateid,
	पूर्ण,
	[OP_PUTFH] = अणु
		.op_func = nfsd4_putfh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_CLEAR_STATEID,
		.op_name = "OP_PUTFH",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_PUTPUBFH] = अणु
		.op_func = nfsd4_putrootfh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_CLEAR_STATEID,
		.op_name = "OP_PUTPUBFH",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_PUTROOTFH] = अणु
		.op_func = nfsd4_putrootfh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_CLEAR_STATEID,
		.op_name = "OP_PUTROOTFH",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_READ] = अणु
		.op_func = nfsd4_पढ़ो,
		.op_release = nfsd4_पढ़ो_release,
		.op_name = "OP_READ",
		.op_rsize_bop = nfsd4_पढ़ो_rsize,
		.op_get_currentstateid = nfsd4_get_पढ़ोstateid,
	पूर्ण,
	[OP_READसूची] = अणु
		.op_func = nfsd4_सूची_पढ़ो,
		.op_name = "OP_READDIR",
		.op_rsize_bop = nfsd4_सूची_पढ़ो_rsize,
	पूर्ण,
	[OP_READLINK] = अणु
		.op_func = nfsd4_पढ़ोlink,
		.op_name = "OP_READLINK",
		.op_rsize_bop = nfsd4_पढ़ोlink_rsize,
	पूर्ण,
	[OP_REMOVE] = अणु
		.op_func = nfsd4_हटाओ,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_REMOVE",
		.op_rsize_bop = nfsd4_हटाओ_rsize,
	पूर्ण,
	[OP_RENAME] = अणु
		.op_func = nfsd4_नाम,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_RENAME",
		.op_rsize_bop = nfsd4_नाम_rsize,
	पूर्ण,
	[OP_RENEW] = अणु
		.op_func = nfsd4_renew,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_RENEW",
		.op_rsize_bop = nfsd4_only_status_rsize,

	पूर्ण,
	[OP_RESTOREFH] = अणु
		.op_func = nfsd4_restorefh,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_IS_PUTFH_LIKE | OP_MODIFIES_SOMETHING,
		.op_name = "OP_RESTOREFH",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_SAVEFH] = अणु
		.op_func = nfsd4_savefh,
		.op_flags = OP_HANDLES_WRONGSEC | OP_MODIFIES_SOMETHING,
		.op_name = "OP_SAVEFH",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_SECINFO] = अणु
		.op_func = nfsd4_secinfo,
		.op_release = nfsd4_secinfo_release,
		.op_flags = OP_HANDLES_WRONGSEC,
		.op_name = "OP_SECINFO",
		.op_rsize_bop = nfsd4_secinfo_rsize,
	पूर्ण,
	[OP_SETATTR] = अणु
		.op_func = nfsd4_setattr,
		.op_name = "OP_SETATTR",
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME
				| OP_NONTRIVIAL_ERROR_ENCODE,
		.op_rsize_bop = nfsd4_setattr_rsize,
		.op_get_currentstateid = nfsd4_get_setattrstateid,
	पूर्ण,
	[OP_SETCLIENTID] = अणु
		.op_func = nfsd4_setclientid,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING | OP_CACHEME
				| OP_NONTRIVIAL_ERROR_ENCODE,
		.op_name = "OP_SETCLIENTID",
		.op_rsize_bop = nfsd4_setclientid_rsize,
	पूर्ण,
	[OP_SETCLIENTID_CONFIRM] = अणु
		.op_func = nfsd4_setclientid_confirm,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_SETCLIENTID_CONFIRM",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_VERIFY] = अणु
		.op_func = nfsd4_verअगरy,
		.op_name = "OP_VERIFY",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_WRITE] = अणु
		.op_func = nfsd4_ग_लिखो,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_WRITE",
		.op_rsize_bop = nfsd4_ग_लिखो_rsize,
		.op_get_currentstateid = nfsd4_get_ग_लिखोstateid,
	पूर्ण,
	[OP_RELEASE_LOCKOWNER] = अणु
		.op_func = nfsd4_release_lockowner,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_ON_ABSENT_FS
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_RELEASE_LOCKOWNER",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,

	/* NFSv4.1 operations */
	[OP_EXCHANGE_ID] = अणु
		.op_func = nfsd4_exchange_id,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_EXCHANGE_ID",
		.op_rsize_bop = nfsd4_exchange_id_rsize,
	पूर्ण,
	[OP_BACKCHANNEL_CTL] = अणु
		.op_func = nfsd4_backchannel_ctl,
		.op_flags = ALLOWED_WITHOUT_FH | OP_MODIFIES_SOMETHING,
		.op_name = "OP_BACKCHANNEL_CTL",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_BIND_CONN_TO_SESSION] = अणु
		.op_func = nfsd4_bind_conn_to_session,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_BIND_CONN_TO_SESSION",
		.op_rsize_bop = nfsd4_bind_conn_to_session_rsize,
	पूर्ण,
	[OP_CREATE_SESSION] = अणु
		.op_func = nfsd4_create_session,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_CREATE_SESSION",
		.op_rsize_bop = nfsd4_create_session_rsize,
	पूर्ण,
	[OP_DESTROY_SESSION] = अणु
		.op_func = nfsd4_destroy_session,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_DESTROY_SESSION",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_SEQUENCE] = अणु
		.op_func = nfsd4_sequence,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP,
		.op_name = "OP_SEQUENCE",
		.op_rsize_bop = nfsd4_sequence_rsize,
	पूर्ण,
	[OP_DESTROY_CLIENTID] = अणु
		.op_func = nfsd4_destroy_clientid,
		.op_flags = ALLOWED_WITHOUT_FH | ALLOWED_AS_FIRST_OP
				| OP_MODIFIES_SOMETHING,
		.op_name = "OP_DESTROY_CLIENTID",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_RECLAIM_COMPLETE] = अणु
		.op_func = nfsd4_reclaim_complete,
		.op_flags = ALLOWED_WITHOUT_FH | OP_MODIFIES_SOMETHING,
		.op_name = "OP_RECLAIM_COMPLETE",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_SECINFO_NO_NAME] = अणु
		.op_func = nfsd4_secinfo_no_name,
		.op_release = nfsd4_secinfo_no_name_release,
		.op_flags = OP_HANDLES_WRONGSEC,
		.op_name = "OP_SECINFO_NO_NAME",
		.op_rsize_bop = nfsd4_secinfo_rsize,
	पूर्ण,
	[OP_TEST_STATEID] = अणु
		.op_func = nfsd4_test_stateid,
		.op_flags = ALLOWED_WITHOUT_FH,
		.op_name = "OP_TEST_STATEID",
		.op_rsize_bop = nfsd4_test_stateid_rsize,
	पूर्ण,
	[OP_FREE_STATEID] = अणु
		.op_func = nfsd4_मुक्त_stateid,
		.op_flags = ALLOWED_WITHOUT_FH | OP_MODIFIES_SOMETHING,
		.op_name = "OP_FREE_STATEID",
		.op_get_currentstateid = nfsd4_get_मुक्तstateid,
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
#अगर_घोषित CONFIG_NFSD_PNFS
	[OP_GETDEVICEINFO] = अणु
		.op_func = nfsd4_getdeviceinfo,
		.op_release = nfsd4_getdeviceinfo_release,
		.op_flags = ALLOWED_WITHOUT_FH,
		.op_name = "OP_GETDEVICEINFO",
		.op_rsize_bop = nfsd4_getdeviceinfo_rsize,
	पूर्ण,
	[OP_LAYOUTGET] = अणु
		.op_func = nfsd4_layoutget,
		.op_release = nfsd4_layoutget_release,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LAYOUTGET",
		.op_rsize_bop = nfsd4_layoutget_rsize,
	पूर्ण,
	[OP_LAYOUTCOMMIT] = अणु
		.op_func = nfsd4_layoutcommit,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LAYOUTCOMMIT",
		.op_rsize_bop = nfsd4_layoutcommit_rsize,
	पूर्ण,
	[OP_LAYOUTRETURN] = अणु
		.op_func = nfsd4_layoutवापस,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_LAYOUTRETURN",
		.op_rsize_bop = nfsd4_layoutवापस_rsize,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

	/* NFSv4.2 operations */
	[OP_ALLOCATE] = अणु
		.op_func = nfsd4_allocate,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_ALLOCATE",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_DEALLOCATE] = अणु
		.op_func = nfsd4_deallocate,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_DEALLOCATE",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_CLONE] = अणु
		.op_func = nfsd4_clone,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_CLONE",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_COPY] = अणु
		.op_func = nfsd4_copy,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_COPY",
		.op_rsize_bop = nfsd4_copy_rsize,
	पूर्ण,
	[OP_READ_PLUS] = अणु
		.op_func = nfsd4_पढ़ो,
		.op_release = nfsd4_पढ़ो_release,
		.op_name = "OP_READ_PLUS",
		.op_rsize_bop = nfsd4_पढ़ो_plus_rsize,
		.op_get_currentstateid = nfsd4_get_पढ़ोstateid,
	पूर्ण,
	[OP_SEEK] = अणु
		.op_func = nfsd4_seek,
		.op_name = "OP_SEEK",
		.op_rsize_bop = nfsd4_seek_rsize,
	पूर्ण,
	[OP_OFFLOAD_STATUS] = अणु
		.op_func = nfsd4_offload_status,
		.op_name = "OP_OFFLOAD_STATUS",
		.op_rsize_bop = nfsd4_offload_status_rsize,
	पूर्ण,
	[OP_OFFLOAD_CANCEL] = अणु
		.op_func = nfsd4_offload_cancel,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_OFFLOAD_CANCEL",
		.op_rsize_bop = nfsd4_only_status_rsize,
	पूर्ण,
	[OP_COPY_NOTIFY] = अणु
		.op_func = nfsd4_copy_notअगरy,
		.op_flags = OP_MODIFIES_SOMETHING,
		.op_name = "OP_COPY_NOTIFY",
		.op_rsize_bop = nfsd4_copy_notअगरy_rsize,
	पूर्ण,
	[OP_GETXATTR] = अणु
		.op_func = nfsd4_getxattr,
		.op_name = "OP_GETXATTR",
		.op_rsize_bop = nfsd4_getxattr_rsize,
	पूर्ण,
	[OP_SETXATTR] = अणु
		.op_func = nfsd4_setxattr,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_SETXATTR",
		.op_rsize_bop = nfsd4_setxattr_rsize,
	पूर्ण,
	[OP_LISTXATTRS] = अणु
		.op_func = nfsd4_listxattrs,
		.op_name = "OP_LISTXATTRS",
		.op_rsize_bop = nfsd4_listxattrs_rsize,
	पूर्ण,
	[OP_REMOVEXATTR] = अणु
		.op_func = nfsd4_हटाओxattr,
		.op_flags = OP_MODIFIES_SOMETHING | OP_CACHEME,
		.op_name = "OP_REMOVEXATTR",
		.op_rsize_bop = nfsd4_हटाओxattr_rsize,
	पूर्ण,
पूर्ण;

/**
 * nfsd4_spo_must_allow - Determine अगर the compound op contains an
 * operation that is allowed to be sent with machine credentials
 *
 * @rqstp: a poपूर्णांकer to the काष्ठा svc_rqst
 *
 * Checks to see अगर the compound contains a spo_must_allow op
 * and confirms that it was sent with the proper machine creds.
 */

bool nfsd4_spo_must_allow(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd4_compoundres *resp = rqstp->rq_resp;
	काष्ठा nfsd4_compoundargs *argp = rqstp->rq_argp;
	काष्ठा nfsd4_op *this = &argp->ops[resp->opcnt - 1];
	काष्ठा nfsd4_compound_state *cstate = &resp->cstate;
	काष्ठा nfs4_op_map *allow = &cstate->clp->cl_spo_must_allow;
	u32 opiter;

	अगर (!cstate->minorversion)
		वापस false;

	अगर (cstate->spo_must_allowed)
		वापस true;

	opiter = resp->opcnt;
	जबतक (opiter < argp->opcnt) अणु
		this = &argp->ops[opiter++];
		अगर (test_bit(this->opnum, allow->u.दीर्घs) &&
			cstate->clp->cl_mach_cred &&
			nfsd4_mach_creds_match(cstate->clp, rqstp)) अणु
			cstate->spo_must_allowed = true;
			वापस true;
		पूर्ण
	पूर्ण
	cstate->spo_must_allowed = false;
	वापस false;
पूर्ण

पूर्णांक nfsd4_max_reply(काष्ठा svc_rqst *rqstp, काष्ठा nfsd4_op *op)
अणु
	अगर (op->opnum == OP_ILLEGAL || op->status == nfserr_notsupp)
		वापस op_encode_hdr_size * माप(__be32);

	BUG_ON(OPDESC(op)->op_rsize_bop == शून्य);
	वापस OPDESC(op)->op_rsize_bop(rqstp, op);
पूर्ण

व्योम warn_on_nonidempotent_op(काष्ठा nfsd4_op *op)
अणु
	अगर (OPDESC(op)->op_flags & OP_MODIFIES_SOMETHING) अणु
		pr_err("unable to encode reply to nonidempotent op %u (%s)\n",
			op->opnum, nfsd4_op_name(op->opnum));
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *nfsd4_op_name(अचिन्हित opnum)
अणु
	अगर (opnum < ARRAY_SIZE(nfsd4_ops))
		वापस nfsd4_ops[opnum].op_name;
	वापस "unknown_operation";
पूर्ण

अटल स्थिर काष्ठा svc_procedure nfsd_procedures4[2] = अणु
	[NFSPROC4_शून्य] = अणु
		.pc_func = nfsd4_proc_null,
		.pc_decode = nfssvc_decode_व्योमarg,
		.pc_encode = nfssvc_encode_व्योमres,
		.pc_argsize = माप(काष्ठा nfsd_व्योमargs),
		.pc_ressize = माप(काष्ठा nfsd_व्योमres),
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = 1,
		.pc_name = "NULL",
	पूर्ण,
	[NFSPROC4_COMPOUND] = अणु
		.pc_func = nfsd4_proc_compound,
		.pc_decode = nfs4svc_decode_compoundargs,
		.pc_encode = nfs4svc_encode_compoundres,
		.pc_argsize = माप(काष्ठा nfsd4_compoundargs),
		.pc_ressize = माप(काष्ठा nfsd4_compoundres),
		.pc_release = nfsd4_release_compoundargs,
		.pc_cachetype = RC_NOCACHE,
		.pc_xdrressize = NFSD_बफ_मानE/4,
		.pc_name = "COMPOUND",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nfsd_count3[ARRAY_SIZE(nfsd_procedures4)];
स्थिर काष्ठा svc_version nfsd_version4 = अणु
	.vs_vers		= 4,
	.vs_nproc		= 2,
	.vs_proc		= nfsd_procedures4,
	.vs_count		= nfsd_count3,
	.vs_dispatch		= nfsd_dispatch,
	.vs_xdrsize		= NFS4_SVC_XDRSIZE,
	.vs_rpcb_optnl		= true,
	.vs_need_cong_ctrl	= true,
पूर्ण;
