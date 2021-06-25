<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Fileserver-directed operation handling.
 *
 * Copyright (C) 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश "internal.h"

अटल atomic_t afs_operation_debug_counter;

/*
 * Create an operation against a volume.
 */
काष्ठा afs_operation *afs_alloc_operation(काष्ठा key *key, काष्ठा afs_volume *volume)
अणु
	काष्ठा afs_operation *op;

	_enter("");

	op = kzalloc(माप(*op), GFP_KERNEL);
	अगर (!op)
		वापस ERR_PTR(-ENOMEM);

	अगर (!key) अणु
		key = afs_request_key(volume->cell);
		अगर (IS_ERR(key)) अणु
			kमुक्त(op);
			वापस ERR_CAST(key);
		पूर्ण
	पूर्ण अन्यथा अणु
		key_get(key);
	पूर्ण

	op->key		= key;
	op->volume	= afs_get_volume(volume, afs_volume_trace_get_new_op);
	op->net		= volume->cell->net;
	op->cb_v_अवरोध	= volume->cb_v_अवरोध;
	op->debug_id	= atomic_inc_वापस(&afs_operation_debug_counter);
	op->error	= -EDESTADDRREQ;
	op->ac.error	= लघु_उच्च;

	_leave(" = [op=%08x]", op->debug_id);
	वापस op;
पूर्ण

/*
 * Lock the vnode(s) being operated upon.
 */
