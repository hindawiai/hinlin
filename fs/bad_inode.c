<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/bad_inode.c
 *
 *  Copyright (C) 1997, Stephen Tweedie
 *
 *  Provide stub functions क्रम unपढ़ोable inodes
 *
 *  Fabian Frederick : August 2003 - All file operations asचिन्हित to EIO
 */

#समावेश <linux/fs.h>
#समावेश <linux/export.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/समय.स>
#समावेश <linux/namei.h>
#समावेश <linux/poll.h>
#समावेश <linux/fiemap.h>

अटल पूर्णांक bad_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा file_operations bad_file_ops =
अणु
	.खोलो		= bad_file_खोलो,
पूर्ण;

अटल पूर्णांक bad_inode_create(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *dir, काष्ठा dentry *dentry,
			    umode_t mode, bool excl)
अणु
	वापस -EIO;
पूर्ण

अटल काष्ठा dentry *bad_inode_lookup(काष्ठा inode *dir,
			काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस ERR_PTR(-EIO);
पूर्ण

अटल पूर्णांक bad_inode_link (काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		काष्ठा dentry *dentry)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_symlink(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *dir, काष्ठा dentry *dentry,
			     स्थिर अक्षर *symname)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, umode_t mode)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_सूची_हटाओ (काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_नाम2(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			     अचिन्हित पूर्णांक flags)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_पढ़ोlink(काष्ठा dentry *dentry, अक्षर __user *buffer,
		पूर्णांक buflen)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_permission(काष्ठा user_namespace *mnt_userns,
				काष्ठा inode *inode, पूर्णांक mask)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_getattr(काष्ठा user_namespace *mnt_userns,
			     स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			     u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_setattr(काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *direntry, काष्ठा iattr *attrs)
अणु
	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार bad_inode_listxattr(काष्ठा dentry *dentry, अक्षर *buffer,
			माप_प्रकार buffer_size)
अणु
	वापस -EIO;
पूर्ण

अटल स्थिर अक्षर *bad_inode_get_link(काष्ठा dentry *dentry,
				      काष्ठा inode *inode,
				      काष्ठा delayed_call *करोne)
अणु
	वापस ERR_PTR(-EIO);
पूर्ण

अटल काष्ठा posix_acl *bad_inode_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	वापस ERR_PTR(-EIO);
पूर्ण

अटल पूर्णांक bad_inode_fiemap(काष्ठा inode *inode,
			    काष्ठा fiemap_extent_info *fieinfo, u64 start,
			    u64 len)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *समय,
				 पूर्णांक flags)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_atomic_खोलो(काष्ठा inode *inode, काष्ठा dentry *dentry,
				 काष्ठा file *file, अचिन्हित पूर्णांक खोलो_flag,
				 umode_t create_mode)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *inode, काष्ठा dentry *dentry,
			     umode_t mode)
अणु
	वापस -EIO;
पूर्ण

अटल पूर्णांक bad_inode_set_acl(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *inode, काष्ठा posix_acl *acl,
			     पूर्णांक type)
अणु
	वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा inode_operations bad_inode_ops =
अणु
	.create		= bad_inode_create,
	.lookup		= bad_inode_lookup,
	.link		= bad_inode_link,
	.unlink		= bad_inode_unlink,
	.symlink	= bad_inode_symlink,
	.सूची_गढ़ो		= bad_inode_सूची_गढ़ो,
	.सूची_हटाओ		= bad_inode_सूची_हटाओ,
	.mknod		= bad_inode_mknod,
	.नाम		= bad_inode_नाम2,
	.पढ़ोlink	= bad_inode_पढ़ोlink,
	.permission	= bad_inode_permission,
	.getattr	= bad_inode_getattr,
	.setattr	= bad_inode_setattr,
	.listxattr	= bad_inode_listxattr,
	.get_link	= bad_inode_get_link,
	.get_acl	= bad_inode_get_acl,
	.fiemap		= bad_inode_fiemap,
	.update_समय	= bad_inode_update_समय,
	.atomic_खोलो	= bad_inode_atomic_खोलो,
	.क्षणिक_ख	= bad_inode_क्षणिक_ख,
	.set_acl	= bad_inode_set_acl,
पूर्ण;


/*
 * When a fileप्रणाली is unable to पढ़ो an inode due to an I/O error in
 * its पढ़ो_inode() function, it can call make_bad_inode() to वापस a
 * set of stubs which will वापस EIO errors as required. 
 *
 * We only need to करो limited initialisation: all other fields are
 * preinitialised to zero स्वतःmatically.
 */
 
/**
 *	make_bad_inode - mark an inode bad due to an I/O error
 *	@inode: Inode to mark bad
 *
 *	When an inode cannot be पढ़ो due to a media or remote network
 *	failure this function makes the inode "bad" and causes I/O operations
 *	on it to fail from this poपूर्णांक on.
 */
 
व्योम make_bad_inode(काष्ठा inode *inode)
अणु
	हटाओ_inode_hash(inode);

	inode->i_mode = S_IFREG;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय =
		current_समय(inode);
	inode->i_op = &bad_inode_ops;	
	inode->i_opflags &= ~IOP_XATTR;
	inode->i_fop = &bad_file_ops;	
पूर्ण
EXPORT_SYMBOL(make_bad_inode);

/*
 * This tests whether an inode has been flagged as bad. The test uses
 * &bad_inode_ops to cover the हाल of invalidated inodes as well as
 * those created by make_bad_inode() above.
 */
 
/**
 *	is_bad_inode - is an inode errored
 *	@inode: inode to test
 *
 *	Returns true अगर the inode in question has been marked as bad.
 */
 
bool is_bad_inode(काष्ठा inode *inode)
अणु
	वापस (inode->i_op == &bad_inode_ops);	
पूर्ण

EXPORT_SYMBOL(is_bad_inode);

/**
 * iget_failed - Mark an under-स्थिरruction inode as dead and release it
 * @inode: The inode to discard
 *
 * Mark an under-स्थिरruction inode as dead and release it.
 */
व्योम iget_failed(काष्ठा inode *inode)
अणु
	make_bad_inode(inode);
	unlock_new_inode(inode);
	iput(inode);
पूर्ण
EXPORT_SYMBOL(iget_failed);
