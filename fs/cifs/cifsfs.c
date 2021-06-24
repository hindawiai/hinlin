<शैली गुरु>
/*
 *   fs/cअगरs/cअगरsfs.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   Common Internet FileSystem (CIFS) client
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* Note that BB means BUGBUG (ie something to fix eventually) */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vfs.h>
#समावेश <linux/mempool.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/namei.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/uuid.h>
#समावेश <linux/xattr.h>
#समावेश <net/ipv6.h>
#समावेश "cifsfs.h"
#समावेश "cifspdu.h"
#घोषणा DECLARE_GLOBALS_HERE
#समावेश "cifsglob.h"
#समावेश "cifsproto.h"
#समावेश "cifs_debug.h"
#समावेश "cifs_fs_sb.h"
#समावेश <linux/mm.h>
#समावेश <linux/key-type.h>
#समावेश "cifs_spnego.h"
#समावेश "fscache.h"
#समावेश "smb2pdu.h"
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
#समावेश "dfs_cache.h"
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
#समावेश "netlink.h"
#पूर्ण_अगर
#समावेश "fs_context.h"

/*
 * DOS dates from 1980/1/1 through 2107/12/31
 * Protocol specअगरications indicate the range should be to 119, which
 * limits maximum year to 2099. But this range has not been checked.
 */
#घोषणा SMB_DATE_MAX (127<<9 | 12<<5 | 31)
#घोषणा SMB_DATE_MIN (0<<9 | 1<<5 | 1)
#घोषणा SMB_TIME_MAX (23<<11 | 59<<5 | 29)

पूर्णांक cअगरsFYI = 0;
bool traceSMB;
bool enable_oplocks = true;
bool linuxExtEnabled = true;
bool lookupCacheEnabled = true;
bool disable_legacy_dialects; /* false by शेष */
bool enable_gcm_256 = true;
bool require_gcm_256; /* false by शेष */
अचिन्हित पूर्णांक global_secflags = CIFSSEC_DEF;
/* अचिन्हित पूर्णांक ntlmv2_support = 0; */
अचिन्हित पूर्णांक sign_CIFS_PDUs = 1;
अटल स्थिर काष्ठा super_operations cअगरs_super_ops;
अचिन्हित पूर्णांक CIFSMaxBufSize = CIFS_MAX_MSGSIZE;
module_param(CIFSMaxBufSize, uपूर्णांक, 0444);
MODULE_PARM_DESC(CIFSMaxBufSize, "Network buffer size (not including header) "
				 "for CIFS requests. "
				 "Default: 16384 Range: 8192 to 130048");
अचिन्हित पूर्णांक cअगरs_min_rcv = CIFS_MIN_RCV_POOL;
module_param(cअगरs_min_rcv, uपूर्णांक, 0444);
MODULE_PARM_DESC(cअगरs_min_rcv, "Network buffers in pool. Default: 4 Range: "
				"1 to 64");
अचिन्हित पूर्णांक cअगरs_min_small = 30;
module_param(cअगरs_min_small, uपूर्णांक, 0444);
MODULE_PARM_DESC(cअगरs_min_small, "Small network buffers in pool. Default: 30 "
				 "Range: 2 to 256");
अचिन्हित पूर्णांक cअगरs_max_pending = CIFS_MAX_REQ;
module_param(cअगरs_max_pending, uपूर्णांक, 0444);
MODULE_PARM_DESC(cअगरs_max_pending, "Simultaneous requests to server for "
				   "CIFS/SMB1 dialect (N/A for SMB3) "
				   "Default: 32767 Range: 2 to 32767.");
#अगर_घोषित CONFIG_CIFS_STATS2
अचिन्हित पूर्णांक slow_rsp_threshold = 1;
module_param(slow_rsp_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(slow_rsp_threshold, "Amount of time (in seconds) to wait "
				   "before logging that a response is delayed. "
				   "Default: 1 (if set to 0 disables msg).");
#पूर्ण_अगर /* STATS2 */

module_param(enable_oplocks, bool, 0644);
MODULE_PARM_DESC(enable_oplocks, "Enable or disable oplocks. Default: y/Y/1");

module_param(enable_gcm_256, bool, 0644);
MODULE_PARM_DESC(enable_gcm_256, "Enable requesting strongest (256 bit) GCM encryption. Default: n/N/0");

module_param(require_gcm_256, bool, 0644);
MODULE_PARM_DESC(require_gcm_256, "Require strongest (256 bit) GCM encryption. Default: n/N/0");

module_param(disable_legacy_dialects, bool, 0644);
MODULE_PARM_DESC(disable_legacy_dialects, "To improve security it may be "
				  "helpful to restrict the ability to "
				  "override the default dialects (SMB2.1, "
				  "SMB3 and SMB3.02) on mount with old "
				  "dialects (CIFS/SMB1 and SMB2) since "
				  "vers=1.0 (CIFS/SMB1) and vers=2.0 are weaker"
				  " and less secure. Default: n/N/0");

बाह्य mempool_t *cअगरs_sm_req_poolp;
बाह्य mempool_t *cअगरs_req_poolp;
बाह्य mempool_t *cअगरs_mid_poolp;

काष्ठा workqueue_काष्ठा	*cअगरsiod_wq;
काष्ठा workqueue_काष्ठा	*decrypt_wq;
काष्ठा workqueue_काष्ठा	*fileinfo_put_wq;
काष्ठा workqueue_काष्ठा	*cअगरsoplockd_wq;
काष्ठा workqueue_काष्ठा	*deferredबंद_wq;
__u32 cअगरs_lock_secret;

/*
 * Bumps refcount क्रम cअगरs super block.
 * Note that it should be only called अगर a referece to VFS super block is
 * alपढ़ोy held, e.g. in खोलो-type syscalls context. Otherwise it can race with
 * atomic_dec_and_test in deactivate_locked_super.
 */
व्योम
cअगरs_sb_active(काष्ठा super_block *sb)
अणु
	काष्ठा cअगरs_sb_info *server = CIFS_SB(sb);

	अगर (atomic_inc_वापस(&server->active) == 1)
		atomic_inc(&sb->s_active);
पूर्ण

व्योम
cअगरs_sb_deactive(काष्ठा super_block *sb)
अणु
	काष्ठा cअगरs_sb_info *server = CIFS_SB(sb);

	अगर (atomic_dec_and_test(&server->active))
		deactivate_super(sb);
पूर्ण

अटल पूर्णांक
cअगरs_पढ़ो_super(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode;
	काष्ठा cअगरs_sb_info *cअगरs_sb;
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा बारpec64 ts;
	पूर्णांक rc = 0;

	cअगरs_sb = CIFS_SB(sb);
	tcon = cअगरs_sb_master_tcon(cअगरs_sb);

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_POSIXACL)
		sb->s_flags |= SB_POSIXACL;

	अगर (tcon->snapshot_समय)
		sb->s_flags |= SB_RDONLY;

	अगर (tcon->ses->capabilities & tcon->ses->server->vals->cap_large_files)
		sb->s_maxbytes = MAX_LFS_खाताSIZE;
	अन्यथा
		sb->s_maxbytes = MAX_NON_LFS;

	/*
	 * Some very old servers like DOS and OS/2 used 2 second granularity
	 * (जबतक all current servers use 100ns granularity - see MS-DTYP)
	 * but 1 second is the maximum allowed granularity क्रम the VFS
	 * so क्रम old servers set समय granularity to 1 second जबतक क्रम
	 * everything अन्यथा (current servers) set it to 100ns.
	 */
	अगर ((tcon->ses->server->vals->protocol_id == SMB10_PROT_ID) &&
	    ((tcon->ses->capabilities &
	      tcon->ses->server->vals->cap_nt_find) == 0) &&
	    !tcon->unix_ext) अणु
		sb->s_समय_gran = 1000000000; /* 1 second is max allowed gran */
		ts = cnvrtDosUnixTm(cpu_to_le16(SMB_DATE_MIN), 0, 0);
		sb->s_समय_min = ts.tv_sec;
		ts = cnvrtDosUnixTm(cpu_to_le16(SMB_DATE_MAX),
				    cpu_to_le16(SMB_TIME_MAX), 0);
		sb->s_समय_max = ts.tv_sec;
	पूर्ण अन्यथा अणु
		/*
		 * Almost every server, including all SMB2+, uses DCE TIME
		 * ie 100 nanosecond units, since 1601.  See MS-DTYP and MS-FSCC
		 */
		sb->s_समय_gran = 100;
		ts = cअगरs_NTसमयToUnix(0);
		sb->s_समय_min = ts.tv_sec;
		ts = cअगरs_NTसमयToUnix(cpu_to_le64(S64_MAX));
		sb->s_समय_max = ts.tv_sec;
	पूर्ण

	sb->s_magic = CIFS_MAGIC_NUMBER;
	sb->s_op = &cअगरs_super_ops;
	sb->s_xattr = cअगरs_xattr_handlers;
	rc = super_setup_bdi(sb);
	अगर (rc)
		जाओ out_no_root;
	/* tune पढ़ोahead according to rsize अगर पढ़ोahead size not set on mount */
	अगर (cअगरs_sb->ctx->rasize)
		sb->s_bdi->ra_pages = cअगरs_sb->ctx->rasize / PAGE_SIZE;
	अन्यथा
		sb->s_bdi->ra_pages = cअगरs_sb->ctx->rsize / PAGE_SIZE;

	sb->s_blocksize = CIFS_MAX_MSGSIZE;
	sb->s_blocksize_bits = 14;	/* शेष 2**14 = CIFS_MAX_MSGSIZE */
	inode = cअगरs_root_iget(sb);

	अगर (IS_ERR(inode)) अणु
		rc = PTR_ERR(inode);
		जाओ out_no_root;
	पूर्ण

	अगर (tcon->noहाल)
		sb->s_d_op = &cअगरs_ci_dentry_ops;
	अन्यथा
		sb->s_d_op = &cअगरs_dentry_ops;

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root) अणु
		rc = -ENOMEM;
		जाओ out_no_root;
	पूर्ण

