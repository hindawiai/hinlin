<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/nfs/inode.c
 *
 *  Copyright (C) 1992  Rick Sladkey
 *
 *  nfs inode and superblock handling functions
 *
 *  Modularised by Alan Cox <alan@lxorguk.ukuu.org.uk>, जबतक hacking some
 *  experimental NFS changes. Modularisation taken straight from SYS5 fs.
 *
 *  Change to nfs_पढ़ो_super() to permit NFS mounts to multi-homed hosts.
 *  J.S.Peatfield@damtp.cam.ac.uk
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/metrics.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs4_mount.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/vfs.h>
#समावेश <linux/inet.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/iversion.h>

#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "delegation.h"
#समावेश "iostat.h"
#समावेश "internal.h"
#समावेश "fscache.h"
#समावेश "pnfs.h"
#समावेश "nfs.h"
#समावेश "netns.h"
#समावेश "sysfs.h"

#समावेश "nfstrace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

#घोषणा NFS_64_BIT_INODE_NUMBERS_ENABLED	1

/* Default is to see 64-bit inode numbers */
अटल bool enable_ino64 = NFS_64_BIT_INODE_NUMBERS_ENABLED;

अटल पूर्णांक nfs_update_inode(काष्ठा inode *, काष्ठा nfs_fattr *);

अटल काष्ठा kmem_cache * nfs_inode_cachep;

अटल अंतरभूत अचिन्हित दीर्घ
nfs_fattr_to_ino_t(काष्ठा nfs_fattr *fattr)
अणु
	वापस nfs_fileid_to_ino_t(fattr->fileid);
पूर्ण

अटल पूर्णांक nfs_रुको_समाप्तable(पूर्णांक mode)
अणु
	मुक्तzable_schedule_unsafe();
	अगर (संकेत_pending_state(mode, current))
		वापस -ERESTARTSYS;
	वापस 0;
पूर्ण

पूर्णांक nfs_रुको_bit_समाप्तable(काष्ठा रुको_bit_key *key, पूर्णांक mode)
अणु
	वापस nfs_रुको_समाप्तable(mode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_रुको_bit_समाप्तable);

/**
 * nfs_compat_user_ino64 - वापसs the user-visible inode number
 * @fileid: 64-bit fileid
 *
 * This function वापसs a 32-bit inode number अगर the boot parameter
 * nfs.enable_ino64 is zero.
 */
u64 nfs_compat_user_ino64(u64 fileid)
अणु
#अगर_घोषित CONFIG_COMPAT
	compat_uदीर्घ_t ino;
#अन्यथा	
	अचिन्हित दीर्घ ino;
#पूर्ण_अगर

	अगर (enable_ino64)
		वापस fileid;
	ino = fileid;
	अगर (माप(ino) < माप(fileid))
		ino ^= fileid >> (माप(fileid)-माप(ino)) * 8;
	वापस ino;
पूर्ण

पूर्णांक nfs_drop_inode(काष्ठा inode *inode)
अणु
	वापस NFS_STALE(inode) || generic_drop_inode(inode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_drop_inode);

व्योम nfs_clear_inode(काष्ठा inode *inode)
अणु
	/*
	 * The following should never happen...
	 */
	WARN_ON_ONCE(nfs_have_ग_लिखोbacks(inode));
	WARN_ON_ONCE(!list_empty(&NFS_I(inode)->खोलो_files));
	nfs_zap_acl_cache(inode);
	nfs_access_zap_cache(inode);
	nfs_fscache_clear_inode(inode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_clear_inode);

व्योम nfs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	nfs_clear_inode(inode);
पूर्ण

पूर्णांक nfs_sync_inode(काष्ठा inode *inode)
अणु
	inode_dio_रुको(inode);
	वापस nfs_wb_all(inode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_sync_inode);

/**
 * nfs_sync_mapping - helper to flush all mmapped dirty data to disk
 * @mapping: poपूर्णांकer to काष्ठा address_space
 */
पूर्णांक nfs_sync_mapping(काष्ठा address_space *mapping)
अणु
	पूर्णांक ret = 0;

	अगर (mapping->nrpages != 0) अणु
		unmap_mapping_range(mapping, 0, 0, 0);
		ret = nfs_wb_all(mapping->host);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nfs_attribute_समयout(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	वापस !समय_in_range_खोलो(jअगरfies, nfsi->पढ़ो_cache_jअगरfies, nfsi->पढ़ो_cache_jअगरfies + nfsi->attrसमयo);
पूर्ण

अटल bool nfs_check_cache_flags_invalid(काष्ठा inode *inode,
					  अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ cache_validity = READ_ONCE(NFS_I(inode)->cache_validity);

	वापस (cache_validity & flags) != 0;
पूर्ण

bool nfs_check_cache_invalid(काष्ठा inode *inode, अचिन्हित दीर्घ flags)
अणु
	अगर (nfs_check_cache_flags_invalid(inode, flags))
		वापस true;
	वापस nfs_attribute_cache_expired(inode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_check_cache_invalid);

#अगर_घोषित CONFIG_NFS_V4_2
अटल bool nfs_has_xattr_cache(स्थिर काष्ठा nfs_inode *nfsi)
अणु
	वापस nfsi->xattr_cache != शून्य;
पूर्ण
#अन्यथा
अटल bool nfs_has_xattr_cache(स्थिर काष्ठा nfs_inode *nfsi)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

व्योम nfs_set_cache_invalid(काष्ठा inode *inode, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	bool have_delegation = NFS_PROTO(inode)->have_delegation(inode, FMODE_READ);

	अगर (have_delegation) अणु
		अगर (!(flags & NFS_INO_REVAL_FORCED))
			flags &= ~(NFS_INO_INVALID_MODE |
				   NFS_INO_INVALID_OTHER |
				   NFS_INO_INVALID_XATTR);
		flags &= ~(NFS_INO_INVALID_CHANGE | NFS_INO_INVALID_SIZE);
	पूर्ण अन्यथा अगर (flags & NFS_INO_REVAL_PAGECACHE)
		flags |= NFS_INO_INVALID_CHANGE | NFS_INO_INVALID_SIZE;

	अगर (!nfs_has_xattr_cache(nfsi))
		flags &= ~NFS_INO_INVALID_XATTR;
	अगर (flags & NFS_INO_INVALID_DATA)
		nfs_fscache_invalidate(inode);
	अगर (inode->i_mapping->nrpages == 0)
		flags &= ~(NFS_INO_INVALID_DATA|NFS_INO_DATA_INVAL_DEFER);
	flags &= ~(NFS_INO_REVAL_PAGECACHE | NFS_INO_REVAL_FORCED);
	nfsi->cache_validity |= flags;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_set_cache_invalid);

/*
 * Invalidate the local caches
 */
अटल व्योम nfs_zap_caches_locked(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	पूर्णांक mode = inode->i_mode;

	nfs_inc_stats(inode, NFSIOS_ATTRINVALIDATE);

	nfsi->attrसमयo = NFS_MINATTRTIMEO(inode);
	nfsi->attrसमयo_बारtamp = jअगरfies;

	अगर (S_ISREG(mode) || S_ISसूची(mode) || S_ISLNK(mode)) अणु
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATTR
					| NFS_INO_INVALID_DATA
					| NFS_INO_INVALID_ACCESS
					| NFS_INO_INVALID_ACL
					| NFS_INO_INVALID_XATTR
					| NFS_INO_REVAL_PAGECACHE);
	पूर्ण अन्यथा
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATTR
					| NFS_INO_INVALID_ACCESS
					| NFS_INO_INVALID_ACL
					| NFS_INO_INVALID_XATTR
					| NFS_INO_REVAL_PAGECACHE);
	nfs_zap_label_cache_locked(nfsi);
पूर्ण

व्योम nfs_zap_caches(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	nfs_zap_caches_locked(inode);
	spin_unlock(&inode->i_lock);
पूर्ण

व्योम nfs_zap_mapping(काष्ठा inode *inode, काष्ठा address_space *mapping)
अणु
	अगर (mapping->nrpages != 0) अणु
		spin_lock(&inode->i_lock);
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA);
		spin_unlock(&inode->i_lock);
	पूर्ण
पूर्ण

व्योम nfs_zap_acl_cache(काष्ठा inode *inode)
अणु
	व्योम (*clear_acl_cache)(काष्ठा inode *);

	clear_acl_cache = NFS_PROTO(inode)->clear_acl_cache;
	अगर (clear_acl_cache != शून्य)
		clear_acl_cache(inode);
	spin_lock(&inode->i_lock);
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_ACL;
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_zap_acl_cache);

व्योम nfs_invalidate_aसमय(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATIME);
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_invalidate_aसमय);

/*
 * Invalidate, but करो not unhash, the inode.
 * NB: must be called with inode->i_lock held!
 */
अटल व्योम nfs_set_inode_stale_locked(काष्ठा inode *inode)
अणु
	set_bit(NFS_INO_STALE, &NFS_I(inode)->flags);
	nfs_zap_caches_locked(inode);
	trace_nfs_set_inode_stale(inode);
पूर्ण

