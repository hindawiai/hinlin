<शैली गुरु>
/*
 * Copyright (c) 2002 Red Hat, Inc. All rights reserved.
 *
 * This software may be मुक्तly redistributed under the terms of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Authors: David Woodhouse <dwmw2@infradead.org>
 *          David Howells <dhowells@redhat.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/iversion.h>
#समावेश "internal.h"
#समावेश "afs_fs.h"

अटल स्थिर काष्ठा inode_operations afs_symlink_inode_operations = अणु
	.get_link	= page_get_link,
पूर्ण;

अटल noअंतरभूत व्योम dump_vnode(काष्ठा afs_vnode *vnode, काष्ठा afs_vnode *parent_vnode)
अणु
	अटल अचिन्हित दीर्घ once_only;

	pr_warn("kAFS: AFS vnode with undefined type %u\n", vnode->status.type);
	pr_warn("kAFS: A=%d m=%o s=%llx v=%llx\n",
		vnode->status.पात_code,
		vnode->status.mode,
		vnode->status.size,
		vnode->status.data_version);
	pr_warn("kAFS: vnode %llx:%llx:%x\n",
		vnode->fid.vid,
		vnode->fid.vnode,
		vnode->fid.unique);
	अगर (parent_vnode)
		pr_warn("kAFS: dir %llx:%llx:%x\n",
			parent_vnode->fid.vid,
			parent_vnode->fid.vnode,
			parent_vnode->fid.unique);

	अगर (!test_and_set_bit(0, &once_only))
		dump_stack();
पूर्ण

/*
 * Set the file size and block count.  Estimate the number of 512 bytes blocks
 * used, rounded up to nearest 1K क्रम consistency with other AFS clients.
 */
अटल व्योम afs_set_i_size(काष्ठा afs_vnode *vnode, u64 size)
अणु
	i_size_ग_लिखो(&vnode->vfs_inode, size);
	vnode->vfs_inode.i_blocks = ((size + 1023) >> 10) << 1;
पूर्ण

/*
 * Initialise an inode from the vnode status.
 */
अटल पूर्णांक afs_inode_init_from_status(काष्ठा afs_operation *op,
				      काष्ठा afs_vnode_param *vp,
				      काष्ठा afs_vnode *vnode)
अणु
	काष्ठा afs_file_status *status = &vp->scb.status;
	काष्ठा inode *inode = AFS_VNODE_TO_I(vnode);
	काष्ठा बारpec64 t;

	_enter("{%llx:%llu.%u} %s",
	       vp->fid.vid, vp->fid.vnode, vp->fid.unique,
	       op->type ? op->type->name : "???");

	_debug("FS: ft=%d lk=%d sz=%llu ver=%Lu mod=%hu",
	       status->type,
	       status->nlink,
	       (अचिन्हित दीर्घ दीर्घ) status->size,
	       status->data_version,
	       status->mode);

	ग_लिखो_seqlock(&vnode->cb_lock);

	vnode->cb_v_अवरोध = op->cb_v_अवरोध;
	vnode->cb_s_अवरोध = op->cb_s_अवरोध;
	vnode->status = *status;

	t = status->mसमय_client;
	inode->i_स_समय = t;
	inode->i_mसमय = t;
	inode->i_aसमय = t;
	inode->i_flags |= S_NOATIME;
	inode->i_uid = make_kuid(&init_user_ns, status->owner);
	inode->i_gid = make_kgid(&init_user_ns, status->group);
	set_nlink(&vnode->vfs_inode, status->nlink);

	चयन (status->type) अणु
	हाल AFS_FTYPE_खाता:
		inode->i_mode	= S_IFREG | (status->mode & S_IALLUGO);
		inode->i_op	= &afs_file_inode_operations;
		inode->i_fop	= &afs_file_operations;
		inode->i_mapping->a_ops	= &afs_fs_aops;
		अवरोध;
	हाल AFS_FTYPE_सूची:
		inode->i_mode	= S_IFसूची |  (status->mode & S_IALLUGO);
		inode->i_op	= &afs_dir_inode_operations;
		inode->i_fop	= &afs_dir_file_operations;
		inode->i_mapping->a_ops	= &afs_dir_aops;
		अवरोध;
	हाल AFS_FTYPE_SYMLINK:
		/* Symlinks with a mode of 0644 are actually mountpoपूर्णांकs. */
		अगर ((status->mode & 0777) == 0644) अणु
			inode->i_flags |= S_AUTOMOUNT;

			set_bit(AFS_VNODE_MOUNTPOINT, &vnode->flags);

			inode->i_mode	= S_IFसूची | 0555;
			inode->i_op	= &afs_mntpt_inode_operations;
			inode->i_fop	= &afs_mntpt_file_operations;
			inode->i_mapping->a_ops	= &afs_fs_aops;
		पूर्ण अन्यथा अणु
			inode->i_mode	= S_IFLNK | status->mode;
			inode->i_op	= &afs_symlink_inode_operations;
			inode->i_mapping->a_ops	= &afs_fs_aops;
		पूर्ण
		inode_nohighmem(inode);
		अवरोध;
	शेष:
		dump_vnode(vnode, op->file[0].vnode != vnode ? op->file[0].vnode : शून्य);
		ग_लिखो_sequnlock(&vnode->cb_lock);
		वापस afs_protocol_error(शून्य, afs_eproto_file_type);
	पूर्ण

	afs_set_i_size(vnode, status->size);

	vnode->invalid_beक्रमe	= status->data_version;
	inode_set_iversion_raw(&vnode->vfs_inode, status->data_version);

	अगर (!vp->scb.have_cb) अणु
		/* it's a symlink we just created (the fileserver
		 * didn't give us a callback) */
		vnode->cb_expires_at = kसमय_get_real_seconds();
	पूर्ण अन्यथा अणु
		vnode->cb_expires_at = vp->scb.callback.expires_at;
		vnode->cb_server = op->server;
		set_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
	पूर्ण

	ग_लिखो_sequnlock(&vnode->cb_lock);
	वापस 0;
