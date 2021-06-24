<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/nfs/unlink.c
 *
 * nfs sillydelete handling
 *
 */

#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/dcache.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/namei.h>
#समावेश <linux/fsnotअगरy.h>

#समावेश "internal.h"
#समावेश "nfs4_fs.h"
#समावेश "iostat.h"
#समावेश "delegation.h"

#समावेश "nfstrace.h"

/**
 * nfs_मुक्त_unlinkdata - release data from a sillydelete operation.
 * @data: poपूर्णांकer to unlink काष्ठाure.
 */
अटल व्योम
nfs_मुक्त_unlinkdata(काष्ठा nfs_unlinkdata *data)
अणु
	put_cred(data->cred);
	kमुक्त(data->args.name.name);
	kमुक्त(data);
पूर्ण

/**
 * nfs_async_unlink_करोne - Sillydelete post-processing
 * @task: rpc_task of the sillydelete
 * @calldata: poपूर्णांकer to nfs_unlinkdata
 *
 * Do the directory attribute update.
 */
अटल व्योम nfs_async_unlink_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_unlinkdata *data = calldata;
	काष्ठा inode *dir = d_inode(data->dentry->d_parent);

	trace_nfs_sillyनाम_unlink(data, task->tk_status);
	अगर (!NFS_PROTO(dir)->unlink_करोne(task, dir))
		rpc_restart_call_prepare(task);
पूर्ण

/**
 * nfs_async_unlink_release - Release the sillydelete data.
 * @calldata: काष्ठा nfs_unlinkdata to release
 *
 * We need to call nfs_put_unlinkdata as a 'tk_release' task since the
 * rpc_task would be मुक्तd too.
 */
अटल व्योम nfs_async_unlink_release(व्योम *calldata)
अणु
	काष्ठा nfs_unlinkdata	*data = calldata;
	काष्ठा dentry *dentry = data->dentry;
	काष्ठा super_block *sb = dentry->d_sb;

	up_पढ़ो_non_owner(&NFS_I(d_inode(dentry->d_parent))->सूची_हटाओ_sem);
	d_lookup_करोne(dentry);
	nfs_मुक्त_unlinkdata(data);
	dput(dentry);
	nfs_sb_deactive(sb);
पूर्ण

