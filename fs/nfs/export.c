<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, Primary Data, Inc. All rights reserved.
 *
 * Tao Peng <bergwolf@primarydata.com>
 */
#समावेश <linux/dcache.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs_fs.h>

#समावेश "internal.h"
#समावेश "nfstrace.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

क्रमागत अणु
	खाताID_HIGH_OFF = 0,	/* inode fileid high */
	खाताID_LOW_OFF,		/* inode fileid low */
	खाता_I_TYPE_OFF,	/* inode type */
	EMBED_FH_OFF		/* embeded server fh */
पूर्ण;


अटल काष्ठा nfs_fh *nfs_exp_embedfh(__u32 *p)
अणु
	वापस (काष्ठा nfs_fh *)(p + EMBED_FH_OFF);
पूर्ण

/*
 * Let's break subtree checking for now... otherwise we'll have to embed parent fh
 * but there might not be enough space.
 */
अटल पूर्णांक
nfs_encode_fh(काष्ठा inode *inode, __u32 *p, पूर्णांक *max_len, काष्ठा inode *parent)
अणु
	काष्ठा nfs_fh *server_fh = NFS_FH(inode);
	काष्ठा nfs_fh *clnt_fh = nfs_exp_embedfh(p);
	माप_प्रकार fh_size = दुरत्व(काष्ठा nfs_fh, data) + server_fh->size;
	पूर्णांक len = EMBED_FH_OFF + XDR_QUADLEN(fh_size);

	dprपूर्णांकk("%s: max fh len %d inode %p parent %p",
		__func__, *max_len, inode, parent);

	अगर (*max_len < len || IS_AUTOMOUNT(inode)) अणु
		dprपूर्णांकk("%s: fh len %d too small, required %d\n",
			__func__, *max_len, len);
		*max_len = len;
		वापस खाताID_INVALID;
	पूर्ण

	p[खाताID_HIGH_OFF] = NFS_खाताID(inode) >> 32;
	p[खाताID_LOW_OFF] = NFS_खाताID(inode);
	p[खाता_I_TYPE_OFF] = inode->i_mode & S_IFMT;
	p[len - 1] = 0; /* Padding */
	nfs_copy_fh(clnt_fh, server_fh);
	*max_len = len;
	dprपूर्णांकk("%s: result fh fileid %llu mode %u size %d\n",
		__func__, NFS_खाताID(inode), inode->i_mode, *max_len);
	वापस *max_len;
पूर्ण

अटल काष्ठा dentry *
nfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा nfs4_label *label = शून्य;
	काष्ठा nfs_fattr *fattr = शून्य;
	काष्ठा nfs_fh *server_fh = nfs_exp_embedfh(fid->raw);
	माप_प्रकार fh_size = दुरत्व(काष्ठा nfs_fh, data) + server_fh->size;
	स्थिर काष्ठा nfs_rpc_ops *rpc_ops;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	पूर्णांक len = EMBED_FH_OFF + XDR_QUADLEN(fh_size);
	u32 *p = fid->raw;
	पूर्णांक ret;

	/* शून्य translates to ESTALE */
	अगर (fh_len < len || fh_type != len)
		वापस शून्य;

	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य) अणु
		dentry = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	fattr->fileid = ((u64)p[खाताID_HIGH_OFF] << 32) + p[खाताID_LOW_OFF];
	fattr->mode = p[खाता_I_TYPE_OFF];
	fattr->valid |= NFS_ATTR_FATTR_खाताID | NFS_ATTR_FATTR_TYPE;

	dprपूर्णांकk("%s: fileid %llu mode %d\n", __func__, fattr->fileid, fattr->mode);

	inode = nfs_ilookup(sb, fattr, server_fh);
	अगर (inode)
		जाओ out_found;

	label = nfs4_label_alloc(NFS_SB(sb), GFP_KERNEL);
	अगर (IS_ERR(label)) अणु
		dentry = ERR_CAST(label);
		जाओ out_मुक्त_fattr;
	पूर्ण

	rpc_ops = NFS_SB(sb)->nfs_client->rpc_ops;
	ret = rpc_ops->getattr(NFS_SB(sb), server_fh, fattr, label, शून्य);
	अगर (ret) अणु
		dprपूर्णांकk("%s: getattr failed %d\n", __func__, ret);
		trace_nfs_fh_to_dentry(sb, server_fh, fattr->fileid, ret);
		dentry = ERR_PTR(ret);
		जाओ out_मुक्त_label;
	पूर्ण

	inode = nfs_fhget(sb, server_fh, fattr, label);

out_found:
	dentry = d_obtain_alias(inode);

out_मुक्त_label:
	nfs4_label_मुक्त(label);
out_मुक्त_fattr:
	nfs_मुक्त_fattr(fattr);
out:
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *
nfs_get_parent(काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = d_inode(dentry), *pinode;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा nfs_server *server = NFS_SB(sb);
	काष्ठा nfs_fattr *fattr = शून्य;
	काष्ठा nfs4_label *label = शून्य;
	काष्ठा dentry *parent;
	काष्ठा nfs_rpc_ops स्थिर *ops = server->nfs_client->rpc_ops;
	काष्ठा nfs_fh fh;

	अगर (!ops->lookupp)
		वापस ERR_PTR(-EACCES);

	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य) अणु
		parent = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	label = nfs4_label_alloc(server, GFP_KERNEL);
	अगर (IS_ERR(label)) अणु
		parent = ERR_CAST(label);
		जाओ out_मुक्त_fattr;
	पूर्ण

	ret = ops->lookupp(inode, &fh, fattr, label);
	अगर (ret) अणु
		parent = ERR_PTR(ret);
		जाओ out_मुक्त_label;
	पूर्ण

	pinode = nfs_fhget(sb, &fh, fattr, label);
	parent = d_obtain_alias(pinode);
out_मुक्त_label:
	nfs4_label_मुक्त(label);
out_मुक्त_fattr:
	nfs_मुक्त_fattr(fattr);
out:
	वापस parent;
पूर्ण

अटल u64 nfs_fetch_iversion(काष्ठा inode *inode)
अणु
	nfs_revalidate_inode(inode, NFS_INO_INVALID_CHANGE);
	वापस inode_peek_iversion_raw(inode);
पूर्ण

स्थिर काष्ठा export_operations nfs_export_ops = अणु
	.encode_fh = nfs_encode_fh,
	.fh_to_dentry = nfs_fh_to_dentry,
	.get_parent = nfs_get_parent,
	.fetch_iversion = nfs_fetch_iversion,
	.flags = EXPORT_OP_NOWCC|EXPORT_OP_NOSUBTREECHK|
		EXPORT_OP_CLOSE_BEFORE_UNLINK|EXPORT_OP_REMOTE_FS|
		EXPORT_OP_NOATOMIC_ATTR,
पूर्ण;
