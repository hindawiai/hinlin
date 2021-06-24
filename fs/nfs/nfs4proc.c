<शैली गुरु>
/*
 *  fs/nfs/nfs4proc.c
 *
 *  Client-side procedure declarations क्रम NFSv4.
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

#समावेश <linux/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/ratelimit.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/module.h>
#समावेश <linux/xattr.h>
#समावेश <linux/utsname.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/iversion.h>

#समावेश "nfs4_fs.h"
#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "iostat.h"
#समावेश "callback.h"
#समावेश "pnfs.h"
#समावेश "netns.h"
#समावेश "sysfs.h"
#समावेश "nfs4idmap.h"
#समावेश "nfs4session.h"
#समावेश "fscache.h"
#समावेश "nfs42.h"

#समावेश "nfs4trace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PROC

#घोषणा NFS4_BITMASK_SZ		3

#घोषणा NFS4_POLL_RETRY_MIN	(HZ/10)
#घोषणा NFS4_POLL_RETRY_MAX	(15*HZ)

/* file attributes which can be mapped to nfs attributes */
#घोषणा NFS4_VALID_ATTRS (ATTR_MODE \
	| ATTR_UID \
	| ATTR_GID \
	| ATTR_SIZE \
	| ATTR_ATIME \
	| ATTR_MTIME \
	| ATTR_CTIME \
	| ATTR_ATIME_SET \
	| ATTR_MTIME_SET)

काष्ठा nfs4_खोलोdata;
अटल पूर्णांक _nfs4_recover_proc_खोलो(काष्ठा nfs4_खोलोdata *data);
अटल पूर्णांक nfs4_करो_fsinfo(काष्ठा nfs_server *, काष्ठा nfs_fh *, काष्ठा nfs_fsinfo *);
अटल व्योम nfs_fixup_referral_attributes(काष्ठा nfs_fattr *fattr);
अटल पूर्णांक _nfs4_proc_getattr(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label, काष्ठा inode *inode);
अटल पूर्णांक nfs4_करो_setattr(काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
			    काष्ठा nfs_fattr *fattr, काष्ठा iattr *sattr,
			    काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_label *ilabel,
			    काष्ठा nfs4_label *olabel);
#अगर_घोषित CONFIG_NFS_V4_1
अटल काष्ठा rpc_task *_nfs41_proc_sequence(काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred,
		काष्ठा nfs4_slot *slot,
		bool is_privileged);
अटल पूर्णांक nfs41_test_stateid(काष्ठा nfs_server *, nfs4_stateid *,
		स्थिर काष्ठा cred *);
अटल पूर्णांक nfs41_मुक्त_stateid(काष्ठा nfs_server *, स्थिर nfs4_stateid *,
		स्थिर काष्ठा cred *, bool);
#पूर्ण_अगर
अटल व्योम nfs4_biपंचांगask_set(__u32 biपंचांगask[NFS4_BITMASK_SZ],
			     स्थिर __u32 *src, काष्ठा inode *inode,
			     काष्ठा nfs_server *server,
			     काष्ठा nfs4_label *label);

#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
अटल अंतरभूत काष्ठा nfs4_label *
nfs4_label_init_security(काष्ठा inode *dir, काष्ठा dentry *dentry,
	काष्ठा iattr *sattr, काष्ठा nfs4_label *label)
अणु
	पूर्णांक err;

	अगर (label == शून्य)
		वापस शून्य;

	अगर (nfs_server_capable(dir, NFS_CAP_SECURITY_LABEL) == 0)
		वापस शून्य;

	err = security_dentry_init_security(dentry, sattr->ia_mode,
				&dentry->d_name, (व्योम **)&label->label, &label->len);
	अगर (err == 0)
		वापस label;

	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम
nfs4_label_release_security(काष्ठा nfs4_label *label)
अणु
	अगर (label)
		security_release_secctx(label->label, label->len);
पूर्ण
अटल अंतरभूत u32 *nfs4_biपंचांगask(काष्ठा nfs_server *server, काष्ठा nfs4_label *label)
अणु
	अगर (label)
		वापस server->attr_biपंचांगask;

	वापस server->attr_biपंचांगask_nl;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा nfs4_label *
nfs4_label_init_security(काष्ठा inode *dir, काष्ठा dentry *dentry,
	काष्ठा iattr *sattr, काष्ठा nfs4_label *l)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम
nfs4_label_release_security(काष्ठा nfs4_label *label)
अणु वापस; पूर्ण
अटल अंतरभूत u32 *
nfs4_biपंचांगask(काष्ठा nfs_server *server, काष्ठा nfs4_label *label)
अणु वापस server->attr_biपंचांगask; पूर्ण
#पूर्ण_अगर

/* Prevent leaks of NFSv4 errors पूर्णांकo userland */
अटल पूर्णांक nfs4_map_errors(पूर्णांक err)
अणु
	अगर (err >= -1000)
		वापस err;
	चयन (err) अणु
	हाल -NFS4ERR_RESOURCE:
	हाल -NFS4ERR_LAYOUTTRYLATER:
	हाल -NFS4ERR_RECALLCONFLICT:
		वापस -EREMOTEIO;
	हाल -NFS4ERR_WRONGSEC:
	हाल -NFS4ERR_WRONG_CRED:
		वापस -EPERM;
	हाल -NFS4ERR_BADOWNER:
	हाल -NFS4ERR_BADNAME:
		वापस -EINVAL;
	हाल -NFS4ERR_SHARE_DENIED:
		वापस -EACCES;
	हाल -NFS4ERR_MINOR_VERS_MISMATCH:
		वापस -EPROTONOSUPPORT;
	हाल -NFS4ERR_खाता_OPEN:
		वापस -EBUSY;
	हाल -NFS4ERR_NOT_SAME:
		वापस -ENOTSYNC;
	शेष:
		dprपूर्णांकk("%s could not handle NFSv4 error %d\n",
				__func__, -err);
		अवरोध;
	पूर्ण
	वापस -EIO;
पूर्ण

/*
 * This is our standard biपंचांगap क्रम GETATTR requests.
 */
स्थिर u32 nfs4_fattr_biपंचांगap[3] = अणु
	FATTR4_WORD0_TYPE
	| FATTR4_WORD0_CHANGE
	| FATTR4_WORD0_SIZE
	| FATTR4_WORD0_FSID
	| FATTR4_WORD0_खाताID,
	FATTR4_WORD1_MODE
	| FATTR4_WORD1_NUMLINKS
	| FATTR4_WORD1_OWNER
	| FATTR4_WORD1_OWNER_GROUP
	| FATTR4_WORD1_RAWDEV
	| FATTR4_WORD1_SPACE_USED
	| FATTR4_WORD1_TIME_ACCESS
	| FATTR4_WORD1_TIME_METADATA
	| FATTR4_WORD1_TIME_MODIFY
	| FATTR4_WORD1_MOUNTED_ON_खाताID,
#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
	FATTR4_WORD2_SECURITY_LABEL
#पूर्ण_अगर
पूर्ण;

अटल स्थिर u32 nfs4_pnfs_खोलो_biपंचांगap[3] = अणु
	FATTR4_WORD0_TYPE
	| FATTR4_WORD0_CHANGE
	| FATTR4_WORD0_SIZE
	| FATTR4_WORD0_FSID
	| FATTR4_WORD0_खाताID,
	FATTR4_WORD1_MODE
	| FATTR4_WORD1_NUMLINKS
	| FATTR4_WORD1_OWNER
	| FATTR4_WORD1_OWNER_GROUP
	| FATTR4_WORD1_RAWDEV
	| FATTR4_WORD1_SPACE_USED
	| FATTR4_WORD1_TIME_ACCESS
	| FATTR4_WORD1_TIME_METADATA
	| FATTR4_WORD1_TIME_MODIFY,
	FATTR4_WORD2_MDSTHRESHOLD
#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
	| FATTR4_WORD2_SECURITY_LABEL
#पूर्ण_अगर
पूर्ण;

अटल स्थिर u32 nfs4_खोलो_noattr_biपंचांगap[3] = अणु
	FATTR4_WORD0_TYPE
	| FATTR4_WORD0_खाताID,
पूर्ण;

स्थिर u32 nfs4_statfs_biपंचांगap[3] = अणु
	FATTR4_WORD0_खाताS_AVAIL
	| FATTR4_WORD0_खाताS_FREE
	| FATTR4_WORD0_खाताS_TOTAL,
	FATTR4_WORD1_SPACE_AVAIL
	| FATTR4_WORD1_SPACE_FREE
	| FATTR4_WORD1_SPACE_TOTAL
पूर्ण;

स्थिर u32 nfs4_pathconf_biपंचांगap[3] = अणु
	FATTR4_WORD0_MAXLINK
	| FATTR4_WORD0_MAXNAME,
	0
पूर्ण;

स्थिर u32 nfs4_fsinfo_biपंचांगap[3] = अणु FATTR4_WORD0_MAXखाताSIZE
			| FATTR4_WORD0_MAXREAD
			| FATTR4_WORD0_MAXWRITE
			| FATTR4_WORD0_LEASE_TIME,
			FATTR4_WORD1_TIME_DELTA
			| FATTR4_WORD1_FS_LAYOUT_TYPES,
			FATTR4_WORD2_LAYOUT_BLKSIZE
			| FATTR4_WORD2_CLONE_BLKSIZE
			| FATTR4_WORD2_CHANGE_ATTR_TYPE
			| FATTR4_WORD2_XATTR_SUPPORT
पूर्ण;

स्थिर u32 nfs4_fs_locations_biपंचांगap[3] = अणु
	FATTR4_WORD0_CHANGE
	| FATTR4_WORD0_SIZE
	| FATTR4_WORD0_FSID
	| FATTR4_WORD0_खाताID
	| FATTR4_WORD0_FS_LOCATIONS,
	FATTR4_WORD1_OWNER
	| FATTR4_WORD1_OWNER_GROUP
	| FATTR4_WORD1_RAWDEV
	| FATTR4_WORD1_SPACE_USED
	| FATTR4_WORD1_TIME_ACCESS
	| FATTR4_WORD1_TIME_METADATA
	| FATTR4_WORD1_TIME_MODIFY
	| FATTR4_WORD1_MOUNTED_ON_खाताID,
पूर्ण;

अटल व्योम nfs4_biपंचांगap_copy_adjust(__u32 *dst, स्थिर __u32 *src,
				    काष्ठा inode *inode, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ cache_validity;

	स_नकल(dst, src, NFS4_BITMASK_SZ*माप(*dst));
	अगर (!inode || !nfs4_have_delegation(inode, FMODE_READ))
		वापस;

	cache_validity = READ_ONCE(NFS_I(inode)->cache_validity) | flags;

	/* Remove the attributes over which we have full control */
	dst[1] &= ~FATTR4_WORD1_RAWDEV;
	अगर (!(cache_validity & NFS_INO_INVALID_SIZE))
		dst[0] &= ~FATTR4_WORD0_SIZE;

	अगर (!(cache_validity & NFS_INO_INVALID_CHANGE))
		dst[0] &= ~FATTR4_WORD0_CHANGE;

	अगर (!(cache_validity & NFS_INO_INVALID_MODE))
		dst[1] &= ~FATTR4_WORD1_MODE;
	अगर (!(cache_validity & NFS_INO_INVALID_OTHER))
		dst[1] &= ~(FATTR4_WORD1_OWNER | FATTR4_WORD1_OWNER_GROUP);
पूर्ण

अटल व्योम nfs4_setup_सूची_पढ़ो(u64 cookie, __be32 *verअगरier, काष्ठा dentry *dentry,
		काष्ठा nfs4_सूची_पढ़ो_arg *सूची_पढ़ो)
अणु
	अचिन्हित पूर्णांक attrs = FATTR4_WORD0_खाताID | FATTR4_WORD0_TYPE;
	__be32 *start, *p;

	अगर (cookie > 2) अणु
		सूची_पढ़ो->cookie = cookie;
		स_नकल(&सूची_पढ़ो->verअगरier, verअगरier, माप(सूची_पढ़ो->verअगरier));
		वापस;
	पूर्ण

	सूची_पढ़ो->cookie = 0;
	स_रखो(&सूची_पढ़ो->verअगरier, 0, माप(सूची_पढ़ो->verअगरier));
	अगर (cookie == 2)
		वापस;
	
	/*
	 * NFSv4 servers करो not वापस entries क्रम '.' and '..'
	 * Thereक्रमe, we fake these entries here.  We let '.'
	 * have cookie 0 and '..' have cookie 1.  Note that
	 * when talking to the server, we always send cookie 0
	 * instead of 1 or 2.
	 */
	start = p = kmap_atomic(*सूची_पढ़ो->pages);
	
	अगर (cookie == 0) अणु
		*p++ = xdr_one;                                  /* next */
		*p++ = xdr_zero;                   /* cookie, first word */
		*p++ = xdr_one;                   /* cookie, second word */
		*p++ = xdr_one;                             /* entry len */
		स_नकल(p, ".\0\0\0", 4);                        /* entry */
		p++;
		*p++ = xdr_one;                         /* biपंचांगap length */
		*p++ = htonl(attrs);                           /* biपंचांगap */
		*p++ = htonl(12);             /* attribute buffer length */
		*p++ = htonl(NF4सूची);
		p = xdr_encode_hyper(p, NFS_खाताID(d_inode(dentry)));
	पूर्ण
	
	*p++ = xdr_one;                                  /* next */
	*p++ = xdr_zero;                   /* cookie, first word */
	*p++ = xdr_two;                   /* cookie, second word */
	*p++ = xdr_two;                             /* entry len */
	स_नकल(p, "..\0\0", 4);                         /* entry */
	p++;
	*p++ = xdr_one;                         /* biपंचांगap length */
	*p++ = htonl(attrs);                           /* biपंचांगap */
	*p++ = htonl(12);             /* attribute buffer length */
	*p++ = htonl(NF4सूची);
	p = xdr_encode_hyper(p, NFS_खाताID(d_inode(dentry->d_parent)));

	सूची_पढ़ो->pgbase = (अक्षर *)p - (अक्षर *)start;
	सूची_पढ़ो->count -= सूची_पढ़ो->pgbase;
	kunmap_atomic(start);
पूर्ण

अटल व्योम nfs4_test_and_मुक्त_stateid(काष्ठा nfs_server *server,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	स्थिर काष्ठा nfs4_minor_version_ops *ops = server->nfs_client->cl_mvops;

	ops->test_and_मुक्त_expired(server, stateid, cred);
पूर्ण

अटल व्योम __nfs4_मुक्त_revoked_stateid(काष्ठा nfs_server *server,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	stateid->type = NFS4_REVOKED_STATEID_TYPE;
	nfs4_test_and_मुक्त_stateid(server, stateid, cred);
पूर्ण

अटल व्योम nfs4_मुक्त_revoked_stateid(काष्ठा nfs_server *server,
		स्थिर nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	nfs4_stateid पंचांगp;

	nfs4_stateid_copy(&पंचांगp, stateid);
	__nfs4_मुक्त_revoked_stateid(server, &पंचांगp, cred);
पूर्ण

अटल दीर्घ nfs4_update_delay(दीर्घ *समयout)
अणु
	दीर्घ ret;
	अगर (!समयout)
		वापस NFS4_POLL_RETRY_MAX;
	अगर (*समयout <= 0)
		*समयout = NFS4_POLL_RETRY_MIN;
	अगर (*समयout > NFS4_POLL_RETRY_MAX)
		*समयout = NFS4_POLL_RETRY_MAX;
	ret = *समयout;
	*समयout <<= 1;
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_delay_समाप्तable(दीर्घ *समयout)
अणु
	might_sleep();

	मुक्तzable_schedule_समयout_समाप्तable_unsafe(
		nfs4_update_delay(समयout));
	अगर (!__fatal_संकेत_pending(current))
		वापस 0;
	वापस -EINTR;
पूर्ण

अटल पूर्णांक nfs4_delay_पूर्णांकerruptible(दीर्घ *समयout)
अणु
	might_sleep();

	मुक्तzable_schedule_समयout_पूर्णांकerruptible_unsafe(nfs4_update_delay(समयout));
	अगर (!संकेत_pending(current))
		वापस 0;
	वापस __fatal_संकेत_pending(current) ? -EINTR :-ERESTARTSYS;
पूर्ण

अटल पूर्णांक nfs4_delay(दीर्घ *समयout, bool पूर्णांकerruptible)
अणु
	अगर (पूर्णांकerruptible)
		वापस nfs4_delay_पूर्णांकerruptible(समयout);
	वापस nfs4_delay_समाप्तable(समयout);
पूर्ण

अटल स्थिर nfs4_stateid *
nfs4_recoverable_stateid(स्थिर nfs4_stateid *stateid)
अणु
	अगर (!stateid)
		वापस शून्य;
	चयन (stateid->type) अणु
	हाल NFS4_OPEN_STATEID_TYPE:
	हाल NFS4_LOCK_STATEID_TYPE:
	हाल NFS4_DELEGATION_STATEID_TYPE:
		वापस stateid;
	शेष:
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

/* This is the error handling routine क्रम processes that are allowed
 * to sleep.
 */
अटल पूर्णांक nfs4_करो_handle_exception(काष्ठा nfs_server *server,
		पूर्णांक errorcode, काष्ठा nfs4_exception *exception)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_state *state = exception->state;
	स्थिर nfs4_stateid *stateid;
	काष्ठा inode *inode = exception->inode;
	पूर्णांक ret = errorcode;

	exception->delay = 0;
	exception->recovering = 0;
	exception->retry = 0;

	stateid = nfs4_recoverable_stateid(exception->stateid);
	अगर (stateid == शून्य && state != शून्य)
		stateid = nfs4_recoverable_stateid(&state->stateid);

	चयन(errorcode) अणु
		हाल 0:
			वापस 0;
		हाल -NFS4ERR_BADHANDLE:
		हाल -ESTALE:
			अगर (inode != शून्य && S_ISREG(inode->i_mode))
				pnfs_destroy_layout(NFS_I(inode));
			अवरोध;
		हाल -NFS4ERR_DELEG_REVOKED:
		हाल -NFS4ERR_ADMIN_REVOKED:
		हाल -NFS4ERR_EXPIRED:
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_PARTNER_NO_AUTH:
			अगर (inode != शून्य && stateid != शून्य) अणु
				nfs_inode_find_state_and_recover(inode,
						stateid);
				जाओ रुको_on_recovery;
			पूर्ण
			fallthrough;
		हाल -NFS4ERR_OPENMODE:
			अगर (inode) अणु
				पूर्णांक err;

				err = nfs_async_inode_वापस_delegation(inode,
						stateid);
				अगर (err == 0)
					जाओ रुको_on_recovery;
				अगर (stateid != शून्य && stateid->type == NFS4_DELEGATION_STATEID_TYPE) अणु
					exception->retry = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (state == शून्य)
				अवरोध;
			ret = nfs4_schedule_stateid_recovery(server, state);
			अगर (ret < 0)
				अवरोध;
			जाओ रुको_on_recovery;
		हाल -NFS4ERR_STALE_STATEID:
		हाल -NFS4ERR_STALE_CLIENTID:
			nfs4_schedule_lease_recovery(clp);
			जाओ रुको_on_recovery;
		हाल -NFS4ERR_MOVED:
			ret = nfs4_schedule_migration_recovery(server);
			अगर (ret < 0)
				अवरोध;
			जाओ रुको_on_recovery;
		हाल -NFS4ERR_LEASE_MOVED:
			nfs4_schedule_lease_moved_recovery(clp);
			जाओ रुको_on_recovery;
#अगर defined(CONFIG_NFS_V4_1)
		हाल -NFS4ERR_BADSESSION:
		हाल -NFS4ERR_BADSLOT:
		हाल -NFS4ERR_BAD_HIGH_SLOT:
		हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		हाल -NFS4ERR_DEADSESSION:
		हाल -NFS4ERR_SEQ_FALSE_RETRY:
		हाल -NFS4ERR_SEQ_MISORDERED:
			/* Handled in nfs41_sequence_process() */
			जाओ रुको_on_recovery;
#पूर्ण_अगर /* defined(CONFIG_NFS_V4_1) */
		हाल -NFS4ERR_खाता_OPEN:
			अगर (exception->समयout > HZ) अणु
				/* We have retried a decent amount, समय to
				 * fail
				 */
				ret = -EBUSY;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल -NFS4ERR_DELAY:
			nfs_inc_server_stats(server, NFSIOS_DELAY);
			fallthrough;
		हाल -NFS4ERR_GRACE:
		हाल -NFS4ERR_LAYOUTTRYLATER:
		हाल -NFS4ERR_RECALLCONFLICT:
			exception->delay = 1;
			वापस 0;

		हाल -NFS4ERR_RETRY_UNCACHED_REP:
		हाल -NFS4ERR_OLD_STATEID:
			exception->retry = 1;
			अवरोध;
		हाल -NFS4ERR_BADOWNER:
			/* The following works around a Linux server bug! */
		हाल -NFS4ERR_BADNAME:
			अगर (server->caps & NFS_CAP_UIDGID_NOMAP) अणु
				server->caps &= ~NFS_CAP_UIDGID_NOMAP;
				exception->retry = 1;
				prपूर्णांकk(KERN_WARNING "NFS: v4 server %s "
						"does not accept raw "
						"uid/gids. "
						"Reenabling the idmapper.\n",
						server->nfs_client->cl_hostname);
			पूर्ण
	पूर्ण
	/* We failed to handle the error */
	वापस nfs4_map_errors(ret);
रुको_on_recovery:
	exception->recovering = 1;
	वापस 0;
पूर्ण

/* This is the error handling routine क्रम processes that are allowed
 * to sleep.
 */
पूर्णांक nfs4_handle_exception(काष्ठा nfs_server *server, पूर्णांक errorcode, काष्ठा nfs4_exception *exception)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	पूर्णांक ret;

	ret = nfs4_करो_handle_exception(server, errorcode, exception);
	अगर (exception->delay) अणु
		ret = nfs4_delay(&exception->समयout,
				exception->पूर्णांकerruptible);
		जाओ out_retry;
	पूर्ण
	अगर (exception->recovering) अणु
		अगर (exception->task_is_privileged)
			वापस -EDEADLOCK;
		ret = nfs4_रुको_clnt_recover(clp);
		अगर (test_bit(NFS_MIG_FAILED, &server->mig_status))
			वापस -EIO;
		जाओ out_retry;
	पूर्ण
	वापस ret;
out_retry:
	अगर (ret == 0)
		exception->retry = 1;
	वापस ret;
पूर्ण

अटल पूर्णांक
nfs4_async_handle_exception(काष्ठा rpc_task *task, काष्ठा nfs_server *server,
		पूर्णांक errorcode, काष्ठा nfs4_exception *exception)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	पूर्णांक ret;

	ret = nfs4_करो_handle_exception(server, errorcode, exception);
	अगर (exception->delay) अणु
		rpc_delay(task, nfs4_update_delay(&exception->समयout));
		जाओ out_retry;
	पूर्ण
	अगर (exception->recovering) अणु
		अगर (exception->task_is_privileged)
			वापस -EDEADLOCK;
		rpc_sleep_on(&clp->cl_rpcरुकोq, task, शून्य);
		अगर (test_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) == 0)
			rpc_wake_up_queued_task(&clp->cl_rpcरुकोq, task);
		जाओ out_retry;
	पूर्ण
	अगर (test_bit(NFS_MIG_FAILED, &server->mig_status))
		ret = -EIO;
	वापस ret;
out_retry:
	अगर (ret == 0) अणु
		exception->retry = 1;
		/*
		 * For NFS4ERR_MOVED, the client transport will need to
		 * be recomputed after migration recovery has completed.
		 */
		अगर (errorcode == -NFS4ERR_MOVED)
			rpc_task_release_transport(task);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
nfs4_async_handle_error(काष्ठा rpc_task *task, काष्ठा nfs_server *server,
			काष्ठा nfs4_state *state, दीर्घ *समयout)
अणु
	काष्ठा nfs4_exception exception = अणु
		.state = state,
	पूर्ण;

	अगर (task->tk_status >= 0)
		वापस 0;
	अगर (समयout)
		exception.समयout = *समयout;
	task->tk_status = nfs4_async_handle_exception(task, server,
			task->tk_status,
			&exception);
	अगर (exception.delay && समयout)
		*समयout = exception.समयout;
	अगर (exception.retry)
		वापस -EAGAIN;
	वापस 0;
पूर्ण

/*
 * Return 'true' if 'clp' is using an rpc_client that is पूर्णांकegrity रक्षित
 * or 'false' otherwise.
 */
अटल bool _nfs4_is_पूर्णांकegrity_रक्षित(काष्ठा nfs_client *clp)
अणु
	rpc_authflavor_t flavor = clp->cl_rpcclient->cl_auth->au_flavor;
	वापस (flavor == RPC_AUTH_GSS_KRB5I) || (flavor == RPC_AUTH_GSS_KRB5P);
पूर्ण

अटल व्योम करो_renew_lease(काष्ठा nfs_client *clp, अचिन्हित दीर्घ बारtamp)
अणु
	spin_lock(&clp->cl_lock);
	अगर (समय_beक्रमe(clp->cl_last_renewal,बारtamp))
		clp->cl_last_renewal = बारtamp;
	spin_unlock(&clp->cl_lock);
पूर्ण

अटल व्योम renew_lease(स्थिर काष्ठा nfs_server *server, अचिन्हित दीर्घ बारtamp)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;

	अगर (!nfs4_has_session(clp))
		करो_renew_lease(clp, बारtamp);
पूर्ण

काष्ठा nfs4_call_sync_data अणु
	स्थिर काष्ठा nfs_server *seq_server;
	काष्ठा nfs4_sequence_args *seq_args;
	काष्ठा nfs4_sequence_res *seq_res;
पूर्ण;

व्योम nfs4_init_sequence(काष्ठा nfs4_sequence_args *args,
			काष्ठा nfs4_sequence_res *res, पूर्णांक cache_reply,
			पूर्णांक privileged)
अणु
	args->sa_slot = शून्य;
	args->sa_cache_this = cache_reply;
	args->sa_privileged = privileged;

	res->sr_slot = शून्य;
पूर्ण

अटल व्योम nfs40_sequence_मुक्त_slot(काष्ठा nfs4_sequence_res *res)
अणु
	काष्ठा nfs4_slot *slot = res->sr_slot;
	काष्ठा nfs4_slot_table *tbl;

	tbl = slot->table;
	spin_lock(&tbl->slot_tbl_lock);
	अगर (!nfs41_wake_and_assign_slot(tbl, slot))
		nfs4_मुक्त_slot(tbl, slot);
	spin_unlock(&tbl->slot_tbl_lock);

	res->sr_slot = शून्य;
पूर्ण

अटल पूर्णांक nfs40_sequence_करोne(काष्ठा rpc_task *task,
			       काष्ठा nfs4_sequence_res *res)
अणु
	अगर (res->sr_slot != शून्य)
		nfs40_sequence_मुक्त_slot(res);
	वापस 1;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)

अटल व्योम nfs41_release_slot(काष्ठा nfs4_slot *slot)
अणु
	काष्ठा nfs4_session *session;
	काष्ठा nfs4_slot_table *tbl;
	bool send_new_highest_used_slotid = false;

	अगर (!slot)
		वापस;
	tbl = slot->table;
	session = tbl->session;

	/* Bump the slot sequence number */
	अगर (slot->seq_करोne)
		slot->seq_nr++;
	slot->seq_करोne = 0;

	spin_lock(&tbl->slot_tbl_lock);
	/* Be nice to the server: try to ensure that the last transmitted
	 * value क्रम highest_user_slotid <= target_highest_slotid
	 */
	अगर (tbl->highest_used_slotid > tbl->target_highest_slotid)
		send_new_highest_used_slotid = true;

	अगर (nfs41_wake_and_assign_slot(tbl, slot)) अणु
		send_new_highest_used_slotid = false;
		जाओ out_unlock;
	पूर्ण
	nfs4_मुक्त_slot(tbl, slot);

	अगर (tbl->highest_used_slotid != NFS4_NO_SLOT)
		send_new_highest_used_slotid = false;
out_unlock:
	spin_unlock(&tbl->slot_tbl_lock);
	अगर (send_new_highest_used_slotid)
		nfs41_notअगरy_server(session->clp);
	अगर (रुकोqueue_active(&tbl->slot_रुकोq))
		wake_up_all(&tbl->slot_रुकोq);
पूर्ण

अटल व्योम nfs41_sequence_मुक्त_slot(काष्ठा nfs4_sequence_res *res)
अणु
	nfs41_release_slot(res->sr_slot);
	res->sr_slot = शून्य;
पूर्ण

अटल व्योम nfs4_slot_sequence_record_sent(काष्ठा nfs4_slot *slot,
		u32 seqnr)
अणु
	अगर ((s32)(seqnr - slot->seq_nr_highest_sent) > 0)
		slot->seq_nr_highest_sent = seqnr;
पूर्ण
अटल व्योम nfs4_slot_sequence_acked(काष्ठा nfs4_slot *slot,
		u32 seqnr)
अणु
	slot->seq_nr_highest_sent = seqnr;
	slot->seq_nr_last_acked = seqnr;
पूर्ण

अटल व्योम nfs4_probe_sequence(काष्ठा nfs_client *client, स्थिर काष्ठा cred *cred,
				काष्ठा nfs4_slot *slot)
अणु
	काष्ठा rpc_task *task = _nfs41_proc_sequence(client, cred, slot, true);
	अगर (!IS_ERR(task))
		rpc_put_task_async(task);
पूर्ण

अटल पूर्णांक nfs41_sequence_process(काष्ठा rpc_task *task,
		काष्ठा nfs4_sequence_res *res)
अणु
	काष्ठा nfs4_session *session;
	काष्ठा nfs4_slot *slot = res->sr_slot;
	काष्ठा nfs_client *clp;
	पूर्णांक status;
	पूर्णांक ret = 1;

	अगर (slot == शून्य)
		जाओ out_noaction;
	/* करोn't increment the sequence number if the task wasn't sent */
	अगर (!RPC_WAS_SENT(task) || slot->seq_करोne)
		जाओ out;

	session = slot->table->session;
	clp = session->clp;

	trace_nfs4_sequence_करोne(session, res);

	status = res->sr_status;
	अगर (task->tk_status == -NFS4ERR_DEADSESSION)
		status = -NFS4ERR_DEADSESSION;

	/* Check the SEQUENCE operation status */
	चयन (status) अणु
	हाल 0:
		/* Mark this sequence number as having been acked */
		nfs4_slot_sequence_acked(slot, slot->seq_nr);
		/* Update the slot's sequence and clientid lease समयr */
		slot->seq_करोne = 1;
		करो_renew_lease(clp, res->sr_बारtamp);
		/* Check sequence flags */
		nfs41_handle_sequence_flag_errors(clp, res->sr_status_flags,
				!!slot->privileged);
		nfs41_update_target_slotid(slot->table, slot, res);
		अवरोध;
	हाल 1:
		/*
		 * sr_status reमुख्यs 1 अगर an RPC level error occurred.
		 * The server may or may not have processed the sequence
		 * operation..
		 */
		nfs4_slot_sequence_record_sent(slot, slot->seq_nr);
		slot->seq_करोne = 1;
		जाओ out;
	हाल -NFS4ERR_DELAY:
		/* The server detected a resend of the RPC call and
		 * वापसed NFS4ERR_DELAY as per Section 2.10.6.2
		 * of RFC5661.
		 */
		dprपूर्णांकk("%s: slot=%u seq=%u: Operation in progress\n",
			__func__,
			slot->slot_nr,
			slot->seq_nr);
		nfs4_slot_sequence_acked(slot, slot->seq_nr);
		जाओ out_retry;
	हाल -NFS4ERR_RETRY_UNCACHED_REP:
	हाल -NFS4ERR_SEQ_FALSE_RETRY:
		/*
		 * The server thinks we tried to replay a request.
		 * Retry the call after bumping the sequence ID.
		 */
		nfs4_slot_sequence_acked(slot, slot->seq_nr);
		जाओ retry_new_seq;
	हाल -NFS4ERR_BADSLOT:
		/*
		 * The slot id we used was probably retired. Try again
		 * using a dअगरferent slot id.
		 */
		अगर (slot->slot_nr < slot->table->target_highest_slotid)
			जाओ session_recover;
		जाओ retry_noरुको;
	हाल -NFS4ERR_SEQ_MISORDERED:
		nfs4_slot_sequence_record_sent(slot, slot->seq_nr);
		/*
		 * Were one or more calls using this slot पूर्णांकerrupted?
		 * If the server never received the request, then our
		 * transmitted slot sequence number may be too high. However,
		 * अगर the server did receive the request then it might
		 * accidentally give us a reply with a mismatched operation.
		 * We can sort this out by sending a lone sequence operation
		 * to the server on the same slot.
		 */
		अगर ((s32)(slot->seq_nr - slot->seq_nr_last_acked) > 1) अणु
			slot->seq_nr--;
			अगर (task->tk_msg.rpc_proc != &nfs4_procedures[NFSPROC4_CLNT_SEQUENCE]) अणु
				nfs4_probe_sequence(clp, task->tk_msg.rpc_cred, slot);
				res->sr_slot = शून्य;
			पूर्ण
			जाओ retry_noरुको;
		पूर्ण
		/*
		 * RFC5661:
		 * A retry might be sent जबतक the original request is
		 * still in progress on the replier. The replier SHOULD
		 * deal with the issue by वापसing NFS4ERR_DELAY as the
		 * reply to SEQUENCE or CB_SEQUENCE operation, but
		 * implementations MAY वापस NFS4ERR_SEQ_MISORDERED.
		 *
		 * Restart the search after a delay.
		 */
		slot->seq_nr = slot->seq_nr_highest_sent;
		जाओ out_retry;
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_DEADSESSION:
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		जाओ session_recover;
	शेष:
		/* Just update the slot sequence no. */
		slot->seq_करोne = 1;
	पूर्ण
out:
	/* The session may be reset by one of the error handlers. */
	dprपूर्णांकk("%s: Error %d free the slot \n", __func__, res->sr_status);
out_noaction:
	वापस ret;
session_recover:
	nfs4_schedule_session_recovery(session, status);
	dprपूर्णांकk("%s ERROR: %d Reset session\n", __func__, status);
	nfs41_sequence_मुक्त_slot(res);
	जाओ out;
retry_new_seq:
	++slot->seq_nr;
retry_noरुको:
	अगर (rpc_restart_call_prepare(task)) अणु
		nfs41_sequence_मुक्त_slot(res);
		task->tk_status = 0;
		ret = 0;
	पूर्ण
	जाओ out;
out_retry:
	अगर (!rpc_restart_call(task))
		जाओ out;
	rpc_delay(task, NFS4_POLL_RETRY_MAX);
	वापस 0;
पूर्ण

पूर्णांक nfs41_sequence_करोne(काष्ठा rpc_task *task, काष्ठा nfs4_sequence_res *res)
अणु
	अगर (!nfs41_sequence_process(task, res))
		वापस 0;
	अगर (res->sr_slot != शून्य)
		nfs41_sequence_मुक्त_slot(res);
	वापस 1;

पूर्ण
EXPORT_SYMBOL_GPL(nfs41_sequence_करोne);

अटल पूर्णांक nfs4_sequence_process(काष्ठा rpc_task *task, काष्ठा nfs4_sequence_res *res)
अणु
	अगर (res->sr_slot == शून्य)
		वापस 1;
	अगर (res->sr_slot->table->session != शून्य)
		वापस nfs41_sequence_process(task, res);
	वापस nfs40_sequence_करोne(task, res);
पूर्ण

अटल व्योम nfs4_sequence_मुक्त_slot(काष्ठा nfs4_sequence_res *res)
अणु
	अगर (res->sr_slot != शून्य) अणु
		अगर (res->sr_slot->table->session != शून्य)
			nfs41_sequence_मुक्त_slot(res);
		अन्यथा
			nfs40_sequence_मुक्त_slot(res);
	पूर्ण
पूर्ण

पूर्णांक nfs4_sequence_करोne(काष्ठा rpc_task *task, काष्ठा nfs4_sequence_res *res)
अणु
	अगर (res->sr_slot == शून्य)
		वापस 1;
	अगर (!res->sr_slot->table->session)
		वापस nfs40_sequence_करोne(task, res);
	वापस nfs41_sequence_करोne(task, res);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_sequence_करोne);

अटल व्योम nfs41_call_sync_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_call_sync_data *data = calldata;

	dprपूर्णांकk("--> %s data->seq_server %p\n", __func__, data->seq_server);

	nfs4_setup_sequence(data->seq_server->nfs_client,
			    data->seq_args, data->seq_res, task);
पूर्ण

अटल व्योम nfs41_call_sync_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_call_sync_data *data = calldata;

	nfs41_sequence_करोne(task, data->seq_res);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs41_call_sync_ops = अणु
	.rpc_call_prepare = nfs41_call_sync_prepare,
	.rpc_call_करोne = nfs41_call_sync_करोne,
पूर्ण;

#अन्यथा	/* !CONFIG_NFS_V4_1 */

अटल पूर्णांक nfs4_sequence_process(काष्ठा rpc_task *task, काष्ठा nfs4_sequence_res *res)
अणु
	वापस nfs40_sequence_करोne(task, res);
पूर्ण

अटल व्योम nfs4_sequence_मुक्त_slot(काष्ठा nfs4_sequence_res *res)
अणु
	अगर (res->sr_slot != शून्य)
		nfs40_sequence_मुक्त_slot(res);
पूर्ण

पूर्णांक nfs4_sequence_करोne(काष्ठा rpc_task *task,
		       काष्ठा nfs4_sequence_res *res)
अणु
	वापस nfs40_sequence_करोne(task, res);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_sequence_करोne);

#पूर्ण_अगर	/* !CONFIG_NFS_V4_1 */

अटल व्योम nfs41_sequence_res_init(काष्ठा nfs4_sequence_res *res)
अणु
	res->sr_बारtamp = jअगरfies;
	res->sr_status_flags = 0;
	res->sr_status = 1;
पूर्ण

अटल
व्योम nfs4_sequence_attach_slot(काष्ठा nfs4_sequence_args *args,
		काष्ठा nfs4_sequence_res *res,
		काष्ठा nfs4_slot *slot)
अणु
	अगर (!slot)
		वापस;
	slot->privileged = args->sa_privileged ? 1 : 0;
	args->sa_slot = slot;

	res->sr_slot = slot;
पूर्ण

पूर्णांक nfs4_setup_sequence(काष्ठा nfs_client *client,
			काष्ठा nfs4_sequence_args *args,
			काष्ठा nfs4_sequence_res *res,
			काष्ठा rpc_task *task)
अणु
	काष्ठा nfs4_session *session = nfs4_get_session(client);
	काष्ठा nfs4_slot_table *tbl  = client->cl_slot_tbl;
	काष्ठा nfs4_slot *slot;

	/* slot alपढ़ोy allocated? */
	अगर (res->sr_slot != शून्य)
		जाओ out_start;

	अगर (session)
		tbl = &session->fc_slot_table;

	spin_lock(&tbl->slot_tbl_lock);
	/* The state manager will रुको until the slot table is empty */
	अगर (nfs4_slot_tbl_draining(tbl) && !args->sa_privileged)
		जाओ out_sleep;

	slot = nfs4_alloc_slot(tbl);
	अगर (IS_ERR(slot)) अणु
		अगर (slot == ERR_PTR(-ENOMEM))
			जाओ out_sleep_समयout;
		जाओ out_sleep;
	पूर्ण
	spin_unlock(&tbl->slot_tbl_lock);

	nfs4_sequence_attach_slot(args, res, slot);

	trace_nfs4_setup_sequence(session, args);
out_start:
	nfs41_sequence_res_init(res);
	rpc_call_start(task);
	वापस 0;
out_sleep_समयout:
	/* Try again in 1/4 second */
	अगर (args->sa_privileged)
		rpc_sleep_on_priority_समयout(&tbl->slot_tbl_रुकोq, task,
				jअगरfies + (HZ >> 2), RPC_PRIORITY_PRIVILEGED);
	अन्यथा
		rpc_sleep_on_समयout(&tbl->slot_tbl_रुकोq, task,
				शून्य, jअगरfies + (HZ >> 2));
	spin_unlock(&tbl->slot_tbl_lock);
	वापस -EAGAIN;
out_sleep:
	अगर (args->sa_privileged)
		rpc_sleep_on_priority(&tbl->slot_tbl_रुकोq, task,
				RPC_PRIORITY_PRIVILEGED);
	अन्यथा
		rpc_sleep_on(&tbl->slot_tbl_रुकोq, task, शून्य);
	spin_unlock(&tbl->slot_tbl_lock);
	वापस -EAGAIN;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_setup_sequence);

अटल व्योम nfs40_call_sync_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_call_sync_data *data = calldata;
	nfs4_setup_sequence(data->seq_server->nfs_client,
				data->seq_args, data->seq_res, task);
पूर्ण

अटल व्योम nfs40_call_sync_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_call_sync_data *data = calldata;
	nfs4_sequence_करोne(task, data->seq_res);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs40_call_sync_ops = अणु
	.rpc_call_prepare = nfs40_call_sync_prepare,
	.rpc_call_करोne = nfs40_call_sync_करोne,
पूर्ण;

अटल पूर्णांक nfs4_call_sync_custom(काष्ठा rpc_task_setup *task_setup)
अणु
	पूर्णांक ret;
	काष्ठा rpc_task *task;

	task = rpc_run_task(task_setup);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);

	ret = task->tk_status;
	rpc_put_task(task);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_करो_call_sync(काष्ठा rpc_clnt *clnt,
			     काष्ठा nfs_server *server,
			     काष्ठा rpc_message *msg,
			     काष्ठा nfs4_sequence_args *args,
			     काष्ठा nfs4_sequence_res *res,
			     अचिन्हित लघु task_flags)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs4_call_sync_data data = अणु
		.seq_server = server,
		.seq_args = args,
		.seq_res = res,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_client = clnt,
		.rpc_message = msg,
		.callback_ops = clp->cl_mvops->call_sync_ops,
		.callback_data = &data,
		.flags = task_flags,
	पूर्ण;

	वापस nfs4_call_sync_custom(&task_setup);
पूर्ण

अटल पूर्णांक nfs4_call_sync_sequence(काष्ठा rpc_clnt *clnt,
				   काष्ठा nfs_server *server,
				   काष्ठा rpc_message *msg,
				   काष्ठा nfs4_sequence_args *args,
				   काष्ठा nfs4_sequence_res *res)
अणु
	वापस nfs4_करो_call_sync(clnt, server, msg, args, res, 0);
पूर्ण


पूर्णांक nfs4_call_sync(काष्ठा rpc_clnt *clnt,
		   काष्ठा nfs_server *server,
		   काष्ठा rpc_message *msg,
		   काष्ठा nfs4_sequence_args *args,
		   काष्ठा nfs4_sequence_res *res,
		   पूर्णांक cache_reply)
अणु
	nfs4_init_sequence(args, res, cache_reply, 0);
	वापस nfs4_call_sync_sequence(clnt, server, msg, args, res);
पूर्ण

अटल व्योम
nfs4_inc_nlink_locked(काष्ठा inode *inode)
अणु
	nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE |
					     NFS_INO_INVALID_CTIME |
					     NFS_INO_INVALID_NLINK);
	inc_nlink(inode);
पूर्ण

अटल व्योम
nfs4_inc_nlink(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	nfs4_inc_nlink_locked(inode);
	spin_unlock(&inode->i_lock);
पूर्ण

अटल व्योम
nfs4_dec_nlink_locked(काष्ठा inode *inode)
अणु
	nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE |
					     NFS_INO_INVALID_CTIME |
					     NFS_INO_INVALID_NLINK);
	drop_nlink(inode);
पूर्ण

अटल व्योम
nfs4_update_changeattr_locked(काष्ठा inode *inode,
		काष्ठा nfs4_change_info *cinfo,
		अचिन्हित दीर्घ बारtamp, अचिन्हित दीर्घ cache_validity)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	u64 change_attr = inode_peek_iversion_raw(inode);

	cache_validity |= NFS_INO_INVALID_CTIME | NFS_INO_INVALID_MTIME;

	चयन (NFS_SERVER(inode)->change_attr_type) अणु
	हाल NFS4_CHANGE_TYPE_IS_UNDEFINED:
		अवरोध;
	हाल NFS4_CHANGE_TYPE_IS_TIME_METADATA:
		अगर ((s64)(change_attr - cinfo->after) > 0)
			जाओ out;
		अवरोध;
	शेष:
		अगर ((s64)(change_attr - cinfo->after) >= 0)
			जाओ out;
	पूर्ण

	अगर (cinfo->atomic && cinfo->beक्रमe == change_attr) अणु
		nfsi->attrसमयo_बारtamp = jअगरfies;
	पूर्ण अन्यथा अणु
		अगर (S_ISसूची(inode->i_mode)) अणु
			cache_validity |= NFS_INO_INVALID_DATA;
			nfs_क्रमce_lookup_revalidate(inode);
		पूर्ण अन्यथा अणु
			अगर (!NFS_PROTO(inode)->have_delegation(inode,
							       FMODE_READ))
				cache_validity |= NFS_INO_REVAL_PAGECACHE;
		पूर्ण

		अगर (cinfo->beक्रमe != change_attr)
			cache_validity |= NFS_INO_INVALID_ACCESS |
					  NFS_INO_INVALID_ACL |
					  NFS_INO_INVALID_XATTR;
	पूर्ण
	inode_set_iversion_raw(inode, cinfo->after);
	nfsi->पढ़ो_cache_jअगरfies = बारtamp;
	nfsi->attr_gencount = nfs_inc_attr_generation_counter();
	nfsi->cache_validity &= ~NFS_INO_INVALID_CHANGE;
out:
	nfs_set_cache_invalid(inode, cache_validity);
पूर्ण

व्योम
nfs4_update_changeattr(काष्ठा inode *dir, काष्ठा nfs4_change_info *cinfo,
		अचिन्हित दीर्घ बारtamp, अचिन्हित दीर्घ cache_validity)
अणु
	spin_lock(&dir->i_lock);
	nfs4_update_changeattr_locked(dir, cinfo, बारtamp, cache_validity);
	spin_unlock(&dir->i_lock);
पूर्ण

काष्ठा nfs4_खोलो_createattrs अणु
	काष्ठा nfs4_label *label;
	काष्ठा iattr *sattr;
	स्थिर __u32 verf[2];
पूर्ण;

अटल bool nfs4_clear_cap_atomic_खोलो_v1(काष्ठा nfs_server *server,
		पूर्णांक err, काष्ठा nfs4_exception *exception)
अणु
	अगर (err != -EINVAL)
		वापस false;
	अगर (!(server->caps & NFS_CAP_ATOMIC_OPEN_V1))
		वापस false;
	server->caps &= ~NFS_CAP_ATOMIC_OPEN_V1;
	exception->retry = 1;
	वापस true;
पूर्ण

अटल भ_शेषe_t _nfs4_ctx_to_accessmode(स्थिर काष्ठा nfs_खोलो_context *ctx)
अणु
	 वापस ctx->mode & (FMODE_READ|FMODE_WRITE|FMODE_EXEC);
पूर्ण

अटल भ_शेषe_t _nfs4_ctx_to_खोलोmode(स्थिर काष्ठा nfs_खोलो_context *ctx)
अणु
	भ_शेषe_t ret = ctx->mode & (FMODE_READ|FMODE_WRITE);

	वापस (ctx->mode & FMODE_EXEC) ? FMODE_READ | ret : ret;
पूर्ण

अटल u32
nfs4_map_atomic_खोलो_share(काष्ठा nfs_server *server,
		भ_शेषe_t भ_शेषe, पूर्णांक खोलोflags)
अणु
	u32 res = 0;

	चयन (भ_शेषe & (FMODE_READ | FMODE_WRITE)) अणु
	हाल FMODE_READ:
		res = NFS4_SHARE_ACCESS_READ;
		अवरोध;
	हाल FMODE_WRITE:
		res = NFS4_SHARE_ACCESS_WRITE;
		अवरोध;
	हाल FMODE_READ|FMODE_WRITE:
		res = NFS4_SHARE_ACCESS_BOTH;
	पूर्ण
	अगर (!(server->caps & NFS_CAP_ATOMIC_OPEN_V1))
		जाओ out;
	/* Want no delegation अगर we're using O_सूचीECT */
	अगर (खोलोflags & O_सूचीECT)
		res |= NFS4_SHARE_WANT_NO_DELEG;
out:
	वापस res;
पूर्ण

अटल क्रमागत खोलो_claim_type4
nfs4_map_atomic_खोलो_claim(काष्ठा nfs_server *server,
		क्रमागत खोलो_claim_type4 claim)
अणु
	अगर (server->caps & NFS_CAP_ATOMIC_OPEN_V1)
		वापस claim;
	चयन (claim) अणु
	शेष:
		वापस claim;
	हाल NFS4_OPEN_CLAIM_FH:
		वापस NFS4_OPEN_CLAIM_शून्य;
	हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		वापस NFS4_OPEN_CLAIM_DELEGATE_CUR;
	हाल NFS4_OPEN_CLAIM_DELEG_PREV_FH:
		वापस NFS4_OPEN_CLAIM_DELEGATE_PREV;
	पूर्ण
पूर्ण

अटल व्योम nfs4_init_खोलोdata_res(काष्ठा nfs4_खोलोdata *p)
अणु
	p->o_res.f_attr = &p->f_attr;
	p->o_res.f_label = p->f_label;
	p->o_res.seqid = p->o_arg.seqid;
	p->c_res.seqid = p->c_arg.seqid;
	p->o_res.server = p->o_arg.server;
	p->o_res.access_request = p->o_arg.access;
	nfs_fattr_init(&p->f_attr);
	nfs_fattr_init_names(&p->f_attr, &p->owner_name, &p->group_name);
पूर्ण

अटल काष्ठा nfs4_खोलोdata *nfs4_खोलोdata_alloc(काष्ठा dentry *dentry,
		काष्ठा nfs4_state_owner *sp, भ_शेषe_t भ_शेषe, पूर्णांक flags,
		स्थिर काष्ठा nfs4_खोलो_createattrs *c,
		क्रमागत खोलो_claim_type4 claim,
		gfp_t gfp_mask)
अणु
	काष्ठा dentry *parent = dget_parent(dentry);
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs_seqid *(*alloc_seqid)(काष्ठा nfs_seqid_counter *, gfp_t);
	काष्ठा nfs4_label *label = (c != शून्य) ? c->label : शून्य;
	काष्ठा nfs4_खोलोdata *p;

	p = kzalloc(माप(*p), gfp_mask);
	अगर (p == शून्य)
		जाओ err;

	p->f_label = nfs4_label_alloc(server, gfp_mask);
	अगर (IS_ERR(p->f_label))
		जाओ err_मुक्त_p;

	p->a_label = nfs4_label_alloc(server, gfp_mask);
	अगर (IS_ERR(p->a_label))
		जाओ err_मुक्त_f;

	alloc_seqid = server->nfs_client->cl_mvops->alloc_seqid;
	p->o_arg.seqid = alloc_seqid(&sp->so_seqid, gfp_mask);
	अगर (IS_ERR(p->o_arg.seqid))
		जाओ err_मुक्त_label;
	nfs_sb_active(dentry->d_sb);
	p->dentry = dget(dentry);
	p->dir = parent;
	p->owner = sp;
	atomic_inc(&sp->so_count);
	p->o_arg.खोलो_flags = flags;
	p->o_arg.भ_शेषe = भ_शेषe & (FMODE_READ|FMODE_WRITE);
	p->o_arg.claim = nfs4_map_atomic_खोलो_claim(server, claim);
	p->o_arg.share_access = nfs4_map_atomic_खोलो_share(server,
			भ_शेषe, flags);
	अगर (flags & O_CREAT) अणु
		p->o_arg.umask = current_umask();
		p->o_arg.label = nfs4_label_copy(p->a_label, label);
		अगर (c->sattr != शून्य && c->sattr->ia_valid != 0) अणु
			p->o_arg.u.attrs = &p->attrs;
			स_नकल(&p->attrs, c->sattr, माप(p->attrs));

			स_नकल(p->o_arg.u.verअगरier.data, c->verf,
					माप(p->o_arg.u.verअगरier.data));
		पूर्ण
	पूर्ण
	/* करोn't put an ACCESS op in OPEN compound अगर O_EXCL, because ACCESS
	 * will वापस permission denied क्रम all bits until बंद */
	अगर (!(flags & O_EXCL)) अणु
		/* ask server to check क्रम all possible rights as results
		 * are cached */
		चयन (p->o_arg.claim) अणु
		शेष:
			अवरोध;
		हाल NFS4_OPEN_CLAIM_शून्य:
		हाल NFS4_OPEN_CLAIM_FH:
			p->o_arg.access = NFS4_ACCESS_READ |
				NFS4_ACCESS_MODIFY |
				NFS4_ACCESS_EXTEND |
				NFS4_ACCESS_EXECUTE;
#अगर_घोषित CONFIG_NFS_V4_2
			अगर (server->caps & NFS_CAP_XATTR)
				p->o_arg.access |= NFS4_ACCESS_XAREAD |
				    NFS4_ACCESS_XAWRITE |
				    NFS4_ACCESS_XALIST;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	p->o_arg.clientid = server->nfs_client->cl_clientid;
	p->o_arg.id.create_समय = kसमय_प्रकारo_ns(sp->so_seqid.create_समय);
	p->o_arg.id.uniquअगरier = sp->so_seqid.owner_id;
	p->o_arg.name = &dentry->d_name;
	p->o_arg.server = server;
	p->o_arg.biपंचांगask = nfs4_biपंचांगask(server, label);
	p->o_arg.खोलो_biपंचांगap = &nfs4_fattr_biपंचांगap[0];
	चयन (p->o_arg.claim) अणु
	हाल NFS4_OPEN_CLAIM_शून्य:
	हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
	हाल NFS4_OPEN_CLAIM_DELEGATE_PREV:
		p->o_arg.fh = NFS_FH(dir);
		अवरोध;
	हाल NFS4_OPEN_CLAIM_PREVIOUS:
	हाल NFS4_OPEN_CLAIM_FH:
	हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
	हाल NFS4_OPEN_CLAIM_DELEG_PREV_FH:
		p->o_arg.fh = NFS_FH(d_inode(dentry));
	पूर्ण
	p->c_arg.fh = &p->o_res.fh;
	p->c_arg.stateid = &p->o_res.stateid;
	p->c_arg.seqid = p->o_arg.seqid;
	nfs4_init_खोलोdata_res(p);
	kref_init(&p->kref);
	वापस p;

err_मुक्त_label:
	nfs4_label_मुक्त(p->a_label);
err_मुक्त_f:
	nfs4_label_मुक्त(p->f_label);
err_मुक्त_p:
	kमुक्त(p);
err:
	dput(parent);
	वापस शून्य;
पूर्ण

अटल व्योम nfs4_खोलोdata_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा nfs4_खोलोdata *p = container_of(kref,
			काष्ठा nfs4_खोलोdata, kref);
	काष्ठा super_block *sb = p->dentry->d_sb;

	nfs4_lgखोलो_release(p->lgp);
	nfs_मुक्त_seqid(p->o_arg.seqid);
	nfs4_sequence_मुक्त_slot(&p->o_res.seq_res);
	अगर (p->state != शून्य)
		nfs4_put_खोलो_state(p->state);
	nfs4_put_state_owner(p->owner);

	nfs4_label_मुक्त(p->a_label);
	nfs4_label_मुक्त(p->f_label);

	dput(p->dir);
	dput(p->dentry);
	nfs_sb_deactive(sb);
	nfs_fattr_मुक्त_names(&p->f_attr);
	kमुक्त(p->f_attr.mdsthreshold);
	kमुक्त(p);
पूर्ण

अटल व्योम nfs4_खोलोdata_put(काष्ठा nfs4_खोलोdata *p)
अणु
	अगर (p != शून्य)
		kref_put(&p->kref, nfs4_खोलोdata_मुक्त);
पूर्ण

अटल bool nfs4_mode_match_खोलो_stateid(काष्ठा nfs4_state *state,
		भ_शेषe_t भ_शेषe)
अणु
	चयन(भ_शेषe & (FMODE_READ|FMODE_WRITE)) अणु
	हाल FMODE_READ|FMODE_WRITE:
		वापस state->n_rdwr != 0;
	हाल FMODE_WRITE:
		वापस state->n_wronly != 0;
	हाल FMODE_READ:
		वापस state->n_rकरोnly != 0;
	पूर्ण
	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

अटल पूर्णांक can_खोलो_cached(काष्ठा nfs4_state *state, भ_शेषe_t mode,
		पूर्णांक खोलो_mode, क्रमागत खोलो_claim_type4 claim)
अणु
	पूर्णांक ret = 0;

	अगर (खोलो_mode & (O_EXCL|O_TRUNC))
		जाओ out;
	चयन (claim) अणु
	हाल NFS4_OPEN_CLAIM_शून्य:
	हाल NFS4_OPEN_CLAIM_FH:
		जाओ out;
	शेष:
		अवरोध;
	पूर्ण
	चयन (mode & (FMODE_READ|FMODE_WRITE)) अणु
		हाल FMODE_READ:
			ret |= test_bit(NFS_O_RDONLY_STATE, &state->flags) != 0
				&& state->n_rकरोnly != 0;
			अवरोध;
		हाल FMODE_WRITE:
			ret |= test_bit(NFS_O_WRONLY_STATE, &state->flags) != 0
				&& state->n_wronly != 0;
			अवरोध;
		हाल FMODE_READ|FMODE_WRITE:
			ret |= test_bit(NFS_O_RDWR_STATE, &state->flags) != 0
				&& state->n_rdwr != 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक can_खोलो_delegated(काष्ठा nfs_delegation *delegation, भ_शेषe_t भ_शेषe,
		क्रमागत खोलो_claim_type4 claim)
अणु
	अगर (delegation == शून्य)
		वापस 0;
	अगर ((delegation->type & भ_शेषe) != भ_शेषe)
		वापस 0;
	चयन (claim) अणु
	हाल NFS4_OPEN_CLAIM_शून्य:
	हाल NFS4_OPEN_CLAIM_FH:
		अवरोध;
	हाल NFS4_OPEN_CLAIM_PREVIOUS:
		अगर (!test_bit(NFS_DELEGATION_NEED_RECLAIM, &delegation->flags))
			अवरोध;
		fallthrough;
	शेष:
		वापस 0;
	पूर्ण
	nfs_mark_delegation_referenced(delegation);
	वापस 1;
पूर्ण

अटल व्योम update_खोलो_stateflags(काष्ठा nfs4_state *state, भ_शेषe_t भ_शेषe)
अणु
	चयन (भ_शेषe) अणु
		हाल FMODE_WRITE:
			state->n_wronly++;
			अवरोध;
		हाल FMODE_READ:
			state->n_rकरोnly++;
			अवरोध;
		हाल FMODE_READ|FMODE_WRITE:
			state->n_rdwr++;
	पूर्ण
	nfs4_state_set_mode_locked(state, state->state | भ_शेषe);
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
अटल bool nfs_खोलो_stateid_recover_खोलोmode(काष्ठा nfs4_state *state)
अणु
	अगर (state->n_rकरोnly && !test_bit(NFS_O_RDONLY_STATE, &state->flags))
		वापस true;
	अगर (state->n_wronly && !test_bit(NFS_O_WRONLY_STATE, &state->flags))
		वापस true;
	अगर (state->n_rdwr && !test_bit(NFS_O_RDWR_STATE, &state->flags))
		वापस true;
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल व्योम nfs_state_log_update_खोलो_stateid(काष्ठा nfs4_state *state)
अणु
	अगर (test_and_clear_bit(NFS_STATE_CHANGE_WAIT, &state->flags))
		wake_up_all(&state->रुकोq);
पूर्ण

अटल व्योम nfs_test_and_clear_all_खोलो_stateid(काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_client *clp = state->owner->so_server->nfs_client;
	bool need_recover = false;

	अगर (test_and_clear_bit(NFS_O_RDONLY_STATE, &state->flags) && state->n_rकरोnly)
		need_recover = true;
	अगर (test_and_clear_bit(NFS_O_WRONLY_STATE, &state->flags) && state->n_wronly)
		need_recover = true;
	अगर (test_and_clear_bit(NFS_O_RDWR_STATE, &state->flags) && state->n_rdwr)
		need_recover = true;
	अगर (need_recover)
		nfs4_state_mark_reclaim_nograce(clp, state);
पूर्ण

/*
 * Check क्रम whether or not the caller may update the खोलो stateid
 * to the value passed in by stateid.
 *
 * Note: This function relies heavily on the server implementing
 * RFC7530 Section 9.1.4.2, and RFC5661 Section 8.2.2
 * correctly.
 * i.e. The stateid seqids have to be initialised to 1, and
 * are then incremented on every state transition.
 */
अटल bool nfs_stateid_is_sequential(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *stateid)
अणु
	अगर (test_bit(NFS_OPEN_STATE, &state->flags)) अणु
		/* The common हाल - we're updating to a new sequence number */
		अगर (nfs4_stateid_match_other(stateid, &state->खोलो_stateid) &&
			nfs4_stateid_is_next(&state->खोलो_stateid, stateid)) अणु
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* This is the first OPEN in this generation */
		अगर (stateid->seqid == cpu_to_be32(1))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम nfs_resync_खोलो_stateid_locked(काष्ठा nfs4_state *state)
अणु
	अगर (!(state->n_wronly || state->n_rकरोnly || state->n_rdwr))
		वापस;
	अगर (state->n_wronly)
		set_bit(NFS_O_WRONLY_STATE, &state->flags);
	अगर (state->n_rकरोnly)
		set_bit(NFS_O_RDONLY_STATE, &state->flags);
	अगर (state->n_rdwr)
		set_bit(NFS_O_RDWR_STATE, &state->flags);
	set_bit(NFS_OPEN_STATE, &state->flags);
पूर्ण

अटल व्योम nfs_clear_खोलो_stateid_locked(काष्ठा nfs4_state *state,
		nfs4_stateid *stateid, भ_शेषe_t भ_शेषe)
अणु
	clear_bit(NFS_O_RDWR_STATE, &state->flags);
	चयन (भ_शेषe & (FMODE_READ|FMODE_WRITE)) अणु
	हाल FMODE_WRITE:
		clear_bit(NFS_O_RDONLY_STATE, &state->flags);
		अवरोध;
	हाल FMODE_READ:
		clear_bit(NFS_O_WRONLY_STATE, &state->flags);
		अवरोध;
	हाल 0:
		clear_bit(NFS_O_RDONLY_STATE, &state->flags);
		clear_bit(NFS_O_WRONLY_STATE, &state->flags);
		clear_bit(NFS_OPEN_STATE, &state->flags);
	पूर्ण
	अगर (stateid == शून्य)
		वापस;
	/* Handle OPEN+OPEN_DOWNGRADE races */
	अगर (nfs4_stateid_match_other(stateid, &state->खोलो_stateid) &&
	    !nfs4_stateid_is_newer(stateid, &state->खोलो_stateid)) अणु
		nfs_resync_खोलो_stateid_locked(state);
		जाओ out;
	पूर्ण
	अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0)
		nfs4_stateid_copy(&state->stateid, stateid);
	nfs4_stateid_copy(&state->खोलो_stateid, stateid);
	trace_nfs4_खोलो_stateid_update(state->inode, stateid, 0);
out:
	nfs_state_log_update_खोलो_stateid(state);
पूर्ण

अटल व्योम nfs_clear_खोलो_stateid(काष्ठा nfs4_state *state,
	nfs4_stateid *arg_stateid,
	nfs4_stateid *stateid, भ_शेषe_t भ_शेषe)
अणु
	ग_लिखो_seqlock(&state->seqlock);
	/* Ignore, अगर the CLOSE argment करोesn't match the current stateid */
	अगर (nfs4_state_match_खोलो_stateid_other(state, arg_stateid))
		nfs_clear_खोलो_stateid_locked(state, stateid, भ_शेषe);
	ग_लिखो_sequnlock(&state->seqlock);
	अगर (test_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags))
		nfs4_schedule_state_manager(state->owner->so_server->nfs_client);
पूर्ण

अटल व्योम nfs_set_खोलो_stateid_locked(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *stateid, nfs4_stateid *मुक्तme)
	__must_hold(&state->owner->so_lock)
	__must_hold(&state->seqlock)
	__must_hold(RCU)

अणु
	DEFINE_WAIT(रुको);
	पूर्णांक status = 0;
	क्रम (;;) अणु

		अगर (nfs_stateid_is_sequential(state, stateid))
			अवरोध;

		अगर (status)
			अवरोध;
		/* Rely on seqids क्रम serialisation with NFSv4.0 */
		अगर (!nfs4_has_session(NFS_SERVER(state->inode)->nfs_client))
			अवरोध;

		set_bit(NFS_STATE_CHANGE_WAIT, &state->flags);
		prepare_to_रुको(&state->रुकोq, &रुको, TASK_KILLABLE);
		/*
		 * Ensure we process the state changes in the same order
		 * in which the server processed them by delaying the
		 * update of the stateid until we are in sequence.
		 */
		ग_लिखो_sequnlock(&state->seqlock);
		spin_unlock(&state->owner->so_lock);
		rcu_पढ़ो_unlock();
		trace_nfs4_खोलो_stateid_update_रुको(state->inode, stateid, 0);

		अगर (!fatal_संकेत_pending(current)) अणु
			अगर (schedule_समयout(5*HZ) == 0)
				status = -EAGAIN;
			अन्यथा
				status = 0;
		पूर्ण अन्यथा
			status = -EINTR;
		finish_रुको(&state->रुकोq, &रुको);
		rcu_पढ़ो_lock();
		spin_lock(&state->owner->so_lock);
		ग_लिखो_seqlock(&state->seqlock);
	पूर्ण

	अगर (test_bit(NFS_OPEN_STATE, &state->flags) &&
	    !nfs4_stateid_match_other(stateid, &state->खोलो_stateid)) अणु
		nfs4_stateid_copy(मुक्तme, &state->खोलो_stateid);
		nfs_test_and_clear_all_खोलो_stateid(state);
	पूर्ण

	अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0)
		nfs4_stateid_copy(&state->stateid, stateid);
	nfs4_stateid_copy(&state->खोलो_stateid, stateid);
	trace_nfs4_खोलो_stateid_update(state->inode, stateid, status);
	nfs_state_log_update_खोलो_stateid(state);
पूर्ण

अटल व्योम nfs_state_set_खोलो_stateid(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *खोलो_stateid,
		भ_शेषe_t भ_शेषe,
		nfs4_stateid *मुक्तme)
अणु
	/*
	 * Protect the call to nfs4_state_set_mode_locked and
	 * serialise the stateid update
	 */
	ग_लिखो_seqlock(&state->seqlock);
	nfs_set_खोलो_stateid_locked(state, खोलो_stateid, मुक्तme);
	चयन (भ_शेषe) अणु
	हाल FMODE_READ:
		set_bit(NFS_O_RDONLY_STATE, &state->flags);
		अवरोध;
	हाल FMODE_WRITE:
		set_bit(NFS_O_WRONLY_STATE, &state->flags);
		अवरोध;
	हाल FMODE_READ|FMODE_WRITE:
		set_bit(NFS_O_RDWR_STATE, &state->flags);
	पूर्ण
	set_bit(NFS_OPEN_STATE, &state->flags);
	ग_लिखो_sequnlock(&state->seqlock);
पूर्ण

अटल व्योम nfs_state_clear_खोलो_state_flags(काष्ठा nfs4_state *state)
अणु
	clear_bit(NFS_O_RDWR_STATE, &state->flags);
	clear_bit(NFS_O_WRONLY_STATE, &state->flags);
	clear_bit(NFS_O_RDONLY_STATE, &state->flags);
	clear_bit(NFS_OPEN_STATE, &state->flags);
पूर्ण

अटल व्योम nfs_state_set_delegation(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *deleg_stateid,
		भ_शेषe_t भ_शेषe)
अणु
	/*
	 * Protect the call to nfs4_state_set_mode_locked and
	 * serialise the stateid update
	 */
	ग_लिखो_seqlock(&state->seqlock);
	nfs4_stateid_copy(&state->stateid, deleg_stateid);
	set_bit(NFS_DELEGATED_STATE, &state->flags);
	ग_लिखो_sequnlock(&state->seqlock);
पूर्ण

अटल व्योम nfs_state_clear_delegation(काष्ठा nfs4_state *state)
अणु
	ग_लिखो_seqlock(&state->seqlock);
	nfs4_stateid_copy(&state->stateid, &state->खोलो_stateid);
	clear_bit(NFS_DELEGATED_STATE, &state->flags);
	ग_लिखो_sequnlock(&state->seqlock);
पूर्ण

पूर्णांक update_खोलो_stateid(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *खोलो_stateid,
		स्थिर nfs4_stateid *delegation,
		भ_शेषe_t भ_शेषe)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs_inode *nfsi = NFS_I(state->inode);
	काष्ठा nfs_delegation *deleg_cur;
	nfs4_stateid मुक्तme = अणु पूर्ण;
	पूर्णांक ret = 0;

	भ_शेषe &= (FMODE_READ|FMODE_WRITE);

	rcu_पढ़ो_lock();
	spin_lock(&state->owner->so_lock);
	अगर (खोलो_stateid != शून्य) अणु
		nfs_state_set_खोलो_stateid(state, खोलो_stateid, भ_शेषe, &मुक्तme);
		ret = 1;
	पूर्ण

	deleg_cur = nfs4_get_valid_delegation(state->inode);
	अगर (deleg_cur == शून्य)
		जाओ no_delegation;

	spin_lock(&deleg_cur->lock);
	अगर (rcu_dereference(nfsi->delegation) != deleg_cur ||
	   test_bit(NFS_DELEGATION_RETURNING, &deleg_cur->flags) ||
	    (deleg_cur->type & भ_शेषe) != भ_शेषe)
		जाओ no_delegation_unlock;

	अगर (delegation == शून्य)
		delegation = &deleg_cur->stateid;
	अन्यथा अगर (!nfs4_stateid_match_other(&deleg_cur->stateid, delegation))
		जाओ no_delegation_unlock;

	nfs_mark_delegation_referenced(deleg_cur);
	nfs_state_set_delegation(state, &deleg_cur->stateid, भ_शेषe);
	ret = 1;
no_delegation_unlock:
	spin_unlock(&deleg_cur->lock);
no_delegation:
	अगर (ret)
		update_खोलो_stateflags(state, भ_शेषe);
	spin_unlock(&state->owner->so_lock);
	rcu_पढ़ो_unlock();

	अगर (test_bit(NFS_STATE_RECLAIM_NOGRACE, &state->flags))
		nfs4_schedule_state_manager(clp);
	अगर (मुक्तme.type != 0)
		nfs4_test_and_मुक्त_stateid(server, &मुक्तme,
				state->owner->so_cred);

	वापस ret;
पूर्ण

अटल bool nfs4_update_lock_stateid(काष्ठा nfs4_lock_state *lsp,
		स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs4_state *state = lsp->ls_state;
	bool ret = false;

	spin_lock(&state->state_lock);
	अगर (!nfs4_stateid_match_other(stateid, &lsp->ls_stateid))
		जाओ out_noupdate;
	अगर (!nfs4_stateid_is_newer(stateid, &lsp->ls_stateid))
		जाओ out_noupdate;
	nfs4_stateid_copy(&lsp->ls_stateid, stateid);
	ret = true;
out_noupdate:
	spin_unlock(&state->state_lock);
	वापस ret;
पूर्ण

अटल व्योम nfs4_वापस_incompatible_delegation(काष्ठा inode *inode, भ_शेषe_t भ_शेषe)
अणु
	काष्ठा nfs_delegation *delegation;

	भ_शेषe &= FMODE_READ|FMODE_WRITE;
	rcu_पढ़ो_lock();
	delegation = nfs4_get_valid_delegation(inode);
	अगर (delegation == शून्य || (delegation->type & भ_शेषe) == भ_शेषe) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();
	nfs4_inode_वापस_delegation(inode);
पूर्ण

अटल काष्ठा nfs4_state *nfs4_try_खोलो_cached(काष्ठा nfs4_खोलोdata *खोलोdata)
अणु
	काष्ठा nfs4_state *state = खोलोdata->state;
	काष्ठा nfs_delegation *delegation;
	पूर्णांक खोलो_mode = खोलोdata->o_arg.खोलो_flags;
	भ_शेषe_t भ_शेषe = खोलोdata->o_arg.भ_शेषe;
	क्रमागत खोलो_claim_type4 claim = खोलोdata->o_arg.claim;
	nfs4_stateid stateid;
	पूर्णांक ret = -EAGAIN;

	क्रम (;;) अणु
		spin_lock(&state->owner->so_lock);
		अगर (can_खोलो_cached(state, भ_शेषe, खोलो_mode, claim)) अणु
			update_खोलो_stateflags(state, भ_शेषe);
			spin_unlock(&state->owner->so_lock);
			जाओ out_वापस_state;
		पूर्ण
		spin_unlock(&state->owner->so_lock);
		rcu_पढ़ो_lock();
		delegation = nfs4_get_valid_delegation(state->inode);
		अगर (!can_खोलो_delegated(delegation, भ_शेषe, claim)) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण
		/* Save the delegation */
		nfs4_stateid_copy(&stateid, &delegation->stateid);
		rcu_पढ़ो_unlock();
		nfs_release_seqid(खोलोdata->o_arg.seqid);
		अगर (!खोलोdata->is_recover) अणु
			ret = nfs_may_खोलो(state->inode, state->owner->so_cred, खोलो_mode);
			अगर (ret != 0)
				जाओ out;
		पूर्ण
		ret = -EAGAIN;

		/* Try to update the stateid using the delegation */
		अगर (update_खोलो_stateid(state, शून्य, &stateid, भ_शेषe))
			जाओ out_वापस_state;
	पूर्ण
out:
	वापस ERR_PTR(ret);
out_वापस_state:
	refcount_inc(&state->count);
	वापस state;
पूर्ण

अटल व्योम
nfs4_खोलोdata_check_deleg(काष्ठा nfs4_खोलोdata *data, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_client *clp = NFS_SERVER(state->inode)->nfs_client;
	काष्ठा nfs_delegation *delegation;
	पूर्णांक delegation_flags = 0;

	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(state->inode)->delegation);
	अगर (delegation)
		delegation_flags = delegation->flags;
	rcu_पढ़ो_unlock();
	चयन (data->o_arg.claim) अणु
	शेष:
		अवरोध;
	हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
	हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
		pr_err_ratelimited("NFS: Broken NFSv4 server %s is "
				   "returning a delegation for "
				   "OPEN(CLAIM_DELEGATE_CUR)\n",
				   clp->cl_hostname);
		वापस;
	पूर्ण
	अगर ((delegation_flags & 1UL<<NFS_DELEGATION_NEED_RECLAIM) == 0)
		nfs_inode_set_delegation(state->inode,
				data->owner->so_cred,
				data->o_res.delegation_type,
				&data->o_res.delegation,
				data->o_res.pagemod_limit);
	अन्यथा
		nfs_inode_reclaim_delegation(state->inode,
				data->owner->so_cred,
				data->o_res.delegation_type,
				&data->o_res.delegation,
				data->o_res.pagemod_limit);

	अगर (data->o_res.करो_recall)
		nfs_async_inode_वापस_delegation(state->inode,
						  &data->o_res.delegation);
पूर्ण

/*
 * Check the inode attributes against the CLAIM_PREVIOUS वापसed attributes
 * and update the nfs4_state.
 */
अटल काष्ठा nfs4_state *
_nfs4_खोलोdata_reclaim_to_nfs4_state(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा inode *inode = data->state->inode;
	काष्ठा nfs4_state *state = data->state;
	पूर्णांक ret;

	अगर (!data->rpc_करोne) अणु
		अगर (data->rpc_status)
			वापस ERR_PTR(data->rpc_status);
		/* cached खोलोs have alपढ़ोy been processed */
		जाओ update;
	पूर्ण

	ret = nfs_refresh_inode(inode, &data->f_attr);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (data->o_res.delegation_type != 0)
		nfs4_खोलोdata_check_deleg(data, state);
update:
	अगर (!update_खोलो_stateid(state, &data->o_res.stateid,
				शून्य, data->o_arg.भ_शेषe))
		वापस ERR_PTR(-EAGAIN);
	refcount_inc(&state->count);

	वापस state;
पूर्ण

अटल काष्ठा inode *
nfs4_खोलोdata_get_inode(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा inode *inode;

	चयन (data->o_arg.claim) अणु
	हाल NFS4_OPEN_CLAIM_शून्य:
	हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
	हाल NFS4_OPEN_CLAIM_DELEGATE_PREV:
		अगर (!(data->f_attr.valid & NFS_ATTR_FATTR))
			वापस ERR_PTR(-EAGAIN);
		inode = nfs_fhget(data->dir->d_sb, &data->o_res.fh,
				&data->f_attr, data->f_label);
		अवरोध;
	शेष:
		inode = d_inode(data->dentry);
		ihold(inode);
		nfs_refresh_inode(inode, &data->f_attr);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा nfs4_state *
nfs4_खोलोdata_find_nfs4_state(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा nfs4_state *state;
	काष्ठा inode *inode;

	inode = nfs4_खोलोdata_get_inode(data);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (data->state != शून्य && data->state->inode == inode) अणु
		state = data->state;
		refcount_inc(&state->count);
	पूर्ण अन्यथा
		state = nfs4_get_खोलो_state(inode, data->owner);
	iput(inode);
	अगर (state == शून्य)
		state = ERR_PTR(-ENOMEM);
	वापस state;
पूर्ण

अटल काष्ठा nfs4_state *
_nfs4_खोलोdata_to_nfs4_state(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा nfs4_state *state;

	अगर (!data->rpc_करोne) अणु
		state = nfs4_try_खोलो_cached(data);
		trace_nfs4_cached_खोलो(data->state);
		जाओ out;
	पूर्ण

	state = nfs4_खोलोdata_find_nfs4_state(data);
	अगर (IS_ERR(state))
		जाओ out;

	अगर (data->o_res.delegation_type != 0)
		nfs4_खोलोdata_check_deleg(data, state);
	अगर (!update_खोलो_stateid(state, &data->o_res.stateid,
				शून्य, data->o_arg.भ_शेषe)) अणु
		nfs4_put_खोलो_state(state);
		state = ERR_PTR(-EAGAIN);
	पूर्ण
out:
	nfs_release_seqid(data->o_arg.seqid);
	वापस state;
पूर्ण

अटल काष्ठा nfs4_state *
nfs4_खोलोdata_to_nfs4_state(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा nfs4_state *ret;

	अगर (data->o_arg.claim == NFS4_OPEN_CLAIM_PREVIOUS)
		ret =_nfs4_खोलोdata_reclaim_to_nfs4_state(data);
	अन्यथा
		ret = _nfs4_खोलोdata_to_nfs4_state(data);
	nfs4_sequence_मुक्त_slot(&data->o_res.seq_res);
	वापस ret;
पूर्ण

अटल काष्ठा nfs_खोलो_context *
nfs4_state_find_खोलो_context_mode(काष्ठा nfs4_state *state, भ_शेषe_t mode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(state->inode);
	काष्ठा nfs_खोलो_context *ctx;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(ctx, &nfsi->खोलो_files, list) अणु
		अगर (ctx->state != state)
			जारी;
		अगर ((ctx->mode & mode) != mode)
			जारी;
		अगर (!get_nfs_खोलो_context(ctx))
			जारी;
		rcu_पढ़ो_unlock();
		वापस ctx;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल काष्ठा nfs_खोलो_context *
nfs4_state_find_खोलो_context(काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_खोलो_context *ctx;

	ctx = nfs4_state_find_खोलो_context_mode(state, FMODE_READ|FMODE_WRITE);
	अगर (!IS_ERR(ctx))
		वापस ctx;
	ctx = nfs4_state_find_खोलो_context_mode(state, FMODE_WRITE);
	अगर (!IS_ERR(ctx))
		वापस ctx;
	वापस nfs4_state_find_खोलो_context_mode(state, FMODE_READ);
पूर्ण

अटल काष्ठा nfs4_खोलोdata *nfs4_खोलो_recoverdata_alloc(काष्ठा nfs_खोलो_context *ctx,
		काष्ठा nfs4_state *state, क्रमागत खोलो_claim_type4 claim)
अणु
	काष्ठा nfs4_खोलोdata *खोलोdata;

	खोलोdata = nfs4_खोलोdata_alloc(ctx->dentry, state->owner, 0, 0,
			शून्य, claim, GFP_NOFS);
	अगर (खोलोdata == शून्य)
		वापस ERR_PTR(-ENOMEM);
	खोलोdata->state = state;
	refcount_inc(&state->count);
	वापस खोलोdata;
पूर्ण

अटल पूर्णांक nfs4_खोलो_recover_helper(काष्ठा nfs4_खोलोdata *खोलोdata,
		भ_शेषe_t भ_शेषe)
अणु
	काष्ठा nfs4_state *newstate;
	पूर्णांक ret;

	अगर (!nfs4_mode_match_खोलो_stateid(खोलोdata->state, भ_शेषe))
		वापस 0;
	खोलोdata->o_arg.खोलो_flags = 0;
	खोलोdata->o_arg.भ_शेषe = भ_शेषe;
	खोलोdata->o_arg.share_access = nfs4_map_atomic_खोलो_share(
			NFS_SB(खोलोdata->dentry->d_sb),
			भ_शेषe, 0);
	स_रखो(&खोलोdata->o_res, 0, माप(खोलोdata->o_res));
	स_रखो(&खोलोdata->c_res, 0, माप(खोलोdata->c_res));
	nfs4_init_खोलोdata_res(खोलोdata);
	ret = _nfs4_recover_proc_खोलो(खोलोdata);
	अगर (ret != 0)
		वापस ret; 
	newstate = nfs4_खोलोdata_to_nfs4_state(खोलोdata);
	अगर (IS_ERR(newstate))
		वापस PTR_ERR(newstate);
	अगर (newstate != खोलोdata->state)
		ret = -ESTALE;
	nfs4_बंद_state(newstate, भ_शेषe);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_खोलो_recover(काष्ठा nfs4_खोलोdata *खोलोdata, काष्ठा nfs4_state *state)
अणु
	पूर्णांक ret;

	/* memory barrier prior to पढ़ोing state->n_* */
	smp_rmb();
	ret = nfs4_खोलो_recover_helper(खोलोdata, FMODE_READ|FMODE_WRITE);
	अगर (ret != 0)
		वापस ret;
	ret = nfs4_खोलो_recover_helper(खोलोdata, FMODE_WRITE);
	अगर (ret != 0)
		वापस ret;
	ret = nfs4_खोलो_recover_helper(खोलोdata, FMODE_READ);
	अगर (ret != 0)
		वापस ret;
	/*
	 * We may have perक्रमmed cached खोलोs क्रम all three recoveries.
	 * Check अगर we need to update the current stateid.
	 */
	अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0 &&
	    !nfs4_stateid_match(&state->stateid, &state->खोलो_stateid)) अणु
		ग_लिखो_seqlock(&state->seqlock);
		अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) == 0)
			nfs4_stateid_copy(&state->stateid, &state->खोलो_stateid);
		ग_लिखो_sequnlock(&state->seqlock);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * OPEN_RECLAIM:
 * 	reclaim state on the server after a reboot.
 */
अटल पूर्णांक _nfs4_करो_खोलो_reclaim(काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_delegation *delegation;
	काष्ठा nfs4_खोलोdata *खोलोdata;
	भ_शेषe_t delegation_type = 0;
	पूर्णांक status;

	खोलोdata = nfs4_खोलो_recoverdata_alloc(ctx, state,
			NFS4_OPEN_CLAIM_PREVIOUS);
	अगर (IS_ERR(खोलोdata))
		वापस PTR_ERR(खोलोdata);
	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(state->inode)->delegation);
	अगर (delegation != शून्य && test_bit(NFS_DELEGATION_NEED_RECLAIM, &delegation->flags) != 0)
		delegation_type = delegation->type;
	rcu_पढ़ो_unlock();
	खोलोdata->o_arg.u.delegation_type = delegation_type;
	status = nfs4_खोलो_recover(खोलोdata, state);
	nfs4_खोलोdata_put(खोलोdata);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_करो_खोलो_reclaim(काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_करो_खोलो_reclaim(ctx, state);
		trace_nfs4_खोलो_reclaim(ctx, 0, err);
		अगर (nfs4_clear_cap_atomic_खोलो_v1(server, err, &exception))
			जारी;
		अगर (err != -NFS4ERR_DELAY)
			अवरोध;
		nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक nfs4_खोलो_reclaim(काष्ठा nfs4_state_owner *sp, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_खोलो_context *ctx;
	पूर्णांक ret;

	ctx = nfs4_state_find_खोलो_context(state);
	अगर (IS_ERR(ctx))
		वापस -EAGAIN;
	clear_bit(NFS_DELEGATED_STATE, &state->flags);
	nfs_state_clear_खोलो_state_flags(state);
	ret = nfs4_करो_खोलो_reclaim(ctx, state);
	put_nfs_खोलो_context(ctx);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_handle_delegation_recall_error(काष्ठा nfs_server *server, काष्ठा nfs4_state *state, स्थिर nfs4_stateid *stateid, काष्ठा file_lock *fl, पूर्णांक err)
अणु
	चयन (err) अणु
		शेष:
			prपूर्णांकk(KERN_ERR "NFS: %s: unhandled error "
					"%d.\n", __func__, err);
			fallthrough;
		हाल 0:
		हाल -ENOENT:
		हाल -EAGAIN:
		हाल -ESTALE:
		हाल -ETIMEDOUT:
			अवरोध;
		हाल -NFS4ERR_BADSESSION:
		हाल -NFS4ERR_BADSLOT:
		हाल -NFS4ERR_BAD_HIGH_SLOT:
		हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		हाल -NFS4ERR_DEADSESSION:
			वापस -EAGAIN;
		हाल -NFS4ERR_STALE_CLIENTID:
		हाल -NFS4ERR_STALE_STATEID:
			/* Don't recall a delegation अगर it was lost */
			nfs4_schedule_lease_recovery(server->nfs_client);
			वापस -EAGAIN;
		हाल -NFS4ERR_MOVED:
			nfs4_schedule_migration_recovery(server);
			वापस -EAGAIN;
		हाल -NFS4ERR_LEASE_MOVED:
			nfs4_schedule_lease_moved_recovery(server->nfs_client);
			वापस -EAGAIN;
		हाल -NFS4ERR_DELEG_REVOKED:
		हाल -NFS4ERR_ADMIN_REVOKED:
		हाल -NFS4ERR_EXPIRED:
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_OPENMODE:
			nfs_inode_find_state_and_recover(state->inode,
					stateid);
			nfs4_schedule_stateid_recovery(server, state);
			वापस -EAGAIN;
		हाल -NFS4ERR_DELAY:
		हाल -NFS4ERR_GRACE:
			ssleep(1);
			वापस -EAGAIN;
		हाल -ENOMEM:
		हाल -NFS4ERR_DENIED:
			अगर (fl) अणु
				काष्ठा nfs4_lock_state *lsp = fl->fl_u.nfs4_fl.owner;
				अगर (lsp)
					set_bit(NFS_LOCK_LOST, &lsp->ls_flags);
			पूर्ण
			वापस 0;
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक nfs4_खोलो_delegation_recall(काष्ठा nfs_खोलो_context *ctx,
		काष्ठा nfs4_state *state, स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs4_खोलोdata *खोलोdata;
	पूर्णांक err = 0;

	खोलोdata = nfs4_खोलो_recoverdata_alloc(ctx, state,
			NFS4_OPEN_CLAIM_DELEG_CUR_FH);
	अगर (IS_ERR(खोलोdata))
		वापस PTR_ERR(खोलोdata);
	nfs4_stateid_copy(&खोलोdata->o_arg.u.delegation, stateid);
	अगर (!test_bit(NFS_O_RDWR_STATE, &state->flags)) अणु
		err = nfs4_खोलो_recover_helper(खोलोdata, FMODE_READ|FMODE_WRITE);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (!test_bit(NFS_O_WRONLY_STATE, &state->flags)) अणु
		err = nfs4_खोलो_recover_helper(खोलोdata, FMODE_WRITE);
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (!test_bit(NFS_O_RDONLY_STATE, &state->flags)) अणु
		err = nfs4_खोलो_recover_helper(खोलोdata, FMODE_READ);
		अगर (err)
			जाओ out;
	पूर्ण
	nfs_state_clear_delegation(state);
out:
	nfs4_खोलोdata_put(खोलोdata);
	वापस nfs4_handle_delegation_recall_error(server, state, stateid, शून्य, err);
पूर्ण

अटल व्योम nfs4_खोलो_confirm_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_खोलोdata *data = calldata;

	nfs4_setup_sequence(data->o_arg.server->nfs_client,
			   &data->c_arg.seq_args, &data->c_res.seq_res, task);
पूर्ण

अटल व्योम nfs4_खोलो_confirm_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_खोलोdata *data = calldata;

	nfs40_sequence_करोne(task, &data->c_res.seq_res);

	data->rpc_status = task->tk_status;
	अगर (data->rpc_status == 0) अणु
		nfs4_stateid_copy(&data->o_res.stateid, &data->c_res.stateid);
		nfs_confirm_seqid(&data->owner->so_seqid, 0);
		renew_lease(data->o_res.server, data->बारtamp);
		data->rpc_करोne = true;
	पूर्ण
पूर्ण

अटल व्योम nfs4_खोलो_confirm_release(व्योम *calldata)
अणु
	काष्ठा nfs4_खोलोdata *data = calldata;
	काष्ठा nfs4_state *state = शून्य;

	/* If this request hasn't been cancelled, करो nothing */
	अगर (!data->cancelled)
		जाओ out_मुक्त;
	/* In हाल of error, no cleanup! */
	अगर (!data->rpc_करोne)
		जाओ out_मुक्त;
	state = nfs4_खोलोdata_to_nfs4_state(data);
	अगर (!IS_ERR(state))
		nfs4_बंद_state(state, data->o_arg.भ_शेषe);
out_मुक्त:
	nfs4_खोलोdata_put(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_खोलो_confirm_ops = अणु
	.rpc_call_prepare = nfs4_खोलो_confirm_prepare,
	.rpc_call_करोne = nfs4_खोलो_confirm_करोne,
	.rpc_release = nfs4_खोलो_confirm_release,
पूर्ण;

/*
 * Note: On error, nfs4_proc_खोलो_confirm will मुक्त the काष्ठा nfs4_खोलोdata
 */
अटल पूर्णांक _nfs4_proc_खोलो_confirm(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(d_inode(data->dir));
	काष्ठा rpc_task *task;
	काष्ठा  rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_OPEN_CONFIRM],
		.rpc_argp = &data->c_arg,
		.rpc_resp = &data->c_res,
		.rpc_cred = data->owner->so_cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_खोलो_confirm_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;
	पूर्णांक status;

	nfs4_init_sequence(&data->c_arg.seq_args, &data->c_res.seq_res, 1,
				data->is_recover);
	kref_get(&data->kref);
	data->rpc_करोne = false;
	data->rpc_status = 0;
	data->बारtamp = jअगरfies;
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	status = rpc_रुको_क्रम_completion_task(task);
	अगर (status != 0) अणु
		data->cancelled = true;
		smp_wmb();
	पूर्ण अन्यथा
		status = data->rpc_status;
	rpc_put_task(task);
	वापस status;
पूर्ण

अटल व्योम nfs4_खोलो_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_खोलोdata *data = calldata;
	काष्ठा nfs4_state_owner *sp = data->owner;
	काष्ठा nfs_client *clp = sp->so_server->nfs_client;
	क्रमागत खोलो_claim_type4 claim = data->o_arg.claim;

	अगर (nfs_रुको_on_sequence(data->o_arg.seqid, task) != 0)
		जाओ out_रुको;
	/*
	 * Check अगर we still need to send an OPEN call, or अगर we can use
	 * a delegation instead.
	 */
	अगर (data->state != शून्य) अणु
		काष्ठा nfs_delegation *delegation;

		अगर (can_खोलो_cached(data->state, data->o_arg.भ_शेषe,
					data->o_arg.खोलो_flags, claim))
			जाओ out_no_action;
		rcu_पढ़ो_lock();
		delegation = nfs4_get_valid_delegation(data->state->inode);
		अगर (can_खोलो_delegated(delegation, data->o_arg.भ_शेषe, claim))
			जाओ unlock_no_action;
		rcu_पढ़ो_unlock();
	पूर्ण
	/* Update client id. */
	data->o_arg.clientid = clp->cl_clientid;
	चयन (claim) अणु
	शेष:
		अवरोध;
	हाल NFS4_OPEN_CLAIM_PREVIOUS:
	हाल NFS4_OPEN_CLAIM_DELEG_CUR_FH:
	हाल NFS4_OPEN_CLAIM_DELEG_PREV_FH:
		data->o_arg.खोलो_biपंचांगap = &nfs4_खोलो_noattr_biपंचांगap[0];
		fallthrough;
	हाल NFS4_OPEN_CLAIM_FH:
		task->tk_msg.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_OPEN_NOATTR];
	पूर्ण
	data->बारtamp = jअगरfies;
	अगर (nfs4_setup_sequence(data->o_arg.server->nfs_client,
				&data->o_arg.seq_args,
				&data->o_res.seq_res,
				task) != 0)
		nfs_release_seqid(data->o_arg.seqid);

	/* Set the create mode (note dependency on the session type) */
	data->o_arg.createmode = NFS4_CREATE_UNCHECKED;
	अगर (data->o_arg.खोलो_flags & O_EXCL) अणु
		data->o_arg.createmode = NFS4_CREATE_EXCLUSIVE;
		अगर (nfs4_has_persistent_session(clp))
			data->o_arg.createmode = NFS4_CREATE_GUARDED;
		अन्यथा अगर (clp->cl_mvops->minor_version > 0)
			data->o_arg.createmode = NFS4_CREATE_EXCLUSIVE4_1;
	पूर्ण
	वापस;
unlock_no_action:
	trace_nfs4_cached_खोलो(data->state);
	rcu_पढ़ो_unlock();
out_no_action:
	task->tk_action = शून्य;
out_रुको:
	nfs4_sequence_करोne(task, &data->o_res.seq_res);
पूर्ण

अटल व्योम nfs4_खोलो_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_खोलोdata *data = calldata;

	data->rpc_status = task->tk_status;

	अगर (!nfs4_sequence_process(task, &data->o_res.seq_res))
		वापस;

	अगर (task->tk_status == 0) अणु
		अगर (data->o_res.f_attr->valid & NFS_ATTR_FATTR_TYPE) अणु
			चयन (data->o_res.f_attr->mode & S_IFMT) अणु
			हाल S_IFREG:
				अवरोध;
			हाल S_IFLNK:
				data->rpc_status = -ELOOP;
				अवरोध;
			हाल S_IFसूची:
				data->rpc_status = -EISसूची;
				अवरोध;
			शेष:
				data->rpc_status = -ENOTसूची;
			पूर्ण
		पूर्ण
		renew_lease(data->o_res.server, data->बारtamp);
		अगर (!(data->o_res.rflags & NFS4_OPEN_RESULT_CONFIRM))
			nfs_confirm_seqid(&data->owner->so_seqid, 0);
	पूर्ण
	data->rpc_करोne = true;
पूर्ण

अटल व्योम nfs4_खोलो_release(व्योम *calldata)
अणु
	काष्ठा nfs4_खोलोdata *data = calldata;
	काष्ठा nfs4_state *state = शून्य;

	/* If this request hasn't been cancelled, करो nothing */
	अगर (!data->cancelled)
		जाओ out_मुक्त;
	/* In हाल of error, no cleanup! */
	अगर (data->rpc_status != 0 || !data->rpc_करोne)
		जाओ out_मुक्त;
	/* In हाल we need an खोलो_confirm, no cleanup! */
	अगर (data->o_res.rflags & NFS4_OPEN_RESULT_CONFIRM)
		जाओ out_मुक्त;
	state = nfs4_खोलोdata_to_nfs4_state(data);
	अगर (!IS_ERR(state))
		nfs4_बंद_state(state, data->o_arg.भ_शेषe);
out_मुक्त:
	nfs4_खोलोdata_put(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_खोलो_ops = अणु
	.rpc_call_prepare = nfs4_खोलो_prepare,
	.rpc_call_करोne = nfs4_खोलो_करोne,
	.rpc_release = nfs4_खोलो_release,
पूर्ण;

अटल पूर्णांक nfs4_run_खोलो_task(काष्ठा nfs4_खोलोdata *data,
			      काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा inode *dir = d_inode(data->dir);
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs_खोलोargs *o_arg = &data->o_arg;
	काष्ठा nfs_खोलोres *o_res = &data->o_res;
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_OPEN],
		.rpc_argp = o_arg,
		.rpc_resp = o_res,
		.rpc_cred = data->owner->so_cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_खोलो_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;
	पूर्णांक status;

	kref_get(&data->kref);
	data->rpc_करोne = false;
	data->rpc_status = 0;
	data->cancelled = false;
	data->is_recover = false;
	अगर (!ctx) अणु
		nfs4_init_sequence(&o_arg->seq_args, &o_res->seq_res, 1, 1);
		data->is_recover = true;
		task_setup_data.flags |= RPC_TASK_TIMEOUT;
	पूर्ण अन्यथा अणु
		nfs4_init_sequence(&o_arg->seq_args, &o_res->seq_res, 1, 0);
		pnfs_lgखोलो_prepare(data, ctx);
	पूर्ण
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	status = rpc_रुको_क्रम_completion_task(task);
	अगर (status != 0) अणु
		data->cancelled = true;
		smp_wmb();
	पूर्ण अन्यथा
		status = data->rpc_status;
	rpc_put_task(task);

	वापस status;
पूर्ण

अटल पूर्णांक _nfs4_recover_proc_खोलो(काष्ठा nfs4_खोलोdata *data)
अणु
	काष्ठा inode *dir = d_inode(data->dir);
	काष्ठा nfs_खोलोres *o_res = &data->o_res;
	पूर्णांक status;

	status = nfs4_run_खोलो_task(data, शून्य);
	अगर (status != 0 || !data->rpc_करोne)
		वापस status;

	nfs_fattr_map_and_मुक्त_names(NFS_SERVER(dir), &data->f_attr);

	अगर (o_res->rflags & NFS4_OPEN_RESULT_CONFIRM)
		status = _nfs4_proc_खोलो_confirm(data);

	वापस status;
पूर्ण

/*
 * Additional permission checks in order to distinguish between an
 * खोलो क्रम पढ़ो, and an खोलो क्रम execute. This works around the
 * fact that NFSv4 OPEN treats पढ़ो and execute permissions as being
 * the same.
 * Note that in the non-execute हाल, we want to turn off permission
 * checking अगर we just created a new file (POSIX खोलो() semantics).
 */
अटल पूर्णांक nfs4_खोलोdata_access(स्थिर काष्ठा cred *cred,
				काष्ठा nfs4_खोलोdata *खोलोdata,
				काष्ठा nfs4_state *state, भ_शेषe_t भ_शेषe,
				पूर्णांक खोलोflags)
अणु
	काष्ठा nfs_access_entry cache;
	u32 mask, flags;

	/* access call failed or क्रम some reason the server करोesn't
	 * support any access modes -- defer access call until later */
	अगर (खोलोdata->o_res.access_supported == 0)
		वापस 0;

	mask = 0;
	/*
	 * Use खोलोflags to check क्रम exec, because भ_शेषe won't
	 * always have FMODE_EXEC set when file खोलो क्रम exec.
	 */
	अगर (खोलोflags & __FMODE_EXEC) अणु
		/* ONLY check क्रम exec rights */
		अगर (S_ISसूची(state->inode->i_mode))
			mask = NFS4_ACCESS_LOOKUP;
		अन्यथा
			mask = NFS4_ACCESS_EXECUTE;
	पूर्ण अन्यथा अगर ((भ_शेषe & FMODE_READ) && !खोलोdata->file_created)
		mask = NFS4_ACCESS_READ;

	cache.cred = cred;
	nfs_access_set_mask(&cache, खोलोdata->o_res.access_result);
	nfs_access_add_cache(state->inode, &cache);

	flags = NFS4_ACCESS_READ | NFS4_ACCESS_EXECUTE | NFS4_ACCESS_LOOKUP;
	अगर ((mask & ~cache.mask & flags) == 0)
		वापस 0;

	वापस -EACCES;
पूर्ण

/*
 * Note: On error, nfs4_proc_खोलो will मुक्त the काष्ठा nfs4_खोलोdata
 */
अटल पूर्णांक _nfs4_proc_खोलो(काष्ठा nfs4_खोलोdata *data,
			   काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा inode *dir = d_inode(data->dir);
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs_खोलोargs *o_arg = &data->o_arg;
	काष्ठा nfs_खोलोres *o_res = &data->o_res;
	पूर्णांक status;

	status = nfs4_run_खोलो_task(data, ctx);
	अगर (!data->rpc_करोne)
		वापस status;
	अगर (status != 0) अणु
		अगर (status == -NFS4ERR_BADNAME &&
				!(o_arg->खोलो_flags & O_CREAT))
			वापस -ENOENT;
		वापस status;
	पूर्ण

	nfs_fattr_map_and_मुक्त_names(server, &data->f_attr);

	अगर (o_arg->खोलो_flags & O_CREAT) अणु
		अगर (o_arg->खोलो_flags & O_EXCL)
			data->file_created = true;
		अन्यथा अगर (o_res->cinfo.beक्रमe != o_res->cinfo.after)
			data->file_created = true;
		अगर (data->file_created ||
		    inode_peek_iversion_raw(dir) != o_res->cinfo.after)
			nfs4_update_changeattr(dir, &o_res->cinfo,
					o_res->f_attr->समय_start,
					NFS_INO_INVALID_DATA);
	पूर्ण
	अगर ((o_res->rflags & NFS4_OPEN_RESULT_LOCKTYPE_POSIX) == 0)
		server->caps &= ~NFS_CAP_POSIX_LOCK;
	अगर(o_res->rflags & NFS4_OPEN_RESULT_CONFIRM) अणु
		status = _nfs4_proc_खोलो_confirm(data);
		अगर (status != 0)
			वापस status;
	पूर्ण
	अगर (!(o_res->f_attr->valid & NFS_ATTR_FATTR)) अणु
		nfs4_sequence_मुक्त_slot(&o_res->seq_res);
		nfs4_proc_getattr(server, &o_res->fh, o_res->f_attr,
				o_res->f_label, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * OPEN_EXPIRED:
 * 	reclaim state on the server after a network partition.
 * 	Assumes caller holds the appropriate lock
 */
अटल पूर्णांक _nfs4_खोलो_expired(काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs4_खोलोdata *खोलोdata;
	पूर्णांक ret;

	खोलोdata = nfs4_खोलो_recoverdata_alloc(ctx, state,
			NFS4_OPEN_CLAIM_FH);
	अगर (IS_ERR(खोलोdata))
		वापस PTR_ERR(खोलोdata);
	ret = nfs4_खोलो_recover(खोलोdata, state);
	अगर (ret == -ESTALE)
		d_drop(ctx->dentry);
	nfs4_खोलोdata_put(खोलोdata);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_करो_खोलो_expired(काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs4_खोलो_expired(ctx, state);
		trace_nfs4_खोलो_expired(ctx, 0, err);
		अगर (nfs4_clear_cap_atomic_खोलो_v1(server, err, &exception))
			जारी;
		चयन (err) अणु
		शेष:
			जाओ out;
		हाल -NFS4ERR_GRACE:
		हाल -NFS4ERR_DELAY:
			nfs4_handle_exception(server, err, &exception);
			err = 0;
		पूर्ण
	पूर्ण जबतक (exception.retry);
out:
	वापस err;
पूर्ण

अटल पूर्णांक nfs4_खोलो_expired(काष्ठा nfs4_state_owner *sp, काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_खोलो_context *ctx;
	पूर्णांक ret;

	ctx = nfs4_state_find_खोलो_context(state);
	अगर (IS_ERR(ctx))
		वापस -EAGAIN;
	ret = nfs4_करो_खोलो_expired(ctx, state);
	put_nfs_खोलो_context(ctx);
	वापस ret;
पूर्ण

अटल व्योम nfs_finish_clear_delegation_stateid(काष्ठा nfs4_state *state,
		स्थिर nfs4_stateid *stateid)
अणु
	nfs_हटाओ_bad_delegation(state->inode, stateid);
	nfs_state_clear_delegation(state);
पूर्ण

अटल व्योम nfs40_clear_delegation_stateid(काष्ठा nfs4_state *state)
अणु
	अगर (rcu_access_poपूर्णांकer(NFS_I(state->inode)->delegation) != शून्य)
		nfs_finish_clear_delegation_stateid(state, शून्य);
पूर्ण

अटल पूर्णांक nfs40_खोलो_expired(काष्ठा nfs4_state_owner *sp, काष्ठा nfs4_state *state)
अणु
	/* NFSv4.0 करोesn't allow क्रम delegation recovery on खोलो expire */
	nfs40_clear_delegation_stateid(state);
	nfs_state_clear_खोलो_state_flags(state);
	वापस nfs4_खोलो_expired(sp, state);
पूर्ण

अटल पूर्णांक nfs40_test_and_मुक्त_expired_stateid(काष्ठा nfs_server *server,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	वापस -NFS4ERR_BAD_STATEID;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
अटल पूर्णांक nfs41_test_and_मुक्त_expired_stateid(काष्ठा nfs_server *server,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक status;

	चयन (stateid->type) अणु
	शेष:
		अवरोध;
	हाल NFS4_INVALID_STATEID_TYPE:
	हाल NFS4_SPECIAL_STATEID_TYPE:
		वापस -NFS4ERR_BAD_STATEID;
	हाल NFS4_REVOKED_STATEID_TYPE:
		जाओ out_मुक्त;
	पूर्ण

	status = nfs41_test_stateid(server, stateid, cred);
	चयन (status) अणु
	हाल -NFS4ERR_EXPIRED:
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_DELEG_REVOKED:
		अवरोध;
	शेष:
		वापस status;
	पूर्ण
out_मुक्त:
	/* Ack the revoked state to the server */
	nfs41_मुक्त_stateid(server, stateid, cred, true);
	वापस -NFS4ERR_EXPIRED;
पूर्ण

अटल पूर्णांक nfs41_check_delegation_stateid(काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	nfs4_stateid stateid;
	काष्ठा nfs_delegation *delegation;
	स्थिर काष्ठा cred *cred = शून्य;
	पूर्णांक status, ret = NFS_OK;

	/* Get the delegation credential क्रम use by test/मुक्त_stateid */
	rcu_पढ़ो_lock();
	delegation = rcu_dereference(NFS_I(state->inode)->delegation);
	अगर (delegation == शून्य) अणु
		rcu_पढ़ो_unlock();
		nfs_state_clear_delegation(state);
		वापस NFS_OK;
	पूर्ण

	spin_lock(&delegation->lock);
	nfs4_stateid_copy(&stateid, &delegation->stateid);

	अगर (!test_and_clear_bit(NFS_DELEGATION_TEST_EXPIRED,
				&delegation->flags)) अणु
		spin_unlock(&delegation->lock);
		rcu_पढ़ो_unlock();
		वापस NFS_OK;
	पूर्ण

	अगर (delegation->cred)
		cred = get_cred(delegation->cred);
	spin_unlock(&delegation->lock);
	rcu_पढ़ो_unlock();
	status = nfs41_test_and_मुक्त_expired_stateid(server, &stateid, cred);
	trace_nfs4_test_delegation_stateid(state, शून्य, status);
	अगर (status == -NFS4ERR_EXPIRED || status == -NFS4ERR_BAD_STATEID)
		nfs_finish_clear_delegation_stateid(state, &stateid);
	अन्यथा
		ret = status;

	put_cred(cred);
	वापस ret;
पूर्ण

अटल व्योम nfs41_delegation_recover_stateid(काष्ठा nfs4_state *state)
अणु
	nfs4_stateid पंचांगp;

	अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) &&
	    nfs4_copy_delegation_stateid(state->inode, state->state,
				&पंचांगp, शून्य) &&
	    nfs4_stateid_match_other(&state->stateid, &पंचांगp))
		nfs_state_set_delegation(state, &पंचांगp, state->state);
	अन्यथा
		nfs_state_clear_delegation(state);
पूर्ण

/**
 * nfs41_check_expired_locks - possibly मुक्त a lock stateid
 *
 * @state: NFSv4 state क्रम an inode
 *
 * Returns NFS_OK अगर recovery क्रम this stateid is now finished.
 * Otherwise a negative NFS4ERR value is वापसed.
 */
अटल पूर्णांक nfs41_check_expired_locks(काष्ठा nfs4_state *state)
अणु
	पूर्णांक status, ret = NFS_OK;
	काष्ठा nfs4_lock_state *lsp, *prev = शून्य;
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);

	अगर (!test_bit(LK_STATE_IN_USE, &state->flags))
		जाओ out;

	spin_lock(&state->state_lock);
	list_क्रम_each_entry(lsp, &state->lock_states, ls_locks) अणु
		अगर (test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags)) अणु
			स्थिर काष्ठा cred *cred = lsp->ls_state->owner->so_cred;

			refcount_inc(&lsp->ls_count);
			spin_unlock(&state->state_lock);

			nfs4_put_lock_state(prev);
			prev = lsp;

			status = nfs41_test_and_मुक्त_expired_stateid(server,
					&lsp->ls_stateid,
					cred);
			trace_nfs4_test_lock_stateid(state, lsp, status);
			अगर (status == -NFS4ERR_EXPIRED ||
			    status == -NFS4ERR_BAD_STATEID) अणु
				clear_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags);
				lsp->ls_stateid.type = NFS4_INVALID_STATEID_TYPE;
				अगर (!recover_lost_locks)
					set_bit(NFS_LOCK_LOST, &lsp->ls_flags);
			पूर्ण अन्यथा अगर (status != NFS_OK) अणु
				ret = status;
				nfs4_put_lock_state(prev);
				जाओ out;
			पूर्ण
			spin_lock(&state->state_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&state->state_lock);
	nfs4_put_lock_state(prev);
out:
	वापस ret;
पूर्ण

/**
 * nfs41_check_खोलो_stateid - possibly मुक्त an खोलो stateid
 *
 * @state: NFSv4 state क्रम an inode
 *
 * Returns NFS_OK अगर recovery क्रम this stateid is now finished.
 * Otherwise a negative NFS4ERR value is वापसed.
 */
अटल पूर्णांक nfs41_check_खोलो_stateid(काष्ठा nfs4_state *state)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	nfs4_stateid *stateid = &state->खोलो_stateid;
	स्थिर काष्ठा cred *cred = state->owner->so_cred;
	पूर्णांक status;

	अगर (test_bit(NFS_OPEN_STATE, &state->flags) == 0)
		वापस -NFS4ERR_BAD_STATEID;
	status = nfs41_test_and_मुक्त_expired_stateid(server, stateid, cred);
	trace_nfs4_test_खोलो_stateid(state, शून्य, status);
	अगर (status == -NFS4ERR_EXPIRED || status == -NFS4ERR_BAD_STATEID) अणु
		nfs_state_clear_खोलो_state_flags(state);
		stateid->type = NFS4_INVALID_STATEID_TYPE;
		वापस status;
	पूर्ण
	अगर (nfs_खोलो_stateid_recover_खोलोmode(state))
		वापस -NFS4ERR_OPENMODE;
	वापस NFS_OK;
पूर्ण

अटल पूर्णांक nfs41_खोलो_expired(काष्ठा nfs4_state_owner *sp, काष्ठा nfs4_state *state)
अणु
	पूर्णांक status;

	status = nfs41_check_delegation_stateid(state);
	अगर (status != NFS_OK)
		वापस status;
	nfs41_delegation_recover_stateid(state);

	status = nfs41_check_expired_locks(state);
	अगर (status != NFS_OK)
		वापस status;
	status = nfs41_check_खोलो_stateid(state);
	अगर (status != NFS_OK)
		status = nfs4_खोलो_expired(sp, state);
	वापस status;
पूर्ण
#पूर्ण_अगर

/*
 * on an EXCLUSIVE create, the server should send back a biपंचांगask with FATTR4-*
 * fields corresponding to attributes that were used to store the verअगरier.
 * Make sure we clobber those fields in the later setattr call
 */
अटल अचिन्हित nfs4_exclusive_attrset(काष्ठा nfs4_खोलोdata *खोलोdata,
				काष्ठा iattr *sattr, काष्ठा nfs4_label **label)
अणु
	स्थिर __u32 *biपंचांगask = खोलोdata->o_arg.server->exclcreat_biपंचांगask;
	__u32 attrset[3];
	अचिन्हित ret;
	अचिन्हित i;

	क्रम (i = 0; i < ARRAY_SIZE(attrset); i++) अणु
		attrset[i] = खोलोdata->o_res.attrset[i];
		अगर (खोलोdata->o_arg.createmode == NFS4_CREATE_EXCLUSIVE4_1)
			attrset[i] &= ~biपंचांगask[i];
	पूर्ण

	ret = (खोलोdata->o_arg.createmode == NFS4_CREATE_EXCLUSIVE) ?
		sattr->ia_valid : 0;

	अगर ((attrset[1] & (FATTR4_WORD1_TIME_ACCESS|FATTR4_WORD1_TIME_ACCESS_SET))) अणु
		अगर (sattr->ia_valid & ATTR_ATIME_SET)
			ret |= ATTR_ATIME_SET;
		अन्यथा
			ret |= ATTR_ATIME;
	पूर्ण

	अगर ((attrset[1] & (FATTR4_WORD1_TIME_MODIFY|FATTR4_WORD1_TIME_MODIFY_SET))) अणु
		अगर (sattr->ia_valid & ATTR_MTIME_SET)
			ret |= ATTR_MTIME_SET;
		अन्यथा
			ret |= ATTR_MTIME;
	पूर्ण

	अगर (!(attrset[2] & FATTR4_WORD2_SECURITY_LABEL))
		*label = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक _nfs4_खोलो_and_get_state(काष्ठा nfs4_खोलोdata *खोलोdata,
		पूर्णांक flags, काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा nfs4_state_owner *sp = खोलोdata->owner;
	काष्ठा nfs_server *server = sp->so_server;
	काष्ठा dentry *dentry;
	काष्ठा nfs4_state *state;
	भ_शेषe_t acc_mode = _nfs4_ctx_to_accessmode(ctx);
	काष्ठा inode *dir = d_inode(खोलोdata->dir);
	अचिन्हित दीर्घ dir_verअगरier;
	अचिन्हित पूर्णांक seq;
	पूर्णांक ret;

	seq = raw_seqcount_begin(&sp->so_reclaim_seqcount);
	dir_verअगरier = nfs_save_change_attribute(dir);

	ret = _nfs4_proc_खोलो(खोलोdata, ctx);
	अगर (ret != 0)
		जाओ out;

	state = _nfs4_खोलोdata_to_nfs4_state(खोलोdata);
	ret = PTR_ERR(state);
	अगर (IS_ERR(state))
		जाओ out;
	ctx->state = state;
	अगर (server->caps & NFS_CAP_POSIX_LOCK)
		set_bit(NFS_STATE_POSIX_LOCKS, &state->flags);
	अगर (खोलोdata->o_res.rflags & NFS4_OPEN_RESULT_MAY_NOTIFY_LOCK)
		set_bit(NFS_STATE_MAY_NOTIFY_LOCK, &state->flags);

	dentry = खोलोdata->dentry;
	अगर (d_really_is_negative(dentry)) अणु
		काष्ठा dentry *alias;
		d_drop(dentry);
		alias = d_exact_alias(dentry, state->inode);
		अगर (!alias)
			alias = d_splice_alias(igrab(state->inode), dentry);
		/* d_splice_alias() can't fail here - it's a non-directory */
		अगर (alias) अणु
			dput(ctx->dentry);
			ctx->dentry = dentry = alias;
		पूर्ण
	पूर्ण

	चयन(खोलोdata->o_arg.claim) अणु
	शेष:
		अवरोध;
	हाल NFS4_OPEN_CLAIM_शून्य:
	हाल NFS4_OPEN_CLAIM_DELEGATE_CUR:
	हाल NFS4_OPEN_CLAIM_DELEGATE_PREV:
		अगर (!खोलोdata->rpc_करोne)
			अवरोध;
		अगर (खोलोdata->o_res.delegation_type != 0)
			dir_verअगरier = nfs_save_change_attribute(dir);
		nfs_set_verअगरier(dentry, dir_verअगरier);
	पूर्ण

	/* Parse layoutget results beक्रमe we check क्रम access */
	pnfs_parse_lgखोलो(state->inode, खोलोdata->lgp, ctx);

	ret = nfs4_खोलोdata_access(sp->so_cred, खोलोdata, state,
			acc_mode, flags);
	अगर (ret != 0)
		जाओ out;

	अगर (d_inode(dentry) == state->inode) अणु
		nfs_inode_attach_खोलो_context(ctx);
		अगर (पढ़ो_seqcount_retry(&sp->so_reclaim_seqcount, seq))
			nfs4_schedule_stateid_recovery(server, state);
	पूर्ण

out:
	अगर (!खोलोdata->cancelled)
		nfs4_sequence_मुक्त_slot(&खोलोdata->o_res.seq_res);
	वापस ret;
पूर्ण

/*
 * Returns a referenced nfs4_state
 */
अटल पूर्णांक _nfs4_करो_खोलो(काष्ठा inode *dir,
			काष्ठा nfs_खोलो_context *ctx,
			पूर्णांक flags,
			स्थिर काष्ठा nfs4_खोलो_createattrs *c,
			पूर्णांक *खोलोed)
अणु
	काष्ठा nfs4_state_owner  *sp;
	काष्ठा nfs4_state     *state = शून्य;
	काष्ठा nfs_server       *server = NFS_SERVER(dir);
	काष्ठा nfs4_खोलोdata *खोलोdata;
	काष्ठा dentry *dentry = ctx->dentry;
	स्थिर काष्ठा cred *cred = ctx->cred;
	काष्ठा nfs4_threshold **ctx_th = &ctx->mdsthreshold;
	भ_शेषe_t भ_शेषe = _nfs4_ctx_to_खोलोmode(ctx);
	क्रमागत खोलो_claim_type4 claim = NFS4_OPEN_CLAIM_शून्य;
	काष्ठा iattr *sattr = c->sattr;
	काष्ठा nfs4_label *label = c->label;
	काष्ठा nfs4_label *olabel = शून्य;
	पूर्णांक status;

	/* Protect against reboot recovery conflicts */
	status = -ENOMEM;
	sp = nfs4_get_state_owner(server, cred, GFP_KERNEL);
	अगर (sp == शून्य) अणु
		dprपूर्णांकk("nfs4_do_open: nfs4_get_state_owner failed!\n");
		जाओ out_err;
	पूर्ण
	status = nfs4_client_recover_expired_lease(server->nfs_client);
	अगर (status != 0)
		जाओ err_put_state_owner;
	अगर (d_really_is_positive(dentry))
		nfs4_वापस_incompatible_delegation(d_inode(dentry), भ_शेषe);
	status = -ENOMEM;
	अगर (d_really_is_positive(dentry))
		claim = NFS4_OPEN_CLAIM_FH;
	खोलोdata = nfs4_खोलोdata_alloc(dentry, sp, भ_शेषe, flags,
			c, claim, GFP_KERNEL);
	अगर (खोलोdata == शून्य)
		जाओ err_put_state_owner;

	अगर (label) अणु
		olabel = nfs4_label_alloc(server, GFP_KERNEL);
		अगर (IS_ERR(olabel)) अणु
			status = PTR_ERR(olabel);
			जाओ err_खोलोdata_put;
		पूर्ण
	पूर्ण

	अगर (server->attr_biपंचांगask[2] & FATTR4_WORD2_MDSTHRESHOLD) अणु
		अगर (!खोलोdata->f_attr.mdsthreshold) अणु
			खोलोdata->f_attr.mdsthreshold = pnfs_mdsthreshold_alloc();
			अगर (!खोलोdata->f_attr.mdsthreshold)
				जाओ err_मुक्त_label;
		पूर्ण
		खोलोdata->o_arg.खोलो_biपंचांगap = &nfs4_pnfs_खोलो_biपंचांगap[0];
	पूर्ण
	अगर (d_really_is_positive(dentry))
		खोलोdata->state = nfs4_get_खोलो_state(d_inode(dentry), sp);

	status = _nfs4_खोलो_and_get_state(खोलोdata, flags, ctx);
	अगर (status != 0)
		जाओ err_मुक्त_label;
	state = ctx->state;

	अगर ((खोलोdata->o_arg.खोलो_flags & (O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL) &&
	    (खोलोdata->o_arg.createmode != NFS4_CREATE_GUARDED)) अणु
		अचिन्हित attrs = nfs4_exclusive_attrset(खोलोdata, sattr, &label);
		/*
		 * send create attributes which was not set by खोलो
		 * with an extra setattr.
		 */
		अगर (attrs || label) अणु
			अचिन्हित ia_old = sattr->ia_valid;

			sattr->ia_valid = attrs;
			nfs_fattr_init(खोलोdata->o_res.f_attr);
			status = nfs4_करो_setattr(state->inode, cred,
					खोलोdata->o_res.f_attr, sattr,
					ctx, label, olabel);
			अगर (status == 0) अणु
				nfs_setattr_update_inode(state->inode, sattr,
						खोलोdata->o_res.f_attr);
				nfs_setsecurity(state->inode, खोलोdata->o_res.f_attr, olabel);
			पूर्ण
			sattr->ia_valid = ia_old;
		पूर्ण
	पूर्ण
	अगर (खोलोed && खोलोdata->file_created)
		*खोलोed = 1;

	अगर (pnfs_use_threshold(ctx_th, खोलोdata->f_attr.mdsthreshold, server)) अणु
		*ctx_th = खोलोdata->f_attr.mdsthreshold;
		खोलोdata->f_attr.mdsthreshold = शून्य;
	पूर्ण

	nfs4_label_मुक्त(olabel);

	nfs4_खोलोdata_put(खोलोdata);
	nfs4_put_state_owner(sp);
	वापस 0;
err_मुक्त_label:
	nfs4_label_मुक्त(olabel);
err_खोलोdata_put:
	nfs4_खोलोdata_put(खोलोdata);
err_put_state_owner:
	nfs4_put_state_owner(sp);
out_err:
	वापस status;
पूर्ण


अटल काष्ठा nfs4_state *nfs4_करो_खोलो(काष्ठा inode *dir,
					काष्ठा nfs_खोलो_context *ctx,
					पूर्णांक flags,
					काष्ठा iattr *sattr,
					काष्ठा nfs4_label *label,
					पूर्णांक *खोलोed)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	काष्ठा nfs4_state *res;
	काष्ठा nfs4_खोलो_createattrs c = अणु
		.label = label,
		.sattr = sattr,
		.verf = अणु
			[0] = (__u32)jअगरfies,
			[1] = (__u32)current->pid,
		पूर्ण,
	पूर्ण;
	पूर्णांक status;

	करो अणु
		status = _nfs4_करो_खोलो(dir, ctx, flags, &c, खोलोed);
		res = ctx->state;
		trace_nfs4_खोलो_file(ctx, flags, status);
		अगर (status == 0)
			अवरोध;
		/* NOTE: BAD_SEQID means the server and client disagree about the
		 * book-keeping w.r.t. state-changing operations
		 * (OPEN/CLOSE/LOCK/LOCKU...)
		 * It is actually a sign of a bug on the client or on the server.
		 *
		 * If we receive a BAD_SEQID error in the particular हाल of
		 * करोing an OPEN, we assume that nfs_increment_खोलो_seqid() will
		 * have unhashed the old state_owner क्रम us, and that we can
		 * thereक्रमe safely retry using a new one. We should still warn
		 * the user though...
		 */
		अगर (status == -NFS4ERR_BAD_SEQID) अणु
			pr_warn_ratelimited("NFS: v4 server %s "
					" returned a bad sequence-id error!\n",
					NFS_SERVER(dir)->nfs_client->cl_hostname);
			exception.retry = 1;
			जारी;
		पूर्ण
		/*
		 * BAD_STATEID on OPEN means that the server cancelled our
		 * state beक्रमe it received the OPEN_CONFIRM.
		 * Recover by retrying the request as per the discussion
		 * on Page 181 of RFC3530.
		 */
		अगर (status == -NFS4ERR_BAD_STATEID) अणु
			exception.retry = 1;
			जारी;
		पूर्ण
		अगर (status == -NFS4ERR_EXPIRED) अणु
			nfs4_schedule_lease_recovery(server->nfs_client);
			exception.retry = 1;
			जारी;
		पूर्ण
		अगर (status == -EAGAIN) अणु
			/* We must have found a delegation */
			exception.retry = 1;
			जारी;
		पूर्ण
		अगर (nfs4_clear_cap_atomic_खोलो_v1(server, status, &exception))
			जारी;
		res = ERR_PTR(nfs4_handle_exception(server,
					status, &exception));
	पूर्ण जबतक (exception.retry);
	वापस res;
पूर्ण

अटल पूर्णांक _nfs4_करो_setattr(काष्ठा inode *inode,
			    काष्ठा nfs_setattrargs *arg,
			    काष्ठा nfs_setattrres *res,
			    स्थिर काष्ठा cred *cred,
			    काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_SETATTR],
		.rpc_argp	= arg,
		.rpc_resp	= res,
		.rpc_cred	= cred,
	पूर्ण;
	स्थिर काष्ठा cred *delegation_cred = शून्य;
	अचिन्हित दीर्घ बारtamp = jअगरfies;
	bool truncate;
	पूर्णांक status;

	nfs_fattr_init(res->fattr);

	/* Servers should only apply खोलो mode checks क्रम file size changes */
	truncate = (arg->iap->ia_valid & ATTR_SIZE) ? true : false;
	अगर (!truncate) अणु
		nfs4_inode_make_ग_लिखोable(inode);
		जाओ zero_stateid;
	पूर्ण

	अगर (nfs4_copy_delegation_stateid(inode, FMODE_WRITE, &arg->stateid, &delegation_cred)) अणु
		/* Use that stateid */
	पूर्ण अन्यथा अगर (ctx != शून्य && ctx->state) अणु
		काष्ठा nfs_lock_context *l_ctx;
		अगर (!nfs4_valid_खोलो_stateid(ctx->state))
			वापस -EBADF;
		l_ctx = nfs_get_lock_context(ctx);
		अगर (IS_ERR(l_ctx))
			वापस PTR_ERR(l_ctx);
		status = nfs4_select_rw_stateid(ctx->state, FMODE_WRITE, l_ctx,
						&arg->stateid, &delegation_cred);
		nfs_put_lock_context(l_ctx);
		अगर (status == -EIO)
			वापस -EBADF;
		अन्यथा अगर (status == -EAGAIN)
			जाओ zero_stateid;
	पूर्ण अन्यथा अणु
zero_stateid:
		nfs4_stateid_copy(&arg->stateid, &zero_stateid);
	पूर्ण
	अगर (delegation_cred)
		msg.rpc_cred = delegation_cred;

	status = nfs4_call_sync(server->client, server, &msg, &arg->seq_args, &res->seq_res, 1);

	put_cred(delegation_cred);
	अगर (status == 0 && ctx != शून्य)
		renew_lease(server, बारtamp);
	trace_nfs4_setattr(inode, &arg->stateid, status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_करो_setattr(काष्ठा inode *inode, स्थिर काष्ठा cred *cred,
			   काष्ठा nfs_fattr *fattr, काष्ठा iattr *sattr,
			   काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_label *ilabel,
			   काष्ठा nfs4_label *olabel)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	__u32 biपंचांगask[NFS4_BITMASK_SZ];
	काष्ठा nfs4_state *state = ctx ? ctx->state : शून्य;
	काष्ठा nfs_setattrargs	arg = अणु
		.fh		= NFS_FH(inode),
		.iap		= sattr,
		.server		= server,
		.biपंचांगask = biपंचांगask,
		.label		= ilabel,
	पूर्ण;
	काष्ठा nfs_setattrres  res = अणु
		.fattr		= fattr,
		.label		= olabel,
		.server		= server,
	पूर्ण;
	काष्ठा nfs4_exception exception = अणु
		.state = state,
		.inode = inode,
		.stateid = &arg.stateid,
	पूर्ण;
	अचिन्हित दीर्घ adjust_flags = NFS_INO_INVALID_CHANGE;
	पूर्णांक err;

	अगर (sattr->ia_valid & (ATTR_MODE | ATTR_KILL_SUID | ATTR_KILL_SGID))
		adjust_flags |= NFS_INO_INVALID_MODE;
	अगर (sattr->ia_valid & (ATTR_UID | ATTR_GID))
		adjust_flags |= NFS_INO_INVALID_OTHER;

	करो अणु
		nfs4_biपंचांगap_copy_adjust(biपंचांगask, nfs4_biपंचांगask(server, olabel),
					inode, adjust_flags);

		err = _nfs4_करो_setattr(inode, &arg, &res, cred, ctx);
		चयन (err) अणु
		हाल -NFS4ERR_OPENMODE:
			अगर (!(sattr->ia_valid & ATTR_SIZE)) अणु
				pr_warn_once("NFSv4: server %s is incorrectly "
						"applying open mode checks to "
						"a SETATTR that is not "
						"changing file size.\n",
						server->nfs_client->cl_hostname);
			पूर्ण
			अगर (state && !(state->state & FMODE_WRITE)) अणु
				err = -EBADF;
				अगर (sattr->ia_valid & ATTR_OPEN)
					err = -EACCES;
				जाओ out;
			पूर्ण
		पूर्ण
		err = nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);
out:
	वापस err;
पूर्ण

अटल bool
nfs4_रुको_on_layoutवापस(काष्ठा inode *inode, काष्ठा rpc_task *task)
अणु
	अगर (inode == शून्य || !nfs_have_layout(inode))
		वापस false;

	वापस pnfs_रुको_on_layoutवापस(inode, task);
पूर्ण

/*
 * Update the seqid of an खोलो stateid
 */
अटल व्योम nfs4_sync_खोलो_stateid(nfs4_stateid *dst,
		काष्ठा nfs4_state *state)
अणु
	__be32 seqid_खोलो;
	u32 dst_seqid;
	पूर्णांक seq;

	क्रम (;;) अणु
		अगर (!nfs4_valid_खोलो_stateid(state))
			अवरोध;
		seq = पढ़ो_seqbegin(&state->seqlock);
		अगर (!nfs4_state_match_खोलो_stateid_other(state, dst)) अणु
			nfs4_stateid_copy(dst, &state->खोलो_stateid);
			अगर (पढ़ो_seqretry(&state->seqlock, seq))
				जारी;
			अवरोध;
		पूर्ण
		seqid_खोलो = state->खोलो_stateid.seqid;
		अगर (पढ़ो_seqretry(&state->seqlock, seq))
			जारी;

		dst_seqid = be32_to_cpu(dst->seqid);
		अगर ((s32)(dst_seqid - be32_to_cpu(seqid_खोलो)) < 0)
			dst->seqid = seqid_खोलो;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Update the seqid of an खोलो stateid after receiving
 * NFS4ERR_OLD_STATEID
 */
अटल bool nfs4_refresh_खोलो_old_stateid(nfs4_stateid *dst,
		काष्ठा nfs4_state *state)
अणु
	__be32 seqid_खोलो;
	u32 dst_seqid;
	bool ret;
	पूर्णांक seq, status = -EAGAIN;
	DEFINE_WAIT(रुको);

	क्रम (;;) अणु
		ret = false;
		अगर (!nfs4_valid_खोलो_stateid(state))
			अवरोध;
		seq = पढ़ो_seqbegin(&state->seqlock);
		अगर (!nfs4_state_match_खोलो_stateid_other(state, dst)) अणु
			अगर (पढ़ो_seqretry(&state->seqlock, seq))
				जारी;
			अवरोध;
		पूर्ण

		ग_लिखो_seqlock(&state->seqlock);
		seqid_खोलो = state->खोलो_stateid.seqid;

		dst_seqid = be32_to_cpu(dst->seqid);

		/* Did another OPEN bump the state's seqid?  try again: */
		अगर ((s32)(be32_to_cpu(seqid_खोलो) - dst_seqid) > 0) अणु
			dst->seqid = seqid_खोलो;
			ग_लिखो_sequnlock(&state->seqlock);
			ret = true;
			अवरोध;
		पूर्ण

		/* server says we're behind but we haven't seen the update yet */
		set_bit(NFS_STATE_CHANGE_WAIT, &state->flags);
		prepare_to_रुको(&state->रुकोq, &रुको, TASK_KILLABLE);
		ग_लिखो_sequnlock(&state->seqlock);
		trace_nfs4_बंद_stateid_update_रुको(state->inode, dst, 0);

		अगर (fatal_संकेत_pending(current))
			status = -EINTR;
		अन्यथा
			अगर (schedule_समयout(5*HZ) != 0)
				status = 0;

		finish_रुको(&state->रुकोq, &रुको);

		अगर (!status)
			जारी;
		अगर (status == -EINTR)
			अवरोध;

		/* we slept the whole 5 seconds, we must have lost a seqid */
		dst->seqid = cpu_to_be32(dst_seqid + 1);
		ret = true;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा nfs4_बंदdata अणु
	काष्ठा inode *inode;
	काष्ठा nfs4_state *state;
	काष्ठा nfs_बंदargs arg;
	काष्ठा nfs_बंदres res;
	काष्ठा अणु
		काष्ठा nfs4_layoutवापस_args arg;
		काष्ठा nfs4_layoutवापस_res res;
		काष्ठा nfs4_xdr_opaque_data ld_निजी;
		u32 roc_barrier;
		bool roc;
	पूर्ण lr;
	काष्ठा nfs_fattr fattr;
	अचिन्हित दीर्घ बारtamp;
पूर्ण;

अटल व्योम nfs4_मुक्त_बंदdata(व्योम *data)
अणु
	काष्ठा nfs4_बंदdata *calldata = data;
	काष्ठा nfs4_state_owner *sp = calldata->state->owner;
	काष्ठा super_block *sb = calldata->state->inode->i_sb;

	अगर (calldata->lr.roc)
		pnfs_roc_release(&calldata->lr.arg, &calldata->lr.res,
				calldata->res.lr_ret);
	nfs4_put_खोलो_state(calldata->state);
	nfs_मुक्त_seqid(calldata->arg.seqid);
	nfs4_put_state_owner(sp);
	nfs_sb_deactive(sb);
	kमुक्त(calldata);
पूर्ण

अटल व्योम nfs4_बंद_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_बंदdata *calldata = data;
	काष्ठा nfs4_state *state = calldata->state;
	काष्ठा nfs_server *server = NFS_SERVER(calldata->inode);
	nfs4_stateid *res_stateid = शून्य;
	काष्ठा nfs4_exception exception = अणु
		.state = state,
		.inode = calldata->inode,
		.stateid = &calldata->arg.stateid,
	पूर्ण;

	dprपूर्णांकk("%s: begin!\n", __func__);
	अगर (!nfs4_sequence_करोne(task, &calldata->res.seq_res))
		वापस;
	trace_nfs4_बंद(state, &calldata->arg, &calldata->res, task->tk_status);

	/* Handle Layoutवापस errors */
	अगर (pnfs_roc_करोne(task, &calldata->arg.lr_args, &calldata->res.lr_res,
			  &calldata->res.lr_ret) == -EAGAIN)
		जाओ out_restart;

	/* hmm. we are करोne with the inode, and in the process of मुक्तing
	 * the state_owner. we keep this around to process errors
	 */
	चयन (task->tk_status) अणु
		हाल 0:
			res_stateid = &calldata->res.stateid;
			renew_lease(server, calldata->बारtamp);
			अवरोध;
		हाल -NFS4ERR_ACCESS:
			अगर (calldata->arg.biपंचांगask != शून्य) अणु
				calldata->arg.biपंचांगask = शून्य;
				calldata->res.fattr = शून्य;
				जाओ out_restart;

			पूर्ण
			अवरोध;
		हाल -NFS4ERR_OLD_STATEID:
			/* Did we race with OPEN? */
			अगर (nfs4_refresh_खोलो_old_stateid(&calldata->arg.stateid,
						state))
				जाओ out_restart;
			जाओ out_release;
		हाल -NFS4ERR_ADMIN_REVOKED:
		हाल -NFS4ERR_STALE_STATEID:
		हाल -NFS4ERR_EXPIRED:
			nfs4_मुक्त_revoked_stateid(server,
					&calldata->arg.stateid,
					task->tk_msg.rpc_cred);
			fallthrough;
		हाल -NFS4ERR_BAD_STATEID:
			अगर (calldata->arg.भ_शेषe == 0)
				अवरोध;
			fallthrough;
		शेष:
			task->tk_status = nfs4_async_handle_exception(task,
					server, task->tk_status, &exception);
			अगर (exception.retry)
				जाओ out_restart;
	पूर्ण
	nfs_clear_खोलो_stateid(state, &calldata->arg.stateid,
			res_stateid, calldata->arg.भ_शेषe);
out_release:
	task->tk_status = 0;
	nfs_release_seqid(calldata->arg.seqid);
	nfs_refresh_inode(calldata->inode, &calldata->fattr);
	dprपूर्णांकk("%s: done, ret = %d!\n", __func__, task->tk_status);
	वापस;
out_restart:
	task->tk_status = 0;
	rpc_restart_call_prepare(task);
	जाओ out_release;
पूर्ण

अटल व्योम nfs4_बंद_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_बंदdata *calldata = data;
	काष्ठा nfs4_state *state = calldata->state;
	काष्ठा inode *inode = calldata->inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा pnfs_layout_hdr *lo;
	bool is_rकरोnly, is_wronly, is_rdwr;
	पूर्णांक call_बंद = 0;

	dprपूर्णांकk("%s: begin!\n", __func__);
	अगर (nfs_रुको_on_sequence(calldata->arg.seqid, task) != 0)
		जाओ out_रुको;

	task->tk_msg.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_OPEN_DOWNGRADE];
	spin_lock(&state->owner->so_lock);
	is_rdwr = test_bit(NFS_O_RDWR_STATE, &state->flags);
	is_rकरोnly = test_bit(NFS_O_RDONLY_STATE, &state->flags);
	is_wronly = test_bit(NFS_O_WRONLY_STATE, &state->flags);
	/* Calculate the change in खोलो mode */
	calldata->arg.भ_शेषe = 0;
	अगर (state->n_rdwr == 0) अणु
		अगर (state->n_rकरोnly == 0)
			call_बंद |= is_rकरोnly;
		अन्यथा अगर (is_rकरोnly)
			calldata->arg.भ_शेषe |= FMODE_READ;
		अगर (state->n_wronly == 0)
			call_बंद |= is_wronly;
		अन्यथा अगर (is_wronly)
			calldata->arg.भ_शेषe |= FMODE_WRITE;
		अगर (calldata->arg.भ_शेषe != (FMODE_READ|FMODE_WRITE))
			call_बंद |= is_rdwr;
	पूर्ण अन्यथा अगर (is_rdwr)
		calldata->arg.भ_शेषe |= FMODE_READ|FMODE_WRITE;

	nfs4_sync_खोलो_stateid(&calldata->arg.stateid, state);
	अगर (!nfs4_valid_खोलो_stateid(state))
		call_बंद = 0;
	spin_unlock(&state->owner->so_lock);

	अगर (!call_बंद) अणु
		/* Note: निकास _without_ calling nfs4_बंद_करोne */
		जाओ out_no_action;
	पूर्ण

	अगर (!calldata->lr.roc && nfs4_रुको_on_layoutवापस(inode, task)) अणु
		nfs_release_seqid(calldata->arg.seqid);
		जाओ out_रुको;
	पूर्ण

	lo = calldata->arg.lr_args ? calldata->arg.lr_args->layout : शून्य;
	अगर (lo && !pnfs_layout_is_valid(lo)) अणु
		calldata->arg.lr_args = शून्य;
		calldata->res.lr_res = शून्य;
	पूर्ण

	अगर (calldata->arg.भ_शेषe == 0)
		task->tk_msg.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CLOSE];

	अगर (calldata->arg.भ_शेषe == 0 || calldata->arg.भ_शेषe == FMODE_READ) अणु
		/* Close-to-खोलो cache consistency revalidation */
		अगर (!nfs4_have_delegation(inode, FMODE_READ)) अणु
			nfs4_biपंचांगask_set(calldata->arg.biपंचांगask_store,
					 server->cache_consistency_biपंचांगask,
					 inode, server, शून्य);
			calldata->arg.biपंचांगask = calldata->arg.biपंचांगask_store;
		पूर्ण अन्यथा
			calldata->arg.biपंचांगask = शून्य;
	पूर्ण

	calldata->arg.share_access =
		nfs4_map_atomic_खोलो_share(NFS_SERVER(inode),
				calldata->arg.भ_शेषe, 0);

	अगर (calldata->res.fattr == शून्य)
		calldata->arg.biपंचांगask = शून्य;
	अन्यथा अगर (calldata->arg.biपंचांगask == शून्य)
		calldata->res.fattr = शून्य;
	calldata->बारtamp = jअगरfies;
	अगर (nfs4_setup_sequence(NFS_SERVER(inode)->nfs_client,
				&calldata->arg.seq_args,
				&calldata->res.seq_res,
				task) != 0)
		nfs_release_seqid(calldata->arg.seqid);
	dprपूर्णांकk("%s: done!\n", __func__);
	वापस;
out_no_action:
	task->tk_action = शून्य;
out_रुको:
	nfs4_sequence_करोne(task, &calldata->res.seq_res);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_बंद_ops = अणु
	.rpc_call_prepare = nfs4_बंद_prepare,
	.rpc_call_करोne = nfs4_बंद_करोne,
	.rpc_release = nfs4_मुक्त_बंदdata,
पूर्ण;

/* 
 * It is possible क्रम data to be पढ़ो/written from a mem-mapped file 
 * after the sys_बंद call (which hits the vfs layer as a flush).
 * This means that we can't safely call nfsv4 बंद on a file until 
 * the inode is cleared. This in turn means that we are not good
 * NFSv4 citizens - we करो not indicate to the server to update the file's 
 * share state even when we are करोne with one of the three share 
 * stateid's in the inode.
 *
 * NOTE: Caller must be holding the sp->so_owner semaphore!
 */
पूर्णांक nfs4_करो_बंद(काष्ठा nfs4_state *state, gfp_t gfp_mask, पूर्णांक रुको)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs_seqid *(*alloc_seqid)(काष्ठा nfs_seqid_counter *, gfp_t);
	काष्ठा nfs4_बंदdata *calldata;
	काष्ठा nfs4_state_owner *sp = state->owner;
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CLOSE],
		.rpc_cred = state->owner->so_cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_बंद_ops,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	nfs4_state_protect(server->nfs_client, NFS_SP4_MACH_CRED_CLEANUP,
		&task_setup_data.rpc_client, &msg);

	calldata = kzalloc(माप(*calldata), gfp_mask);
	अगर (calldata == शून्य)
		जाओ out;
	nfs4_init_sequence(&calldata->arg.seq_args, &calldata->res.seq_res, 1, 0);
	calldata->inode = state->inode;
	calldata->state = state;
	calldata->arg.fh = NFS_FH(state->inode);
	अगर (!nfs4_copy_खोलो_stateid(&calldata->arg.stateid, state))
		जाओ out_मुक्त_calldata;
	/* Serialization क्रम the sequence id */
	alloc_seqid = server->nfs_client->cl_mvops->alloc_seqid;
	calldata->arg.seqid = alloc_seqid(&state->owner->so_seqid, gfp_mask);
	अगर (IS_ERR(calldata->arg.seqid))
		जाओ out_मुक्त_calldata;
	nfs_fattr_init(&calldata->fattr);
	calldata->arg.भ_शेषe = 0;
	calldata->lr.arg.ld_निजी = &calldata->lr.ld_निजी;
	calldata->res.fattr = &calldata->fattr;
	calldata->res.seqid = calldata->arg.seqid;
	calldata->res.server = server;
	calldata->res.lr_ret = -NFS4ERR_NOMATCHING_LAYOUT;
	calldata->lr.roc = pnfs_roc(state->inode,
			&calldata->lr.arg, &calldata->lr.res, msg.rpc_cred);
	अगर (calldata->lr.roc) अणु
		calldata->arg.lr_args = &calldata->lr.arg;
		calldata->res.lr_res = &calldata->lr.res;
	पूर्ण
	nfs_sb_active(calldata->inode->i_sb);

	msg.rpc_argp = &calldata->arg;
	msg.rpc_resp = &calldata->res;
	task_setup_data.callback_data = calldata;
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	status = 0;
	अगर (रुको)
		status = rpc_रुको_क्रम_completion_task(task);
	rpc_put_task(task);
	वापस status;
out_मुक्त_calldata:
	kमुक्त(calldata);
out:
	nfs4_put_खोलो_state(state);
	nfs4_put_state_owner(sp);
	वापस status;
पूर्ण

अटल काष्ठा inode *
nfs4_atomic_खोलो(काष्ठा inode *dir, काष्ठा nfs_खोलो_context *ctx,
		पूर्णांक खोलो_flags, काष्ठा iattr *attr, पूर्णांक *खोलोed)
अणु
	काष्ठा nfs4_state *state;
	काष्ठा nfs4_label l = अणु0, 0, 0, शून्यपूर्ण, *label = शून्य;

	label = nfs4_label_init_security(dir, ctx->dentry, attr, &l);

	/* Protect against concurrent sillydeletes */
	state = nfs4_करो_खोलो(dir, ctx, खोलो_flags, attr, label, खोलोed);

	nfs4_label_release_security(label);

	अगर (IS_ERR(state))
		वापस ERR_CAST(state);
	वापस state->inode;
पूर्ण

अटल व्योम nfs4_बंद_context(काष्ठा nfs_खोलो_context *ctx, पूर्णांक is_sync)
अणु
	अगर (ctx->state == शून्य)
		वापस;
	अगर (is_sync)
		nfs4_बंद_sync(ctx->state, _nfs4_ctx_to_खोलोmode(ctx));
	अन्यथा
		nfs4_बंद_state(ctx->state, _nfs4_ctx_to_खोलोmode(ctx));
पूर्ण

#घोषणा FATTR4_WORD1_NFS40_MASK (2*FATTR4_WORD1_MOUNTED_ON_खाताID - 1UL)
#घोषणा FATTR4_WORD2_NFS41_MASK (2*FATTR4_WORD2_SUPPATTR_EXCLCREAT - 1UL)
#घोषणा FATTR4_WORD2_NFS42_MASK (2*FATTR4_WORD2_XATTR_SUPPORT - 1UL)

अटल पूर्णांक _nfs4_server_capabilities(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle)
अणु
	u32 biपंचांगask[3] = अणुपूर्ण, minorversion = server->nfs_client->cl_minorversion;
	काष्ठा nfs4_server_caps_arg args = अणु
		.fhandle = fhandle,
		.biपंचांगask = biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_server_caps_res res = अणुपूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SERVER_CAPS],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	पूर्णांक status;
	पूर्णांक i;

	biपंचांगask[0] = FATTR4_WORD0_SUPPORTED_ATTRS |
		     FATTR4_WORD0_FH_EXPIRE_TYPE |
		     FATTR4_WORD0_LINK_SUPPORT |
		     FATTR4_WORD0_SYMLINK_SUPPORT |
		     FATTR4_WORD0_ACLSUPPORT;
	अगर (minorversion)
		biपंचांगask[2] = FATTR4_WORD2_SUPPATTR_EXCLCREAT;

	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
	अगर (status == 0) अणु
		/* Sanity check the server answers */
		चयन (minorversion) अणु
		हाल 0:
			res.attr_biपंचांगask[1] &= FATTR4_WORD1_NFS40_MASK;
			res.attr_biपंचांगask[2] = 0;
			अवरोध;
		हाल 1:
			res.attr_biपंचांगask[2] &= FATTR4_WORD2_NFS41_MASK;
			अवरोध;
		हाल 2:
			res.attr_biपंचांगask[2] &= FATTR4_WORD2_NFS42_MASK;
		पूर्ण
		स_नकल(server->attr_biपंचांगask, res.attr_biपंचांगask, माप(server->attr_biपंचांगask));
		server->caps &= ~(NFS_CAP_ACLS | NFS_CAP_HARDLINKS |
				  NFS_CAP_SYMLINKS| NFS_CAP_SECURITY_LABEL);
		server->fattr_valid = NFS_ATTR_FATTR_V4;
		अगर (res.attr_biपंचांगask[0] & FATTR4_WORD0_ACL &&
				res.acl_biपंचांगask & ACL4_SUPPORT_ALLOW_ACL)
			server->caps |= NFS_CAP_ACLS;
		अगर (res.has_links != 0)
			server->caps |= NFS_CAP_HARDLINKS;
		अगर (res.has_symlinks != 0)
			server->caps |= NFS_CAP_SYMLINKS;
#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
		अगर (res.attr_biपंचांगask[2] & FATTR4_WORD2_SECURITY_LABEL)
			server->caps |= NFS_CAP_SECURITY_LABEL;
#पूर्ण_अगर
		अगर (!(res.attr_biपंचांगask[0] & FATTR4_WORD0_खाताID))
			server->fattr_valid &= ~NFS_ATTR_FATTR_खाताID;
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_MODE))
			server->fattr_valid &= ~NFS_ATTR_FATTR_MODE;
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_NUMLINKS))
			server->fattr_valid &= ~NFS_ATTR_FATTR_NLINK;
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_OWNER))
			server->fattr_valid &= ~(NFS_ATTR_FATTR_OWNER |
				NFS_ATTR_FATTR_OWNER_NAME);
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_OWNER_GROUP))
			server->fattr_valid &= ~(NFS_ATTR_FATTR_GROUP |
				NFS_ATTR_FATTR_GROUP_NAME);
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_SPACE_USED))
			server->fattr_valid &= ~NFS_ATTR_FATTR_SPACE_USED;
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_TIME_ACCESS))
			server->fattr_valid &= ~NFS_ATTR_FATTR_ATIME;
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_TIME_METADATA))
			server->fattr_valid &= ~NFS_ATTR_FATTR_CTIME;
		अगर (!(res.attr_biपंचांगask[1] & FATTR4_WORD1_TIME_MODIFY))
			server->fattr_valid &= ~NFS_ATTR_FATTR_MTIME;
		स_नकल(server->attr_biपंचांगask_nl, res.attr_biपंचांगask,
				माप(server->attr_biपंचांगask));
		server->attr_biपंचांगask_nl[2] &= ~FATTR4_WORD2_SECURITY_LABEL;

		स_नकल(server->cache_consistency_biपंचांगask, res.attr_biपंचांगask, माप(server->cache_consistency_biपंचांगask));
		server->cache_consistency_biपंचांगask[0] &= FATTR4_WORD0_CHANGE|FATTR4_WORD0_SIZE;
		server->cache_consistency_biपंचांगask[1] &= FATTR4_WORD1_TIME_METADATA|FATTR4_WORD1_TIME_MODIFY;
		server->cache_consistency_biपंचांगask[2] = 0;

		/* Aव्योम a regression due to buggy server */
		क्रम (i = 0; i < ARRAY_SIZE(res.exclcreat_biपंचांगask); i++)
			res.exclcreat_biपंचांगask[i] &= res.attr_biपंचांगask[i];
		स_नकल(server->exclcreat_biपंचांगask, res.exclcreat_biपंचांगask,
			माप(server->exclcreat_biपंचांगask));

		server->acl_biपंचांगask = res.acl_biपंचांगask;
		server->fh_expire_type = res.fh_expire_type;
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक nfs4_server_capabilities(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = nfs4_handle_exception(server,
				_nfs4_server_capabilities(server, fhandle),
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_lookup_root(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_fsinfo *info)
अणु
	u32 biपंचांगask[3];
	काष्ठा nfs4_lookup_root_arg args = अणु
		.biपंचांगask = biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_lookup_res res = अणु
		.server = server,
		.fattr = info->fattr,
		.fh = fhandle,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LOOKUP_ROOT],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;

	biपंचांगask[0] = nfs4_fattr_biपंचांगap[0];
	biपंचांगask[1] = nfs4_fattr_biपंचांगap[1];
	/*
	 * Process the label in the upcoming getfattr
	 */
	biपंचांगask[2] = nfs4_fattr_biपंचांगap[2] & ~FATTR4_WORD2_SECURITY_LABEL;

	nfs_fattr_init(info->fattr);
	वापस nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
पूर्ण

अटल पूर्णांक nfs4_lookup_root(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_fsinfo *info)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_lookup_root(server, fhandle, info);
		trace_nfs4_lookup_root(server, fhandle, info->fattr, err);
		चयन (err) अणु
		हाल 0:
		हाल -NFS4ERR_WRONGSEC:
			जाओ out;
		शेष:
			err = nfs4_handle_exception(server, err, &exception);
		पूर्ण
	पूर्ण जबतक (exception.retry);
out:
	वापस err;
पूर्ण

अटल पूर्णांक nfs4_lookup_root_sec(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
				काष्ठा nfs_fsinfo *info, rpc_authflavor_t flavor)
अणु
	काष्ठा rpc_auth_create_args auth_args = अणु
		.pseuकरोflavor = flavor,
	पूर्ण;
	काष्ठा rpc_auth *auth;

	auth = rpcauth_create(&auth_args, server->client);
	अगर (IS_ERR(auth))
		वापस -EACCES;
	वापस nfs4_lookup_root(server, fhandle, info);
पूर्ण

/*
 * Retry pseuकरोroot lookup with various security flavors.  We करो this when:
 *
 *   NFSv4.0: the PUTROOTFH operation वापसs NFS4ERR_WRONGSEC
 *   NFSv4.1: the server करोes not support the SECINFO_NO_NAME operation
 *
 * Returns zero on success, or a negative NFS4ERR value, or a
 * negative त्रुटि_सं value.
 */
अटल पूर्णांक nfs4_find_root_sec(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
			      काष्ठा nfs_fsinfo *info)
अणु
	/* Per 3530bis 15.33.5 */
	अटल स्थिर rpc_authflavor_t flav_array[] = अणु
		RPC_AUTH_GSS_KRB5P,
		RPC_AUTH_GSS_KRB5I,
		RPC_AUTH_GSS_KRB5,
		RPC_AUTH_UNIX,			/* courtesy */
		RPC_AUTH_शून्य,
	पूर्ण;
	पूर्णांक status = -EPERM;
	माप_प्रकार i;

	अगर (server->auth_info.flavor_len > 0) अणु
		/* try each flavor specअगरied by user */
		क्रम (i = 0; i < server->auth_info.flavor_len; i++) अणु
			status = nfs4_lookup_root_sec(server, fhandle, info,
						server->auth_info.flavors[i]);
			अगर (status == -NFS4ERR_WRONGSEC || status == -EACCES)
				जारी;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* no flavors specअगरied by user, try शेष list */
		क्रम (i = 0; i < ARRAY_SIZE(flav_array); i++) अणु
			status = nfs4_lookup_root_sec(server, fhandle, info,
						      flav_array[i]);
			अगर (status == -NFS4ERR_WRONGSEC || status == -EACCES)
				जारी;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * -EACCES could mean that the user करोesn't have correct permissions
	 * to access the mount.  It could also mean that we tried to mount
	 * with a gss auth flavor, but rpc.gssd isn't running.  Either way,
	 * existing mount programs करोn't handle -EACCES very well so it should
	 * be mapped to -EPERM instead.
	 */
	अगर (status == -EACCES)
		status = -EPERM;
	वापस status;
पूर्ण

/**
 * nfs4_proc_get_rootfh - get file handle क्रम server's pseuकरोroot
 * @server: initialized nfs_server handle
 * @fhandle: we fill in the pseuकरो-fs root file handle
 * @info: we fill in an FSINFO काष्ठा
 * @auth_probe: probe the auth flavours
 *
 * Returns zero on success, or a negative त्रुटि_सं.
 */
पूर्णांक nfs4_proc_get_rootfh(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
			 काष्ठा nfs_fsinfo *info,
			 bool auth_probe)
अणु
	पूर्णांक status = 0;

	अगर (!auth_probe)
		status = nfs4_lookup_root(server, fhandle, info);

	अगर (auth_probe || status == NFS4ERR_WRONGSEC)
		status = server->nfs_client->cl_mvops->find_root_sec(server,
				fhandle, info);

	अगर (status == 0)
		status = nfs4_server_capabilities(server, fhandle);
	अगर (status == 0)
		status = nfs4_करो_fsinfo(server, fhandle, info);

	वापस nfs4_map_errors(status);
पूर्ण

अटल पूर्णांक nfs4_proc_get_root(काष्ठा nfs_server *server, काष्ठा nfs_fh *mntfh,
			      काष्ठा nfs_fsinfo *info)
अणु
	पूर्णांक error;
	काष्ठा nfs_fattr *fattr = info->fattr;
	काष्ठा nfs4_label *label = fattr->label;

	error = nfs4_server_capabilities(server, mntfh);
	अगर (error < 0) अणु
		dprपूर्णांकk("nfs4_get_root: getcaps error = %d\n", -error);
		वापस error;
	पूर्ण

	error = nfs4_proc_getattr(server, mntfh, fattr, label, शून्य);
	अगर (error < 0) अणु
		dprपूर्णांकk("nfs4_get_root: getattr error = %d\n", -error);
		जाओ out;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_FSID &&
	    !nfs_fsid_equal(&server->fsid, &fattr->fsid))
		स_नकल(&server->fsid, &fattr->fsid, माप(server->fsid));

out:
	वापस error;
पूर्ण

/*
 * Get locations and (maybe) other attributes of a referral.
 * Note that we'll actually follow the referral later when
 * we detect fsid mismatch in inode revalidation
 */
अटल पूर्णांक nfs4_get_referral(काष्ठा rpc_clnt *client, काष्ठा inode *dir,
			     स्थिर काष्ठा qstr *name, काष्ठा nfs_fattr *fattr,
			     काष्ठा nfs_fh *fhandle)
अणु
	पूर्णांक status = -ENOMEM;
	काष्ठा page *page = शून्य;
	काष्ठा nfs4_fs_locations *locations = शून्य;

	page = alloc_page(GFP_KERNEL);
	अगर (page == शून्य)
		जाओ out;
	locations = kदो_स्मृति(माप(काष्ठा nfs4_fs_locations), GFP_KERNEL);
	अगर (locations == शून्य)
		जाओ out;

	status = nfs4_proc_fs_locations(client, dir, name, locations, page);
	अगर (status != 0)
		जाओ out;

	/*
	 * If the fsid didn't change, this is a migration event, not a
	 * referral.  Cause us to drop पूर्णांकo the exception handler, which
	 * will kick off migration recovery.
	 */
	अगर (nfs_fsid_equal(&NFS_SERVER(dir)->fsid, &locations->fattr.fsid)) अणु
		dprपूर्णांकk("%s: server did not return a different fsid for"
			" a referral at %s\n", __func__, name->name);
		status = -NFS4ERR_MOVED;
		जाओ out;
	पूर्ण
	/* Fixup attributes क्रम the nfs_lookup() call to nfs_fhget() */
	nfs_fixup_referral_attributes(&locations->fattr);

	/* replace the lookup nfs_fattr with the locations nfs_fattr */
	स_नकल(fattr, &locations->fattr, माप(काष्ठा nfs_fattr));
	स_रखो(fhandle, 0, माप(काष्ठा nfs_fh));
out:
	अगर (page)
		__मुक्त_page(page);
	kमुक्त(locations);
	वापस status;
पूर्ण

अटल पूर्णांक _nfs4_proc_getattr(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
				काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label,
				काष्ठा inode *inode)
अणु
	__u32 biपंचांगask[NFS4_BITMASK_SZ];
	काष्ठा nfs4_getattr_arg args = अणु
		.fh = fhandle,
		.biपंचांगask = biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_getattr_res res = अणु
		.fattr = fattr,
		.label = label,
		.server = server,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_GETATTR],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	अचिन्हित लघु task_flags = 0;

	/* Is this is an attribute revalidation, subject to softreval? */
	अगर (inode && (server->flags & NFS_MOUNT_SOFTREVAL))
		task_flags |= RPC_TASK_TIMEOUT;

	nfs4_biपंचांगap_copy_adjust(biपंचांगask, nfs4_biपंचांगask(server, label), inode, 0);
	nfs_fattr_init(fattr);
	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 0);
	वापस nfs4_करो_call_sync(server->client, server, &msg,
			&args.seq_args, &res.seq_res, task_flags);
पूर्ण

पूर्णांक nfs4_proc_getattr(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
				काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label,
				काष्ठा inode *inode)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_getattr(server, fhandle, fattr, label, inode);
		trace_nfs4_getattr(server, fhandle, fattr, err);
		err = nfs4_handle_exception(server, err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

/* 
 * The file is not बंदd अगर it is खोलोed due to the a request to change
 * the size of the file. The खोलो call will not be needed once the
 * VFS layer lookup-पूर्णांकents are implemented.
 *
 * Close is called when the inode is destroyed.
 * If we haven't खोलोed the file क्रम O_WRONLY, we
 * need to in the size_change हाल to obtain a stateid.
 *
 * Got race?
 * Because OPEN is always करोne by name in nfsv4, it is
 * possible that we खोलोed a dअगरferent file by the same
 * name.  We can recognize this race condition, but we
 * can't करो anything about it besides वापसing an error.
 *
 * This will be fixed with VFS changes (lookup-पूर्णांकent).
 */
अटल पूर्णांक
nfs4_proc_setattr(काष्ठा dentry *dentry, काष्ठा nfs_fattr *fattr,
		  काष्ठा iattr *sattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	स्थिर काष्ठा cred *cred = शून्य;
	काष्ठा nfs_खोलो_context *ctx = शून्य;
	काष्ठा nfs4_label *label = शून्य;
	पूर्णांक status;

	अगर (pnfs_ld_layoutret_on_setattr(inode) &&
	    sattr->ia_valid & ATTR_SIZE &&
	    sattr->ia_size < i_size_पढ़ो(inode))
		pnfs_commit_and_वापस_layout(inode);

	nfs_fattr_init(fattr);
	
	/* Deal with खोलो(O_TRUNC) */
	अगर (sattr->ia_valid & ATTR_OPEN)
		sattr->ia_valid &= ~(ATTR_MTIME|ATTR_CTIME);

	/* Optimization: अगर the end result is no change, करोn't RPC */
	अगर ((sattr->ia_valid & ~(ATTR_खाता|ATTR_OPEN)) == 0)
		वापस 0;

	/* Search क्रम an existing खोलो(O_WRITE) file */
	अगर (sattr->ia_valid & ATTR_खाता) अणु

		ctx = nfs_file_खोलो_context(sattr->ia_file);
		अगर (ctx)
			cred = ctx->cred;
	पूर्ण

	label = nfs4_label_alloc(NFS_SERVER(inode), GFP_KERNEL);
	अगर (IS_ERR(label))
		वापस PTR_ERR(label);

	/* Return any delegations अगर we're going to change ACLs */
	अगर ((sattr->ia_valid & (ATTR_MODE|ATTR_UID|ATTR_GID)) != 0)
		nfs4_inode_make_ग_लिखोable(inode);

	status = nfs4_करो_setattr(inode, cred, fattr, sattr, ctx, शून्य, label);
	अगर (status == 0) अणु
		nfs_setattr_update_inode(inode, sattr, fattr);
		nfs_setsecurity(inode, fattr, label);
	पूर्ण
	nfs4_label_मुक्त(label);
	वापस status;
पूर्ण

अटल पूर्णांक _nfs4_proc_lookup(काष्ठा rpc_clnt *clnt, काष्ठा inode *dir,
		काष्ठा dentry *dentry, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	पूर्णांक		       status;
	काष्ठा nfs4_lookup_arg args = अणु
		.biपंचांगask = server->attr_biपंचांगask,
		.dir_fh = NFS_FH(dir),
		.name = &dentry->d_name,
	पूर्ण;
	काष्ठा nfs4_lookup_res res = अणु
		.server = server,
		.fattr = fattr,
		.label = label,
		.fh = fhandle,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LOOKUP],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	अचिन्हित लघु task_flags = 0;

	/* Is this is an attribute revalidation, subject to softreval? */
	अगर (nfs_lookup_is_soft_revalidate(dentry))
		task_flags |= RPC_TASK_TIMEOUT;

	args.biपंचांगask = nfs4_biपंचांगask(server, label);

	nfs_fattr_init(fattr);

	dprपूर्णांकk("NFS call  lookup %pd2\n", dentry);
	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 0);
	status = nfs4_करो_call_sync(clnt, server, &msg,
			&args.seq_args, &res.seq_res, task_flags);
	dprपूर्णांकk("NFS reply lookup: %d\n", status);
	वापस status;
पूर्ण

अटल व्योम nfs_fixup_secinfo_attributes(काष्ठा nfs_fattr *fattr)
अणु
	fattr->valid |= NFS_ATTR_FATTR_TYPE | NFS_ATTR_FATTR_MODE |
		NFS_ATTR_FATTR_NLINK | NFS_ATTR_FATTR_MOUNTPOINT;
	fattr->mode = S_IFसूची | S_IRUGO | S_IXUGO;
	fattr->nlink = 2;
पूर्ण

अटल पूर्णांक nfs4_proc_lookup_common(काष्ठा rpc_clnt **clnt, काष्ठा inode *dir,
				   काष्ठा dentry *dentry, काष्ठा nfs_fh *fhandle,
				   काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	काष्ठा rpc_clnt *client = *clnt;
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_lookup(client, dir, dentry, fhandle, fattr, label);
		trace_nfs4_lookup(dir, name, err);
		चयन (err) अणु
		हाल -NFS4ERR_BADNAME:
			err = -ENOENT;
			जाओ out;
		हाल -NFS4ERR_MOVED:
			err = nfs4_get_referral(client, dir, name, fattr, fhandle);
			अगर (err == -NFS4ERR_MOVED)
				err = nfs4_handle_exception(NFS_SERVER(dir), err, &exception);
			जाओ out;
		हाल -NFS4ERR_WRONGSEC:
			err = -EPERM;
			अगर (client != *clnt)
				जाओ out;
			client = nfs4_negotiate_security(client, dir, name);
			अगर (IS_ERR(client))
				वापस PTR_ERR(client);

			exception.retry = 1;
			अवरोध;
		शेष:
			err = nfs4_handle_exception(NFS_SERVER(dir), err, &exception);
		पूर्ण
	पूर्ण जबतक (exception.retry);

out:
	अगर (err == 0)
		*clnt = client;
	अन्यथा अगर (client != *clnt)
		rpc_shutकरोwn_client(client);

	वापस err;
पूर्ण

अटल पूर्णांक nfs4_proc_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			    काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr,
			    काष्ठा nfs4_label *label)
अणु
	पूर्णांक status;
	काष्ठा rpc_clnt *client = NFS_CLIENT(dir);

	status = nfs4_proc_lookup_common(&client, dir, dentry, fhandle, fattr, label);
	अगर (client != NFS_CLIENT(dir)) अणु
		rpc_shutकरोwn_client(client);
		nfs_fixup_secinfo_attributes(fattr);
	पूर्ण
	वापस status;
पूर्ण

काष्ठा rpc_clnt *
nfs4_proc_lookup_mountpoपूर्णांक(काष्ठा inode *dir, काष्ठा dentry *dentry,
			    काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा rpc_clnt *client = NFS_CLIENT(dir);
	पूर्णांक status;

	status = nfs4_proc_lookup_common(&client, dir, dentry, fhandle, fattr, शून्य);
	अगर (status < 0)
		वापस ERR_PTR(status);
	वापस (client == NFS_CLIENT(dir)) ? rpc_clone_client(client) : client;
पूर्ण

अटल पूर्णांक _nfs4_proc_lookupp(काष्ठा inode *inode,
		काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_label *label)
अणु
	काष्ठा rpc_clnt *clnt = NFS_CLIENT(inode);
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	पूर्णांक		       status;
	काष्ठा nfs4_lookupp_arg args = अणु
		.biपंचांगask = server->attr_biपंचांगask,
		.fh = NFS_FH(inode),
	पूर्ण;
	काष्ठा nfs4_lookupp_res res = अणु
		.server = server,
		.fattr = fattr,
		.label = label,
		.fh = fhandle,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LOOKUPP],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	अचिन्हित लघु task_flags = 0;

	अगर (NFS_SERVER(inode)->flags & NFS_MOUNT_SOFTREVAL)
		task_flags |= RPC_TASK_TIMEOUT;

	args.biपंचांगask = nfs4_biपंचांगask(server, label);

	nfs_fattr_init(fattr);

	dprपूर्णांकk("NFS call  lookupp ino=0x%lx\n", inode->i_ino);
	status = nfs4_call_sync(clnt, server, &msg, &args.seq_args,
				&res.seq_res, task_flags);
	dprपूर्णांकk("NFS reply lookupp: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_lookupp(काष्ठा inode *inode, काष्ठा nfs_fh *fhandle,
			     काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_lookupp(inode, fhandle, fattr, label);
		trace_nfs4_lookupp(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_proc_access(काष्ठा inode *inode, काष्ठा nfs_access_entry *entry)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs4_accessargs args = अणु
		.fh = NFS_FH(inode),
		.access = entry->mask,
	पूर्ण;
	काष्ठा nfs4_accessres res = अणु
		.server = server,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_ACCESS],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = entry->cred,
	पूर्ण;
	पूर्णांक status = 0;

	अगर (!nfs4_have_delegation(inode, FMODE_READ)) अणु
		res.fattr = nfs_alloc_fattr();
		अगर (res.fattr == शून्य)
			वापस -ENOMEM;
		args.biपंचांगask = server->cache_consistency_biपंचांगask;
	पूर्ण
	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
	अगर (!status) अणु
		nfs_access_set_mask(entry, res.access);
		अगर (res.fattr)
			nfs_refresh_inode(inode, res.fattr);
	पूर्ण
	nfs_मुक्त_fattr(res.fattr);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_access(काष्ठा inode *inode, काष्ठा nfs_access_entry *entry)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_access(inode, entry);
		trace_nfs4_access(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

/*
 * TODO: For the समय being, we करोn't try to get any attributes
 * aदीर्घ with any of the zero-copy operations READ, READसूची,
 * READLINK, WRITE.
 *
 * In the हाल of the first three, we want to put the GETATTR
 * after the पढ़ो-type operation -- this is because it is hard
 * to predict the length of a GETATTR response in v4, and thus
 * align the READ data correctly.  This means that the GETATTR
 * may end up partially falling पूर्णांकo the page cache, and we should
 * shअगरt it पूर्णांकo the 'tail' of the xdr_buf beक्रमe processing.
 * To करो this efficiently, we need to know the total length
 * of data received, which करोesn't seem to be available outside
 * of the RPC layer.
 *
 * In the हाल of WRITE, we also want to put the GETATTR after
 * the operation -- in this हाल because we want to make sure
 * we get the post-operation mसमय and size.
 *
 * Both of these changes to the XDR layer would in fact be quite
 * minor, but I decided to leave them क्रम a subsequent patch.
 */
अटल पूर्णांक _nfs4_proc_पढ़ोlink(काष्ठा inode *inode, काष्ठा page *page,
		अचिन्हित पूर्णांक pgbase, अचिन्हित पूर्णांक pglen)
अणु
	काष्ठा nfs4_पढ़ोlink args = अणु
		.fh       = NFS_FH(inode),
		.pgbase	  = pgbase,
		.pglen    = pglen,
		.pages    = &page,
	पूर्ण;
	काष्ठा nfs4_पढ़ोlink_res res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_READLINK],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;

	वापस nfs4_call_sync(NFS_SERVER(inode)->client, NFS_SERVER(inode), &msg, &args.seq_args, &res.seq_res, 0);
पूर्ण

अटल पूर्णांक nfs4_proc_पढ़ोlink(काष्ठा inode *inode, काष्ठा page *page,
		अचिन्हित पूर्णांक pgbase, अचिन्हित पूर्णांक pglen)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_पढ़ोlink(inode, page, pgbase, pglen);
		trace_nfs4_पढ़ोlink(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

/*
 * This is just क्रम mknod.  खोलो(O_CREAT) will always करो ->खोलो_context().
 */
अटल पूर्णांक
nfs4_proc_create(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr,
		 पूर्णांक flags)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs4_label l, *ilabel = शून्य;
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs4_state *state;
	पूर्णांक status = 0;

	ctx = alloc_nfs_खोलो_context(dentry, FMODE_READ, शून्य);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);

	ilabel = nfs4_label_init_security(dir, dentry, sattr, &l);

	अगर (!(server->attr_biपंचांगask[2] & FATTR4_WORD2_MODE_UMASK))
		sattr->ia_mode &= ~current_umask();
	state = nfs4_करो_खोलो(dir, ctx, flags, sattr, ilabel, शून्य);
	अगर (IS_ERR(state)) अणु
		status = PTR_ERR(state);
		जाओ out;
	पूर्ण
out:
	nfs4_label_release_security(ilabel);
	put_nfs_खोलो_context(ctx);
	वापस status;
पूर्ण

अटल पूर्णांक
_nfs4_proc_हटाओ(काष्ठा inode *dir, स्थिर काष्ठा qstr *name, u32 ftype)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs_हटाओargs args = अणु
		.fh = NFS_FH(dir),
		.name = *name,
	पूर्ण;
	काष्ठा nfs_हटाओres res = अणु
		.server = server,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_REMOVE],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	अचिन्हित दीर्घ बारtamp = jअगरfies;
	पूर्णांक status;

	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 1);
	अगर (status == 0) अणु
		spin_lock(&dir->i_lock);
		/* Removing a directory decrements nlink in the parent */
		अगर (ftype == NF4सूची && dir->i_nlink > 2)
			nfs4_dec_nlink_locked(dir);
		nfs4_update_changeattr_locked(dir, &res.cinfo, बारtamp,
					      NFS_INO_INVALID_DATA);
		spin_unlock(&dir->i_lock);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक err;

	अगर (inode) अणु
		अगर (inode->i_nlink == 1)
			nfs4_inode_वापस_delegation(inode);
		अन्यथा
			nfs4_inode_make_ग_लिखोable(inode);
	पूर्ण
	करो अणु
		err = _nfs4_proc_हटाओ(dir, &dentry->d_name, NF4REG);
		trace_nfs4_हटाओ(dir, &dentry->d_name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक nfs4_proc_सूची_हटाओ(काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs4_proc_हटाओ(dir, name, NF4सूची);
		trace_nfs4_हटाओ(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल व्योम nfs4_proc_unlink_setup(काष्ठा rpc_message *msg,
		काष्ठा dentry *dentry,
		काष्ठा inode *inode)
अणु
	काष्ठा nfs_हटाओargs *args = msg->rpc_argp;
	काष्ठा nfs_हटाओres *res = msg->rpc_resp;

	res->server = NFS_SB(dentry->d_sb);
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_REMOVE];
	nfs4_init_sequence(&args->seq_args, &res->seq_res, 1, 0);

	nfs_fattr_init(res->dir_attr);

	अगर (inode)
		nfs4_inode_वापस_delegation(inode);
पूर्ण

अटल व्योम nfs4_proc_unlink_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_unlinkdata *data)
अणु
	nfs4_setup_sequence(NFS_SB(data->dentry->d_sb)->nfs_client,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
पूर्ण

अटल पूर्णांक nfs4_proc_unlink_करोne(काष्ठा rpc_task *task, काष्ठा inode *dir)
अणु
	काष्ठा nfs_unlinkdata *data = task->tk_calldata;
	काष्ठा nfs_हटाओres *res = &data->res;

	अगर (!nfs4_sequence_करोne(task, &res->seq_res))
		वापस 0;
	अगर (nfs4_async_handle_error(task, res->server, शून्य,
				    &data->समयout) == -EAGAIN)
		वापस 0;
	अगर (task->tk_status == 0)
		nfs4_update_changeattr(dir, &res->cinfo,
				res->dir_attr->समय_start,
				NFS_INO_INVALID_DATA);
	वापस 1;
पूर्ण

अटल व्योम nfs4_proc_नाम_setup(काष्ठा rpc_message *msg,
		काष्ठा dentry *old_dentry,
		काष्ठा dentry *new_dentry)
अणु
	काष्ठा nfs_नामargs *arg = msg->rpc_argp;
	काष्ठा nfs_नामres *res = msg->rpc_resp;
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);

	अगर (old_inode)
		nfs4_inode_make_ग_लिखोable(old_inode);
	अगर (new_inode)
		nfs4_inode_वापस_delegation(new_inode);
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RENAME];
	res->server = NFS_SB(old_dentry->d_sb);
	nfs4_init_sequence(&arg->seq_args, &res->seq_res, 1, 0);
पूर्ण

अटल व्योम nfs4_proc_नाम_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_नामdata *data)
अणु
	nfs4_setup_sequence(NFS_SERVER(data->old_dir)->nfs_client,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
पूर्ण

अटल पूर्णांक nfs4_proc_नाम_करोne(काष्ठा rpc_task *task, काष्ठा inode *old_dir,
				 काष्ठा inode *new_dir)
अणु
	काष्ठा nfs_नामdata *data = task->tk_calldata;
	काष्ठा nfs_नामres *res = &data->res;

	अगर (!nfs4_sequence_करोne(task, &res->seq_res))
		वापस 0;
	अगर (nfs4_async_handle_error(task, res->server, शून्य, &data->समयout) == -EAGAIN)
		वापस 0;

	अगर (task->tk_status == 0) अणु
		अगर (new_dir != old_dir) अणु
			/* Note: If we moved a directory, nlink will change */
			nfs4_update_changeattr(old_dir, &res->old_cinfo,
					res->old_fattr->समय_start,
					NFS_INO_INVALID_NLINK |
					    NFS_INO_INVALID_DATA);
			nfs4_update_changeattr(new_dir, &res->new_cinfo,
					res->new_fattr->समय_start,
					NFS_INO_INVALID_NLINK |
					    NFS_INO_INVALID_DATA);
		पूर्ण अन्यथा
			nfs4_update_changeattr(old_dir, &res->old_cinfo,
					res->old_fattr->समय_start,
					NFS_INO_INVALID_DATA);
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक _nfs4_proc_link(काष्ठा inode *inode, काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	__u32 biपंचांगask[NFS4_BITMASK_SZ];
	काष्ठा nfs4_link_arg arg = अणु
		.fh     = NFS_FH(inode),
		.dir_fh = NFS_FH(dir),
		.name   = name,
		.biपंचांगask = biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_link_res res = अणु
		.server = server,
		.label = शून्य,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LINK],
		.rpc_argp = &arg,
		.rpc_resp = &res,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	res.fattr = nfs_alloc_fattr();
	अगर (res.fattr == शून्य)
		जाओ out;

	res.label = nfs4_label_alloc(server, GFP_KERNEL);
	अगर (IS_ERR(res.label)) अणु
		status = PTR_ERR(res.label);
		जाओ out;
	पूर्ण

	nfs4_inode_make_ग_लिखोable(inode);
	nfs4_biपंचांगap_copy_adjust(biपंचांगask, nfs4_biपंचांगask(server, res.label), inode,
				NFS_INO_INVALID_CHANGE);
	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	अगर (!status) अणु
		nfs4_update_changeattr(dir, &res.cinfo, res.fattr->समय_start,
				       NFS_INO_INVALID_DATA);
		nfs4_inc_nlink(inode);
		status = nfs_post_op_update_inode(inode, res.fattr);
		अगर (!status)
			nfs_setsecurity(inode, res.fattr, res.label);
	पूर्ण


	nfs4_label_मुक्त(res.label);

out:
	nfs_मुक्त_fattr(res.fattr);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_link(काष्ठा inode *inode, काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = nfs4_handle_exception(NFS_SERVER(inode),
				_nfs4_proc_link(inode, dir, name),
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

काष्ठा nfs4_createdata अणु
	काष्ठा rpc_message msg;
	काष्ठा nfs4_create_arg arg;
	काष्ठा nfs4_create_res res;
	काष्ठा nfs_fh fh;
	काष्ठा nfs_fattr fattr;
	काष्ठा nfs4_label *label;
पूर्ण;

अटल काष्ठा nfs4_createdata *nfs4_alloc_createdata(काष्ठा inode *dir,
		स्थिर काष्ठा qstr *name, काष्ठा iattr *sattr, u32 ftype)
अणु
	काष्ठा nfs4_createdata *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (data != शून्य) अणु
		काष्ठा nfs_server *server = NFS_SERVER(dir);

		data->label = nfs4_label_alloc(server, GFP_KERNEL);
		अगर (IS_ERR(data->label))
			जाओ out_मुक्त;

		data->msg.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CREATE];
		data->msg.rpc_argp = &data->arg;
		data->msg.rpc_resp = &data->res;
		data->arg.dir_fh = NFS_FH(dir);
		data->arg.server = server;
		data->arg.name = name;
		data->arg.attrs = sattr;
		data->arg.ftype = ftype;
		data->arg.biपंचांगask = nfs4_biपंचांगask(server, data->label);
		data->arg.umask = current_umask();
		data->res.server = server;
		data->res.fh = &data->fh;
		data->res.fattr = &data->fattr;
		data->res.label = data->label;
		nfs_fattr_init(data->res.fattr);
	पूर्ण
	वापस data;
out_मुक्त:
	kमुक्त(data);
	वापस शून्य;
पूर्ण

अटल पूर्णांक nfs4_करो_create(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा nfs4_createdata *data)
अणु
	पूर्णांक status = nfs4_call_sync(NFS_SERVER(dir)->client, NFS_SERVER(dir), &data->msg,
				    &data->arg.seq_args, &data->res.seq_res, 1);
	अगर (status == 0) अणु
		spin_lock(&dir->i_lock);
		/* Creating a directory bumps nlink in the parent */
		अगर (data->arg.ftype == NF4सूची)
			nfs4_inc_nlink_locked(dir);
		nfs4_update_changeattr_locked(dir, &data->res.dir_cinfo,
					      data->res.fattr->समय_start,
					      NFS_INO_INVALID_DATA);
		spin_unlock(&dir->i_lock);
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, data->res.label);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम nfs4_मुक्त_createdata(काष्ठा nfs4_createdata *data)
अणु
	nfs4_label_मुक्त(data->label);
	kमुक्त(data);
पूर्ण

अटल पूर्णांक _nfs4_proc_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा page *page, अचिन्हित पूर्णांक len, काष्ठा iattr *sattr,
		काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs4_createdata *data;
	पूर्णांक status = -ENAMETOOLONG;

	अगर (len > NFS4_MAXPATHLEN)
		जाओ out;

	status = -ENOMEM;
	data = nfs4_alloc_createdata(dir, &dentry->d_name, sattr, NF4LNK);
	अगर (data == शून्य)
		जाओ out;

	data->msg.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SYMLINK];
	data->arg.u.symlink.pages = &page;
	data->arg.u.symlink.len = len;
	data->arg.label = label;
	
	status = nfs4_करो_create(dir, dentry, data);

	nfs4_मुक्त_createdata(data);
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा page *page, अचिन्हित पूर्णांक len, काष्ठा iattr *sattr)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	काष्ठा nfs4_label l, *label = शून्य;
	पूर्णांक err;

	label = nfs4_label_init_security(dir, dentry, sattr, &l);

	करो अणु
		err = _nfs4_proc_symlink(dir, dentry, page, len, sattr, label);
		trace_nfs4_symlink(dir, &dentry->d_name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);

	nfs4_label_release_security(label);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_proc_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा iattr *sattr, काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs4_createdata *data;
	पूर्णांक status = -ENOMEM;

	data = nfs4_alloc_createdata(dir, &dentry->d_name, sattr, NF4सूची);
	अगर (data == शून्य)
		जाओ out;

	data->arg.label = label;
	status = nfs4_करो_create(dir, dentry, data);

	nfs4_मुक्त_createdata(data);
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा iattr *sattr)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	काष्ठा nfs4_label l, *label = शून्य;
	पूर्णांक err;

	label = nfs4_label_init_security(dir, dentry, sattr, &l);

	अगर (!(server->attr_biपंचांगask[2] & FATTR4_WORD2_MODE_UMASK))
		sattr->ia_mode &= ~current_umask();
	करो अणु
		err = _nfs4_proc_सूची_गढ़ो(dir, dentry, sattr, label);
		trace_nfs4_सूची_गढ़ो(dir, &dentry->d_name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	nfs4_label_release_security(label);

	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_proc_सूची_पढ़ो(काष्ठा nfs_सूची_पढ़ो_arg *nr_arg,
			      काष्ठा nfs_सूची_पढ़ो_res *nr_res)
अणु
	काष्ठा inode		*dir = d_inode(nr_arg->dentry);
	काष्ठा nfs_server	*server = NFS_SERVER(dir);
	काष्ठा nfs4_सूची_पढ़ो_arg args = अणु
		.fh = NFS_FH(dir),
		.pages = nr_arg->pages,
		.pgbase = 0,
		.count = nr_arg->page_len,
		.plus = nr_arg->plus,
	पूर्ण;
	काष्ठा nfs4_सूची_पढ़ो_res res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_READसूची],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = nr_arg->cred,
	पूर्ण;
	पूर्णांक			status;

	dprपूर्णांकk("%s: dentry = %pd2, cookie = %llu\n", __func__,
		nr_arg->dentry, (अचिन्हित दीर्घ दीर्घ)nr_arg->cookie);
	अगर (!(server->caps & NFS_CAP_SECURITY_LABEL))
		args.biपंचांगask = server->attr_biपंचांगask_nl;
	अन्यथा
		args.biपंचांगask = server->attr_biपंचांगask;

	nfs4_setup_सूची_पढ़ो(nr_arg->cookie, nr_arg->verf, nr_arg->dentry, &args);
	res.pgbase = args.pgbase;
	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args,
			&res.seq_res, 0);
	अगर (status >= 0) अणु
		स_नकल(nr_res->verf, res.verअगरier.data, NFS4_VERIFIER_SIZE);
		status += args.pgbase;
	पूर्ण

	nfs_invalidate_aसमय(dir);

	dprपूर्णांकk("%s: returns %d\n", __func__, status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_सूची_पढ़ो(काष्ठा nfs_सूची_पढ़ो_arg *arg,
			     काष्ठा nfs_सूची_पढ़ो_res *res)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_सूची_पढ़ो(arg, res);
		trace_nfs4_सूची_पढ़ो(d_inode(arg->dentry), err);
		err = nfs4_handle_exception(NFS_SERVER(d_inode(arg->dentry)),
					    err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_proc_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा iattr *sattr, काष्ठा nfs4_label *label, dev_t rdev)
अणु
	काष्ठा nfs4_createdata *data;
	पूर्णांक mode = sattr->ia_mode;
	पूर्णांक status = -ENOMEM;

	data = nfs4_alloc_createdata(dir, &dentry->d_name, sattr, NF4SOCK);
	अगर (data == शून्य)
		जाओ out;

	अगर (S_ISFIFO(mode))
		data->arg.ftype = NF4FIFO;
	अन्यथा अगर (S_ISBLK(mode)) अणु
		data->arg.ftype = NF4BLK;
		data->arg.u.device.specdata1 = MAJOR(rdev);
		data->arg.u.device.specdata2 = MINOR(rdev);
	पूर्ण
	अन्यथा अगर (S_ISCHR(mode)) अणु
		data->arg.ftype = NF4CHR;
		data->arg.u.device.specdata1 = MAJOR(rdev);
		data->arg.u.device.specdata2 = MINOR(rdev);
	पूर्ण अन्यथा अगर (!S_ISSOCK(mode)) अणु
		status = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	data->arg.label = label;
	status = nfs4_करो_create(dir, dentry, data);
out_मुक्त:
	nfs4_मुक्त_createdata(data);
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा iattr *sattr, dev_t rdev)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	काष्ठा nfs4_label l, *label = शून्य;
	पूर्णांक err;

	label = nfs4_label_init_security(dir, dentry, sattr, &l);

	अगर (!(server->attr_biपंचांगask[2] & FATTR4_WORD2_MODE_UMASK))
		sattr->ia_mode &= ~current_umask();
	करो अणु
		err = _nfs4_proc_mknod(dir, dentry, sattr, label, rdev);
		trace_nfs4_mknod(dir, &dentry->d_name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);

	nfs4_label_release_security(label);

	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_proc_statfs(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		 काष्ठा nfs_fsstat *fsstat)
अणु
	काष्ठा nfs4_statfs_arg args = अणु
		.fh = fhandle,
		.biपंचांगask = server->attr_biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_statfs_res res = अणु
		.fsstat = fsstat,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_STATFS],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;

	nfs_fattr_init(fsstat->fattr);
	वापस  nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
पूर्ण

अटल पूर्णांक nfs4_proc_statfs(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle, काष्ठा nfs_fsstat *fsstat)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = nfs4_handle_exception(server,
				_nfs4_proc_statfs(server, fhandle, fsstat),
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_करो_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_fsinfo *fsinfo)
अणु
	काष्ठा nfs4_fsinfo_arg args = अणु
		.fh = fhandle,
		.biपंचांगask = server->attr_biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_fsinfo_res res = अणु
		.fsinfo = fsinfo,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_FSINFO],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;

	वापस nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
पूर्ण

अटल पूर्णांक nfs4_करो_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle, काष्ठा nfs_fsinfo *fsinfo)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs4_करो_fsinfo(server, fhandle, fsinfo);
		trace_nfs4_fsinfo(server, fhandle, fsinfo->fattr, err);
		अगर (err == 0) अणु
			nfs4_set_lease_period(server->nfs_client, fsinfo->lease_समय * HZ);
			अवरोध;
		पूर्ण
		err = nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक nfs4_proc_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle, काष्ठा nfs_fsinfo *fsinfo)
अणु
	पूर्णांक error;

	nfs_fattr_init(fsinfo->fattr);
	error = nfs4_करो_fsinfo(server, fhandle, fsinfo);
	अगर (error == 0) अणु
		/* block layout checks this! */
		server->pnfs_blksize = fsinfo->blksize;
		set_pnfs_layoutdriver(server, fhandle, fsinfo);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक _nfs4_proc_pathconf(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_pathconf *pathconf)
अणु
	काष्ठा nfs4_pathconf_arg args = अणु
		.fh = fhandle,
		.biपंचांगask = server->attr_biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_pathconf_res res = अणु
		.pathconf = pathconf,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_PATHCONF],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;

	/* None of the pathconf attributes are mandatory to implement */
	अगर ((args.biपंचांगask[0] & nfs4_pathconf_biपंचांगap[0]) == 0) अणु
		स_रखो(pathconf, 0, माप(*pathconf));
		वापस 0;
	पूर्ण

	nfs_fattr_init(pathconf->fattr);
	वापस nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
पूर्ण

अटल पूर्णांक nfs4_proc_pathconf(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_pathconf *pathconf)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;

	करो अणु
		err = nfs4_handle_exception(server,
				_nfs4_proc_pathconf(server, fhandle, pathconf),
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

पूर्णांक nfs4_set_rw_stateid(nfs4_stateid *stateid,
		स्थिर काष्ठा nfs_खोलो_context *ctx,
		स्थिर काष्ठा nfs_lock_context *l_ctx,
		भ_शेषe_t भ_शेषe)
अणु
	वापस nfs4_select_rw_stateid(ctx->state, भ_शेषe, l_ctx, stateid, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_set_rw_stateid);

अटल bool nfs4_stateid_is_current(nfs4_stateid *stateid,
		स्थिर काष्ठा nfs_खोलो_context *ctx,
		स्थिर काष्ठा nfs_lock_context *l_ctx,
		भ_शेषe_t भ_शेषe)
अणु
	nfs4_stateid _current_stateid;

	/* If the current stateid represents a lost lock, then निकास */
	अगर (nfs4_set_rw_stateid(&_current_stateid, ctx, l_ctx, भ_शेषe) == -EIO)
		वापस true;
	वापस nfs4_stateid_match(stateid, &_current_stateid);
पूर्ण

अटल bool nfs4_error_stateid_expired(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल -NFS4ERR_DELEG_REVOKED:
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_BAD_STATEID:
	हाल -NFS4ERR_STALE_STATEID:
	हाल -NFS4ERR_OLD_STATEID:
	हाल -NFS4ERR_OPENMODE:
	हाल -NFS4ERR_EXPIRED:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक nfs4_पढ़ो_करोne_cb(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(hdr->inode);

	trace_nfs4_पढ़ो(hdr, task->tk_status);
	अगर (task->tk_status < 0) अणु
		काष्ठा nfs4_exception exception = अणु
			.inode = hdr->inode,
			.state = hdr->args.context->state,
			.stateid = &hdr->args.stateid,
		पूर्ण;
		task->tk_status = nfs4_async_handle_exception(task,
				server, task->tk_status, &exception);
		अगर (exception.retry) अणु
			rpc_restart_call_prepare(task);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	अगर (task->tk_status > 0)
		renew_lease(server, hdr->बारtamp);
	वापस 0;
पूर्ण

अटल bool nfs4_पढ़ो_stateid_changed(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_args *args)
अणु

	अगर (!nfs4_error_stateid_expired(task->tk_status) ||
		nfs4_stateid_is_current(&args->stateid,
				args->context,
				args->lock_context,
				FMODE_READ))
		वापस false;
	rpc_restart_call_prepare(task);
	वापस true;
पूर्ण

अटल bool nfs4_पढ़ो_plus_not_supported(काष्ठा rpc_task *task,
					 काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(hdr->inode);
	काष्ठा rpc_message *msg = &task->tk_msg;

	अगर (msg->rpc_proc == &nfs4_procedures[NFSPROC4_CLNT_READ_PLUS] &&
	    server->caps & NFS_CAP_READ_PLUS && task->tk_status == -ENOTSUPP) अणु
		server->caps &= ~NFS_CAP_READ_PLUS;
		msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_READ];
		rpc_restart_call_prepare(task);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक nfs4_पढ़ो_करोne(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	dprपूर्णांकk("--> %s\n", __func__);

	अगर (!nfs4_sequence_करोne(task, &hdr->res.seq_res))
		वापस -EAGAIN;
	अगर (nfs4_पढ़ो_stateid_changed(task, &hdr->args))
		वापस -EAGAIN;
	अगर (nfs4_पढ़ो_plus_not_supported(task, hdr))
		वापस -EAGAIN;
	अगर (task->tk_status > 0)
		nfs_invalidate_aसमय(hdr->inode);
	वापस hdr->pgio_करोne_cb ? hdr->pgio_करोne_cb(task, hdr) :
				    nfs4_पढ़ो_करोne_cb(task, hdr);
पूर्ण

#अगर defined CONFIG_NFS_V4_2 && defined CONFIG_NFS_V4_2_READ_PLUS
अटल व्योम nfs42_पढ़ो_plus_support(काष्ठा nfs_pgio_header *hdr,
				    काष्ठा rpc_message *msg)
अणु
	/* Note: We करोn't use READ_PLUS with pNFS yet */
	अगर (nfs_server_capable(hdr->inode, NFS_CAP_READ_PLUS) && !hdr->ds_clp)
		msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_READ_PLUS];
पूर्ण
#अन्यथा
अटल व्योम nfs42_पढ़ो_plus_support(काष्ठा nfs_pgio_header *hdr,
				    काष्ठा rpc_message *msg)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

अटल व्योम nfs4_proc_पढ़ो_setup(काष्ठा nfs_pgio_header *hdr,
				 काष्ठा rpc_message *msg)
अणु
	hdr->बारtamp   = jअगरfies;
	अगर (!hdr->pgio_करोne_cb)
		hdr->pgio_करोne_cb = nfs4_पढ़ो_करोne_cb;
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_READ];
	nfs42_पढ़ो_plus_support(hdr, msg);
	nfs4_init_sequence(&hdr->args.seq_args, &hdr->res.seq_res, 0, 0);
पूर्ण

अटल पूर्णांक nfs4_proc_pgio_rpc_prepare(काष्ठा rpc_task *task,
				      काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (nfs4_setup_sequence(NFS_SERVER(hdr->inode)->nfs_client,
			&hdr->args.seq_args,
			&hdr->res.seq_res,
			task))
		वापस 0;
	अगर (nfs4_set_rw_stateid(&hdr->args.stateid, hdr->args.context,
				hdr->args.lock_context,
				hdr->rw_mode) == -EIO)
		वापस -EIO;
	अगर (unlikely(test_bit(NFS_CONTEXT_BAD, &hdr->args.context->flags)))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_ग_लिखो_करोne_cb(काष्ठा rpc_task *task,
			      काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा inode *inode = hdr->inode;

	trace_nfs4_ग_लिखो(hdr, task->tk_status);
	अगर (task->tk_status < 0) अणु
		काष्ठा nfs4_exception exception = अणु
			.inode = hdr->inode,
			.state = hdr->args.context->state,
			.stateid = &hdr->args.stateid,
		पूर्ण;
		task->tk_status = nfs4_async_handle_exception(task,
				NFS_SERVER(inode), task->tk_status,
				&exception);
		अगर (exception.retry) अणु
			rpc_restart_call_prepare(task);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	अगर (task->tk_status >= 0) अणु
		renew_lease(NFS_SERVER(inode), hdr->बारtamp);
		nfs_ग_लिखोback_update_inode(hdr);
	पूर्ण
	वापस 0;
पूर्ण

अटल bool nfs4_ग_लिखो_stateid_changed(काष्ठा rpc_task *task,
		काष्ठा nfs_pgio_args *args)
अणु

	अगर (!nfs4_error_stateid_expired(task->tk_status) ||
		nfs4_stateid_is_current(&args->stateid,
				args->context,
				args->lock_context,
				FMODE_WRITE))
		वापस false;
	rpc_restart_call_prepare(task);
	वापस true;
पूर्ण

अटल पूर्णांक nfs4_ग_लिखो_करोne(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (!nfs4_sequence_करोne(task, &hdr->res.seq_res))
		वापस -EAGAIN;
	अगर (nfs4_ग_लिखो_stateid_changed(task, &hdr->args))
		वापस -EAGAIN;
	वापस hdr->pgio_करोne_cb ? hdr->pgio_करोne_cb(task, hdr) :
		nfs4_ग_लिखो_करोne_cb(task, hdr);
पूर्ण

अटल
bool nfs4_ग_लिखो_need_cache_consistency_data(काष्ठा nfs_pgio_header *hdr)
अणु
	/* Don't request attributes क्रम pNFS or O_सूचीECT ग_लिखोs */
	अगर (hdr->ds_clp != शून्य || hdr->dreq != शून्य)
		वापस false;
	/* Otherwise, request attributes अगर and only अगर we करोn't hold
	 * a delegation
	 */
	वापस nfs4_have_delegation(hdr->inode, FMODE_READ) == 0;
पूर्ण

अटल व्योम nfs4_biपंचांगask_set(__u32 biपंचांगask[NFS4_BITMASK_SZ], स्थिर __u32 *src,
			     काष्ठा inode *inode, काष्ठा nfs_server *server,
			     काष्ठा nfs4_label *label)
अणु
	अचिन्हित दीर्घ cache_validity = READ_ONCE(NFS_I(inode)->cache_validity);
	अचिन्हित पूर्णांक i;

	स_नकल(biपंचांगask, src, माप(*biपंचांगask) * NFS4_BITMASK_SZ);

	अगर (cache_validity & NFS_INO_INVALID_CHANGE)
		biपंचांगask[0] |= FATTR4_WORD0_CHANGE;
	अगर (cache_validity & NFS_INO_INVALID_ATIME)
		biपंचांगask[1] |= FATTR4_WORD1_TIME_ACCESS;
	अगर (cache_validity & NFS_INO_INVALID_MODE)
		biपंचांगask[1] |= FATTR4_WORD1_MODE;
	अगर (cache_validity & NFS_INO_INVALID_OTHER)
		biपंचांगask[1] |= FATTR4_WORD1_OWNER | FATTR4_WORD1_OWNER_GROUP;
	अगर (cache_validity & NFS_INO_INVALID_NLINK)
		biपंचांगask[1] |= FATTR4_WORD1_NUMLINKS;
	अगर (label && label->len && cache_validity & NFS_INO_INVALID_LABEL)
		biपंचांगask[2] |= FATTR4_WORD2_SECURITY_LABEL;
	अगर (cache_validity & NFS_INO_INVALID_CTIME)
		biपंचांगask[1] |= FATTR4_WORD1_TIME_METADATA;
	अगर (cache_validity & NFS_INO_INVALID_MTIME)
		biपंचांगask[1] |= FATTR4_WORD1_TIME_MODIFY;
	अगर (cache_validity & NFS_INO_INVALID_BLOCKS)
		biपंचांगask[1] |= FATTR4_WORD1_SPACE_USED;

	अगर (cache_validity & NFS_INO_INVALID_SIZE)
		biपंचांगask[0] |= FATTR4_WORD0_SIZE;

	क्रम (i = 0; i < NFS4_BITMASK_SZ; i++)
		biपंचांगask[i] &= server->attr_biपंचांगask[i];
पूर्ण

अटल व्योम nfs4_proc_ग_लिखो_setup(काष्ठा nfs_pgio_header *hdr,
				  काष्ठा rpc_message *msg,
				  काष्ठा rpc_clnt **clnt)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(hdr->inode);

	अगर (!nfs4_ग_लिखो_need_cache_consistency_data(hdr)) अणु
		hdr->args.biपंचांगask = शून्य;
		hdr->res.fattr = शून्य;
	पूर्ण अन्यथा अणु
		nfs4_biपंचांगask_set(hdr->args.biपंचांगask_store,
				 server->cache_consistency_biपंचांगask,
				 hdr->inode, server, शून्य);
		hdr->args.biपंचांगask = hdr->args.biपंचांगask_store;
	पूर्ण

	अगर (!hdr->pgio_करोne_cb)
		hdr->pgio_करोne_cb = nfs4_ग_लिखो_करोne_cb;
	hdr->res.server = server;
	hdr->बारtamp   = jअगरfies;

	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_WRITE];
	nfs4_init_sequence(&hdr->args.seq_args, &hdr->res.seq_res, 0, 0);
	nfs4_state_protect_ग_लिखो(server->nfs_client, clnt, msg, hdr);
पूर्ण

अटल व्योम nfs4_proc_commit_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data)
अणु
	nfs4_setup_sequence(NFS_SERVER(data->inode)->nfs_client,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
पूर्ण

अटल पूर्णांक nfs4_commit_करोne_cb(काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data)
अणु
	काष्ठा inode *inode = data->inode;

	trace_nfs4_commit(data, task->tk_status);
	अगर (nfs4_async_handle_error(task, NFS_SERVER(inode),
				    शून्य, शून्य) == -EAGAIN) अणु
		rpc_restart_call_prepare(task);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_commit_करोne(काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data)
अणु
	अगर (!nfs4_sequence_करोne(task, &data->res.seq_res))
		वापस -EAGAIN;
	वापस data->commit_करोne_cb(task, data);
पूर्ण

अटल व्योम nfs4_proc_commit_setup(काष्ठा nfs_commit_data *data, काष्ठा rpc_message *msg,
				   काष्ठा rpc_clnt **clnt)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(data->inode);

	अगर (data->commit_करोne_cb == शून्य)
		data->commit_करोne_cb = nfs4_commit_करोne_cb;
	data->res.server = server;
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_COMMIT];
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 1, 0);
	nfs4_state_protect(server->nfs_client, NFS_SP4_MACH_CRED_COMMIT, clnt, msg);
पूर्ण

अटल पूर्णांक _nfs4_proc_commit(काष्ठा file *dst, काष्ठा nfs_commitargs *args,
				काष्ठा nfs_commitres *res)
अणु
	काष्ठा inode *dst_inode = file_inode(dst);
	काष्ठा nfs_server *server = NFS_SERVER(dst_inode);
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_COMMIT],
		.rpc_argp = args,
		.rpc_resp = res,
	पूर्ण;

	args->fh = NFS_FH(dst_inode);
	वापस nfs4_call_sync(server->client, server, &msg,
			&args->seq_args, &res->seq_res, 1);
पूर्ण

पूर्णांक nfs4_proc_commit(काष्ठा file *dst, __u64 offset, __u32 count, काष्ठा nfs_commitres *res)
अणु
	काष्ठा nfs_commitargs args = अणु
		.offset = offset,
		.count = count,
	पूर्ण;
	काष्ठा nfs_server *dst_server = NFS_SERVER(file_inode(dst));
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक status;

	करो अणु
		status = _nfs4_proc_commit(dst, &args, res);
		status = nfs4_handle_exception(dst_server, status, &exception);
	पूर्ण जबतक (exception.retry);

	वापस status;
पूर्ण

काष्ठा nfs4_renewdata अणु
	काष्ठा nfs_client	*client;
	अचिन्हित दीर्घ		बारtamp;
पूर्ण;

/*
 * nfs4_proc_async_renew(): This is not one of the nfs_rpc_ops; it is a special
 * standalone procedure क्रम queueing an asynchronous RENEW.
 */
अटल व्योम nfs4_renew_release(व्योम *calldata)
अणु
	काष्ठा nfs4_renewdata *data = calldata;
	काष्ठा nfs_client *clp = data->client;

	अगर (refcount_पढ़ो(&clp->cl_count) > 1)
		nfs4_schedule_state_renewal(clp);
	nfs_put_client(clp);
	kमुक्त(data);
पूर्ण

अटल व्योम nfs4_renew_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_renewdata *data = calldata;
	काष्ठा nfs_client *clp = data->client;
	अचिन्हित दीर्घ बारtamp = data->बारtamp;

	trace_nfs4_renew_async(clp, task->tk_status);
	चयन (task->tk_status) अणु
	हाल 0:
		अवरोध;
	हाल -NFS4ERR_LEASE_MOVED:
		nfs4_schedule_lease_moved_recovery(clp);
		अवरोध;
	शेष:
		/* Unless we're shutting करोwn, schedule state recovery! */
		अगर (test_bit(NFS_CS_RENEWD, &clp->cl_res_state) == 0)
			वापस;
		अगर (task->tk_status != NFS4ERR_CB_PATH_DOWN) अणु
			nfs4_schedule_lease_recovery(clp);
			वापस;
		पूर्ण
		nfs4_schedule_path_करोwn_recovery(clp);
	पूर्ण
	करो_renew_lease(clp, बारtamp);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_renew_ops = अणु
	.rpc_call_करोne = nfs4_renew_करोne,
	.rpc_release = nfs4_renew_release,
पूर्ण;

अटल पूर्णांक nfs4_proc_async_renew(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred, अचिन्हित renew_flags)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_RENEW],
		.rpc_argp	= clp,
		.rpc_cred	= cred,
	पूर्ण;
	काष्ठा nfs4_renewdata *data;

	अगर (renew_flags == 0)
		वापस 0;
	अगर (!refcount_inc_not_zero(&clp->cl_count))
		वापस -EIO;
	data = kदो_स्मृति(माप(*data), GFP_NOFS);
	अगर (data == शून्य) अणु
		nfs_put_client(clp);
		वापस -ENOMEM;
	पूर्ण
	data->client = clp;
	data->बारtamp = jअगरfies;
	वापस rpc_call_async(clp->cl_rpcclient, &msg, RPC_TASK_TIMEOUT,
			&nfs4_renew_ops, data);
पूर्ण

अटल पूर्णांक nfs4_proc_renew(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_RENEW],
		.rpc_argp	= clp,
		.rpc_cred	= cred,
	पूर्ण;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक status;

	status = rpc_call_sync(clp->cl_rpcclient, &msg, RPC_TASK_TIMEOUT);
	अगर (status < 0)
		वापस status;
	करो_renew_lease(clp, now);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nfs4_server_supports_acls(काष्ठा nfs_server *server)
अणु
	वापस server->caps & NFS_CAP_ACLS;
पूर्ण

/* Assuming that XATTR_SIZE_MAX is a multiple of PAGE_SIZE, and that
 * it's OK to put माप(व्योम) * (XATTR_SIZE_MAX/PAGE_SIZE) bytes on
 * the stack.
 */
#घोषणा NFS4ACL_MAXPAGES DIV_ROUND_UP(XATTR_SIZE_MAX, PAGE_SIZE)

पूर्णांक nfs4_buf_to_pages_noslab(स्थिर व्योम *buf, माप_प्रकार buflen,
		काष्ठा page **pages)
अणु
	काष्ठा page *newpage, **spages;
	पूर्णांक rc = 0;
	माप_प्रकार len;
	spages = pages;

	करो अणु
		len = min_t(माप_प्रकार, PAGE_SIZE, buflen);
		newpage = alloc_page(GFP_KERNEL);

		अगर (newpage == शून्य)
			जाओ unwind;
		स_नकल(page_address(newpage), buf, len);
		buf += len;
		buflen -= len;
		*pages++ = newpage;
		rc++;
	पूर्ण जबतक (buflen != 0);

	वापस rc;

unwind:
	क्रम(; rc > 0; rc--)
		__मुक्त_page(spages[rc-1]);
	वापस -ENOMEM;
पूर्ण

काष्ठा nfs4_cached_acl अणु
	पूर्णांक cached;
	माप_प्रकार len;
	अक्षर data[];
पूर्ण;

अटल व्योम nfs4_set_cached_acl(काष्ठा inode *inode, काष्ठा nfs4_cached_acl *acl)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	spin_lock(&inode->i_lock);
	kमुक्त(nfsi->nfs4_acl);
	nfsi->nfs4_acl = acl;
	spin_unlock(&inode->i_lock);
पूर्ण

अटल व्योम nfs4_zap_acl_attr(काष्ठा inode *inode)
अणु
	nfs4_set_cached_acl(inode, शून्य);
पूर्ण

अटल अंतरभूत sमाप_प्रकार nfs4_पढ़ो_cached_acl(काष्ठा inode *inode, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs4_cached_acl *acl;
	पूर्णांक ret = -ENOENT;

	spin_lock(&inode->i_lock);
	acl = nfsi->nfs4_acl;
	अगर (acl == शून्य)
		जाओ out;
	अगर (buf == शून्य) /* user is just asking क्रम length */
		जाओ out_len;
	अगर (acl->cached == 0)
		जाओ out;
	ret = -दुस्फल; /* see getxattr(2) man page */
	अगर (acl->len > buflen)
		जाओ out;
	स_नकल(buf, acl->data, acl->len);
out_len:
	ret = acl->len;
out:
	spin_unlock(&inode->i_lock);
	वापस ret;
पूर्ण

अटल व्योम nfs4_ग_लिखो_cached_acl(काष्ठा inode *inode, काष्ठा page **pages, माप_प्रकार pgbase, माप_प्रकार acl_len)
अणु
	काष्ठा nfs4_cached_acl *acl;
	माप_प्रकार buflen = माप(*acl) + acl_len;

	अगर (buflen <= PAGE_SIZE) अणु
		acl = kदो_स्मृति(buflen, GFP_KERNEL);
		अगर (acl == शून्य)
			जाओ out;
		acl->cached = 1;
		_copy_from_pages(acl->data, pages, pgbase, acl_len);
	पूर्ण अन्यथा अणु
		acl = kदो_स्मृति(माप(*acl), GFP_KERNEL);
		अगर (acl == शून्य)
			जाओ out;
		acl->cached = 0;
	पूर्ण
	acl->len = acl_len;
out:
	nfs4_set_cached_acl(inode, acl);
पूर्ण

/*
 * The getxattr API वापसs the required buffer length when called with a
 * शून्य buf. The NFSv4 acl tool then calls getxattr again after allocating
 * the required buf.  On a शून्य buf, we send a page of data to the server
 * guessing that the ACL request can be serviced by a page. If so, we cache
 * up to the page of ACL data, and the 2nd call to getxattr is serviced by
 * the cache. If not so, we throw away the page, and cache the required
 * length. The next getxattr call will then produce another round trip to
 * the server, this समय with the input buf of the required size.
 */
अटल sमाप_प्रकार __nfs4_get_acl_uncached(काष्ठा inode *inode, व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा page **pages;
	काष्ठा nfs_getaclargs args = अणु
		.fh = NFS_FH(inode),
		.acl_len = buflen,
	पूर्ण;
	काष्ठा nfs_getaclres res = अणु
		.acl_len = buflen,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_GETACL],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	अचिन्हित पूर्णांक npages;
	पूर्णांक ret = -ENOMEM, i;
	काष्ठा nfs_server *server = NFS_SERVER(inode);

	अगर (buflen == 0)
		buflen = server->rsize;

	npages = DIV_ROUND_UP(buflen, PAGE_SIZE) + 1;
	pages = kदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_NOFS);
	अगर (!pages)
		वापस -ENOMEM;

	args.acl_pages = pages;

	क्रम (i = 0; i < npages; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL);
		अगर (!pages[i])
			जाओ out_मुक्त;
	पूर्ण

	/* क्रम decoding across pages */
	res.acl_scratch = alloc_page(GFP_KERNEL);
	अगर (!res.acl_scratch)
		जाओ out_मुक्त;

	args.acl_len = npages * PAGE_SIZE;

	dprपूर्णांकk("%s  buf %p buflen %zu npages %d args.acl_len %zu\n",
		__func__, buf, buflen, npages, args.acl_len);
	ret = nfs4_call_sync(NFS_SERVER(inode)->client, NFS_SERVER(inode),
			     &msg, &args.seq_args, &res.seq_res, 0);
	अगर (ret)
		जाओ out_मुक्त;

	/* Handle the हाल where the passed-in buffer is too लघु */
	अगर (res.acl_flags & NFS4_ACL_TRUNC) अणु
		/* Did the user only issue a request क्रम the acl length? */
		अगर (buf == शून्य)
			जाओ out_ok;
		ret = -दुस्फल;
		जाओ out_मुक्त;
	पूर्ण
	nfs4_ग_लिखो_cached_acl(inode, pages, res.acl_data_offset, res.acl_len);
	अगर (buf) अणु
		अगर (res.acl_len > buflen) अणु
			ret = -दुस्फल;
			जाओ out_मुक्त;
		पूर्ण
		_copy_from_pages(buf, pages, res.acl_data_offset, res.acl_len);
	पूर्ण
out_ok:
	ret = res.acl_len;
out_मुक्त:
	क्रम (i = 0; i < npages; i++)
		अगर (pages[i])
			__मुक्त_page(pages[i]);
	अगर (res.acl_scratch)
		__मुक्त_page(res.acl_scratch);
	kमुक्त(pages);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार nfs4_get_acl_uncached(काष्ठा inode *inode, व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	sमाप_प्रकार ret;
	करो अणु
		ret = __nfs4_get_acl_uncached(inode, buf, buflen);
		trace_nfs4_get_acl(inode, ret);
		अगर (ret >= 0)
			अवरोध;
		ret = nfs4_handle_exception(NFS_SERVER(inode), ret, &exception);
	पूर्ण जबतक (exception.retry);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार nfs4_proc_get_acl(काष्ठा inode *inode, व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	पूर्णांक ret;

	अगर (!nfs4_server_supports_acls(server))
		वापस -EOPNOTSUPP;
	ret = nfs_revalidate_inode(inode, NFS_INO_INVALID_CHANGE);
	अगर (ret < 0)
		वापस ret;
	अगर (NFS_I(inode)->cache_validity & NFS_INO_INVALID_ACL)
		nfs_zap_acl_cache(inode);
	ret = nfs4_पढ़ो_cached_acl(inode, buf, buflen);
	अगर (ret != -ENOENT)
		/* -ENOENT is वापसed अगर there is no ACL or अगर there is an ACL
		 * but no cached acl data, just the acl length */
		वापस ret;
	वापस nfs4_get_acl_uncached(inode, buf, buflen);
पूर्ण

अटल पूर्णांक __nfs4_proc_set_acl(काष्ठा inode *inode, स्थिर व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा page *pages[NFS4ACL_MAXPAGES];
	काष्ठा nfs_setaclargs arg = अणु
		.fh		= NFS_FH(inode),
		.acl_pages	= pages,
		.acl_len	= buflen,
	पूर्ण;
	काष्ठा nfs_setaclres res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_SETACL],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	अचिन्हित पूर्णांक npages = DIV_ROUND_UP(buflen, PAGE_SIZE);
	पूर्णांक ret, i;

	/* You can't हटाओ प्रणाली.nfs4_acl: */
	अगर (buflen == 0)
		वापस -EINVAL;
	अगर (!nfs4_server_supports_acls(server))
		वापस -EOPNOTSUPP;
	अगर (npages > ARRAY_SIZE(pages))
		वापस -दुस्फल;
	i = nfs4_buf_to_pages_noslab(buf, buflen, arg.acl_pages);
	अगर (i < 0)
		वापस i;
	nfs4_inode_make_ग_लिखोable(inode);
	ret = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);

	/*
	 * Free each page after tx, so the only ref left is
	 * held by the network stack
	 */
	क्रम (; i > 0; i--)
		put_page(pages[i-1]);

	/*
	 * Acl update can result in inode attribute update.
	 * so mark the attribute cache invalid.
	 */
	spin_lock(&inode->i_lock);
	nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE |
					     NFS_INO_INVALID_CTIME |
					     NFS_INO_REVAL_FORCED);
	spin_unlock(&inode->i_lock);
	nfs_access_zap_cache(inode);
	nfs_zap_acl_cache(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_proc_set_acl(काष्ठा inode *inode, स्थिर व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;
	करो अणु
		err = __nfs4_proc_set_acl(inode, buf, buflen);
		trace_nfs4_set_acl(inode, err);
		अगर (err == -NFS4ERR_BADOWNER || err == -NFS4ERR_BADNAME) अणु
			/*
			 * no need to retry since the kernel
			 * isn't involved in encoding the ACEs.
			 */
			err = -EINVAL;
			अवरोध;
		पूर्ण
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
अटल पूर्णांक _nfs4_get_security_label(काष्ठा inode *inode, व्योम *buf,
					माप_प्रकार buflen)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_fattr fattr;
	काष्ठा nfs4_label label = अणु0, 0, buflen, bufपूर्ण;

	u32 biपंचांगask[3] = अणु 0, 0, FATTR4_WORD2_SECURITY_LABEL पूर्ण;
	काष्ठा nfs4_getattr_arg arg = अणु
		.fh		= NFS_FH(inode),
		.biपंचांगask	= biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_getattr_res res = अणु
		.fattr		= &fattr,
		.label		= &label,
		.server		= server,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_GETATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक ret;

	nfs_fattr_init(&fattr);

	ret = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 0);
	अगर (ret)
		वापस ret;
	अगर (!(fattr.valid & NFS_ATTR_FATTR_V4_SECURITY_LABEL))
		वापस -ENOENT;
	वापस label.len;
पूर्ण

अटल पूर्णांक nfs4_get_security_label(काष्ठा inode *inode, व्योम *buf,
					माप_प्रकार buflen)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;

	अगर (!nfs_server_capable(inode, NFS_CAP_SECURITY_LABEL))
		वापस -EOPNOTSUPP;

	करो अणु
		err = _nfs4_get_security_label(inode, buf, buflen);
		trace_nfs4_get_security_label(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_करो_set_security_label(काष्ठा inode *inode,
		काष्ठा nfs4_label *ilabel,
		काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_label *olabel)
अणु

	काष्ठा iattr sattr = अणु0पूर्ण;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	स्थिर u32 biपंचांगask[3] = अणु 0, 0, FATTR4_WORD2_SECURITY_LABEL पूर्ण;
	काष्ठा nfs_setattrargs arg = अणु
		.fh		= NFS_FH(inode),
		.iap		= &sattr,
		.server		= server,
		.biपंचांगask	= biपंचांगask,
		.label		= ilabel,
	पूर्ण;
	काष्ठा nfs_setattrres res = अणु
		.fattr		= fattr,
		.label		= olabel,
		.server		= server,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_SETATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक status;

	nfs4_stateid_copy(&arg.stateid, &zero_stateid);

	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	अगर (status)
		dprपूर्णांकk("%s failed: %d\n", __func__, status);

	वापस status;
पूर्ण

अटल पूर्णांक nfs4_करो_set_security_label(काष्ठा inode *inode,
		काष्ठा nfs4_label *ilabel,
		काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_label *olabel)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs4_करो_set_security_label(inode, ilabel,
				fattr, olabel);
		trace_nfs4_set_security_label(inode, err);
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक
nfs4_set_security_label(काष्ठा inode *inode, स्थिर व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs4_label ilabel, *olabel = शून्य;
	काष्ठा nfs_fattr fattr;
	पूर्णांक status;

	अगर (!nfs_server_capable(inode, NFS_CAP_SECURITY_LABEL))
		वापस -EOPNOTSUPP;

	nfs_fattr_init(&fattr);

	ilabel.pi = 0;
	ilabel.lfs = 0;
	ilabel.label = (अक्षर *)buf;
	ilabel.len = buflen;

	olabel = nfs4_label_alloc(NFS_SERVER(inode), GFP_KERNEL);
	अगर (IS_ERR(olabel)) अणु
		status = -PTR_ERR(olabel);
		जाओ out;
	पूर्ण

	status = nfs4_करो_set_security_label(inode, &ilabel, &fattr, olabel);
	अगर (status == 0)
		nfs_setsecurity(inode, &fattr, olabel);

	nfs4_label_मुक्त(olabel);
out:
	वापस status;
पूर्ण
#पूर्ण_अगर	/* CONFIG_NFS_V4_SECURITY_LABEL */


अटल व्योम nfs4_init_boot_verअगरier(स्थिर काष्ठा nfs_client *clp,
				    nfs4_verअगरier *bootverf)
अणु
	__be32 verf[2];

	अगर (test_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state)) अणु
		/* An impossible बारtamp guarantees this value
		 * will never match a generated boot समय. */
		verf[0] = cpu_to_be32(U32_MAX);
		verf[1] = cpu_to_be32(U32_MAX);
	पूर्ण अन्यथा अणु
		काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
		u64 ns = kसमय_प्रकारo_ns(nn->boot_समय);

		verf[0] = cpu_to_be32(ns >> 32);
		verf[1] = cpu_to_be32(ns);
	पूर्ण
	स_नकल(bootverf->data, verf, माप(bootverf->data));
पूर्ण

अटल माप_प्रकार
nfs4_get_uniquअगरier(काष्ठा nfs_client *clp, अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
	काष्ठा nfs_netns_client *nn_clp = nn->nfs_client;
	स्थिर अक्षर *id;

	buf[0] = '\0';

	अगर (nn_clp) अणु
		rcu_पढ़ो_lock();
		id = rcu_dereference(nn_clp->identअगरier);
		अगर (id)
			strscpy(buf, id, buflen);
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (nfs4_client_id_uniquअगरier[0] != '\0' && buf[0] == '\0')
		strscpy(buf, nfs4_client_id_uniquअगरier, buflen);

	वापस म_माप(buf);
पूर्ण

अटल पूर्णांक
nfs4_init_nonunअगरorm_client_string(काष्ठा nfs_client *clp)
अणु
	अक्षर buf[NFS4_CLIENT_ID_UNIQ_LEN];
	माप_प्रकार buflen;
	माप_प्रकार len;
	अक्षर *str;

	अगर (clp->cl_owner_id != शून्य)
		वापस 0;

	rcu_पढ़ो_lock();
	len = 14 +
		म_माप(clp->cl_rpcclient->cl_nodename) +
		1 +
		म_माप(rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_ADDR)) +
		1;
	rcu_पढ़ो_unlock();

	buflen = nfs4_get_uniquअगरier(clp, buf, माप(buf));
	अगर (buflen)
		len += buflen + 1;

	अगर (len > NFS4_OPAQUE_LIMIT + 1)
		वापस -EINVAL;

	/*
	 * Since this string is allocated at mount समय, and held until the
	 * nfs_client is destroyed, we can use GFP_KERNEL here w/o worrying
	 * about a memory-reclaim deadlock.
	 */
	str = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	अगर (buflen)
		scnम_लिखो(str, len, "Linux NFSv4.0 %s/%s/%s",
			  clp->cl_rpcclient->cl_nodename, buf,
			  rpc_peeraddr2str(clp->cl_rpcclient,
					   RPC_DISPLAY_ADDR));
	अन्यथा
		scnम_लिखो(str, len, "Linux NFSv4.0 %s/%s",
			  clp->cl_rpcclient->cl_nodename,
			  rpc_peeraddr2str(clp->cl_rpcclient,
					   RPC_DISPLAY_ADDR));
	rcu_पढ़ो_unlock();

	clp->cl_owner_id = str;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfs4_init_unअगरorm_client_string(काष्ठा nfs_client *clp)
अणु
	अक्षर buf[NFS4_CLIENT_ID_UNIQ_LEN];
	माप_प्रकार buflen;
	माप_प्रकार len;
	अक्षर *str;

	अगर (clp->cl_owner_id != शून्य)
		वापस 0;

	len = 10 + 10 + 1 + 10 + 1 +
		म_माप(clp->cl_rpcclient->cl_nodename) + 1;

	buflen = nfs4_get_uniquअगरier(clp, buf, माप(buf));
	अगर (buflen)
		len += buflen + 1;

	अगर (len > NFS4_OPAQUE_LIMIT + 1)
		वापस -EINVAL;

	/*
	 * Since this string is allocated at mount समय, and held until the
	 * nfs_client is destroyed, we can use GFP_KERNEL here w/o worrying
	 * about a memory-reclaim deadlock.
	 */
	str = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	अगर (buflen)
		scnम_लिखो(str, len, "Linux NFSv%u.%u %s/%s",
			  clp->rpc_ops->version, clp->cl_minorversion,
			  buf, clp->cl_rpcclient->cl_nodename);
	अन्यथा
		scnम_लिखो(str, len, "Linux NFSv%u.%u %s",
			  clp->rpc_ops->version, clp->cl_minorversion,
			  clp->cl_rpcclient->cl_nodename);
	clp->cl_owner_id = str;
	वापस 0;
पूर्ण

/*
 * nfs4_callback_up_net() starts only "tcp" and "tcp6" callback
 * services.  Advertise one based on the address family of the
 * clientaddr.
 */
अटल अचिन्हित पूर्णांक
nfs4_init_callback_netid(स्थिर काष्ठा nfs_client *clp, अक्षर *buf, माप_प्रकार len)
अणु
	अगर (म_अक्षर(clp->cl_ipaddr, ':') != शून्य)
		वापस scnम_लिखो(buf, len, "tcp6");
	अन्यथा
		वापस scnम_लिखो(buf, len, "tcp");
पूर्ण

अटल व्योम nfs4_setclientid_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_setclientid *sc = calldata;

	अगर (task->tk_status == 0)
		sc->sc_cred = get_rpccred(task->tk_rqstp->rq_cred);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_setclientid_ops = अणु
	.rpc_call_करोne = nfs4_setclientid_करोne,
पूर्ण;

/**
 * nfs4_proc_setclientid - Negotiate client ID
 * @clp: state data काष्ठाure
 * @program: RPC program क्रम NFSv4 callback service
 * @port: IP port number क्रम NFS4 callback service
 * @cred: credential to use क्रम this call
 * @res: where to place the result
 *
 * Returns zero, a negative त्रुटि_सं, or a negative NFS4ERR status code.
 */
पूर्णांक nfs4_proc_setclientid(काष्ठा nfs_client *clp, u32 program,
		अचिन्हित लघु port, स्थिर काष्ठा cred *cred,
		काष्ठा nfs4_setclientid_res *res)
अणु
	nfs4_verअगरier sc_verअगरier;
	काष्ठा nfs4_setclientid setclientid = अणु
		.sc_verअगरier = &sc_verअगरier,
		.sc_prog = program,
		.sc_clnt = clp,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SETCLIENTID],
		.rpc_argp = &setclientid,
		.rpc_resp = res,
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs4_setclientid_ops,
		.callback_data = &setclientid,
		.flags = RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN,
	पूर्ण;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक status;

	/* nfs_client_id4 */
	nfs4_init_boot_verअगरier(clp, &sc_verअगरier);

	अगर (test_bit(NFS_CS_MIGRATION, &clp->cl_flags))
		status = nfs4_init_unअगरorm_client_string(clp);
	अन्यथा
		status = nfs4_init_nonunअगरorm_client_string(clp);

	अगर (status)
		जाओ out;

	/* cb_client4 */
	setclientid.sc_netid_len =
				nfs4_init_callback_netid(clp,
						setclientid.sc_netid,
						माप(setclientid.sc_netid));
	setclientid.sc_uaddr_len = scnम_लिखो(setclientid.sc_uaddr,
				माप(setclientid.sc_uaddr), "%s.%u.%u",
				clp->cl_ipaddr, port >> 8, port & 255);

	dprपूर्णांकk("NFS call  setclientid auth=%s, '%s'\n",
		clp->cl_rpcclient->cl_auth->au_ops->au_name,
		clp->cl_owner_id);

	status = nfs4_call_sync_custom(&task_setup_data);
	अगर (setclientid.sc_cred) अणु
		kमुक्त(clp->cl_acceptor);
		clp->cl_acceptor = rpcauth_stringअगरy_acceptor(setclientid.sc_cred);
		put_rpccred(setclientid.sc_cred);
	पूर्ण

	अगर (status == 0)
		करो_renew_lease(clp, now);
out:
	trace_nfs4_setclientid(clp, status);
	dprपूर्णांकk("NFS reply setclientid: %d\n", status);
	वापस status;
पूर्ण

/**
 * nfs4_proc_setclientid_confirm - Confirm client ID
 * @clp: state data काष्ठाure
 * @arg: result of a previous SETCLIENTID
 * @cred: credential to use क्रम this call
 *
 * Returns zero, a negative त्रुटि_सं, or a negative NFS4ERR status code.
 */
पूर्णांक nfs4_proc_setclientid_confirm(काष्ठा nfs_client *clp,
		काष्ठा nfs4_setclientid_res *arg,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SETCLIENTID_CONFIRM],
		.rpc_argp = arg,
		.rpc_cred = cred,
	पूर्ण;
	पूर्णांक status;

	dprपूर्णांकk("NFS call  setclientid_confirm auth=%s, (client ID %llx)\n",
		clp->cl_rpcclient->cl_auth->au_ops->au_name,
		clp->cl_clientid);
	status = rpc_call_sync(clp->cl_rpcclient, &msg,
			       RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN);
	trace_nfs4_setclientid_confirm(clp, status);
	dprपूर्णांकk("NFS reply setclientid_confirm: %d\n", status);
	वापस status;
पूर्ण

काष्ठा nfs4_delegवापसdata अणु
	काष्ठा nfs4_delegवापसargs args;
	काष्ठा nfs4_delegवापसres res;
	काष्ठा nfs_fh fh;
	nfs4_stateid stateid;
	अचिन्हित दीर्घ बारtamp;
	काष्ठा अणु
		काष्ठा nfs4_layoutवापस_args arg;
		काष्ठा nfs4_layoutवापस_res res;
		काष्ठा nfs4_xdr_opaque_data ld_निजी;
		u32 roc_barrier;
		bool roc;
	पूर्ण lr;
	काष्ठा nfs_fattr fattr;
	पूर्णांक rpc_status;
	काष्ठा inode *inode;
पूर्ण;

अटल व्योम nfs4_delegवापस_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_delegवापसdata *data = calldata;
	काष्ठा nfs4_exception exception = अणु
		.inode = data->inode,
		.stateid = &data->stateid,
		.task_is_privileged = data->args.seq_args.sa_privileged,
	पूर्ण;

	अगर (!nfs4_sequence_करोne(task, &data->res.seq_res))
		वापस;

	trace_nfs4_delegवापस_निकास(&data->args, &data->res, task->tk_status);

	/* Handle Layoutवापस errors */
	अगर (pnfs_roc_करोne(task, &data->args.lr_args, &data->res.lr_res,
			  &data->res.lr_ret) == -EAGAIN)
		जाओ out_restart;

	चयन (task->tk_status) अणु
	हाल 0:
		renew_lease(data->res.server, data->बारtamp);
		अवरोध;
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_DELEG_REVOKED:
	हाल -NFS4ERR_EXPIRED:
		nfs4_मुक्त_revoked_stateid(data->res.server,
				data->args.stateid,
				task->tk_msg.rpc_cred);
		fallthrough;
	हाल -NFS4ERR_BAD_STATEID:
	हाल -NFS4ERR_STALE_STATEID:
	हाल -ETIMEDOUT:
		task->tk_status = 0;
		अवरोध;
	हाल -NFS4ERR_OLD_STATEID:
		अगर (!nfs4_refresh_delegation_stateid(&data->stateid, data->inode))
			nfs4_stateid_seqid_inc(&data->stateid);
		अगर (data->args.biपंचांगask) अणु
			data->args.biपंचांगask = शून्य;
			data->res.fattr = शून्य;
		पूर्ण
		जाओ out_restart;
	हाल -NFS4ERR_ACCESS:
		अगर (data->args.biपंचांगask) अणु
			data->args.biपंचांगask = शून्य;
			data->res.fattr = शून्य;
			जाओ out_restart;
		पूर्ण
		fallthrough;
	शेष:
		task->tk_status = nfs4_async_handle_exception(task,
				data->res.server, task->tk_status,
				&exception);
		अगर (exception.retry)
			जाओ out_restart;
	पूर्ण
	nfs_delegation_mark_वापसed(data->inode, data->args.stateid);
	data->rpc_status = task->tk_status;
	वापस;
out_restart:
	task->tk_status = 0;
	rpc_restart_call_prepare(task);
पूर्ण

अटल व्योम nfs4_delegवापस_release(व्योम *calldata)
अणु
	काष्ठा nfs4_delegवापसdata *data = calldata;
	काष्ठा inode *inode = data->inode;

	अगर (data->lr.roc)
		pnfs_roc_release(&data->lr.arg, &data->lr.res,
				 data->res.lr_ret);
	अगर (inode) अणु
		nfs_post_op_update_inode_क्रमce_wcc(inode, &data->fattr);
		nfs_iput_and_deactive(inode);
	पूर्ण
	kमुक्त(calldata);
पूर्ण

अटल व्योम nfs4_delegवापस_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_delegवापसdata *d_data;
	काष्ठा pnfs_layout_hdr *lo;

	d_data = (काष्ठा nfs4_delegवापसdata *)data;

	अगर (!d_data->lr.roc && nfs4_रुको_on_layoutवापस(d_data->inode, task)) अणु
		nfs4_sequence_करोne(task, &d_data->res.seq_res);
		वापस;
	पूर्ण

	lo = d_data->args.lr_args ? d_data->args.lr_args->layout : शून्य;
	अगर (lo && !pnfs_layout_is_valid(lo)) अणु
		d_data->args.lr_args = शून्य;
		d_data->res.lr_res = शून्य;
	पूर्ण

	nfs4_setup_sequence(d_data->res.server->nfs_client,
			&d_data->args.seq_args,
			&d_data->res.seq_res,
			task);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_delegवापस_ops = अणु
	.rpc_call_prepare = nfs4_delegवापस_prepare,
	.rpc_call_करोne = nfs4_delegवापस_करोne,
	.rpc_release = nfs4_delegवापस_release,
पूर्ण;

अटल पूर्णांक _nfs4_proc_delegवापस(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, स्थिर nfs4_stateid *stateid, पूर्णांक issync)
अणु
	काष्ठा nfs4_delegवापसdata *data;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DELEGRETURN],
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_delegवापस_ops,
		.flags = RPC_TASK_ASYNC | RPC_TASK_TIMEOUT,
	पूर्ण;
	पूर्णांक status = 0;

	data = kzalloc(माप(*data), GFP_NOFS);
	अगर (data == शून्य)
		वापस -ENOMEM;

	nfs4_state_protect(server->nfs_client,
			NFS_SP4_MACH_CRED_CLEANUP,
			&task_setup_data.rpc_client, &msg);

	data->args.fhandle = &data->fh;
	data->args.stateid = &data->stateid;
	nfs4_biपंचांगask_set(data->args.biपंचांगask_store,
			 server->cache_consistency_biपंचांगask, inode, server,
			 शून्य);
	data->args.biपंचांगask = data->args.biपंचांगask_store;
	nfs_copy_fh(&data->fh, NFS_FH(inode));
	nfs4_stateid_copy(&data->stateid, stateid);
	data->res.fattr = &data->fattr;
	data->res.server = server;
	data->res.lr_ret = -NFS4ERR_NOMATCHING_LAYOUT;
	data->lr.arg.ld_निजी = &data->lr.ld_निजी;
	nfs_fattr_init(data->res.fattr);
	data->बारtamp = jअगरfies;
	data->rpc_status = 0;
	data->inode = nfs_igrab_and_active(inode);
	अगर (data->inode || issync) अणु
		data->lr.roc = pnfs_roc(inode, &data->lr.arg, &data->lr.res,
					cred);
		अगर (data->lr.roc) अणु
			data->args.lr_args = &data->lr.arg;
			data->res.lr_res = &data->lr.res;
		पूर्ण
	पूर्ण

	अगर (!data->inode)
		nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 1,
				   1);
	अन्यथा
		nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 1,
				   0);
	task_setup_data.callback_data = data;
	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	अगर (!issync)
		जाओ out;
	status = rpc_रुको_क्रम_completion_task(task);
	अगर (status != 0)
		जाओ out;
	status = data->rpc_status;
out:
	rpc_put_task(task);
	वापस status;
पूर्ण

पूर्णांक nfs4_proc_delegवापस(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, स्थिर nfs4_stateid *stateid, पूर्णांक issync)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_delegवापस(inode, cred, stateid, issync);
		trace_nfs4_delegवापस(inode, stateid, err);
		चयन (err) अणु
			हाल -NFS4ERR_STALE_STATEID:
			हाल -NFS4ERR_EXPIRED:
			हाल 0:
				वापस 0;
		पूर्ण
		err = nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक _nfs4_proc_getlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा inode *inode = state->inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs_lockt_args arg = अणु
		.fh = NFS_FH(inode),
		.fl = request,
	पूर्ण;
	काष्ठा nfs_lockt_res res = अणु
		.denied = request,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_LOCKT],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
		.rpc_cred	= state->owner->so_cred,
	पूर्ण;
	काष्ठा nfs4_lock_state *lsp;
	पूर्णांक status;

	arg.lock_owner.clientid = clp->cl_clientid;
	status = nfs4_set_lock_state(state, request);
	अगर (status != 0)
		जाओ out;
	lsp = request->fl_u.nfs4_fl.owner;
	arg.lock_owner.id = lsp->ls_seqid.owner_id;
	arg.lock_owner.s_dev = server->s_dev;
	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	चयन (status) अणु
		हाल 0:
			request->fl_type = F_UNLCK;
			अवरोध;
		हाल -NFS4ERR_DENIED:
			status = 0;
	पूर्ण
	request->fl_ops->fl_release_निजी(request);
	request->fl_ops = शून्य;
out:
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_getlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs4_proc_getlk(state, cmd, request);
		trace_nfs4_get_lock(request, state, cmd, err);
		err = nfs4_handle_exception(NFS_SERVER(state->inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

/*
 * Update the seqid of a lock stateid after receiving
 * NFS4ERR_OLD_STATEID
 */
अटल bool nfs4_refresh_lock_old_stateid(nfs4_stateid *dst,
		काष्ठा nfs4_lock_state *lsp)
अणु
	काष्ठा nfs4_state *state = lsp->ls_state;
	bool ret = false;

	spin_lock(&state->state_lock);
	अगर (!nfs4_stateid_match_other(dst, &lsp->ls_stateid))
		जाओ out;
	अगर (!nfs4_stateid_is_newer(&lsp->ls_stateid, dst))
		nfs4_stateid_seqid_inc(dst);
	अन्यथा
		dst->seqid = lsp->ls_stateid.seqid;
	ret = true;
out:
	spin_unlock(&state->state_lock);
	वापस ret;
पूर्ण

अटल bool nfs4_sync_lock_stateid(nfs4_stateid *dst,
		काष्ठा nfs4_lock_state *lsp)
अणु
	काष्ठा nfs4_state *state = lsp->ls_state;
	bool ret;

	spin_lock(&state->state_lock);
	ret = !nfs4_stateid_match_other(dst, &lsp->ls_stateid);
	nfs4_stateid_copy(dst, &lsp->ls_stateid);
	spin_unlock(&state->state_lock);
	वापस ret;
पूर्ण

काष्ठा nfs4_unlockdata अणु
	काष्ठा nfs_locku_args arg;
	काष्ठा nfs_locku_res res;
	काष्ठा nfs4_lock_state *lsp;
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs_lock_context *l_ctx;
	काष्ठा file_lock fl;
	काष्ठा nfs_server *server;
	अचिन्हित दीर्घ बारtamp;
पूर्ण;

अटल काष्ठा nfs4_unlockdata *nfs4_alloc_unlockdata(काष्ठा file_lock *fl,
		काष्ठा nfs_खोलो_context *ctx,
		काष्ठा nfs4_lock_state *lsp,
		काष्ठा nfs_seqid *seqid)
अणु
	काष्ठा nfs4_unlockdata *p;
	काष्ठा nfs4_state *state = lsp->ls_state;
	काष्ठा inode *inode = state->inode;

	p = kzalloc(माप(*p), GFP_NOFS);
	अगर (p == शून्य)
		वापस शून्य;
	p->arg.fh = NFS_FH(inode);
	p->arg.fl = &p->fl;
	p->arg.seqid = seqid;
	p->res.seqid = seqid;
	p->lsp = lsp;
	/* Ensure we करोn't close file until we're करोne मुक्तing locks! */
	p->ctx = get_nfs_खोलो_context(ctx);
	p->l_ctx = nfs_get_lock_context(ctx);
	locks_init_lock(&p->fl);
	locks_copy_lock(&p->fl, fl);
	p->server = NFS_SERVER(inode);
	spin_lock(&state->state_lock);
	nfs4_stateid_copy(&p->arg.stateid, &lsp->ls_stateid);
	spin_unlock(&state->state_lock);
	वापस p;
पूर्ण

अटल व्योम nfs4_locku_release_calldata(व्योम *data)
अणु
	काष्ठा nfs4_unlockdata *calldata = data;
	nfs_मुक्त_seqid(calldata->arg.seqid);
	nfs4_put_lock_state(calldata->lsp);
	nfs_put_lock_context(calldata->l_ctx);
	put_nfs_खोलो_context(calldata->ctx);
	kमुक्त(calldata);
पूर्ण

अटल व्योम nfs4_locku_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_unlockdata *calldata = data;
	काष्ठा nfs4_exception exception = अणु
		.inode = calldata->lsp->ls_state->inode,
		.stateid = &calldata->arg.stateid,
	पूर्ण;

	अगर (!nfs4_sequence_करोne(task, &calldata->res.seq_res))
		वापस;
	चयन (task->tk_status) अणु
		हाल 0:
			renew_lease(calldata->server, calldata->बारtamp);
			locks_lock_inode_रुको(calldata->lsp->ls_state->inode, &calldata->fl);
			अगर (nfs4_update_lock_stateid(calldata->lsp,
					&calldata->res.stateid))
				अवरोध;
			fallthrough;
		हाल -NFS4ERR_ADMIN_REVOKED:
		हाल -NFS4ERR_EXPIRED:
			nfs4_मुक्त_revoked_stateid(calldata->server,
					&calldata->arg.stateid,
					task->tk_msg.rpc_cred);
			fallthrough;
		हाल -NFS4ERR_BAD_STATEID:
		हाल -NFS4ERR_STALE_STATEID:
			अगर (nfs4_sync_lock_stateid(&calldata->arg.stateid,
						calldata->lsp))
				rpc_restart_call_prepare(task);
			अवरोध;
		हाल -NFS4ERR_OLD_STATEID:
			अगर (nfs4_refresh_lock_old_stateid(&calldata->arg.stateid,
						calldata->lsp))
				rpc_restart_call_prepare(task);
			अवरोध;
		शेष:
			task->tk_status = nfs4_async_handle_exception(task,
					calldata->server, task->tk_status,
					&exception);
			अगर (exception.retry)
				rpc_restart_call_prepare(task);
	पूर्ण
	nfs_release_seqid(calldata->arg.seqid);
पूर्ण

अटल व्योम nfs4_locku_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_unlockdata *calldata = data;

	अगर (test_bit(NFS_CONTEXT_UNLOCK, &calldata->l_ctx->खोलो_context->flags) &&
		nfs_async_iocounter_रुको(task, calldata->l_ctx))
		वापस;

	अगर (nfs_रुको_on_sequence(calldata->arg.seqid, task) != 0)
		जाओ out_रुको;
	अगर (test_bit(NFS_LOCK_INITIALIZED, &calldata->lsp->ls_flags) == 0) अणु
		/* Note: निकास _without_ running nfs4_locku_करोne */
		जाओ out_no_action;
	पूर्ण
	calldata->बारtamp = jअगरfies;
	अगर (nfs4_setup_sequence(calldata->server->nfs_client,
				&calldata->arg.seq_args,
				&calldata->res.seq_res,
				task) != 0)
		nfs_release_seqid(calldata->arg.seqid);
	वापस;
out_no_action:
	task->tk_action = शून्य;
out_रुको:
	nfs4_sequence_करोne(task, &calldata->res.seq_res);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_locku_ops = अणु
	.rpc_call_prepare = nfs4_locku_prepare,
	.rpc_call_करोne = nfs4_locku_करोne,
	.rpc_release = nfs4_locku_release_calldata,
पूर्ण;

अटल काष्ठा rpc_task *nfs4_करो_unlck(काष्ठा file_lock *fl,
		काष्ठा nfs_खोलो_context *ctx,
		काष्ठा nfs4_lock_state *lsp,
		काष्ठा nfs_seqid *seqid)
अणु
	काष्ठा nfs4_unlockdata *data;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LOCKU],
		.rpc_cred = ctx->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = NFS_CLIENT(lsp->ls_state->inode),
		.rpc_message = &msg,
		.callback_ops = &nfs4_locku_ops,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC,
	पूर्ण;

	nfs4_state_protect(NFS_SERVER(lsp->ls_state->inode)->nfs_client,
		NFS_SP4_MACH_CRED_CLEANUP, &task_setup_data.rpc_client, &msg);

	/* Ensure this is an unlock - when canceling a lock, the
	 * canceled lock is passed in, and it won't be an unlock.
	 */
	fl->fl_type = F_UNLCK;
	अगर (fl->fl_flags & FL_CLOSE)
		set_bit(NFS_CONTEXT_UNLOCK, &ctx->flags);

	data = nfs4_alloc_unlockdata(fl, ctx, lsp, seqid);
	अगर (data == शून्य) अणु
		nfs_मुक्त_seqid(seqid);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	nfs4_init_sequence(&data->arg.seq_args, &data->res.seq_res, 1, 0);
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;
	task_setup_data.callback_data = data;
	वापस rpc_run_task(&task_setup_data);
पूर्ण

अटल पूर्णांक nfs4_proc_unlck(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा inode *inode = state->inode;
	काष्ठा nfs4_state_owner *sp = state->owner;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_seqid *seqid;
	काष्ठा nfs4_lock_state *lsp;
	काष्ठा rpc_task *task;
	काष्ठा nfs_seqid *(*alloc_seqid)(काष्ठा nfs_seqid_counter *, gfp_t);
	पूर्णांक status = 0;
	अचिन्हित अक्षर fl_flags = request->fl_flags;

	status = nfs4_set_lock_state(state, request);
	/* Unlock _beक्रमe_ we करो the RPC call */
	request->fl_flags |= FL_EXISTS;
	/* Exclude nfs_delegation_claim_locks() */
	mutex_lock(&sp->so_delegवापस_mutex);
	/* Exclude nfs4_reclaim_खोलो_stateid() - note nesting! */
	करोwn_पढ़ो(&nfsi->rwsem);
	अगर (locks_lock_inode_रुको(inode, request) == -ENOENT) अणु
		up_पढ़ो(&nfsi->rwsem);
		mutex_unlock(&sp->so_delegवापस_mutex);
		जाओ out;
	पूर्ण
	up_पढ़ो(&nfsi->rwsem);
	mutex_unlock(&sp->so_delegवापस_mutex);
	अगर (status != 0)
		जाओ out;
	/* Is this a delegated lock? */
	lsp = request->fl_u.nfs4_fl.owner;
	अगर (test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags) == 0)
		जाओ out;
	alloc_seqid = NFS_SERVER(inode)->nfs_client->cl_mvops->alloc_seqid;
	seqid = alloc_seqid(&lsp->ls_seqid, GFP_KERNEL);
	status = -ENOMEM;
	अगर (IS_ERR(seqid))
		जाओ out;
	task = nfs4_करो_unlck(request, nfs_file_खोलो_context(request->fl_file), lsp, seqid);
	status = PTR_ERR(task);
	अगर (IS_ERR(task))
		जाओ out;
	status = rpc_रुको_क्रम_completion_task(task);
	rpc_put_task(task);
out:
	request->fl_flags = fl_flags;
	trace_nfs4_unlock(request, state, F_SETLK, status);
	वापस status;
पूर्ण

काष्ठा nfs4_lockdata अणु
	काष्ठा nfs_lock_args arg;
	काष्ठा nfs_lock_res res;
	काष्ठा nfs4_lock_state *lsp;
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा file_lock fl;
	अचिन्हित दीर्घ बारtamp;
	पूर्णांक rpc_status;
	पूर्णांक cancelled;
	काष्ठा nfs_server *server;
पूर्ण;

अटल काष्ठा nfs4_lockdata *nfs4_alloc_lockdata(काष्ठा file_lock *fl,
		काष्ठा nfs_खोलो_context *ctx, काष्ठा nfs4_lock_state *lsp,
		gfp_t gfp_mask)
अणु
	काष्ठा nfs4_lockdata *p;
	काष्ठा inode *inode = lsp->ls_state->inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_seqid *(*alloc_seqid)(काष्ठा nfs_seqid_counter *, gfp_t);

	p = kzalloc(माप(*p), gfp_mask);
	अगर (p == शून्य)
		वापस शून्य;

	p->arg.fh = NFS_FH(inode);
	p->arg.fl = &p->fl;
	p->arg.खोलो_seqid = nfs_alloc_seqid(&lsp->ls_state->owner->so_seqid, gfp_mask);
	अगर (IS_ERR(p->arg.खोलो_seqid))
		जाओ out_मुक्त;
	alloc_seqid = server->nfs_client->cl_mvops->alloc_seqid;
	p->arg.lock_seqid = alloc_seqid(&lsp->ls_seqid, gfp_mask);
	अगर (IS_ERR(p->arg.lock_seqid))
		जाओ out_मुक्त_seqid;
	p->arg.lock_owner.clientid = server->nfs_client->cl_clientid;
	p->arg.lock_owner.id = lsp->ls_seqid.owner_id;
	p->arg.lock_owner.s_dev = server->s_dev;
	p->res.lock_seqid = p->arg.lock_seqid;
	p->lsp = lsp;
	p->server = server;
	p->ctx = get_nfs_खोलो_context(ctx);
	locks_init_lock(&p->fl);
	locks_copy_lock(&p->fl, fl);
	वापस p;
out_मुक्त_seqid:
	nfs_मुक्त_seqid(p->arg.खोलो_seqid);
out_मुक्त:
	kमुक्त(p);
	वापस शून्य;
पूर्ण

अटल व्योम nfs4_lock_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_lockdata *data = calldata;
	काष्ठा nfs4_state *state = data->lsp->ls_state;

	dprपूर्णांकk("%s: begin!\n", __func__);
	अगर (nfs_रुको_on_sequence(data->arg.lock_seqid, task) != 0)
		जाओ out_रुको;
	/* Do we need to करो an खोलो_to_lock_owner? */
	अगर (!test_bit(NFS_LOCK_INITIALIZED, &data->lsp->ls_flags)) अणु
		अगर (nfs_रुको_on_sequence(data->arg.खोलो_seqid, task) != 0) अणु
			जाओ out_release_lock_seqid;
		पूर्ण
		nfs4_stateid_copy(&data->arg.खोलो_stateid,
				&state->खोलो_stateid);
		data->arg.new_lock_owner = 1;
		data->res.खोलो_seqid = data->arg.खोलो_seqid;
	पूर्ण अन्यथा अणु
		data->arg.new_lock_owner = 0;
		nfs4_stateid_copy(&data->arg.lock_stateid,
				&data->lsp->ls_stateid);
	पूर्ण
	अगर (!nfs4_valid_खोलो_stateid(state)) अणु
		data->rpc_status = -EBADF;
		task->tk_action = शून्य;
		जाओ out_release_खोलो_seqid;
	पूर्ण
	data->बारtamp = jअगरfies;
	अगर (nfs4_setup_sequence(data->server->nfs_client,
				&data->arg.seq_args,
				&data->res.seq_res,
				task) == 0)
		वापस;
out_release_खोलो_seqid:
	nfs_release_seqid(data->arg.खोलो_seqid);
out_release_lock_seqid:
	nfs_release_seqid(data->arg.lock_seqid);
out_रुको:
	nfs4_sequence_करोne(task, &data->res.seq_res);
	dprपूर्णांकk("%s: done!, ret = %d\n", __func__, data->rpc_status);
पूर्ण

अटल व्योम nfs4_lock_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_lockdata *data = calldata;
	काष्ठा nfs4_lock_state *lsp = data->lsp;

	dprपूर्णांकk("%s: begin!\n", __func__);

	अगर (!nfs4_sequence_करोne(task, &data->res.seq_res))
		वापस;

	data->rpc_status = task->tk_status;
	चयन (task->tk_status) अणु
	हाल 0:
		renew_lease(NFS_SERVER(d_inode(data->ctx->dentry)),
				data->बारtamp);
		अगर (data->arg.new_lock && !data->cancelled) अणु
			data->fl.fl_flags &= ~(FL_SLEEP | FL_ACCESS);
			अगर (locks_lock_inode_रुको(lsp->ls_state->inode, &data->fl) < 0)
				जाओ out_restart;
		पूर्ण
		अगर (data->arg.new_lock_owner != 0) अणु
			nfs_confirm_seqid(&lsp->ls_seqid, 0);
			nfs4_stateid_copy(&lsp->ls_stateid, &data->res.stateid);
			set_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags);
		पूर्ण अन्यथा अगर (!nfs4_update_lock_stateid(lsp, &data->res.stateid))
			जाओ out_restart;
		अवरोध;
	हाल -NFS4ERR_BAD_STATEID:
	हाल -NFS4ERR_OLD_STATEID:
	हाल -NFS4ERR_STALE_STATEID:
	हाल -NFS4ERR_EXPIRED:
		अगर (data->arg.new_lock_owner != 0) अणु
			अगर (!nfs4_stateid_match(&data->arg.खोलो_stateid,
						&lsp->ls_state->खोलो_stateid))
				जाओ out_restart;
		पूर्ण अन्यथा अगर (!nfs4_stateid_match(&data->arg.lock_stateid,
						&lsp->ls_stateid))
				जाओ out_restart;
	पूर्ण
out_करोne:
	dprपूर्णांकk("%s: done, ret = %d!\n", __func__, data->rpc_status);
	वापस;
out_restart:
	अगर (!data->cancelled)
		rpc_restart_call_prepare(task);
	जाओ out_करोne;
पूर्ण

अटल व्योम nfs4_lock_release(व्योम *calldata)
अणु
	काष्ठा nfs4_lockdata *data = calldata;

	dprपूर्णांकk("%s: begin!\n", __func__);
	nfs_मुक्त_seqid(data->arg.खोलो_seqid);
	अगर (data->cancelled && data->rpc_status == 0) अणु
		काष्ठा rpc_task *task;
		task = nfs4_करो_unlck(&data->fl, data->ctx, data->lsp,
				data->arg.lock_seqid);
		अगर (!IS_ERR(task))
			rpc_put_task_async(task);
		dprपूर्णांकk("%s: cancelling lock!\n", __func__);
	पूर्ण अन्यथा
		nfs_मुक्त_seqid(data->arg.lock_seqid);
	nfs4_put_lock_state(data->lsp);
	put_nfs_खोलो_context(data->ctx);
	kमुक्त(data);
	dprपूर्णांकk("%s: done!\n", __func__);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_lock_ops = अणु
	.rpc_call_prepare = nfs4_lock_prepare,
	.rpc_call_करोne = nfs4_lock_करोne,
	.rpc_release = nfs4_lock_release,
पूर्ण;

अटल व्योम nfs4_handle_setlk_error(काष्ठा nfs_server *server, काष्ठा nfs4_lock_state *lsp, पूर्णांक new_lock_owner, पूर्णांक error)
अणु
	चयन (error) अणु
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_EXPIRED:
	हाल -NFS4ERR_BAD_STATEID:
		lsp->ls_seqid.flags &= ~NFS_SEQID_CONFIRMED;
		अगर (new_lock_owner != 0 ||
		   test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags) != 0)
			nfs4_schedule_stateid_recovery(server, lsp->ls_state);
		अवरोध;
	हाल -NFS4ERR_STALE_STATEID:
		lsp->ls_seqid.flags &= ~NFS_SEQID_CONFIRMED;
		nfs4_schedule_lease_recovery(server->nfs_client);
	पूर्ण
पूर्ण

अटल पूर्णांक _nfs4_करो_setlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *fl, पूर्णांक recovery_type)
अणु
	काष्ठा nfs4_lockdata *data;
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LOCK],
		.rpc_cred = state->owner->so_cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = NFS_CLIENT(state->inode),
		.rpc_message = &msg,
		.callback_ops = &nfs4_lock_ops,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;
	पूर्णांक ret;

	dprपूर्णांकk("%s: begin!\n", __func__);
	data = nfs4_alloc_lockdata(fl, nfs_file_खोलो_context(fl->fl_file),
			fl->fl_u.nfs4_fl.owner,
			recovery_type == NFS_LOCK_NEW ? GFP_KERNEL : GFP_NOFS);
	अगर (data == शून्य)
		वापस -ENOMEM;
	अगर (IS_SETLKW(cmd))
		data->arg.block = 1;
	nfs4_init_sequence(&data->arg.seq_args, &data->res.seq_res, 1,
				recovery_type > NFS_LOCK_NEW);
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;
	task_setup_data.callback_data = data;
	अगर (recovery_type > NFS_LOCK_NEW) अणु
		अगर (recovery_type == NFS_LOCK_RECLAIM)
			data->arg.reclaim = NFS_LOCK_RECLAIM;
	पूर्ण अन्यथा
		data->arg.new_lock = 1;
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	ret = rpc_रुको_क्रम_completion_task(task);
	अगर (ret == 0) अणु
		ret = data->rpc_status;
		अगर (ret)
			nfs4_handle_setlk_error(data->server, data->lsp,
					data->arg.new_lock_owner, ret);
	पूर्ण अन्यथा
		data->cancelled = true;
	trace_nfs4_set_lock(fl, state, &data->res.stateid, cmd, ret);
	rpc_put_task(task);
	dprपूर्णांकk("%s: done, ret = %d!\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_lock_reclaim(काष्ठा nfs4_state *state, काष्ठा file_lock *request)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs4_exception exception = अणु
		.inode = state->inode,
	पूर्ण;
	पूर्णांक err;

	करो अणु
		/* Cache the lock अगर possible... */
		अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) != 0)
			वापस 0;
		err = _nfs4_करो_setlk(state, F_SETLK, request, NFS_LOCK_RECLAIM);
		अगर (err != -NFS4ERR_DELAY)
			अवरोध;
		nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

अटल पूर्णांक nfs4_lock_expired(काष्ठा nfs4_state *state, काष्ठा file_lock *request)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs4_exception exception = अणु
		.inode = state->inode,
	पूर्ण;
	पूर्णांक err;

	err = nfs4_set_lock_state(state, request);
	अगर (err != 0)
		वापस err;
	अगर (!recover_lost_locks) अणु
		set_bit(NFS_LOCK_LOST, &request->fl_u.nfs4_fl.owner->ls_flags);
		वापस 0;
	पूर्ण
	करो अणु
		अगर (test_bit(NFS_DELEGATED_STATE, &state->flags) != 0)
			वापस 0;
		err = _nfs4_करो_setlk(state, F_SETLK, request, NFS_LOCK_EXPIRED);
		चयन (err) अणु
		शेष:
			जाओ out;
		हाल -NFS4ERR_GRACE:
		हाल -NFS4ERR_DELAY:
			nfs4_handle_exception(server, err, &exception);
			err = 0;
		पूर्ण
	पूर्ण जबतक (exception.retry);
out:
	वापस err;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
अटल पूर्णांक nfs41_lock_expired(काष्ठा nfs4_state *state, काष्ठा file_lock *request)
अणु
	काष्ठा nfs4_lock_state *lsp;
	पूर्णांक status;

	status = nfs4_set_lock_state(state, request);
	अगर (status != 0)
		वापस status;
	lsp = request->fl_u.nfs4_fl.owner;
	अगर (test_bit(NFS_LOCK_INITIALIZED, &lsp->ls_flags) ||
	    test_bit(NFS_LOCK_LOST, &lsp->ls_flags))
		वापस 0;
	वापस nfs4_lock_expired(state, request);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक _nfs4_proc_setlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(state->inode);
	काष्ठा nfs4_state_owner *sp = state->owner;
	अचिन्हित अक्षर fl_flags = request->fl_flags;
	पूर्णांक status;

	request->fl_flags |= FL_ACCESS;
	status = locks_lock_inode_रुको(state->inode, request);
	अगर (status < 0)
		जाओ out;
	mutex_lock(&sp->so_delegवापस_mutex);
	करोwn_पढ़ो(&nfsi->rwsem);
	अगर (test_bit(NFS_DELEGATED_STATE, &state->flags)) अणु
		/* Yes: cache locks! */
		/* ...but aव्योम races with delegation recall... */
		request->fl_flags = fl_flags & ~FL_SLEEP;
		status = locks_lock_inode_रुको(state->inode, request);
		up_पढ़ो(&nfsi->rwsem);
		mutex_unlock(&sp->so_delegवापस_mutex);
		जाओ out;
	पूर्ण
	up_पढ़ो(&nfsi->rwsem);
	mutex_unlock(&sp->so_delegवापस_mutex);
	status = _nfs4_करो_setlk(state, cmd, request, NFS_LOCK_NEW);
out:
	request->fl_flags = fl_flags;
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_setlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा nfs4_exception exception = अणु
		.state = state,
		.inode = state->inode,
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs4_proc_setlk(state, cmd, request);
		अगर (err == -NFS4ERR_DENIED)
			err = -EAGAIN;
		err = nfs4_handle_exception(NFS_SERVER(state->inode),
				err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

#घोषणा NFS4_LOCK_MINTIMEOUT (1 * HZ)
#घोषणा NFS4_LOCK_MAXTIMEOUT (30 * HZ)

अटल पूर्णांक
nfs4_retry_setlk_simple(काष्ठा nfs4_state *state, पूर्णांक cmd,
			काष्ठा file_lock *request)
अणु
	पूर्णांक		status = -ERESTARTSYS;
	अचिन्हित दीर्घ	समयout = NFS4_LOCK_MINTIMEOUT;

	जबतक(!संकेतled()) अणु
		status = nfs4_proc_setlk(state, cmd, request);
		अगर ((status != -EAGAIN) || IS_SETLK(cmd))
			अवरोध;
		मुक्तzable_schedule_समयout_पूर्णांकerruptible(समयout);
		समयout *= 2;
		समयout = min_t(अचिन्हित दीर्घ, NFS4_LOCK_MAXTIMEOUT, समयout);
		status = -ERESTARTSYS;
	पूर्ण
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
काष्ठा nfs4_lock_रुकोer अणु
	काष्ठा inode		*inode;
	काष्ठा nfs_lowner	owner;
	रुको_queue_entry_t	रुको;
पूर्ण;

अटल पूर्णांक
nfs4_wake_lock_रुकोer(रुको_queue_entry_t *रुको, अचिन्हित पूर्णांक mode, पूर्णांक flags, व्योम *key)
अणु
	काष्ठा nfs4_lock_रुकोer	*रुकोer	=
		container_of(रुको, काष्ठा nfs4_lock_रुकोer, रुको);

	/* शून्य key means to wake up everyone */
	अगर (key) अणु
		काष्ठा cb_notअगरy_lock_args	*cbnl = key;
		काष्ठा nfs_lowner		*lowner = &cbnl->cbnl_owner,
						*wowner = &रुकोer->owner;

		/* Only wake अगर the callback was क्रम the same owner. */
		अगर (lowner->id != wowner->id || lowner->s_dev != wowner->s_dev)
			वापस 0;

		/* Make sure it's क्रम the right inode */
		अगर (nfs_compare_fh(NFS_FH(रुकोer->inode), &cbnl->cbnl_fh))
			वापस 0;
	पूर्ण

	वापस woken_wake_function(रुको, mode, flags, key);
पूर्ण

अटल पूर्णांक
nfs4_retry_setlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा nfs4_lock_state *lsp = request->fl_u.nfs4_fl.owner;
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	रुको_queue_head_t *q = &clp->cl_lock_रुकोq;
	काष्ठा nfs4_lock_रुकोer रुकोer = अणु
		.inode = state->inode,
		.owner = अणु .clientid = clp->cl_clientid,
			   .id = lsp->ls_seqid.owner_id,
			   .s_dev = server->s_dev पूर्ण,
	पूर्ण;
	पूर्णांक status;

	/* Don't bother with waitqueue if we don't expect a callback */
	अगर (!test_bit(NFS_STATE_MAY_NOTIFY_LOCK, &state->flags))
		वापस nfs4_retry_setlk_simple(state, cmd, request);

	init_रुको(&रुकोer.रुको);
	रुकोer.रुको.func = nfs4_wake_lock_रुकोer;
	add_रुको_queue(q, &रुकोer.रुको);

	करो अणु
		status = nfs4_proc_setlk(state, cmd, request);
		अगर (status != -EAGAIN || IS_SETLK(cmd))
			अवरोध;

		status = -ERESTARTSYS;
		मुक्तzer_करो_not_count();
		रुको_woken(&रुकोer.रुको, TASK_INTERRUPTIBLE,
			   NFS4_LOCK_MAXTIMEOUT);
		मुक्तzer_count();
	पूर्ण जबतक (!संकेतled());

	हटाओ_रुको_queue(q, &रुकोer.रुको);

	वापस status;
पूर्ण
#अन्यथा /* !CONFIG_NFS_V4_1 */
अटल अंतरभूत पूर्णांक
nfs4_retry_setlk(काष्ठा nfs4_state *state, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	वापस nfs4_retry_setlk_simple(state, cmd, request);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
nfs4_proc_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *request)
अणु
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs4_state *state;
	पूर्णांक status;

	/* verअगरy खोलो state */
	ctx = nfs_file_खोलो_context(filp);
	state = ctx->state;

	अगर (IS_GETLK(cmd)) अणु
		अगर (state != शून्य)
			वापस nfs4_proc_getlk(state, F_GETLK, request);
		वापस 0;
	पूर्ण

	अगर (!(IS_SETLK(cmd) || IS_SETLKW(cmd)))
		वापस -EINVAL;

	अगर (request->fl_type == F_UNLCK) अणु
		अगर (state != शून्य)
			वापस nfs4_proc_unlck(state, cmd, request);
		वापस 0;
	पूर्ण

	अगर (state == शून्य)
		वापस -ENOLCK;

	अगर ((request->fl_flags & FL_POSIX) &&
	    !test_bit(NFS_STATE_POSIX_LOCKS, &state->flags))
		वापस -ENOLCK;

	/*
	 * Don't rely on the VFS having checked the file खोलो mode,
	 * since it won't करो this क्रम flock() locks.
	 */
	चयन (request->fl_type) अणु
	हाल F_RDLCK:
		अगर (!(filp->f_mode & FMODE_READ))
			वापस -EBADF;
		अवरोध;
	हाल F_WRLCK:
		अगर (!(filp->f_mode & FMODE_WRITE))
			वापस -EBADF;
	पूर्ण

	status = nfs4_set_lock_state(state, request);
	अगर (status != 0)
		वापस status;

	वापस nfs4_retry_setlk(state, cmd, request);
पूर्ण

पूर्णांक nfs4_lock_delegation_recall(काष्ठा file_lock *fl, काष्ठा nfs4_state *state, स्थिर nfs4_stateid *stateid)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(state->inode);
	पूर्णांक err;

	err = nfs4_set_lock_state(state, fl);
	अगर (err != 0)
		वापस err;
	करो अणु
		err = _nfs4_करो_setlk(state, F_SETLK, fl, NFS_LOCK_NEW);
		अगर (err != -NFS4ERR_DELAY)
			अवरोध;
		ssleep(1);
	पूर्ण जबतक (err == -NFS4ERR_DELAY);
	वापस nfs4_handle_delegation_recall_error(server, state, stateid, fl, err);
पूर्ण

काष्ठा nfs_release_lockowner_data अणु
	काष्ठा nfs4_lock_state *lsp;
	काष्ठा nfs_server *server;
	काष्ठा nfs_release_lockowner_args args;
	काष्ठा nfs_release_lockowner_res res;
	अचिन्हित दीर्घ बारtamp;
पूर्ण;

अटल व्योम nfs4_release_lockowner_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_release_lockowner_data *data = calldata;
	काष्ठा nfs_server *server = data->server;
	nfs4_setup_sequence(server->nfs_client, &data->args.seq_args,
			   &data->res.seq_res, task);
	data->args.lock_owner.clientid = server->nfs_client->cl_clientid;
	data->बारtamp = jअगरfies;
पूर्ण

अटल व्योम nfs4_release_lockowner_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_release_lockowner_data *data = calldata;
	काष्ठा nfs_server *server = data->server;

	nfs40_sequence_करोne(task, &data->res.seq_res);

	चयन (task->tk_status) अणु
	हाल 0:
		renew_lease(server, data->बारtamp);
		अवरोध;
	हाल -NFS4ERR_STALE_CLIENTID:
	हाल -NFS4ERR_EXPIRED:
		nfs4_schedule_lease_recovery(server->nfs_client);
		अवरोध;
	हाल -NFS4ERR_LEASE_MOVED:
	हाल -NFS4ERR_DELAY:
		अगर (nfs4_async_handle_error(task, server,
					    शून्य, शून्य) == -EAGAIN)
			rpc_restart_call_prepare(task);
	पूर्ण
पूर्ण

अटल व्योम nfs4_release_lockowner_release(व्योम *calldata)
अणु
	काष्ठा nfs_release_lockowner_data *data = calldata;
	nfs4_मुक्त_lock_state(data->server, data->lsp);
	kमुक्त(calldata);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_release_lockowner_ops = अणु
	.rpc_call_prepare = nfs4_release_lockowner_prepare,
	.rpc_call_करोne = nfs4_release_lockowner_करोne,
	.rpc_release = nfs4_release_lockowner_release,
पूर्ण;

अटल व्योम
nfs4_release_lockowner(काष्ठा nfs_server *server, काष्ठा nfs4_lock_state *lsp)
अणु
	काष्ठा nfs_release_lockowner_data *data;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RELEASE_LOCKOWNER],
	पूर्ण;

	अगर (server->nfs_client->cl_mvops->minor_version != 0)
		वापस;

	data = kदो_स्मृति(माप(*data), GFP_NOFS);
	अगर (!data)
		वापस;
	data->lsp = lsp;
	data->server = server;
	data->args.lock_owner.clientid = server->nfs_client->cl_clientid;
	data->args.lock_owner.id = lsp->ls_seqid.owner_id;
	data->args.lock_owner.s_dev = server->s_dev;

	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 0, 0);
	rpc_call_async(server->client, &msg, 0, &nfs4_release_lockowner_ops, data);
पूर्ण

#घोषणा XATTR_NAME_NFSV4_ACL "system.nfs4_acl"

अटल पूर्णांक nfs4_xattr_set_nfs4_acl(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा user_namespace *mnt_userns,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *key, स्थिर व्योम *buf,
				   माप_प्रकार buflen, पूर्णांक flags)
अणु
	वापस nfs4_proc_set_acl(inode, buf, buflen);
पूर्ण

अटल पूर्णांक nfs4_xattr_get_nfs4_acl(स्थिर काष्ठा xattr_handler *handler,
				   काष्ठा dentry *unused, काष्ठा inode *inode,
				   स्थिर अक्षर *key, व्योम *buf, माप_प्रकार buflen)
अणु
	वापस nfs4_proc_get_acl(inode, buf, buflen);
पूर्ण

अटल bool nfs4_xattr_list_nfs4_acl(काष्ठा dentry *dentry)
अणु
	वापस nfs4_server_supports_acls(NFS_SERVER(d_inode(dentry)));
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL

अटल पूर्णांक nfs4_xattr_set_nfs4_label(स्थिर काष्ठा xattr_handler *handler,
				     काष्ठा user_namespace *mnt_userns,
				     काष्ठा dentry *unused, काष्ठा inode *inode,
				     स्थिर अक्षर *key, स्थिर व्योम *buf,
				     माप_प्रकार buflen, पूर्णांक flags)
अणु
	अगर (security_ismaclabel(key))
		वापस nfs4_set_security_label(inode, buf, buflen);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक nfs4_xattr_get_nfs4_label(स्थिर काष्ठा xattr_handler *handler,
				     काष्ठा dentry *unused, काष्ठा inode *inode,
				     स्थिर अक्षर *key, व्योम *buf, माप_प्रकार buflen)
अणु
	अगर (security_ismaclabel(key))
		वापस nfs4_get_security_label(inode, buf, buflen);
	वापस -EOPNOTSUPP;
पूर्ण

अटल sमाप_प्रकार
nfs4_listxattr_nfs4_label(काष्ठा inode *inode, अक्षर *list, माप_प्रकार list_len)
अणु
	पूर्णांक len = 0;

	अगर (nfs_server_capable(inode, NFS_CAP_SECURITY_LABEL)) अणु
		len = security_inode_listsecurity(inode, list, list_len);
		अगर (len >= 0 && list_len && len > list_len)
			वापस -दुस्फल;
	पूर्ण
	वापस len;
पूर्ण

अटल स्थिर काष्ठा xattr_handler nfs4_xattr_nfs4_label_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.get	= nfs4_xattr_get_nfs4_label,
	.set	= nfs4_xattr_set_nfs4_label,
पूर्ण;

#अन्यथा

अटल sमाप_प्रकार
nfs4_listxattr_nfs4_label(काष्ठा inode *inode, अक्षर *list, माप_प्रकार list_len)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_NFS_V4_2
अटल पूर्णांक nfs4_xattr_set_nfs4_user(स्थिर काष्ठा xattr_handler *handler,
				    काष्ठा user_namespace *mnt_userns,
				    काष्ठा dentry *unused, काष्ठा inode *inode,
				    स्थिर अक्षर *key, स्थिर व्योम *buf,
				    माप_प्रकार buflen, पूर्णांक flags)
अणु
	काष्ठा nfs_access_entry cache;
	पूर्णांक ret;

	अगर (!nfs_server_capable(inode, NFS_CAP_XATTR))
		वापस -EOPNOTSUPP;

	/*
	 * There is no mapping from the MAY_* flags to the NFS_ACCESS_XA*
	 * flags right now. Handling of xattr operations use the normal
	 * file पढ़ो/ग_लिखो permissions.
	 *
	 * Just in हाल the server has other ideas (which RFC 8276 allows),
	 * करो a cached access check क्रम the XA* flags to possibly aव्योम
	 * करोing an RPC and getting EACCES back.
	 */
	अगर (!nfs_access_get_cached(inode, current_cred(), &cache, true)) अणु
		अगर (!(cache.mask & NFS_ACCESS_XAWRITE))
			वापस -EACCES;
	पूर्ण

	अगर (buf == शून्य) अणु
		ret = nfs42_proc_हटाओxattr(inode, key);
		अगर (!ret)
			nfs4_xattr_cache_हटाओ(inode, key);
	पूर्ण अन्यथा अणु
		ret = nfs42_proc_setxattr(inode, key, buf, buflen, flags);
		अगर (!ret)
			nfs4_xattr_cache_add(inode, key, buf, शून्य, buflen);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_xattr_get_nfs4_user(स्थिर काष्ठा xattr_handler *handler,
				    काष्ठा dentry *unused, काष्ठा inode *inode,
				    स्थिर अक्षर *key, व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs_access_entry cache;
	sमाप_प्रकार ret;

	अगर (!nfs_server_capable(inode, NFS_CAP_XATTR))
		वापस -EOPNOTSUPP;

	अगर (!nfs_access_get_cached(inode, current_cred(), &cache, true)) अणु
		अगर (!(cache.mask & NFS_ACCESS_XAREAD))
			वापस -EACCES;
	पूर्ण

	ret = nfs_revalidate_inode(inode, NFS_INO_INVALID_CHANGE);
	अगर (ret)
		वापस ret;

	ret = nfs4_xattr_cache_get(inode, key, buf, buflen);
	अगर (ret >= 0 || (ret < 0 && ret != -ENOENT))
		वापस ret;

	ret = nfs42_proc_getxattr(inode, key, buf, buflen);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
nfs4_listxattr_nfs4_user(काष्ठा inode *inode, अक्षर *list, माप_प्रकार list_len)
अणु
	u64 cookie;
	bool eof;
	sमाप_प्रकार ret, size;
	अक्षर *buf;
	माप_प्रकार buflen;
	काष्ठा nfs_access_entry cache;

	अगर (!nfs_server_capable(inode, NFS_CAP_XATTR))
		वापस 0;

	अगर (!nfs_access_get_cached(inode, current_cred(), &cache, true)) अणु
		अगर (!(cache.mask & NFS_ACCESS_XALIST))
			वापस 0;
	पूर्ण

	ret = nfs_revalidate_inode(inode, NFS_INO_INVALID_CHANGE);
	अगर (ret)
		वापस ret;

	ret = nfs4_xattr_cache_list(inode, list, list_len);
	अगर (ret >= 0 || (ret < 0 && ret != -ENOENT))
		वापस ret;

	cookie = 0;
	eof = false;
	buflen = list_len ? list_len : XATTR_LIST_MAX;
	buf = list_len ? list : शून्य;
	size = 0;

	जबतक (!eof) अणु
		ret = nfs42_proc_listxattrs(inode, buf, buflen,
		    &cookie, &eof);
		अगर (ret < 0)
			वापस ret;

		अगर (list_len) अणु
			buf += ret;
			buflen -= ret;
		पूर्ण
		size += ret;
	पूर्ण

	अगर (list_len)
		nfs4_xattr_cache_set_list(inode, list, size);

	वापस size;
पूर्ण

#अन्यथा

अटल sमाप_प्रकार
nfs4_listxattr_nfs4_user(काष्ठा inode *inode, अक्षर *list, माप_प्रकार list_len)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

/*
 * nfs_fhget will use either the mounted_on_fileid or the fileid
 */
अटल व्योम nfs_fixup_referral_attributes(काष्ठा nfs_fattr *fattr)
अणु
	अगर (!(((fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID) ||
	       (fattr->valid & NFS_ATTR_FATTR_खाताID)) &&
	      (fattr->valid & NFS_ATTR_FATTR_FSID) &&
	      (fattr->valid & NFS_ATTR_FATTR_V4_LOCATIONS)))
		वापस;

	fattr->valid |= NFS_ATTR_FATTR_TYPE | NFS_ATTR_FATTR_MODE |
		NFS_ATTR_FATTR_NLINK | NFS_ATTR_FATTR_V4_REFERRAL;
	fattr->mode = S_IFसूची | S_IRUGO | S_IXUGO;
	fattr->nlink = 2;
पूर्ण

अटल पूर्णांक _nfs4_proc_fs_locations(काष्ठा rpc_clnt *client, काष्ठा inode *dir,
				   स्थिर काष्ठा qstr *name,
				   काष्ठा nfs4_fs_locations *fs_locations,
				   काष्ठा page *page)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(dir);
	u32 biपंचांगask[3];
	काष्ठा nfs4_fs_locations_arg args = अणु
		.dir_fh = NFS_FH(dir),
		.name = name,
		.page = page,
		.biपंचांगask = biपंचांगask,
	पूर्ण;
	काष्ठा nfs4_fs_locations_res res = अणु
		.fs_locations = fs_locations,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_FS_LOCATIONS],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	पूर्णांक status;

	dprपूर्णांकk("%s: start\n", __func__);

	biपंचांगask[0] = nfs4_fattr_biपंचांगap[0] | FATTR4_WORD0_FS_LOCATIONS;
	biपंचांगask[1] = nfs4_fattr_biपंचांगap[1];

	/* Ask क्रम the fileid of the असलent fileप्रणाली अगर mounted_on_fileid
	 * is not supported */
	अगर (NFS_SERVER(dir)->attr_biपंचांगask[1] & FATTR4_WORD1_MOUNTED_ON_खाताID)
		biपंचांगask[0] &= ~FATTR4_WORD0_खाताID;
	अन्यथा
		biपंचांगask[1] &= ~FATTR4_WORD1_MOUNTED_ON_खाताID;

	nfs_fattr_init(&fs_locations->fattr);
	fs_locations->server = server;
	fs_locations->nlocations = 0;
	status = nfs4_call_sync(client, server, &msg, &args.seq_args, &res.seq_res, 0);
	dprपूर्णांकk("%s: returned status = %d\n", __func__, status);
	वापस status;
पूर्ण

पूर्णांक nfs4_proc_fs_locations(काष्ठा rpc_clnt *client, काष्ठा inode *dir,
			   स्थिर काष्ठा qstr *name,
			   काष्ठा nfs4_fs_locations *fs_locations,
			   काष्ठा page *page)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs4_proc_fs_locations(client, dir, name,
				fs_locations, page);
		trace_nfs4_get_fs_locations(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

/*
 * This operation also संकेतs the server that this client is
 * perक्रमming migration recovery.  The server can stop वापसing
 * NFS4ERR_LEASE_MOVED to this client.  A RENEW operation is
 * appended to this compound to identअगरy the client ID which is
 * perक्रमming recovery.
 */
अटल पूर्णांक _nfs40_proc_get_locations(काष्ठा inode *inode,
				     काष्ठा nfs4_fs_locations *locations,
				     काष्ठा page *page, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा rpc_clnt *clnt = server->client;
	u32 biपंचांगask[2] = अणु
		[0] = FATTR4_WORD0_FSID | FATTR4_WORD0_FS_LOCATIONS,
	पूर्ण;
	काष्ठा nfs4_fs_locations_arg args = अणु
		.clientid	= server->nfs_client->cl_clientid,
		.fh		= NFS_FH(inode),
		.page		= page,
		.biपंचांगask	= biपंचांगask,
		.migration	= 1,		/* skip LOOKUP */
		.renew		= 1,		/* append RENEW */
	पूर्ण;
	काष्ठा nfs4_fs_locations_res res = अणु
		.fs_locations	= locations,
		.migration	= 1,
		.renew		= 1,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_FS_LOCATIONS],
		.rpc_argp	= &args,
		.rpc_resp	= &res,
		.rpc_cred	= cred,
	पूर्ण;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक status;

	nfs_fattr_init(&locations->fattr);
	locations->server = server;
	locations->nlocations = 0;

	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 1);
	status = nfs4_call_sync_sequence(clnt, server, &msg,
					&args.seq_args, &res.seq_res);
	अगर (status)
		वापस status;

	renew_lease(server, now);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1

/*
 * This operation also संकेतs the server that this client is
 * perक्रमming migration recovery.  The server can stop निश्चितing
 * SEQ4_STATUS_LEASE_MOVED क्रम this client.  The client ID
 * perक्रमming this operation is identअगरied in the SEQUENCE
 * operation in this compound.
 *
 * When the client supports GETATTR(fs_locations_info), it can
 * be plumbed in here.
 */
अटल पूर्णांक _nfs41_proc_get_locations(काष्ठा inode *inode,
				     काष्ठा nfs4_fs_locations *locations,
				     काष्ठा page *page, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा rpc_clnt *clnt = server->client;
	u32 biपंचांगask[2] = अणु
		[0] = FATTR4_WORD0_FSID | FATTR4_WORD0_FS_LOCATIONS,
	पूर्ण;
	काष्ठा nfs4_fs_locations_arg args = अणु
		.fh		= NFS_FH(inode),
		.page		= page,
		.biपंचांगask	= biपंचांगask,
		.migration	= 1,		/* skip LOOKUP */
	पूर्ण;
	काष्ठा nfs4_fs_locations_res res = अणु
		.fs_locations	= locations,
		.migration	= 1,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_FS_LOCATIONS],
		.rpc_argp	= &args,
		.rpc_resp	= &res,
		.rpc_cred	= cred,
	पूर्ण;
	पूर्णांक status;

	nfs_fattr_init(&locations->fattr);
	locations->server = server;
	locations->nlocations = 0;

	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 1);
	status = nfs4_call_sync_sequence(clnt, server, &msg,
					&args.seq_args, &res.seq_res);
	अगर (status == NFS4_OK &&
	    res.seq_res.sr_status_flags & SEQ4_STATUS_LEASE_MOVED)
		status = -NFS4ERR_LEASE_MOVED;
	वापस status;
पूर्ण

#पूर्ण_अगर	/* CONFIG_NFS_V4_1 */

/**
 * nfs4_proc_get_locations - discover locations क्रम a migrated FSID
 * @inode: inode on FSID that is migrating
 * @locations: result of query
 * @page: buffer
 * @cred: credential to use क्रम this operation
 *
 * Returns NFS4_OK on success, a negative NFS4ERR status code अगर the
 * operation failed, or a negative त्रुटि_सं अगर a local error occurred.
 *
 * On success, "locations" is filled in, but अगर the server has
 * no locations inक्रमmation, NFS_ATTR_FATTR_V4_LOCATIONS is not
 * निश्चितed.
 *
 * -NFS4ERR_LEASE_MOVED is वापसed अगर the server still has leases
 * from this client that require migration recovery.
 */
पूर्णांक nfs4_proc_get_locations(काष्ठा inode *inode,
			    काष्ठा nfs4_fs_locations *locations,
			    काष्ठा page *page, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	स्थिर काष्ठा nfs4_mig_recovery_ops *ops =
					clp->cl_mvops->mig_recovery_ops;
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक status;

	dprपूर्णांकk("%s: FSID %llx:%llx on \"%s\"\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)server->fsid.major,
		(अचिन्हित दीर्घ दीर्घ)server->fsid.minor,
		clp->cl_hostname);
	nfs_display_fhandle(NFS_FH(inode), __func__);

	करो अणु
		status = ops->get_locations(inode, locations, page, cred);
		अगर (status != -NFS4ERR_DELAY)
			अवरोध;
		nfs4_handle_exception(server, status, &exception);
	पूर्ण जबतक (exception.retry);
	वापस status;
पूर्ण

/*
 * This operation also संकेतs the server that this client is
 * perक्रमming "lease moved" recovery.  The server can stop
 * वापसing NFS4ERR_LEASE_MOVED to this client.  A RENEW operation
 * is appended to this compound to identअगरy the client ID which is
 * perक्रमming recovery.
 */
अटल पूर्णांक _nfs40_proc_fsid_present(काष्ठा inode *inode, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_client *clp = NFS_SERVER(inode)->nfs_client;
	काष्ठा rpc_clnt *clnt = server->client;
	काष्ठा nfs4_fsid_present_arg args = अणु
		.fh		= NFS_FH(inode),
		.clientid	= clp->cl_clientid,
		.renew		= 1,		/* append RENEW */
	पूर्ण;
	काष्ठा nfs4_fsid_present_res res = अणु
		.renew		= 1,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_FSID_PRESENT],
		.rpc_argp	= &args,
		.rpc_resp	= &res,
		.rpc_cred	= cred,
	पूर्ण;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक status;

	res.fh = nfs_alloc_fhandle();
	अगर (res.fh == शून्य)
		वापस -ENOMEM;

	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 1);
	status = nfs4_call_sync_sequence(clnt, server, &msg,
						&args.seq_args, &res.seq_res);
	nfs_मुक्त_fhandle(res.fh);
	अगर (status)
		वापस status;

	करो_renew_lease(clp, now);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1

/*
 * This operation also संकेतs the server that this client is
 * perक्रमming "lease moved" recovery.  The server can stop निश्चितing
 * SEQ4_STATUS_LEASE_MOVED क्रम this client.  The client ID perक्रमming
 * this operation is identअगरied in the SEQUENCE operation in this
 * compound.
 */
अटल पूर्णांक _nfs41_proc_fsid_present(काष्ठा inode *inode, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा rpc_clnt *clnt = server->client;
	काष्ठा nfs4_fsid_present_arg args = अणु
		.fh		= NFS_FH(inode),
	पूर्ण;
	काष्ठा nfs4_fsid_present_res res = अणु
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_FSID_PRESENT],
		.rpc_argp	= &args,
		.rpc_resp	= &res,
		.rpc_cred	= cred,
	पूर्ण;
	पूर्णांक status;

	res.fh = nfs_alloc_fhandle();
	अगर (res.fh == शून्य)
		वापस -ENOMEM;

	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 1);
	status = nfs4_call_sync_sequence(clnt, server, &msg,
						&args.seq_args, &res.seq_res);
	nfs_मुक्त_fhandle(res.fh);
	अगर (status == NFS4_OK &&
	    res.seq_res.sr_status_flags & SEQ4_STATUS_LEASE_MOVED)
		status = -NFS4ERR_LEASE_MOVED;
	वापस status;
पूर्ण

#पूर्ण_अगर	/* CONFIG_NFS_V4_1 */

/**
 * nfs4_proc_fsid_present - Is this FSID present or असलent on server?
 * @inode: inode on FSID to check
 * @cred: credential to use क्रम this operation
 *
 * Server indicates whether the FSID is present, moved, or not
 * recognized.  This operation is necessary to clear a LEASE_MOVED
 * condition क्रम this client ID.
 *
 * Returns NFS4_OK अगर the FSID is present on this server,
 * -NFS4ERR_MOVED अगर the FSID is no दीर्घer present, a negative
 *  NFS4ERR code अगर some error occurred on the server, or a
 *  negative त्रुटि_सं अगर a local failure occurred.
 */
पूर्णांक nfs4_proc_fsid_present(काष्ठा inode *inode, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_client *clp = server->nfs_client;
	स्थिर काष्ठा nfs4_mig_recovery_ops *ops =
					clp->cl_mvops->mig_recovery_ops;
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक status;

	dprपूर्णांकk("%s: FSID %llx:%llx on \"%s\"\n", __func__,
		(अचिन्हित दीर्घ दीर्घ)server->fsid.major,
		(अचिन्हित दीर्घ दीर्घ)server->fsid.minor,
		clp->cl_hostname);
	nfs_display_fhandle(NFS_FH(inode), __func__);

	करो अणु
		status = ops->fsid_present(inode, cred);
		अगर (status != -NFS4ERR_DELAY)
			अवरोध;
		nfs4_handle_exception(server, status, &exception);
	पूर्ण जबतक (exception.retry);
	वापस status;
पूर्ण

/*
 * If 'use_integrity' is true and the state managment nfs_client
 * cl_rpcclient is using krb5i/p, use the पूर्णांकegrity रक्षित cl_rpcclient
 * and the machine credential as per RFC3530bis and RFC5661 Security
 * Considerations sections. Otherwise, just use the user cred with the
 * fileप्रणाली's rpc_client.
 */
अटल पूर्णांक _nfs4_proc_secinfo(काष्ठा inode *dir, स्थिर काष्ठा qstr *name, काष्ठा nfs4_secinfo_flavors *flavors, bool use_पूर्णांकegrity)
अणु
	पूर्णांक status;
	काष्ठा rpc_clnt *clnt = NFS_SERVER(dir)->client;
	काष्ठा nfs_client *clp = NFS_SERVER(dir)->nfs_client;
	काष्ठा nfs4_secinfo_arg args = अणु
		.dir_fh = NFS_FH(dir),
		.name   = name,
	पूर्ण;
	काष्ठा nfs4_secinfo_res res = अणु
		.flavors     = flavors,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SECINFO],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	काष्ठा nfs4_call_sync_data data = अणु
		.seq_server = NFS_SERVER(dir),
		.seq_args = &args.seq_args,
		.seq_res = &res.seq_res,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_client = clnt,
		.rpc_message = &msg,
		.callback_ops = clp->cl_mvops->call_sync_ops,
		.callback_data = &data,
		.flags = RPC_TASK_NO_ROUND_ROBIN,
	पूर्ण;
	स्थिर काष्ठा cred *cred = शून्य;

	अगर (use_पूर्णांकegrity) अणु
		clnt = clp->cl_rpcclient;
		task_setup.rpc_client = clnt;

		cred = nfs4_get_clid_cred(clp);
		msg.rpc_cred = cred;
	पूर्ण

	dprपूर्णांकk("NFS call  secinfo %s\n", name->name);

	nfs4_state_protect(clp, NFS_SP4_MACH_CRED_SECINFO, &clnt, &msg);
	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 0);
	status = nfs4_call_sync_custom(&task_setup);

	dprपूर्णांकk("NFS reply  secinfo: %d\n", status);

	put_cred(cred);
	वापस status;
पूर्ण

पूर्णांक nfs4_proc_secinfo(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
		      काष्ठा nfs4_secinfo_flavors *flavors)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = -NFS4ERR_WRONGSEC;

		/* try to use पूर्णांकegrity protection with machine cred */
		अगर (_nfs4_is_पूर्णांकegrity_रक्षित(NFS_SERVER(dir)->nfs_client))
			err = _nfs4_proc_secinfo(dir, name, flavors, true);

		/*
		 * अगर unable to use पूर्णांकegrity protection, or SECINFO with
		 * पूर्णांकegrity protection वापसs NFS4ERR_WRONGSEC (which is
		 * disallowed by spec, but exists in deployed servers) use
		 * the current fileप्रणाली's rpc_client and the user cred.
		 */
		अगर (err == -NFS4ERR_WRONGSEC)
			err = _nfs4_proc_secinfo(dir, name, flavors, false);

		trace_nfs4_secinfo(dir, name, err);
		err = nfs4_handle_exception(NFS_SERVER(dir), err,
				&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1
/*
 * Check the exchange flags वापसed by the server क्रम invalid flags, having
 * both PNFS and NON_PNFS flags set, and not having one of NON_PNFS, PNFS, or
 * DS flags set.
 */
अटल पूर्णांक nfs4_check_cl_exchange_flags(u32 flags, u32 version)
अणु
	अगर (version >= 2 && (flags & ~EXCHGID4_2_FLAG_MASK_R))
		जाओ out_inval;
	अन्यथा अगर (version < 2 && (flags & ~EXCHGID4_FLAG_MASK_R))
		जाओ out_inval;
	अगर ((flags & EXCHGID4_FLAG_USE_PNFS_MDS) &&
	    (flags & EXCHGID4_FLAG_USE_NON_PNFS))
		जाओ out_inval;
	अगर (!(flags & (EXCHGID4_FLAG_MASK_PNFS)))
		जाओ out_inval;
	वापस NFS_OK;
out_inval:
	वापस -NFS4ERR_INVAL;
पूर्ण

अटल bool
nfs41_same_server_scope(काष्ठा nfs41_server_scope *a,
			काष्ठा nfs41_server_scope *b)
अणु
	अगर (a->server_scope_sz != b->server_scope_sz)
		वापस false;
	वापस स_भेद(a->server_scope, b->server_scope, a->server_scope_sz) == 0;
पूर्ण

अटल व्योम
nfs4_bind_one_conn_to_session_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs41_bind_conn_to_session_args *args = task->tk_msg.rpc_argp;
	काष्ठा nfs41_bind_conn_to_session_res *res = task->tk_msg.rpc_resp;
	काष्ठा nfs_client *clp = args->client;

	चयन (task->tk_status) अणु
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_DEADSESSION:
		nfs4_schedule_session_recovery(clp->cl_session,
				task->tk_status);
	पूर्ण
	अगर (args->dir == NFS4_CDFC4_FORE_OR_BOTH &&
			res->dir != NFS4_CDFS4_BOTH) अणु
		rpc_task_बंद_connection(task);
		अगर (args->retries++ < MAX_BIND_CONN_TO_SESSION_RETRIES)
			rpc_restart_call(task);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_bind_one_conn_to_session_ops = अणु
	.rpc_call_करोne =  nfs4_bind_one_conn_to_session_करोne,
पूर्ण;

/*
 * nfs4_proc_bind_one_conn_to_session()
 *
 * The 4.1 client currently uses the same TCP connection क्रम the
 * क्रमe and backchannel.
 */
अटल
पूर्णांक nfs4_proc_bind_one_conn_to_session(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक status;
	काष्ठा nfs41_bind_conn_to_session_args args = अणु
		.client = clp,
		.dir = NFS4_CDFC4_FORE_OR_BOTH,
		.retries = 0,
	पूर्ण;
	काष्ठा nfs41_bind_conn_to_session_res res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc =
			&nfs4_procedures[NFSPROC4_CLNT_BIND_CONN_TO_SESSION],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clnt,
		.rpc_xprt = xprt,
		.callback_ops = &nfs4_bind_one_conn_to_session_ops,
		.rpc_message = &msg,
		.flags = RPC_TASK_TIMEOUT,
	पूर्ण;
	काष्ठा rpc_task *task;

	nfs4_copy_sessionid(&args.sessionid, &clp->cl_session->sess_id);
	अगर (!(clp->cl_session->flags & SESSION4_BACK_CHAN))
		args.dir = NFS4_CDFC4_FORE;

	/* Do not set the backchannel flag unless this is clnt->cl_xprt */
	अगर (xprt != rcu_access_poपूर्णांकer(clnt->cl_xprt))
		args.dir = NFS4_CDFC4_FORE;

	task = rpc_run_task(&task_setup_data);
	अगर (!IS_ERR(task)) अणु
		status = task->tk_status;
		rpc_put_task(task);
	पूर्ण अन्यथा
		status = PTR_ERR(task);
	trace_nfs4_bind_conn_to_session(clp, status);
	अगर (status == 0) अणु
		अगर (स_भेद(res.sessionid.data,
		    clp->cl_session->sess_id.data, NFS4_MAX_SESSIONID_LEN)) अणु
			dprपूर्णांकk("NFS: %s: Session ID mismatch\n", __func__);
			वापस -EIO;
		पूर्ण
		अगर ((res.dir & args.dir) != res.dir || res.dir == 0) अणु
			dprपूर्णांकk("NFS: %s: Unexpected direction from server\n",
				__func__);
			वापस -EIO;
		पूर्ण
		अगर (res.use_conn_in_rdma_mode != args.use_conn_in_rdma_mode) अणु
			dprपूर्णांकk("NFS: %s: Server returned RDMA mode = true\n",
				__func__);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

काष्ठा rpc_bind_conn_calldata अणु
	काष्ठा nfs_client *clp;
	स्थिर काष्ठा cred *cred;
पूर्ण;

अटल पूर्णांक
nfs4_proc_bind_conn_to_session_callback(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		व्योम *calldata)
अणु
	काष्ठा rpc_bind_conn_calldata *p = calldata;

	वापस nfs4_proc_bind_one_conn_to_session(clnt, xprt, p->clp, p->cred);
पूर्ण

पूर्णांक nfs4_proc_bind_conn_to_session(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rpc_bind_conn_calldata data = अणु
		.clp = clp,
		.cred = cred,
	पूर्ण;
	वापस rpc_clnt_iterate_क्रम_each_xprt(clp->cl_rpcclient,
			nfs4_proc_bind_conn_to_session_callback, &data);
पूर्ण

/*
 * Minimum set of SP4_MACH_CRED operations from RFC 5661 in the enक्रमce map
 * and operations we'd like to see to enable certain features in the allow map
 */
अटल स्थिर काष्ठा nfs41_state_protection nfs4_sp4_mach_cred_request = अणु
	.how = SP4_MACH_CRED,
	.enक्रमce.u.words = अणु
		[1] = 1 << (OP_BIND_CONN_TO_SESSION - 32) |
		      1 << (OP_EXCHANGE_ID - 32) |
		      1 << (OP_CREATE_SESSION - 32) |
		      1 << (OP_DESTROY_SESSION - 32) |
		      1 << (OP_DESTROY_CLIENTID - 32)
	पूर्ण,
	.allow.u.words = अणु
		[0] = 1 << (OP_CLOSE) |
		      1 << (OP_OPEN_DOWNGRADE) |
		      1 << (OP_LOCKU) |
		      1 << (OP_DELEGRETURN) |
		      1 << (OP_COMMIT),
		[1] = 1 << (OP_SECINFO - 32) |
		      1 << (OP_SECINFO_NO_NAME - 32) |
		      1 << (OP_LAYOUTRETURN - 32) |
		      1 << (OP_TEST_STATEID - 32) |
		      1 << (OP_FREE_STATEID - 32) |
		      1 << (OP_WRITE - 32)
	पूर्ण
पूर्ण;

/*
 * Select the state protection mode क्रम client `clp' given the server results
 * from exchange_id in `sp'.
 *
 * Returns 0 on success, negative त्रुटि_सं otherwise.
 */
अटल पूर्णांक nfs4_sp4_select_mode(काष्ठा nfs_client *clp,
				 काष्ठा nfs41_state_protection *sp)
अणु
	अटल स्थिर u32 supported_enक्रमce[NFS4_OP_MAP_NUM_WORDS] = अणु
		[1] = 1 << (OP_BIND_CONN_TO_SESSION - 32) |
		      1 << (OP_EXCHANGE_ID - 32) |
		      1 << (OP_CREATE_SESSION - 32) |
		      1 << (OP_DESTROY_SESSION - 32) |
		      1 << (OP_DESTROY_CLIENTID - 32)
	पूर्ण;
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	अगर (sp->how == SP4_MACH_CRED) अणु
		/* Prपूर्णांक state protect result */
		dfprपूर्णांकk(MOUNT, "Server SP4_MACH_CRED support:\n");
		क्रम (i = 0; i <= LAST_NFS4_OP; i++) अणु
			अगर (test_bit(i, sp->enक्रमce.u.दीर्घs))
				dfprपूर्णांकk(MOUNT, "  enforce op %d\n", i);
			अगर (test_bit(i, sp->allow.u.दीर्घs))
				dfprपूर्णांकk(MOUNT, "  allow op %d\n", i);
		पूर्ण

		/* make sure nothing is on enक्रमce list that isn't supported */
		क्रम (i = 0; i < NFS4_OP_MAP_NUM_WORDS; i++) अणु
			अगर (sp->enक्रमce.u.words[i] & ~supported_enक्रमce[i]) अणु
				dfprपूर्णांकk(MOUNT, "sp4_mach_cred: disabled\n");
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * Minimal mode - state operations are allowed to use machine
		 * credential.  Note this alपढ़ोy happens by शेष, so the
		 * client करोesn't have to करो anything more than the negotiation.
		 *
		 * NOTE: we करोn't care अगर EXCHANGE_ID is in the list -
		 *       we're alपढ़ोy using the machine cred क्रम exchange_id
		 *       and will never use a dअगरferent cred.
		 */
		अगर (test_bit(OP_BIND_CONN_TO_SESSION, sp->enक्रमce.u.दीर्घs) &&
		    test_bit(OP_CREATE_SESSION, sp->enक्रमce.u.दीर्घs) &&
		    test_bit(OP_DESTROY_SESSION, sp->enक्रमce.u.दीर्घs) &&
		    test_bit(OP_DESTROY_CLIENTID, sp->enक्रमce.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "sp4_mach_cred:\n");
			dfprपूर्णांकk(MOUNT, "  minimal mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_MINIMAL, &flags);
		पूर्ण अन्यथा अणु
			dfprपूर्णांकk(MOUNT, "sp4_mach_cred: disabled\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (test_bit(OP_CLOSE, sp->allow.u.दीर्घs) &&
		    test_bit(OP_OPEN_DOWNGRADE, sp->allow.u.दीर्घs) &&
		    test_bit(OP_DELEGRETURN, sp->allow.u.दीर्घs) &&
		    test_bit(OP_LOCKU, sp->allow.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "  cleanup mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_CLEANUP, &flags);
		पूर्ण

		अगर (test_bit(OP_LAYOUTRETURN, sp->allow.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "  pnfs cleanup mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_PNFS_CLEANUP, &flags);
		पूर्ण

		अगर (test_bit(OP_SECINFO, sp->allow.u.दीर्घs) &&
		    test_bit(OP_SECINFO_NO_NAME, sp->allow.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "  secinfo mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_SECINFO, &flags);
		पूर्ण

		अगर (test_bit(OP_TEST_STATEID, sp->allow.u.दीर्घs) &&
		    test_bit(OP_FREE_STATEID, sp->allow.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "  stateid mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_STATEID, &flags);
		पूर्ण

		अगर (test_bit(OP_WRITE, sp->allow.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "  write mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_WRITE, &flags);
		पूर्ण

		अगर (test_bit(OP_COMMIT, sp->allow.u.दीर्घs)) अणु
			dfprपूर्णांकk(MOUNT, "  commit mode enabled\n");
			__set_bit(NFS_SP4_MACH_CRED_COMMIT, &flags);
		पूर्ण
	पूर्ण
out:
	clp->cl_sp4_flags = flags;
	वापस ret;
पूर्ण

काष्ठा nfs41_exchange_id_data अणु
	काष्ठा nfs41_exchange_id_res res;
	काष्ठा nfs41_exchange_id_args args;
पूर्ण;

अटल व्योम nfs4_exchange_id_release(व्योम *data)
अणु
	काष्ठा nfs41_exchange_id_data *cdata =
					(काष्ठा nfs41_exchange_id_data *)data;

	nfs_put_client(cdata->args.client);
	kमुक्त(cdata->res.impl_id);
	kमुक्त(cdata->res.server_scope);
	kमुक्त(cdata->res.server_owner);
	kमुक्त(cdata);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_exchange_id_call_ops = अणु
	.rpc_release = nfs4_exchange_id_release,
पूर्ण;

/*
 * _nfs4_proc_exchange_id()
 *
 * Wrapper क्रम EXCHANGE_ID operation.
 */
अटल काष्ठा rpc_task *
nfs4_run_exchange_id(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred,
			u32 sp4_how, काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_EXCHANGE_ID],
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clp->cl_rpcclient,
		.callback_ops = &nfs4_exchange_id_call_ops,
		.rpc_message = &msg,
		.flags = RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN,
	पूर्ण;
	काष्ठा nfs41_exchange_id_data *calldata;
	पूर्णांक status;

	अगर (!refcount_inc_not_zero(&clp->cl_count))
		वापस ERR_PTR(-EIO);

	status = -ENOMEM;
	calldata = kzalloc(माप(*calldata), GFP_NOFS);
	अगर (!calldata)
		जाओ out;

	nfs4_init_boot_verअगरier(clp, &calldata->args.verअगरier);

	status = nfs4_init_unअगरorm_client_string(clp);
	अगर (status)
		जाओ out_calldata;

	calldata->res.server_owner = kzalloc(माप(काष्ठा nfs41_server_owner),
						GFP_NOFS);
	status = -ENOMEM;
	अगर (unlikely(calldata->res.server_owner == शून्य))
		जाओ out_calldata;

	calldata->res.server_scope = kzalloc(माप(काष्ठा nfs41_server_scope),
					GFP_NOFS);
	अगर (unlikely(calldata->res.server_scope == शून्य))
		जाओ out_server_owner;

	calldata->res.impl_id = kzalloc(माप(काष्ठा nfs41_impl_id), GFP_NOFS);
	अगर (unlikely(calldata->res.impl_id == शून्य))
		जाओ out_server_scope;

	चयन (sp4_how) अणु
	हाल SP4_NONE:
		calldata->args.state_protect.how = SP4_NONE;
		अवरोध;

	हाल SP4_MACH_CRED:
		calldata->args.state_protect = nfs4_sp4_mach_cred_request;
		अवरोध;

	शेष:
		/* unsupported! */
		WARN_ON_ONCE(1);
		status = -EINVAL;
		जाओ out_impl_id;
	पूर्ण
	अगर (xprt) अणु
		task_setup_data.rpc_xprt = xprt;
		task_setup_data.flags |= RPC_TASK_SOFTCONN;
		स_नकल(calldata->args.verअगरier.data, clp->cl_confirm.data,
				माप(calldata->args.verअगरier.data));
	पूर्ण
	calldata->args.client = clp;
	calldata->args.flags = EXCHGID4_FLAG_SUPP_MOVED_REFER |
	EXCHGID4_FLAG_BIND_PRINC_STATEID;
#अगर_घोषित CONFIG_NFS_V4_1_MIGRATION
	calldata->args.flags |= EXCHGID4_FLAG_SUPP_MOVED_MIGR;
#पूर्ण_अगर
	msg.rpc_argp = &calldata->args;
	msg.rpc_resp = &calldata->res;
	task_setup_data.callback_data = calldata;

	वापस rpc_run_task(&task_setup_data);

out_impl_id:
	kमुक्त(calldata->res.impl_id);
out_server_scope:
	kमुक्त(calldata->res.server_scope);
out_server_owner:
	kमुक्त(calldata->res.server_owner);
out_calldata:
	kमुक्त(calldata);
out:
	nfs_put_client(clp);
	वापस ERR_PTR(status);
पूर्ण

/*
 * _nfs4_proc_exchange_id()
 *
 * Wrapper क्रम EXCHANGE_ID operation.
 */
अटल पूर्णांक _nfs4_proc_exchange_id(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred,
			u32 sp4_how)
अणु
	काष्ठा rpc_task *task;
	काष्ठा nfs41_exchange_id_args *argp;
	काष्ठा nfs41_exchange_id_res *resp;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक status;

	task = nfs4_run_exchange_id(clp, cred, sp4_how, शून्य);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);

	argp = task->tk_msg.rpc_argp;
	resp = task->tk_msg.rpc_resp;
	status = task->tk_status;
	अगर (status  != 0)
		जाओ out;

	status = nfs4_check_cl_exchange_flags(resp->flags,
			clp->cl_mvops->minor_version);
	अगर (status  != 0)
		जाओ out;

	status = nfs4_sp4_select_mode(clp, &resp->state_protect);
	अगर (status != 0)
		जाओ out;

	करो_renew_lease(clp, now);

	clp->cl_clientid = resp->clientid;
	clp->cl_exchange_flags = resp->flags;
	clp->cl_seqid = resp->seqid;
	/* Client ID is not confirmed */
	अगर (!(resp->flags & EXCHGID4_FLAG_CONFIRMED_R))
		clear_bit(NFS4_SESSION_ESTABLISHED,
			  &clp->cl_session->session_state);

	अगर (clp->cl_serverscope != शून्य &&
	    !nfs41_same_server_scope(clp->cl_serverscope,
				resp->server_scope)) अणु
		dprपूर्णांकk("%s: server_scope mismatch detected\n",
			__func__);
		set_bit(NFS4CLNT_SERVER_SCOPE_MISMATCH, &clp->cl_state);
	पूर्ण

	swap(clp->cl_serverowner, resp->server_owner);
	swap(clp->cl_serverscope, resp->server_scope);
	swap(clp->cl_implid, resp->impl_id);

	/* Save the EXCHANGE_ID verअगरier session trunk tests */
	स_नकल(clp->cl_confirm.data, argp->verअगरier.data,
	       माप(clp->cl_confirm.data));
out:
	trace_nfs4_exchange_id(clp, status);
	rpc_put_task(task);
	वापस status;
पूर्ण

/*
 * nfs4_proc_exchange_id()
 *
 * Returns zero, a negative त्रुटि_सं, or a negative NFS4ERR status code.
 *
 * Since the clientid has expired, all compounds using sessions
 * associated with the stale clientid will be वापसing
 * NFS4ERR_BADSESSION in the sequence operation, and will thereक्रमe
 * be in some phase of session reset.
 *
 * Will attempt to negotiate SP4_MACH_CRED अगर krb5i / krb5p auth is used.
 */
पूर्णांक nfs4_proc_exchange_id(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	rpc_authflavor_t authflavor = clp->cl_rpcclient->cl_auth->au_flavor;
	पूर्णांक status;

	/* try SP4_MACH_CRED अगर krb5i/p	*/
	अगर (authflavor == RPC_AUTH_GSS_KRB5I ||
	    authflavor == RPC_AUTH_GSS_KRB5P) अणु
		status = _nfs4_proc_exchange_id(clp, cred, SP4_MACH_CRED);
		अगर (!status)
			वापस 0;
	पूर्ण

	/* try SP4_NONE */
	वापस _nfs4_proc_exchange_id(clp, cred, SP4_NONE);
पूर्ण

/**
 * nfs4_test_session_trunk
 *
 * This is an add_xprt_test() test function called from
 * rpc_clnt_setup_test_and_add_xprt.
 *
 * The rpc_xprt_चयन is referrenced by rpc_clnt_setup_test_and_add_xprt
 * and is dereferrenced in nfs4_exchange_id_release
 *
 * Upon success, add the new transport to the rpc_clnt
 *
 * @clnt: काष्ठा rpc_clnt to get new transport
 * @xprt: the rpc_xprt to test
 * @data: call data क्रम _nfs4_proc_exchange_id.
 */
व्योम nfs4_test_session_trunk(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt *xprt,
			    व्योम *data)
अणु
	काष्ठा nfs4_add_xprt_data *adata = (काष्ठा nfs4_add_xprt_data *)data;
	काष्ठा rpc_task *task;
	पूर्णांक status;

	u32 sp4_how;

	dprपूर्णांकk("--> %s try %s\n", __func__,
		xprt->address_strings[RPC_DISPLAY_ADDR]);

	sp4_how = (adata->clp->cl_sp4_flags == 0 ? SP4_NONE : SP4_MACH_CRED);

	/* Test connection क्रम session trunking. Async exchange_id call */
	task = nfs4_run_exchange_id(adata->clp, adata->cred, sp4_how, xprt);
	अगर (IS_ERR(task))
		वापस;

	status = task->tk_status;
	अगर (status == 0)
		status = nfs4_detect_session_trunking(adata->clp,
				task->tk_msg.rpc_resp, xprt);

	अगर (status == 0)
		rpc_clnt_xprt_चयन_add_xprt(clnt, xprt);

	rpc_put_task(task);
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_test_session_trunk);

अटल पूर्णांक _nfs4_proc_destroy_clientid(काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DESTROY_CLIENTID],
		.rpc_argp = clp,
		.rpc_cred = cred,
	पूर्ण;
	पूर्णांक status;

	status = rpc_call_sync(clp->cl_rpcclient, &msg,
			       RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN);
	trace_nfs4_destroy_clientid(clp, status);
	अगर (status)
		dprपूर्णांकk("NFS: Got error %d from the server %s on "
			"DESTROY_CLIENTID.", status, clp->cl_hostname);
	वापस status;
पूर्ण

अटल पूर्णांक nfs4_proc_destroy_clientid(काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred)
अणु
	अचिन्हित पूर्णांक loop;
	पूर्णांक ret;

	क्रम (loop = NFS4_MAX_LOOP_ON_RECOVER; loop != 0; loop--) अणु
		ret = _nfs4_proc_destroy_clientid(clp, cred);
		चयन (ret) अणु
		हाल -NFS4ERR_DELAY:
		हाल -NFS4ERR_CLIENTID_BUSY:
			ssleep(1);
			अवरोध;
		शेष:
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक nfs4_destroy_clientid(काष्ठा nfs_client *clp)
अणु
	स्थिर काष्ठा cred *cred;
	पूर्णांक ret = 0;

	अगर (clp->cl_mvops->minor_version < 1)
		जाओ out;
	अगर (clp->cl_exchange_flags == 0)
		जाओ out;
	अगर (clp->cl_preserve_clid)
		जाओ out;
	cred = nfs4_get_clid_cred(clp);
	ret = nfs4_proc_destroy_clientid(clp, cred);
	put_cred(cred);
	चयन (ret) अणु
	हाल 0:
	हाल -NFS4ERR_STALE_CLIENTID:
		clp->cl_exchange_flags = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

काष्ठा nfs4_get_lease_समय_data अणु
	काष्ठा nfs4_get_lease_समय_args *args;
	काष्ठा nfs4_get_lease_समय_res *res;
	काष्ठा nfs_client *clp;
पूर्ण;

अटल व्योम nfs4_get_lease_समय_prepare(काष्ठा rpc_task *task,
					व्योम *calldata)
अणु
	काष्ठा nfs4_get_lease_समय_data *data =
			(काष्ठा nfs4_get_lease_समय_data *)calldata;

	dprपूर्णांकk("--> %s\n", __func__);
	/* just setup sequence, करो not trigger session recovery
	   since we're invoked within one */
	nfs4_setup_sequence(data->clp,
			&data->args->la_seq_args,
			&data->res->lr_seq_res,
			task);
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

/*
 * Called from nfs4_state_manager thपढ़ो क्रम session setup, so करोn't recover
 * from sequence operation or clientid errors.
 */
अटल व्योम nfs4_get_lease_समय_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_get_lease_समय_data *data =
			(काष्ठा nfs4_get_lease_समय_data *)calldata;

	dprपूर्णांकk("--> %s\n", __func__);
	अगर (!nfs4_sequence_करोne(task, &data->res->lr_seq_res))
		वापस;
	चयन (task->tk_status) अणु
	हाल -NFS4ERR_DELAY:
	हाल -NFS4ERR_GRACE:
		dprपूर्णांकk("%s Retry: tk_status %d\n", __func__, task->tk_status);
		rpc_delay(task, NFS4_POLL_RETRY_MIN);
		task->tk_status = 0;
		fallthrough;
	हाल -NFS4ERR_RETRY_UNCACHED_REP:
		rpc_restart_call_prepare(task);
		वापस;
	पूर्ण
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_get_lease_समय_ops = अणु
	.rpc_call_prepare = nfs4_get_lease_समय_prepare,
	.rpc_call_करोne = nfs4_get_lease_समय_करोne,
पूर्ण;

पूर्णांक nfs4_proc_get_lease_समय(काष्ठा nfs_client *clp, काष्ठा nfs_fsinfo *fsinfo)
अणु
	काष्ठा nfs4_get_lease_समय_args args;
	काष्ठा nfs4_get_lease_समय_res res = अणु
		.lr_fsinfo = fsinfo,
	पूर्ण;
	काष्ठा nfs4_get_lease_समय_data data = अणु
		.args = &args,
		.res = &res,
		.clp = clp,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_GET_LEASE_TIME],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs4_get_lease_समय_ops,
		.callback_data = &data,
		.flags = RPC_TASK_TIMEOUT,
	पूर्ण;

	nfs4_init_sequence(&args.la_seq_args, &res.lr_seq_res, 0, 1);
	वापस nfs4_call_sync_custom(&task_setup);
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_1

/*
 * Initialize the values to be used by the client in CREATE_SESSION
 * If nfs4_init_session set the क्रमe channel request and response sizes,
 * use them.
 *
 * Set the back channel max_resp_sz_cached to zero to क्रमce the client to
 * always set csa_cachethis to FALSE because the current implementation
 * of the back channel DRC only supports caching the CB_SEQUENCE operation.
 */
अटल व्योम nfs4_init_channel_attrs(काष्ठा nfs41_create_session_args *args,
				    काष्ठा rpc_clnt *clnt)
अणु
	अचिन्हित पूर्णांक max_rqst_sz, max_resp_sz;
	अचिन्हित पूर्णांक max_bc_payload = rpc_max_bc_payload(clnt);
	अचिन्हित पूर्णांक max_bc_slots = rpc_num_bc_slots(clnt);

	max_rqst_sz = NFS_MAX_खाता_IO_SIZE + nfs41_maxग_लिखो_overhead;
	max_resp_sz = NFS_MAX_खाता_IO_SIZE + nfs41_maxपढ़ो_overhead;

	/* Fore channel attributes */
	args->fc_attrs.max_rqst_sz = max_rqst_sz;
	args->fc_attrs.max_resp_sz = max_resp_sz;
	args->fc_attrs.max_ops = NFS4_MAX_OPS;
	args->fc_attrs.max_reqs = max_session_slots;

	dprपूर्णांकk("%s: Fore Channel : max_rqst_sz=%u max_resp_sz=%u "
		"max_ops=%u max_reqs=%u\n",
		__func__,
		args->fc_attrs.max_rqst_sz, args->fc_attrs.max_resp_sz,
		args->fc_attrs.max_ops, args->fc_attrs.max_reqs);

	/* Back channel attributes */
	args->bc_attrs.max_rqst_sz = max_bc_payload;
	args->bc_attrs.max_resp_sz = max_bc_payload;
	args->bc_attrs.max_resp_sz_cached = 0;
	args->bc_attrs.max_ops = NFS4_MAX_BACK_CHANNEL_OPS;
	args->bc_attrs.max_reqs = max_t(अचिन्हित लघु, max_session_cb_slots, 1);
	अगर (args->bc_attrs.max_reqs > max_bc_slots)
		args->bc_attrs.max_reqs = max_bc_slots;

	dprपूर्णांकk("%s: Back Channel : max_rqst_sz=%u max_resp_sz=%u "
		"max_resp_sz_cached=%u max_ops=%u max_reqs=%u\n",
		__func__,
		args->bc_attrs.max_rqst_sz, args->bc_attrs.max_resp_sz,
		args->bc_attrs.max_resp_sz_cached, args->bc_attrs.max_ops,
		args->bc_attrs.max_reqs);
पूर्ण

अटल पूर्णांक nfs4_verअगरy_क्रमe_channel_attrs(काष्ठा nfs41_create_session_args *args,
		काष्ठा nfs41_create_session_res *res)
अणु
	काष्ठा nfs4_channel_attrs *sent = &args->fc_attrs;
	काष्ठा nfs4_channel_attrs *rcvd = &res->fc_attrs;

	अगर (rcvd->max_resp_sz > sent->max_resp_sz)
		वापस -EINVAL;
	/*
	 * Our requested max_ops is the minimum we need; we're not
	 * prepared to अवरोध up compounds पूर्णांकo smaller pieces than that.
	 * So, no poपूर्णांक even trying to जारी अगर the server won't
	 * cooperate:
	 */
	अगर (rcvd->max_ops < sent->max_ops)
		वापस -EINVAL;
	अगर (rcvd->max_reqs == 0)
		वापस -EINVAL;
	अगर (rcvd->max_reqs > NFS4_MAX_SLOT_TABLE)
		rcvd->max_reqs = NFS4_MAX_SLOT_TABLE;
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_verअगरy_back_channel_attrs(काष्ठा nfs41_create_session_args *args,
		काष्ठा nfs41_create_session_res *res)
अणु
	काष्ठा nfs4_channel_attrs *sent = &args->bc_attrs;
	काष्ठा nfs4_channel_attrs *rcvd = &res->bc_attrs;

	अगर (!(res->flags & SESSION4_BACK_CHAN))
		जाओ out;
	अगर (rcvd->max_rqst_sz > sent->max_rqst_sz)
		वापस -EINVAL;
	अगर (rcvd->max_resp_sz < sent->max_resp_sz)
		वापस -EINVAL;
	अगर (rcvd->max_resp_sz_cached > sent->max_resp_sz_cached)
		वापस -EINVAL;
	अगर (rcvd->max_ops > sent->max_ops)
		वापस -EINVAL;
	अगर (rcvd->max_reqs > sent->max_reqs)
		वापस -EINVAL;
out:
	वापस 0;
पूर्ण

अटल पूर्णांक nfs4_verअगरy_channel_attrs(काष्ठा nfs41_create_session_args *args,
				     काष्ठा nfs41_create_session_res *res)
अणु
	पूर्णांक ret;

	ret = nfs4_verअगरy_क्रमe_channel_attrs(args, res);
	अगर (ret)
		वापस ret;
	वापस nfs4_verअगरy_back_channel_attrs(args, res);
पूर्ण

अटल व्योम nfs4_update_session(काष्ठा nfs4_session *session,
		काष्ठा nfs41_create_session_res *res)
अणु
	nfs4_copy_sessionid(&session->sess_id, &res->sessionid);
	/* Mark client id and session as being confirmed */
	session->clp->cl_exchange_flags |= EXCHGID4_FLAG_CONFIRMED_R;
	set_bit(NFS4_SESSION_ESTABLISHED, &session->session_state);
	session->flags = res->flags;
	स_नकल(&session->fc_attrs, &res->fc_attrs, माप(session->fc_attrs));
	अगर (res->flags & SESSION4_BACK_CHAN)
		स_नकल(&session->bc_attrs, &res->bc_attrs,
				माप(session->bc_attrs));
पूर्ण

अटल पूर्णांक _nfs4_proc_create_session(काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_session *session = clp->cl_session;
	काष्ठा nfs41_create_session_args args = अणु
		.client = clp,
		.clientid = clp->cl_clientid,
		.seqid = clp->cl_seqid,
		.cb_program = NFS4_CALLBACK,
	पूर्ण;
	काष्ठा nfs41_create_session_res res;

	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CREATE_SESSION],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = cred,
	पूर्ण;
	पूर्णांक status;

	nfs4_init_channel_attrs(&args, clp->cl_rpcclient);
	args.flags = (SESSION4_PERSIST | SESSION4_BACK_CHAN);

	status = rpc_call_sync(session->clp->cl_rpcclient, &msg,
			       RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN);
	trace_nfs4_create_session(clp, status);

	चयन (status) अणु
	हाल -NFS4ERR_STALE_CLIENTID:
	हाल -NFS4ERR_DELAY:
	हाल -ETIMEDOUT:
	हाल -EACCES:
	हाल -EAGAIN:
		जाओ out;
	पूर्ण

	clp->cl_seqid++;
	अगर (!status) अणु
		/* Verअगरy the session's negotiated channel_attrs values */
		status = nfs4_verअगरy_channel_attrs(&args, &res);
		/* Increment the clientid slot sequence id */
		अगर (status)
			जाओ out;
		nfs4_update_session(session, &res);
	पूर्ण
out:
	वापस status;
पूर्ण

/*
 * Issues a CREATE_SESSION operation to the server.
 * It is the responsibility of the caller to verअगरy the session is
 * expired beक्रमe calling this routine.
 */
पूर्णांक nfs4_proc_create_session(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक status;
	अचिन्हित *ptr;
	काष्ठा nfs4_session *session = clp->cl_session;

	dprपूर्णांकk("--> %s clp=%p session=%p\n", __func__, clp, session);

	status = _nfs4_proc_create_session(clp, cred);
	अगर (status)
		जाओ out;

	/* Init or reset the session slot tables */
	status = nfs4_setup_session_slot_tables(session);
	dprपूर्णांकk("slot table setup returned %d\n", status);
	अगर (status)
		जाओ out;

	ptr = (अचिन्हित *)&session->sess_id.data[0];
	dprपूर्णांकk("%s client>seqid %d sessionid %u:%u:%u:%u\n", __func__,
		clp->cl_seqid, ptr[0], ptr[1], ptr[2], ptr[3]);
out:
	dprपूर्णांकk("<-- %s\n", __func__);
	वापस status;
पूर्ण

/*
 * Issue the over-the-wire RPC DESTROY_SESSION.
 * The caller must serialize access to this routine.
 */
पूर्णांक nfs4_proc_destroy_session(काष्ठा nfs4_session *session,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DESTROY_SESSION],
		.rpc_argp = session,
		.rpc_cred = cred,
	पूर्ण;
	पूर्णांक status = 0;

	dprपूर्णांकk("--> nfs4_proc_destroy_session\n");

	/* session is still being setup */
	अगर (!test_and_clear_bit(NFS4_SESSION_ESTABLISHED, &session->session_state))
		वापस 0;

	status = rpc_call_sync(session->clp->cl_rpcclient, &msg,
			       RPC_TASK_TIMEOUT | RPC_TASK_NO_ROUND_ROBIN);
	trace_nfs4_destroy_session(session->clp, status);

	अगर (status)
		dprपूर्णांकk("NFS: Got error %d from the server on DESTROY_SESSION. "
			"Session has been destroyed regardless...\n", status);

	dprपूर्णांकk("<-- nfs4_proc_destroy_session\n");
	वापस status;
पूर्ण

/*
 * Renew the cl_session lease.
 */
काष्ठा nfs4_sequence_data अणु
	काष्ठा nfs_client *clp;
	काष्ठा nfs4_sequence_args args;
	काष्ठा nfs4_sequence_res res;
पूर्ण;

अटल व्योम nfs41_sequence_release(व्योम *data)
अणु
	काष्ठा nfs4_sequence_data *calldata = data;
	काष्ठा nfs_client *clp = calldata->clp;

	अगर (refcount_पढ़ो(&clp->cl_count) > 1)
		nfs4_schedule_state_renewal(clp);
	nfs_put_client(clp);
	kमुक्त(calldata);
पूर्ण

अटल पूर्णांक nfs41_sequence_handle_errors(काष्ठा rpc_task *task, काष्ठा nfs_client *clp)
अणु
	चयन(task->tk_status) अणु
	हाल -NFS4ERR_DELAY:
		rpc_delay(task, NFS4_POLL_RETRY_MAX);
		वापस -EAGAIN;
	शेष:
		nfs4_schedule_lease_recovery(clp);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nfs41_sequence_call_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_sequence_data *calldata = data;
	काष्ठा nfs_client *clp = calldata->clp;

	अगर (!nfs41_sequence_करोne(task, task->tk_msg.rpc_resp))
		वापस;

	trace_nfs4_sequence(clp, task->tk_status);
	अगर (task->tk_status < 0) अणु
		dprपूर्णांकk("%s ERROR %d\n", __func__, task->tk_status);
		अगर (refcount_पढ़ो(&clp->cl_count) == 1)
			जाओ out;

		अगर (nfs41_sequence_handle_errors(task, clp) == -EAGAIN) अणु
			rpc_restart_call_prepare(task);
			वापस;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("%s rpc_cred %p\n", __func__, task->tk_msg.rpc_cred);
out:
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल व्योम nfs41_sequence_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_sequence_data *calldata = data;
	काष्ठा nfs_client *clp = calldata->clp;
	काष्ठा nfs4_sequence_args *args;
	काष्ठा nfs4_sequence_res *res;

	args = task->tk_msg.rpc_argp;
	res = task->tk_msg.rpc_resp;

	nfs4_setup_sequence(clp, args, res, task);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs41_sequence_ops = अणु
	.rpc_call_करोne = nfs41_sequence_call_करोne,
	.rpc_call_prepare = nfs41_sequence_prepare,
	.rpc_release = nfs41_sequence_release,
पूर्ण;

अटल काष्ठा rpc_task *_nfs41_proc_sequence(काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred,
		काष्ठा nfs4_slot *slot,
		bool is_privileged)
अणु
	काष्ठा nfs4_sequence_data *calldata;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SEQUENCE],
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs41_sequence_ops,
		.flags = RPC_TASK_ASYNC | RPC_TASK_TIMEOUT,
	पूर्ण;
	काष्ठा rpc_task *ret;

	ret = ERR_PTR(-EIO);
	अगर (!refcount_inc_not_zero(&clp->cl_count))
		जाओ out_err;

	ret = ERR_PTR(-ENOMEM);
	calldata = kzalloc(माप(*calldata), GFP_NOFS);
	अगर (calldata == शून्य)
		जाओ out_put_clp;
	nfs4_init_sequence(&calldata->args, &calldata->res, 0, is_privileged);
	nfs4_sequence_attach_slot(&calldata->args, &calldata->res, slot);
	msg.rpc_argp = &calldata->args;
	msg.rpc_resp = &calldata->res;
	calldata->clp = clp;
	task_setup_data.callback_data = calldata;

	ret = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(ret))
		जाओ out_err;
	वापस ret;
out_put_clp:
	nfs_put_client(clp);
out_err:
	nfs41_release_slot(slot);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs41_proc_async_sequence(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred, अचिन्हित renew_flags)
अणु
	काष्ठा rpc_task *task;
	पूर्णांक ret = 0;

	अगर ((renew_flags & NFS4_RENEW_TIMEOUT) == 0)
		वापस -EAGAIN;
	task = _nfs41_proc_sequence(clp, cred, शून्य, false);
	अगर (IS_ERR(task))
		ret = PTR_ERR(task);
	अन्यथा
		rpc_put_task_async(task);
	dprपूर्णांकk("<-- %s status=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक nfs4_proc_sequence(काष्ठा nfs_client *clp, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा rpc_task *task;
	पूर्णांक ret;

	task = _nfs41_proc_sequence(clp, cred, शून्य, true);
	अगर (IS_ERR(task)) अणु
		ret = PTR_ERR(task);
		जाओ out;
	पूर्ण
	ret = rpc_रुको_क्रम_completion_task(task);
	अगर (!ret)
		ret = task->tk_status;
	rpc_put_task(task);
out:
	dprपूर्णांकk("<-- %s status=%d\n", __func__, ret);
	वापस ret;
पूर्ण

काष्ठा nfs4_reclaim_complete_data अणु
	काष्ठा nfs_client *clp;
	काष्ठा nfs41_reclaim_complete_args arg;
	काष्ठा nfs41_reclaim_complete_res res;
पूर्ण;

अटल व्योम nfs4_reclaim_complete_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_reclaim_complete_data *calldata = data;

	nfs4_setup_sequence(calldata->clp,
			&calldata->arg.seq_args,
			&calldata->res.seq_res,
			task);
पूर्ण

अटल पूर्णांक nfs41_reclaim_complete_handle_errors(काष्ठा rpc_task *task, काष्ठा nfs_client *clp)
अणु
	चयन(task->tk_status) अणु
	हाल 0:
		wake_up_all(&clp->cl_lock_रुकोq);
		fallthrough;
	हाल -NFS4ERR_COMPLETE_ALREADY:
	हाल -NFS4ERR_WRONG_CRED: /* What to करो here? */
		अवरोध;
	हाल -NFS4ERR_DELAY:
		rpc_delay(task, NFS4_POLL_RETRY_MAX);
		fallthrough;
	हाल -NFS4ERR_RETRY_UNCACHED_REP:
		वापस -EAGAIN;
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_DEADSESSION:
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
		अवरोध;
	शेष:
		nfs4_schedule_lease_recovery(clp);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nfs4_reclaim_complete_करोne(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs4_reclaim_complete_data *calldata = data;
	काष्ठा nfs_client *clp = calldata->clp;
	काष्ठा nfs4_sequence_res *res = &calldata->res.seq_res;

	dprपूर्णांकk("--> %s\n", __func__);
	अगर (!nfs41_sequence_करोne(task, res))
		वापस;

	trace_nfs4_reclaim_complete(clp, task->tk_status);
	अगर (nfs41_reclaim_complete_handle_errors(task, clp) == -EAGAIN) अणु
		rpc_restart_call_prepare(task);
		वापस;
	पूर्ण
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल व्योम nfs4_मुक्त_reclaim_complete_data(व्योम *data)
अणु
	काष्ठा nfs4_reclaim_complete_data *calldata = data;

	kमुक्त(calldata);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_reclaim_complete_call_ops = अणु
	.rpc_call_prepare = nfs4_reclaim_complete_prepare,
	.rpc_call_करोne = nfs4_reclaim_complete_करोne,
	.rpc_release = nfs4_मुक्त_reclaim_complete_data,
पूर्ण;

/*
 * Issue a global reclaim complete.
 */
अटल पूर्णांक nfs41_proc_reclaim_complete(काष्ठा nfs_client *clp,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_reclaim_complete_data *calldata;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RECLAIM_COMPLETE],
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clp->cl_rpcclient,
		.rpc_message = &msg,
		.callback_ops = &nfs4_reclaim_complete_call_ops,
		.flags = RPC_TASK_NO_ROUND_ROBIN,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("--> %s\n", __func__);
	calldata = kzalloc(माप(*calldata), GFP_NOFS);
	अगर (calldata == शून्य)
		जाओ out;
	calldata->clp = clp;
	calldata->arg.one_fs = 0;

	nfs4_init_sequence(&calldata->arg.seq_args, &calldata->res.seq_res, 0, 1);
	msg.rpc_argp = &calldata->arg;
	msg.rpc_resp = &calldata->res;
	task_setup_data.callback_data = calldata;
	status = nfs4_call_sync_custom(&task_setup_data);
out:
	dprपूर्णांकk("<-- %s status=%d\n", __func__, status);
	वापस status;
पूर्ण

अटल व्योम
nfs4_layoutget_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_layoutget *lgp = calldata;
	काष्ठा nfs_server *server = NFS_SERVER(lgp->args.inode);

	dprपूर्णांकk("--> %s\n", __func__);
	nfs4_setup_sequence(server->nfs_client, &lgp->args.seq_args,
				&lgp->res.seq_res, task);
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल व्योम nfs4_layoutget_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_layoutget *lgp = calldata;

	dprपूर्णांकk("--> %s\n", __func__);
	nfs41_sequence_process(task, &lgp->res.seq_res);
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल पूर्णांक
nfs4_layoutget_handle_exception(काष्ठा rpc_task *task,
		काष्ठा nfs4_layoutget *lgp, काष्ठा nfs4_exception *exception)
अणु
	काष्ठा inode *inode = lgp->args.inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा pnfs_layout_hdr *lo;
	पूर्णांक nfs4err = task->tk_status;
	पूर्णांक err, status = 0;
	LIST_HEAD(head);

	dprपूर्णांकk("--> %s tk_status => %d\n", __func__, -task->tk_status);

	nfs4_sequence_मुक्त_slot(&lgp->res.seq_res);

	चयन (nfs4err) अणु
	हाल 0:
		जाओ out;

	/*
	 * NFS4ERR_LAYOUTUNAVAILABLE means we are not supposed to use pnfs
	 * on the file. set tk_status to -ENODATA to tell upper layer to
	 * retry go inband.
	 */
	हाल -NFS4ERR_LAYOUTUNAVAILABLE:
		status = -ENODATA;
		जाओ out;
	/*
	 * NFS4ERR_BADLAYOUT means the MDS cannot वापस a layout of
	 * length lgp->args.minlength != 0 (see RFC5661 section 18.43.3).
	 */
	हाल -NFS4ERR_BADLAYOUT:
		status = -EOVERFLOW;
		जाओ out;
	/*
	 * NFS4ERR_LAYOUTTRYLATER is a conflict with another client
	 * (or clients) writing to the same RAID stripe except when
	 * the minlength argument is 0 (see RFC5661 section 18.43.3).
	 *
	 * Treat it like we would RECALLCONFLICT -- we retry क्रम a little
	 * जबतक, and then eventually give up.
	 */
	हाल -NFS4ERR_LAYOUTTRYLATER:
		अगर (lgp->args.minlength == 0) अणु
			status = -EOVERFLOW;
			जाओ out;
		पूर्ण
		status = -EBUSY;
		अवरोध;
	हाल -NFS4ERR_RECALLCONFLICT:
		status = -ERECALLCONFLICT;
		अवरोध;
	हाल -NFS4ERR_DELEG_REVOKED:
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_EXPIRED:
	हाल -NFS4ERR_BAD_STATEID:
		exception->समयout = 0;
		spin_lock(&inode->i_lock);
		lo = NFS_I(inode)->layout;
		/* If the खोलो stateid was bad, then recover it. */
		अगर (!lo || test_bit(NFS_LAYOUT_INVALID_STID, &lo->plh_flags) ||
		    !nfs4_stateid_match_other(&lgp->args.stateid, &lo->plh_stateid)) अणु
			spin_unlock(&inode->i_lock);
			exception->state = lgp->args.ctx->state;
			exception->stateid = &lgp->args.stateid;
			अवरोध;
		पूर्ण

		/*
		 * Mark the bad layout state as invalid, then retry
		 */
		pnfs_mark_layout_stateid_invalid(lo, &head);
		spin_unlock(&inode->i_lock);
		nfs_commit_inode(inode, 0);
		pnfs_मुक्त_lseg_list(&head);
		status = -EAGAIN;
		जाओ out;
	पूर्ण

	err = nfs4_handle_exception(server, nfs4err, exception);
	अगर (!status) अणु
		अगर (exception->retry)
			status = -EAGAIN;
		अन्यथा
			status = err;
	पूर्ण
out:
	dprपूर्णांकk("<-- %s\n", __func__);
	वापस status;
पूर्ण

माप_प्रकार max_response_pages(काष्ठा nfs_server *server)
अणु
	u32 max_resp_sz = server->nfs_client->cl_session->fc_attrs.max_resp_sz;
	वापस nfs_page_array_len(0, max_resp_sz);
पूर्ण

अटल व्योम nfs4_layoutget_release(व्योम *calldata)
अणु
	काष्ठा nfs4_layoutget *lgp = calldata;

	dprपूर्णांकk("--> %s\n", __func__);
	nfs4_sequence_मुक्त_slot(&lgp->res.seq_res);
	pnfs_layoutget_मुक्त(lgp);
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_layoutget_call_ops = अणु
	.rpc_call_prepare = nfs4_layoutget_prepare,
	.rpc_call_करोne = nfs4_layoutget_करोne,
	.rpc_release = nfs4_layoutget_release,
पूर्ण;

काष्ठा pnfs_layout_segment *
nfs4_proc_layoutget(काष्ठा nfs4_layoutget *lgp, दीर्घ *समयout)
अणु
	काष्ठा inode *inode = lgp->args.inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LAYOUTGET],
		.rpc_argp = &lgp->args,
		.rpc_resp = &lgp->res,
		.rpc_cred = lgp->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_layoutget_call_ops,
		.callback_data = lgp,
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;
	काष्ठा pnfs_layout_segment *lseg = शून्य;
	काष्ठा nfs4_exception exception = अणु
		.inode = inode,
		.समयout = *समयout,
	पूर्ण;
	पूर्णांक status = 0;

	dprपूर्णांकk("--> %s\n", __func__);

	/* nfs4_layoutget_release calls pnfs_put_layout_hdr */
	pnfs_get_layout_hdr(NFS_I(inode)->layout);

	nfs4_init_sequence(&lgp->args.seq_args, &lgp->res.seq_res, 0, 0);

	task = rpc_run_task(&task_setup_data);

	status = rpc_रुको_क्रम_completion_task(task);
	अगर (status != 0)
		जाओ out;

	अगर (task->tk_status < 0) अणु
		status = nfs4_layoutget_handle_exception(task, lgp, &exception);
		*समयout = exception.समयout;
	पूर्ण अन्यथा अगर (lgp->res.layoutp->len == 0) अणु
		status = -EAGAIN;
		*समयout = nfs4_update_delay(&exception.समयout);
	पूर्ण अन्यथा
		lseg = pnfs_layout_process(lgp);
out:
	trace_nfs4_layoutget(lgp->args.ctx,
			&lgp->args.range,
			&lgp->res.range,
			&lgp->res.stateid,
			status);

	rpc_put_task(task);
	dprपूर्णांकk("<-- %s status=%d\n", __func__, status);
	अगर (status)
		वापस ERR_PTR(status);
	वापस lseg;
पूर्ण

अटल व्योम
nfs4_layoutवापस_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_layoutवापस *lrp = calldata;

	dprपूर्णांकk("--> %s\n", __func__);
	nfs4_setup_sequence(lrp->clp,
			&lrp->args.seq_args,
			&lrp->res.seq_res,
			task);
	अगर (!pnfs_layout_is_valid(lrp->args.layout))
		rpc_निकास(task, 0);
पूर्ण

अटल व्योम nfs4_layoutवापस_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_layoutवापस *lrp = calldata;
	काष्ठा nfs_server *server;

	dprपूर्णांकk("--> %s\n", __func__);

	अगर (!nfs41_sequence_process(task, &lrp->res.seq_res))
		वापस;

	/*
	 * Was there an RPC level error? Assume the call succeeded,
	 * and that we need to release the layout
	 */
	अगर (task->tk_rpc_status != 0 && RPC_WAS_SENT(task)) अणु
		lrp->res.lrs_present = 0;
		वापस;
	पूर्ण

	server = NFS_SERVER(lrp->args.inode);
	चयन (task->tk_status) अणु
	हाल -NFS4ERR_OLD_STATEID:
		अगर (nfs4_layout_refresh_old_stateid(&lrp->args.stateid,
					&lrp->args.range,
					lrp->args.inode))
			जाओ out_restart;
		fallthrough;
	शेष:
		task->tk_status = 0;
		fallthrough;
	हाल 0:
		अवरोध;
	हाल -NFS4ERR_DELAY:
		अगर (nfs4_async_handle_error(task, server, शून्य, शून्य) != -EAGAIN)
			अवरोध;
		जाओ out_restart;
	पूर्ण
	dprपूर्णांकk("<-- %s\n", __func__);
	वापस;
out_restart:
	task->tk_status = 0;
	nfs4_sequence_मुक्त_slot(&lrp->res.seq_res);
	rpc_restart_call_prepare(task);
पूर्ण

अटल व्योम nfs4_layoutवापस_release(व्योम *calldata)
अणु
	काष्ठा nfs4_layoutवापस *lrp = calldata;
	काष्ठा pnfs_layout_hdr *lo = lrp->args.layout;

	dprपूर्णांकk("--> %s\n", __func__);
	pnfs_layoutवापस_मुक्त_lsegs(lo, &lrp->args.stateid, &lrp->args.range,
			lrp->res.lrs_present ? &lrp->res.stateid : शून्य);
	nfs4_sequence_मुक्त_slot(&lrp->res.seq_res);
	अगर (lrp->ld_निजी.ops && lrp->ld_निजी.ops->मुक्त)
		lrp->ld_निजी.ops->मुक्त(&lrp->ld_निजी);
	pnfs_put_layout_hdr(lrp->args.layout);
	nfs_iput_and_deactive(lrp->inode);
	put_cred(lrp->cred);
	kमुक्त(calldata);
	dprपूर्णांकk("<-- %s\n", __func__);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_layoutवापस_call_ops = अणु
	.rpc_call_prepare = nfs4_layoutवापस_prepare,
	.rpc_call_करोne = nfs4_layoutवापस_करोne,
	.rpc_release = nfs4_layoutवापस_release,
पूर्ण;

पूर्णांक nfs4_proc_layoutवापस(काष्ठा nfs4_layoutवापस *lrp, bool sync)
अणु
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LAYOUTRETURN],
		.rpc_argp = &lrp->args,
		.rpc_resp = &lrp->res,
		.rpc_cred = lrp->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = NFS_SERVER(lrp->args.inode)->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_layoutवापस_call_ops,
		.callback_data = lrp,
	पूर्ण;
	पूर्णांक status = 0;

	nfs4_state_protect(NFS_SERVER(lrp->args.inode)->nfs_client,
			NFS_SP4_MACH_CRED_PNFS_CLEANUP,
			&task_setup_data.rpc_client, &msg);

	dprपूर्णांकk("--> %s\n", __func__);
	lrp->inode = nfs_igrab_and_active(lrp->args.inode);
	अगर (!sync) अणु
		अगर (!lrp->inode) अणु
			nfs4_layoutवापस_release(lrp);
			वापस -EAGAIN;
		पूर्ण
		task_setup_data.flags |= RPC_TASK_ASYNC;
	पूर्ण
	अगर (!lrp->inode)
		nfs4_init_sequence(&lrp->args.seq_args, &lrp->res.seq_res, 1,
				   1);
	अन्यथा
		nfs4_init_sequence(&lrp->args.seq_args, &lrp->res.seq_res, 1,
				   0);
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	अगर (sync)
		status = task->tk_status;
	trace_nfs4_layoutवापस(lrp->args.inode, &lrp->args.stateid, status);
	dprपूर्णांकk("<-- %s status=%d\n", __func__, status);
	rpc_put_task(task);
	वापस status;
पूर्ण

अटल पूर्णांक
_nfs4_proc_getdeviceinfo(काष्ठा nfs_server *server,
		काष्ठा pnfs_device *pdev,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_getdeviceinfo_args args = अणु
		.pdev = pdev,
		.notअगरy_types = NOTIFY_DEVICEID4_CHANGE |
			NOTIFY_DEVICEID4_DELETE,
	पूर्ण;
	काष्ठा nfs4_getdeviceinfo_res res = अणु
		.pdev = pdev,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_GETDEVICEINFO],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = cred,
	पूर्ण;
	पूर्णांक status;

	dprपूर्णांकk("--> %s\n", __func__);
	status = nfs4_call_sync(server->client, server, &msg, &args.seq_args, &res.seq_res, 0);
	अगर (res.notअगरication & ~args.notअगरy_types)
		dprपूर्णांकk("%s: unsupported notification\n", __func__);
	अगर (res.notअगरication != args.notअगरy_types)
		pdev->nocache = 1;

	trace_nfs4_getdeviceinfo(server, &pdev->dev_id, status);

	dprपूर्णांकk("<-- %s status=%d\n", __func__, status);

	वापस status;
पूर्ण

पूर्णांक nfs4_proc_getdeviceinfo(काष्ठा nfs_server *server,
		काष्ठा pnfs_device *pdev,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;

	करो अणु
		err = nfs4_handle_exception(server,
					_nfs4_proc_getdeviceinfo(server, pdev, cred),
					&exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_proc_getdeviceinfo);

अटल व्योम nfs4_layoutcommit_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_layoutcommit_data *data = calldata;
	काष्ठा nfs_server *server = NFS_SERVER(data->args.inode);

	nfs4_setup_sequence(server->nfs_client,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
पूर्ण

अटल व्योम
nfs4_layoutcommit_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_layoutcommit_data *data = calldata;
	काष्ठा nfs_server *server = NFS_SERVER(data->args.inode);

	अगर (!nfs41_sequence_करोne(task, &data->res.seq_res))
		वापस;

	चयन (task->tk_status) अणु /* Just ignore these failures */
	हाल -NFS4ERR_DELEG_REVOKED: /* layout was recalled */
	हाल -NFS4ERR_BADIOMODE:     /* no IOMODE_RW layout क्रम range */
	हाल -NFS4ERR_BADLAYOUT:     /* no layout */
	हाल -NFS4ERR_GRACE:	    /* loca_recalim always false */
		task->tk_status = 0;
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		अगर (nfs4_async_handle_error(task, server, शून्य, शून्य) == -EAGAIN) अणु
			rpc_restart_call_prepare(task);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम nfs4_layoutcommit_release(व्योम *calldata)
अणु
	काष्ठा nfs4_layoutcommit_data *data = calldata;

	pnfs_cleanup_layoutcommit(data);
	nfs_post_op_update_inode_क्रमce_wcc(data->args.inode,
					   data->res.fattr);
	put_cred(data->cred);
	nfs_iput_and_deactive(data->inode);
	kमुक्त(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs4_layoutcommit_ops = अणु
	.rpc_call_prepare = nfs4_layoutcommit_prepare,
	.rpc_call_करोne = nfs4_layoutcommit_करोne,
	.rpc_release = nfs4_layoutcommit_release,
पूर्ण;

पूर्णांक
nfs4_proc_layoutcommit(काष्ठा nfs4_layoutcommit_data *data, bool sync)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LAYOUTCOMMIT],
		.rpc_argp = &data->args,
		.rpc_resp = &data->res,
		.rpc_cred = data->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.task = &data->task,
		.rpc_client = NFS_CLIENT(data->args.inode),
		.rpc_message = &msg,
		.callback_ops = &nfs4_layoutcommit_ops,
		.callback_data = data,
	पूर्ण;
	काष्ठा rpc_task *task;
	पूर्णांक status = 0;

	dprपूर्णांकk("NFS: initiating layoutcommit call. sync %d "
		"lbw: %llu inode %lu\n", sync,
		data->args.lastbytewritten,
		data->args.inode->i_ino);

	अगर (!sync) अणु
		data->inode = nfs_igrab_and_active(data->args.inode);
		अगर (data->inode == शून्य) अणु
			nfs4_layoutcommit_release(data);
			वापस -EAGAIN;
		पूर्ण
		task_setup_data.flags = RPC_TASK_ASYNC;
	पूर्ण
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 1, 0);
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	अगर (sync)
		status = task->tk_status;
	trace_nfs4_layoutcommit(data->args.inode, &data->args.stateid, status);
	dprपूर्णांकk("%s: status %d\n", __func__, status);
	rpc_put_task(task);
	वापस status;
पूर्ण

/*
 * Use the state managment nfs_client cl_rpcclient, which uses krb5i (अगर
 * possible) as per RFC3530bis and RFC5661 Security Considerations sections
 */
अटल पूर्णांक
_nfs41_proc_secinfo_no_name(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		    काष्ठा nfs_fsinfo *info,
		    काष्ठा nfs4_secinfo_flavors *flavors, bool use_पूर्णांकegrity)
अणु
	काष्ठा nfs41_secinfo_no_name_args args = अणु
		.style = SECINFO_STYLE_CURRENT_FH,
	पूर्ण;
	काष्ठा nfs4_secinfo_res res = अणु
		.flavors = flavors,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SECINFO_NO_NAME],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	काष्ठा nfs4_call_sync_data data = अणु
		.seq_server = server,
		.seq_args = &args.seq_args,
		.seq_res = &res.seq_res,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = server->nfs_client->cl_mvops->call_sync_ops,
		.callback_data = &data,
		.flags = RPC_TASK_NO_ROUND_ROBIN,
	पूर्ण;
	स्थिर काष्ठा cred *cred = शून्य;
	पूर्णांक status;

	अगर (use_पूर्णांकegrity) अणु
		task_setup.rpc_client = server->nfs_client->cl_rpcclient;

		cred = nfs4_get_clid_cred(server->nfs_client);
		msg.rpc_cred = cred;
	पूर्ण

	dprपूर्णांकk("--> %s\n", __func__);
	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 0);
	status = nfs4_call_sync_custom(&task_setup);
	dprपूर्णांकk("<-- %s status=%d\n", __func__, status);

	put_cred(cred);

	वापस status;
पूर्ण

अटल पूर्णांक
nfs41_proc_secinfo_no_name(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
			   काष्ठा nfs_fsinfo *info, काष्ठा nfs4_secinfo_flavors *flavors)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		/* first try using पूर्णांकegrity protection */
		err = -NFS4ERR_WRONGSEC;

		/* try to use पूर्णांकegrity protection with machine cred */
		अगर (_nfs4_is_पूर्णांकegrity_रक्षित(server->nfs_client))
			err = _nfs41_proc_secinfo_no_name(server, fhandle, info,
							  flavors, true);

		/*
		 * अगर unable to use पूर्णांकegrity protection, or SECINFO with
		 * पूर्णांकegrity protection वापसs NFS4ERR_WRONGSEC (which is
		 * disallowed by spec, but exists in deployed servers) use
		 * the current fileप्रणाली's rpc_client and the user cred.
		 */
		अगर (err == -NFS4ERR_WRONGSEC)
			err = _nfs41_proc_secinfo_no_name(server, fhandle, info,
							  flavors, false);

		चयन (err) अणु
		हाल 0:
		हाल -NFS4ERR_WRONGSEC:
		हाल -ENOTSUPP:
			जाओ out;
		शेष:
			err = nfs4_handle_exception(server, err, &exception);
		पूर्ण
	पूर्ण जबतक (exception.retry);
out:
	वापस err;
पूर्ण

अटल पूर्णांक
nfs41_find_root_sec(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		    काष्ठा nfs_fsinfo *info)
अणु
	पूर्णांक err;
	काष्ठा page *page;
	rpc_authflavor_t flavor = RPC_AUTH_MAXFLAVOR;
	काष्ठा nfs4_secinfo_flavors *flavors;
	काष्ठा nfs4_secinfo4 *secinfo;
	पूर्णांक i;

	page = alloc_page(GFP_KERNEL);
	अगर (!page) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	flavors = page_address(page);
	err = nfs41_proc_secinfo_no_name(server, fhandle, info, flavors);

	/*
	 * Fall back on "guess and check" method अगर
	 * the server करोesn't support SECINFO_NO_NAME
	 */
	अगर (err == -NFS4ERR_WRONGSEC || err == -ENOTSUPP) अणु
		err = nfs4_find_root_sec(server, fhandle, info);
		जाओ out_मुक्तpage;
	पूर्ण
	अगर (err)
		जाओ out_मुक्तpage;

	क्रम (i = 0; i < flavors->num_flavors; i++) अणु
		secinfo = &flavors->flavors[i];

		चयन (secinfo->flavor) अणु
		हाल RPC_AUTH_शून्य:
		हाल RPC_AUTH_UNIX:
		हाल RPC_AUTH_GSS:
			flavor = rpcauth_get_pseuकरोflavor(secinfo->flavor,
					&secinfo->flavor_info);
			अवरोध;
		शेष:
			flavor = RPC_AUTH_MAXFLAVOR;
			अवरोध;
		पूर्ण

		अगर (!nfs_auth_info_match(&server->auth_info, flavor))
			flavor = RPC_AUTH_MAXFLAVOR;

		अगर (flavor != RPC_AUTH_MAXFLAVOR) अणु
			err = nfs4_lookup_root_sec(server, fhandle,
						   info, flavor);
			अगर (!err)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (flavor == RPC_AUTH_MAXFLAVOR)
		err = -EPERM;

out_मुक्तpage:
	put_page(page);
	अगर (err == -EACCES)
		वापस -EPERM;
out:
	वापस err;
पूर्ण

अटल पूर्णांक _nfs41_test_stateid(काष्ठा nfs_server *server,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक status;
	काष्ठा nfs41_test_stateid_args args = अणु
		.stateid = stateid,
	पूर्ण;
	काष्ठा nfs41_test_stateid_res res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_TEST_STATEID],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_clnt *rpc_client = server->client;

	nfs4_state_protect(server->nfs_client, NFS_SP4_MACH_CRED_STATEID,
		&rpc_client, &msg);

	dprपूर्णांकk("NFS call  test_stateid %p\n", stateid);
	nfs4_init_sequence(&args.seq_args, &res.seq_res, 0, 1);
	status = nfs4_call_sync_sequence(rpc_client, server, &msg,
			&args.seq_args, &res.seq_res);
	अगर (status != NFS_OK) अणु
		dprपूर्णांकk("NFS reply test_stateid: failed, %d\n", status);
		वापस status;
	पूर्ण
	dprपूर्णांकk("NFS reply test_stateid: succeeded, %d\n", -res.status);
	वापस -res.status;
पूर्ण

अटल व्योम nfs4_handle_delay_or_session_error(काष्ठा nfs_server *server,
		पूर्णांक err, काष्ठा nfs4_exception *exception)
अणु
	exception->retry = 0;
	चयन(err) अणु
	हाल -NFS4ERR_DELAY:
	हाल -NFS4ERR_RETRY_UNCACHED_REP:
		nfs4_handle_exception(server, err, exception);
		अवरोध;
	हाल -NFS4ERR_BADSESSION:
	हाल -NFS4ERR_BADSLOT:
	हाल -NFS4ERR_BAD_HIGH_SLOT:
	हाल -NFS4ERR_CONN_NOT_BOUND_TO_SESSION:
	हाल -NFS4ERR_DEADSESSION:
		nfs4_करो_handle_exception(server, err, exception);
	पूर्ण
पूर्ण

/**
 * nfs41_test_stateid - perक्रमm a TEST_STATEID operation
 *
 * @server: server / transport on which to perक्रमm the operation
 * @stateid: state ID to test
 * @cred: credential
 *
 * Returns NFS_OK अगर the server recognizes that "stateid" is valid.
 * Otherwise a negative NFS4ERR value is वापसed अगर the operation
 * failed or the state ID is not currently valid.
 */
अटल पूर्णांक nfs41_test_stateid(काष्ठा nfs_server *server,
		nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfs4_exception exception = अणु
		.पूर्णांकerruptible = true,
	पूर्ण;
	पूर्णांक err;
	करो अणु
		err = _nfs41_test_stateid(server, stateid, cred);
		nfs4_handle_delay_or_session_error(server, err, &exception);
	पूर्ण जबतक (exception.retry);
	वापस err;
पूर्ण

काष्ठा nfs_मुक्त_stateid_data अणु
	काष्ठा nfs_server *server;
	काष्ठा nfs41_मुक्त_stateid_args args;
	काष्ठा nfs41_मुक्त_stateid_res res;
पूर्ण;

अटल व्योम nfs41_मुक्त_stateid_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_मुक्त_stateid_data *data = calldata;
	nfs4_setup_sequence(data->server->nfs_client,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
पूर्ण

अटल व्योम nfs41_मुक्त_stateid_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_मुक्त_stateid_data *data = calldata;

	nfs41_sequence_करोne(task, &data->res.seq_res);

	चयन (task->tk_status) अणु
	हाल -NFS4ERR_DELAY:
		अगर (nfs4_async_handle_error(task, data->server, शून्य, शून्य) == -EAGAIN)
			rpc_restart_call_prepare(task);
	पूर्ण
पूर्ण

अटल व्योम nfs41_मुक्त_stateid_release(व्योम *calldata)
अणु
	kमुक्त(calldata);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs41_मुक्त_stateid_ops = अणु
	.rpc_call_prepare = nfs41_मुक्त_stateid_prepare,
	.rpc_call_करोne = nfs41_मुक्त_stateid_करोne,
	.rpc_release = nfs41_मुक्त_stateid_release,
पूर्ण;

/**
 * nfs41_मुक्त_stateid - perक्रमm a FREE_STATEID operation
 *
 * @server: server / transport on which to perक्रमm the operation
 * @stateid: state ID to release
 * @cred: credential
 * @privileged: set to true अगर this call needs to be privileged
 *
 * Note: this function is always asynchronous.
 */
अटल पूर्णांक nfs41_मुक्त_stateid(काष्ठा nfs_server *server,
		स्थिर nfs4_stateid *stateid,
		स्थिर काष्ठा cred *cred,
		bool privileged)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_FREE_STATEID],
		.rpc_cred = cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs41_मुक्त_stateid_ops,
		.flags = RPC_TASK_ASYNC,
	पूर्ण;
	काष्ठा nfs_मुक्त_stateid_data *data;
	काष्ठा rpc_task *task;

	nfs4_state_protect(server->nfs_client, NFS_SP4_MACH_CRED_STATEID,
		&task_setup.rpc_client, &msg);

	dprपूर्णांकk("NFS call  free_stateid %p\n", stateid);
	data = kदो_स्मृति(माप(*data), GFP_NOFS);
	अगर (!data)
		वापस -ENOMEM;
	data->server = server;
	nfs4_stateid_copy(&data->args.stateid, stateid);

	task_setup.callback_data = data;

	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 1, privileged);
	task = rpc_run_task(&task_setup);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण

अटल व्योम
nfs41_मुक्त_lock_state(काष्ठा nfs_server *server, काष्ठा nfs4_lock_state *lsp)
अणु
	स्थिर काष्ठा cred *cred = lsp->ls_state->owner->so_cred;

	nfs41_मुक्त_stateid(server, &lsp->ls_stateid, cred, false);
	nfs4_मुक्त_lock_state(server, lsp);
पूर्ण

अटल bool nfs41_match_stateid(स्थिर nfs4_stateid *s1,
		स्थिर nfs4_stateid *s2)
अणु
	अगर (s1->type != s2->type)
		वापस false;

	अगर (स_भेद(s1->other, s2->other, माप(s1->other)) != 0)
		वापस false;

	अगर (s1->seqid == s2->seqid)
		वापस true;

	वापस s1->seqid == 0 || s2->seqid == 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल bool nfs4_match_stateid(स्थिर nfs4_stateid *s1,
		स्थिर nfs4_stateid *s2)
अणु
	वापस nfs4_stateid_match(s1, s2);
पूर्ण


अटल स्थिर काष्ठा nfs4_state_recovery_ops nfs40_reboot_recovery_ops = अणु
	.owner_flag_bit = NFS_OWNER_RECLAIM_REBOOT,
	.state_flag_bit	= NFS_STATE_RECLAIM_REBOOT,
	.recover_खोलो	= nfs4_खोलो_reclaim,
	.recover_lock	= nfs4_lock_reclaim,
	.establish_clid = nfs4_init_clientid,
	.detect_trunking = nfs40_discover_server_trunking,
पूर्ण;

#अगर defined(CONFIG_NFS_V4_1)
अटल स्थिर काष्ठा nfs4_state_recovery_ops nfs41_reboot_recovery_ops = अणु
	.owner_flag_bit = NFS_OWNER_RECLAIM_REBOOT,
	.state_flag_bit	= NFS_STATE_RECLAIM_REBOOT,
	.recover_खोलो	= nfs4_खोलो_reclaim,
	.recover_lock	= nfs4_lock_reclaim,
	.establish_clid = nfs41_init_clientid,
	.reclaim_complete = nfs41_proc_reclaim_complete,
	.detect_trunking = nfs41_discover_server_trunking,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल स्थिर काष्ठा nfs4_state_recovery_ops nfs40_nograce_recovery_ops = अणु
	.owner_flag_bit = NFS_OWNER_RECLAIM_NOGRACE,
	.state_flag_bit	= NFS_STATE_RECLAIM_NOGRACE,
	.recover_खोलो	= nfs40_खोलो_expired,
	.recover_lock	= nfs4_lock_expired,
	.establish_clid = nfs4_init_clientid,
पूर्ण;

#अगर defined(CONFIG_NFS_V4_1)
अटल स्थिर काष्ठा nfs4_state_recovery_ops nfs41_nograce_recovery_ops = अणु
	.owner_flag_bit = NFS_OWNER_RECLAIM_NOGRACE,
	.state_flag_bit	= NFS_STATE_RECLAIM_NOGRACE,
	.recover_खोलो	= nfs41_खोलो_expired,
	.recover_lock	= nfs41_lock_expired,
	.establish_clid = nfs41_init_clientid,
पूर्ण;
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल स्थिर काष्ठा nfs4_state_मुख्यtenance_ops nfs40_state_renewal_ops = अणु
	.sched_state_renewal = nfs4_proc_async_renew,
	.get_state_renewal_cred = nfs4_get_renew_cred,
	.renew_lease = nfs4_proc_renew,
पूर्ण;

#अगर defined(CONFIG_NFS_V4_1)
अटल स्थिर काष्ठा nfs4_state_मुख्यtenance_ops nfs41_state_renewal_ops = अणु
	.sched_state_renewal = nfs41_proc_async_sequence,
	.get_state_renewal_cred = nfs4_get_machine_cred,
	.renew_lease = nfs4_proc_sequence,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा nfs4_mig_recovery_ops nfs40_mig_recovery_ops = अणु
	.get_locations = _nfs40_proc_get_locations,
	.fsid_present = _nfs40_proc_fsid_present,
पूर्ण;

#अगर defined(CONFIG_NFS_V4_1)
अटल स्थिर काष्ठा nfs4_mig_recovery_ops nfs41_mig_recovery_ops = अणु
	.get_locations = _nfs41_proc_get_locations,
	.fsid_present = _nfs41_proc_fsid_present,
पूर्ण;
#पूर्ण_अगर	/* CONFIG_NFS_V4_1 */

अटल स्थिर काष्ठा nfs4_minor_version_ops nfs_v4_0_minor_ops = अणु
	.minor_version = 0,
	.init_caps = NFS_CAP_READसूचीPLUS
		| NFS_CAP_ATOMIC_OPEN
		| NFS_CAP_POSIX_LOCK,
	.init_client = nfs40_init_client,
	.shutकरोwn_client = nfs40_shutकरोwn_client,
	.match_stateid = nfs4_match_stateid,
	.find_root_sec = nfs4_find_root_sec,
	.मुक्त_lock_state = nfs4_release_lockowner,
	.test_and_मुक्त_expired = nfs40_test_and_मुक्त_expired_stateid,
	.alloc_seqid = nfs_alloc_seqid,
	.call_sync_ops = &nfs40_call_sync_ops,
	.reboot_recovery_ops = &nfs40_reboot_recovery_ops,
	.nograce_recovery_ops = &nfs40_nograce_recovery_ops,
	.state_renewal_ops = &nfs40_state_renewal_ops,
	.mig_recovery_ops = &nfs40_mig_recovery_ops,
पूर्ण;

#अगर defined(CONFIG_NFS_V4_1)
अटल काष्ठा nfs_seqid *
nfs_alloc_no_seqid(काष्ठा nfs_seqid_counter *arg1, gfp_t arg2)
अणु
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा nfs4_minor_version_ops nfs_v4_1_minor_ops = अणु
	.minor_version = 1,
	.init_caps = NFS_CAP_READसूचीPLUS
		| NFS_CAP_ATOMIC_OPEN
		| NFS_CAP_POSIX_LOCK
		| NFS_CAP_STATEID_NFSV41
		| NFS_CAP_ATOMIC_OPEN_V1
		| NFS_CAP_LGOPEN,
	.init_client = nfs41_init_client,
	.shutकरोwn_client = nfs41_shutकरोwn_client,
	.match_stateid = nfs41_match_stateid,
	.find_root_sec = nfs41_find_root_sec,
	.मुक्त_lock_state = nfs41_मुक्त_lock_state,
	.test_and_मुक्त_expired = nfs41_test_and_मुक्त_expired_stateid,
	.alloc_seqid = nfs_alloc_no_seqid,
	.session_trunk = nfs4_test_session_trunk,
	.call_sync_ops = &nfs41_call_sync_ops,
	.reboot_recovery_ops = &nfs41_reboot_recovery_ops,
	.nograce_recovery_ops = &nfs41_nograce_recovery_ops,
	.state_renewal_ops = &nfs41_state_renewal_ops,
	.mig_recovery_ops = &nfs41_mig_recovery_ops,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_NFS_V4_2)
अटल स्थिर काष्ठा nfs4_minor_version_ops nfs_v4_2_minor_ops = अणु
	.minor_version = 2,
	.init_caps = NFS_CAP_READसूचीPLUS
		| NFS_CAP_ATOMIC_OPEN
		| NFS_CAP_POSIX_LOCK
		| NFS_CAP_STATEID_NFSV41
		| NFS_CAP_ATOMIC_OPEN_V1
		| NFS_CAP_LGOPEN
		| NFS_CAP_ALLOCATE
		| NFS_CAP_COPY
		| NFS_CAP_OFFLOAD_CANCEL
		| NFS_CAP_COPY_NOTIFY
		| NFS_CAP_DEALLOCATE
		| NFS_CAP_SEEK
		| NFS_CAP_LAYOUTSTATS
		| NFS_CAP_CLONE
		| NFS_CAP_LAYOUTERROR
		| NFS_CAP_READ_PLUS,
	.init_client = nfs41_init_client,
	.shutकरोwn_client = nfs41_shutकरोwn_client,
	.match_stateid = nfs41_match_stateid,
	.find_root_sec = nfs41_find_root_sec,
	.मुक्त_lock_state = nfs41_मुक्त_lock_state,
	.call_sync_ops = &nfs41_call_sync_ops,
	.test_and_मुक्त_expired = nfs41_test_and_मुक्त_expired_stateid,
	.alloc_seqid = nfs_alloc_no_seqid,
	.session_trunk = nfs4_test_session_trunk,
	.reboot_recovery_ops = &nfs41_reboot_recovery_ops,
	.nograce_recovery_ops = &nfs41_nograce_recovery_ops,
	.state_renewal_ops = &nfs41_state_renewal_ops,
	.mig_recovery_ops = &nfs41_mig_recovery_ops,
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा nfs4_minor_version_ops *nfs_v4_minor_ops[] = अणु
	[0] = &nfs_v4_0_minor_ops,
#अगर defined(CONFIG_NFS_V4_1)
	[1] = &nfs_v4_1_minor_ops,
#पूर्ण_अगर
#अगर defined(CONFIG_NFS_V4_2)
	[2] = &nfs_v4_2_minor_ops,
#पूर्ण_अगर
पूर्ण;

अटल sमाप_प्रकार nfs4_listxattr(काष्ठा dentry *dentry, अक्षर *list, माप_प्रकार size)
अणु
	sमाप_प्रकार error, error2, error3;

	error = generic_listxattr(dentry, list, size);
	अगर (error < 0)
		वापस error;
	अगर (list) अणु
		list += error;
		size -= error;
	पूर्ण

	error2 = nfs4_listxattr_nfs4_label(d_inode(dentry), list, size);
	अगर (error2 < 0)
		वापस error2;

	अगर (list) अणु
		list += error2;
		size -= error2;
	पूर्ण

	error3 = nfs4_listxattr_nfs4_user(d_inode(dentry), list, size);
	अगर (error3 < 0)
		वापस error3;

	वापस error + error2 + error3;
पूर्ण

अटल स्थिर काष्ठा inode_operations nfs4_dir_inode_operations = अणु
	.create		= nfs_create,
	.lookup		= nfs_lookup,
	.atomic_खोलो	= nfs_atomic_खोलो,
	.link		= nfs_link,
	.unlink		= nfs_unlink,
	.symlink	= nfs_symlink,
	.सूची_गढ़ो		= nfs_सूची_गढ़ो,
	.सूची_हटाओ		= nfs_सूची_हटाओ,
	.mknod		= nfs_mknod,
	.नाम		= nfs_नाम,
	.permission	= nfs_permission,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
	.listxattr	= nfs4_listxattr,
पूर्ण;

अटल स्थिर काष्ठा inode_operations nfs4_file_inode_operations = अणु
	.permission	= nfs_permission,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
	.listxattr	= nfs4_listxattr,
पूर्ण;

स्थिर काष्ठा nfs_rpc_ops nfs_v4_clientops = अणु
	.version	= 4,			/* protocol version */
	.dentry_ops	= &nfs4_dentry_operations,
	.dir_inode_ops	= &nfs4_dir_inode_operations,
	.file_inode_ops	= &nfs4_file_inode_operations,
	.file_ops	= &nfs4_file_operations,
	.getroot	= nfs4_proc_get_root,
	.submount	= nfs4_submount,
	.try_get_tree	= nfs4_try_get_tree,
	.getattr	= nfs4_proc_getattr,
	.setattr	= nfs4_proc_setattr,
	.lookup		= nfs4_proc_lookup,
	.lookupp	= nfs4_proc_lookupp,
	.access		= nfs4_proc_access,
	.पढ़ोlink	= nfs4_proc_पढ़ोlink,
	.create		= nfs4_proc_create,
	.हटाओ		= nfs4_proc_हटाओ,
	.unlink_setup	= nfs4_proc_unlink_setup,
	.unlink_rpc_prepare = nfs4_proc_unlink_rpc_prepare,
	.unlink_करोne	= nfs4_proc_unlink_करोne,
	.नाम_setup	= nfs4_proc_नाम_setup,
	.नाम_rpc_prepare = nfs4_proc_नाम_rpc_prepare,
	.नाम_करोne	= nfs4_proc_नाम_करोne,
	.link		= nfs4_proc_link,
	.symlink	= nfs4_proc_symlink,
	.सूची_गढ़ो		= nfs4_proc_सूची_गढ़ो,
	.सूची_हटाओ		= nfs4_proc_सूची_हटाओ,
	.सूची_पढ़ो	= nfs4_proc_सूची_पढ़ो,
	.mknod		= nfs4_proc_mknod,
	.statfs		= nfs4_proc_statfs,
	.fsinfo		= nfs4_proc_fsinfo,
	.pathconf	= nfs4_proc_pathconf,
	.set_capabilities = nfs4_server_capabilities,
	.decode_dirent	= nfs4_decode_dirent,
	.pgio_rpc_prepare = nfs4_proc_pgio_rpc_prepare,
	.पढ़ो_setup	= nfs4_proc_पढ़ो_setup,
	.पढ़ो_करोne	= nfs4_पढ़ो_करोne,
	.ग_लिखो_setup	= nfs4_proc_ग_लिखो_setup,
	.ग_लिखो_करोne	= nfs4_ग_लिखो_करोne,
	.commit_setup	= nfs4_proc_commit_setup,
	.commit_rpc_prepare = nfs4_proc_commit_rpc_prepare,
	.commit_करोne	= nfs4_commit_करोne,
	.lock		= nfs4_proc_lock,
	.clear_acl_cache = nfs4_zap_acl_attr,
	.बंद_context  = nfs4_बंद_context,
	.खोलो_context	= nfs4_atomic_खोलो,
	.have_delegation = nfs4_have_delegation,
	.alloc_client	= nfs4_alloc_client,
	.init_client	= nfs4_init_client,
	.मुक्त_client	= nfs4_मुक्त_client,
	.create_server	= nfs4_create_server,
	.clone_server	= nfs_clone_server,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler nfs4_xattr_nfs4_acl_handler = अणु
	.name	= XATTR_NAME_NFSV4_ACL,
	.list	= nfs4_xattr_list_nfs4_acl,
	.get	= nfs4_xattr_get_nfs4_acl,
	.set	= nfs4_xattr_set_nfs4_acl,
पूर्ण;

#अगर_घोषित CONFIG_NFS_V4_2
अटल स्थिर काष्ठा xattr_handler nfs4_xattr_nfs4_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.get	= nfs4_xattr_get_nfs4_user,
	.set	= nfs4_xattr_set_nfs4_user,
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा xattr_handler *nfs4_xattr_handlers[] = अणु
	&nfs4_xattr_nfs4_acl_handler,
#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
	&nfs4_xattr_nfs4_label_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NFS_V4_2
	&nfs4_xattr_nfs4_user_handler,
#पूर्ण_अगर
	शून्य
पूर्ण;
