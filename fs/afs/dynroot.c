<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS dynamic root handling
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/dns_resolver.h>
#समावेश "internal.h"

अटल atomic_t afs_स्वतःcell_ino;

/*
 * iget5() comparator क्रम inode created by स्वतःcell operations
 *
 * These pseuकरो inodes करोn't match anything.
 */
अटल पूर्णांक afs_iget5_pseuकरो_test(काष्ठा inode *inode, व्योम *opaque)
अणु
	वापस 0;
पूर्ण

/*
 * iget5() inode initialiser
 */
अटल पूर्णांक afs_iget5_pseuकरो_set(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(inode->i_sb);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा afs_fid *fid = opaque;

	vnode->volume		= as->volume;
	vnode->fid		= *fid;
	inode->i_ino		= fid->vnode;
	inode->i_generation	= fid->unique;
	वापस 0;
पूर्ण

/*
 * Create an inode क्रम a dynamic root directory or an स्वतःcell dynamic
 * स्वतःmount dir.
 */
काष्ठा inode *afs_iget_pseuकरो_dir(काष्ठा super_block *sb, bool root)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(sb);
	काष्ठा afs_vnode *vnode;
	काष्ठा inode *inode;
	काष्ठा afs_fid fid = अणुपूर्ण;

	_enter("");

	अगर (as->volume)
		fid.vid = as->volume->vid;
	अगर (root) अणु
		fid.vnode = 1;
		fid.unique = 1;
	पूर्ण अन्यथा अणु
		fid.vnode = atomic_inc_वापस(&afs_स्वतःcell_ino);
		fid.unique = 0;
	पूर्ण

	inode = iget5_locked(sb, fid.vnode,
			     afs_iget5_pseuकरो_test, afs_iget5_pseuकरो_set, &fid);
	अगर (!inode) अणु
		_leave(" = -ENOMEM");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	_debug("GOT INODE %p { ino=%lu, vl=%llx, vn=%llx, u=%x }",
	       inode, inode->i_ino, fid.vid, fid.vnode, fid.unique);

	vnode = AFS_FS_I(inode);

	/* there shouldn't be an existing inode */
	BUG_ON(!(inode->i_state & I_NEW));

	inode->i_size		= 0;
	inode->i_mode		= S_IFसूची | S_IRUGO | S_IXUGO;
	अगर (root) अणु
		inode->i_op	= &afs_dynroot_inode_operations;
		inode->i_fop	= &simple_dir_operations;
	पूर्ण अन्यथा अणु
		inode->i_op	= &afs_स्वतःcell_inode_operations;
	पूर्ण
	set_nlink(inode, 2);
	inode->i_uid		= GLOBAL_ROOT_UID;
	inode->i_gid		= GLOBAL_ROOT_GID;
	inode->i_स_समय = inode->i_aसमय = inode->i_mसमय = current_समय(inode);
	inode->i_blocks		= 0;
	inode->i_generation	= 0;

	set_bit(AFS_VNODE_PSEUDOसूची, &vnode->flags);
	अगर (!root) अणु
		set_bit(AFS_VNODE_MOUNTPOINT, &vnode->flags);
		inode->i_flags |= S_AUTOMOUNT;
	पूर्ण

	inode->i_flags |= S_NOATIME;
	unlock_new_inode(inode);
	_leave(" = %p", inode);
	वापस inode;
पूर्ण

/*
 * Probe to see अगर a cell may exist.  This prevents positive dentries from
 * being created unnecessarily.
 */
अटल पूर्णांक afs_probe_cell_name(काष्ठा dentry *dentry)
अणु
	काष्ठा afs_cell *cell;
	काष्ठा afs_net *net = afs_d2net(dentry);
	स्थिर अक्षर *name = dentry->d_name.name;
	माप_प्रकार len = dentry->d_name.len;
	पूर्णांक ret;

	/* Names prefixed with a करोt are R/W mounts. */
	अगर (name[0] == '.') अणु
		अगर (len == 1)
			वापस -EINVAL;
		name++;
		len--;
	पूर्ण

	cell = afs_find_cell(net, name, len, afs_cell_trace_use_probe);
	अगर (!IS_ERR(cell)) अणु
		afs_unuse_cell(net, cell, afs_cell_trace_unuse_probe);
		वापस 0;
	पूर्ण

	ret = dns_query(net->net, "afsdb", name, len, "srv=1",
			शून्य, शून्य, false);
	अगर (ret == -ENODATA)
		ret = -EDESTADDRREQ;
	वापस ret;
पूर्ण

/*
 * Try to स्वतः mount the mountpoपूर्णांक with pseuकरो directory, अगर the स्वतःcell
 * operation is setted.
 */
काष्ठा inode *afs_try_स्वतः_mntpt(काष्ठा dentry *dentry, काष्ठा inode *dir)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(dir);
	काष्ठा inode *inode;
	पूर्णांक ret = -ENOENT;

	_enter("%p{%pd}, {%llx:%llu}",
	       dentry, dentry, vnode->fid.vid, vnode->fid.vnode);

	अगर (!test_bit(AFS_VNODE_AUTOCELL, &vnode->flags))
		जाओ out;

	ret = afs_probe_cell_name(dentry);
	अगर (ret < 0)
		जाओ out;

	inode = afs_iget_pseuकरो_dir(dir->i_sb, false);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		जाओ out;
	पूर्ण

	_leave("= %p", inode);
	वापस inode;

out:
	_leave("= %d", ret);
	वापस ret == -ENOENT ? शून्य : ERR_PTR(ret);
पूर्ण

/*
 * Look up @cell in a dynroot directory.  This is a substitution क्रम the
 * local cell name क्रम the net namespace.
 */
अटल काष्ठा dentry *afs_lookup_atcell(काष्ठा dentry *dentry)
अणु
	काष्ठा afs_cell *cell;
	काष्ठा afs_net *net = afs_d2net(dentry);
	काष्ठा dentry *ret;
	अक्षर *name;
	पूर्णांक len;

	अगर (!net->ws_cell)
		वापस ERR_PTR(-ENOENT);

	ret = ERR_PTR(-ENOMEM);
	name = kदो_स्मृति(AFS_MAXCELLNAME + 1, GFP_KERNEL);
	अगर (!name)
		जाओ out_p;

	करोwn_पढ़ो(&net->cells_lock);
	cell = net->ws_cell;
	अगर (cell) अणु
		len = cell->name_len;
		स_नकल(name, cell->name, len + 1);
	पूर्ण
	up_पढ़ो(&net->cells_lock);

	ret = ERR_PTR(-ENOENT);
	अगर (!cell)
		जाओ out_n;

	ret = lookup_one_len(name, dentry->d_parent, len);

	/* We करोn't want to d_add() the @cell dentry here as we don't want to
	 * the cached dentry to hide changes to the local cell name.
	 */

out_n:
	kमुक्त(name);
out_p:
	वापस ret;
पूर्ण

/*
 * Look up an entry in a dynroot directory.
 */
अटल काष्ठा dentry *afs_dynroot_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
					 अचिन्हित पूर्णांक flags)