#अगर_घोषित CONFIG_CIFS_NFSD_EXPORT
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM) अणु
		cअगरs_dbg(FYI, "export ops supported\n");
		sb->s_export_op = &cअगरs_export_ops;
	पूर्ण
#पूर्ण_अगर /* CONFIG_CIFS_NFSD_EXPORT */

	वापस 0;

out_no_root:
	cअगरs_dbg(VFS, "%s: get root inode failed\n", __func__);
	वापस rc;
पूर्ण

अटल व्योम cअगरs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_tcon *tcon;
	काष्ठा cached_fid *cfid;

	/*
	 * We ned to release all dentries क्रम the cached directories
	 * beक्रमe we समाप्त the sb.
	 */
	अगर (cअगरs_sb->root) अणु
		dput(cअगरs_sb->root);
		cअगरs_sb->root = शून्य;
	पूर्ण
	tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	अगर (tcon) अणु
		cfid = &tcon->crfid;
		mutex_lock(&cfid->fid_mutex);
		अगर (cfid->dentry) अणु

			dput(cfid->dentry);
			cfid->dentry = शून्य;
		पूर्ण
		mutex_unlock(&cfid->fid_mutex);
	पूर्ण

	समाप्त_anon_super(sb);
	cअगरs_umount(cअगरs_sb);
पूर्ण

अटल पूर्णांक
cअगरs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc = 0;

	xid = get_xid();

	अगर (le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength) > 0)
		buf->f_namelen =
		       le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength);
	अन्यथा
		buf->f_namelen = PATH_MAX;

	buf->f_fsid.val[0] = tcon->vol_serial_number;
	/* are using part of create समय क्रम more अक्रमomness, see man statfs */
	buf->f_fsid.val[1] =  (पूर्णांक)le64_to_cpu(tcon->vol_create_समय);

	buf->f_files = 0;	/* undefined */
	buf->f_fमुक्त = 0;	/* unlimited */

	अगर (server->ops->queryfs)
		rc = server->ops->queryfs(xid, tcon, cअगरs_sb, buf);

	मुक्त_xid(xid);
	वापस rc;
पूर्ण

अटल दीर्घ cअगरs_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t off, loff_t len)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_खाता_SB(file);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा TCP_Server_Info *server = tcon->ses->server;

	अगर (server->ops->fallocate)
		वापस server->ops->fallocate(file, tcon, mode, off, len);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक cअगरs_permission(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb;

	cअगरs_sb = CIFS_SB(inode->i_sb);

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_PERM) अणु
		अगर ((mask & MAY_EXEC) && !execute_ok(inode))
			वापस -EACCES;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा /* file mode might have been restricted at mount समय
		on the client (above and beyond ACL on servers) क्रम
		servers which करो not support setting and viewing mode bits,
		so allowing client to check permissions is useful */
		वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

अटल काष्ठा kmem_cache *cअगरs_inode_cachep;
अटल काष्ठा kmem_cache *cअगरs_req_cachep;
अटल काष्ठा kmem_cache *cअगरs_mid_cachep;
अटल काष्ठा kmem_cache *cअगरs_sm_req_cachep;
mempool_t *cअगरs_sm_req_poolp;
mempool_t *cअगरs_req_poolp;
mempool_t *cअगरs_mid_poolp;

अटल काष्ठा inode *
cअगरs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा cअगरsInodeInfo *cअगरs_inode;
	cअगरs_inode = kmem_cache_alloc(cअगरs_inode_cachep, GFP_KERNEL);
	अगर (!cअगरs_inode)
		वापस शून्य;
	cअगरs_inode->cअगरsAttrs = 0x20;	/* शेष */
	cअगरs_inode->समय = 0;
	/*
	 * Until the file is खोलो and we have gotten oplock info back from the
	 * server, can not assume caching of file data or metadata.
	 */
	cअगरs_set_oplock_level(cअगरs_inode, 0);
	cअगरs_inode->flags = 0;
	spin_lock_init(&cअगरs_inode->ग_लिखोrs_lock);
	cअगरs_inode->ग_लिखोrs = 0;
	cअगरs_inode->vfs_inode.i_blkbits = 14;  /* 2**14 = CIFS_MAX_MSGSIZE */
	cअगरs_inode->server_eof = 0;
	cअगरs_inode->uniqueid = 0;
	cअगरs_inode->createसमय = 0;
	cअगरs_inode->epoch = 0;
	spin_lock_init(&cअगरs_inode->खोलो_file_lock);
	generate_अक्रमom_uuid(cअगरs_inode->lease_key);

	/*
	 * Can not set i_flags here - they get immediately overwritten to zero
	 * by the VFS.
	 */
	/* cअगरs_inode->vfs_inode.i_flags = S_NOATIME | S_NOCMTIME; */
	INIT_LIST_HEAD(&cअगरs_inode->खोलोFileList);
	INIT_LIST_HEAD(&cअगरs_inode->llist);
	INIT_LIST_HEAD(&cअगरs_inode->deferred_बंदs);
	spin_lock_init(&cअगरs_inode->deferred_lock);
	वापस &cअगरs_inode->vfs_inode;
पूर्ण

अटल व्योम
cअगरs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(cअगरs_inode_cachep, CIFS_I(inode));
पूर्ण

अटल व्योम
cअगरs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	cअगरs_fscache_release_inode_cookie(inode);
पूर्ण

अटल व्योम
cअगरs_show_address(काष्ठा seq_file *s, काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा sockaddr_in *sa = (काष्ठा sockaddr_in *) &server->dstaddr;
	काष्ठा sockaddr_in6 *sa6 = (काष्ठा sockaddr_in6 *) &server->dstaddr;

	seq_माला_दो(s, ",addr=");

	चयन (server->dstaddr.ss_family) अणु
	हाल AF_INET:
		seq_म_लिखो(s, "%pI4", &sa->sin_addr.s_addr);
		अवरोध;
	हाल AF_INET6:
		seq_म_लिखो(s, "%pI6", &sa6->sin6_addr.s6_addr);
		अगर (sa6->sin6_scope_id)
			seq_म_लिखो(s, "%%%u", sa6->sin6_scope_id);
		अवरोध;
	शेष:
		seq_माला_दो(s, "(unknown)");
	पूर्ण
	अगर (server->rdma)
		seq_माला_दो(s, ",rdma");
पूर्ण

अटल व्योम
cअगरs_show_security(काष्ठा seq_file *s, काष्ठा cअगरs_ses *ses)
अणु
	अगर (ses->sectype == Unspecअगरied) अणु
		अगर (ses->user_name == शून्य)
			seq_माला_दो(s, ",sec=none");
		वापस;
	पूर्ण

	seq_माला_दो(s, ",sec=");

	चयन (ses->sectype) अणु
	हाल LANMAN:
		seq_माला_दो(s, "lanman");
		अवरोध;
	हाल NTLMv2:
		seq_माला_दो(s, "ntlmv2");
		अवरोध;
	हाल NTLM:
		seq_माला_दो(s, "ntlm");
		अवरोध;
	हाल Kerberos:
		seq_माला_दो(s, "krb5");
		अवरोध;
	हाल RawNTLMSSP:
		seq_माला_दो(s, "ntlmssp");
		अवरोध;
	शेष:
		/* shouldn't ever happen */
		seq_माला_दो(s, "unknown");
		अवरोध;
	पूर्ण

	अगर (ses->sign)
		seq_माला_दो(s, "i");

	अगर (ses->sectype == Kerberos)
		seq_म_लिखो(s, ",cruid=%u",
			   from_kuid_munged(&init_user_ns, ses->cred_uid));
पूर्ण

अटल व्योम
cअगरs_show_cache_flavor(काष्ठा seq_file *s, काष्ठा cअगरs_sb_info *cअगरs_sb)
अणु
	seq_माला_दो(s, ",cache=");

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_STRICT_IO)
		seq_माला_दो(s, "strict");
	अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_सूचीECT_IO)
		seq_माला_दो(s, "none");
	अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RW_CACHE)
		seq_माला_दो(s, "singleclient"); /* assume only one client access */
	अन्यथा अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RO_CACHE)
		seq_माला_दो(s, "ro"); /* पढ़ो only caching assumed */
	अन्यथा
		seq_माला_दो(s, "loose");
