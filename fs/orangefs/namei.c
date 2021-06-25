<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

/*
 *  Linux VFS namei operations.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"

/*
 * Get a newly allocated inode to go with a negative dentry.
 */
अटल पूर्णांक orangefs_create(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *dir,
			काष्ठा dentry *dentry,
			umode_t mode,
			bool exclusive)
अणु
	काष्ठा orangefs_inode_s *parent = ORANGEFS_I(dir);
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा orangefs_object_kref ref;
	काष्ठा inode *inode;
	काष्ठा iattr iattr;
	पूर्णांक ret;

	gossip_debug(GOSSIP_NAME_DEBUG, "%s: %pd\n",
		     __func__,
		     dentry);

	new_op = op_alloc(ORANGEFS_VFS_OP_CREATE);
	अगर (!new_op)
		वापस -ENOMEM;

	new_op->upcall.req.create.parent_refn = parent->refn;

	fill_शेष_sys_attrs(new_op->upcall.req.create.attributes,
			       ORANGEFS_TYPE_METAखाता, mode);

	म_नकलन(new_op->upcall.req.create.d_name,
		dentry->d_name.name, ORANGEFS_NAME_MAX - 1);

	ret = service_operation(new_op, __func__, get_पूर्णांकerruptible_flag(dir));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: %pd: handle:%pU: fsid:%d: new_op:%p: ret:%d:\n",
		     __func__,
		     dentry,
		     &new_op->करोwncall.resp.create.refn.khandle,
		     new_op->करोwncall.resp.create.refn.fs_id,
		     new_op,
		     ret);

	अगर (ret < 0)
		जाओ out;

	ref = new_op->करोwncall.resp.create.refn;

	inode = orangefs_new_inode(dir->i_sb, dir, S_IFREG | mode, 0, &ref);
	अगर (IS_ERR(inode)) अणु
		gossip_err("%s: Failed to allocate inode for file :%pd:\n",
			   __func__,
			   dentry);
		ret = PTR_ERR(inode);
		जाओ out;
	पूर्ण

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: Assigned inode :%pU: for file :%pd:\n",
		     __func__,
		     get_khandle_from_ino(inode),
		     dentry);

	d_instantiate_new(dentry, inode);
	orangefs_set_समयout(dentry);

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: dentry instantiated for %pd\n",
		     __func__,
		     dentry);

	स_रखो(&iattr, 0, माप iattr);
	iattr.ia_valid |= ATTR_MTIME | ATTR_CTIME;
	iattr.ia_mसमय = iattr.ia_स_समय = current_समय(dir);
	__orangefs_setattr(dir, &iattr);
	ret = 0;
out:
	op_release(new_op);
	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: %pd: returning %d\n",
		     __func__,
		     dentry,
		     ret);
	वापस ret;
पूर्ण

/*
 * Attempt to resolve an object name (dentry->d_name), parent handle, and
 * fsid पूर्णांकo a handle क्रम the object.
 */
अटल काष्ठा dentry *orangefs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा orangefs_inode_s *parent = ORANGEFS_I(dir);
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा inode *inode;
	पूर्णांक ret = -EINVAL;

	/*
	 * in theory we could skip a lookup here (अगर the पूर्णांकent is to
	 * create) in order to aव्योम a potentially failed lookup, but
	 * leaving it in can skip a valid lookup and try to create a file
	 * that alपढ़ोy exists (e.g. the vfs alपढ़ोy handles checking क्रम
	 * -EEXIST on O_EXCL खोलोs, which is broken अगर we skip this lookup
	 * in the create path)
	 */
	gossip_debug(GOSSIP_NAME_DEBUG, "%s called on %pd\n",
		     __func__, dentry);

	अगर (dentry->d_name.len > (ORANGEFS_NAME_MAX - 1))
		वापस ERR_PTR(-ENAMETOOLONG);

	new_op = op_alloc(ORANGEFS_VFS_OP_LOOKUP);
	अगर (!new_op)
		वापस ERR_PTR(-ENOMEM);

	new_op->upcall.req.lookup.sym_follow = ORANGEFS_LOOKUP_LINK_NO_FOLLOW;

	gossip_debug(GOSSIP_NAME_DEBUG, "%s:%s:%d using parent %pU\n",
		     __खाता__,
		     __func__,
		     __LINE__,
		     &parent->refn.khandle);
	new_op->upcall.req.lookup.parent_refn = parent->refn;

	म_नकलन(new_op->upcall.req.lookup.d_name, dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: doing lookup on %s under %pU,%d\n",
		     __func__,
		     new_op->upcall.req.lookup.d_name,
		     &new_op->upcall.req.lookup.parent_refn.khandle,
		     new_op->upcall.req.lookup.parent_refn.fs_id);

	ret = service_operation(new_op, __func__, get_पूर्णांकerruptible_flag(dir));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Lookup Got %pU, fsid %d (ret=%d)\n",
		     &new_op->करोwncall.resp.lookup.refn.khandle,
		     new_op->करोwncall.resp.lookup.refn.fs_id,
		     ret);

	अगर (ret == 0) अणु
		orangefs_set_समयout(dentry);
		inode = orangefs_iget(dir->i_sb, &new_op->करोwncall.resp.lookup.refn);
	पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
		inode = शून्य;
	पूर्ण अन्यथा अणु
		/* must be a non-recoverable error */
		inode = ERR_PTR(ret);
	पूर्ण

	op_release(new_op);
	वापस d_splice_alias(inode, dentry);
