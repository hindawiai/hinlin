<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS silly नाम handling
 *
 * Copyright (C) 2019 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 * - Derived from NFS's sillyनाम.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश "internal.h"

अटल व्योम afs_silly_नाम_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);

	afs_check_dir_conflict(op, &op->file[0]);
	afs_vnode_commit_status(op, &op->file[0]);
पूर्ण

अटल व्योम afs_silly_नाम_edit_dir(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode *dvnode = dvp->vnode;
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(op->dentry));
	काष्ठा dentry *old = op->dentry;
	काष्ठा dentry *new = op->dentry_2;

	spin_lock(&old->d_lock);
	old->d_flags |= DCACHE_NFSFS_RENAMED;
	spin_unlock(&old->d_lock);
	अगर (dvnode->silly_key != op->key) अणु
		key_put(dvnode->silly_key);
		dvnode->silly_key = key_get(op->key);
	पूर्ण

	करोwn_ग_लिखो(&dvnode->validate_lock);
	अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags) &&
	    dvnode->status.data_version == dvp->dv_beक्रमe + dvp->dv_delta) अणु
		afs_edit_dir_हटाओ(dvnode, &old->d_name,
				    afs_edit_dir_क्रम_silly_0);
		afs_edit_dir_add(dvnode, &new->d_name,
				 &vnode->fid, afs_edit_dir_क्रम_silly_1);
	पूर्ण
	up_ग_लिखो(&dvnode->validate_lock);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_silly_नाम_operation = अणु
	.issue_afs_rpc	= afs_fs_नाम,
	.issue_yfs_rpc	= yfs_fs_नाम,
	.success	= afs_silly_नाम_success,
	.edit_dir	= afs_silly_नाम_edit_dir,
पूर्ण;

/*
 * Actually perक्रमm the silly नाम step.
 */
अटल पूर्णांक afs_करो_silly_नाम(काष्ठा afs_vnode *dvnode, काष्ठा afs_vnode *vnode,
			       काष्ठा dentry *old, काष्ठा dentry *new,
			       काष्ठा key *key)