पूर्ण

/*
 * cअगरs_show_devname() is used so we show the mount device name with correct
 * क्रमmat (e.g. क्रमward slashes vs. back slashes) in /proc/mounts
 */
अटल पूर्णांक cअगरs_show_devname(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(root->d_sb);
	अक्षर *devname = kstrdup(cअगरs_sb->ctx->source, GFP_KERNEL);

	अगर (devname == शून्य)
		seq_माला_दो(m, "none");
	अन्यथा अणु
		convert_delimiter(devname, '/');
		/* escape all spaces in share names */
		seq_escape(m, devname, " \t");
		kमुक्त(devname);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * cअगरs_show_options() is क्रम displaying mount options in /proc/mounts.
 * Not all settable options are displayed but most of the important
 * ones are.
 */
अटल पूर्णांक
cअगरs_show_options(काष्ठा seq_file *s, काष्ठा dentry *root)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(root->d_sb);
	काष्ठा cअगरs_tcon *tcon = cअगरs_sb_master_tcon(cअगरs_sb);
	काष्ठा sockaddr *srcaddr;
	srcaddr = (काष्ठा sockaddr *)&tcon->ses->server->srcaddr;

	seq_show_option(s, "vers", tcon->ses->server->vals->version_string);
	cअगरs_show_security(s, tcon->ses);
	cअगरs_show_cache_flavor(s, cअगरs_sb);

	अगर (tcon->no_lease)
		seq_माला_दो(s, ",nolease");
	अगर (cअगरs_sb->ctx->multiuser)
		seq_माला_दो(s, ",multiuser");
	अन्यथा अगर (tcon->ses->user_name)
		seq_show_option(s, "username", tcon->ses->user_name);

	अगर (tcon->ses->करोमुख्यName && tcon->ses->करोमुख्यName[0] != 0)
		seq_show_option(s, "domain", tcon->ses->करोमुख्यName);

	अगर (srcaddr->sa_family != AF_UNSPEC) अणु
		काष्ठा sockaddr_in *saddr4;
		काष्ठा sockaddr_in6 *saddr6;
		saddr4 = (काष्ठा sockaddr_in *)srcaddr;
		saddr6 = (काष्ठा sockaddr_in6 *)srcaddr;
		अगर (srcaddr->sa_family == AF_INET6)
			seq_म_लिखो(s, ",srcaddr=%pI6c",
				   &saddr6->sin6_addr);
		अन्यथा अगर (srcaddr->sa_family == AF_INET)
			seq_म_लिखो(s, ",srcaddr=%pI4",
				   &saddr4->sin_addr.s_addr);
		अन्यथा
			seq_म_लिखो(s, ",srcaddr=BAD-AF:%i",
				   (पूर्णांक)(srcaddr->sa_family));
	पूर्ण

	seq_म_लिखो(s, ",uid=%u",
		   from_kuid_munged(&init_user_ns, cअगरs_sb->ctx->linux_uid));
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_OVERR_UID)
		seq_माला_दो(s, ",forceuid");
	अन्यथा
		seq_माला_दो(s, ",noforceuid");

	seq_म_लिखो(s, ",gid=%u",
		   from_kgid_munged(&init_user_ns, cअगरs_sb->ctx->linux_gid));
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_OVERR_GID)
		seq_माला_दो(s, ",forcegid");
	अन्यथा
		seq_माला_दो(s, ",noforcegid");

	cअगरs_show_address(s, tcon->ses->server);

	अगर (!tcon->unix_ext)
		seq_म_लिखो(s, ",file_mode=0%ho,dir_mode=0%ho",
					   cअगरs_sb->ctx->file_mode,
					   cअगरs_sb->ctx->dir_mode);
	अगर (cअगरs_sb->ctx->ioअक्षरset)
		seq_म_लिखो(s, ",iocharset=%s", cअगरs_sb->ctx->ioअक्षरset);
	अगर (tcon->seal)
		seq_माला_दो(s, ",seal");
	अन्यथा अगर (tcon->ses->server->ignore_signature)
		seq_माला_दो(s, ",signloosely");
	अगर (tcon->noहाल)
		seq_माला_दो(s, ",nocase");
	अगर (tcon->nodelete)
		seq_माला_दो(s, ",nodelete");
	अगर (tcon->local_lease)
		seq_माला_दो(s, ",locallease");
	अगर (tcon->retry)
		seq_माला_दो(s, ",hard");
	अन्यथा
		seq_माला_दो(s, ",soft");
	अगर (tcon->use_persistent)
		seq_माला_दो(s, ",persistenthandles");
	अन्यथा अगर (tcon->use_resilient)
		seq_माला_दो(s, ",resilienthandles");
	अगर (tcon->posix_extensions)
		seq_माला_दो(s, ",posix");
	अन्यथा अगर (tcon->unix_ext)
		seq_माला_दो(s, ",unix");
	अन्यथा
		seq_माला_दो(s, ",nounix");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_DFS)
		seq_माला_दो(s, ",nodfs");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_POSIX_PATHS)
		seq_माला_दो(s, ",posixpaths");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SET_UID)
		seq_माला_दो(s, ",setuids");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UID_FROM_ACL)
		seq_माला_दो(s, ",idsfromsid");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM)
		seq_माला_दो(s, ",serverino");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_RWPIDFORWARD)
		seq_माला_दो(s, ",rwpidforward");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOPOSIXBRL)
		seq_माला_दो(s, ",forcemand");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_XATTR)
		seq_माला_दो(s, ",nouser_xattr");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MAP_SPECIAL_CHR)
		seq_माला_दो(s, ",mapchars");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MAP_SFM_CHR)
		seq_माला_दो(s, ",mapposix");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_UNX_EMUL)
		seq_माला_दो(s, ",sfu");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_BRL)
		seq_माला_दो(s, ",nobrl");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_HANDLE_CACHE)
		seq_माला_दो(s, ",nohandlecache");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MODE_FROM_SID)
		seq_माला_दो(s, ",modefromsid");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_ACL)
		seq_माला_दो(s, ",cifsacl");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_DYNPERM)
		seq_माला_दो(s, ",dynperm");
	अगर (root->d_sb->s_flags & SB_POSIXACL)
		seq_माला_दो(s, ",acl");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_MF_SYMLINKS)
		seq_माला_दो(s, ",mfsymlinks");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_FSCACHE)
		seq_माला_दो(s, ",fsc");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NOSSYNC)
		seq_माला_दो(s, ",nostrictsync");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_NO_PERM)
		seq_माला_दो(s, ",noperm");
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_BACKUPUID)
		seq_म_लिखो(s, ",backupuid=%u",
			   from_kuid_munged(&init_user_ns,
					    cअगरs_sb->ctx->backupuid));
	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_CIFS_BACKUPGID)
		seq_म_लिखो(s, ",backupgid=%u",
			   from_kgid_munged(&init_user_ns,
					    cअगरs_sb->ctx->backupgid));

	seq_म_लिखो(s, ",rsize=%u", cअगरs_sb->ctx->rsize);
	seq_म_लिखो(s, ",wsize=%u", cअगरs_sb->ctx->wsize);
	seq_म_लिखो(s, ",bsize=%u", cअगरs_sb->ctx->bsize);
	अगर (cअगरs_sb->ctx->rasize)
		seq_म_लिखो(s, ",rasize=%u", cअगरs_sb->ctx->rasize);
	अगर (tcon->ses->server->min_offload)
		seq_म_लिखो(s, ",esize=%u", tcon->ses->server->min_offload);
	seq_म_लिखो(s, ",echo_interval=%lu",
			tcon->ses->server->echo_पूर्णांकerval / HZ);

	/* Only display max_credits अगर it was overridden on mount */
	अगर (tcon->ses->server->max_credits != SMB2_MAX_CREDITS_AVAILABLE)
		seq_म_लिखो(s, ",max_credits=%u", tcon->ses->server->max_credits);

	अगर (tcon->snapshot_समय)
		seq_म_लिखो(s, ",snapshot=%llu", tcon->snapshot_समय);
	अगर (tcon->handle_समयout)
		seq_म_लिखो(s, ",handletimeout=%u", tcon->handle_समयout);

	/*
	 * Display file and directory attribute समयout in seconds.
	 * If file and directory attribute समयout the same then aस_समयo
	 * was likely specअगरied on mount
	 */
	अगर (cअगरs_sb->ctx->acdirmax == cअगरs_sb->ctx->acregmax)
		seq_म_लिखो(s, ",actimeo=%lu", cअगरs_sb->ctx->acregmax / HZ);
	अन्यथा अणु
		seq_म_लिखो(s, ",acdirmax=%lu", cअगरs_sb->ctx->acdirmax / HZ);
		seq_म_लिखो(s, ",acregmax=%lu", cअगरs_sb->ctx->acregmax / HZ);
	पूर्ण

	अगर (tcon->ses->chan_max > 1)
		seq_म_लिखो(s, ",multichannel,max_channels=%zu",
			   tcon->ses->chan_max);

	अगर (tcon->use_witness)
		seq_माला_दो(s, ",witness");

	वापस 0;