पूर्ण

/* वापस 0 on success; non-zero otherwise */
अटल पूर्णांक orangefs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा orangefs_inode_s *parent = ORANGEFS_I(dir);
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा iattr iattr;
	पूर्णांक ret;

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: called on %pd\n"
		     "  (inode %pU): Parent is %pU | fs_id %d\n",
		     __func__,
		     dentry,
		     get_khandle_from_ino(inode),
		     &parent->refn.khandle,
		     parent->refn.fs_id);

	new_op = op_alloc(ORANGEFS_VFS_OP_REMOVE);
	अगर (!new_op)
		वापस -ENOMEM;

	new_op->upcall.req.हटाओ.parent_refn = parent->refn;
	म_नकलन(new_op->upcall.req.हटाओ.d_name, dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);

	ret = service_operation(new_op, "orangefs_unlink",
				get_पूर्णांकerruptible_flag(inode));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "%s: service_operation returned:%d:\n",
		     __func__,
		     ret);

	op_release(new_op);

	अगर (!ret) अणु
		drop_nlink(inode);

		स_रखो(&iattr, 0, माप iattr);
		iattr.ia_valid |= ATTR_MTIME | ATTR_CTIME;
		iattr.ia_mसमय = iattr.ia_स_समय = current_समय(dir);
		__orangefs_setattr(dir, &iattr);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_symlink(काष्ठा user_namespace *mnt_userns,
		         काष्ठा inode *dir,
			 काष्ठा dentry *dentry,
			 स्थिर अक्षर *symname)
अणु
	काष्ठा orangefs_inode_s *parent = ORANGEFS_I(dir);
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा orangefs_object_kref ref;
	काष्ठा inode *inode;
	काष्ठा iattr iattr;
	पूर्णांक mode = 0755;
	पूर्णांक ret;

	gossip_debug(GOSSIP_NAME_DEBUG, "%s: called\n", __func__);

	अगर (!symname)
		वापस -EINVAL;

	अगर (म_माप(symname)+1 > ORANGEFS_NAME_MAX)
		वापस -ENAMETOOLONG;

	new_op = op_alloc(ORANGEFS_VFS_OP_SYMLINK);
	अगर (!new_op)
		वापस -ENOMEM;

	new_op->upcall.req.sym.parent_refn = parent->refn;

	fill_शेष_sys_attrs(new_op->upcall.req.sym.attributes,
			       ORANGEFS_TYPE_SYMLINK,
			       mode);

	म_नकलन(new_op->upcall.req.sym.entry_name,
		dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);
	म_नकलन(new_op->upcall.req.sym.target, symname, ORANGEFS_NAME_MAX - 1);

	ret = service_operation(new_op, __func__, get_पूर्णांकerruptible_flag(dir));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Symlink Got ORANGEFS handle %pU on fsid %d (ret=%d)\n",
		     &new_op->करोwncall.resp.sym.refn.khandle,
		     new_op->करोwncall.resp.sym.refn.fs_id, ret);

	अगर (ret < 0) अणु
		gossip_debug(GOSSIP_NAME_DEBUG,
			    "%s: failed with error code %d\n",
			    __func__, ret);
		जाओ out;
	पूर्ण

	ref = new_op->करोwncall.resp.sym.refn;

	inode = orangefs_new_inode(dir->i_sb, dir, S_IFLNK | mode, 0, &ref);
	अगर (IS_ERR(inode)) अणु
		gossip_err
		    ("*** Failed to allocate orangefs symlink inode\n");
		ret = PTR_ERR(inode);
		जाओ out;
	पूर्ण
	/*
	 * This is necessary because orangefs_inode_getattr will not
	 * re-पढ़ो symlink size as it is impossible क्रम it to change.
	 * Invalidating the cache करोes not help.  orangefs_new_inode
	 * करोes not set the correct size (it करोes not know symname).
	 */
	inode->i_size = म_माप(symname);

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Assigned symlink inode new number of %pU\n",
		     get_khandle_from_ino(inode));

	d_instantiate_new(dentry, inode);
	orangefs_set_समयout(dentry);

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Inode (Symlink) %pU -> %pd\n",
		     get_khandle_from_ino(inode),
		     dentry);

	स_रखो(&iattr, 0, माप iattr);
	iattr.ia_valid |= ATTR_MTIME | ATTR_CTIME;
	iattr.ia_mसमय = iattr.ia_स_समय = current_समय(dir);
	__orangefs_setattr(dir, &iattr);
	ret = 0;
