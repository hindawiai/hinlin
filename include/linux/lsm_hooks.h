<शैली गुरु>
/*
 * Linux Security Module पूर्णांकerfaces
 *
 * Copyright (C) 2001 WireX Communications, Inc <chris@wirex.com>
 * Copyright (C) 2001 Greg Kroah-Harपंचांगan <greg@kroah.com>
 * Copyright (C) 2001 Networks Associates Technology, Inc <ssmalley@nai.com>
 * Copyright (C) 2001 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (C) 2001 Silicon Graphics, Inc. (Trust Technology Group)
 * Copyright (C) 2015 Intel Corporation.
 * Copyright (C) 2015 Casey Schaufler <हालy@schaufler-ca.com>
 * Copyright (C) 2016 Mellanox Techonologies
 *
 *	This program is मुक्त software; you can redistribute it and/or modअगरy
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	Due to this file being licensed under the GPL there is controversy over
 *	whether this permits you to ग_लिखो a module that #समावेशs this file
 *	without placing your module under the GPL.  Please consult a lawyer क्रम
 *	advice beक्रमe करोing this.
 *
 */

#अगर_अघोषित __LINUX_LSM_HOOKS_H
#घोषणा __LINUX_LSM_HOOKS_H

#समावेश <linux/security.h>
#समावेश <linux/init.h>
#समावेश <linux/rculist.h>

