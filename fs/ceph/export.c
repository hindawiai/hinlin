<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/exportfs.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "super.h"
#समावेश "mds_client.h"

/*
 * Basic fh
 */
काष्ठा ceph_nfs_fh अणु
	u64 ino;
पूर्ण __attribute__ ((packed));

/*
 * Larger fh that includes parent ino.
 */
काष्ठा ceph_nfs_confh अणु
	u64 ino, parent_ino;
पूर्ण __attribute__ ((packed));

/*
 * fh क्रम snapped inode
 */
काष्ठा ceph_nfs_snapfh अणु
	u64 ino;
	u64 snapid;
	u64 parent_ino;
	u32 hash;
पूर्ण __attribute__ ((packed));

अटल पूर्णांक ceph_encode_snapfh(काष्ठा inode *inode, u32 *rawfh, पूर्णांक *max_len,
			      काष्ठा inode *parent_inode)
अणु
	अटल स्थिर पूर्णांक snap_handle_length =
		माप(काष्ठा ceph_nfs_snapfh) >> 2;
	काष्ठा ceph_nfs_snapfh *sfh = (व्योम *)rawfh;
	u64 snapid = ceph_snap(inode);
	पूर्णांक ret;
	bool no_parent = true;

	अगर (*max_len < snap_handle_length) अणु
		*max_len = snap_handle_length;
		ret = खाताID_INVALID;
		जाओ out;
	पूर्ण

	ret =  -EINVAL;
	अगर (snapid != CEPH_SNAPसूची) अणु
		काष्ठा inode *dir;
		काष्ठा dentry *dentry = d_find_alias(inode);
		अगर (!dentry)
			जाओ out;

		rcu_पढ़ो_lock();
		dir = d_inode_rcu(dentry->d_parent);
		अगर (ceph_snap(dir) != CEPH_SNAPसूची) अणु
			sfh->parent_ino = ceph_ino(dir);
			sfh->hash = ceph_dentry_hash(dir, dentry);
			no_parent = false;
		पूर्ण
		rcu_पढ़ो_unlock();
		dput(dentry);
	पूर्ण

	अगर (no_parent) अणु
		अगर (!S_ISसूची(inode->i_mode))
			जाओ out;
		sfh->parent_ino = sfh->ino;
		sfh->hash = 0;
	पूर्ण
	sfh->ino = ceph_ino(inode);
	sfh->snapid = snapid;

	*max_len = snap_handle_length;
	ret = खाताID_BTRFS_WITH_PARENT;