out:
	op_release(new_op);
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			  काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा orangefs_inode_s *parent = ORANGEFS_I(dir);
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा orangefs_object_kref ref;
	काष्ठा inode *inode;
	काष्ठा iattr iattr;
	पूर्णांक ret;

	new_op = op_alloc(ORANGEFS_VFS_OP_MKसूची);
	अगर (!new_op)
		वापस -ENOMEM;

	new_op->upcall.req.सूची_गढ़ो.parent_refn = parent->refn;

	fill_शेष_sys_attrs(new_op->upcall.req.सूची_गढ़ो.attributes,
			      ORANGEFS_TYPE_सूचीECTORY, mode);

	म_नकलन(new_op->upcall.req.सूची_गढ़ो.d_name,
		dentry->d_name.name, ORANGEFS_NAME_MAX - 1);

	ret = service_operation(new_op, __func__, get_पूर्णांकerruptible_flag(dir));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Mkdir Got ORANGEFS handle %pU on fsid %d\n",
		     &new_op->करोwncall.resp.सूची_गढ़ो.refn.khandle,
		     new_op->करोwncall.resp.सूची_गढ़ो.refn.fs_id);

	अगर (ret < 0) अणु
		gossip_debug(GOSSIP_NAME_DEBUG,
			     "%s: failed with error code %d\n",
			     __func__, ret);
		जाओ out;
	पूर्ण

	ref = new_op->करोwncall.resp.सूची_गढ़ो.refn;

	inode = orangefs_new_inode(dir->i_sb, dir, S_IFसूची | mode, 0, &ref);
	अगर (IS_ERR(inode)) अणु
		gossip_err("*** Failed to allocate orangefs dir inode\n");
		ret = PTR_ERR(inode);
		जाओ out;
	पूर्ण

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Assigned dir inode new number of %pU\n",
		     get_khandle_from_ino(inode));

	d_instantiate_new(dentry, inode);
	orangefs_set_समयout(dentry);

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "Inode (Directory) %pU -> %pd\n",
		     get_khandle_from_ino(inode),
		     dentry);

	/*
	 * NOTE: we have no good way to keep nlink consistent क्रम directories
	 * across clients; keep स्थिरant at 1.
	 */
	स_रखो(&iattr, 0, माप iattr);
	iattr.ia_valid |= ATTR_MTIME | ATTR_CTIME;
	iattr.ia_mसमय = iattr.ia_स_समय = current_समय(dir);
	__orangefs_setattr(dir, &iattr);
out:
	op_release(new_op);
	वापस ret;
पूर्ण

अटल पूर्णांक orangefs_नाम(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir,
			काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir,
			काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा iattr iattr;
	पूर्णांक ret;

	अगर (flags)
		वापस -EINVAL;

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "orangefs_rename: called (%pd2 => %pd2) ct=%d\n",
		     old_dentry, new_dentry, d_count(new_dentry));

	स_रखो(&iattr, 0, माप iattr);
	iattr.ia_valid |= ATTR_MTIME | ATTR_CTIME;
	iattr.ia_mसमय = iattr.ia_स_समय = current_समय(new_dir);
	__orangefs_setattr(new_dir, &iattr);

	new_op = op_alloc(ORANGEFS_VFS_OP_RENAME);
	अगर (!new_op)
		वापस -EINVAL;

	new_op->upcall.req.नाम.old_parent_refn = ORANGEFS_I(old_dir)->refn;
	new_op->upcall.req.नाम.new_parent_refn = ORANGEFS_I(new_dir)->refn;

	म_नकलन(new_op->upcall.req.नाम.d_old_name,
		old_dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);
	म_नकलन(new_op->upcall.req.नाम.d_new_name,
		new_dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);

	ret = service_operation(new_op,
				"orangefs_rename",
				get_पूर्णांकerruptible_flag(old_dentry->d_inode));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "orangefs_rename: got downcall status %d\n",
		     ret);

	अगर (new_dentry->d_inode)
		new_dentry->d_inode->i_स_समय = current_समय(new_dentry->d_inode);

	op_release(new_op);
	वापस ret;
पूर्ण

/* ORANGEFS implementation of VFS inode operations क्रम directories */
स्थिर काष्ठा inode_operations orangefs_dir_inode_operations = अणु
	.lookup = orangefs_lookup,
	.get_acl = orangefs_get_acl,
	.set_acl = orangefs_set_acl,
	.create = orangefs_create,
	.unlink = orangefs_unlink,
	.symlink = orangefs_symlink,
	.सूची_गढ़ो = orangefs_सूची_गढ़ो,
	.सूची_हटाओ = orangefs_unlink,
	.नाम = orangefs_नाम,
	.setattr = orangefs_setattr,
	.getattr = orangefs_getattr,
	.listxattr = orangefs_listxattr,
	.permission = orangefs_permission,
	.update_समय = orangefs_update_समय,
पूर्ण;