/**
 * जोड़ security_list_options - Linux Security Module hook function list
 *
 * Security hooks क्रम program execution operations.
 *
 * @bprm_creds_क्रम_exec:
 *	If the setup in prepare_exec_creds did not setup @bprm->cred->security
 *	properly क्रम executing @bprm->file, update the LSM's portion of
 *	@bprm->cred->security to be what commit_creds needs to install क्रम the
 *	new program.  This hook may also optionally check permissions
 *	(e.g. क्रम transitions between security करोमुख्यs).
 *	The hook must set @bprm->secureexec to 1 अगर AT_SECURE should be set to
 *	request libc enable secure mode.
 *	@bprm contains the linux_binprm काष्ठाure.
 *	Return 0 अगर the hook is successful and permission is granted.
 * @bprm_creds_from_file:
 *	If @file is setpcap, suid, sgid or otherwise marked to change
 *	privilege upon exec, update @bprm->cred to reflect that change.
 *	This is called after finding the binary that will be executed.
 *	without an पूर्णांकerpreter.  This ensures that the credentials will not
 *	be derived from a script that the binary will need to reखोलो, which
 *	when reखोलोd may end up being a completely dअगरferent file.  This
 *	hook may also optionally check permissions (e.g. क्रम transitions
 *	between security करोमुख्यs).
 *	The hook must set @bprm->secureexec to 1 अगर AT_SECURE should be set to
 *	request libc enable secure mode.
 *	The hook must add to @bprm->per_clear any personality flags that
 * 	should be cleared from current->personality.
 *	@bprm contains the linux_binprm काष्ठाure.
 *	Return 0 अगर the hook is successful and permission is granted.
 * @bprm_check_security:
 *	This hook mediates the poपूर्णांक when a search क्रम a binary handler will
 *	begin.  It allows a check against the @bprm->cred->security value
 *	which was set in the preceding creds_क्रम_exec call.  The argv list and
 *	envp list are reliably available in @bprm.  This hook may be called
 *	multiple बार during a single execve.
 *	@bprm contains the linux_binprm काष्ठाure.
 *	Return 0 अगर the hook is successful and permission is granted.
 * @bprm_committing_creds:
 *	Prepare to install the new security attributes of a process being
 *	transक्रमmed by an execve operation, based on the old credentials
 *	poपूर्णांकed to by @current->cred and the inक्रमmation set in @bprm->cred by
 *	the bprm_creds_क्रम_exec hook.  @bprm poपूर्णांकs to the linux_binprm
 *	काष्ठाure.  This hook is a good place to perक्रमm state changes on the
 *	process such as closing खोलो file descriptors to which access will no
 *	दीर्घer be granted when the attributes are changed.  This is called
 *	immediately beक्रमe commit_creds().
 * @bprm_committed_creds:
 *	Tidy up after the installation of the new security attributes of a
 *	process being transक्रमmed by an execve operation.  The new credentials
 *	have, by this poपूर्णांक, been set to @current->cred.  @bprm poपूर्णांकs to the
 *	linux_binprm काष्ठाure.  This hook is a good place to perक्रमm state
 *	changes on the process such as clearing out non-inheritable संकेत
 *	state.  This is called immediately after commit_creds().
 *
 * Security hooks क्रम mount using fs_context.
 *	[See also Documentation/fileप्रणालीs/mount_api.rst]
 *
 * @fs_context_dup:
 *	Allocate and attach a security काष्ठाure to sc->security.  This poपूर्णांकer
 *	is initialised to शून्य by the caller.
 *	@fc indicates the new fileप्रणाली context.
 *	@src_fc indicates the original fileप्रणाली context.
 * @fs_context_parse_param:
 *	Userspace provided a parameter to configure a superblock.  The LSM may
 *	reject it with an error and may use it क्रम itself, in which हाल it
 *	should वापस 0; otherwise it should वापस -ENOPARAM to pass it on to
 *	the fileप्रणाली.
 *	@fc indicates the fileप्रणाली context.
 *	@param The parameter
 *
 * Security hooks क्रम fileप्रणाली operations.
 *
 * @sb_alloc_security:
 *	Allocate and attach a security काष्ठाure to the sb->s_security field.
 *	The s_security field is initialized to शून्य when the काष्ठाure is
 *	allocated.
 *	@sb contains the super_block काष्ठाure to be modअगरied.
 *	Return 0 अगर operation was successful.
 * @sb_delete:
 *	Release objects tied to a superblock (e.g. inodes).
 *	@sb contains the super_block काष्ठाure being released.
 * @sb_मुक्त_security:
 *	Deallocate and clear the sb->s_security field.
 *	@sb contains the super_block काष्ठाure to be modअगरied.
 * @sb_मुक्त_mnt_opts:
 * 	Free memory associated with @mnt_ops.
 * @sb_eat_lsm_opts:
 * 	Eat (scan @orig options) and save them in @mnt_opts.
 * @sb_statfs:
 *	Check permission beक्रमe obtaining fileप्रणाली statistics क्रम the @mnt
 *	mountpoपूर्णांक.
 *	@dentry is a handle on the superblock क्रम the fileप्रणाली.
 *	Return 0 अगर permission is granted.
 * @sb_mount:
 *	Check permission beक्रमe an object specअगरied by @dev_name is mounted on
 *	the mount poपूर्णांक named by @nd.  For an ordinary mount, @dev_name
 *	identअगरies a device अगर the file प्रणाली type requires a device.  For a
 *	remount (@flags & MS_REMOUNT), @dev_name is irrelevant.  For a
 *	loopback/bind mount (@flags & MS_BIND), @dev_name identअगरies the
 *	pathname of the object being mounted.
 *	@dev_name contains the name क्रम object being mounted.
 *	@path contains the path क्रम mount poपूर्णांक object.
 *	@type contains the fileप्रणाली type.
 *	@flags contains the mount flags.
 *	@data contains the fileप्रणाली-specअगरic data.
 *	Return 0 अगर permission is granted.
 * @sb_copy_data:
 *	Allow mount option data to be copied prior to parsing by the fileप्रणाली,
 *	so that the security module can extract security-specअगरic mount
 *	options cleanly (a fileप्रणाली may modअगरy the data e.g. with strsep()).
 *	This also allows the original mount data to be stripped of security-
 *	specअगरic options to aव्योम having to make fileप्रणालीs aware of them.
 *	@orig the original mount data copied from userspace.
 *	@copy copied data which will be passed to the security module.
 *	Returns 0 अगर the copy was successful.
 * @sb_mnt_opts_compat:
 *	Determine अगर the new mount options in @mnt_opts are allowed given
 *	the existing mounted fileप्रणाली at @sb.
 *	@sb superblock being compared
 *	@mnt_opts new mount options
 *	Return 0 अगर options are compatible.
 * @sb_remount:
 *	Extracts security प्रणाली specअगरic mount options and verअगरies no changes
 *	are being made to those options.
 *	@sb superblock being remounted
 *	@data contains the fileप्रणाली-specअगरic data.
 *	Return 0 अगर permission is granted.
 * @sb_kern_mount:
 * 	Mount this @sb अगर allowed by permissions.
 * @sb_show_options:
 * 	Show (prपूर्णांक on @m) mount options क्रम this @sb.
 * @sb_umount:
 *	Check permission beक्रमe the @mnt file प्रणाली is unmounted.
 *	@mnt contains the mounted file प्रणाली.
 *	@flags contains the unmount flags, e.g. MNT_FORCE.
 *	Return 0 अगर permission is granted.
 * @sb_pivotroot:
 *	Check permission beक्रमe pivoting the root fileप्रणाली.
 *	@old_path contains the path क्रम the new location of the
 *	current root (put_old).
 *	@new_path contains the path क्रम the new root (new_root).
 *	Return 0 अगर permission is granted.
 * @sb_set_mnt_opts:
 *	Set the security relevant mount options used क्रम a superblock
 *	@sb the superblock to set security mount options क्रम
 *	@opts binary data काष्ठाure containing all lsm mount data
 * @sb_clone_mnt_opts:
 *	Copy all security options from a given superblock to another
 *	@oldsb old superblock which contain inक्रमmation to clone
 *	@newsb new superblock which needs filled in
 * @sb_add_mnt_opt:
 * 	Add one mount @option to @mnt_opts.
 * @sb_parse_opts_str:
 *	Parse a string of security data filling in the opts काष्ठाure
 *	@options string containing all mount options known by the LSM
 *	@opts binary data काष्ठाure usable by the LSM
 * @move_mount:
 *	Check permission beक्रमe a mount is moved.
 *	@from_path indicates the mount that is going to be moved.
 *	@to_path indicates the mountpoपूर्णांक that will be mounted upon.
 * @dentry_init_security:
 *	Compute a context क्रम a dentry as the inode is not yet available
 *	since NFSv4 has no label backed by an EA anyway.
 *	@dentry dentry to use in calculating the context.
 *	@mode mode used to determine resource type.
 *	@name name of the last path component used to create file
 *	@ctx poपूर्णांकer to place the poपूर्णांकer to the resulting context in.
 *	@ctxlen poपूर्णांक to place the length of the resulting context.
 * @dentry_create_files_as:
 *	Compute a context क्रम a dentry as the inode is not yet available
 *	and set that context in passed in creds so that new files are
 *	created using that context. Context is calculated using the
 *	passed in creds and not the creds of the caller.
 *	@dentry dentry to use in calculating the context.
 *	@mode mode used to determine resource type.
 *	@name name of the last path component used to create file
 *	@old creds which should be used क्रम context calculation
 *	@new creds to modअगरy
 *
 *
 * Security hooks क्रम inode operations.
 *
 * @inode_alloc_security:
 *	Allocate and attach a security काष्ठाure to @inode->i_security.  The
 *	i_security field is initialized to शून्य when the inode काष्ठाure is
 *	allocated.
 *	@inode contains the inode काष्ठाure.
 *	Return 0 अगर operation was successful.
 * @inode_मुक्त_security:
 *	@inode contains the inode काष्ठाure.
 *	Deallocate the inode security काष्ठाure and set @inode->i_security to
 *	शून्य.
 * @inode_init_security:
 *	Obtain the security attribute name suffix and value to set on a newly
 *	created inode and set up the incore security field क्रम the new inode.
 *	This hook is called by the fs code as part of the inode creation
 *	transaction and provides क्रम atomic labeling of the inode, unlike
 *	the post_create/सूची_गढ़ो/... hooks called by the VFS.  The hook function
 *	is expected to allocate the name and value via kदो_स्मृति, with the caller
 *	being responsible क्रम calling kमुक्त after using them.
 *	If the security module करोes not use security attributes or करोes
 *	not wish to put a security attribute on this particular inode,
 *	then it should वापस -EOPNOTSUPP to skip this processing.
 *	@inode contains the inode काष्ठाure of the newly created inode.
 *	@dir contains the inode काष्ठाure of the parent directory.
 *	@qstr contains the last path component of the new object
 *	@name will be set to the allocated name suffix (e.g. selinux).
 *	@value will be set to the allocated attribute value.
 *	@len will be set to the length of the value.
 *	Returns 0 अगर @name and @value have been successfully set,
 *	-EOPNOTSUPP अगर no security attribute is needed, or
 *	-ENOMEM on memory allocation failure.
 * @inode_init_security_anon:
 *      Set up the incore security field क्रम the new anonymous inode
 *      and वापस whether the inode creation is permitted by the security
 *      module or not.
 *      @inode contains the inode काष्ठाure
 *      @name name of the anonymous inode class
 *      @context_inode optional related inode
 *	Returns 0 on success, -EACCES अगर the security module denies the
 *	creation of this inode, or another -त्रुटि_सं upon other errors.
 * @inode_create:
 *	Check permission to create a regular file.
 *	@dir contains inode काष्ठाure of the parent of the new file.
 *	@dentry contains the dentry काष्ठाure क्रम the file to be created.
 *	@mode contains the file mode of the file to be created.
 *	Return 0 अगर permission is granted.
 * @inode_link:
 *	Check permission beक्रमe creating a new hard link to a file.
 *	@old_dentry contains the dentry काष्ठाure क्रम an existing
 *	link to the file.
 *	@dir contains the inode काष्ठाure of the parent directory
 *	of the new link.
 *	@new_dentry contains the dentry काष्ठाure क्रम the new link.
 *	Return 0 अगर permission is granted.
 * @path_link:
 *	Check permission beक्रमe creating a new hard link to a file.
 *	@old_dentry contains the dentry काष्ठाure क्रम an existing link
 *	to the file.
 *	@new_dir contains the path काष्ठाure of the parent directory of
 *	the new link.
 *	@new_dentry contains the dentry काष्ठाure क्रम the new link.
 *	Return 0 अगर permission is granted.
 * @inode_unlink:
 *	Check the permission to हटाओ a hard link to a file.
 *	@dir contains the inode काष्ठाure of parent directory of the file.
 *	@dentry contains the dentry काष्ठाure क्रम file to be unlinked.
 *	Return 0 अगर permission is granted.
 * @path_unlink:
 *	Check the permission to हटाओ a hard link to a file.
 *	@dir contains the path काष्ठाure of parent directory of the file.
 *	@dentry contains the dentry काष्ठाure क्रम file to be unlinked.
 *	Return 0 अगर permission is granted.
 * @inode_symlink:
 *	Check the permission to create a symbolic link to a file.
 *	@dir contains the inode काष्ठाure of parent directory of
 *	the symbolic link.
 *	@dentry contains the dentry काष्ठाure of the symbolic link.
 *	@old_name contains the pathname of file.
 *	Return 0 अगर permission is granted.
 * @path_symlink:
 *	Check the permission to create a symbolic link to a file.
 *	@dir contains the path काष्ठाure of parent directory of
 *	the symbolic link.
 *	@dentry contains the dentry काष्ठाure of the symbolic link.
 *	@old_name contains the pathname of file.
 *	Return 0 अगर permission is granted.
 * @inode_सूची_गढ़ो:
 *	Check permissions to create a new directory in the existing directory
 *	associated with inode काष्ठाure @dir.
 *	@dir contains the inode काष्ठाure of parent of the directory
 *	to be created.
 *	@dentry contains the dentry काष्ठाure of new directory.
 *	@mode contains the mode of new directory.
 *	Return 0 अगर permission is granted.
 * @path_सूची_गढ़ो:
 *	Check permissions to create a new directory in the existing directory
 *	associated with path काष्ठाure @path.
 *	@dir contains the path काष्ठाure of parent of the directory
 *	to be created.
 *	@dentry contains the dentry काष्ठाure of new directory.
 *	@mode contains the mode of new directory.
 *	Return 0 अगर permission is granted.
 * @inode_सूची_हटाओ:
 *	Check the permission to हटाओ a directory.
 *	@dir contains the inode काष्ठाure of parent of the directory
 *	to be हटाओd.
 *	@dentry contains the dentry काष्ठाure of directory to be हटाओd.
 *	Return 0 अगर permission is granted.
 * @path_सूची_हटाओ:
 *	Check the permission to हटाओ a directory.
 *	@dir contains the path काष्ठाure of parent of the directory to be
 *	हटाओd.
 *	@dentry contains the dentry काष्ठाure of directory to be हटाओd.
 *	Return 0 अगर permission is granted.
 * @inode_mknod:
 *	Check permissions when creating a special file (or a socket or a fअगरo
 *	file created via the mknod प्रणाली call).  Note that अगर mknod operation
 *	is being करोne क्रम a regular file, then the create hook will be called
 *	and not this hook.
 *	@dir contains the inode काष्ठाure of parent of the new file.
 *	@dentry contains the dentry काष्ठाure of the new file.
 *	@mode contains the mode of the new file.
 *	@dev contains the device number.
 *	Return 0 अगर permission is granted.
 * @path_mknod:
 *	Check permissions when creating a file. Note that this hook is called
 *	even अगर mknod operation is being करोne क्रम a regular file.
 *	@dir contains the path काष्ठाure of parent of the new file.
 *	@dentry contains the dentry काष्ठाure of the new file.
 *	@mode contains the mode of the new file.
 *	@dev contains the undecoded device number. Use new_decode_dev() to get
 *	the decoded device number.
 *	Return 0 अगर permission is granted.
 * @inode_नाम:
 *	Check क्रम permission to नाम a file or directory.
 *	@old_dir contains the inode काष्ठाure क्रम parent of the old link.
 *	@old_dentry contains the dentry काष्ठाure of the old link.
 *	@new_dir contains the inode काष्ठाure क्रम parent of the new link.
 *	@new_dentry contains the dentry काष्ठाure of the new link.
 *	Return 0 अगर permission is granted.
 * @path_नाम:
 *	Check क्रम permission to नाम a file or directory.
 *	@old_dir contains the path काष्ठाure क्रम parent of the old link.
 *	@old_dentry contains the dentry काष्ठाure of the old link.
 *	@new_dir contains the path काष्ठाure क्रम parent of the new link.
 *	@new_dentry contains the dentry काष्ठाure of the new link.
 *	Return 0 अगर permission is granted.
 * @path_chmod:
 *	Check क्रम permission to change a mode of the file @path. The new
 *	mode is specअगरied in @mode.
 *	@path contains the path काष्ठाure of the file to change the mode.
 *	@mode contains the new DAC's permission, which is a biपंचांगask of
 *	स्थिरants from <include/uapi/linux/स्थिति.स>
 *	Return 0 अगर permission is granted.
 * @path_chown:
 *	Check क्रम permission to change owner/group of a file or directory.
 *	@path contains the path काष्ठाure.
 *	@uid contains new owner's ID.
 *	@gid contains new group's ID.
 *	Return 0 अगर permission is granted.
 * @path_chroot:
 *	Check क्रम permission to change root directory.
 *	@path contains the path काष्ठाure.
 *	Return 0 अगर permission is granted.
 * @path_notअगरy:
 *	Check permissions beक्रमe setting a watch on events as defined by @mask,
 *	on an object at @path, whose type is defined by @obj_type.
 * @inode_पढ़ोlink:
 *	Check the permission to पढ़ो the symbolic link.
 *	@dentry contains the dentry काष्ठाure क्रम the file link.
 *	Return 0 अगर permission is granted.
 * @inode_follow_link:
 *	Check permission to follow a symbolic link when looking up a pathname.
 *	@dentry contains the dentry काष्ठाure क्रम the link.
 *	@inode contains the inode, which itself is not stable in RCU-walk
 *	@rcu indicates whether we are in RCU-walk mode.
 *	Return 0 अगर permission is granted.
 * @inode_permission:
 *	Check permission beक्रमe accessing an inode.  This hook is called by the
 *	existing Linux permission function, so a security module can use it to
 *	provide additional checking क्रम existing Linux permission checks.
 *	Notice that this hook is called when a file is खोलोed (as well as many
 *	other operations), whereas the file_security_ops permission hook is
 *	called when the actual पढ़ो/ग_लिखो operations are perक्रमmed.
 *	@inode contains the inode काष्ठाure to check.
 *	@mask contains the permission mask.
 *	Return 0 अगर permission is granted.
 * @inode_setattr:
 *	Check permission beक्रमe setting file attributes.  Note that the kernel
 *	call to notअगरy_change is perक्रमmed from several locations, whenever
 *	file attributes change (such as when a file is truncated, chown/chmod
 *	operations, transferring disk quotas, etc).
 *	@dentry contains the dentry काष्ठाure क्रम the file.
 *	@attr is the iattr काष्ठाure containing the new file attributes.
 *	Return 0 अगर permission is granted.
 * @path_truncate:
 *	Check permission beक्रमe truncating a file.
 *	@path contains the path काष्ठाure क्रम the file.
 *	Return 0 अगर permission is granted.
 * @inode_getattr:
 *	Check permission beक्रमe obtaining file attributes.
 *	@path contains the path काष्ठाure क्रम the file.
 *	Return 0 अगर permission is granted.
 * @inode_setxattr:
 *	Check permission beक्रमe setting the extended attributes
 *	@value identअगरied by @name क्रम @dentry.
 *	Return 0 अगर permission is granted.
 * @inode_post_setxattr:
 *	Update inode security field after successful setxattr operation.
 *	@value identअगरied by @name क्रम @dentry.
 * @inode_getxattr:
 *	Check permission beक्रमe obtaining the extended attributes
 *	identअगरied by @name क्रम @dentry.
 *	Return 0 अगर permission is granted.
 * @inode_listxattr:
 *	Check permission beक्रमe obtaining the list of extended attribute
 *	names क्रम @dentry.
 *	Return 0 अगर permission is granted.
 * @inode_हटाओxattr:
 *	Check permission beक्रमe removing the extended attribute
 *	identअगरied by @name क्रम @dentry.
 *	Return 0 अगर permission is granted.
 * @inode_माला_लोecurity:
 *	Retrieve a copy of the extended attribute representation of the
 *	security label associated with @name क्रम @inode via @buffer.  Note that
 *	@name is the reमुख्यder of the attribute name after the security prefix
 *	has been हटाओd. @alloc is used to specअगरy of the call should वापस a
 *	value via the buffer or just the value length Return size of buffer on
 *	success.
 * @inode_setsecurity:
 *	Set the security label associated with @name क्रम @inode from the
 *	extended attribute value @value.  @size indicates the size of the
 *	@value in bytes.  @flags may be XATTR_CREATE, XATTR_REPLACE, or 0.
 *	Note that @name is the reमुख्यder of the attribute name after the
 *	security. prefix has been हटाओd.
 *	Return 0 on success.
 * @inode_listsecurity:
 *	Copy the extended attribute names क्रम the security labels
 *	associated with @inode पूर्णांकo @buffer.  The maximum size of @buffer
 *	is specअगरied by @buffer_size.  @buffer may be शून्य to request
 *	the size of the buffer required.
 *	Returns number of bytes used/required on success.
 * @inode_need_समाप्तpriv:
 *	Called when an inode has been changed.
 *	@dentry is the dentry being changed.
 *	Return <0 on error to पात the inode change operation.
 *	Return 0 अगर inode_समाप्तpriv करोes not need to be called.
 *	Return >0 अगर inode_समाप्तpriv करोes need to be called.
 * @inode_समाप्तpriv:
 *	The setuid bit is being हटाओd.  Remove similar security labels.
 *	Called with the dentry->d_inode->i_mutex held.
 *	@mnt_userns: user namespace of the mount
 *	@dentry is the dentry being changed.
 *	Return 0 on success.  If error is वापसed, then the operation
 *	causing setuid bit removal is failed.
 * @inode_माला_लोecid:
 *	Get the secid associated with the node.
 *	@inode contains a poपूर्णांकer to the inode.
 *	@secid contains a poपूर्णांकer to the location where result will be saved.
 *	In हाल of failure, @secid will be set to zero.
 * @inode_copy_up:
 *	A file is about to be copied up from lower layer to upper layer of
 *	overlay fileप्रणाली. Security module can prepare a set of new creds
 *	and modअगरy as need be and वापस new creds. Caller will चयन to
 *	new creds temporarily to create new file and release newly allocated
 *	creds.
 *	@src indicates the जोड़ dentry of file that is being copied up.
 *	@new poपूर्णांकer to poपूर्णांकer to वापस newly allocated creds.
 *	Returns 0 on success or a negative error code on error.
 * @inode_copy_up_xattr:
 *	Filter the xattrs being copied up when a जोड़ed file is copied
 *	up from a lower layer to the जोड़/overlay layer.
 *	@name indicates the name of the xattr.
 *	Returns 0 to accept the xattr, 1 to discard the xattr, -EOPNOTSUPP अगर
 *	security module करोes not know about attribute or a negative error code
 *	to पात the copy up. Note that the caller is responsible क्रम पढ़ोing
 *	and writing the xattrs as this hook is merely a filter.
 * @d_instantiate:
 * 	Fill in @inode security inक्रमmation क्रम a @dentry अगर allowed.
 * @getprocattr:
 * 	Read attribute @name क्रम process @p and store it पूर्णांकo @value अगर allowed.
 * @setprocattr:
 * 	Write (set) attribute @name to @value, size @size अगर allowed.
 *
 * Security hooks क्रम kernfs node operations
 *
 * @kernfs_init_security:
 *	Initialize the security context of a newly created kernfs node based
 *	on its own and its parent's attributes.
 *
 *	@kn_dir the parent kernfs node
 *	@kn the new child kernfs node
 *
 * Security hooks क्रम file operations
 *
 * @file_permission:
 *	Check file permissions beक्रमe accessing an खोलो file.  This hook is
 *	called by various operations that पढ़ो or ग_लिखो files.  A security
 *	module can use this hook to perक्रमm additional checking on these
 *	operations, e.g.  to revalidate permissions on use to support privilege
 *	bracketing or policy changes.  Notice that this hook is used when the
 *	actual पढ़ो/ग_लिखो operations are perक्रमmed, whereas the
 *	inode_security_ops hook is called when a file is खोलोed (as well as
 *	many other operations).
 *	Caveat:  Although this hook can be used to revalidate permissions क्रम
 *	various प्रणाली call operations that पढ़ो or ग_लिखो files, it करोes not
 *	address the revalidation of permissions क्रम memory-mapped files.
 *	Security modules must handle this separately अगर they need such
 *	revalidation.
 *	@file contains the file काष्ठाure being accessed.
 *	@mask contains the requested permissions.
 *	Return 0 अगर permission is granted.
 * @file_alloc_security:
 *	Allocate and attach a security काष्ठाure to the file->f_security field.
 *	The security field is initialized to शून्य when the काष्ठाure is first
 *	created.
 *	@file contains the file काष्ठाure to secure.
 *	Return 0 अगर the hook is successful and permission is granted.
 * @file_मुक्त_security:
 *	Deallocate and मुक्त any security काष्ठाures stored in file->f_security.
 *	@file contains the file काष्ठाure being modअगरied.
 * @file_ioctl:
 *	@file contains the file काष्ठाure.
 *	@cmd contains the operation to perक्रमm.
 *	@arg contains the operational arguments.
 *	Check permission क्रम an ioctl operation on @file.  Note that @arg
 *	someबार represents a user space poपूर्णांकer; in other हालs, it may be a
 *	simple पूर्णांकeger value.  When @arg represents a user space poपूर्णांकer, it
 *	should never be used by the security module.
 *	Return 0 अगर permission is granted.
 * @mmap_addr :
 *	Check permissions क्रम a mmap operation at @addr.
 *	@addr contains भव address that will be used क्रम the operation.
 *	Return 0 अगर permission is granted.
 * @mmap_file :
 *	Check permissions क्रम a mmap operation.  The @file may be शून्य, e.g.
 *	अगर mapping anonymous memory.
 *	@file contains the file काष्ठाure क्रम file to map (may be शून्य).
 *	@reqprot contains the protection requested by the application.
 *	@prot contains the protection that will be applied by the kernel.
 *	@flags contains the operational flags.
 *	Return 0 अगर permission is granted.
 * @file_mprotect:
 *	Check permissions beक्रमe changing memory access permissions.
 *	@vma contains the memory region to modअगरy.
 *	@reqprot contains the protection requested by the application.
 *	@prot contains the protection that will be applied by the kernel.
 *	Return 0 अगर permission is granted.
 * @file_lock:
 *	Check permission beक्रमe perक्रमming file locking operations.
 *	Note the hook mediates both flock and fcntl style locks.
 *	@file contains the file काष्ठाure.
 *	@cmd contains the posix-translated lock operation to perक्रमm
 *	(e.g. F_RDLCK, F_WRLCK).
 *	Return 0 अगर permission is granted.
 * @file_fcntl:
 *	Check permission beक्रमe allowing the file operation specअगरied by @cmd
 *	from being perक्रमmed on the file @file.  Note that @arg someबार
 *	represents a user space poपूर्णांकer; in other हालs, it may be a simple
 *	पूर्णांकeger value.  When @arg represents a user space poपूर्णांकer, it should
 *	never be used by the security module.
 *	@file contains the file काष्ठाure.
 *	@cmd contains the operation to be perक्रमmed.
 *	@arg contains the operational arguments.
 *	Return 0 अगर permission is granted.
 * @file_set_fowner:
 *	Save owner security inक्रमmation (typically from current->security) in
 *	file->f_security क्रम later use by the send_sigiotask hook.
 *	@file contains the file काष्ठाure to update.
 *	Return 0 on success.
 * @file_send_sigiotask:
 *	Check permission क्रम the file owner @fown to send SIGIO or SIGURG to the
 *	process @tsk.  Note that this hook is someबार called from पूर्णांकerrupt.
 *	Note that the fown_काष्ठा, @fown, is never outside the context of a
 *	काष्ठा file, so the file काष्ठाure (and associated security inक्रमmation)
 *	can always be obtained: container_of(fown, काष्ठा file, f_owner)
 *	@tsk contains the काष्ठाure of task receiving संकेत.
 *	@fown contains the file owner inक्रमmation.
 *	@sig is the संकेत that will be sent.  When 0, kernel sends SIGIO.
 *	Return 0 अगर permission is granted.
 * @file_receive:
 *	This hook allows security modules to control the ability of a process
 *	to receive an खोलो file descriptor via socket IPC.
 *	@file contains the file काष्ठाure being received.
 *	Return 0 अगर permission is granted.
 * @file_खोलो:
 *	Save खोलो-समय permission checking state क्रम later use upon
 *	file_permission, and recheck access अगर anything has changed
 *	since inode_permission.
 *
 * Security hooks क्रम task operations.
 *
 * @task_alloc:
 *	@task task being allocated.
 *	@clone_flags contains the flags indicating what should be shared.
 *	Handle allocation of task-related resources.
 *	Returns a zero on success, negative values on failure.
 * @task_मुक्त:
 *	@task task about to be मुक्तd.
 *	Handle release of task-related resources. (Note that this can be called
 *	from पूर्णांकerrupt context.)
 * @cred_alloc_blank:
 *	@cred poपूर्णांकs to the credentials.
 *	@gfp indicates the atomicity of any memory allocations.
 *	Only allocate sufficient memory and attach to @cred such that
 *	cred_transfer() will not get ENOMEM.
 * @cred_मुक्त:
 *	@cred poपूर्णांकs to the credentials.
 *	Deallocate and clear the cred->security field in a set of credentials.
 * @cred_prepare:
 *	@new poपूर्णांकs to the new credentials.
 *	@old poपूर्णांकs to the original credentials.
 *	@gfp indicates the atomicity of any memory allocations.
 *	Prepare a new set of credentials by copying the data from the old set.
 * @cred_transfer:
 *	@new poपूर्णांकs to the new credentials.
 *	@old poपूर्णांकs to the original credentials.
 *	Transfer data from original creds to new creds
 * @cred_माला_लोecid:
 *	Retrieve the security identअगरier of the cred काष्ठाure @c
 *	@c contains the credentials, secid will be placed पूर्णांकo @secid.
 *	In हाल of failure, @secid will be set to zero.
 * @kernel_act_as:
 *	Set the credentials क्रम a kernel service to act as (subjective context).
 *	@new poपूर्णांकs to the credentials to be modअगरied.
 *	@secid specअगरies the security ID to be set
 *	The current task must be the one that nominated @secid.
 *	Return 0 अगर successful.
 * @kernel_create_files_as:
 *	Set the file creation context in a set of credentials to be the same as
 *	the objective context of the specअगरied inode.
 *	@new poपूर्णांकs to the credentials to be modअगरied.
 *	@inode poपूर्णांकs to the inode to use as a reference.
 *	The current task must be the one that nominated @inode.
 *	Return 0 अगर successful.
 * @kernel_module_request:
 *	Ability to trigger the kernel to स्वतःmatically upcall to userspace क्रम
 *	userspace to load a kernel module with the given name.
 *	@kmod_name name of the module requested by the kernel
 *	Return 0 अगर successful.
 * @kernel_load_data:
 *	Load data provided by userspace.
 *	@id kernel load data identअगरier
 *	@contents अगर a subsequent @kernel_post_load_data will be called.
 *	Return 0 अगर permission is granted.
 * @kernel_post_load_data:
 *	Load data provided by a non-file source (usually userspace buffer).
 *	@buf poपूर्णांकer to buffer containing the data contents.
 *	@size length of the data contents.
 *	@id kernel load data identअगरier
 *	@description a text description of what was loaded, @id-specअगरic
 *	Return 0 अगर permission is granted.
 *	This must be paired with a prior @kernel_load_data call that had
 *	@contents set to true.
 * @kernel_पढ़ो_file:
 *	Read a file specअगरied by userspace.
 *	@file contains the file काष्ठाure poपूर्णांकing to the file being पढ़ो
 *	by the kernel.
 *	@id kernel पढ़ो file identअगरier
 *	@contents अगर a subsequent @kernel_post_पढ़ो_file will be called.
 *	Return 0 अगर permission is granted.
 * @kernel_post_पढ़ो_file:
 *	Read a file specअगरied by userspace.
 *	@file contains the file काष्ठाure poपूर्णांकing to the file being पढ़ो
 *	by the kernel.
 *	@buf poपूर्णांकer to buffer containing the file contents.
 *	@size length of the file contents.
 *	@id kernel पढ़ो file identअगरier
 *	This must be paired with a prior @kernel_पढ़ो_file call that had
 *	@contents set to true.
 *	Return 0 अगर permission is granted.
 * @task_fix_setuid:
 *	Update the module's state after setting one or more of the user
 *	identity attributes of the current process.  The @flags parameter
 *	indicates which of the set*uid प्रणाली calls invoked this hook.  If
 *	@new is the set of credentials that will be installed.  Modअगरications
 *	should be made to this rather than to @current->cred.
 *	@old is the set of credentials that are being replaces
 *	@flags contains one of the LSM_SETID_* values.
 *	Return 0 on success.
 * @task_fix_setgid:
 *	Update the module's state after setting one or more of the group
 *	identity attributes of the current process.  The @flags parameter
 *	indicates which of the set*gid प्रणाली calls invoked this hook.
 *	@new is the set of credentials that will be installed.  Modअगरications
 *	should be made to this rather than to @current->cred.
 *	@old is the set of credentials that are being replaced.
 *	@flags contains one of the LSM_SETID_* values.
 *	Return 0 on success.
 * @task_setpgid:
 *	Check permission beक्रमe setting the process group identअगरier of the
 *	process @p to @pgid.
 *	@p contains the task_काष्ठा क्रम process being modअगरied.
 *	@pgid contains the new pgid.
 *	Return 0 अगर permission is granted.
 * @task_getpgid:
 *	Check permission beक्रमe getting the process group identअगरier of the
 *	process @p.
 *	@p contains the task_काष्ठा क्रम the process.
 *	Return 0 अगर permission is granted.
 * @task_माला_लोid:
 *	Check permission beक्रमe getting the session identअगरier of the process
 *	@p.
 *	@p contains the task_काष्ठा क्रम the process.
 *	Return 0 अगर permission is granted.
 * @task_माला_लोecid_subj:
 *	Retrieve the subjective security identअगरier of the task_काष्ठा in @p
 *	and वापस it in @secid.  Special care must be taken to ensure that @p
 *	is the either the "current" task, or the caller has exclusive access
 *	to @p.
 *	In हाल of failure, @secid will be set to zero.
 * @task_माला_लोecid_obj:
 *	Retrieve the objective security identअगरier of the task_काष्ठा in @p
 *	and वापस it in @secid.
 *	In हाल of failure, @secid will be set to zero.
 *
 * @task_setnice:
 *	Check permission beक्रमe setting the nice value of @p to @nice.
 *	@p contains the task_काष्ठा of process.
 *	@nice contains the new nice value.
 *	Return 0 अगर permission is granted.
 * @task_setioprio:
 *	Check permission beक्रमe setting the ioprio value of @p to @ioprio.
 *	@p contains the task_काष्ठा of process.
 *	@ioprio contains the new ioprio value
 *	Return 0 अगर permission is granted.
 * @task_getioprio:
 *	Check permission beक्रमe getting the ioprio value of @p.
 *	@p contains the task_काष्ठा of process.
 *	Return 0 अगर permission is granted.
 * @task_prlimit:
 *	Check permission beक्रमe getting and/or setting the resource limits of
 *	another task.
 *	@cred poपूर्णांकs to the cred काष्ठाure क्रम the current task.
 *	@tcred poपूर्णांकs to the cred काष्ठाure क्रम the target task.
 *	@flags contains the LSM_PRLIMIT_* flag bits indicating whether the
 *	resource limits are being पढ़ो, modअगरied, or both.
 *	Return 0 अगर permission is granted.
 * @task_setrlimit:
 *	Check permission beक्रमe setting the resource limits of process @p
 *	क्रम @resource to @new_rlim.  The old resource limit values can
 *	be examined by dereferencing (p->संकेत->rlim + resource).
 *	@p poपूर्णांकs to the task_काष्ठा क्रम the target task's group leader.
 *	@resource contains the resource whose limit is being set.
 *	@new_rlim contains the new limits क्रम @resource.
 *	Return 0 अगर permission is granted.
 * @task_setscheduler:
 *	Check permission beक्रमe setting scheduling policy and/or parameters of
 *	process @p.
 *	@p contains the task_काष्ठा क्रम process.
 *	Return 0 अगर permission is granted.
 * @task_माला_लोcheduler:
 *	Check permission beक्रमe obtaining scheduling inक्रमmation क्रम process
 *	@p.
 *	@p contains the task_काष्ठा क्रम process.
 *	Return 0 अगर permission is granted.
 * @task_movememory:
 *	Check permission beक्रमe moving memory owned by process @p.
 *	@p contains the task_काष्ठा क्रम process.
 *	Return 0 अगर permission is granted.
 * @task_समाप्त:
 *	Check permission beक्रमe sending संकेत @sig to @p.  @info can be शून्य,
 *	the स्थिरant 1, or a poपूर्णांकer to a kernel_siginfo काष्ठाure.  If @info is 1 or
 *	SI_FROMKERNEL(info) is true, then the संकेत should be viewed as coming
 *	from the kernel and should typically be permitted.
 *	SIGIO संकेतs are handled separately by the send_sigiotask hook in
 *	file_security_ops.
 *	@p contains the task_काष्ठा क्रम process.
 *	@info contains the संकेत inक्रमmation.
 *	@sig contains the संकेत value.
 *	@cred contains the cred of the process where the संकेत originated, or
 *	शून्य अगर the current task is the originator.
 *	Return 0 अगर permission is granted.
 * @task_prctl:
 *	Check permission beक्रमe perक्रमming a process control operation on the
 *	current process.
 *	@option contains the operation.
 *	@arg2 contains a argument.
 *	@arg3 contains a argument.
 *	@arg4 contains a argument.
 *	@arg5 contains a argument.
 *	Return -ENOSYS अगर no-one wanted to handle this op, any other value to
 *	cause prctl() to वापस immediately with that value.
 * @task_to_inode:
 *	Set the security attributes क्रम an inode based on an associated task's
 *	security attributes, e.g. क्रम /proc/pid inodes.
 *	@p contains the task_काष्ठा क्रम the task.
 *	@inode contains the inode काष्ठाure क्रम the inode.
 *
 * Security hooks क्रम Netlink messaging.
 *
 * @netlink_send:
 *	Save security inक्रमmation क्रम a netlink message so that permission
 *	checking can be perक्रमmed when the message is processed.  The security
 *	inक्रमmation can be saved using the eff_cap field of the
 *	netlink_skb_parms काष्ठाure.  Also may be used to provide fine
 *	grained control over message transmission.
 *	@sk associated sock of task sending the message.
 *	@skb contains the sk_buff काष्ठाure क्रम the netlink message.
 *	Return 0 अगर the inक्रमmation was successfully saved and message
 *	is allowed to be transmitted.
 *
 * Security hooks क्रम Unix करोमुख्य networking.
 *
 * @unix_stream_connect:
 *	Check permissions beक्रमe establishing a Unix करोमुख्य stream connection
 *	between @sock and @other.
 *	@sock contains the sock काष्ठाure.
 *	@other contains the peer sock काष्ठाure.
 *	@newsk contains the new sock काष्ठाure.
 *	Return 0 अगर permission is granted.
 * @unix_may_send:
 *	Check permissions beक्रमe connecting or sending datagrams from @sock to
 *	@other.
 *	@sock contains the socket काष्ठाure.
 *	@other contains the peer socket काष्ठाure.
 *	Return 0 अगर permission is granted.
 *
 * The @unix_stream_connect and @unix_may_send hooks were necessary because
 * Linux provides an alternative to the conventional file name space क्रम Unix
 * करोमुख्य sockets.  Whereas binding and connecting to sockets in the file name
 * space is mediated by the typical file permissions (and caught by the mknod
 * and permission hooks in inode_security_ops), binding and connecting to
 * sockets in the असलtract name space is completely unmediated.  Sufficient
 * control of Unix करोमुख्य sockets in the असलtract name space isn't possible
 * using only the socket layer hooks, since we need to know the actual target
 * socket, which is not looked up until we are inside the af_unix code.
 *
 * Security hooks क्रम socket operations.
 *
 * @socket_create:
 *	Check permissions prior to creating a new socket.
 *	@family contains the requested protocol family.
 *	@type contains the requested communications type.
 *	@protocol contains the requested protocol.
 *	@kern set to 1 अगर a kernel socket.
 *	Return 0 अगर permission is granted.
 * @socket_post_create:
 *	This hook allows a module to update or allocate a per-socket security
 *	काष्ठाure. Note that the security field was not added directly to the
 *	socket काष्ठाure, but rather, the socket security inक्रमmation is stored
 *	in the associated inode.  Typically, the inode alloc_security hook will
 *	allocate and attach security inक्रमmation to
 *	SOCK_INODE(sock)->i_security.  This hook may be used to update the
 *	SOCK_INODE(sock)->i_security field with additional inक्रमmation that
 *	wasn't available when the inode was allocated.
 *	@sock contains the newly created socket काष्ठाure.
 *	@family contains the requested protocol family.
 *	@type contains the requested communications type.
 *	@protocol contains the requested protocol.
 *	@kern set to 1 अगर a kernel socket.
 * @socket_socketpair:
 *	Check permissions beक्रमe creating a fresh pair of sockets.
 *	@socka contains the first socket काष्ठाure.
 *	@sockb contains the second socket काष्ठाure.
 *	Return 0 अगर permission is granted and the connection was established.
 * @socket_bind:
 *	Check permission beक्रमe socket protocol layer bind operation is
 *	perक्रमmed and the socket @sock is bound to the address specअगरied in the
 *	@address parameter.
 *	@sock contains the socket काष्ठाure.
 *	@address contains the address to bind to.
 *	@addrlen contains the length of address.
 *	Return 0 अगर permission is granted.
 * @socket_connect:
 *	Check permission beक्रमe socket protocol layer connect operation
 *	attempts to connect socket @sock to a remote address, @address.
 *	@sock contains the socket काष्ठाure.
 *	@address contains the address of remote endpoपूर्णांक.
 *	@addrlen contains the length of address.
 *	Return 0 अगर permission is granted.
 * @socket_listen:
 *	Check permission beक्रमe socket protocol layer listen operation.
 *	@sock contains the socket काष्ठाure.
 *	@backlog contains the maximum length क्रम the pending connection queue.
 *	Return 0 अगर permission is granted.
 * @socket_accept:
 *	Check permission beक्रमe accepting a new connection.  Note that the new
 *	socket, @newsock, has been created and some inक्रमmation copied to it,
 *	but the accept operation has not actually been perक्रमmed.
 *	@sock contains the listening socket काष्ठाure.
 *	@newsock contains the newly created server socket क्रम connection.
 *	Return 0 अगर permission is granted.
 * @socket_sendmsg:
 *	Check permission beक्रमe transmitting a message to another socket.
 *	@sock contains the socket काष्ठाure.
 *	@msg contains the message to be transmitted.
 *	@size contains the size of message.
 *	Return 0 अगर permission is granted.
 * @socket_recvmsg:
 *	Check permission beक्रमe receiving a message from a socket.
 *	@sock contains the socket काष्ठाure.
 *	@msg contains the message काष्ठाure.
 *	@size contains the size of message काष्ठाure.
 *	@flags contains the operational flags.
 *	Return 0 अगर permission is granted.
 * @socket_माला_लोockname:
 *	Check permission beक्रमe the local address (name) of the socket object
 *	@sock is retrieved.
 *	@sock contains the socket काष्ठाure.
 *	Return 0 अगर permission is granted.
 * @socket_getpeername:
 *	Check permission beक्रमe the remote address (name) of a socket object
 *	@sock is retrieved.
 *	@sock contains the socket काष्ठाure.
 *	Return 0 अगर permission is granted.
 * @socket_माला_लोockopt:
 *	Check permissions beक्रमe retrieving the options associated with socket
 *	@sock.
 *	@sock contains the socket काष्ठाure.
 *	@level contains the protocol level to retrieve option from.
 *	@optname contains the name of option to retrieve.
 *	Return 0 अगर permission is granted.
 * @socket_setsockopt:
 *	Check permissions beक्रमe setting the options associated with socket
 *	@sock.
 *	@sock contains the socket काष्ठाure.
 *	@level contains the protocol level to set options क्रम.
 *	@optname contains the name of the option to set.
 *	Return 0 अगर permission is granted.
 * @socket_shutकरोwn:
 *	Checks permission beक्रमe all or part of a connection on the socket
 *	@sock is shut करोwn.
 *	@sock contains the socket काष्ठाure.
 *	@how contains the flag indicating how future sends and receives
 *	are handled.
 *	Return 0 अगर permission is granted.
 * @socket_sock_rcv_skb:
 *	Check permissions on incoming network packets.  This hook is distinct
 *	from Netfilter's IP input hooks since it is the first समय that the
 *	incoming sk_buff @skb has been associated with a particular socket, @sk.
 *	Must not sleep inside this hook because some callers hold spinlocks.
 *	@sk contains the sock (not socket) associated with the incoming sk_buff.
 *	@skb contains the incoming network data.
 * @socket_getpeersec_stream:
 *	This hook allows the security module to provide peer socket security
 *	state क्रम unix or connected tcp sockets to userspace via माला_लोockopt
 *	SO_GETPEERSEC.  For tcp sockets this can be meaningful अगर the
 *	socket is associated with an ipsec SA.
 *	@sock is the local socket.
 *	@optval userspace memory where the security state is to be copied.
 *	@optlen userspace पूर्णांक where the module should copy the actual length
 *	of the security state.
 *	@len as input is the maximum length to copy to userspace provided
 *	by the caller.
 *	Return 0 अगर all is well, otherwise, typical माला_लोockopt वापस
 *	values.
 * @socket_getpeersec_dgram:
 *	This hook allows the security module to provide peer socket security
 *	state क्रम udp sockets on a per-packet basis to userspace via
 *	माला_लोockopt SO_GETPEERSEC. The application must first have indicated
 *	the IP_PASSSEC option via माला_लोockopt. It can then retrieve the
 *	security state वापसed by this hook क्रम a packet via the SCM_SECURITY
 *	ancillary message type.
 *	@sock contains the peer socket. May be शून्य.
 *	@skb is the sk_buff क्रम the packet being queried. May be शून्य.
 *	@secid poपूर्णांकer to store the secid of the packet.
 *	Return 0 on success, error on failure.
 * @sk_alloc_security:
 *	Allocate and attach a security काष्ठाure to the sk->sk_security field,
 *	which is used to copy security attributes between local stream sockets.
 * @sk_मुक्त_security:
 *	Deallocate security काष्ठाure.
 * @sk_clone_security:
 *	Clone/copy security काष्ठाure.
 * @sk_माला_लोecid:
 *	Retrieve the LSM-specअगरic secid क्रम the sock to enable caching
 *	of network authorizations.
 * @sock_graft:
 *	Sets the socket's isec sid to the sock's sid.
 * @inet_conn_request:
 *	Sets the खोलोreq's sid to socket's sid with MLS portion taken
 *	from peer sid.
 * @inet_csk_clone:
 *	Sets the new child socket's sid to the खोलोreq sid.
 * @inet_conn_established:
 *	Sets the connection's peersid to the secmark on skb.
 * @secmark_relabel_packet:
 *	check अगर the process should be allowed to relabel packets to
 *	the given secid
 * @secmark_refcount_inc:
 *	tells the LSM to increment the number of secmark labeling rules loaded
 * @secmark_refcount_dec:
 *	tells the LSM to decrement the number of secmark labeling rules loaded
 * @req_classअगरy_flow:
 *	Sets the flow's sid to the खोलोreq sid.
 * @tun_dev_alloc_security:
 *	This hook allows a module to allocate a security काष्ठाure क्रम a TUN
 *	device.
 *	@security poपूर्णांकer to a security काष्ठाure poपूर्णांकer.
 *	Returns a zero on success, negative values on failure.
 * @tun_dev_मुक्त_security:
 *	This hook allows a module to मुक्त the security काष्ठाure क्रम a TUN
 *	device.
 *	@security poपूर्णांकer to the TUN device's security काष्ठाure
 * @tun_dev_create:
 *	Check permissions prior to creating a new TUN device.
 * @tun_dev_attach_queue:
 *	Check permissions prior to attaching to a TUN device queue.
 *	@security poपूर्णांकer to the TUN device's security काष्ठाure.
 * @tun_dev_attach:
 *	This hook can be used by the module to update any security state
 *	associated with the TUN device's sock काष्ठाure.
 *	@sk contains the existing sock काष्ठाure.
 *	@security poपूर्णांकer to the TUN device's security काष्ठाure.
 * @tun_dev_खोलो:
 *	This hook can be used by the module to update any security state
 *	associated with the TUN device's security काष्ठाure.
 *	@security poपूर्णांकer to the TUN devices's security काष्ठाure.
 *
 * Security hooks क्रम SCTP
 *
 * @sctp_assoc_request:
 *	Passes the @ep and @chunk->skb of the association INIT packet to
 *	the security module.
 *	@ep poपूर्णांकer to sctp endpoपूर्णांक काष्ठाure.
 *	@skb poपूर्णांकer to skbuff of association packet.
 *	Return 0 on success, error on failure.
 * @sctp_bind_connect:
 *	Validiate permissions required क्रम each address associated with sock
 *	@sk. Depending on @optname, the addresses will be treated as either
 *	क्रम a connect or bind service. The @addrlen is calculated on each
 *	ipv4 and ipv6 address using माप(काष्ठा sockaddr_in) or
 *	माप(काष्ठा sockaddr_in6).
 *	@sk poपूर्णांकer to sock काष्ठाure.
 *	@optname name of the option to validate.
 *	@address list containing one or more ipv4/ipv6 addresses.
 *	@addrlen total length of address(s).
 *	Return 0 on success, error on failure.
 * @sctp_sk_clone:
 *	Called whenever a new socket is created by accept(2) (i.e. a TCP
 *	style socket) or when a socket is 'peeled off' e.g userspace
 *	calls sctp_peeloff(3).
 *	@ep poपूर्णांकer to current sctp endpoपूर्णांक काष्ठाure.
 *	@sk poपूर्णांकer to current sock काष्ठाure.
 *	@sk poपूर्णांकer to new sock काष्ठाure.
 *
 * Security hooks क्रम Infiniband
 *
 * @ib_pkey_access:
 *	Check permission to access a pkey when modअगरing a QP.
 *	@subnet_prefix the subnet prefix of the port being used.
 *	@pkey the pkey to be accessed.
 *	@sec poपूर्णांकer to a security काष्ठाure.
 * @ib_endport_manage_subnet:
 *	Check permissions to send and receive SMPs on a end port.
 *	@dev_name the IB device name (i.e. mlx4_0).
 *	@port_num the port number.
 *	@sec poपूर्णांकer to a security काष्ठाure.
 * @ib_alloc_security:
 *	Allocate a security काष्ठाure क्रम Infiniband objects.
 *	@sec poपूर्णांकer to a security काष्ठाure poपूर्णांकer.
 *	Returns 0 on success, non-zero on failure
 * @ib_मुक्त_security:
 *	Deallocate an Infiniband security काष्ठाure.
 *	@sec contains the security काष्ठाure to be मुक्तd.
 *
 * Security hooks क्रम XFRM operations.
 *
 * @xfrm_policy_alloc_security:
 *	@ctxp is a poपूर्णांकer to the xfrm_sec_ctx being added to Security Policy
 *	Database used by the XFRM प्रणाली.
 *	@sec_ctx contains the security context inक्रमmation being provided by
 *	the user-level policy update program (e.g., setkey).
 *	Allocate a security काष्ठाure to the xp->security field; the security
 *	field is initialized to शून्य when the xfrm_policy is allocated.
 *	Return 0 अगर operation was successful (memory to allocate, legal context)
 *	@gfp is to specअगरy the context क्रम the allocation
 * @xfrm_policy_clone_security:
 *	@old_ctx contains an existing xfrm_sec_ctx.
 *	@new_ctxp contains a new xfrm_sec_ctx being cloned from old.
 *	Allocate a security काष्ठाure in new_ctxp that contains the
 *	inक्रमmation from the old_ctx काष्ठाure.
 *	Return 0 अगर operation was successful (memory to allocate).
 * @xfrm_policy_मुक्त_security:
 *	@ctx contains the xfrm_sec_ctx
 *	Deallocate xp->security.
 * @xfrm_policy_delete_security:
 *	@ctx contains the xfrm_sec_ctx.
 *	Authorize deletion of xp->security.
 * @xfrm_state_alloc:
 *	@x contains the xfrm_state being added to the Security Association
 *	Database by the XFRM प्रणाली.
 *	@sec_ctx contains the security context inक्रमmation being provided by
 *	the user-level SA generation program (e.g., setkey or racoon).
 *	Allocate a security काष्ठाure to the x->security field; the security
 *	field is initialized to शून्य when the xfrm_state is allocated. Set the
 *	context to correspond to sec_ctx. Return 0 अगर operation was successful
 *	(memory to allocate, legal context).
 * @xfrm_state_alloc_acquire:
 *	@x contains the xfrm_state being added to the Security Association
 *	Database by the XFRM प्रणाली.
 *	@polsec contains the policy's security context.
 *	@secid contains the secid from which to take the mls portion of the
 *	context.
 *	Allocate a security काष्ठाure to the x->security field; the security
 *	field is initialized to शून्य when the xfrm_state is allocated. Set the
 *	context to correspond to secid. Return 0 अगर operation was successful
 *	(memory to allocate, legal context).
 * @xfrm_state_मुक्त_security:
 *	@x contains the xfrm_state.
 *	Deallocate x->security.
 * @xfrm_state_delete_security:
 *	@x contains the xfrm_state.
 *	Authorize deletion of x->security.
 * @xfrm_policy_lookup:
 *	@ctx contains the xfrm_sec_ctx क्रम which the access control is being
 *	checked.
 *	@fl_secid contains the flow security label that is used to authorize
 *	access to the policy xp.
 *	@dir contains the direction of the flow (input or output).
 *	Check permission when a flow selects a xfrm_policy क्रम processing
 *	XFRMs on a packet.  The hook is called when selecting either a
 *	per-socket policy or a generic xfrm policy.
 *	Return 0 अगर permission is granted, -ESRCH otherwise, or -त्रुटि_सं
 *	on other errors.
 * @xfrm_state_pol_flow_match:
 *	@x contains the state to match.
 *	@xp contains the policy to check क्रम a match.
 *	@flic contains the flowi_common काष्ठा to check क्रम a match.
 *	Return 1 अगर there is a match.
 * @xfrm_decode_session:
 *	@skb poपूर्णांकs to skb to decode.
 *	@secid poपूर्णांकs to the flow key secid to set.
 *	@ckall says अगर all xfrms used should be checked क्रम same secid.
 *	Return 0 अगर ckall is zero or all xfrms used have the same secid.
 *
 * Security hooks affecting all Key Management operations
 *
 * @key_alloc:
 *	Permit allocation of a key and assign security data. Note that key करोes
 *	not have a serial number asचिन्हित at this poपूर्णांक.
 *	@key poपूर्णांकs to the key.
 *	@flags is the allocation flags
 *	Return 0 अगर permission is granted, -ve error otherwise.
 * @key_मुक्त:
 *	Notअगरication of deकाष्ठाion; मुक्त security data.
 *	@key poपूर्णांकs to the key.
 *	No वापस value.
 * @key_permission:
 *	See whether a specअगरic operational right is granted to a process on a
 *	key.
 *	@key_ref refers to the key (key poपूर्णांकer + possession attribute bit).
 *	@cred poपूर्णांकs to the credentials to provide the context against which to
 *	evaluate the security data on the key.
 *	@perm describes the combination of permissions required of this key.
 *	Return 0 अगर permission is granted, -ve error otherwise.
 * @key_माला_लोecurity:
 *	Get a textual representation of the security context attached to a key
 *	क्रम the purposes of honouring KEYCTL_GETSECURITY.  This function
 *	allocates the storage क्रम the NUL-terminated string and the caller
 *	should मुक्त it.
 *	@key poपूर्णांकs to the key to be queried.
 *	@_buffer poपूर्णांकs to a poपूर्णांकer that should be set to poपूर्णांक to the
 *	resulting string (अगर no label or an error occurs).
 *	Return the length of the string (including terminating NUL) or -ve अगर
 *	an error.
 *	May also वापस 0 (and a शून्य buffer poपूर्णांकer) अगर there is no label.
 *
 * Security hooks affecting all System V IPC operations.
 *
 * @ipc_permission:
 *	Check permissions क्रम access to IPC
 *	@ipcp contains the kernel IPC permission काष्ठाure
 *	@flag contains the desired (requested) permission set
 *	Return 0 अगर permission is granted.
 * @ipc_माला_लोecid:
 *	Get the secid associated with the ipc object.
 *	@ipcp contains the kernel IPC permission काष्ठाure.
 *	@secid contains a poपूर्णांकer to the location where result will be saved.
 *	In हाल of failure, @secid will be set to zero.
 *
 * Security hooks क्रम inभागidual messages held in System V IPC message queues
 *
 * @msg_msg_alloc_security:
 *	Allocate and attach a security काष्ठाure to the msg->security field.
 *	The security field is initialized to शून्य when the काष्ठाure is first
 *	created.
 *	@msg contains the message काष्ठाure to be modअगरied.
 *	Return 0 अगर operation was successful and permission is granted.
 * @msg_msg_मुक्त_security:
 *	Deallocate the security काष्ठाure क्रम this message.
 *	@msg contains the message काष्ठाure to be modअगरied.
 *
 * Security hooks क्रम System V IPC Message Queues
 *
 * @msg_queue_alloc_security:
 *	Allocate and attach a security काष्ठाure to the
 *	@perm->security field. The security field is initialized to
 *	शून्य when the काष्ठाure is first created.
 *	@perm contains the IPC permissions of the message queue.
 *	Return 0 अगर operation was successful and permission is granted.
 * @msg_queue_मुक्त_security:
 *	Deallocate security field @perm->security क्रम the message queue.
 *	@perm contains the IPC permissions of the message queue.
 * @msg_queue_associate:
 *	Check permission when a message queue is requested through the
 *	msgget प्रणाली call. This hook is only called when वापसing the
 *	message queue identअगरier क्रम an existing message queue, not when a
 *	new message queue is created.
 *	@perm contains the IPC permissions of the message queue.
 *	@msqflg contains the operation control flags.
 *	Return 0 अगर permission is granted.
 * @msg_queue_msgctl:
 *	Check permission when a message control operation specअगरied by @cmd
 *	is to be perक्रमmed on the message queue with permissions @perm.
 *	The @perm may be शून्य, e.g. क्रम IPC_INFO or MSG_INFO.
 *	@perm contains the IPC permissions of the msg queue. May be शून्य.
 *	@cmd contains the operation to be perक्रमmed.
 *	Return 0 अगर permission is granted.
 * @msg_queue_msgsnd:
 *	Check permission beक्रमe a message, @msg, is enqueued on the message
 *	queue with permissions @perm.
 *	@perm contains the IPC permissions of the message queue.
 *	@msg contains the message to be enqueued.
 *	@msqflg contains operational flags.
 *	Return 0 अगर permission is granted.
 * @msg_queue_msgrcv:
 *	Check permission beक्रमe a message, @msg, is हटाओd from the message
 *	queue. The @target task काष्ठाure contains a poपूर्णांकer to the
 *	process that will be receiving the message (not equal to the current
 *	process when अंतरभूत receives are being perक्रमmed).
 *	@perm contains the IPC permissions of the message queue.
 *	@msg contains the message destination.
 *	@target contains the task काष्ठाure क्रम recipient process.
 *	@type contains the type of message requested.
 *	@mode contains the operational flags.
 *	Return 0 अगर permission is granted.
 *
 * Security hooks क्रम System V Shared Memory Segments
 *
 * @shm_alloc_security:
 *	Allocate and attach a security काष्ठाure to the @perm->security
 *	field. The security field is initialized to शून्य when the काष्ठाure is
 *	first created.
 *	@perm contains the IPC permissions of the shared memory काष्ठाure.
 *	Return 0 अगर operation was successful and permission is granted.
 * @shm_मुक्त_security:
 *	Deallocate the security काष्ठाure @perm->security क्रम the memory segment.
 *	@perm contains the IPC permissions of the shared memory काष्ठाure.
 * @shm_associate:
 *	Check permission when a shared memory region is requested through the
 *	shmget प्रणाली call. This hook is only called when वापसing the shared
 *	memory region identअगरier क्रम an existing region, not when a new shared
 *	memory region is created.
 *	@perm contains the IPC permissions of the shared memory काष्ठाure.
 *	@shmflg contains the operation control flags.
 *	Return 0 अगर permission is granted.
 * @shm_shmctl:
 *	Check permission when a shared memory control operation specअगरied by
 *	@cmd is to be perक्रमmed on the shared memory region with permissions @perm.
 *	The @perm may be शून्य, e.g. क्रम IPC_INFO or SHM_INFO.
 *	@perm contains the IPC permissions of the shared memory काष्ठाure.
 *	@cmd contains the operation to be perक्रमmed.
 *	Return 0 अगर permission is granted.
 * @shm_shmat:
 *	Check permissions prior to allowing the shmat प्रणाली call to attach the
 *	shared memory segment with permissions @perm to the data segment of the
 *	calling process. The attaching address is specअगरied by @shmaddr.
 *	@perm contains the IPC permissions of the shared memory काष्ठाure.
 *	@shmaddr contains the address to attach memory region to.
 *	@shmflg contains the operational flags.
 *	Return 0 अगर permission is granted.
 *
 * Security hooks क्रम System V Semaphores
 *
 * @sem_alloc_security:
 *	Allocate and attach a security काष्ठाure to the @perm->security
 *	field. The security field is initialized to शून्य when the काष्ठाure is
 *	first created.
 *	@perm contains the IPC permissions of the semaphore.
 *	Return 0 अगर operation was successful and permission is granted.
 * @sem_मुक्त_security:
 *	Deallocate security काष्ठाure @perm->security क्रम the semaphore.
 *	@perm contains the IPC permissions of the semaphore.
 * @sem_associate:
 *	Check permission when a semaphore is requested through the semget
 *	प्रणाली call. This hook is only called when वापसing the semaphore
 *	identअगरier क्रम an existing semaphore, not when a new one must be
 *	created.
 *	@perm contains the IPC permissions of the semaphore.
 *	@semflg contains the operation control flags.
 *	Return 0 अगर permission is granted.
 * @sem_semctl:
 *	Check permission when a semaphore operation specअगरied by @cmd is to be
 *	perक्रमmed on the semaphore. The @perm may be शून्य, e.g. क्रम
 *	IPC_INFO or SEM_INFO.
 *	@perm contains the IPC permissions of the semaphore. May be शून्य.
 *	@cmd contains the operation to be perक्रमmed.
 *	Return 0 अगर permission is granted.
 * @sem_semop:
 *	Check permissions beक्रमe perक्रमming operations on members of the
 *	semaphore set. If the @alter flag is nonzero, the semaphore set
 *	may be modअगरied.
 *	@perm contains the IPC permissions of the semaphore.
 *	@sops contains the operations to perक्रमm.
 *	@nsops contains the number of operations to perक्रमm.
 *	@alter contains the flag indicating whether changes are to be made.
 *	Return 0 अगर permission is granted.
 *
 * @binder_set_context_mgr:
 *	Check whether @mgr is allowed to be the binder context manager.
 *	@mgr contains the task_काष्ठा क्रम the task being रेजिस्टरed.
 *	Return 0 अगर permission is granted.
 * @binder_transaction:
 *	Check whether @from is allowed to invoke a binder transaction call
 *	to @to.
 *	@from contains the task_काष्ठा क्रम the sending task.
 *	@to contains the task_काष्ठा क्रम the receiving task.
 * @binder_transfer_binder:
 *	Check whether @from is allowed to transfer a binder reference to @to.
 *	@from contains the task_काष्ठा क्रम the sending task.
 *	@to contains the task_काष्ठा क्रम the receiving task.
 * @binder_transfer_file:
 *	Check whether @from is allowed to transfer @file to @to.
 *	@from contains the task_काष्ठा क्रम the sending task.
 *	@file contains the काष्ठा file being transferred.
 *	@to contains the task_काष्ठा क्रम the receiving task.
 *
 * @ptrace_access_check:
 *	Check permission beक्रमe allowing the current process to trace the
 *	@child process.
 *	Security modules may also want to perक्रमm a process tracing check
 *	during an execve in the set_security or apply_creds hooks of
 *	tracing check during an execve in the bprm_set_creds hook of
 *	binprm_security_ops अगर the process is being traced and its security
 *	attributes would be changed by the execve.
 *	@child contains the task_काष्ठा काष्ठाure क्रम the target process.
 *	@mode contains the PTRACE_MODE flags indicating the क्रमm of access.
 *	Return 0 अगर permission is granted.
 * @ptrace_traceme:
 *	Check that the @parent process has sufficient permission to trace the
 *	current process beक्रमe allowing the current process to present itself
 *	to the @parent process क्रम tracing.
 *	@parent contains the task_काष्ठा काष्ठाure क्रम debugger process.
 *	Return 0 अगर permission is granted.
 * @capget:
 *	Get the @effective, @inheritable, and @permitted capability sets क्रम
 *	the @target process.  The hook may also perक्रमm permission checking to
 *	determine अगर the current process is allowed to see the capability sets
 *	of the @target process.
 *	@target contains the task_काष्ठा काष्ठाure क्रम target process.
 *	@effective contains the effective capability set.
 *	@inheritable contains the inheritable capability set.
 *	@permitted contains the permitted capability set.
 *	Return 0 अगर the capability sets were successfully obtained.
 * @capset:
 *	Set the @effective, @inheritable, and @permitted capability sets क्रम
 *	the current process.
 *	@new contains the new credentials काष्ठाure क्रम target process.
 *	@old contains the current credentials काष्ठाure क्रम target process.
 *	@effective contains the effective capability set.
 *	@inheritable contains the inheritable capability set.
 *	@permitted contains the permitted capability set.
 *	Return 0 and update @new अगर permission is granted.
 * @capable:
 *	Check whether the @tsk process has the @cap capability in the indicated
 *	credentials.
 *	@cred contains the credentials to use.
 *	@ns contains the user namespace we want the capability in
 *	@cap contains the capability <include/linux/capability.h>.
 *	@opts contains options क्रम the capable check <include/linux/security.h>
 *	Return 0 अगर the capability is granted क्रम @tsk.
 * @quotactl:
 * 	Check whether the quotactl syscall is allowed क्रम this @sb.
 * @quota_on:
 * 	Check whether QUOTAON is allowed क्रम this @dentry.
 * @syslog:
 *	Check permission beक्रमe accessing the kernel message ring or changing
 *	logging to the console.
 *	See the syslog(2) manual page क्रम an explanation of the @type values.
 *	@type contains the SYSLOG_ACTION_* स्थिरant from <include/linux/syslog.h>
 *	Return 0 अगर permission is granted.
 * @समय_रखो:
 *	Check permission to change the प्रणाली समय.
 *	काष्ठा बारpec64 is defined in <include/linux/समय64.h> and समयzone
 *	is defined in <include/linux/समय.स>
 *	@ts contains new समय
 *	@tz contains new समयzone
 *	Return 0 अगर permission is granted.
 * @vm_enough_memory:
 *	Check permissions क्रम allocating a new भव mapping.
 *	@mm contains the mm काष्ठा it is being added to.
 *	@pages contains the number of pages.
 *	Return 0 अगर permission is granted.
 *
 * @ismaclabel:
 *	Check अगर the extended attribute specअगरied by @name
 *	represents a MAC label. Returns 1 अगर name is a MAC
 *	attribute otherwise वापसs 0.
 *	@name full extended attribute name to check against
 *	LSM as a MAC label.
 *
 * @secid_to_secctx:
 *	Convert secid to security context.  If secdata is शून्य the length of
 *	the result will be वापसed in seclen, but no secdata will be वापसed.
 *	This करोes mean that the length could change between calls to check the
 *	length and the next call which actually allocates and वापसs the
 *	secdata.
 *	@secid contains the security ID.
 *	@secdata contains the poपूर्णांकer that stores the converted security
 *	context.
 *	@seclen poपूर्णांकer which contains the length of the data
 * @secctx_to_secid:
 *	Convert security context to secid.
 *	@secid contains the poपूर्णांकer to the generated security ID.
 *	@secdata contains the security context.
 *
 * @release_secctx:
 *	Release the security context.
 *	@secdata contains the security context.
 *	@seclen contains the length of the security context.
 *
 * Security hooks क्रम Audit
 *
 * @audit_rule_init:
 *	Allocate and initialize an LSM audit rule काष्ठाure.
 *	@field contains the required Audit action.
 *	Fields flags are defined in <include/linux/audit.h>
 *	@op contains the चालक the rule uses.
 *	@rulestr contains the context where the rule will be applied to.
 *	@lsmrule contains a poपूर्णांकer to receive the result.
 *	Return 0 अगर @lsmrule has been successfully set,
 *	-EINVAL in हाल of an invalid rule.
 *
 * @audit_rule_known:
 *	Specअगरies whether given @krule contains any fields related to
 *	current LSM.
 *	@krule contains the audit rule of पूर्णांकerest.
 *	Return 1 in हाल of relation found, 0 otherwise.
 *
 * @audit_rule_match:
 *	Determine अगर given @secid matches a rule previously approved
 *	by @audit_rule_known.
 *	@secid contains the security id in question.
 *	@field contains the field which relates to current LSM.
 *	@op contains the चालक that will be used क्रम matching.
 *	@lrule poपूर्णांकs to the audit rule that will be checked against.
 *	Return 1 अगर secid matches the rule, 0 अगर it करोes not, -ERRNO on failure.
 *
 * @audit_rule_मुक्त:
 *	Deallocate the LSM audit rule काष्ठाure previously allocated by
 *	audit_rule_init.
 *	@lsmrule contains the allocated rule
 *
 * @inode_invalidate_secctx:
 *	Notअगरy the security module that it must revalidate the security context
 *	of an inode.
 *
 * @inode_notअगरysecctx:
 *	Notअगरy the security module of what the security context of an inode
 *	should be.  Initializes the incore security context managed by the
 *	security module क्रम this inode.  Example usage:  NFS client invokes
 *	this hook to initialize the security context in its incore inode to the
 *	value provided by the server क्रम the file when the server वापसed the
 *	file's attributes to the client.
 *	Must be called with inode->i_mutex locked.
 *	@inode we wish to set the security context of.
 *	@ctx contains the string which we wish to set in the inode.
 *	@ctxlen contains the length of @ctx.
 *
 * @inode_setsecctx:
 *	Change the security context of an inode.  Updates the
 *	incore security context managed by the security module and invokes the
 *	fs code as needed (via __vfs_setxattr_noperm) to update any backing
 *	xattrs that represent the context.  Example usage:  NFS server invokes
 *	this hook to change the security context in its incore inode and on the
 *	backing fileप्रणाली to a value provided by the client on a SETATTR
 *	operation.
 *	Must be called with inode->i_mutex locked.
 *	@dentry contains the inode we wish to set the security context of.
 *	@ctx contains the string which we wish to set in the inode.
 *	@ctxlen contains the length of @ctx.
 *
 * @inode_माला_लोecctx:
 *	On success, वापसs 0 and fills out @ctx and @ctxlen with the security
 *	context क्रम the given @inode.
 *	@inode we wish to get the security context of.
 *	@ctx is a poपूर्णांकer in which to place the allocated security context.
 *	@ctxlen poपूर्णांकs to the place to put the length of @ctx.
 *
 * Security hooks क्रम the general notअगरication queue:
 *
 * @post_notअगरication:
 *	Check to see अगर a watch notअगरication can be posted to a particular
 *	queue.
 *	@w_cred: The credentials of the whoever set the watch.
 *	@cred: The event-triggerer's credentials
 *	@n: The notअगरication being posted
 *
 * @watch_key:
 *	Check to see अगर a process is allowed to watch क्रम event notअगरications
 *	from a key or keyring.
 *	@key: The key to watch.
 *
 * Security hooks क्रम using the eBPF maps and programs functionalities through
 * eBPF syscalls.
 *
 * @bpf:
 *	Do a initial check क्रम all bpf syscalls after the attribute is copied
 *	पूर्णांकo the kernel. The actual security module can implement their own
 *	rules to check the specअगरic cmd they need.
 *
 * @bpf_map:
 *	Do a check when the kernel generate and वापस a file descriptor क्रम
 *	eBPF maps.
 *
 *	@map: bpf map that we want to access
 *	@mask: the access flags
 *
 * @bpf_prog:
 *	Do a check when the kernel generate and वापस a file descriptor क्रम
 *	eBPF programs.
 *
 *	@prog: bpf prog that userspace want to use.
 *
 * @bpf_map_alloc_security:
 *	Initialize the security field inside bpf map.
 *
 * @bpf_map_मुक्त_security:
 *	Clean up the security inक्रमmation stored inside bpf map.
 *
 * @bpf_prog_alloc_security:
 *	Initialize the security field inside bpf program.
 *
 * @bpf_prog_मुक्त_security:
 *	Clean up the security inक्रमmation stored inside bpf prog.
 *
 * @locked_करोwn:
 *     Determine whether a kernel feature that potentially enables arbitrary
 *     code execution in kernel space should be permitted.
 *
 *     @what: kernel feature being accessed
 *
 * Security hooks क्रम perf events
 *
 * @perf_event_खोलो:
 * 	Check whether the @type of perf_event_खोलो syscall is allowed.
 * @perf_event_alloc:
 * 	Allocate and save perf_event security info.
 * @perf_event_मुक्त:
 * 	Release (मुक्त) perf_event security info.
 * @perf_event_पढ़ो:
 * 	Read perf_event security info अगर allowed.
 * @perf_event_ग_लिखो:
 * 	Write perf_event security info अगर allowed.
 */