व्योम nfs_set_inode_stale(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	nfs_set_inode_stale_locked(inode);
	spin_unlock(&inode->i_lock);
पूर्ण

काष्ठा nfs_find_desc अणु
	काष्ठा nfs_fh		*fh;
	काष्ठा nfs_fattr	*fattr;
पूर्ण;

/*
 * In NFSv3 we can have 64bit inode numbers. In order to support
 * this, and re-exported directories (also seen in NFSv2)
 * we are क्रमced to allow 2 dअगरferent inodes to have the same
 * i_ino.
 */
अटल पूर्णांक
nfs_find_actor(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा nfs_find_desc	*desc = (काष्ठा nfs_find_desc *)opaque;
	काष्ठा nfs_fh		*fh = desc->fh;
	काष्ठा nfs_fattr	*fattr = desc->fattr;

	अगर (NFS_खाताID(inode) != fattr->fileid)
		वापस 0;
	अगर (inode_wrong_type(inode, fattr->mode))
		वापस 0;
	अगर (nfs_compare_fh(NFS_FH(inode), fh))
		वापस 0;
	अगर (is_bad_inode(inode) || NFS_STALE(inode))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक
nfs_init_locked(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा nfs_find_desc	*desc = (काष्ठा nfs_find_desc *)opaque;
	काष्ठा nfs_fattr	*fattr = desc->fattr;

	set_nfs_fileid(inode, fattr->fileid);
	inode->i_mode = fattr->mode;
	nfs_copy_fh(NFS_FH(inode), desc->fh);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
अटल व्योम nfs_clear_label_invalid(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_LABEL;
	spin_unlock(&inode->i_lock);
पूर्ण

व्योम nfs_setsecurity(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr,
					काष्ठा nfs4_label *label)
अणु
	पूर्णांक error;

	अगर (label == शून्य)
		वापस;

	अगर ((fattr->valid & NFS_ATTR_FATTR_V4_SECURITY_LABEL) && inode->i_security) अणु
		error = security_inode_notअगरysecctx(inode, label->label,
				label->len);
		अगर (error)
			prपूर्णांकk(KERN_ERR "%s() %s %d "
					"security_inode_notifysecctx() %d\n",
					__func__,
					(अक्षर *)label->label,
					label->len, error);
		nfs_clear_label_invalid(inode);
	पूर्ण
पूर्ण

काष्ठा nfs4_label *nfs4_label_alloc(काष्ठा nfs_server *server, gfp_t flags)
अणु
	काष्ठा nfs4_label *label = शून्य;
	पूर्णांक minor_version = server->nfs_client->cl_minorversion;

	अगर (minor_version < 2)
		वापस label;

	अगर (!(server->caps & NFS_CAP_SECURITY_LABEL))
		वापस label;

	label = kzalloc(माप(काष्ठा nfs4_label), flags);
	अगर (label == शून्य)
		वापस ERR_PTR(-ENOMEM);

	label->label = kzalloc(NFS4_MAXLABELLEN, flags);
	अगर (label->label == शून्य) अणु
		kमुक्त(label);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	label->len = NFS4_MAXLABELLEN;

	वापस label;
पूर्ण
EXPORT_SYMBOL_GPL(nfs4_label_alloc);
#अन्यथा
व्योम nfs_setsecurity(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr,
					काष्ठा nfs4_label *label)
अणु
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL_GPL(nfs_setsecurity);

/* Search क्रम inode identअगरied by fh, fileid and i_mode in inode cache. */
काष्ठा inode *
nfs_ilookup(काष्ठा super_block *sb, काष्ठा nfs_fattr *fattr, काष्ठा nfs_fh *fh)
अणु
	काष्ठा nfs_find_desc desc = अणु
		.fh	= fh,
		.fattr	= fattr,
	पूर्ण;
	काष्ठा inode *inode;
	अचिन्हित दीर्घ hash;

	अगर (!(fattr->valid & NFS_ATTR_FATTR_खाताID) ||
	    !(fattr->valid & NFS_ATTR_FATTR_TYPE))
		वापस शून्य;

	hash = nfs_fattr_to_ino_t(fattr);
	inode = ilookup5(sb, hash, nfs_find_actor, &desc);

	dprपूर्णांकk("%s: returning %p\n", __func__, inode);
	वापस inode;
पूर्ण

/*
 * This is our front-end to iget that looks up inodes by file handle
 * instead of inode number.
 */
काष्ठा inode *
nfs_fhget(काष्ठा super_block *sb, काष्ठा nfs_fh *fh, काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs_find_desc desc = अणु
		.fh	= fh,
		.fattr	= fattr
	पूर्ण;
	काष्ठा inode *inode = ERR_PTR(-ENOENT);
	u64 fattr_supported = NFS_SB(sb)->fattr_valid;
	अचिन्हित दीर्घ hash;

	nfs_attr_check_mountpoपूर्णांक(sb, fattr);

	अगर (nfs_attr_use_mounted_on_fileid(fattr))
		fattr->fileid = fattr->mounted_on_fileid;
	अन्यथा अगर ((fattr->valid & NFS_ATTR_FATTR_खाताID) == 0)
		जाओ out_no_inode;
	अगर ((fattr->valid & NFS_ATTR_FATTR_TYPE) == 0)
		जाओ out_no_inode;

	hash = nfs_fattr_to_ino_t(fattr);

	inode = iget5_locked(sb, hash, nfs_find_actor, nfs_init_locked, &desc);
	अगर (inode == शून्य) अणु
		inode = ERR_PTR(-ENOMEM);
		जाओ out_no_inode;
	पूर्ण

	अगर (inode->i_state & I_NEW) अणु
		काष्ठा nfs_inode *nfsi = NFS_I(inode);
		अचिन्हित दीर्घ now = jअगरfies;

		/* We set i_ino क्रम the few things that still rely on it,
		 * such as stat(2) */
		inode->i_ino = hash;

		/* We can't support update_aसमय(), since the server will reset it */
		inode->i_flags |= S_NOATIME|S_NOCMTIME;
		inode->i_mode = fattr->mode;
		nfsi->cache_validity = 0;
		अगर ((fattr->valid & NFS_ATTR_FATTR_MODE) == 0
				&& (fattr_supported & NFS_ATTR_FATTR_MODE))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_MODE);
		/* Why so? Because we want revalidate क्रम devices/FIFOs, and
		 * that's precisely what we have in nfs_file_inode_operations.
		 */
		inode->i_op = NFS_SB(sb)->nfs_client->rpc_ops->file_inode_ops;
		अगर (S_ISREG(inode->i_mode)) अणु
			inode->i_fop = NFS_SB(sb)->nfs_client->rpc_ops->file_ops;
			inode->i_data.a_ops = &nfs_file_aops;
		पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
			inode->i_op = NFS_SB(sb)->nfs_client->rpc_ops->dir_inode_ops;
			inode->i_fop = &nfs_dir_operations;
			inode->i_data.a_ops = &nfs_dir_aops;
			/* Deal with crossing mountpoपूर्णांकs */
			अगर (fattr->valid & NFS_ATTR_FATTR_MOUNTPOINT ||
					fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL) अणु
				अगर (fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL)
					inode->i_op = &nfs_referral_inode_operations;
				अन्यथा
					inode->i_op = &nfs_mountpoपूर्णांक_inode_operations;
				inode->i_fop = शून्य;
				inode->i_flags |= S_AUTOMOUNT;
			पूर्ण
		पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
			inode->i_op = &nfs_symlink_inode_operations;
			inode_nohighmem(inode);
		पूर्ण अन्यथा
			init_special_inode(inode, inode->i_mode, fattr->rdev);

		स_रखो(&inode->i_aसमय, 0, माप(inode->i_aसमय));
		स_रखो(&inode->i_mसमय, 0, माप(inode->i_mसमय));
		स_रखो(&inode->i_स_समय, 0, माप(inode->i_स_समय));
		inode_set_iversion_raw(inode, 0);
		inode->i_size = 0;
		clear_nlink(inode);
		inode->i_uid = make_kuid(&init_user_ns, -2);
		inode->i_gid = make_kgid(&init_user_ns, -2);
		inode->i_blocks = 0;
		स_रखो(nfsi->cookieverf, 0, माप(nfsi->cookieverf));
		nfsi->ग_लिखो_io = 0;
		nfsi->पढ़ो_io = 0;

		nfsi->पढ़ो_cache_jअगरfies = fattr->समय_start;
		nfsi->attr_gencount = fattr->gencount;
		अगर (fattr->valid & NFS_ATTR_FATTR_ATIME)
			inode->i_aसमय = fattr->aसमय;
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_ATIME)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATIME);
		अगर (fattr->valid & NFS_ATTR_FATTR_MTIME)
			inode->i_mसमय = fattr->mसमय;
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_MTIME)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_MTIME);
		अगर (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_स_समय = fattr->स_समय;
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_CTIME)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CTIME);
		अगर (fattr->valid & NFS_ATTR_FATTR_CHANGE)
			inode_set_iversion_raw(inode, fattr->change_attr);
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE);
		अगर (fattr->valid & NFS_ATTR_FATTR_SIZE)
			inode->i_size = nfs_माप_प्रकारo_loff_t(fattr->size);
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_SIZE);
		अगर (fattr->valid & NFS_ATTR_FATTR_NLINK)
			set_nlink(inode, fattr->nlink);
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_NLINK)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_NLINK);
		अगर (fattr->valid & NFS_ATTR_FATTR_OWNER)
			inode->i_uid = fattr->uid;
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_OWNER)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_OTHER);
		अगर (fattr->valid & NFS_ATTR_FATTR_GROUP)
			inode->i_gid = fattr->gid;
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_GROUP)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_OTHER);
		अगर (nfs_server_capable(inode, NFS_CAP_XATTR))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_XATTR);
		अगर (fattr->valid & NFS_ATTR_FATTR_BLOCKS_USED)
			inode->i_blocks = fattr->du.nfs2.blocks;
		अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_BLOCKS_USED &&
			 fattr->size != 0)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_BLOCKS);
		अगर (fattr->valid & NFS_ATTR_FATTR_SPACE_USED) अणु
			/*
			 * report the blocks in 512byte units
			 */
			inode->i_blocks = nfs_calc_block_size(fattr->du.nfs3.used);
		पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_SPACE_USED &&
			   fattr->size != 0)
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_BLOCKS);

		nfs_setsecurity(inode, fattr, label);

		nfsi->attrसमयo = NFS_MINATTRTIMEO(inode);
		nfsi->attrसमयo_बारtamp = now;
		nfsi->access_cache = RB_ROOT;

		nfs_fscache_init_inode(inode);

		unlock_new_inode(inode);
	पूर्ण अन्यथा अणु
		पूर्णांक err = nfs_refresh_inode(inode, fattr);
		अगर (err < 0) अणु
			iput(inode);
			inode = ERR_PTR(err);
			जाओ out_no_inode;
		पूर्ण
	पूर्ण
	dprपूर्णांकk("NFS: nfs_fhget(%s/%Lu fh_crc=0x%08x ct=%d)\n",
		inode->i_sb->s_id,
		(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode),
		nfs_display_fhandle_hash(fh),
		atomic_पढ़ो(&inode->i_count));

out:
	वापस inode;

out_no_inode:
	dprपूर्णांकk("nfs_fhget: iget failed with error %ld\n", PTR_ERR(inode));
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_fhget);

#घोषणा NFS_VALID_ATTRS (ATTR_MODE|ATTR_UID|ATTR_GID|ATTR_SIZE|ATTR_ATIME|ATTR_ATIME_SET|ATTR_MTIME|ATTR_MTIME_SET|ATTR_खाता|ATTR_OPEN)

पूर्णांक
nfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
	    काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा nfs_fattr *fattr;
	पूर्णांक error = 0;

	nfs_inc_stats(inode, NFSIOS_VFSSETATTR);

	/* skip mode change अगर it's just क्रम clearing setuid/setgid */
	अगर (attr->ia_valid & (ATTR_KILL_SUID | ATTR_KILL_SGID))
		attr->ia_valid &= ~ATTR_MODE;

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		BUG_ON(!S_ISREG(inode->i_mode));

		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			वापस error;

		अगर (attr->ia_size == i_size_पढ़ो(inode))
			attr->ia_valid &= ~ATTR_SIZE;
	पूर्ण

	/* Optimization: अगर the end result is no change, करोn't RPC */
	अगर (((attr->ia_valid & NFS_VALID_ATTRS) & ~(ATTR_खाता|ATTR_OPEN)) == 0)
		वापस 0;

	trace_nfs_setattr_enter(inode);

	/* Write all dirty data */
	अगर (S_ISREG(inode->i_mode))
		nfs_sync_inode(inode);

	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	error = NFS_PROTO(inode)->setattr(dentry, fattr, attr);
	अगर (error == 0)
		error = nfs_refresh_inode(inode, fattr);
	nfs_मुक्त_fattr(fattr);
out:
	trace_nfs_setattr_निकास(inode, error);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_setattr);

/**
 * nfs_vmtruncate - unmap mappings "freed" by truncate() syscall
 * @inode: inode of the file used
 * @offset: file offset to start truncating
 *
 * This is a copy of the common vmtruncate, but with the locking
 * corrected to take पूर्णांकo account the fact that NFS requires
 * inode->i_size to be updated under the inode->i_lock.
 * Note: must be called with inode->i_lock held!
 */
अटल पूर्णांक nfs_vmtruncate(काष्ठा inode * inode, loff_t offset)
अणु
	पूर्णांक err;

	err = inode_newsize_ok(inode, offset);
	अगर (err)
		जाओ out;

	i_size_ग_लिखो(inode, offset);
	/* Optimisation */
	अगर (offset == 0)
		NFS_I(inode)->cache_validity &= ~(NFS_INO_INVALID_DATA |
				NFS_INO_DATA_INVAL_DEFER);
	NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_SIZE;

	spin_unlock(&inode->i_lock);
	truncate_pagecache(inode, offset);
	spin_lock(&inode->i_lock);
out:
	वापस err;
पूर्ण