पूर्ण

अटल व्योम cअगरs_umount_begin(काष्ठा super_block *sb)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	काष्ठा cअगरs_tcon *tcon;

	अगर (cअगरs_sb == शून्य)
		वापस;

	tcon = cअगरs_sb_master_tcon(cअगरs_sb);

	spin_lock(&cअगरs_tcp_ses_lock);
	अगर ((tcon->tc_count > 1) || (tcon->tidStatus == CअगरsExiting)) अणु
		/* we have other mounts to same share or we have
		   alपढ़ोy tried to क्रमce umount this and woken up
		   all रुकोing network requests, nothing to करो */
		spin_unlock(&cअगरs_tcp_ses_lock);
		वापस;
	पूर्ण अन्यथा अगर (tcon->tc_count == 1)
		tcon->tidStatus = CअगरsExiting;
	spin_unlock(&cअगरs_tcp_ses_lock);

	/* cancel_brl_requests(tcon); */ /* BB mark all brl mids as निकासing */
	/* cancel_notअगरy_requests(tcon); */
	अगर (tcon->ses && tcon->ses->server) अणु
		cअगरs_dbg(FYI, "wake up tasks now - umount begin not complete\n");
		wake_up_all(&tcon->ses->server->request_q);
		wake_up_all(&tcon->ses->server->response_q);
		msleep(1); /* yield */
		/* we have to kick the requests once more */
		wake_up_all(&tcon->ses->server->response_q);
		msleep(1);
	पूर्ण

	वापस;
पूर्ण