out:
	करोut("encode_snapfh %llx.%llx ret=%d\n", ceph_vinop(inode), ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ceph_encode_fh(काष्ठा inode *inode, u32 *rawfh, पूर्णांक *max_len,
			  काष्ठा inode *parent_inode)
अणु
	अटल स्थिर पूर्णांक handle_length =
		माप(काष्ठा ceph_nfs_fh) >> 2;
	अटल स्थिर पूर्णांक connected_handle_length =
		माप(काष्ठा ceph_nfs_confh) >> 2;
	पूर्णांक type;

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस ceph_encode_snapfh(inode, rawfh, max_len, parent_inode);

	अगर (parent_inode && (*max_len < connected_handle_length)) अणु
		*max_len = connected_handle_length;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (*max_len < handle_length) अणु
		*max_len = handle_length;
		वापस खाताID_INVALID;
	पूर्ण

	अगर (parent_inode) अणु
		काष्ठा ceph_nfs_confh *cfh = (व्योम *)rawfh;
		करोut("encode_fh %llx with parent %llx\n",
		     ceph_ino(inode), ceph_ino(parent_inode));
		cfh->ino = ceph_ino(inode);
		cfh->parent_ino = ceph_ino(parent_inode);
		*max_len = connected_handle_length;
		type = खाताID_INO32_GEN_PARENT;
	पूर्ण अन्यथा अणु
		काष्ठा ceph_nfs_fh *fh = (व्योम *)rawfh;
		करोut("encode_fh %llx\n", ceph_ino(inode));
		fh->ino = ceph_ino(inode);
		*max_len = handle_length;
		type = खाताID_INO32_GEN;
	पूर्ण
	वापस type;
पूर्ण

अटल काष्ठा inode *__lookup_inode(काष्ठा super_block *sb, u64 ino)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(sb)->mdsc;
	काष्ठा inode *inode;
	काष्ठा ceph_vino vino;
	पूर्णांक err;

	vino.ino = ino;
	vino.snap = CEPH_NOSNAP;

	अगर (ceph_vino_is_reserved(vino))
		वापस ERR_PTR(-ESTALE);

	inode = ceph_find_inode(sb, vino);
	अगर (!inode) अणु
		काष्ठा ceph_mds_request *req;
		पूर्णांक mask;

		req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LOOKUPINO,
					       USE_ANY_MDS);
		अगर (IS_ERR(req))
			वापस ERR_CAST(req);

		mask = CEPH_STAT_CAP_INODE;
		अगर (ceph_security_xattr_wanted(d_inode(sb->s_root)))
			mask |= CEPH_CAP_XATTR_SHARED;
		req->r_args.lookupino.mask = cpu_to_le32(mask);

		req->r_ino1 = vino;
		req->r_num_caps = 1;
		err = ceph_mdsc_करो_request(mdsc, शून्य, req);
		inode = req->r_target_inode;
		अगर (inode)
			ihold(inode);
		ceph_mdsc_put_request(req);
		अगर (!inode)
			वापस err < 0 ? ERR_PTR(err) : ERR_PTR(-ESTALE);
	पूर्ण
	वापस inode;
पूर्ण

काष्ठा inode *ceph_lookup_inode(काष्ठा super_block *sb, u64 ino)
अणु
	काष्ठा inode *inode = __lookup_inode(sb, ino);
	अगर (IS_ERR(inode))
		वापस inode;
	अगर (inode->i_nlink == 0) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा dentry *__fh_to_dentry(काष्ठा super_block *sb, u64 ino)