/**
 * nfs_setattr_update_inode - Update inode metadata after a setattr call.
 * @inode: poपूर्णांकer to काष्ठा inode
 * @attr: poपूर्णांकer to काष्ठा iattr
 * @fattr: poपूर्णांकer to काष्ठा nfs_fattr
 *
 * Note: we करो this in the *proc.c in order to ensure that
 *       it works क्रम things like exclusive creates too.
 */
व्योम nfs_setattr_update_inode(काष्ठा inode *inode, काष्ठा iattr *attr,
		काष्ठा nfs_fattr *fattr)
अणु
	/* Barrier: bump the attribute generation count. */
	nfs_fattr_set_barrier(fattr);

	spin_lock(&inode->i_lock);
	NFS_I(inode)->attr_gencount = fattr->gencount;
	अगर ((attr->ia_valid & ATTR_SIZE) != 0) अणु
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_MTIME |
						     NFS_INO_INVALID_BLOCKS);
		nfs_inc_stats(inode, NFSIOS_SETATTRTRUNC);
		nfs_vmtruncate(inode, attr->ia_size);
	पूर्ण
	अगर ((attr->ia_valid & (ATTR_MODE|ATTR_UID|ATTR_GID)) != 0) अणु
		NFS_I(inode)->cache_validity &= ~NFS_INO_INVALID_CTIME;
		अगर ((attr->ia_valid & ATTR_KILL_SUID) != 0 &&
		    inode->i_mode & S_ISUID)
			inode->i_mode &= ~S_ISUID;
		अगर ((attr->ia_valid & ATTR_KILL_SGID) != 0 &&
		    (inode->i_mode & (S_ISGID | S_IXGRP)) ==
		     (S_ISGID | S_IXGRP))
			inode->i_mode &= ~S_ISGID;
		अगर ((attr->ia_valid & ATTR_MODE) != 0) अणु
			पूर्णांक mode = attr->ia_mode & S_IALLUGO;
			mode |= inode->i_mode & ~S_IALLUGO;
			inode->i_mode = mode;
		पूर्ण
		अगर ((attr->ia_valid & ATTR_UID) != 0)
			inode->i_uid = attr->ia_uid;
		अगर ((attr->ia_valid & ATTR_GID) != 0)
			inode->i_gid = attr->ia_gid;
		अगर (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_स_समय = fattr->स_समय;
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE
					| NFS_INO_INVALID_CTIME);
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_ACCESS
				| NFS_INO_INVALID_ACL);
	पूर्ण
	अगर (attr->ia_valid & (ATTR_ATIME_SET|ATTR_ATIME)) अणु
		NFS_I(inode)->cache_validity &= ~(NFS_INO_INVALID_ATIME
				| NFS_INO_INVALID_CTIME);
		अगर (fattr->valid & NFS_ATTR_FATTR_ATIME)
			inode->i_aसमय = fattr->aसमय;
		अन्यथा अगर (attr->ia_valid & ATTR_ATIME_SET)
			inode->i_aसमय = attr->ia_aसमय;
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_ATIME);

		अगर (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_स_समय = fattr->स_समय;
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE
					| NFS_INO_INVALID_CTIME);
	पूर्ण
	अगर (attr->ia_valid & (ATTR_MTIME_SET|ATTR_MTIME)) अणु
		NFS_I(inode)->cache_validity &= ~(NFS_INO_INVALID_MTIME
				| NFS_INO_INVALID_CTIME);
		अगर (fattr->valid & NFS_ATTR_FATTR_MTIME)
			inode->i_mसमय = fattr->mसमय;
		अन्यथा अगर (attr->ia_valid & ATTR_MTIME_SET)
			inode->i_mसमय = attr->ia_mसमय;
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_MTIME);

		अगर (fattr->valid & NFS_ATTR_FATTR_CTIME)
			inode->i_स_समय = fattr->स_समय;
		अन्यथा
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE
					| NFS_INO_INVALID_CTIME);
	पूर्ण
	अगर (fattr->valid)
		nfs_update_inode(inode, fattr);
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_setattr_update_inode);

अटल व्योम nfs_सूची_पढ़ोplus_parent_cache_miss(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;

	अगर (!nfs_server_capable(d_inode(dentry), NFS_CAP_READसूचीPLUS))
		वापस;
	parent = dget_parent(dentry);
	nfs_क्रमce_use_सूची_पढ़ोplus(d_inode(parent));
	dput(parent);
पूर्ण

अटल व्योम nfs_सूची_पढ़ोplus_parent_cache_hit(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;

	अगर (!nfs_server_capable(d_inode(dentry), NFS_CAP_READसूचीPLUS))
		वापस;
	parent = dget_parent(dentry);
	nfs_advise_use_सूची_पढ़ोplus(d_inode(parent));
	dput(parent);
पूर्ण

अटल u32 nfs_get_valid_attrmask(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ cache_validity = READ_ONCE(NFS_I(inode)->cache_validity);
	u32 reply_mask = STATX_INO | STATX_TYPE;

	अगर (!(cache_validity & NFS_INO_INVALID_ATIME))
		reply_mask |= STATX_ATIME;
	अगर (!(cache_validity & NFS_INO_INVALID_CTIME))
		reply_mask |= STATX_CTIME;
	अगर (!(cache_validity & NFS_INO_INVALID_MTIME))
		reply_mask |= STATX_MTIME;
	अगर (!(cache_validity & NFS_INO_INVALID_SIZE))
		reply_mask |= STATX_SIZE;
	अगर (!(cache_validity & NFS_INO_INVALID_NLINK))
		reply_mask |= STATX_NLINK;
	अगर (!(cache_validity & NFS_INO_INVALID_MODE))
		reply_mask |= STATX_MODE;
	अगर (!(cache_validity & NFS_INO_INVALID_OTHER))
		reply_mask |= STATX_UID | STATX_GID;
	अगर (!(cache_validity & NFS_INO_INVALID_BLOCKS))
		reply_mask |= STATX_BLOCKS;
	वापस reply_mask;
पूर्ण

पूर्णांक nfs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	अचिन्हित दीर्घ cache_validity;
	पूर्णांक err = 0;
	bool क्रमce_sync = query_flags & AT_STATX_FORCE_SYNC;
	bool करो_update = false;

	trace_nfs_getattr_enter(inode);

	request_mask &= STATX_TYPE | STATX_MODE | STATX_NLINK | STATX_UID |
			STATX_GID | STATX_ATIME | STATX_MTIME | STATX_CTIME |
			STATX_INO | STATX_SIZE | STATX_BLOCKS;

	अगर ((query_flags & AT_STATX_DONT_SYNC) && !क्रमce_sync) अणु
		nfs_सूची_पढ़ोplus_parent_cache_hit(path->dentry);
		जाओ out_no_revalidate;
	पूर्ण

	/* Flush out ग_लिखोs to the server in order to update c/mसमय.  */
	अगर ((request_mask & (STATX_CTIME|STATX_MTIME)) &&
			S_ISREG(inode->i_mode)) अणु
		err = filemap_ग_लिखो_and_रुको(inode->i_mapping);
		अगर (err)
			जाओ out;
	पूर्ण

	/*
	 * We may क्रमce a getattr अगर the user cares about aसमय.
	 *
	 * Note that we only have to check the vfsmount flags here:
	 *  - NFS always sets S_NOATIME by so checking it would give a
	 *    bogus result
	 *  - NFS never sets SB_NOATIME or SB_NOसूचीATIME so there is
	 *    no poपूर्णांक in checking those.
	 */
	अगर ((path->mnt->mnt_flags & MNT_NOATIME) ||
	    ((path->mnt->mnt_flags & MNT_NOसूचीATIME) && S_ISसूची(inode->i_mode)))
		request_mask &= ~STATX_ATIME;

	/* Is the user requesting attributes that might need revalidation? */
	अगर (!(request_mask & (STATX_MODE|STATX_NLINK|STATX_ATIME|STATX_CTIME|
					STATX_MTIME|STATX_UID|STATX_GID|
					STATX_SIZE|STATX_BLOCKS)))
		जाओ out_no_revalidate;

	/* Check whether the cached attributes are stale */
	करो_update |= क्रमce_sync || nfs_attribute_cache_expired(inode);
	cache_validity = READ_ONCE(NFS_I(inode)->cache_validity);
	करो_update |= cache_validity & NFS_INO_INVALID_CHANGE;
	अगर (request_mask & STATX_ATIME)
		करो_update |= cache_validity & NFS_INO_INVALID_ATIME;
	अगर (request_mask & STATX_CTIME)
		करो_update |= cache_validity & NFS_INO_INVALID_CTIME;
	अगर (request_mask & STATX_MTIME)
		करो_update |= cache_validity & NFS_INO_INVALID_MTIME;
	अगर (request_mask & STATX_SIZE)
		करो_update |= cache_validity & NFS_INO_INVALID_SIZE;
	अगर (request_mask & STATX_NLINK)
		करो_update |= cache_validity & NFS_INO_INVALID_NLINK;
	अगर (request_mask & STATX_MODE)
		करो_update |= cache_validity & NFS_INO_INVALID_MODE;
	अगर (request_mask & (STATX_UID | STATX_GID))
		करो_update |= cache_validity & NFS_INO_INVALID_OTHER;
	अगर (request_mask & STATX_BLOCKS)
		करो_update |= cache_validity & NFS_INO_INVALID_BLOCKS;

	अगर (करो_update) अणु
		/* Update the attribute cache */
		अगर (!(server->flags & NFS_MOUNT_NOAC))
			nfs_सूची_पढ़ोplus_parent_cache_miss(path->dentry);
		अन्यथा
			nfs_सूची_पढ़ोplus_parent_cache_hit(path->dentry);
		err = __nfs_revalidate_inode(server, inode);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा
		nfs_सूची_पढ़ोplus_parent_cache_hit(path->dentry);
out_no_revalidate:
	/* Only वापस attributes that were revalidated. */
	stat->result_mask = nfs_get_valid_attrmask(inode) | request_mask;

	generic_fillattr(&init_user_ns, inode, stat);
	stat->ino = nfs_compat_user_ino64(NFS_खाताID(inode));
	अगर (S_ISसूची(inode->i_mode))
		stat->blksize = NFS_SERVER(inode)->dtsize;
out:
	trace_nfs_getattr_निकास(inode, err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_getattr);

अटल व्योम nfs_init_lock_context(काष्ठा nfs_lock_context *l_ctx)
अणु
	refcount_set(&l_ctx->count, 1);
	l_ctx->lockowner = current->files;
	INIT_LIST_HEAD(&l_ctx->list);
	atomic_set(&l_ctx->io_count, 0);
पूर्ण

अटल काष्ठा nfs_lock_context *__nfs_find_lock_context(काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा nfs_lock_context *pos;

	list_क्रम_each_entry_rcu(pos, &ctx->lock_context.list, list) अणु
		अगर (pos->lockowner != current->files)
			जारी;
		अगर (refcount_inc_not_zero(&pos->count))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा nfs_lock_context *nfs_get_lock_context(काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा nfs_lock_context *res, *new = शून्य;
	काष्ठा inode *inode = d_inode(ctx->dentry);

	rcu_पढ़ो_lock();
	res = __nfs_find_lock_context(ctx);
	rcu_पढ़ो_unlock();
	अगर (res == शून्य) अणु
		new = kदो_स्मृति(माप(*new), GFP_KERNEL);
		अगर (new == शून्य)
			वापस ERR_PTR(-ENOMEM);
		nfs_init_lock_context(new);
		spin_lock(&inode->i_lock);
		res = __nfs_find_lock_context(ctx);
		अगर (res == शून्य) अणु
			new->खोलो_context = get_nfs_खोलो_context(ctx);
			अगर (new->खोलो_context) अणु
				list_add_tail_rcu(&new->list,
						&ctx->lock_context.list);
				res = new;
				new = शून्य;
			पूर्ण अन्यथा
				res = ERR_PTR(-EBADF);
		पूर्ण
		spin_unlock(&inode->i_lock);
		kमुक्त(new);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_get_lock_context);

व्योम nfs_put_lock_context(काष्ठा nfs_lock_context *l_ctx)
अणु
	काष्ठा nfs_खोलो_context *ctx = l_ctx->खोलो_context;
	काष्ठा inode *inode = d_inode(ctx->dentry);

	अगर (!refcount_dec_and_lock(&l_ctx->count, &inode->i_lock))
		वापस;
	list_del_rcu(&l_ctx->list);
	spin_unlock(&inode->i_lock);
	put_nfs_खोलो_context(ctx);
	kमुक्त_rcu(l_ctx, rcu_head);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_put_lock_context);

/**
 * nfs_बंद_context - Common बंद_context() routine NFSv2/v3
 * @ctx: poपूर्णांकer to context
 * @is_sync: is this a synchronous बंद
 *
 * Ensure that the attributes are up to date अगर we're mounted
 * with बंद-to-खोलो semantics and we have cached data that will
 * need to be revalidated on खोलो.
 */
व्योम nfs_बंद_context(काष्ठा nfs_खोलो_context *ctx, पूर्णांक is_sync)
अणु
	काष्ठा nfs_inode *nfsi;
	काष्ठा inode *inode;

	अगर (!(ctx->mode & FMODE_WRITE))
		वापस;
	अगर (!is_sync)
		वापस;
	inode = d_inode(ctx->dentry);
	अगर (NFS_PROTO(inode)->have_delegation(inode, FMODE_READ))
		वापस;
	nfsi = NFS_I(inode);
	अगर (inode->i_mapping->nrpages == 0)
		वापस;
	अगर (nfsi->cache_validity & NFS_INO_INVALID_DATA)
		वापस;
	अगर (!list_empty(&nfsi->खोलो_files))
		वापस;
	अगर (NFS_SERVER(inode)->flags & NFS_MOUNT_NOCTO)
		वापस;
	nfs_revalidate_inode(inode,
			     NFS_INO_INVALID_CHANGE | NFS_INO_INVALID_SIZE);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_बंद_context);

काष्ठा nfs_खोलो_context *alloc_nfs_खोलो_context(काष्ठा dentry *dentry,
						भ_शेषe_t f_mode,
						काष्ठा file *filp)
अणु
	काष्ठा nfs_खोलो_context *ctx;

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);
	nfs_sb_active(dentry->d_sb);
	ctx->dentry = dget(dentry);
	अगर (filp)
		ctx->cred = get_cred(filp->f_cred);
	अन्यथा
		ctx->cred = get_current_cred();
	ctx->ll_cred = शून्य;
	ctx->state = शून्य;
	ctx->mode = f_mode;
	ctx->flags = 0;
	ctx->error = 0;
	ctx->flock_owner = (fl_owner_t)filp;
	nfs_init_lock_context(&ctx->lock_context);
	ctx->lock_context.खोलो_context = ctx;
	INIT_LIST_HEAD(&ctx->list);
	ctx->mdsthreshold = शून्य;
	वापस ctx;
पूर्ण
EXPORT_SYMBOL_GPL(alloc_nfs_खोलो_context);

काष्ठा nfs_खोलो_context *get_nfs_खोलो_context(काष्ठा nfs_खोलो_context *ctx)
अणु
	अगर (ctx != शून्य && refcount_inc_not_zero(&ctx->lock_context.count))
		वापस ctx;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(get_nfs_खोलो_context);

अटल व्योम __put_nfs_खोलो_context(काष्ठा nfs_खोलो_context *ctx, पूर्णांक is_sync)
अणु
	काष्ठा inode *inode = d_inode(ctx->dentry);
	काष्ठा super_block *sb = ctx->dentry->d_sb;

	अगर (!refcount_dec_and_test(&ctx->lock_context.count))
		वापस;
	अगर (!list_empty(&ctx->list)) अणु
		spin_lock(&inode->i_lock);
		list_del_rcu(&ctx->list);
		spin_unlock(&inode->i_lock);
	पूर्ण
	अगर (inode != शून्य)
		NFS_PROTO(inode)->बंद_context(ctx, is_sync);
	put_cred(ctx->cred);
	dput(ctx->dentry);
	nfs_sb_deactive(sb);
	put_rpccred(ctx->ll_cred);
	kमुक्त(ctx->mdsthreshold);
	kमुक्त_rcu(ctx, rcu_head);
पूर्ण

व्योम put_nfs_खोलो_context(काष्ठा nfs_खोलो_context *ctx)
अणु
	__put_nfs_खोलो_context(ctx, 0);
पूर्ण
EXPORT_SYMBOL_GPL(put_nfs_खोलो_context);

अटल व्योम put_nfs_खोलो_context_sync(काष्ठा nfs_खोलो_context *ctx)
अणु
	__put_nfs_खोलो_context(ctx, 1);
पूर्ण

/*
 * Ensure that mmap has a recent RPC credential क्रम use when writing out
 * shared pages
 */
व्योम nfs_inode_attach_खोलो_context(काष्ठा nfs_खोलो_context *ctx)
अणु
	काष्ठा inode *inode = d_inode(ctx->dentry);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	spin_lock(&inode->i_lock);
	अगर (list_empty(&nfsi->खोलो_files) &&
	    (nfsi->cache_validity & NFS_INO_DATA_INVAL_DEFER))
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA |
						     NFS_INO_REVAL_FORCED);
	list_add_tail_rcu(&ctx->list, &nfsi->खोलो_files);
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_inode_attach_खोलो_context);