जोड़ security_list_options अणु
	#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) RET (*NAME)(__VA_ARGS__);
	#समावेश "lsm_hook_defs.h"
	#अघोषित LSM_HOOK
पूर्ण;

काष्ठा security_hook_heads अणु
	#घोषणा LSM_HOOK(RET, DEFAULT, NAME, ...) काष्ठा hlist_head NAME;
	#समावेश "lsm_hook_defs.h"
	#अघोषित LSM_HOOK
पूर्ण __अक्रमomize_layout;

/*
 * Security module hook list काष्ठाure.
 * For use with generic list macros क्रम common operations.
 */
काष्ठा security_hook_list अणु
	काष्ठा hlist_node		list;
	काष्ठा hlist_head		*head;
	जोड़ security_list_options	hook;
	अक्षर				*lsm;
पूर्ण __अक्रमomize_layout;

/*
 * Security blob size or offset data.
 */
काष्ठा lsm_blob_sizes अणु
	पूर्णांक	lbs_cred;
	पूर्णांक	lbs_file;
	पूर्णांक	lbs_inode;
	पूर्णांक	lbs_superblock;
	पूर्णांक	lbs_ipc;
	पूर्णांक	lbs_msg_msg;
	पूर्णांक	lbs_task;
पूर्ण;

/*
 * LSM_RET_VOID is used as the शेष value in LSM_HOOK definitions क्रम व्योम
 * LSM hooks (in include/linux/lsm_hook_defs.h).
 */