पूर्ण

/*
 * Update the core inode काष्ठा from a वापसed status record.
 */
अटल व्योम afs_apply_status(काष्ठा afs_operation *op,
			     काष्ठा afs_vnode_param *vp)
अणु
	काष्ठा afs_file_status *status = &vp->scb.status;
	काष्ठा afs_vnode *vnode = vp->vnode;
	काष्ठा inode *inode = &vnode->vfs_inode;
	काष्ठा बारpec64 t;
	umode_t mode;
	bool data_changed = false;
	bool change_size = vp->set_size;

	_enter("{%llx:%llu.%u} %s",
	       vp->fid.vid, vp->fid.vnode, vp->fid.unique,
	       op->type ? op->type->name : "???");

	BUG_ON(test_bit(AFS_VNODE_UNSET, &vnode->flags));

	अगर (status->type != vnode->status.type) अणु
		pr_warn("Vnode %llx:%llx:%x changed type %u to %u\n",
			vnode->fid.vid,
			vnode->fid.vnode,
			vnode->fid.unique,
			status->type, vnode->status.type);
		afs_protocol_error(शून्य, afs_eproto_bad_status);
		वापस;
	पूर्ण

	अगर (status->nlink != vnode->status.nlink)
		set_nlink(inode, status->nlink);

	अगर (status->owner != vnode->status.owner)
		inode->i_uid = make_kuid(&init_user_ns, status->owner);

	अगर (status->group != vnode->status.group)
		inode->i_gid = make_kgid(&init_user_ns, status->group);

	अगर (status->mode != vnode->status.mode) अणु
		mode = inode->i_mode;
		mode &= ~S_IALLUGO;
		mode |= status->mode & S_IALLUGO;
		WRITE_ONCE(inode->i_mode, mode);
	पूर्ण

	t = status->mसमय_client;
	inode->i_mसमय = t;
	अगर (vp->update_स_समय)
		inode->i_स_समय = op->स_समय;

	अगर (vnode->status.data_version != status->data_version)
		data_changed = true;

	vnode->status = *status;

	अगर (vp->dv_beक्रमe + vp->dv_delta != status->data_version) अणु
		अगर (test_bit(AFS_VNODE_CB_PROMISED, &vnode->flags))
			pr_warn("kAFS: vnode modified {%llx:%llu} %llx->%llx %s (op=%x)\n",
				vnode->fid.vid, vnode->fid.vnode,
				(अचिन्हित दीर्घ दीर्घ)vp->dv_beक्रमe + vp->dv_delta,
				(अचिन्हित दीर्घ दीर्घ)status->data_version,
				op->type ? op->type->name : "???",
				op->debug_id);

		vnode->invalid_beक्रमe = status->data_version;
		अगर (vnode->status.type == AFS_FTYPE_सूची) अणु
			अगर (test_and_clear_bit(AFS_VNODE_सूची_VALID, &vnode->flags))
				afs_stat_v(vnode, n_inval);
		पूर्ण अन्यथा अणु
			set_bit(AFS_VNODE_ZAP_DATA, &vnode->flags);
		पूर्ण
		change_size = true;
	पूर्ण अन्यथा अगर (vnode->status.type == AFS_FTYPE_सूची) अणु
		/* Expected directory change is handled अन्यथाwhere so
		 * that we can locally edit the directory and save on a
		 * करोwnload.
		 */
		अगर (test_bit(AFS_VNODE_सूची_VALID, &vnode->flags))
			data_changed = false;
		change_size = true;
	पूर्ण

	अगर (data_changed) अणु
		inode_set_iversion_raw(inode, status->data_version);

		/* Only update the size अगर the data version jumped.  If the
		 * file is being modअगरied locally, then we might have our own
		 * idea of what the size should be that's not the same as
		 * what's on the server.
		 */
		अगर (change_size) अणु
			afs_set_i_size(vnode, status->size);
			inode->i_स_समय = t;
			inode->i_aसमय = t;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Apply a callback to a vnode.
 */