व्योम nfs_file_set_खोलो_context(काष्ठा file *filp, काष्ठा nfs_खोलो_context *ctx)
अणु
	filp->निजी_data = get_nfs_खोलो_context(ctx);
	अगर (list_empty(&ctx->list))
		nfs_inode_attach_खोलो_context(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_file_set_खोलो_context);

/*
 * Given an inode, search क्रम an खोलो context with the desired अक्षरacteristics
 */
काष्ठा nfs_खोलो_context *nfs_find_खोलो_context(काष्ठा inode *inode, स्थिर काष्ठा cred *cred, भ_शेषe_t mode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	काष्ठा nfs_खोलो_context *pos, *ctx = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pos, &nfsi->खोलो_files, list) अणु
		अगर (cred != शून्य && cred_fscmp(pos->cred, cred) != 0)
			जारी;
		अगर ((pos->mode & (FMODE_READ|FMODE_WRITE)) != mode)
			जारी;
		ctx = get_nfs_खोलो_context(pos);
		अगर (ctx)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ctx;
पूर्ण

व्योम nfs_file_clear_खोलो_context(काष्ठा file *filp)
अणु
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(filp);

	अगर (ctx) अणु
		काष्ठा inode *inode = d_inode(ctx->dentry);

		/*
		 * We fatal error on ग_लिखो beक्रमe. Try to ग_लिखोback
		 * every page again.
		 */
		अगर (ctx->error < 0)
			invalidate_inode_pages2(inode->i_mapping);
		filp->निजी_data = शून्य;
		put_nfs_खोलो_context_sync(ctx);
	पूर्ण
पूर्ण

/*
 * These allocate and release file पढ़ो/ग_लिखो context inक्रमmation.
 */
पूर्णांक nfs_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा nfs_खोलो_context *ctx;

	ctx = alloc_nfs_खोलो_context(file_dentry(filp), filp->f_mode, filp);
	अगर (IS_ERR(ctx))
		वापस PTR_ERR(ctx);
	nfs_file_set_खोलो_context(filp, ctx);
	put_nfs_खोलो_context(ctx);
	nfs_fscache_खोलो_file(inode, filp);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_खोलो);

/*
 * This function is called whenever some part of NFS notices that
 * the cached attributes have to be refreshed.
 */
पूर्णांक
__nfs_revalidate_inode(काष्ठा nfs_server *server, काष्ठा inode *inode)
अणु
	पूर्णांक		 status = -ESTALE;
	काष्ठा nfs4_label *label = शून्य;
	काष्ठा nfs_fattr *fattr = शून्य;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);

	dfprपूर्णांकk(PAGECACHE, "NFS: revalidating (%s/%Lu)\n",
		inode->i_sb->s_id, (अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode));

	trace_nfs_revalidate_inode_enter(inode);

	अगर (is_bad_inode(inode))
		जाओ out;
	अगर (NFS_STALE(inode))
		जाओ out;

	/* pNFS: Attributes aren't updated until we layoutcommit */
	अगर (S_ISREG(inode->i_mode)) अणु
		status = pnfs_sync_inode(inode, false);
		अगर (status)
			जाओ out;
	पूर्ण

	status = -ENOMEM;
	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य)
		जाओ out;

	nfs_inc_stats(inode, NFSIOS_INODEREVALIDATE);

	label = nfs4_label_alloc(NFS_SERVER(inode), GFP_KERNEL);
	अगर (IS_ERR(label)) अणु
		status = PTR_ERR(label);
		जाओ out;
	पूर्ण

	status = NFS_PROTO(inode)->getattr(server, NFS_FH(inode), fattr,
			label, inode);
	अगर (status != 0) अणु
		dfprपूर्णांकk(PAGECACHE, "nfs_revalidate_inode: (%s/%Lu) getattr failed, error=%d\n",
			 inode->i_sb->s_id,
			 (अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode), status);
		चयन (status) अणु
		हाल -ETIMEDOUT:
			/* A soft समयout occurred. Use cached inक्रमmation? */
			अगर (server->flags & NFS_MOUNT_SOFTREVAL)
				status = 0;
			अवरोध;
		हाल -ESTALE:
			अगर (!S_ISसूची(inode->i_mode))
				nfs_set_inode_stale(inode);
			अन्यथा
				nfs_zap_caches(inode);
		पूर्ण
		जाओ err_out;
	पूर्ण

	status = nfs_refresh_inode(inode, fattr);
	अगर (status) अणु
		dfprपूर्णांकk(PAGECACHE, "nfs_revalidate_inode: (%s/%Lu) refresh failed, error=%d\n",
			 inode->i_sb->s_id,
			 (अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode), status);
		जाओ err_out;
	पूर्ण

	अगर (nfsi->cache_validity & NFS_INO_INVALID_ACL)
		nfs_zap_acl_cache(inode);

	nfs_setsecurity(inode, fattr, label);

	dfprपूर्णांकk(PAGECACHE, "NFS: (%s/%Lu) revalidation complete\n",
		inode->i_sb->s_id,
		(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode));

err_out:
	nfs4_label_मुक्त(label);
out:
	nfs_मुक्त_fattr(fattr);
	trace_nfs_revalidate_inode_निकास(inode, status);
	वापस status;
पूर्ण

पूर्णांक nfs_attribute_cache_expired(काष्ठा inode *inode)
अणु
	अगर (nfs_have_delegated_attributes(inode))
		वापस 0;
	वापस nfs_attribute_समयout(inode);
पूर्ण

/**
 * nfs_revalidate_inode - Revalidate the inode attributes
 * @inode: poपूर्णांकer to inode काष्ठा
 * @flags: cache flags to check
 *
 * Updates inode attribute inक्रमmation by retrieving the data from the server.
 */