अणु
	काष्ठा inode *inode = __lookup_inode(sb, ino);
	पूर्णांक err;

	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	/* We need LINK caps to reliably check i_nlink */
	err = ceph_करो_getattr(inode, CEPH_CAP_LINK_SHARED, false);
	अगर (err) अणु
		iput(inode);
		वापस ERR_PTR(err);
	पूर्ण
	/* -ESTALE अगर inode as been unlinked and no file is खोलो */
	अगर ((inode->i_nlink == 0) && (atomic_पढ़ो(&inode->i_count) == 1)) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *__snapfh_to_dentry(काष्ठा super_block *sb,
					  काष्ठा ceph_nfs_snapfh *sfh,
					  bool want_parent)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(sb)->mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा inode *inode;
	काष्ठा ceph_vino vino;
	पूर्णांक mask;
	पूर्णांक err;
	bool unlinked = false;

	अगर (want_parent) अणु
		vino.ino = sfh->parent_ino;
		अगर (sfh->snapid == CEPH_SNAPसूची)
			vino.snap = CEPH_NOSNAP;
		अन्यथा अगर (sfh->ino == sfh->parent_ino)
			vino.snap = CEPH_SNAPसूची;
		अन्यथा
			vino.snap = sfh->snapid;
	पूर्ण अन्यथा अणु
		vino.ino = sfh->ino;
		vino.snap = sfh->snapid;
	पूर्ण

	अगर (ceph_vino_is_reserved(vino))
		वापस ERR_PTR(-ESTALE);

	inode = ceph_find_inode(sb, vino);
	अगर (inode)
		वापस d_obtain_alias(inode);

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LOOKUPINO,
				       USE_ANY_MDS);
	अगर (IS_ERR(req))
		वापस ERR_CAST(req);

	mask = CEPH_STAT_CAP_INODE;
	अगर (ceph_security_xattr_wanted(d_inode(sb->s_root)))
		mask |= CEPH_CAP_XATTR_SHARED;
	req->r_args.lookupino.mask = cpu_to_le32(mask);
	अगर (vino.snap < CEPH_NOSNAP) अणु
		req->r_args.lookupino.snapid = cpu_to_le64(vino.snap);
		अगर (!want_parent && sfh->ino != sfh->parent_ino) अणु
			req->r_args.lookupino.parent =
					cpu_to_le64(sfh->parent_ino);
			req->r_args.lookupino.hash =
					cpu_to_le32(sfh->hash);
		पूर्ण
	पूर्ण

	req->r_ino1 = vino;
	req->r_num_caps = 1;
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	inode = req->r_target_inode;
	अगर (inode) अणु
		अगर (vino.snap == CEPH_SNAPसूची) अणु
			अगर (inode->i_nlink == 0)
				unlinked = true;
			inode = ceph_get_snapdir(inode);
		पूर्ण अन्यथा अगर (ceph_snap(inode) == vino.snap) अणु
			ihold(inode);
		पूर्ण अन्यथा अणु
			/* mds करोes not support lookup snapped inode */
			inode = ERR_PTR(-EOPNOTSUPP);
		पूर्ण
	पूर्ण अन्यथा अणु
		inode = ERR_PTR(-ESTALE);
	पूर्ण
	ceph_mdsc_put_request(req);

	अगर (want_parent) अणु
		करोut("snapfh_to_parent %llx.%llx\n err=%d\n",
		     vino.ino, vino.snap, err);
	पूर्ण अन्यथा अणु
		करोut("snapfh_to_dentry %llx.%llx parent %llx hash %x err=%d",
		      vino.ino, vino.snap, sfh->parent_ino, sfh->hash, err);
	पूर्ण
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	/* see comments in ceph_get_parent() */
	वापस unlinked ? d_obtain_root(inode) : d_obtain_alias(inode);
पूर्ण

/*
 * convert regular fh to dentry
 */
अटल काष्ठा dentry *ceph_fh_to_dentry(काष्ठा super_block *sb,
					काष्ठा fid *fid,
					पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा ceph_nfs_fh *fh = (व्योम *)fid->raw;

	अगर (fh_type == खाताID_BTRFS_WITH_PARENT) अणु
		काष्ठा ceph_nfs_snapfh *sfh = (व्योम *)fid->raw;
		वापस __snapfh_to_dentry(sb, sfh, false);
	पूर्ण

	अगर (fh_type != खाताID_INO32_GEN  &&
	    fh_type != खाताID_INO32_GEN_PARENT)
		वापस शून्य;
	अगर (fh_len < माप(*fh) / 4)
		वापस शून्य;

	करोut("fh_to_dentry %llx\n", fh->ino);
	वापस __fh_to_dentry(sb, fh->ino);
पूर्ण

अटल काष्ठा dentry *__get_parent(काष्ठा super_block *sb,
				   काष्ठा dentry *child, u64 ino)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(sb)->mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा inode *inode;
	पूर्णांक mask;
	पूर्णांक err;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LOOKUPPARENT,
				       USE_ANY_MDS);
	अगर (IS_ERR(req))
		वापस ERR_CAST(req);

	अगर (child) अणु
		req->r_inode = d_inode(child);
		ihold(d_inode(child));
	पूर्ण अन्यथा अणु
		req->r_ino1 = (काष्ठा ceph_vino) अणु
			.ino = ino,
			.snap = CEPH_NOSNAP,
		पूर्ण;
	पूर्ण

	mask = CEPH_STAT_CAP_INODE;
	अगर (ceph_security_xattr_wanted(d_inode(sb->s_root)))
		mask |= CEPH_CAP_XATTR_SHARED;
	req->r_args.getattr.mask = cpu_to_le32(mask);

	req->r_num_caps = 1;
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	अगर (err) अणु
		ceph_mdsc_put_request(req);
		वापस ERR_PTR(err);
	पूर्ण

	inode = req->r_target_inode;
	अगर (inode)
		ihold(inode);
	ceph_mdsc_put_request(req);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *ceph_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा inode *inode = d_inode(child);
	काष्ठा dentry *dn;

	अगर (ceph_snap(inode) != CEPH_NOSNAP) अणु
		काष्ठा inode* dir;
		bool unlinked = false;
		/* करो not support non-directory */
		अगर (!d_is_dir(child)) अणु
			dn = ERR_PTR(-EINVAL);
			जाओ out;
		पूर्ण
		dir = __lookup_inode(inode->i_sb, ceph_ino(inode));
		अगर (IS_ERR(dir)) अणु
			dn = ERR_CAST(dir);
			जाओ out;
		पूर्ण
		/* There can be multiple paths to access snapped inode.
		 * For simplicity, treat snapdir of head inode as parent */
		अगर (ceph_snap(inode) != CEPH_SNAPसूची) अणु
			काष्ठा inode *snapdir = ceph_get_snapdir(dir);
			अगर (dir->i_nlink == 0)
				unlinked = true;
			iput(dir);
			अगर (IS_ERR(snapdir)) अणु
				dn = ERR_CAST(snapdir);
				जाओ out;
			पूर्ण
			dir = snapdir;
		पूर्ण
		/* If directory has alपढ़ोy been deleted, futher get_parent
		 * will fail. Do not mark snapdir dentry as disconnected,
		 * this prevent exportfs from करोing futher get_parent. */
		अगर (unlinked)
			dn = d_obtain_root(dir);
		अन्यथा
			dn = d_obtain_alias(dir);
	पूर्ण अन्यथा अणु
		dn = __get_parent(child->d_sb, child, 0);
	पूर्ण