अटल व्योम afs_apply_callback(काष्ठा afs_operation *op,
			       काष्ठा afs_vnode_param *vp)
अणु
	काष्ठा afs_callback *cb = &vp->scb.callback;
	काष्ठा afs_vnode *vnode = vp->vnode;

	अगर (!afs_cb_is_broken(vp->cb_अवरोध_beक्रमe, vnode)) अणु
		vnode->cb_expires_at	= cb->expires_at;
		vnode->cb_server	= op->server;
		set_bit(AFS_VNODE_CB_PROMISED, &vnode->flags);
	पूर्ण
पूर्ण

/*
 * Apply the received status and callback to an inode all in the same critical
 * section to aव्योम races with afs_validate().
 */
व्योम afs_vnode_commit_status(काष्ठा afs_operation *op, काष्ठा afs_vnode_param *vp)
अणु
	काष्ठा afs_vnode *vnode = vp->vnode;

	_enter("");

	ग_लिखो_seqlock(&vnode->cb_lock);

	अगर (vp->scb.have_error) अणु
		/* A YFS server will वापस this from RemoveFile2 and AFS and
		 * YFS will वापस this from InlineBulkStatus.
		 */
		अगर (vp->scb.status.पात_code == VNOVNODE) अणु
			set_bit(AFS_VNODE_DELETED, &vnode->flags);
			clear_nlink(&vnode->vfs_inode);
			__afs_अवरोध_callback(vnode, afs_cb_अवरोध_क्रम_deleted);
			op->flags &= ~AFS_OPERATION_सूची_CONFLICT;
		पूर्ण
	पूर्ण अन्यथा अगर (vp->scb.have_status) अणु
		अगर (vp->speculative &&
		    (test_bit(AFS_VNODE_MODIFYING, &vnode->flags) ||
		     vp->dv_beक्रमe != vnode->status.data_version))
			/* Ignore the result of a speculative bulk status fetch
			 * अगर it splits around a modअगरication op, thereby
			 * appearing to regress the data version.
			 */
			जाओ out;
		afs_apply_status(op, vp);
		अगर (vp->scb.have_cb)
			afs_apply_callback(op, vp);
	पूर्ण अन्यथा अगर (vp->op_unlinked && !(op->flags & AFS_OPERATION_सूची_CONFLICT)) अणु
		drop_nlink(&vnode->vfs_inode);
		अगर (vnode->vfs_inode.i_nlink == 0) अणु
			set_bit(AFS_VNODE_DELETED, &vnode->flags);
			__afs_अवरोध_callback(vnode, afs_cb_अवरोध_क्रम_deleted);
		पूर्ण
	पूर्ण