पूर्णांक nfs_revalidate_inode(काष्ठा inode *inode, अचिन्हित दीर्घ flags)
अणु
	अगर (!nfs_check_cache_invalid(inode, flags))
		वापस NFS_STALE(inode) ? -ESTALE : 0;
	वापस __nfs_revalidate_inode(NFS_SERVER(inode), inode);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_revalidate_inode);

अटल पूर्णांक nfs_invalidate_mapping(काष्ठा inode *inode, काष्ठा address_space *mapping)
अणु
	पूर्णांक ret;

	अगर (mapping->nrpages != 0) अणु
		अगर (S_ISREG(inode->i_mode)) अणु
			ret = nfs_sync_mapping(mapping);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		ret = invalidate_inode_pages2(mapping);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	nfs_inc_stats(inode, NFSIOS_DATAINVALIDATE);
	nfs_fscache_रुको_on_invalidate(inode);

	dfprपूर्णांकk(PAGECACHE, "NFS: (%s/%Lu) data cache invalidated\n",
			inode->i_sb->s_id,
			(अचिन्हित दीर्घ दीर्घ)NFS_खाताID(inode));
	वापस 0;
पूर्ण

/**
 * nfs_clear_invalid_mapping - Conditionally clear a mapping
 * @mapping: poपूर्णांकer to mapping
 *
 * If the NFS_INO_INVALID_DATA inode flag is set, clear the mapping.
 */
पूर्णांक nfs_clear_invalid_mapping(काष्ठा address_space *mapping)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	अचिन्हित दीर्घ *bitlock = &nfsi->flags;
	पूर्णांक ret = 0;

	/*
	 * We must clear NFS_INO_INVALID_DATA first to ensure that
	 * invalidations that come in जबतक we're shooting करोwn the mappings
	 * are respected. But, that leaves a race winकरोw where one revalidator
	 * can clear the flag, and then another checks it beक्रमe the mapping
	 * माला_लो invalidated. Fix that by serializing access to this part of
	 * the function.
	 *
	 * At the same समय, we need to allow other tasks to see whether we
	 * might be in the middle of invalidating the pages, so we only set
	 * the bit lock here अगर it looks like we're going to be करोing that.
	 */
	क्रम (;;) अणु
		ret = रुको_on_bit_action(bitlock, NFS_INO_INVALIDATING,
					 nfs_रुको_bit_समाप्तable, TASK_KILLABLE);
		अगर (ret)
			जाओ out;
		spin_lock(&inode->i_lock);
		अगर (test_bit(NFS_INO_INVALIDATING, bitlock)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		अगर (nfsi->cache_validity & NFS_INO_INVALID_DATA)
			अवरोध;
		spin_unlock(&inode->i_lock);
		जाओ out;
	पूर्ण

	set_bit(NFS_INO_INVALIDATING, bitlock);
	smp_wmb();
	nfsi->cache_validity &=
		~(NFS_INO_INVALID_DATA | NFS_INO_DATA_INVAL_DEFER);
	spin_unlock(&inode->i_lock);
	trace_nfs_invalidate_mapping_enter(inode);
	ret = nfs_invalidate_mapping(inode, mapping);
	trace_nfs_invalidate_mapping_निकास(inode, ret);

	clear_bit_unlock(NFS_INO_INVALIDATING, bitlock);
	smp_mb__after_atomic();
	wake_up_bit(bitlock, NFS_INO_INVALIDATING);
out:
	वापस ret;
पूर्ण

bool nfs_mapping_need_revalidate_inode(काष्ठा inode *inode)
अणु
	वापस nfs_check_cache_invalid(inode, NFS_INO_INVALID_CHANGE) ||
		NFS_STALE(inode);
पूर्ण

पूर्णांक nfs_revalidate_mapping_rcu(काष्ठा inode *inode)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	अचिन्हित दीर्घ *bitlock = &nfsi->flags;
	पूर्णांक ret = 0;

	अगर (IS_SWAPखाता(inode))
		जाओ out;
	अगर (nfs_mapping_need_revalidate_inode(inode)) अणु
		ret = -ECHILD;
		जाओ out;
	पूर्ण
	spin_lock(&inode->i_lock);
	अगर (test_bit(NFS_INO_INVALIDATING, bitlock) ||
	    (nfsi->cache_validity & NFS_INO_INVALID_DATA))
		ret = -ECHILD;
	spin_unlock(&inode->i_lock);
out:
	वापस ret;
पूर्ण

/**
 * nfs_revalidate_mapping - Revalidate the pagecache
 * @inode: poपूर्णांकer to host inode
 * @mapping: poपूर्णांकer to mapping
 */
पूर्णांक nfs_revalidate_mapping(काष्ठा inode *inode, काष्ठा address_space *mapping)
अणु
	/* swapfiles are not supposed to be shared. */
	अगर (IS_SWAPखाता(inode))
		वापस 0;

	अगर (nfs_mapping_need_revalidate_inode(inode)) अणु
		पूर्णांक ret = __nfs_revalidate_inode(NFS_SERVER(inode), inode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस nfs_clear_invalid_mapping(mapping);
पूर्ण

अटल bool nfs_file_has_ग_लिखोrs(काष्ठा nfs_inode *nfsi)
अणु
	काष्ठा inode *inode = &nfsi->vfs_inode;

	अगर (!S_ISREG(inode->i_mode))
		वापस false;
	अगर (list_empty(&nfsi->खोलो_files))
		वापस false;
	वापस inode_is_खोलो_क्रम_ग_लिखो(inode);
पूर्ण

अटल bool nfs_file_has_buffered_ग_लिखोrs(काष्ठा nfs_inode *nfsi)
अणु
	वापस nfs_file_has_ग_लिखोrs(nfsi) && nfs_file_io_is_buffered(nfsi);
पूर्ण

अटल व्योम nfs_wcc_update_inode(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा बारpec64 ts;

	अगर ((fattr->valid & NFS_ATTR_FATTR_PRECHANGE)
			&& (fattr->valid & NFS_ATTR_FATTR_CHANGE)
			&& inode_eq_iversion_raw(inode, fattr->pre_change_attr)) अणु
		inode_set_iversion_raw(inode, fattr->change_attr);
		अगर (S_ISसूची(inode->i_mode))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA);
		अन्यथा अगर (nfs_server_capable(inode, NFS_CAP_XATTR))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_XATTR);
	पूर्ण
	/* If we have atomic WCC data, we may update some attributes */
	ts = inode->i_स_समय;
	अगर ((fattr->valid & NFS_ATTR_FATTR_PRECTIME)
			&& (fattr->valid & NFS_ATTR_FATTR_CTIME)
			&& बारpec64_equal(&ts, &fattr->pre_स_समय)) अणु
		inode->i_स_समय = fattr->स_समय;
	पूर्ण

	ts = inode->i_mसमय;
	अगर ((fattr->valid & NFS_ATTR_FATTR_PREMTIME)
			&& (fattr->valid & NFS_ATTR_FATTR_MTIME)
			&& बारpec64_equal(&ts, &fattr->pre_mसमय)) अणु
		inode->i_mसमय = fattr->mसमय;
		अगर (S_ISसूची(inode->i_mode))
			nfs_set_cache_invalid(inode, NFS_INO_INVALID_DATA);
	पूर्ण
	अगर ((fattr->valid & NFS_ATTR_FATTR_PRESIZE)
			&& (fattr->valid & NFS_ATTR_FATTR_SIZE)
			&& i_size_पढ़ो(inode) == nfs_माप_प्रकारo_loff_t(fattr->pre_size)
			&& !nfs_have_ग_लिखोbacks(inode)) अणु
		i_size_ग_लिखो(inode, nfs_माप_प्रकारo_loff_t(fattr->size));
	पूर्ण
पूर्ण

/**
 * nfs_check_inode_attributes - verअगरy consistency of the inode attribute cache
 * @inode: poपूर्णांकer to inode
 * @fattr: updated attributes
 *
 * Verअगरies the attribute cache. If we have just changed the attributes,
 * so that fattr carries weak cache consistency data, then it may
 * also update the स_समय/mसमय/change_attribute.
 */
अटल पूर्णांक nfs_check_inode_attributes(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	loff_t cur_size, new_isize;
	अचिन्हित दीर्घ invalid = 0;
	काष्ठा बारpec64 ts;

	अगर (NFS_PROTO(inode)->have_delegation(inode, FMODE_READ))
		वापस 0;

	अगर (!(fattr->valid & NFS_ATTR_FATTR_खाताID)) अणु
		/* Only a mounted-on-fileid? Just निकास */
		अगर (fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID)
			वापस 0;
	/* Has the inode gone and changed behind our back? */
	पूर्ण अन्यथा अगर (nfsi->fileid != fattr->fileid) अणु
		/* Is this perhaps the mounted-on fileid? */
		अगर ((fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID) &&
		    nfsi->fileid == fattr->mounted_on_fileid)
			वापस 0;
		वापस -ESTALE;
	पूर्ण
	अगर ((fattr->valid & NFS_ATTR_FATTR_TYPE) && inode_wrong_type(inode, fattr->mode))
		वापस -ESTALE;


	अगर (!nfs_file_has_buffered_ग_लिखोrs(nfsi)) अणु
		/* Verअगरy a few of the more important attributes */
		अगर ((fattr->valid & NFS_ATTR_FATTR_CHANGE) != 0 && !inode_eq_iversion_raw(inode, fattr->change_attr))
			invalid |= NFS_INO_INVALID_CHANGE;

		ts = inode->i_mसमय;
		अगर ((fattr->valid & NFS_ATTR_FATTR_MTIME) && !बारpec64_equal(&ts, &fattr->mसमय))
			invalid |= NFS_INO_INVALID_MTIME;

		ts = inode->i_स_समय;
		अगर ((fattr->valid & NFS_ATTR_FATTR_CTIME) && !बारpec64_equal(&ts, &fattr->स_समय))
			invalid |= NFS_INO_INVALID_CTIME;

		अगर (fattr->valid & NFS_ATTR_FATTR_SIZE) अणु
			cur_size = i_size_पढ़ो(inode);
			new_isize = nfs_माप_प्रकारo_loff_t(fattr->size);
			अगर (cur_size != new_isize)
				invalid |= NFS_INO_INVALID_SIZE;
		पूर्ण
	पूर्ण

	/* Have any file permissions changed? */
	अगर ((fattr->valid & NFS_ATTR_FATTR_MODE) && (inode->i_mode & S_IALLUGO) != (fattr->mode & S_IALLUGO))
		invalid |= NFS_INO_INVALID_MODE;
	अगर ((fattr->valid & NFS_ATTR_FATTR_OWNER) && !uid_eq(inode->i_uid, fattr->uid))
		invalid |= NFS_INO_INVALID_OTHER;
	अगर ((fattr->valid & NFS_ATTR_FATTR_GROUP) && !gid_eq(inode->i_gid, fattr->gid))
		invalid |= NFS_INO_INVALID_OTHER;

	/* Has the link count changed? */
	अगर ((fattr->valid & NFS_ATTR_FATTR_NLINK) && inode->i_nlink != fattr->nlink)
		invalid |= NFS_INO_INVALID_NLINK;

	ts = inode->i_aसमय;
	अगर ((fattr->valid & NFS_ATTR_FATTR_ATIME) && !बारpec64_equal(&ts, &fattr->aसमय))
		invalid |= NFS_INO_INVALID_ATIME;

	अगर (invalid != 0)
		nfs_set_cache_invalid(inode, invalid);

	nfsi->पढ़ो_cache_jअगरfies = fattr->समय_start;
	वापस 0;
पूर्ण

अटल atomic_दीर्घ_t nfs_attr_generation_counter;

अटल अचिन्हित दीर्घ nfs_पढ़ो_attr_generation_counter(व्योम)
अणु
	वापस atomic_दीर्घ_पढ़ो(&nfs_attr_generation_counter);
पूर्ण

अचिन्हित दीर्घ nfs_inc_attr_generation_counter(व्योम)
अणु
	वापस atomic_दीर्घ_inc_वापस(&nfs_attr_generation_counter);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_inc_attr_generation_counter);

व्योम nfs_fattr_init(काष्ठा nfs_fattr *fattr)
अणु
	fattr->valid = 0;
	fattr->समय_start = jअगरfies;
	fattr->gencount = nfs_inc_attr_generation_counter();
	fattr->owner_name = शून्य;
	fattr->group_name = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_fattr_init);