अणु
	_enter("%pd", dentry);

	ASSERTCMP(d_inode(dentry), ==, शून्य);

	अगर (flags & LOOKUP_CREATE)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (dentry->d_name.len >= AFSNAMEMAX) अणु
		_leave(" = -ENAMETOOLONG");
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण

	अगर (dentry->d_name.len == 5 &&
	    स_भेद(dentry->d_name.name, "@cell", 5) == 0)
		वापस afs_lookup_atcell(dentry);

	वापस d_splice_alias(afs_try_स्वतः_mntpt(dentry, dir), dentry);
पूर्ण

स्थिर काष्ठा inode_operations afs_dynroot_inode_operations = अणु
	.lookup		= afs_dynroot_lookup,
पूर्ण;

/*
 * Dirs in the dynamic root करोn't need revalidation.
 */
अटल पूर्णांक afs_dynroot_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस 1;
पूर्ण

/*
 * Allow the VFS to enquire as to whether a dentry should be unhashed (mustn't
 * sleep)
 * - called from dput() when d_count is going to 0.
 * - वापस 1 to request dentry be unhashed, 0 otherwise
 */
अटल पूर्णांक afs_dynroot_d_delete(स्थिर काष्ठा dentry *dentry)
अणु
	वापस d_really_is_positive(dentry);
पूर्ण

