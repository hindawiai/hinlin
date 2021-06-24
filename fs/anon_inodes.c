<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  fs/anon_inodes.c
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 *  Thanks to Arnd Bergmann क्रम code review and suggestions.
 *  More changes क्रम Thomas Gleixner suggestions.
 *
 */

#समावेश <linux/cred.h>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/magic.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/pseuकरो_fs.h>

#समावेश <linux/uaccess.h>

अटल काष्ठा vfsmount *anon_inode_mnt __पढ़ो_mostly;
अटल काष्ठा inode *anon_inode_inode;

/*
 * anon_inodefs_dname() is called from d_path().
 */
अटल अक्षर *anon_inodefs_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen)
अणु
	वापस dynamic_dname(dentry, buffer, buflen, "anon_inode:%s",
				dentry->d_name.name);
पूर्ण

अटल स्थिर काष्ठा dentry_operations anon_inodefs_dentry_operations = अणु
	.d_dname	= anon_inodefs_dname,
पूर्ण;

अटल पूर्णांक anon_inodefs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा pseuकरो_fs_context *ctx = init_pseuकरो(fc, ANON_INODE_FS_MAGIC);
	अगर (!ctx)
		वापस -ENOMEM;
	ctx->करोps = &anon_inodefs_dentry_operations;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type anon_inode_fs_type = अणु
	.name		= "anon_inodefs",
	.init_fs_context = anon_inodefs_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल काष्ठा inode *anon_inode_make_secure_inode(
	स्थिर अक्षर *name,
	स्थिर काष्ठा inode *context_inode)
अणु
	काष्ठा inode *inode;
	स्थिर काष्ठा qstr qname = QSTR_INIT(name, म_माप(name));
	पूर्णांक error;

	inode = alloc_anon_inode(anon_inode_mnt->mnt_sb);
	अगर (IS_ERR(inode))
		वापस inode;
	inode->i_flags &= ~S_PRIVATE;
	error =	security_inode_init_security_anon(inode, &qname, context_inode);
	अगर (error) अणु
		iput(inode);
		वापस ERR_PTR(error);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा file *__anon_inode_getfile(स्थिर अक्षर *name,
					 स्थिर काष्ठा file_operations *fops,
					 व्योम *priv, पूर्णांक flags,
					 स्थिर काष्ठा inode *context_inode,
					 bool secure)
अणु
	काष्ठा inode *inode;
	काष्ठा file *file;

	अगर (fops->owner && !try_module_get(fops->owner))
		वापस ERR_PTR(-ENOENT);

	अगर (secure) अणु
		inode =	anon_inode_make_secure_inode(name, context_inode);
		अगर (IS_ERR(inode)) अणु
			file = ERR_CAST(inode);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		inode =	anon_inode_inode;
		अगर (IS_ERR(inode)) अणु
			file = ERR_PTR(-ENODEV);
			जाओ err;
		पूर्ण
		/*
		 * We know the anon_inode inode count is always
		 * greater than zero, so ihold() is safe.
		 */
		ihold(inode);
	पूर्ण

	file = alloc_file_pseuकरो(inode, anon_inode_mnt, name,
				 flags & (O_ACCMODE | O_NONBLOCK), fops);
	अगर (IS_ERR(file))
		जाओ err_iput;

	file->f_mapping = inode->i_mapping;

	file->निजी_data = priv;

	वापस file;

err_iput:
	iput(inode);
err:
	module_put(fops->owner);
	वापस file;
पूर्ण

/**
 * anon_inode_getfile - creates a new file instance by hooking it up to an
 *                      anonymous inode, and a dentry that describe the "class"
 *                      of the file
 *
 * @name:    [in]    name of the "class" of the new file
 * @fops:    [in]    file operations क्रम the new file
 * @priv:    [in]    निजी data क्रम the new file (will be file's निजी_data)
 * @flags:   [in]    flags
 *
 * Creates a new file by hooking it on a single inode. This is useful क्रम files
 * that करो not need to have a full-fledged inode in order to operate correctly.
 * All the files created with anon_inode_getfile() will share a single inode,
 * hence saving memory and aव्योमing code duplication क्रम the file/inode/dentry
 * setup.  Returns the newly created file* or an error poपूर्णांकer.
 */