#अगर_घोषित CONFIG_CIFS_STATS2
अटल पूर्णांक cअगरs_show_stats(काष्ठा seq_file *s, काष्ठा dentry *root)
अणु
	/* BB FIXME */
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक cअगरs_drop_inode(काष्ठा inode *inode)
अणु
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(inode->i_sb);

	/* no serverino => unconditional eviction */
	वापस !(cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_SERVER_INUM) ||
		generic_drop_inode(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations cअगरs_super_ops = अणु
	.statfs = cअगरs_statfs,
	.alloc_inode = cअगरs_alloc_inode,
	.मुक्त_inode = cअगरs_मुक्त_inode,
	.drop_inode	= cअगरs_drop_inode,
	.evict_inode	= cअगरs_evict_inode,
/*	.show_path	= cअगरs_show_path, */ /* Would we ever need show path? */
	.show_devname   = cअगरs_show_devname,
/*	.delete_inode	= cअगरs_delete_inode,  */  /* Do not need above
	function unless later we add lazy बंद of inodes or unless the
	kernel क्रममाला_लो to call us with the same number of releases (बंदs)
	as खोलोs */
	.show_options = cअगरs_show_options,
	.umount_begin   = cअगरs_umount_begin,
#अगर_घोषित CONFIG_CIFS_STATS2
	.show_stats = cअगरs_show_stats,
#पूर्ण_अगर
पूर्ण;

/*
 * Get root dentry from superblock according to prefix path mount option.
 * Return dentry with refcount + 1 on success and शून्य otherwise.
 */
अटल काष्ठा dentry *
cअगरs_get_root(काष्ठा smb3_fs_context *ctx, काष्ठा super_block *sb)
अणु
	काष्ठा dentry *dentry;
	काष्ठा cअगरs_sb_info *cअगरs_sb = CIFS_SB(sb);
	अक्षर *full_path = शून्य;
	अक्षर *s, *p;
	अक्षर sep;

	अगर (cअगरs_sb->mnt_cअगरs_flags & CIFS_MOUNT_USE_PREFIX_PATH)
		वापस dget(sb->s_root);

	full_path = cअगरs_build_path_to_root(ctx, cअगरs_sb,
				cअगरs_sb_master_tcon(cअगरs_sb), 0);
	अगर (full_path == शून्य)
		वापस ERR_PTR(-ENOMEM);

	cअगरs_dbg(FYI, "Get root dentry for %s\n", full_path);

	sep = CIFS_सूची_SEP(cअगरs_sb);
	dentry = dget(sb->s_root);
	p = s = full_path;

	करो अणु
		काष्ठा inode *dir = d_inode(dentry);
		काष्ठा dentry *child;

		अगर (!S_ISसूची(dir->i_mode)) अणु
			dput(dentry);
			dentry = ERR_PTR(-ENOTसूची);
			अवरोध;
		पूर्ण

		/* skip separators */
		जबतक (*s == sep)
			s++;
		अगर (!*s)
			अवरोध;
		p = s++;
		/* next separator */
		जबतक (*s && *s != sep)
			s++;

		child = lookup_positive_unlocked(p, dentry, s - p);
		dput(dentry);
		dentry = child;
	पूर्ण जबतक (!IS_ERR(dentry));
	kमुक्त(full_path);
	वापस dentry;
पूर्ण

अटल पूर्णांक cअगरs_set_super(काष्ठा super_block *sb, व्योम *data)
अणु
	काष्ठा cअगरs_mnt_data *mnt_data = data;
	sb->s_fs_info = mnt_data->cअगरs_sb;
	वापस set_anon_super(sb, शून्य);
पूर्ण

काष्ठा dentry *
cअगरs_smb3_करो_mount(काष्ठा file_प्रणाली_type *fs_type,
	      पूर्णांक flags, काष्ठा smb3_fs_context *old_ctx)
अणु
	पूर्णांक rc;
	काष्ठा super_block *sb;
	काष्ठा cअगरs_sb_info *cअगरs_sb = शून्य;
	काष्ठा cअगरs_mnt_data mnt_data;
	काष्ठा dentry *root;

	/*
	 * Prपूर्णांकs in Kernel / CIFS log the attempted mount operation
	 *	If CIFS_DEBUG && cअगरs_FYI
	 */
	अगर (cअगरsFYI)
		cअगरs_dbg(FYI, "Devname: %s flags: %d\n", old_ctx->UNC, flags);
	अन्यथा
		cअगरs_info("Attempting to mount %s\n", old_ctx->UNC);

	cअगरs_sb = kzalloc(माप(काष्ठा cअगरs_sb_info), GFP_KERNEL);
	अगर (cअगरs_sb == शून्य) अणु
		root = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	cअगरs_sb->ctx = kzalloc(माप(काष्ठा smb3_fs_context), GFP_KERNEL);
	अगर (!cअगरs_sb->ctx) अणु
		root = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	rc = smb3_fs_context_dup(cअगरs_sb->ctx, old_ctx);
	अगर (rc) अणु
		root = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	rc = cअगरs_setup_volume_info(cअगरs_sb->ctx, शून्य, शून्य);
	अगर (rc) अणु
		root = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	rc = cअगरs_setup_cअगरs_sb(cअगरs_sb);
	अगर (rc) अणु
		root = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	rc = cअगरs_mount(cअगरs_sb, cअगरs_sb->ctx);
	अगर (rc) अणु
		अगर (!(flags & SB_SILENT))
			cअगरs_dbg(VFS, "cifs_mount failed w/return code = %d\n",
				 rc);
		root = ERR_PTR(rc);
		जाओ out;
	पूर्ण

	mnt_data.ctx = cअगरs_sb->ctx;
	mnt_data.cअगरs_sb = cअगरs_sb;
	mnt_data.flags = flags;

	/* BB should we make this contingent on mount parm? */
	flags |= SB_NOसूचीATIME | SB_NOATIME;

	sb = sget(fs_type, cअगरs_match_super, cअगरs_set_super, flags, &mnt_data);
	अगर (IS_ERR(sb)) अणु
		root = ERR_CAST(sb);
		cअगरs_umount(cअगरs_sb);
		cअगरs_sb = शून्य;
		जाओ out;
	पूर्ण

	अगर (sb->s_root) अणु
		cअगरs_dbg(FYI, "Use existing superblock\n");
		cअगरs_umount(cअगरs_sb);
		cअगरs_sb = शून्य;
	पूर्ण अन्यथा अणु
		rc = cअगरs_पढ़ो_super(sb);
		अगर (rc) अणु
			root = ERR_PTR(rc);
			जाओ out_super;
		पूर्ण

		sb->s_flags |= SB_ACTIVE;
	पूर्ण

	root = cअगरs_get_root(cअगरs_sb ? cअगरs_sb->ctx : old_ctx, sb);
	अगर (IS_ERR(root))
		जाओ out_super;

	अगर (cअगरs_sb)
		cअगरs_sb->root = dget(root);

	cअगरs_dbg(FYI, "dentry root is: %p\n", root);
	वापस root;

out_super:
	deactivate_locked_super(sb);
out:
	अगर (cअगरs_sb) अणु
		kमुक्त(cअगरs_sb->prepath);
		smb3_cleanup_fs_context(cअगरs_sb->ctx);
		kमुक्त(cअगरs_sb);
	पूर्ण
	वापस root;
पूर्ण


अटल sमाप_प्रकार
cअगरs_loose_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	sमाप_प्रकार rc;
	काष्ठा inode *inode = file_inode(iocb->ki_filp);

	अगर (iocb->ki_filp->f_flags & O_सूचीECT)
		वापस cअगरs_user_पढ़ोv(iocb, iter);

	rc = cअगरs_revalidate_mapping(inode);
	अगर (rc)
		वापस rc;

	वापस generic_file_पढ़ो_iter(iocb, iter);
पूर्ण

अटल sमाप_प्रकार cअगरs_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा cअगरsInodeInfo *cinode = CIFS_I(inode);
	sमाप_प्रकार written;
	पूर्णांक rc;

	अगर (iocb->ki_filp->f_flags & O_सूचीECT) अणु
		written = cअगरs_user_ग_लिखोv(iocb, from);
		अगर (written > 0 && CIFS_CACHE_READ(cinode)) अणु
			cअगरs_zap_mapping(inode);
			cअगरs_dbg(FYI,
				 "Set no oplock for inode=%p after a write operation\n",
				 inode);
			cinode->oplock = 0;
		पूर्ण
		वापस written;
	पूर्ण

	written = cअगरs_get_ग_लिखोr(cinode);
	अगर (written)
		वापस written;

	written = generic_file_ग_लिखो_iter(iocb, from);

	अगर (CIFS_CACHE_WRITE(CIFS_I(inode)))
		जाओ out;

	rc = filemap_fdataग_लिखो(inode->i_mapping);
	अगर (rc)
		cअगरs_dbg(FYI, "cifs_file_write_iter: %d rc on %p inode\n",
			 rc, inode);

out:
	cअगरs_put_ग_लिखोr(cinode);
	वापस written;
पूर्ण

अटल loff_t cअगरs_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;
	काष्ठा cअगरs_tcon *tcon;

	/*
	 * whence == अंत_से || SEEK_DATA || SEEK_HOLE => we must revalidate
	 * the cached file length
	 */
	अगर (whence != शुरू_से && whence != प्रस्तुत_से) अणु
		पूर्णांक rc;
		काष्ठा inode *inode = file_inode(file);

		/*
		 * We need to be sure that all dirty pages are written and the
		 * server has the newest file length.
		 */
		अगर (!CIFS_CACHE_READ(CIFS_I(inode)) && inode->i_mapping &&
		    inode->i_mapping->nrpages != 0) अणु
			rc = filemap_fdataरुको(inode->i_mapping);
			अगर (rc) अणु
				mapping_set_error(inode->i_mapping, rc);
				वापस rc;
			पूर्ण
		पूर्ण
		/*
		 * Some applications poll क्रम the file length in this strange
		 * way so we must seek to end on non-oplocked files by
		 * setting the revalidate समय to zero.
		 */
		CIFS_I(inode)->समय = 0;

		rc = cअगरs_revalidate_file_attr(file);
		अगर (rc < 0)
			वापस (loff_t)rc;
	पूर्ण
	अगर (cfile && cfile->tlink) अणु
		tcon = tlink_tcon(cfile->tlink);
		अगर (tcon->ses->server->ops->llseek)
			वापस tcon->ses->server->ops->llseek(file, tcon,
							      offset, whence);
	पूर्ण
	वापस generic_file_llseek(file, offset, whence);
पूर्ण

अटल पूर्णांक
cअगरs_setlease(काष्ठा file *file, दीर्घ arg, काष्ठा file_lock **lease, व्योम **priv)
अणु
	/*
	 * Note that this is called by vfs setlease with i_lock held to
	 * protect *lease from going away.
	 */
	काष्ठा inode *inode = file_inode(file);
	काष्ठा cअगरsFileInfo *cfile = file->निजी_data;

	अगर (!(S_ISREG(inode->i_mode)))
		वापस -EINVAL;

	/* Check अगर file is oplocked अगर this is request क्रम new lease */
	अगर (arg == F_UNLCK ||
	    ((arg == F_RDLCK) && CIFS_CACHE_READ(CIFS_I(inode))) ||
	    ((arg == F_WRLCK) && CIFS_CACHE_WRITE(CIFS_I(inode))))
		वापस generic_setlease(file, arg, lease, priv);
	अन्यथा अगर (tlink_tcon(cfile->tlink)->local_lease &&
		 !CIFS_CACHE_READ(CIFS_I(inode)))
		/*
		 * If the server claims to support oplock on this file, then we
		 * still need to check oplock even अगर the local_lease mount
		 * option is set, but there are servers which करो not support
		 * oplock क्रम which this mount option may be useful अगर the user
		 * knows that the file won't be changed on the server by anyone
		 * अन्यथा.
		 */
		वापस generic_setlease(file, arg, lease, priv);
	अन्यथा
		वापस -EAGAIN;
पूर्ण

काष्ठा file_प्रणाली_type cअगरs_fs_type = अणु
	.owner = THIS_MODULE,
	.name = "cifs",
	.init_fs_context = smb3_init_fs_context,
	.parameters = smb3_fs_parameters,
	.समाप्त_sb = cअगरs_समाप्त_sb,
	.fs_flags = FS_RENAME_DOES_D_MOVE,
पूर्ण;
MODULE_ALIAS_FS("cifs");

अटल काष्ठा file_प्रणाली_type smb3_fs_type = अणु
	.owner = THIS_MODULE,
	.name = "smb3",
	.init_fs_context = smb3_init_fs_context,
	.parameters = smb3_fs_parameters,
	.समाप्त_sb = cअगरs_समाप्त_sb,
	.fs_flags = FS_RENAME_DOES_D_MOVE,
पूर्ण;
MODULE_ALIAS_FS("smb3");
MODULE_ALIAS("smb3");

स्थिर काष्ठा inode_operations cअगरs_dir_inode_ops = अणु
	.create = cअगरs_create,
	.atomic_खोलो = cअगरs_atomic_खोलो,
	.lookup = cअगरs_lookup,
	.getattr = cअगरs_getattr,
	.unlink = cअगरs_unlink,
	.link = cअगरs_hardlink,
	.सूची_गढ़ो = cअगरs_सूची_गढ़ो,
	.सूची_हटाओ = cअगरs_सूची_हटाओ,
	.नाम = cअगरs_नाम2,
	.permission = cअगरs_permission,
	.setattr = cअगरs_setattr,
	.symlink = cअगरs_symlink,
	.mknod   = cअगरs_mknod,
	.listxattr = cअगरs_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations cअगरs_file_inode_ops = अणु
	.setattr = cअगरs_setattr,
	.getattr = cअगरs_getattr,
	.permission = cअगरs_permission,
	.listxattr = cअगरs_listxattr,
	.fiemap = cअगरs_fiemap,
पूर्ण;

स्थिर काष्ठा inode_operations cअगरs_symlink_inode_ops = अणु
	.get_link = cअगरs_get_link,
	.permission = cअगरs_permission,
	.listxattr = cअगरs_listxattr,
पूर्ण;

अटल loff_t cअगरs_remap_file_range(काष्ठा file *src_file, loff_t off,
		काष्ठा file *dst_file, loff_t destoff, loff_t len,
		अचिन्हित पूर्णांक remap_flags)
अणु
	काष्ठा inode *src_inode = file_inode(src_file);
	काष्ठा inode *target_inode = file_inode(dst_file);
	काष्ठा cअगरsFileInfo *smb_file_src = src_file->निजी_data;
	काष्ठा cअगरsFileInfo *smb_file_target;
	काष्ठा cअगरs_tcon *target_tcon;
	अचिन्हित पूर्णांक xid;
	पूर्णांक rc;

	अगर (remap_flags & ~(REMAP_खाता_DEDUP | REMAP_खाता_ADVISORY))
		वापस -EINVAL;

	cअगरs_dbg(FYI, "clone range\n");

	xid = get_xid();

	अगर (!src_file->निजी_data || !dst_file->निजी_data) अणु
		rc = -EBADF;
		cअगरs_dbg(VFS, "missing cifsFileInfo on copy range src file\n");
		जाओ out;
	पूर्ण

	smb_file_target = dst_file->निजी_data;
	target_tcon = tlink_tcon(smb_file_target->tlink);

	/*
	 * Note: cअगरs हाल is easier than btrfs since server responsible क्रम
	 * checks क्रम proper खोलो modes and file type and अगर it wants
	 * server could even support copy of range where source = target
	 */
	lock_two_nondirectories(target_inode, src_inode);

	अगर (len == 0)
		len = src_inode->i_size - off;

	cअगरs_dbg(FYI, "about to flush pages\n");
	/* should we flush first and last page first */
	truncate_inode_pages_range(&target_inode->i_data, destoff,
				   PAGE_ALIGN(destoff + len)-1);

	अगर (target_tcon->ses->server->ops->duplicate_extents)
		rc = target_tcon->ses->server->ops->duplicate_extents(xid,
			smb_file_src, smb_file_target, off, len, destoff);
	अन्यथा
		rc = -EOPNOTSUPP;

	/* क्रमce revalidate of size and बारtamps of target file now
	   that target is updated on the server */
	CIFS_I(target_inode)->समय = 0;
	/* although unlocking in the reverse order from locking is not
	   strictly necessary here it is a little cleaner to be consistent */
	unlock_two_nondirectories(src_inode, target_inode);
out:
	मुक्त_xid(xid);
	वापस rc < 0 ? rc : len;
पूर्ण

sमाप_प्रकार cअगरs_file_copychunk_range(अचिन्हित पूर्णांक xid,
				काष्ठा file *src_file, loff_t off,
				काष्ठा file *dst_file, loff_t destoff,
				माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *src_inode = file_inode(src_file);
	काष्ठा inode *target_inode = file_inode(dst_file);
	काष्ठा cअगरsFileInfo *smb_file_src;
	काष्ठा cअगरsFileInfo *smb_file_target;
	काष्ठा cअगरs_tcon *src_tcon;
	काष्ठा cअगरs_tcon *target_tcon;
	sमाप_प्रकार rc;

	cअगरs_dbg(FYI, "copychunk range\n");

	अगर (!src_file->निजी_data || !dst_file->निजी_data) अणु
		rc = -EBADF;
		cअगरs_dbg(VFS, "missing cifsFileInfo on copy range src file\n");
		जाओ out;
	पूर्ण

	rc = -EXDEV;
	smb_file_target = dst_file->निजी_data;
	smb_file_src = src_file->निजी_data;
	src_tcon = tlink_tcon(smb_file_src->tlink);
	target_tcon = tlink_tcon(smb_file_target->tlink);

	अगर (src_tcon->ses != target_tcon->ses) अणु
		cअगरs_dbg(VFS, "source and target of copy not on same server\n");
		जाओ out;
	पूर्ण

	rc = -EOPNOTSUPP;
	अगर (!target_tcon->ses->server->ops->copychunk_range)
		जाओ out;

	/*
	 * Note: cअगरs हाल is easier than btrfs since server responsible क्रम
	 * checks क्रम proper खोलो modes and file type and अगर it wants
	 * server could even support copy of range where source = target
	 */
	lock_two_nondirectories(target_inode, src_inode);

	cअगरs_dbg(FYI, "about to flush pages\n");
	/* should we flush first and last page first */
	truncate_inode_pages(&target_inode->i_data, 0);

	rc = file_modअगरied(dst_file);
	अगर (!rc)
		rc = target_tcon->ses->server->ops->copychunk_range(xid,
			smb_file_src, smb_file_target, off, len, destoff);

	file_accessed(src_file);

	/* क्रमce revalidate of size and बारtamps of target file now
	 * that target is updated on the server
	 */
	CIFS_I(target_inode)->समय = 0;
	/* although unlocking in the reverse order from locking is not
	 * strictly necessary here it is a little cleaner to be consistent
	 */
	unlock_two_nondirectories(src_inode, target_inode);

out:
	वापस rc;
पूर्ण

/*
 * Directory operations under CIFS/SMB2/SMB3 are synchronous, so fsync()
 * is a dummy operation.
 */
अटल पूर्णांक cअगरs_dir_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	cअगरs_dbg(FYI, "Sync directory - name: %pD datasync: 0x%x\n",
		 file, datasync);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cअगरs_copy_file_range(काष्ठा file *src_file, loff_t off,
				काष्ठा file *dst_file, loff_t destoff,
				माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक xid = get_xid();
	sमाप_प्रकार rc;
	काष्ठा cअगरsFileInfo *cfile = dst_file->निजी_data;

	अगर (cfile->swapfile)
		वापस -EOPNOTSUPP;

	rc = cअगरs_file_copychunk_range(xid, src_file, off, dst_file, destoff,
					len, flags);
	मुक्त_xid(xid);

	अगर (rc == -EOPNOTSUPP || rc == -EXDEV)
		rc = generic_copy_file_range(src_file, off, dst_file,
					     destoff, len, flags);
	वापस rc;
पूर्ण

स्थिर काष्ठा file_operations cअगरs_file_ops = अणु
	.पढ़ो_iter = cअगरs_loose_पढ़ो_iter,
	.ग_लिखो_iter = cअगरs_file_ग_लिखो_iter,
	.खोलो = cअगरs_खोलो,
	.release = cअगरs_बंद,
	.lock = cअगरs_lock,
	.flock = cअगरs_flock,
	.fsync = cअगरs_fsync,
	.flush = cअगरs_flush,
	.mmap  = cअगरs_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.llseek = cअगरs_llseek,
	.unlocked_ioctl	= cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.setlease = cअगरs_setlease,
	.fallocate = cअगरs_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations cअगरs_file_strict_ops = अणु
	.पढ़ो_iter = cअगरs_strict_पढ़ोv,
	.ग_लिखो_iter = cअगरs_strict_ग_लिखोv,
	.खोलो = cअगरs_खोलो,
	.release = cअगरs_बंद,
	.lock = cअगरs_lock,
	.flock = cअगरs_flock,
	.fsync = cअगरs_strict_fsync,
	.flush = cअगरs_flush,
	.mmap = cअगरs_file_strict_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.llseek = cअगरs_llseek,
	.unlocked_ioctl	= cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.setlease = cअगरs_setlease,
	.fallocate = cअगरs_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations cअगरs_file_direct_ops = अणु
	.पढ़ो_iter = cअगरs_direct_पढ़ोv,
	.ग_लिखो_iter = cअगरs_direct_ग_लिखोv,
	.खोलो = cअगरs_खोलो,
	.release = cअगरs_बंद,
	.lock = cअगरs_lock,
	.flock = cअगरs_flock,
	.fsync = cअगरs_fsync,
	.flush = cअगरs_flush,
	.mmap = cअगरs_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.unlocked_ioctl  = cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.llseek = cअगरs_llseek,
	.setlease = cअगरs_setlease,
	.fallocate = cअगरs_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations cअगरs_file_nobrl_ops = अणु
	.पढ़ो_iter = cअगरs_loose_पढ़ो_iter,
	.ग_लिखो_iter = cअगरs_file_ग_लिखो_iter,
	.खोलो = cअगरs_खोलो,
	.release = cअगरs_बंद,
	.fsync = cअगरs_fsync,
	.flush = cअगरs_flush,
	.mmap  = cअगरs_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.llseek = cअगरs_llseek,
	.unlocked_ioctl	= cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.setlease = cअगरs_setlease,
	.fallocate = cअगरs_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations cअगरs_file_strict_nobrl_ops = अणु
	.पढ़ो_iter = cअगरs_strict_पढ़ोv,
	.ग_लिखो_iter = cअगरs_strict_ग_लिखोv,
	.खोलो = cअगरs_खोलो,
	.release = cअगरs_बंद,
	.fsync = cअगरs_strict_fsync,
	.flush = cअगरs_flush,
	.mmap = cअगरs_file_strict_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.llseek = cअगरs_llseek,
	.unlocked_ioctl	= cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.setlease = cअगरs_setlease,
	.fallocate = cअगरs_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations cअगरs_file_direct_nobrl_ops = अणु
	.पढ़ो_iter = cअगरs_direct_पढ़ोv,
	.ग_लिखो_iter = cअगरs_direct_ग_लिखोv,
	.खोलो = cअगरs_खोलो,
	.release = cअगरs_बंद,
	.fsync = cअगरs_fsync,
	.flush = cअगरs_flush,
	.mmap = cअगरs_file_mmap,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.unlocked_ioctl  = cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.llseek = cअगरs_llseek,
	.setlease = cअगरs_setlease,
	.fallocate = cअगरs_fallocate,
पूर्ण;

स्थिर काष्ठा file_operations cअगरs_dir_ops = अणु
	.iterate_shared = cअगरs_सूची_पढ़ो,
	.release = cअगरs_बंद_सूची,
	.पढ़ो    = generic_पढ़ो_dir,
	.unlocked_ioctl  = cअगरs_ioctl,
	.copy_file_range = cअगरs_copy_file_range,
	.remap_file_range = cअगरs_remap_file_range,
	.llseek = generic_file_llseek,
	.fsync = cअगरs_dir_fsync,
पूर्ण;

अटल व्योम
cअगरs_init_once(व्योम *inode)
अणु
	काष्ठा cअगरsInodeInfo *cअगरsi = inode;

	inode_init_once(&cअगरsi->vfs_inode);
	init_rwsem(&cअगरsi->lock_sem);
पूर्ण

अटल पूर्णांक __init
cअगरs_init_inodecache(व्योम)
अणु
	cअगरs_inode_cachep = kmem_cache_create("cifs_inode_cache",
					      माप(काष्ठा cअगरsInodeInfo),
					      0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					      cअगरs_init_once);
	अगर (cअगरs_inode_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम
cअगरs_destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(cअगरs_inode_cachep);
पूर्ण

अटल पूर्णांक
cअगरs_init_request_bufs(व्योम)
अणु
	/*
	 * SMB2 maximum header size is bigger than CIFS one - no problems to
	 * allocate some more bytes क्रम CIFS.
	 */
	माप_प्रकार max_hdr_size = MAX_SMB2_HDR_SIZE;

	अगर (CIFSMaxBufSize < 8192) अणु
	/* Buffer size can not be smaller than 2 * PATH_MAX since maximum
	Unicode path name has to fit in any SMB/CIFS path based frames */
		CIFSMaxBufSize = 8192;
	पूर्ण अन्यथा अगर (CIFSMaxBufSize > 1024*127) अणु
		CIFSMaxBufSize = 1024 * 127;
	पूर्ण अन्यथा अणु
		CIFSMaxBufSize &= 0x1FE00; /* Round size to even 512 byte mult*/
	पूर्ण
/*
	cअगरs_dbg(VFS, "CIFSMaxBufSize %d 0x%x\n",
		 CIFSMaxBufSize, CIFSMaxBufSize);
*/
	cअगरs_req_cachep = kmem_cache_create_usercopy("cifs_request",
					    CIFSMaxBufSize + max_hdr_size, 0,
					    SLAB_HWCACHE_ALIGN, 0,
					    CIFSMaxBufSize + max_hdr_size,
					    शून्य);
	अगर (cअगरs_req_cachep == शून्य)
		वापस -ENOMEM;

	अगर (cअगरs_min_rcv < 1)
		cअगरs_min_rcv = 1;
	अन्यथा अगर (cअगरs_min_rcv > 64) अणु
		cअगरs_min_rcv = 64;
		cअगरs_dbg(VFS, "cifs_min_rcv set to maximum (64)\n");
	पूर्ण

	cअगरs_req_poolp = mempool_create_slab_pool(cअगरs_min_rcv,
						  cअगरs_req_cachep);

	अगर (cअगरs_req_poolp == शून्य) अणु
		kmem_cache_destroy(cअगरs_req_cachep);
		वापस -ENOMEM;
	पूर्ण
	/* MAX_CIFS_SMALL_BUFFER_SIZE bytes is enough क्रम most SMB responses and
	almost all handle based requests (but not ग_लिखो response, nor is it
	sufficient क्रम path based requests).  A smaller size would have
	been more efficient (compacting multiple slab items on one 4k page)
	क्रम the हाल in which debug was on, but this larger size allows
	more SMBs to use small buffer alloc and is still much more
	efficient to alloc 1 per page off the slab compared to 17K (5page)
	alloc of large cअगरs buffers even when page debugging is on */
	cअगरs_sm_req_cachep = kmem_cache_create_usercopy("cifs_small_rq",
			MAX_CIFS_SMALL_BUFFER_SIZE, 0, SLAB_HWCACHE_ALIGN,
			0, MAX_CIFS_SMALL_BUFFER_SIZE, शून्य);
	अगर (cअगरs_sm_req_cachep == शून्य) अणु
		mempool_destroy(cअगरs_req_poolp);
		kmem_cache_destroy(cअगरs_req_cachep);
		वापस -ENOMEM;
	पूर्ण

	अगर (cअगरs_min_small < 2)
		cअगरs_min_small = 2;
	अन्यथा अगर (cअगरs_min_small > 256) अणु
		cअगरs_min_small = 256;
		cअगरs_dbg(FYI, "cifs_min_small set to maximum (256)\n");
	पूर्ण

	cअगरs_sm_req_poolp = mempool_create_slab_pool(cअगरs_min_small,
						     cअगरs_sm_req_cachep);

	अगर (cअगरs_sm_req_poolp == शून्य) अणु
		mempool_destroy(cअगरs_req_poolp);
		kmem_cache_destroy(cअगरs_req_cachep);
		kmem_cache_destroy(cअगरs_sm_req_cachep);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
cअगरs_destroy_request_bufs(व्योम)
अणु
	mempool_destroy(cअगरs_req_poolp);
	kmem_cache_destroy(cअगरs_req_cachep);
	mempool_destroy(cअगरs_sm_req_poolp);
	kmem_cache_destroy(cअगरs_sm_req_cachep);
पूर्ण

अटल पूर्णांक
cअगरs_init_mids(व्योम)
अणु
	cअगरs_mid_cachep = kmem_cache_create("cifs_mpx_ids",
					    माप(काष्ठा mid_q_entry), 0,
					    SLAB_HWCACHE_ALIGN, शून्य);
	अगर (cअगरs_mid_cachep == शून्य)
		वापस -ENOMEM;

	/* 3 is a reasonable minimum number of simultaneous operations */
	cअगरs_mid_poolp = mempool_create_slab_pool(3, cअगरs_mid_cachep);
	अगर (cअगरs_mid_poolp == शून्य) अणु
		kmem_cache_destroy(cअगरs_mid_cachep);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
cअगरs_destroy_mids(व्योम)
अणु
	mempool_destroy(cअगरs_mid_poolp);
	kmem_cache_destroy(cअगरs_mid_cachep);
पूर्ण

अटल पूर्णांक __init
init_cअगरs(व्योम)
अणु
	पूर्णांक rc = 0;
	cअगरs_proc_init();
	INIT_LIST_HEAD(&cअगरs_tcp_ses_list);
/*
 *  Initialize Global counters
 */
	atomic_set(&sesInfoAllocCount, 0);
	atomic_set(&tconInfoAllocCount, 0);
	atomic_set(&tcpSesNextId, 0);
	atomic_set(&tcpSesAllocCount, 0);
	atomic_set(&tcpSesReconnectCount, 0);
	atomic_set(&tconInfoReconnectCount, 0);

	atomic_set(&bufAllocCount, 0);
	atomic_set(&smBufAllocCount, 0);
#अगर_घोषित CONFIG_CIFS_STATS2
	atomic_set(&totBufAllocCount, 0);
	atomic_set(&totSmBufAllocCount, 0);
	अगर (slow_rsp_threshold < 1)
		cअगरs_dbg(FYI, "slow_response_threshold msgs disabled\n");
	अन्यथा अगर (slow_rsp_threshold > 32767)
		cअगरs_dbg(VFS,
		       "slow response threshold set higher than recommended (0 to 32767)\n");
#पूर्ण_अगर /* CONFIG_CIFS_STATS2 */

	atomic_set(&midCount, 0);
	GlobalCurrentXid = 0;
	GlobalTotalActiveXid = 0;
	GlobalMaxActiveXid = 0;
	spin_lock_init(&cअगरs_tcp_ses_lock);
	spin_lock_init(&GlobalMid_Lock);

	cअगरs_lock_secret = get_अक्रमom_u32();

	अगर (cअगरs_max_pending < 2) अणु
		cअगरs_max_pending = 2;
		cअगरs_dbg(FYI, "cifs_max_pending set to min of 2\n");
	पूर्ण अन्यथा अगर (cअगरs_max_pending > CIFS_MAX_REQ) अणु
		cअगरs_max_pending = CIFS_MAX_REQ;
		cअगरs_dbg(FYI, "cifs_max_pending set to max of %u\n",
			 CIFS_MAX_REQ);
	पूर्ण

	cअगरsiod_wq = alloc_workqueue("cifsiod", WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	अगर (!cअगरsiod_wq) अणु
		rc = -ENOMEM;
		जाओ out_clean_proc;
	पूर्ण

	/*
	 * Consider in future setting limit!=0 maybe to min(num_of_cores - 1, 3)
	 * so that we करोn't launch too many worker thपढ़ोs but
	 * Documentation/core-api/workqueue.rst recommends setting it to 0
	 */

	/* WQ_UNBOUND allows decrypt tasks to run on any CPU */
	decrypt_wq = alloc_workqueue("smb3decryptd",
				     WQ_UNBOUND|WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	अगर (!decrypt_wq) अणु
		rc = -ENOMEM;
		जाओ out_destroy_cअगरsiod_wq;
	पूर्ण

	fileinfo_put_wq = alloc_workqueue("cifsfileinfoput",
				     WQ_UNBOUND|WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	अगर (!fileinfo_put_wq) अणु
		rc = -ENOMEM;
		जाओ out_destroy_decrypt_wq;
	पूर्ण

	cअगरsoplockd_wq = alloc_workqueue("cifsoplockd",
					 WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	अगर (!cअगरsoplockd_wq) अणु
		rc = -ENOMEM;
		जाओ out_destroy_fileinfo_put_wq;
	पूर्ण

	deferredबंद_wq = alloc_workqueue("deferredclose",
					   WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	अगर (!deferredबंद_wq) अणु
		rc = -ENOMEM;
		जाओ out_destroy_cअगरsoplockd_wq;
	पूर्ण

	rc = cअगरs_fscache_रेजिस्टर();
	अगर (rc)
		जाओ out_destroy_deferredबंद_wq;

	rc = cअगरs_init_inodecache();
	अगर (rc)
		जाओ out_unreg_fscache;

	rc = cअगरs_init_mids();
	अगर (rc)
		जाओ out_destroy_inodecache;

	rc = cअगरs_init_request_bufs();
	अगर (rc)
		जाओ out_destroy_mids;

#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	rc = dfs_cache_init();
	अगर (rc)
		जाओ out_destroy_request_bufs;
#पूर्ण_अगर /* CONFIG_CIFS_DFS_UPCALL */
#अगर_घोषित CONFIG_CIFS_UPCALL
	rc = init_cअगरs_spnego();
	अगर (rc)
		जाओ out_destroy_dfs_cache;
#पूर्ण_अगर /* CONFIG_CIFS_UPCALL */
#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
	rc = cअगरs_genl_init();
	अगर (rc)
		जाओ out_रेजिस्टर_key_type;
#पूर्ण_अगर /* CONFIG_CIFS_SWN_UPCALL */

	rc = init_cअगरs_idmap();
	अगर (rc)
		जाओ out_cअगरs_swn_init;

	rc = रेजिस्टर_fileप्रणाली(&cअगरs_fs_type);
	अगर (rc)
		जाओ out_init_cअगरs_idmap;

	rc = रेजिस्टर_fileप्रणाली(&smb3_fs_type);
	अगर (rc) अणु
		unरेजिस्टर_fileप्रणाली(&cअगरs_fs_type);
		जाओ out_init_cअगरs_idmap;
	पूर्ण

	वापस 0;

out_init_cअगरs_idmap:
	निकास_cअगरs_idmap();
out_cअगरs_swn_init:
#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
	cअगरs_genl_निकास();
out_रेजिस्टर_key_type:
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_UPCALL
	निकास_cअगरs_spnego();
out_destroy_dfs_cache:
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	dfs_cache_destroy();
out_destroy_request_bufs:
#पूर्ण_अगर
	cअगरs_destroy_request_bufs();
out_destroy_mids:
	cअगरs_destroy_mids();
out_destroy_inodecache:
	cअगरs_destroy_inodecache();
out_unreg_fscache:
	cअगरs_fscache_unरेजिस्टर();
out_destroy_deferredबंद_wq:
	destroy_workqueue(deferredबंद_wq);
out_destroy_cअगरsoplockd_wq:
	destroy_workqueue(cअगरsoplockd_wq);
out_destroy_fileinfo_put_wq:
	destroy_workqueue(fileinfo_put_wq);
out_destroy_decrypt_wq:
	destroy_workqueue(decrypt_wq);
out_destroy_cअगरsiod_wq:
	destroy_workqueue(cअगरsiod_wq);
out_clean_proc:
	cअगरs_proc_clean();
	वापस rc;
पूर्ण

अटल व्योम __निकास
निकास_cअगरs(व्योम)
अणु
	cअगरs_dbg(NOISY, "exit_smb3\n");
	unरेजिस्टर_fileप्रणाली(&cअगरs_fs_type);
	unरेजिस्टर_fileप्रणाली(&smb3_fs_type);
	cअगरs_dfs_release_स्वतःmount_समयr();
	निकास_cअगरs_idmap();
#अगर_घोषित CONFIG_CIFS_SWN_UPCALL
	cअगरs_genl_निकास();
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_UPCALL
	निकास_cअगरs_spnego();
#पूर्ण_अगर
#अगर_घोषित CONFIG_CIFS_DFS_UPCALL
	dfs_cache_destroy();
#पूर्ण_अगर
	cअगरs_destroy_request_bufs();
	cअगरs_destroy_mids();
	cअगरs_destroy_inodecache();
	cअगरs_fscache_unरेजिस्टर();
	destroy_workqueue(deferredबंद_wq);
	destroy_workqueue(cअगरsoplockd_wq);
	destroy_workqueue(decrypt_wq);
	destroy_workqueue(fileinfo_put_wq);
	destroy_workqueue(cअगरsiod_wq);
	cअगरs_proc_clean();
पूर्ण

MODULE_AUTHOR("Steve French");
MODULE_LICENSE("GPL");	/* combination of LGPL + GPL source behaves as GPL */
MODULE_DESCRIPTION
	("VFS to access SMB3 servers e.g. Samba, Macs, Azure and Windows (and "
	"also older servers complying with the SNIA CIFS Specification)");
MODULE_VERSION(CIFS_VERSION);
MODULE_SOFTDEP("ecb");
MODULE_SOFTDEP("hmac");
MODULE_SOFTDEP("md4");
MODULE_SOFTDEP("md5");
MODULE_SOFTDEP("nls");
MODULE_SOFTDEP("aes");
MODULE_SOFTDEP("cmac");
MODULE_SOFTDEP("sha256");
MODULE_SOFTDEP("sha512");
MODULE_SOFTDEP("aead2");
MODULE_SOFTDEP("ccm");
MODULE_SOFTDEP("gcm");
module_init(init_cअगरs)
module_निकास(निकास_cअगरs)