/**
 * nfs_fattr_set_barrier
 * @fattr: attributes
 *
 * Used to set a barrier after an attribute was updated. This
 * barrier ensures that older attributes from RPC calls that may
 * have raced with our update cannot clobber these new values.
 * Note that you are still responsible क्रम ensuring that other
 * operations which change the attribute on the server करो not
 * collide.
 */
व्योम nfs_fattr_set_barrier(काष्ठा nfs_fattr *fattr)
अणु
	fattr->gencount = nfs_inc_attr_generation_counter();
पूर्ण

काष्ठा nfs_fattr *nfs_alloc_fattr(व्योम)
अणु
	काष्ठा nfs_fattr *fattr;

	fattr = kदो_स्मृति(माप(*fattr), GFP_NOFS);
	अगर (fattr != शून्य)
		nfs_fattr_init(fattr);
	वापस fattr;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_alloc_fattr);

काष्ठा nfs_fh *nfs_alloc_fhandle(व्योम)
अणु
	काष्ठा nfs_fh *fh;

	fh = kदो_स्मृति(माप(काष्ठा nfs_fh), GFP_NOFS);
	अगर (fh != शून्य)
		fh->size = 0;
	वापस fh;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_alloc_fhandle);

#अगर_घोषित NFS_DEBUG
/*
 * _nfs_display_fhandle_hash - calculate the crc32 hash क्रम the filehandle
 *                             in the same way that wireshark करोes
 *
 * @fh: file handle
 *
 * For debugging only.
 */
u32 _nfs_display_fhandle_hash(स्थिर काष्ठा nfs_fh *fh)
अणु
	/* wireshark uses 32-bit AUTODIN crc and करोes a bitwise
	 * not on the result */
	वापस nfs_fhandle_hash(fh);
पूर्ण
EXPORT_SYMBOL_GPL(_nfs_display_fhandle_hash);

/*
 * _nfs_display_fhandle - display an NFS file handle on the console
 *
 * @fh: file handle to display
 * @caption: display caption
 *
 * For debugging only.
 */
व्योम _nfs_display_fhandle(स्थिर काष्ठा nfs_fh *fh, स्थिर अक्षर *caption)
अणु
	अचिन्हित लघु i;

	अगर (fh == शून्य || fh->size == 0) अणु
		prपूर्णांकk(KERN_DEFAULT "%s at %p is empty\n", caption, fh);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_DEFAULT "%s at %p is %u bytes, crc: 0x%08x:\n",
	       caption, fh, fh->size, _nfs_display_fhandle_hash(fh));
	क्रम (i = 0; i < fh->size; i += 16) अणु
		__be32 *pos = (__be32 *)&fh->data[i];

		चयन ((fh->size - i - 1) >> 2) अणु
		हाल 0:
			prपूर्णांकk(KERN_DEFAULT " %08x\n",
				be32_to_cpup(pos));
			अवरोध;
		हाल 1:
			prपूर्णांकk(KERN_DEFAULT " %08x %08x\n",
				be32_to_cpup(pos), be32_to_cpup(pos + 1));
			अवरोध;
		हाल 2:
			prपूर्णांकk(KERN_DEFAULT " %08x %08x %08x\n",
				be32_to_cpup(pos), be32_to_cpup(pos + 1),
				be32_to_cpup(pos + 2));
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_DEFAULT " %08x %08x %08x %08x\n",
				be32_to_cpup(pos), be32_to_cpup(pos + 1),
				be32_to_cpup(pos + 2), be32_to_cpup(pos + 3));
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(_nfs_display_fhandle);
#पूर्ण_अगर

/**
 * nfs_inode_attrs_cmp_generic - compare attributes
 * @fattr: attributes
 * @inode: poपूर्णांकer to inode
 *
 * Attempt to भागine whether or not an RPC call reply carrying stale
 * attributes got scheduled after another call carrying updated ones.
 * Note also the check क्रम wraparound of 'attr_gencount'
 *
 * The function वापसs '1' अगर it thinks the attributes in @fattr are
 * more recent than the ones cached in @inode. Otherwise it वापसs
 * the value '0'.
 */