काष्ठा file *anon_inode_getfile(स्थिर अक्षर *name,
				स्थिर काष्ठा file_operations *fops,
				व्योम *priv, पूर्णांक flags)
अणु
	वापस __anon_inode_getfile(name, fops, priv, flags, शून्य, false);
पूर्ण
EXPORT_SYMBOL_GPL(anon_inode_getfile);

अटल पूर्णांक __anon_inode_getfd(स्थिर अक्षर *name,
			      स्थिर काष्ठा file_operations *fops,
			      व्योम *priv, पूर्णांक flags,
			      स्थिर काष्ठा inode *context_inode,
			      bool secure)
अणु
	पूर्णांक error, fd;
	काष्ठा file *file;

	error = get_unused_fd_flags(flags);
	अगर (error < 0)
		वापस error;
	fd = error;

	file = __anon_inode_getfile(name, fops, priv, flags, context_inode,
				    secure);
	अगर (IS_ERR(file)) अणु
		error = PTR_ERR(file);
		जाओ err_put_unused_fd;
	पूर्ण
	fd_install(fd, file);

	वापस fd;

err_put_unused_fd:
	put_unused_fd(fd);
	वापस error;
पूर्ण

/**
 * anon_inode_getfd - creates a new file instance by hooking it up to
 *                    an anonymous inode and a dentry that describe
 *                    the "class" of the file
 *
 * @name:    [in]    name of the "class" of the new file
 * @fops:    [in]    file operations क्रम the new file
 * @priv:    [in]    निजी data क्रम the new file (will be file's निजी_data)
 * @flags:   [in]    flags
 *
 * Creates a new file by hooking it on a single inode. This is
 * useful क्रम files that करो not need to have a full-fledged inode in
 * order to operate correctly.  All the files created with
 * anon_inode_getfd() will use the same singleton inode, reducing
 * memory use and aव्योमing code duplication क्रम the file/inode/dentry
 * setup.  Returns a newly created file descriptor or an error code.
 */
पूर्णांक anon_inode_getfd(स्थिर अक्षर *name, स्थिर काष्ठा file_operations *fops,
		     व्योम *priv, पूर्णांक flags)
अणु
	वापस __anon_inode_getfd(name, fops, priv, flags, शून्य, false);
पूर्ण
EXPORT_SYMBOL_GPL(anon_inode_getfd);

/**
 * anon_inode_getfd_secure - Like anon_inode_getfd(), but creates a new
 * !S_PRIVATE anon inode rather than reuse the singleton anon inode, and calls
 * the inode_init_security_anon() LSM hook. This allows the inode to have its
 * own security context and क्रम a LSM to reject creation of the inode.
 *
 * @name:    [in]    name of the "class" of the new file
 * @fops:    [in]    file operations क्रम the new file
 * @priv:    [in]    निजी data क्रम the new file (will be file's निजी_data)
 * @flags:   [in]    flags
 * @context_inode:
 *           [in]    the logical relationship with the new inode (optional)
 *
 * The LSM may use @context_inode in inode_init_security_anon(), but a
 * reference to it is not held.
 */
पूर्णांक anon_inode_getfd_secure(स्थिर अक्षर *name, स्थिर काष्ठा file_operations *fops,
			    व्योम *priv, पूर्णांक flags,
			    स्थिर काष्ठा inode *context_inode)
अणु
	वापस __anon_inode_getfd(name, fops, priv, flags, context_inode, true);
पूर्ण
EXPORT_SYMBOL_GPL(anon_inode_getfd_secure);

अटल पूर्णांक __init anon_inode_init(व्योम)
अणु
	anon_inode_mnt = kern_mount(&anon_inode_fs_type);
	अगर (IS_ERR(anon_inode_mnt))
		panic("anon_inode_init() kernel mount failed (%ld)\n", PTR_ERR(anon_inode_mnt));

	anon_inode_inode = alloc_anon_inode(anon_inode_mnt->mnt_sb);
	अगर (IS_ERR(anon_inode_inode))
		panic("anon_inode_init() inode allocation failed (%ld)\n", PTR_ERR(anon_inode_inode));

	वापस 0;
पूर्ण

fs_initcall(anon_inode_init);