#घोषणा LSM_RET_VOID ((व्योम) 0)

/*
 * Initializing a security_hook_list काष्ठाure takes
 * up a lot of space in a source file. This macro takes
 * care of the common हाल and reduces the amount of
 * text involved.
 */
#घोषणा LSM_HOOK_INIT(HEAD, HOOK) \
	अणु .head = &security_hook_heads.HEAD, .hook = अणु .HEAD = HOOK पूर्ण पूर्ण

बाह्य काष्ठा security_hook_heads security_hook_heads;
बाह्य अक्षर *lsm_names;

बाह्य व्योम security_add_hooks(काष्ठा security_hook_list *hooks, पूर्णांक count,
				अक्षर *lsm);

#घोषणा LSM_FLAG_LEGACY_MAJOR	BIT(0)
#घोषणा LSM_FLAG_EXCLUSIVE	BIT(1)

क्रमागत lsm_order अणु
	LSM_ORDER_FIRST = -1,	/* This is only क्रम capabilities. */
	LSM_ORDER_MUTABLE = 0,
पूर्ण;

काष्ठा lsm_info अणु
	स्थिर अक्षर *name;	/* Required. */
	क्रमागत lsm_order order;	/* Optional: शेष is LSM_ORDER_MUTABLE */
	अचिन्हित दीर्घ flags;	/* Optional: flags describing LSM */
	पूर्णांक *enabled;		/* Optional: controlled by CONFIG_LSM */
	पूर्णांक (*init)(व्योम);	/* Required. */
	काष्ठा lsm_blob_sizes *blobs; /* Optional: क्रम blob sharing. */