अटल पूर्णांक nfs_inode_attrs_cmp_generic(स्थिर काष्ठा nfs_fattr *fattr,
				       स्थिर काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ attr_gencount = NFS_I(inode)->attr_gencount;

	वापस (दीर्घ)(fattr->gencount - attr_gencount) > 0 ||
	       (दीर्घ)(attr_gencount - nfs_पढ़ो_attr_generation_counter()) > 0;
पूर्ण

/**
 * nfs_inode_attrs_cmp_monotonic - compare attributes
 * @fattr: attributes
 * @inode: poपूर्णांकer to inode
 *
 * Attempt to भागine whether or not an RPC call reply carrying stale
 * attributes got scheduled after another call carrying updated ones.
 *
 * We assume that the server observes monotonic semantics क्रम
 * the change attribute, so a larger value means that the attributes in
 * @fattr are more recent, in which हाल the function वापसs the
 * value '1'.
 * A वापस value of '0' indicates no measurable change
 * A वापस value of '-1' means that the attributes in @inode are
 * more recent.
 */
अटल पूर्णांक nfs_inode_attrs_cmp_monotonic(स्थिर काष्ठा nfs_fattr *fattr,
					 स्थिर काष्ठा inode *inode)
अणु
	s64 dअगरf = fattr->change_attr - inode_peek_iversion_raw(inode);
	अगर (dअगरf > 0)
		वापस 1;
	वापस dअगरf == 0 ? 0 : -1;
पूर्ण

/**
 * nfs_inode_attrs_cmp_strict_monotonic - compare attributes
 * @fattr: attributes
 * @inode: poपूर्णांकer to inode
 *
 * Attempt to भागine whether or not an RPC call reply carrying stale
 * attributes got scheduled after another call carrying updated ones.
 *
 * We assume that the server observes strictly monotonic semantics क्रम
 * the change attribute, so a larger value means that the attributes in
 * @fattr are more recent, in which हाल the function वापसs the
 * value '1'.
 * A वापस value of '-1' means that the attributes in @inode are
 * more recent or unchanged.
 */
अटल पूर्णांक nfs_inode_attrs_cmp_strict_monotonic(स्थिर काष्ठा nfs_fattr *fattr,
						स्थिर काष्ठा inode *inode)
अणु
	वापस  nfs_inode_attrs_cmp_monotonic(fattr, inode) > 0 ? 1 : -1;
पूर्ण

/**
 * nfs_inode_attrs_cmp - compare attributes
 * @fattr: attributes
 * @inode: poपूर्णांकer to inode
 *
 * This function वापसs '1' अगर it thinks the attributes in @fattr are
 * more recent than the ones cached in @inode. It वापसs '-1' अगर
 * the attributes in @inode are more recent than the ones in @fattr,
 * and it वापसs 0 अगर not sure.
 */
अटल पूर्णांक nfs_inode_attrs_cmp(स्थिर काष्ठा nfs_fattr *fattr,
			       स्थिर काष्ठा inode *inode)
अणु
	अगर (nfs_inode_attrs_cmp_generic(fattr, inode) > 0)
		वापस 1;
	चयन (NFS_SERVER(inode)->change_attr_type) अणु
	हाल NFS4_CHANGE_TYPE_IS_UNDEFINED:
		अवरोध;
	हाल NFS4_CHANGE_TYPE_IS_TIME_METADATA:
		अगर (!(fattr->valid & NFS_ATTR_FATTR_CHANGE))
			अवरोध;
		वापस nfs_inode_attrs_cmp_monotonic(fattr, inode);
	शेष:
		अगर (!(fattr->valid & NFS_ATTR_FATTR_CHANGE))
			अवरोध;
		वापस nfs_inode_attrs_cmp_strict_monotonic(fattr, inode);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nfs_inode_finish_partial_attr_update - complete a previous inode update
 * @fattr: attributes
 * @inode: poपूर्णांकer to inode
 *
 * Returns '1' अगर the last attribute update left the inode cached
 * attributes in a partially unrevalidated state, and @fattr
 * matches the change attribute of that partial update.
 * Otherwise वापसs '0'.
 */
अटल पूर्णांक nfs_inode_finish_partial_attr_update(स्थिर काष्ठा nfs_fattr *fattr,
						स्थिर काष्ठा inode *inode)
अणु
	स्थिर अचिन्हित दीर्घ check_valid =
		NFS_INO_INVALID_ATIME | NFS_INO_INVALID_CTIME |
		NFS_INO_INVALID_MTIME | NFS_INO_INVALID_SIZE |
		NFS_INO_INVALID_BLOCKS | NFS_INO_INVALID_OTHER |
		NFS_INO_INVALID_NLINK;
	अचिन्हित दीर्घ cache_validity = NFS_I(inode)->cache_validity;

	अगर (!(cache_validity & NFS_INO_INVALID_CHANGE) &&
	    (cache_validity & check_valid) != 0 &&
	    (fattr->valid & NFS_ATTR_FATTR_CHANGE) != 0 &&
	    nfs_inode_attrs_cmp_monotonic(fattr, inode) == 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_refresh_inode_locked(काष्ठा inode *inode,
				    काष्ठा nfs_fattr *fattr)
अणु
	पूर्णांक attr_cmp = nfs_inode_attrs_cmp(fattr, inode);
	पूर्णांक ret = 0;

	trace_nfs_refresh_inode_enter(inode);

	अगर (attr_cmp > 0 || nfs_inode_finish_partial_attr_update(fattr, inode))
		ret = nfs_update_inode(inode, fattr);
	अन्यथा अगर (attr_cmp == 0)
		ret = nfs_check_inode_attributes(inode, fattr);

	trace_nfs_refresh_inode_निकास(inode, ret);
	वापस ret;
पूर्ण

/**
 * nfs_refresh_inode - try to update the inode attribute cache
 * @inode: poपूर्णांकer to inode
 * @fattr: updated attributes
 *
 * Check that an RPC call that वापसed attributes has not overlapped with
 * other recent updates of the inode metadata, then decide whether it is
 * safe to करो a full update of the inode attributes, or whether just to
 * call nfs_check_inode_attributes.
 */
पूर्णांक nfs_refresh_inode(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	पूर्णांक status;

	अगर ((fattr->valid & NFS_ATTR_FATTR) == 0)
		वापस 0;
	spin_lock(&inode->i_lock);
	status = nfs_refresh_inode_locked(inode, fattr);
	spin_unlock(&inode->i_lock);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_refresh_inode);

अटल पूर्णांक nfs_post_op_update_inode_locked(काष्ठा inode *inode,
		काष्ठा nfs_fattr *fattr, अचिन्हित पूर्णांक invalid)
अणु
	अगर (S_ISसूची(inode->i_mode))
		invalid |= NFS_INO_INVALID_DATA;
	nfs_set_cache_invalid(inode, invalid);
	अगर ((fattr->valid & NFS_ATTR_FATTR) == 0)
		वापस 0;
	वापस nfs_refresh_inode_locked(inode, fattr);
पूर्ण

/**
 * nfs_post_op_update_inode - try to update the inode attribute cache
 * @inode: poपूर्णांकer to inode
 * @fattr: updated attributes
 *
 * After an operation that has changed the inode metadata, mark the
 * attribute cache as being invalid, then try to update it.
 *
 * NB: अगर the server didn't वापस any post op attributes, this
 * function will क्रमce the retrieval of attributes beक्रमe the next
 * NFS request.  Thus it should be used only क्रम operations that
 * are expected to change one or more attributes, to aव्योम
 * unnecessary NFS requests and trips through nfs_update_inode().
 */
पूर्णांक nfs_post_op_update_inode(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	पूर्णांक status;

	spin_lock(&inode->i_lock);
	nfs_fattr_set_barrier(fattr);
	status = nfs_post_op_update_inode_locked(inode, fattr,
			NFS_INO_INVALID_CHANGE
			| NFS_INO_INVALID_CTIME
			| NFS_INO_REVAL_FORCED);
	spin_unlock(&inode->i_lock);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_post_op_update_inode);

/**
 * nfs_post_op_update_inode_क्रमce_wcc_locked - update the inode attribute cache
 * @inode: poपूर्णांकer to inode
 * @fattr: updated attributes
 *
 * After an operation that has changed the inode metadata, mark the
 * attribute cache as being invalid, then try to update it. Fake up
 * weak cache consistency data, अगर none exist.
 *
 * This function is मुख्यly deचिन्हित to be used by the ->ग_लिखो_करोne() functions.
 */
पूर्णांक nfs_post_op_update_inode_क्रमce_wcc_locked(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	पूर्णांक attr_cmp = nfs_inode_attrs_cmp(fattr, inode);
	पूर्णांक status;

	/* Don't करो a WCC update अगर these attributes are alपढ़ोy stale */
	अगर (attr_cmp < 0)
		वापस 0;
	अगर ((fattr->valid & NFS_ATTR_FATTR) == 0 || !attr_cmp) अणु
		fattr->valid &= ~(NFS_ATTR_FATTR_PRECHANGE
				| NFS_ATTR_FATTR_PRESIZE
				| NFS_ATTR_FATTR_PREMTIME
				| NFS_ATTR_FATTR_PRECTIME);
		जाओ out_noक्रमce;
	पूर्ण
	अगर ((fattr->valid & NFS_ATTR_FATTR_CHANGE) != 0 &&
			(fattr->valid & NFS_ATTR_FATTR_PRECHANGE) == 0) अणु
		fattr->pre_change_attr = inode_peek_iversion_raw(inode);
		fattr->valid |= NFS_ATTR_FATTR_PRECHANGE;
	पूर्ण
	अगर ((fattr->valid & NFS_ATTR_FATTR_CTIME) != 0 &&
			(fattr->valid & NFS_ATTR_FATTR_PRECTIME) == 0) अणु
		fattr->pre_स_समय = inode->i_स_समय;
		fattr->valid |= NFS_ATTR_FATTR_PRECTIME;
	पूर्ण
	अगर ((fattr->valid & NFS_ATTR_FATTR_MTIME) != 0 &&
			(fattr->valid & NFS_ATTR_FATTR_PREMTIME) == 0) अणु
		fattr->pre_mसमय = inode->i_mसमय;
		fattr->valid |= NFS_ATTR_FATTR_PREMTIME;
	पूर्ण
	अगर ((fattr->valid & NFS_ATTR_FATTR_SIZE) != 0 &&
			(fattr->valid & NFS_ATTR_FATTR_PRESIZE) == 0) अणु
		fattr->pre_size = i_size_पढ़ो(inode);
		fattr->valid |= NFS_ATTR_FATTR_PRESIZE;
	पूर्ण
out_noक्रमce:
	status = nfs_post_op_update_inode_locked(inode, fattr,
			NFS_INO_INVALID_CHANGE
			| NFS_INO_INVALID_CTIME
			| NFS_INO_INVALID_MTIME
			| NFS_INO_INVALID_BLOCKS);
	वापस status;
पूर्ण

/**
 * nfs_post_op_update_inode_क्रमce_wcc - try to update the inode attribute cache
 * @inode: poपूर्णांकer to inode
 * @fattr: updated attributes
 *
 * After an operation that has changed the inode metadata, mark the
 * attribute cache as being invalid, then try to update it. Fake up
 * weak cache consistency data, अगर none exist.
 *
 * This function is मुख्यly deचिन्हित to be used by the ->ग_लिखो_करोne() functions.
 */
पूर्णांक nfs_post_op_update_inode_क्रमce_wcc(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	पूर्णांक status;

	spin_lock(&inode->i_lock);
	nfs_fattr_set_barrier(fattr);
	status = nfs_post_op_update_inode_क्रमce_wcc_locked(inode, fattr);
	spin_unlock(&inode->i_lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_post_op_update_inode_क्रमce_wcc);


/*
 * Many nfs protocol calls वापस the new file attributes after
 * an operation.  Here we update the inode to reflect the state
 * of the server's inode.
 *
 * This is a bit tricky because we have to make sure all dirty pages
 * have been sent off to the server beक्रमe calling invalidate_inode_pages.
 * To make sure no other process adds more ग_लिखो requests जबतक we try
 * our best to flush them, we make them sleep during the attribute refresh.
 *
 * A very similar scenario holds क्रम the dir cache.
 */
अटल पूर्णांक nfs_update_inode(काष्ठा inode *inode, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs_inode *nfsi = NFS_I(inode);
	loff_t cur_isize, new_isize;
	u64 fattr_supported = server->fattr_valid;
	अचिन्हित दीर्घ invalid = 0;
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ save_cache_validity;
	bool have_ग_लिखोrs = nfs_file_has_buffered_ग_लिखोrs(nfsi);
	bool cache_revalidated = true;
	bool attr_changed = false;
	bool have_delegation;

	dfprपूर्णांकk(VFS, "NFS: %s(%s/%lu fh_crc=0x%08x ct=%d info=0x%x)\n",
			__func__, inode->i_sb->s_id, inode->i_ino,
			nfs_display_fhandle_hash(NFS_FH(inode)),
			atomic_पढ़ो(&inode->i_count), fattr->valid);

	अगर (!(fattr->valid & NFS_ATTR_FATTR_खाताID)) अणु
		/* Only a mounted-on-fileid? Just निकास */
		अगर (fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID)
			वापस 0;
	/* Has the inode gone and changed behind our back? */
	पूर्ण अन्यथा अगर (nfsi->fileid != fattr->fileid) अणु
		/* Is this perhaps the mounted-on fileid? */
		अगर ((fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_खाताID) &&
		    nfsi->fileid == fattr->mounted_on_fileid)
			वापस 0;
		prपूर्णांकk(KERN_ERR "NFS: server %s error: fileid changed\n"
			"fsid %s: expected fileid 0x%Lx, got 0x%Lx\n",
			NFS_SERVER(inode)->nfs_client->cl_hostname,
			inode->i_sb->s_id, (दीर्घ दीर्घ)nfsi->fileid,
			(दीर्घ दीर्घ)fattr->fileid);
		जाओ out_err;
	पूर्ण

	/*
	 * Make sure the inode's type hasn't changed.
	 */
	अगर ((fattr->valid & NFS_ATTR_FATTR_TYPE) && inode_wrong_type(inode, fattr->mode)) अणु
		/*
		* Big trouble! The inode has become a dअगरferent object.
		*/
		prपूर्णांकk(KERN_DEBUG "NFS: %s: inode %lu mode changed, %07o to %07o\n",
				__func__, inode->i_ino, inode->i_mode, fattr->mode);
		जाओ out_err;
	पूर्ण

	/* Update the fsid? */
	अगर (S_ISसूची(inode->i_mode) && (fattr->valid & NFS_ATTR_FATTR_FSID) &&
			!nfs_fsid_equal(&server->fsid, &fattr->fsid) &&
			!IS_AUTOMOUNT(inode))
		server->fsid = fattr->fsid;

	/* Save the delegation state beक्रमe clearing cache_validity */
	have_delegation = nfs_have_delegated_attributes(inode);

	/*
	 * Update the पढ़ो समय so we करोn't revalidate too often.
	 */
	nfsi->पढ़ो_cache_jअगरfies = fattr->समय_start;

	save_cache_validity = nfsi->cache_validity;
	nfsi->cache_validity &= ~(NFS_INO_INVALID_ATTR
			| NFS_INO_INVALID_ATIME
			| NFS_INO_REVAL_FORCED
			| NFS_INO_INVALID_BLOCKS);

	/* Do atomic weak cache consistency updates */
	nfs_wcc_update_inode(inode, fattr);

	अगर (pnfs_layoutcommit_outstanding(inode)) अणु
		nfsi->cache_validity |=
			save_cache_validity &
			(NFS_INO_INVALID_CHANGE | NFS_INO_INVALID_CTIME |
			 NFS_INO_INVALID_MTIME | NFS_INO_INVALID_SIZE |
			 NFS_INO_INVALID_BLOCKS);
		cache_revalidated = false;
	पूर्ण

	/* More cache consistency checks */
	अगर (fattr->valid & NFS_ATTR_FATTR_CHANGE) अणु
		अगर (!inode_eq_iversion_raw(inode, fattr->change_attr)) अणु
			/* Could it be a race with ग_लिखोback? */
			अगर (!(have_ग_लिखोrs || have_delegation)) अणु
				invalid |= NFS_INO_INVALID_DATA
					| NFS_INO_INVALID_ACCESS
					| NFS_INO_INVALID_ACL
					| NFS_INO_INVALID_XATTR;
				/* Force revalidate of all attributes */
				save_cache_validity |= NFS_INO_INVALID_CTIME
					| NFS_INO_INVALID_MTIME
					| NFS_INO_INVALID_SIZE
					| NFS_INO_INVALID_BLOCKS
					| NFS_INO_INVALID_NLINK
					| NFS_INO_INVALID_MODE
					| NFS_INO_INVALID_OTHER;
				अगर (S_ISसूची(inode->i_mode))
					nfs_क्रमce_lookup_revalidate(inode);
				dprपूर्णांकk("NFS: change_attr change on server for file %s/%ld\n",
						inode->i_sb->s_id,
						inode->i_ino);
			पूर्ण अन्यथा अगर (!have_delegation)
				nfsi->cache_validity |= NFS_INO_DATA_INVAL_DEFER;
			inode_set_iversion_raw(inode, fattr->change_attr);
			attr_changed = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_CHANGE;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_MTIME) अणु
		inode->i_mसमय = fattr->mसमय;
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_MTIME) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_MTIME;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_CTIME) अणु
		inode->i_स_समय = fattr->स_समय;
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_CTIME) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_CTIME;
		cache_revalidated = false;
	पूर्ण

	/* Check अगर our cached file size is stale */
	अगर (fattr->valid & NFS_ATTR_FATTR_SIZE) अणु
		new_isize = nfs_माप_प्रकारo_loff_t(fattr->size);
		cur_isize = i_size_पढ़ो(inode);
		अगर (new_isize != cur_isize && !have_delegation) अणु
			/* Do we perhaps have any outstanding ग_लिखोs, or has
			 * the file grown beyond our last ग_लिखो? */
			अगर (!nfs_have_ग_लिखोbacks(inode) || new_isize > cur_isize) अणु
				i_size_ग_लिखो(inode, new_isize);
				अगर (!have_ग_लिखोrs)
					invalid |= NFS_INO_INVALID_DATA;
				attr_changed = true;
			पूर्ण
			dprपूर्णांकk("NFS: isize change on server for file %s/%ld "
					"(%Ld to %Ld)\n",
					inode->i_sb->s_id,
					inode->i_ino,
					(दीर्घ दीर्घ)cur_isize,
					(दीर्घ दीर्घ)new_isize);
		पूर्ण
		अगर (new_isize == 0 &&
		    !(fattr->valid & (NFS_ATTR_FATTR_SPACE_USED |
				      NFS_ATTR_FATTR_BLOCKS_USED))) अणु
			fattr->du.nfs3.used = 0;
			fattr->valid |= NFS_ATTR_FATTR_SPACE_USED;
		पूर्ण
	पूर्ण अन्यथा अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_SIZE;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_ATIME)
		inode->i_aसमय = fattr->aसमय;
	अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_ATIME) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_ATIME;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_MODE) अणु
		अगर ((inode->i_mode & S_IALLUGO) != (fattr->mode & S_IALLUGO)) अणु
			umode_t newmode = inode->i_mode & S_IFMT;
			newmode |= fattr->mode & S_IALLUGO;
			inode->i_mode = newmode;
			invalid |= NFS_INO_INVALID_ACCESS
				| NFS_INO_INVALID_ACL;
			attr_changed = true;
		पूर्ण
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_MODE) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_MODE;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_OWNER) अणु
		अगर (!uid_eq(inode->i_uid, fattr->uid)) अणु
			invalid |= NFS_INO_INVALID_ACCESS
				| NFS_INO_INVALID_ACL;
			inode->i_uid = fattr->uid;
			attr_changed = true;
		पूर्ण
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_OWNER) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_OTHER;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_GROUP) अणु
		अगर (!gid_eq(inode->i_gid, fattr->gid)) अणु
			invalid |= NFS_INO_INVALID_ACCESS
				| NFS_INO_INVALID_ACL;
			inode->i_gid = fattr->gid;
			attr_changed = true;
		पूर्ण
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_GROUP) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_OTHER;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_NLINK) अणु
		अगर (inode->i_nlink != fattr->nlink) अणु
			अगर (S_ISसूची(inode->i_mode))
				invalid |= NFS_INO_INVALID_DATA;
			set_nlink(inode, fattr->nlink);
			attr_changed = true;
		पूर्ण
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_NLINK) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_NLINK;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_SPACE_USED) अणु
		/*
		 * report the blocks in 512byte units
		 */
		inode->i_blocks = nfs_calc_block_size(fattr->du.nfs3.used);
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_SPACE_USED) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_BLOCKS;
		cache_revalidated = false;
	पूर्ण

	अगर (fattr->valid & NFS_ATTR_FATTR_BLOCKS_USED) अणु
		inode->i_blocks = fattr->du.nfs2.blocks;
	पूर्ण अन्यथा अगर (fattr_supported & NFS_ATTR_FATTR_BLOCKS_USED) अणु
		nfsi->cache_validity |=
			save_cache_validity & NFS_INO_INVALID_BLOCKS;
		cache_revalidated = false;
	पूर्ण

	/* Update attrसमयo value अगर we're out of the unstable period */
	अगर (attr_changed) अणु
		nfs_inc_stats(inode, NFSIOS_ATTRINVALIDATE);
		nfsi->attrसमयo = NFS_MINATTRTIMEO(inode);
		nfsi->attrसमयo_बारtamp = now;
		/* Set barrier to be more recent than all outstanding updates */
		nfsi->attr_gencount = nfs_inc_attr_generation_counter();
	पूर्ण अन्यथा अणु
		अगर (cache_revalidated) अणु
			अगर (!समय_in_range_खोलो(now, nfsi->attrसमयo_बारtamp,
				nfsi->attrसमयo_बारtamp + nfsi->attrसमयo)) अणु
				nfsi->attrसमयo <<= 1;
				अगर (nfsi->attrसमयo > NFS_MAXATTRTIMEO(inode))
					nfsi->attrसमयo = NFS_MAXATTRTIMEO(inode);
			पूर्ण
			nfsi->attrसमयo_बारtamp = now;
		पूर्ण
		/* Set the barrier to be more recent than this fattr */
		अगर ((दीर्घ)(fattr->gencount - nfsi->attr_gencount) > 0)
			nfsi->attr_gencount = fattr->gencount;
	पूर्ण

	/* Don't invalidate the data अगर we were to blame */
	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode)
				|| S_ISLNK(inode->i_mode)))
		invalid &= ~NFS_INO_INVALID_DATA;
	nfs_set_cache_invalid(inode, invalid);

	वापस 0;
 out_err:
	/*
	 * No need to worry about unhashing the dentry, as the
	 * lookup validation will know that the inode is bad.
	 * (But we fall through to invalidate the caches.)
	 */
	nfs_set_inode_stale_locked(inode);
	वापस -ESTALE;