out:
	ग_लिखो_sequnlock(&vnode->cb_lock);

	अगर (vp->scb.have_status)
		afs_cache_permit(vnode, op->key, vp->cb_अवरोध_beक्रमe, &vp->scb);
पूर्ण

अटल व्योम afs_fetch_status_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[op->fetch_status.which];
	काष्ठा afs_vnode *vnode = vp->vnode;
	पूर्णांक ret;

	अगर (vnode->vfs_inode.i_state & I_NEW) अणु
		ret = afs_inode_init_from_status(op, vp, vnode);
		op->error = ret;
		अगर (ret == 0)
			afs_cache_permit(vnode, op->key, vp->cb_अवरोध_beक्रमe, &vp->scb);
	पूर्ण अन्यथा अणु
		afs_vnode_commit_status(op, vp);
	पूर्ण
पूर्ण

स्थिर काष्ठा afs_operation_ops afs_fetch_status_operation = अणु
	.issue_afs_rpc	= afs_fs_fetch_status,
	.issue_yfs_rpc	= yfs_fs_fetch_status,
	.success	= afs_fetch_status_success,
	.पातed	= afs_check_क्रम_remote_deletion,
पूर्ण;

/*
 * Fetch file status from the volume.
 */
पूर्णांक afs_fetch_status(काष्ठा afs_vnode *vnode, काष्ठा key *key, bool is_new,
		     afs_access_t *_caller_access)
अणु
	काष्ठा afs_operation *op;

	_enter("%s,{%llx:%llu.%u,S=%lx}",
	       vnode->volume->name,
	       vnode->fid.vid, vnode->fid.vnode, vnode->fid.unique,
	       vnode->flags);

	op = afs_alloc_operation(key, vnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, vnode);

	op->nr_files	= 1;
	op->ops		= &afs_fetch_status_operation;
	afs_begin_vnode_operation(op);
	afs_रुको_क्रम_operation(op);

	अगर (_caller_access)
		*_caller_access = op->file[0].scb.status.caller_access;
	वापस afs_put_operation(op);
पूर्ण

/*
 * ilookup() comparator
 */