पूर्ण;

बाह्य काष्ठा lsm_info __start_lsm_info[], __end_lsm_info[];
बाह्य काष्ठा lsm_info __start_early_lsm_info[], __end_early_lsm_info[];

#घोषणा DEFINE_LSM(lsm)							\
	अटल काष्ठा lsm_info __lsm_##lsm				\
		__used __section(".lsm_info.init")			\
		__aligned(माप(अचिन्हित दीर्घ))

#घोषणा DEFINE_EARLY_LSM(lsm)						\
	अटल काष्ठा lsm_info __early_lsm_##lsm			\
		__used __section(".early_lsm_info.init")		\
		__aligned(माप(अचिन्हित दीर्घ))

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
/*
 * Assuring the safety of deleting a security module is up to
 * the security module involved. This may entail ordering the
 * module's hook list in a particular way, refusing to disable
 * the module once a policy is loaded or any number of other
 * actions better imagined than described.
 *
 * The name of the configuration option reflects the only module
 * that currently uses the mechanism. Any developer who thinks
 * disabling their module is a good idea needs to be at least as
 * careful as the SELinux team.
 */
अटल अंतरभूत व्योम security_delete_hooks(काष्ठा security_hook_list *hooks,
						पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		hlist_del_rcu(&hooks[i].list);
पूर्ण
#पूर्ण_अगर /* CONFIG_SECURITY_SELINUX_DISABLE */

/* Currently required to handle SELinux runसमय hook disable. */
#अगर_घोषित CONFIG_SECURITY_WRITABLE_HOOKS
#घोषणा __lsm_ro_after_init
#अन्यथा
#घोषणा __lsm_ro_after_init	__ro_after_init
#पूर्ण_अगर /* CONFIG_SECURITY_WRITABLE_HOOKS */

बाह्य पूर्णांक lsm_inode_alloc(काष्ठा inode *inode);

#पूर्ण_अगर /* ! __LINUX_LSM_HOOKS_H */