पूर्ण

काष्ठा inode *nfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा nfs_inode *nfsi;
	nfsi = kmem_cache_alloc(nfs_inode_cachep, GFP_KERNEL);
	अगर (!nfsi)
		वापस शून्य;
	nfsi->flags = 0UL;
	nfsi->cache_validity = 0UL;
#अगर IS_ENABLED(CONFIG_NFS_V4)
	nfsi->nfs4_acl = शून्य;
#पूर्ण_अगर /* CONFIG_NFS_V4 */
#अगर_घोषित CONFIG_NFS_V4_2
	nfsi->xattr_cache = शून्य;
#पूर्ण_अगर
	वापस &nfsi->vfs_inode;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_alloc_inode);

व्योम nfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(nfs_inode_cachep, NFS_I(inode));
पूर्ण
EXPORT_SYMBOL_GPL(nfs_मुक्त_inode);

अटल अंतरभूत व्योम nfs4_init_once(काष्ठा nfs_inode *nfsi)
अणु
#अगर IS_ENABLED(CONFIG_NFS_V4)
	INIT_LIST_HEAD(&nfsi->खोलो_states);
	nfsi->delegation = शून्य;
	init_rwsem(&nfsi->rwsem);
	nfsi->layout = शून्य;
#पूर्ण_अगर
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा nfs_inode *nfsi = (काष्ठा nfs_inode *) foo;

	inode_init_once(&nfsi->vfs_inode);
	INIT_LIST_HEAD(&nfsi->खोलो_files);
	INIT_LIST_HEAD(&nfsi->access_cache_entry_lru);
	INIT_LIST_HEAD(&nfsi->access_cache_inode_lru);
	INIT_LIST_HEAD(&nfsi->commit_info.list);
	atomic_दीर्घ_set(&nfsi->nrequests, 0);
	atomic_दीर्घ_set(&nfsi->commit_info.ncommit, 0);
	atomic_set(&nfsi->commit_info.rpcs_out, 0);
	init_rwsem(&nfsi->सूची_हटाओ_sem);
	mutex_init(&nfsi->commit_mutex);
	nfs4_init_once(nfsi);
	nfsi->cache_change_attribute = 0;
पूर्ण

अटल पूर्णांक __init nfs_init_inodecache(व्योम)
अणु
	nfs_inode_cachep = kmem_cache_create("nfs_inode_cache",
					     माप(काष्ठा nfs_inode),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (nfs_inode_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम nfs_destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(nfs_inode_cachep);
पूर्ण

काष्ठा workqueue_काष्ठा *nfsiod_workqueue;
EXPORT_SYMBOL_GPL(nfsiod_workqueue);

/*
 * start up the nfsiod workqueue
 */
अटल पूर्णांक nfsiod_start(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;
	dprपूर्णांकk("RPC:       creating workqueue nfsiod\n");
	wq = alloc_workqueue("nfsiod", WQ_MEM_RECLAIM | WQ_UNBOUND, 0);
	अगर (wq == शून्य)
		वापस -ENOMEM;
	nfsiod_workqueue = wq;
	वापस 0;
पूर्ण

/*
 * Destroy the nfsiod workqueue
 */
अटल व्योम nfsiod_stop(व्योम)
अणु
	काष्ठा workqueue_काष्ठा *wq;

	wq = nfsiod_workqueue;
	अगर (wq == शून्य)
		वापस;
	nfsiod_workqueue = शून्य;
	destroy_workqueue(wq);
पूर्ण

अचिन्हित पूर्णांक nfs_net_id;
EXPORT_SYMBOL_GPL(nfs_net_id);

अटल पूर्णांक nfs_net_init(काष्ठा net *net)
अणु
	nfs_clients_init(net);
	वापस nfs_fs_proc_net_init(net);
पूर्ण

अटल व्योम nfs_net_निकास(काष्ठा net *net)
अणु
	nfs_fs_proc_net_निकास(net);
	nfs_clients_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations nfs_net_ops = अणु
	.init = nfs_net_init,
	.निकास = nfs_net_निकास,
	.id   = &nfs_net_id,
	.size = माप(काष्ठा nfs_net),
पूर्ण;

/*
 * Initialize NFS
 */
अटल पूर्णांक __init init_nfs_fs(व्योम)
अणु
	पूर्णांक err;

	err = nfs_sysfs_init();
	अगर (err < 0)
		जाओ out10;

	err = रेजिस्टर_pernet_subsys(&nfs_net_ops);
	अगर (err < 0)
		जाओ out9;

	err = nfs_fscache_रेजिस्टर();
	अगर (err < 0)
		जाओ out8;

	err = nfsiod_start();
	अगर (err)
		जाओ out7;

	err = nfs_fs_proc_init();
	अगर (err)
		जाओ out6;

	err = nfs_init_nfspagecache();
	अगर (err)
		जाओ out5;

	err = nfs_init_inodecache();
	अगर (err)
		जाओ out4;

	err = nfs_init_पढ़ोpagecache();
	अगर (err)
		जाओ out3;

	err = nfs_init_ग_लिखोpagecache();
	अगर (err)
		जाओ out2;

	err = nfs_init_directcache();
	अगर (err)
		जाओ out1;

	rpc_proc_रेजिस्टर(&init_net, &nfs_rpcstat);

	err = रेजिस्टर_nfs_fs();
	अगर (err)
		जाओ out0;

	वापस 0;
out0:
	rpc_proc_unरेजिस्टर(&init_net, "nfs");
	nfs_destroy_directcache();
out1:
	nfs_destroy_ग_लिखोpagecache();
out2:
	nfs_destroy_पढ़ोpagecache();
out3:
	nfs_destroy_inodecache();
out4:
	nfs_destroy_nfspagecache();
out5:
	nfs_fs_proc_निकास();
out6:
	nfsiod_stop();
out7:
	nfs_fscache_unरेजिस्टर();
out8:
	unरेजिस्टर_pernet_subsys(&nfs_net_ops);
out9:
	nfs_sysfs_निकास();
out10:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_nfs_fs(व्योम)
अणु
	nfs_destroy_directcache();
	nfs_destroy_ग_लिखोpagecache();
	nfs_destroy_पढ़ोpagecache();
	nfs_destroy_inodecache();
	nfs_destroy_nfspagecache();
	nfs_fscache_unरेजिस्टर();
	unरेजिस्टर_pernet_subsys(&nfs_net_ops);
	rpc_proc_unरेजिस्टर(&init_net, "nfs");
	unरेजिस्टर_nfs_fs();
	nfs_fs_proc_निकास();
	nfsiod_stop();
	nfs_sysfs_निकास();
पूर्ण

/* Not quite true; I just मुख्यtain it */
MODULE_AUTHOR("Olaf Kirch <okir@monad.swb.de>");
MODULE_LICENSE("GPL");
module_param(enable_ino64, bool, 0644);

module_init(init_nfs_fs)
module_निकास(निकास_nfs_fs)