पूर्णांक afs_ilookup5_test_by_fid(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	काष्ठा afs_fid *fid = opaque;

	वापस (fid->vnode == vnode->fid.vnode &&
		fid->vnode_hi == vnode->fid.vnode_hi &&
		fid->unique == vnode->fid.unique);
पूर्ण

/*
 * iget5() comparator
 */
अटल पूर्णांक afs_iget5_test(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा afs_vnode_param *vp = opaque;
	//काष्ठा afs_vnode *vnode = AFS_FS_I(inode);

	वापस afs_ilookup5_test_by_fid(inode, &vp->fid);
पूर्ण

/*
 * iget5() inode initialiser
 */
अटल पूर्णांक afs_iget5_set(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा afs_vnode_param *vp = opaque;
	काष्ठा afs_super_info *as = AFS_FS_S(inode->i_sb);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);

	vnode->volume		= as->volume;
	vnode->fid		= vp->fid;

	/* YFS supports 96-bit vnode IDs, but Linux only supports
	 * 64-bit inode numbers.
	 */
	inode->i_ino		= vnode->fid.vnode;
	inode->i_generation	= vnode->fid.unique;
	वापस 0;
पूर्ण

/*
 * Get a cache cookie क्रम an inode.
 */
अटल व्योम afs_get_inode_cache(काष्ठा afs_vnode *vnode)
अणु
#अगर_घोषित CONFIG_AFS_FSCACHE
	काष्ठा अणु
		u32 vnode_id;
		u32 unique;
		u32 vnode_id_ext[2];	/* Allow क्रम a 96-bit key */
	पूर्ण __packed key;
	काष्ठा afs_vnode_cache_aux aux;

	अगर (vnode->status.type != AFS_FTYPE_खाता) अणु
		vnode->cache = शून्य;
		वापस;
	पूर्ण

	key.vnode_id		= vnode->fid.vnode;
	key.unique		= vnode->fid.unique;
	key.vnode_id_ext[0]	= vnode->fid.vnode >> 32;
	key.vnode_id_ext[1]	= vnode->fid.vnode_hi;
	aux.data_version	= vnode->status.data_version;

	vnode->cache = fscache_acquire_cookie(vnode->volume->cache,
					      &afs_vnode_cache_index_def,
					      &key, माप(key),
					      &aux, माप(aux),
					      vnode, vnode->status.size, true);
#पूर्ण_अगर
पूर्ण

/*
 * inode retrieval
 */
काष्ठा inode *afs_iget(काष्ठा afs_operation *op, काष्ठा afs_vnode_param *vp)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा super_block *sb = dvp->vnode->vfs_inode.i_sb;
	काष्ठा afs_vnode *vnode;
	काष्ठा inode *inode;
	पूर्णांक ret;

	_enter(",{%llx:%llu.%u},,", vp->fid.vid, vp->fid.vnode, vp->fid.unique);

	inode = iget5_locked(sb, vp->fid.vnode, afs_iget5_test, afs_iget5_set, vp);
	अगर (!inode) अणु
		_leave(" = -ENOMEM");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	vnode = AFS_FS_I(inode);

	_debug("GOT INODE %p { vl=%llx vn=%llx, u=%x }",
	       inode, vnode->fid.vid, vnode->fid.vnode, vnode->fid.unique);

	/* deal with an existing inode */
	अगर (!(inode->i_state & I_NEW)) अणु
		_leave(" = %p", inode);
		वापस inode;
	पूर्ण

	ret = afs_inode_init_from_status(op, vp, vnode);
	अगर (ret < 0)
		जाओ bad_inode;

	afs_get_inode_cache(vnode);

	/* success */
	clear_bit(AFS_VNODE_UNSET, &vnode->flags);
	unlock_new_inode(inode);
	_leave(" = %p", inode);
	वापस inode;

	/* failure */
bad_inode:
	iget_failed(inode);
	_leave(" = %d [bad]", ret);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक afs_iget5_set_root(काष्ठा inode *inode, व्योम *opaque)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(inode->i_sb);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);

	vnode->volume		= as->volume;
	vnode->fid.vid		= as->volume->vid,
	vnode->fid.vnode	= 1;
	vnode->fid.unique	= 1;
	inode->i_ino		= 1;
	inode->i_generation	= 1;
	वापस 0;
पूर्ण

/*
 * Set up the root inode क्रम a volume.  This is always vnode 1, unique 1 within
 * the volume.
 */
काष्ठा inode *afs_root_iget(काष्ठा super_block *sb, काष्ठा key *key)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(sb);
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode;
	काष्ठा inode *inode;
	पूर्णांक ret;

	_enter(",{%llx},,", as->volume->vid);

	inode = iget5_locked(sb, 1, शून्य, afs_iget5_set_root, शून्य);
	अगर (!inode) अणु
		_leave(" = -ENOMEM");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	_debug("GOT ROOT INODE %p { vl=%llx }", inode, as->volume->vid);

	BUG_ON(!(inode->i_state & I_NEW));

	vnode = AFS_FS_I(inode);
	vnode->cb_v_अवरोध = as->volume->cb_v_अवरोध,

	op = afs_alloc_operation(key, as->volume);
	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ error;
	पूर्ण

	afs_op_set_vnode(op, 0, vnode);

	op->nr_files	= 1;
	op->ops		= &afs_fetch_status_operation;
	ret = afs_करो_sync_operation(op);
	अगर (ret < 0)
		जाओ error;

	afs_get_inode_cache(vnode);

	clear_bit(AFS_VNODE_UNSET, &vnode->flags);
	unlock_new_inode(inode);
	_leave(" = %p", inode);
	वापस inode;

error:
	iget_failed(inode);
	_leave(" = %d [bad]", ret);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * mark the data attached to an inode as obsolete due to a ग_लिखो on the server
 * - might also want to ditch all the outstanding ग_लिखोs and dirty pages
 */
अटल व्योम afs_zap_data(काष्ठा afs_vnode *vnode)
अणु
	_enter("{%llx:%llu}", vnode->fid.vid, vnode->fid.vnode);

#अगर_घोषित CONFIG_AFS_FSCACHE
	fscache_invalidate(vnode->cache);
#पूर्ण_अगर

	/* nuke all the non-dirty pages that aren't locked, mapped or being
	 * written back in a regular file and completely discard the pages in a
	 * directory or symlink */
	अगर (S_ISREG(vnode->vfs_inode.i_mode))
		invalidate_remote_inode(&vnode->vfs_inode);
	अन्यथा
		invalidate_inode_pages2(vnode->vfs_inode.i_mapping);
पूर्ण

/*
 * Get the server reinit counter क्रम a vnode's current server.
 */
अटल bool afs_get_s_अवरोध_rcu(काष्ठा afs_vnode *vnode, अचिन्हित पूर्णांक *_s_अवरोध)
अणु
	काष्ठा afs_server_list *slist = rcu_dereference(vnode->volume->servers);
	काष्ठा afs_server *server;
	पूर्णांक i;

	क्रम (i = 0; i < slist->nr_servers; i++) अणु
		server = slist->servers[i].server;
		अगर (server == vnode->cb_server) अणु
			*_s_अवरोध = READ_ONCE(server->cb_s_अवरोध);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/*
 * Check the validity of a vnode/inode.
 */
bool afs_check_validity(काष्ठा afs_vnode *vnode)
अणु
	काष्ठा afs_volume *volume = vnode->volume;
	क्रमागत afs_cb_अवरोध_reason need_clear = afs_cb_अवरोध_no_अवरोध;
	समय64_t now = kसमय_get_real_seconds();
	bool valid;
	अचिन्हित पूर्णांक cb_अवरोध, cb_s_अवरोध, cb_v_अवरोध;
	पूर्णांक seq = 0;

	करो अणु
		पढ़ो_seqbegin_or_lock(&vnode->cb_lock, &seq);
		cb_v_अवरोध = READ_ONCE(volume->cb_v_अवरोध);
		cb_अवरोध = vnode->cb_अवरोध;

		अगर (test_bit(AFS_VNODE_CB_PROMISED, &vnode->flags) &&
		    afs_get_s_अवरोध_rcu(vnode, &cb_s_अवरोध)) अणु
			अगर (vnode->cb_s_अवरोध != cb_s_अवरोध ||
			    vnode->cb_v_अवरोध != cb_v_अवरोध) अणु
				vnode->cb_s_अवरोध = cb_s_अवरोध;
				vnode->cb_v_अवरोध = cb_v_अवरोध;
				need_clear = afs_cb_अवरोध_क्रम_vsअवरोध;
				valid = false;
			पूर्ण अन्यथा अगर (test_bit(AFS_VNODE_ZAP_DATA, &vnode->flags)) अणु
				need_clear = afs_cb_अवरोध_क्रम_zap;
				valid = false;
			पूर्ण अन्यथा अगर (vnode->cb_expires_at - 10 <= now) अणु
				need_clear = afs_cb_अवरोध_क्रम_lapsed;
				valid = false;
			पूर्ण अन्यथा अणु
				valid = true;
			पूर्ण
		पूर्ण अन्यथा अगर (test_bit(AFS_VNODE_DELETED, &vnode->flags)) अणु
			valid = true;
		पूर्ण अन्यथा अणु
			vnode->cb_v_अवरोध = cb_v_अवरोध;
			valid = false;
		पूर्ण

	पूर्ण जबतक (need_seqretry(&vnode->cb_lock, seq));

	करोne_seqretry(&vnode->cb_lock, seq);

	अगर (need_clear != afs_cb_अवरोध_no_अवरोध) अणु
		ग_लिखो_seqlock(&vnode->cb_lock);
		अगर (cb_अवरोध == vnode->cb_अवरोध)
			__afs_अवरोध_callback(vnode, need_clear);
		अन्यथा
			trace_afs_cb_miss(&vnode->fid, need_clear);
		ग_लिखो_sequnlock(&vnode->cb_lock);
		valid = false;
	पूर्ण

	वापस valid;
पूर्ण

/*
 * validate a vnode/inode
 * - there are several things we need to check
 *   - parent dir data changes (rm, सूची_हटाओ, नाम, सूची_गढ़ो, create, link,
 *     symlink)
 *   - parent dir metadata changed (security changes)
 *   - dentry data changed (ग_लिखो, truncate)
 *   - dentry metadata changed (security changes)
 */
पूर्णांक afs_validate(काष्ठा afs_vnode *vnode, काष्ठा key *key)
अणु
	bool valid;
	पूर्णांक ret;

	_enter("{v={%llx:%llu} fl=%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, vnode->flags,
	       key_serial(key));

	rcu_पढ़ो_lock();
	valid = afs_check_validity(vnode);
	rcu_पढ़ो_unlock();

	अगर (test_bit(AFS_VNODE_DELETED, &vnode->flags))
		clear_nlink(&vnode->vfs_inode);

	अगर (valid)
		जाओ valid;

	करोwn_ग_लिखो(&vnode->validate_lock);

	/* अगर the promise has expired, we need to check the server again to get
	 * a new promise - note that अगर the (parent) directory's metadata was
	 * changed then the security may be dअगरferent and we may no दीर्घer have
	 * access */
	अगर (!test_bit(AFS_VNODE_CB_PROMISED, &vnode->flags)) अणु
		_debug("not promised");
		ret = afs_fetch_status(vnode, key, false, शून्य);
		अगर (ret < 0) अणु
			अगर (ret == -ENOENT) अणु
				set_bit(AFS_VNODE_DELETED, &vnode->flags);
				ret = -ESTALE;
			पूर्ण
			जाओ error_unlock;
		पूर्ण
		_debug("new promise [fl=%lx]", vnode->flags);
	पूर्ण

	अगर (test_bit(AFS_VNODE_DELETED, &vnode->flags)) अणु
		_debug("file already deleted");
		ret = -ESTALE;
		जाओ error_unlock;
	पूर्ण

	/* अगर the vnode's data version number changed then its contents are
	 * dअगरferent */
	अगर (test_and_clear_bit(AFS_VNODE_ZAP_DATA, &vnode->flags))
		afs_zap_data(vnode);
	up_ग_लिखो(&vnode->validate_lock);
valid:
	_leave(" = 0");
	वापस 0;

error_unlock:
	up_ग_लिखो(&vnode->validate_lock);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * पढ़ो the attributes of an inode
 */
पूर्णांक afs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	पूर्णांक seq = 0;

	_enter("{ ino=%lu v=%u }", inode->i_ino, inode->i_generation);

	करो अणु
		पढ़ो_seqbegin_or_lock(&vnode->cb_lock, &seq);
		generic_fillattr(&init_user_ns, inode, stat);
		अगर (test_bit(AFS_VNODE_SILLY_DELETED, &vnode->flags) &&
		    stat->nlink > 0)
			stat->nlink -= 1;
	पूर्ण जबतक (need_seqretry(&vnode->cb_lock, seq));

	करोne_seqretry(&vnode->cb_lock, seq);
	वापस 0;
पूर्ण

/*
 * discard an AFS inode
 */
पूर्णांक afs_drop_inode(काष्ठा inode *inode)
अणु
	_enter("");

	अगर (test_bit(AFS_VNODE_PSEUDOसूची, &AFS_FS_I(inode)->flags))
		वापस generic_delete_inode(inode);
	अन्यथा
		वापस generic_drop_inode(inode);
पूर्ण

/*
 * clear an AFS inode
 */
व्योम afs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा afs_vnode *vnode;

	vnode = AFS_FS_I(inode);

	_enter("{%llx:%llu.%d}",
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique);

	_debug("CLEAR INODE %p", inode);

	ASSERTCMP(inode->i_ino, ==, vnode->fid.vnode);

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);

	जबतक (!list_empty(&vnode->wb_keys)) अणु
		काष्ठा afs_wb_key *wbk = list_entry(vnode->wb_keys.next,
						    काष्ठा afs_wb_key, vnode_link);
		list_del(&wbk->vnode_link);
		afs_put_wb_key(wbk);
	पूर्ण