out:
	करोut("get_parent %p ino %llx.%llx err=%ld\n",
	     child, ceph_vinop(inode), (दीर्घ)PTR_ERR_OR_ZERO(dn));
	वापस dn;
पूर्ण

/*
 * convert regular fh to parent
 */
अटल काष्ठा dentry *ceph_fh_to_parent(काष्ठा super_block *sb,
					काष्ठा fid *fid,
					पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा ceph_nfs_confh *cfh = (व्योम *)fid->raw;
	काष्ठा dentry *dentry;

	अगर (fh_type == खाताID_BTRFS_WITH_PARENT) अणु
		काष्ठा ceph_nfs_snapfh *sfh = (व्योम *)fid->raw;
		वापस __snapfh_to_dentry(sb, sfh, true);
	पूर्ण

	अगर (fh_type != खाताID_INO32_GEN_PARENT)
		वापस शून्य;
	अगर (fh_len < माप(*cfh) / 4)
		वापस शून्य;

	करोut("fh_to_parent %llx\n", cfh->parent_ino);
	dentry = __get_parent(sb, शून्य, cfh->ino);
	अगर (unlikely(dentry == ERR_PTR(-ENOENT)))
		dentry = __fh_to_dentry(sb, cfh->parent_ino);
	वापस dentry;
पूर्ण

अटल पूर्णांक __get_snap_name(काष्ठा dentry *parent, अक्षर *name,
			   काष्ठा dentry *child)
अणु
	काष्ठा inode *inode = d_inode(child);
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_mds_request *req = शून्य;
	अक्षर *last_name = शून्य;
	अचिन्हित next_offset = 2;
	पूर्णांक err = -EINVAL;

	अगर (ceph_ino(inode) != ceph_ino(dir))
		जाओ out;
	अगर (ceph_snap(inode) == CEPH_SNAPसूची) अणु
		अगर (ceph_snap(dir) == CEPH_NOSNAP) अणु
			म_नकल(name, fsc->mount_options->snapdir_name);
			err = 0;
		पूर्ण
		जाओ out;
	पूर्ण
	अगर (ceph_snap(dir) != CEPH_SNAPसूची)
		जाओ out;

	जबतक (1) अणु
		काष्ठा ceph_mds_reply_info_parsed *rinfo;
		काष्ठा ceph_mds_reply_dir_entry *rde;
		पूर्णांक i;

		req = ceph_mdsc_create_request(fsc->mdsc, CEPH_MDS_OP_LSSNAP,
					       USE_AUTH_MDS);
		अगर (IS_ERR(req)) अणु
			err = PTR_ERR(req);
			req = शून्य;
			जाओ out;
		पूर्ण
		err = ceph_alloc_सूची_पढ़ो_reply_buffer(req, inode);
		अगर (err)
			जाओ out;

		req->r_direct_mode = USE_AUTH_MDS;
		req->r_सूची_पढ़ो_offset = next_offset;
		req->r_args.सूची_पढ़ो.flags =
				cpu_to_le16(CEPH_READसूची_REPLY_BITFLAGS);
		अगर (last_name) अणु
			req->r_path2 = last_name;
			last_name = शून्य;
		पूर्ण

		req->r_inode = dir;
		ihold(dir);
		req->r_dentry = dget(parent);

		inode_lock(dir);
		err = ceph_mdsc_करो_request(fsc->mdsc, शून्य, req);
		inode_unlock(dir);

		अगर (err < 0)
			जाओ out;

		rinfo = &req->r_reply_info;
		क्रम (i = 0; i < rinfo->dir_nr; i++) अणु
			rde = rinfo->dir_entries + i;
			BUG_ON(!rde->inode.in);
			अगर (ceph_snap(inode) ==
			    le64_to_cpu(rde->inode.in->snapid)) अणु
				स_नकल(name, rde->name, rde->name_len);
				name[rde->name_len] = '\0';
				err = 0;
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (rinfo->dir_end)
			अवरोध;

		BUG_ON(rinfo->dir_nr <= 0);
		rde = rinfo->dir_entries + (rinfo->dir_nr - 1);
		next_offset += rinfo->dir_nr;
		last_name = kstrndup(rde->name, rde->name_len, GFP_KERNEL);
		अगर (!last_name) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		ceph_mdsc_put_request(req);
		req = शून्य;
	पूर्ण
	err = -ENOENT;
out:
	अगर (req)
		ceph_mdsc_put_request(req);
	kमुक्त(last_name);
	करोut("get_snap_name %p ino %llx.%llx err=%d\n",
	     child, ceph_vinop(inode), err);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_get_name(काष्ठा dentry *parent, अक्षर *name,
			 काष्ठा dentry *child)
अणु
	काष्ठा ceph_mds_client *mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा inode *inode = d_inode(child);
	पूर्णांक err;

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस __get_snap_name(parent, name, child);

	mdsc = ceph_inode_to_client(inode)->mdsc;
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LOOKUPNAME,
				       USE_ANY_MDS);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);

	inode_lock(d_inode(parent));

	req->r_inode = inode;
	ihold(inode);
	req->r_ino2 = ceph_vino(d_inode(parent));
	req->r_parent = d_inode(parent);
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_num_caps = 2;
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);

	inode_unlock(d_inode(parent));

	अगर (!err) अणु
		काष्ठा ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
		स_नकल(name, rinfo->dname, rinfo->dname_len);
		name[rinfo->dname_len] = 0;
		करोut("get_name %p ino %llx.%llx name %s\n",
		     child, ceph_vinop(inode), name);
	पूर्ण अन्यथा अणु
		करोut("get_name %p ino %llx.%llx err %d\n",
		     child, ceph_vinop(inode), err);
	पूर्ण

	ceph_mdsc_put_request(req);
	वापस err;
पूर्ण

स्थिर काष्ठा export_operations ceph_export_ops = अणु
	.encode_fh = ceph_encode_fh,
	.fh_to_dentry = ceph_fh_to_dentry,
	.fh_to_parent = ceph_fh_to_parent,
	.get_parent = ceph_get_parent,
	.get_name = ceph_get_name,
पूर्ण;