अटल bool afs_get_io_locks(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *vnode = op->file[0].vnode;
	काष्ठा afs_vnode *vnode2 = op->file[1].vnode;

	_enter("");

	अगर (op->flags & AFS_OPERATION_UNINTR) अणु
		mutex_lock(&vnode->io_lock);
		op->flags |= AFS_OPERATION_LOCK_0;
		_leave(" = t [1]");
		वापस true;
	पूर्ण

	अगर (!vnode2 || !op->file[1].need_io_lock || vnode == vnode2)
		vnode2 = शून्य;

	अगर (vnode2 > vnode)
		swap(vnode, vnode2);

	अगर (mutex_lock_पूर्णांकerruptible(&vnode->io_lock) < 0) अणु
		op->error = -ERESTARTSYS;
		op->flags |= AFS_OPERATION_STOP;
		_leave(" = f [I 0]");
		वापस false;
	पूर्ण
	op->flags |= AFS_OPERATION_LOCK_0;

	अगर (vnode2) अणु
		अगर (mutex_lock_पूर्णांकerruptible_nested(&vnode2->io_lock, 1) < 0) अणु
			op->error = -ERESTARTSYS;
			op->flags |= AFS_OPERATION_STOP;
			mutex_unlock(&vnode->io_lock);
			op->flags &= ~AFS_OPERATION_LOCK_0;
			_leave(" = f [I 1]");
			वापस false;
		पूर्ण
		op->flags |= AFS_OPERATION_LOCK_1;
	पूर्ण

	_leave(" = t [2]");
	वापस true;
पूर्ण

अटल व्योम afs_drop_io_locks(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *vnode = op->file[0].vnode;
	काष्ठा afs_vnode *vnode2 = op->file[1].vnode;

	_enter("");

	अगर (op->flags & AFS_OPERATION_LOCK_1)
		mutex_unlock(&vnode2->io_lock);
	अगर (op->flags & AFS_OPERATION_LOCK_0)
		mutex_unlock(&vnode->io_lock);
पूर्ण

अटल व्योम afs_prepare_vnode(काष्ठा afs_operation *op, काष्ठा afs_vnode_param *vp,
			      अचिन्हित पूर्णांक index)
अणु
	काष्ठा afs_vnode *vnode = vp->vnode;

	अगर (vnode) अणु
		vp->fid			= vnode->fid;
		vp->dv_beक्रमe		= vnode->status.data_version;
		vp->cb_अवरोध_beक्रमe	= afs_calc_vnode_cb_अवरोध(vnode);
		अगर (vnode->lock_state != AFS_VNODE_LOCK_NONE)
			op->flags	|= AFS_OPERATION_CUR_ONLY;
		अगर (vp->modअगरication)
			set_bit(AFS_VNODE_MODIFYING, &vnode->flags);
	पूर्ण

	अगर (vp->fid.vnode)
		_debug("PREP[%u] {%llx:%llu.%u}",
		       index, vp->fid.vid, vp->fid.vnode, vp->fid.unique);
पूर्ण

/*
 * Begin an operation on the fileserver.
 *
 * Fileserver operations are serialised on the server by vnode, so we serialise
 * them here also using the io_lock.
 */
bool afs_begin_vnode_operation(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode *vnode = op->file[0].vnode;

	ASSERT(vnode);

	_enter("");

	अगर (op->file[0].need_io_lock)
		अगर (!afs_get_io_locks(op))
			वापस false;

	afs_prepare_vnode(op, &op->file[0], 0);
	afs_prepare_vnode(op, &op->file[1], 1);
	op->cb_v_अवरोध = op->volume->cb_v_अवरोध;
	_leave(" = true");
	वापस true;
पूर्ण

/*
 * Tidy up a fileप्रणाली cursor and unlock the vnode.
 */
अटल व्योम afs_end_vnode_operation(काष्ठा afs_operation *op)
अणु
	_enter("");

	अगर (op->error == -EDESTADDRREQ ||
	    op->error == -EADDRNOTAVAIL ||
	    op->error == -ENETUNREACH ||
	    op->error == -EHOSTUNREACH)
		afs_dump_edestaddrreq(op);

	afs_drop_io_locks(op);

	अगर (op->error == -ECONNABORTED)
		op->error = afs_पात_to_error(op->ac.पात_code);
पूर्ण

/*
 * Wait क्रम an in-progress operation to complete.
 */
व्योम afs_रुको_क्रम_operation(काष्ठा afs_operation *op)
अणु
	_enter("");

	जबतक (afs_select_fileserver(op)) अणु
		op->cb_s_अवरोध = op->server->cb_s_अवरोध;
		अगर (test_bit(AFS_SERVER_FL_IS_YFS, &op->server->flags) &&
		    op->ops->issue_yfs_rpc)
			op->ops->issue_yfs_rpc(op);
		अन्यथा अगर (op->ops->issue_afs_rpc)
			op->ops->issue_afs_rpc(op);
		अन्यथा
			op->ac.error = -ENOTSUPP;

		अगर (op->call)
			op->error = afs_रुको_क्रम_call_to_complete(op->call, &op->ac);
	पूर्ण

	चयन (op->error) अणु
	हाल 0:
		_debug("success");
		op->ops->success(op);
		अवरोध;
	हाल -ECONNABORTED:
		अगर (op->ops->पातed)
			op->ops->पातed(op);
		fallthrough;
	शेष:
		अगर (op->ops->failed)
			op->ops->failed(op);
		अवरोध;
	पूर्ण

	afs_end_vnode_operation(op);

	अगर (op->error == 0 && op->ops->edit_dir) अणु
		_debug("edit_dir");
		op->ops->edit_dir(op);
	पूर्ण
	_leave("");
पूर्ण

/*
 * Dispose of an operation.
 */
पूर्णांक afs_put_operation(काष्ठा afs_operation *op)
अणु
	पूर्णांक i, ret = op->error;

	_enter("op=%08x,%d", op->debug_id, ret);

	अगर (op->ops && op->ops->put)
		op->ops->put(op);
	अगर (op->file[0].modअगरication)
		clear_bit(AFS_VNODE_MODIFYING, &op->file[0].vnode->flags);
	अगर (op->file[1].modअगरication && op->file[1].vnode != op->file[0].vnode)
		clear_bit(AFS_VNODE_MODIFYING, &op->file[1].vnode->flags);
	अगर (op->file[0].put_vnode)
		iput(&op->file[0].vnode->vfs_inode);
	अगर (op->file[1].put_vnode)
		iput(&op->file[1].vnode->vfs_inode);

	अगर (op->more_files) अणु
		क्रम (i = 0; i < op->nr_files - 2; i++)
			अगर (op->more_files[i].put_vnode)
				iput(&op->more_files[i].vnode->vfs_inode);
		kमुक्त(op->more_files);
	पूर्ण

	afs_end_cursor(&op->ac);
	afs_put_serverlist(op->net, op->server_list);
	afs_put_volume(op->net, op->volume, afs_volume_trace_put_put_op);
	key_put(op->key);
	kमुक्त(op);
	वापस ret;
पूर्ण

पूर्णांक afs_करो_sync_operation(काष्ठा afs_operation *op)
अणु
	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);
	वापस afs_put_operation(op);
पूर्ण