अटल व्योम nfs_unlink_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_unlinkdata *data = calldata;
	काष्ठा inode *dir = d_inode(data->dentry->d_parent);
	NFS_PROTO(dir)->unlink_rpc_prepare(task, data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs_unlink_ops = अणु
	.rpc_call_करोne = nfs_async_unlink_करोne,
	.rpc_release = nfs_async_unlink_release,
	.rpc_call_prepare = nfs_unlink_prepare,
पूर्ण;

अटल व्योम nfs_करो_call_unlink(काष्ठा inode *inode, काष्ठा nfs_unlinkdata *data)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_argp = &data->args,
		.rpc_resp = &data->res,
		.rpc_cred = data->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_message = &msg,
		.callback_ops = &nfs_unlink_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;
	काष्ठा rpc_task *task;
	काष्ठा inode *dir = d_inode(data->dentry->d_parent);
	nfs_sb_active(dir->i_sb);
	data->args.fh = NFS_FH(dir);
	nfs_fattr_init(data->res.dir_attr);

	NFS_PROTO(dir)->unlink_setup(&msg, data->dentry, inode);

	task_setup_data.rpc_client = NFS_CLIENT(dir);
	task = rpc_run_task(&task_setup_data);
	अगर (!IS_ERR(task))
		rpc_put_task_async(task);
पूर्ण

अटल पूर्णांक nfs_call_unlink(काष्ठा dentry *dentry, काष्ठा inode *inode, काष्ठा nfs_unlinkdata *data)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा dentry *alias;

	करोwn_पढ़ो_non_owner(&NFS_I(dir)->सूची_हटाओ_sem);
	alias = d_alloc_parallel(dentry->d_parent, &data->args.name, &data->wq);
	अगर (IS_ERR(alias)) अणु
		up_पढ़ो_non_owner(&NFS_I(dir)->सूची_हटाओ_sem);
		वापस 0;
	पूर्ण
	अगर (!d_in_lookup(alias)) अणु
		पूर्णांक ret;
		व्योम *devname_garbage = शून्य;

		/*
		 * Hey, we raced with lookup... See अगर we need to transfer
		 * the sillyनाम inक्रमmation to the aliased dentry.
		 */
		spin_lock(&alias->d_lock);
		अगर (d_really_is_positive(alias) &&
		    !(alias->d_flags & DCACHE_NFSFS_RENAMED)) अणु
			devname_garbage = alias->d_fsdata;
			alias->d_fsdata = data;
			alias->d_flags |= DCACHE_NFSFS_RENAMED;
			ret = 1;
		पूर्ण अन्यथा
			ret = 0;
		spin_unlock(&alias->d_lock);
		dput(alias);
		up_पढ़ो_non_owner(&NFS_I(dir)->सूची_हटाओ_sem);
		/*
		 * If we'd displaced old cached devname, मुक्त it.  At that
		 * poपूर्णांक dentry is definitely not a root, so we won't need
		 * that anymore.
		 */
		kमुक्त(devname_garbage);
		वापस ret;
	पूर्ण
	data->dentry = alias;
	nfs_करो_call_unlink(inode, data);
	वापस 1;
पूर्ण

/**
 * nfs_async_unlink - asynchronous unlinking of a file
 * @dentry: parent directory of dentry
 * @name: name of dentry to unlink
 */
अटल पूर्णांक
nfs_async_unlink(काष्ठा dentry *dentry, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs_unlinkdata *data;
	पूर्णांक status = -ENOMEM;
	व्योम *devname_garbage = शून्य;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		जाओ out;
	data->args.name.name = kstrdup(name->name, GFP_KERNEL);
	अगर (!data->args.name.name)
		जाओ out_मुक्त;
	data->args.name.len = name->len;

	data->cred = get_current_cred();
	data->res.dir_attr = &data->dir_attr;
	init_रुकोqueue_head(&data->wq);

	status = -EBUSY;
	spin_lock(&dentry->d_lock);
	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		जाओ out_unlock;
	dentry->d_flags |= DCACHE_NFSFS_RENAMED;
	devname_garbage = dentry->d_fsdata;
	dentry->d_fsdata = data;
	spin_unlock(&dentry->d_lock);
	/*
	 * If we'd displaced old cached devname, मुक्त it.  At that
	 * poपूर्णांक dentry is definitely not a root, so we won't need
	 * that anymore.
	 */
	kमुक्त(devname_garbage);
	वापस 0;
out_unlock:
	spin_unlock(&dentry->d_lock);
	put_cred(data->cred);
	kमुक्त(data->args.name.name);
out_मुक्त:
	kमुक्त(data);
out:
	वापस status;
पूर्ण

/**
 * nfs_complete_unlink - Initialize completion of the sillydelete
 * @dentry: dentry to delete
 * @inode: inode
 *
 * Since we're most likely to be called by dentry_iput(), we
 * only use the dentry to find the sillydelete. We then copy the name
 * पूर्णांकo the qstr.
 */
व्योम
nfs_complete_unlink(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा nfs_unlinkdata	*data;

	spin_lock(&dentry->d_lock);
	dentry->d_flags &= ~DCACHE_NFSFS_RENAMED;
	data = dentry->d_fsdata;
	dentry->d_fsdata = शून्य;
	spin_unlock(&dentry->d_lock);

	अगर (NFS_STALE(inode) || !nfs_call_unlink(dentry, inode, data))
		nfs_मुक्त_unlinkdata(data);
पूर्ण

/* Cancel a queued async unlink. Called when a sillyनाम run fails. */
अटल व्योम
nfs_cancel_async_unlink(काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED) अणु
		काष्ठा nfs_unlinkdata *data = dentry->d_fsdata;

		dentry->d_flags &= ~DCACHE_NFSFS_RENAMED;
		dentry->d_fsdata = शून्य;
		spin_unlock(&dentry->d_lock);
		nfs_मुक्त_unlinkdata(data);
		वापस;
	पूर्ण
	spin_unlock(&dentry->d_lock);
पूर्ण

/**
 * nfs_async_नाम_करोne - Sillyनाम post-processing
 * @task: rpc_task of the sillyनाम
 * @calldata: nfs_नामdata क्रम the sillyनाम
 *
 * Do the directory attribute updates and the d_move
 */
अटल व्योम nfs_async_नाम_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_नामdata *data = calldata;
	काष्ठा inode *old_dir = data->old_dir;
	काष्ठा inode *new_dir = data->new_dir;
	काष्ठा dentry *old_dentry = data->old_dentry;

	trace_nfs_sillyनाम_नाम(old_dir, old_dentry,
			new_dir, data->new_dentry, task->tk_status);
	अगर (!NFS_PROTO(old_dir)->नाम_करोne(task, old_dir, new_dir)) अणु
		rpc_restart_call_prepare(task);
		वापस;
	पूर्ण

	अगर (data->complete)
		data->complete(task, data);
पूर्ण

/**
 * nfs_async_नाम_release - Release the sillyनाम data.
 * @calldata: the काष्ठा nfs_नामdata to be released
 */
अटल व्योम nfs_async_नाम_release(व्योम *calldata)
अणु
	काष्ठा nfs_नामdata	*data = calldata;
	काष्ठा super_block *sb = data->old_dir->i_sb;

	अगर (d_really_is_positive(data->old_dentry))
		nfs_mark_क्रम_revalidate(d_inode(data->old_dentry));

	/* The result of the नाम is unknown. Play it safe by
	 * क्रमcing a new lookup */
	अगर (data->cancelled) अणु
		spin_lock(&data->old_dir->i_lock);
		nfs_क्रमce_lookup_revalidate(data->old_dir);
		spin_unlock(&data->old_dir->i_lock);
		अगर (data->new_dir != data->old_dir) अणु
			spin_lock(&data->new_dir->i_lock);
			nfs_क्रमce_lookup_revalidate(data->new_dir);
			spin_unlock(&data->new_dir->i_lock);
		पूर्ण
	पूर्ण

	dput(data->old_dentry);
	dput(data->new_dentry);
	iput(data->old_dir);
	iput(data->new_dir);
	nfs_sb_deactive(sb);
	put_cred(data->cred);
	kमुक्त(data);
पूर्ण

अटल व्योम nfs_नाम_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs_नामdata *data = calldata;
	NFS_PROTO(data->old_dir)->नाम_rpc_prepare(task, data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs_नाम_ops = अणु
	.rpc_call_करोne = nfs_async_नाम_करोne,
	.rpc_release = nfs_async_नाम_release,
	.rpc_call_prepare = nfs_नाम_prepare,
पूर्ण;

/**
 * nfs_async_नाम - perक्रमm an asynchronous नाम operation
 * @old_dir: directory that currently holds the dentry to be नामd
 * @new_dir: target directory क्रम the नाम
 * @old_dentry: original dentry to be नामd
 * @new_dentry: dentry to which the old_dentry should be नामd
 * @complete: Function to run on successful completion
 *
 * It's expected that valid references to the dentries and inodes are held
 */
काष्ठा rpc_task *
nfs_async_नाम(काष्ठा inode *old_dir, काष्ठा inode *new_dir,
		 काष्ठा dentry *old_dentry, काष्ठा dentry *new_dentry,
		 व्योम (*complete)(काष्ठा rpc_task *, काष्ठा nfs_नामdata *))
अणु
	काष्ठा nfs_नामdata *data;
	काष्ठा rpc_message msg = अणु पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_message = &msg,
		.callback_ops = &nfs_नाम_ops,
		.workqueue = nfsiod_workqueue,
		.rpc_client = NFS_CLIENT(old_dir),
		.flags = RPC_TASK_ASYNC | RPC_TASK_CRED_NOREF,
	पूर्ण;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस ERR_PTR(-ENOMEM);
	task_setup_data.callback_data = data;

	data->cred = get_current_cred();

	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	msg.rpc_cred = data->cred;

	/* set up nfs_नामdata */
	data->old_dir = old_dir;
	ihold(old_dir);
	data->new_dir = new_dir;
	ihold(new_dir);
	data->old_dentry = dget(old_dentry);
	data->new_dentry = dget(new_dentry);
	nfs_fattr_init(&data->old_fattr);
	nfs_fattr_init(&data->new_fattr);
	data->complete = complete;

	/* set up nfs_नामargs */
	data->args.old_dir = NFS_FH(old_dir);
	data->args.old_name = &old_dentry->d_name;
	data->args.new_dir = NFS_FH(new_dir);
	data->args.new_name = &new_dentry->d_name;

	/* set up nfs_नामres */
	data->res.old_fattr = &data->old_fattr;
	data->res.new_fattr = &data->new_fattr;

	nfs_sb_active(old_dir->i_sb);

	NFS_PROTO(data->old_dir)->नाम_setup(&msg, old_dentry, new_dentry);

	वापस rpc_run_task(&task_setup_data);
पूर्ण

/*
 * Perक्रमm tasks needed when a sillyनाम is करोne such as cancelling the
 * queued async unlink अगर it failed.
 */
अटल व्योम
nfs_complete_sillyनाम(काष्ठा rpc_task *task, काष्ठा nfs_नामdata *data)
अणु
	काष्ठा dentry *dentry = data->old_dentry;

	अगर (task->tk_status != 0) अणु
		nfs_cancel_async_unlink(dentry);
		वापस;
	पूर्ण
पूर्ण

#घोषणा SILLYNAME_PREFIX ".nfs"
#घोषणा SILLYNAME_PREFIX_LEN ((अचिन्हित)माप(SILLYNAME_PREFIX) - 1)
#घोषणा SILLYNAME_खाताID_LEN ((अचिन्हित)माप(u64) << 1)
#घोषणा SILLYNAME_COUNTER_LEN ((अचिन्हित)माप(अचिन्हित पूर्णांक) << 1)
#घोषणा SILLYNAME_LEN (SILLYNAME_PREFIX_LEN + \
		SILLYNAME_खाताID_LEN + \
		SILLYNAME_COUNTER_LEN)

/**
 * nfs_sillyनाम - Perक्रमm a silly-नाम of a dentry
 * @dir: inode of directory that contains dentry
 * @dentry: dentry to be sillyनामd
 *
 * NFSv2/3 is stateless and the server करोesn't know when the client is
 * holding a file खोलो. To prevent application problems when a file is
 * unlinked जबतक it's still खोलो, the client perक्रमms a "silly-rename".
 * That is, it नामs the file to a hidden file in the same directory,
 * and only perक्रमms the unlink once the last reference to it is put.
 *
 * The final cleanup is करोne during dentry_iput.
 *
 * (Note: NFSv4 is stateful, and has खोलोs, so in theory an NFSv4 server
 * could take responsibility क्रम keeping खोलो files referenced.  The server
 * would also need to ensure that खोलोed-but-deleted files were kept over
 * reboots.  However, we may not assume a server करोes so.  (RFC 5661
 * करोes provide an OPEN4_RESULT_PRESERVE_UNLINKED flag that a server can
 * use to advertise that it करोes this; some day we may take advantage of
 * it.))
 */
पूर्णांक
nfs_sillyनाम(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	अटल अचिन्हित पूर्णांक sillycounter;
	अचिन्हित अक्षर silly[SILLYNAME_LEN + 1];
	अचिन्हित दीर्घ दीर्घ fileid;
	काष्ठा dentry *sdentry;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा rpc_task *task;
	पूर्णांक            error = -EBUSY;

	dfprपूर्णांकk(VFS, "NFS: silly-rename(%pd2, ct=%d)\n",
		dentry, d_count(dentry));
	nfs_inc_stats(dir, NFSIOS_SILLYRENAME);

	/*
	 * We करोn't allow a dentry to be silly-नामd twice.
	 */
	अगर (dentry->d_flags & DCACHE_NFSFS_RENAMED)
		जाओ out;

	fileid = NFS_खाताID(d_inode(dentry));

	sdentry = शून्य;
	करो अणु
		पूर्णांक slen;
		dput(sdentry);
		sillycounter++;
		slen = scnम_लिखो(silly, माप(silly),
				SILLYNAME_PREFIX "%0*llx%0*x",
				SILLYNAME_खाताID_LEN, fileid,
				SILLYNAME_COUNTER_LEN, sillycounter);

		dfprपूर्णांकk(VFS, "NFS: trying to rename %pd to %s\n",
				dentry, silly);

		sdentry = lookup_one_len(silly, dentry->d_parent, slen);
		/*
		 * N.B. Better to वापस EBUSY here ... it could be
		 * dangerous to delete the file जबतक it's in use.
		 */
		अगर (IS_ERR(sdentry))
			जाओ out;
	पूर्ण जबतक (d_inode(sdentry) != शून्य); /* need negative lookup */

	ihold(inode);

	/* queue unlink first. Can't करो this from rpc_release as it
	 * has to allocate memory
	 */
	error = nfs_async_unlink(dentry, &sdentry->d_name);
	अगर (error)
		जाओ out_dput;

	/* run the नाम task, unकरो unlink अगर it fails */
	task = nfs_async_नाम(dir, dir, dentry, sdentry,
					nfs_complete_sillyनाम);
	अगर (IS_ERR(task)) अणु
		error = -EBUSY;
		nfs_cancel_async_unlink(dentry);
		जाओ out_dput;
	पूर्ण

	/* रुको क्रम the RPC task to complete, unless a SIGKILL पूर्णांकervenes */
	error = rpc_रुको_क्रम_completion_task(task);
	अगर (error == 0)
		error = task->tk_status;
	चयन (error) अणु
	हाल 0:
		/* The नाम succeeded */
		nfs_set_verअगरier(dentry, nfs_save_change_attribute(dir));
		spin_lock(&inode->i_lock);
		NFS_I(inode)->attr_gencount = nfs_inc_attr_generation_counter();
		nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE |
						     NFS_INO_INVALID_CTIME |
						     NFS_INO_REVAL_FORCED);
		spin_unlock(&inode->i_lock);
		d_move(dentry, sdentry);
		अवरोध;
	हाल -ERESTARTSYS:
		/* The result of the नाम is unknown. Play it safe by
		 * क्रमcing a new lookup */
		d_drop(dentry);
		d_drop(sdentry);
	पूर्ण
	rpc_put_task(task);
out_dput:
	iput(inode);
	dput(sdentry);
out:
	वापस error;
पूर्ण