स्थिर काष्ठा dentry_operations afs_dynroot_dentry_operations = अणु
	.d_revalidate	= afs_dynroot_d_revalidate,
	.d_delete	= afs_dynroot_d_delete,
	.d_release	= afs_d_release,
	.d_स्वतःmount	= afs_d_स्वतःmount,
पूर्ण;

/*
 * Create a manually added cell mount directory.
 * - The caller must hold net->proc_cells_lock
 */
पूर्णांक afs_dynroot_सूची_गढ़ो(काष्ठा afs_net *net, काष्ठा afs_cell *cell)
अणु
	काष्ठा super_block *sb = net->dynroot_sb;
	काष्ठा dentry *root, *subdir;
	पूर्णांक ret;

	अगर (!sb || atomic_पढ़ो(&sb->s_active) == 0)
		वापस 0;

	/* Let the ->lookup op करो the creation */
	root = sb->s_root;
	inode_lock(root->d_inode);
	subdir = lookup_one_len(cell->name, root, cell->name_len);
	अगर (IS_ERR(subdir)) अणु
		ret = PTR_ERR(subdir);
		जाओ unlock;
	पूर्ण

	/* Note that we're retaining an extra ref on the dentry */
	subdir->d_fsdata = (व्योम *)1UL;
	ret = 0;
unlock:
	inode_unlock(root->d_inode);
	वापस ret;
पूर्ण

/*
 * Remove a manually added cell mount directory.
 * - The caller must hold net->proc_cells_lock
 */
व्योम afs_dynroot_सूची_हटाओ(काष्ठा afs_net *net, काष्ठा afs_cell *cell)
अणु
	काष्ठा super_block *sb = net->dynroot_sb;
	काष्ठा dentry *root, *subdir;

	अगर (!sb || atomic_पढ़ो(&sb->s_active) == 0)
		वापस;

	root = sb->s_root;
	inode_lock(root->d_inode);

	/* Don't want to trigger a lookup call, which will re-add the cell */
	subdir = try_lookup_one_len(cell->name, root, cell->name_len);
	अगर (IS_ERR_OR_शून्य(subdir)) अणु
		_debug("lookup %ld", PTR_ERR(subdir));
		जाओ no_dentry;
	पूर्ण

	_debug("rmdir %pd %u", subdir, d_count(subdir));

	अगर (subdir->d_fsdata) अणु
		_debug("unpin %u", d_count(subdir));
		subdir->d_fsdata = शून्य;
		dput(subdir);
	पूर्ण
	dput(subdir);
no_dentry:
	inode_unlock(root->d_inode);
	_leave("");
पूर्ण

/*
 * Populate a newly created dynamic root with cell names.
 */
पूर्णांक afs_dynroot_populate(काष्ठा super_block *sb)
अणु
	काष्ठा afs_cell *cell;
	काष्ठा afs_net *net = afs_sb2net(sb);
	पूर्णांक ret;

	mutex_lock(&net->proc_cells_lock);

	net->dynroot_sb = sb;
	hlist_क्रम_each_entry(cell, &net->proc_cells, proc_link) अणु
		ret = afs_dynroot_सूची_गढ़ो(net, cell);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	ret = 0;
out:
	mutex_unlock(&net->proc_cells_lock);
	वापस ret;

error:
	net->dynroot_sb = शून्य;
	जाओ out;
पूर्ण

/*
 * When a dynamic root that's in the process of being destroyed, depopulate it
 * of pinned directories.
 */
व्योम afs_dynroot_depopulate(काष्ठा super_block *sb)
अणु
	काष्ठा afs_net *net = afs_sb2net(sb);
	काष्ठा dentry *root = sb->s_root, *subdir, *पंचांगp;

	/* Prevent more subdirs from being created */
	mutex_lock(&net->proc_cells_lock);
	अगर (net->dynroot_sb == sb)
		net->dynroot_sb = शून्य;
	mutex_unlock(&net->proc_cells_lock);

	अगर (root) अणु
		inode_lock(root->d_inode);

		/* Remove all the pins क्रम dirs created क्रम manually added cells */
		list_क्रम_each_entry_safe(subdir, पंचांगp, &root->d_subdirs, d_child) अणु
			अगर (subdir->d_fsdata) अणु
				subdir->d_fsdata = शून्य;
				dput(subdir);
			पूर्ण
		पूर्ण

		inode_unlock(root->d_inode);
	पूर्ण
पूर्ण