अणु
	काष्ठा afs_operation *op;

	_enter("%pd,%pd", old, new);

	op = afs_alloc_operation(key, dvnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_vnode(op, 1, dvnode);
	op->file[0].dv_delta = 1;
	op->file[1].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[1].modअगरication = true;
	op->file[0].update_स_समय = true;
	op->file[1].update_स_समय = true;

	op->dentry		= old;
	op->dentry_2		= new;
	op->ops			= &afs_silly_नाम_operation;

	trace_afs_silly_नाम(vnode, false);
	वापस afs_करो_sync_operation(op);
पूर्ण

/**
 * afs_sillyनाम - Perक्रमm a silly-नाम of a dentry
 *
 * AFS is stateless and the server करोesn't know when the client is holding a
 * file खोलो.  To prevent application problems when a file is unlinked जबतक
 * it's still खोलो, the client perक्रमms a "silly-rename".  That is, it नामs
 * the file to a hidden file in the same directory, and only perक्रमms the
 * unlink once the last reference to it is put.
 *
 * The final cleanup is करोne during dentry_iput.
 */
पूर्णांक afs_sillyनाम(काष्ठा afs_vnode *dvnode, काष्ठा afs_vnode *vnode,
		    काष्ठा dentry *dentry, काष्ठा key *key)
अणु
	अटल अचिन्हित पूर्णांक sillycounter;
	काष्ठा dentry *sdentry = शून्य;
	अचिन्हित अक्षर silly[16];
	पूर्णांक ret = -EBUSY;

	_enter("");

	/* We करोn't allow a dentry to be silly-नामd twice. */
	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		वापस -EBUSY;

	sdentry = शून्य;
	करो अणु
		पूर्णांक slen;

		dput(sdentry);
		sillycounter++;

		/* Create a silly name.  Note that the ".__afs" prefix is
		 * understood by the salvager and must not be changed.
		 */
		slen = scnम_लिखो(silly, माप(silly), ".__afs%04X", sillycounter);
		sdentry = lookup_one_len(silly, dentry->d_parent, slen);

		/* N.B. Better to वापस EBUSY here ... it could be dangerous
		 * to delete the file जबतक it's in use.
		 */
		अगर (IS_ERR(sdentry))
			जाओ out;
	पूर्ण जबतक (!d_is_negative(sdentry));

	ihold(&vnode->vfs_inode);

	ret = afs_करो_silly_नाम(dvnode, vnode, dentry, sdentry, key);
	चयन (ret) अणु
	हाल 0:
		/* The नाम succeeded. */
		set_bit(AFS_VNODE_SILLY_DELETED, &vnode->flags);
		d_move(dentry, sdentry);
		अवरोध;
	हाल -ERESTARTSYS:
		/* The result of the नाम is unknown. Play it safe by क्रमcing
		 * a new lookup.
		 */
		d_drop(dentry);
		d_drop(sdentry);
	पूर्ण

	iput(&vnode->vfs_inode);
	dput(sdentry);
out:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल व्योम afs_silly_unlink_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	afs_check_dir_conflict(op, &op->file[0]);
	afs_vnode_commit_status(op, &op->file[0]);
	afs_vnode_commit_status(op, &op->file[1]);
	afs_update_dentry_version(op, &op->file[0], op->dentry);
पूर्ण

अटल व्योम afs_silly_unlink_edit_dir(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode *dvnode = dvp->vnode;

	_enter("op=%08x", op->debug_id);
	करोwn_ग_लिखो(&dvnode->validate_lock);
	अगर (test_bit(AFS_VNODE_सूची_VALID, &dvnode->flags) &&
	    dvnode->status.data_version == dvp->dv_beक्रमe + dvp->dv_delta)
		afs_edit_dir_हटाओ(dvnode, &op->dentry->d_name,
				    afs_edit_dir_क्रम_unlink);
	up_ग_लिखो(&dvnode->validate_lock);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_silly_unlink_operation = अणु
	.issue_afs_rpc	= afs_fs_हटाओ_file,
	.issue_yfs_rpc	= yfs_fs_हटाओ_file,
	.success	= afs_silly_unlink_success,
	.पातed	= afs_check_क्रम_remote_deletion,
	.edit_dir	= afs_silly_unlink_edit_dir,
पूर्ण;

/*
 * Tell the server to हटाओ a sillyनाम file.
 */
अटल पूर्णांक afs_करो_silly_unlink(काष्ठा afs_vnode *dvnode, काष्ठा afs_vnode *vnode,
			       काष्ठा dentry *dentry, काष्ठा key *key)
अणु
	काष्ठा afs_operation *op;

	_enter("");

	op = afs_alloc_operation(शून्य, dvnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, dvnode);
	afs_op_set_vnode(op, 1, vnode);
	op->file[0].dv_delta = 1;
	op->file[0].modअगरication = true;
	op->file[0].update_स_समय = true;
	op->file[1].op_unlinked = true;
	op->file[1].update_स_समय = true;

	op->dentry	= dentry;
	op->ops		= &afs_silly_unlink_operation;

	trace_afs_silly_नाम(vnode, true);
	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);

	/* If there was a conflict with a third party, check the status of the
	 * unlinked vnode.
	 */
	अगर (op->error == 0 && (op->flags & AFS_OPERATION_सूची_CONFLICT)) अणु
		op->file[1].update_स_समय = false;
		op->fetch_status.which = 1;
		op->ops = &afs_fetch_status_operation;
		afs_begin_vnode_operation(op);
		afs_रुको_क्रम_operation(op);
	पूर्ण

	वापस afs_put_operation(op);
पूर्ण

/*
 * Remove sillyनाम file on iput.
 */
पूर्णांक afs_silly_iput(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा afs_vnode *dvnode = AFS_FS_I(d_inode(dentry->d_parent));
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा dentry *alias;
	पूर्णांक ret;

	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);

	_enter("%p{%pd},%llx", dentry, dentry, vnode->fid.vnode);

	करोwn_पढ़ो(&dvnode->सूची_हटाओ_lock);

	alias = d_alloc_parallel(dentry->d_parent, &dentry->d_name, &wq);
	अगर (IS_ERR(alias)) अणु
		up_पढ़ो(&dvnode->सूची_हटाओ_lock);
		वापस 0;
	पूर्ण

	अगर (!d_in_lookup(alias)) अणु
		/* We raced with lookup...  See अगर we need to transfer the
		 * sillyनाम inक्रमmation to the aliased dentry.
		 */
		ret = 0;
		spin_lock(&alias->d_lock);
		अगर (d_really_is_positive(alias) &&
		    !(alias->d_flags & DCACHE_NFSFS_RENAMED)) अणु
			alias->d_flags |= DCACHE_NFSFS_RENAMED;
			ret = 1;
		पूर्ण
		spin_unlock(&alias->d_lock);
		up_पढ़ो(&dvnode->सूची_हटाओ_lock);
		dput(alias);
		वापस ret;
	पूर्ण

	/* Stop lock-release from complaining. */
	spin_lock(&vnode->lock);
	vnode->lock_state = AFS_VNODE_LOCK_DELETED;
	trace_afs_flock_ev(vnode, शून्य, afs_flock_silly_delete, 0);
	spin_unlock(&vnode->lock);

	afs_करो_silly_unlink(dvnode, vnode, dentry, dvnode->silly_key);
	up_पढ़ो(&dvnode->सूची_हटाओ_lock);
	d_lookup_करोne(alias);
	dput(alias);
	वापस 1;
पूर्ण