#अगर_घोषित CONFIG_AFS_FSCACHE
	अणु
		काष्ठा afs_vnode_cache_aux aux;

		aux.data_version = vnode->status.data_version;
		fscache_relinquish_cookie(vnode->cache, &aux,
					  test_bit(AFS_VNODE_DELETED, &vnode->flags));
		vnode->cache = शून्य;
	पूर्ण
#पूर्ण_अगर

	afs_prune_wb_keys(vnode);
	afs_put_permits(rcu_access_poपूर्णांकer(vnode->permit_cache));
	key_put(vnode->silly_key);
	vnode->silly_key = शून्य;
	key_put(vnode->lock_key);
	vnode->lock_key = शून्य;
	_leave("");
पूर्ण

अटल व्योम afs_setattr_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा inode *inode = &vp->vnode->vfs_inode;
	loff_t old_i_size = i_size_पढ़ो(inode);

	op->setattr.old_i_size = old_i_size;
	afs_vnode_commit_status(op, vp);
	/* inode->i_size has now been changed. */

	अगर (op->setattr.attr->ia_valid & ATTR_SIZE) अणु
		loff_t size = op->setattr.attr->ia_size;
		अगर (size > old_i_size)
			pagecache_isize_extended(inode, old_i_size, size);
	पूर्ण
पूर्ण

अटल व्योम afs_setattr_edit_file(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा inode *inode = &vp->vnode->vfs_inode;

	अगर (op->setattr.attr->ia_valid & ATTR_SIZE) अणु
		loff_t size = op->setattr.attr->ia_size;
		loff_t i_size = op->setattr.old_i_size;

		अगर (size < i_size)
			truncate_pagecache(inode, size);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_setattr_operation = अणु
	.issue_afs_rpc	= afs_fs_setattr,
	.issue_yfs_rpc	= yfs_fs_setattr,
	.success	= afs_setattr_success,
	.edit_dir	= afs_setattr_edit_file,
पूर्ण;

/*
 * set the attributes of an inode
 */
पूर्णांक afs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		काष्ठा iattr *attr)
अणु
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(dentry));
	पूर्णांक ret;

	_enter("{%llx:%llu},{n=%pd},%x",
	       vnode->fid.vid, vnode->fid.vnode, dentry,
	       attr->ia_valid);

	अगर (!(attr->ia_valid & (ATTR_SIZE | ATTR_MODE | ATTR_UID | ATTR_GID |
				ATTR_MTIME | ATTR_MTIME_SET | ATTR_TIMES_SET |
				ATTR_TOUCH))) अणु
		_leave(" = 0 [unsupported]");
		वापस 0;
	पूर्ण

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		अगर (!S_ISREG(vnode->vfs_inode.i_mode))
			वापस -EISसूची;

		ret = inode_newsize_ok(&vnode->vfs_inode, attr->ia_size);
		अगर (ret)
			वापस ret;

		अगर (attr->ia_size == i_size_पढ़ो(&vnode->vfs_inode))
			attr->ia_valid &= ~ATTR_SIZE;
	पूर्ण

	/* flush any dirty data outstanding on a regular file */
	अगर (S_ISREG(vnode->vfs_inode.i_mode))
		filemap_ग_लिखो_and_रुको(vnode->vfs_inode.i_mapping);

	/* Prevent any new ग_लिखोbacks from starting whilst we करो this. */
	करोwn_ग_लिखो(&vnode->validate_lock);

	op = afs_alloc_operation(((attr->ia_valid & ATTR_खाता) ?
				  afs_file_key(attr->ia_file) : शून्य),
				 vnode->volume);
	अगर (IS_ERR(op)) अणु
		ret = PTR_ERR(op);
		जाओ out_unlock;
	पूर्ण

	afs_op_set_vnode(op, 0, vnode);
	op->setattr.attr = attr;

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		op->file[0].dv_delta = 1;
		op->file[0].set_size = true;
	पूर्ण
	op->स_समय = attr->ia_स_समय;
	op->file[0].update_स_समय = 1;
	op->file[0].modअगरication = true;

	op->ops = &afs_setattr_operation;
	ret = afs_करो_sync_operation(op);

out_unlock:
	up_ग_लिखो(&vnode->validate_lock);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण
