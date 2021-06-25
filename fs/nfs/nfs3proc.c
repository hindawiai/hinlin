<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/nfs/nfs3proc.c
 *
 *  Client-side NFSv3 procedures stubs.
 *
 *  Copyright (C) 1997, Olaf Kirch
 */

#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/slab.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/xattr.h>

#समावेश "iostat.h"
#समावेश "internal.h"
#समावेश "nfs3_fs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PROC

/* A wrapper to handle the EJUKEBOX error messages */
अटल पूर्णांक
nfs3_rpc_wrapper(काष्ठा rpc_clnt *clnt, काष्ठा rpc_message *msg, पूर्णांक flags)
अणु
	पूर्णांक res;
	करो अणु
		res = rpc_call_sync(clnt, msg, flags);
		अगर (res != -EJUKEBOX)
			अवरोध;
		मुक्तzable_schedule_समयout_समाप्तable_unsafe(NFS_JUKEBOX_RETRY_TIME);
		res = -ERESTARTSYS;
	पूर्ण जबतक (!fatal_संकेत_pending(current));
	वापस res;
पूर्ण

#घोषणा rpc_call_sync(clnt, msg, flags)	nfs3_rpc_wrapper(clnt, msg, flags)

अटल पूर्णांक
nfs3_async_handle_jukebox(काष्ठा rpc_task *task, काष्ठा inode *inode)
अणु
	अगर (task->tk_status != -EJUKEBOX)
		वापस 0;
	अगर (task->tk_status == -EJUKEBOX)
		nfs_inc_stats(inode, NFSIOS_DELAY);
	task->tk_status = 0;
	rpc_restart_call(task);
	rpc_delay(task, NFS_JUKEBOX_RETRY_TIME);
	वापस 1;
पूर्ण

अटल पूर्णांक
करो_proc_get_root(काष्ठा rpc_clnt *client, काष्ठा nfs_fh *fhandle,
		 काष्ठा nfs_fsinfo *info)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_FSINFO],
		.rpc_argp	= fhandle,
		.rpc_resp	= info,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("%s: call  fsinfo\n", __func__);
	nfs_fattr_init(info->fattr);
	status = rpc_call_sync(client, &msg, 0);
	dprपूर्णांकk("%s: reply fsinfo: %d\n", __func__, status);
	अगर (status == 0 && !(info->fattr->valid & NFS_ATTR_FATTR)) अणु
		msg.rpc_proc = &nfs3_procedures[NFS3PROC_GETATTR];
		msg.rpc_resp = info->fattr;
		status = rpc_call_sync(client, &msg, 0);
		dprपूर्णांकk("%s: reply getattr: %d\n", __func__, status);
	पूर्ण
	वापस status;
पूर्ण

/*
 * Bare-bones access to getattr: this is क्रम nfs_get_root/nfs_get_sb
 */
अटल पूर्णांक
nfs3_proc_get_root(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		   काष्ठा nfs_fsinfo *info)
अणु
	पूर्णांक	status;

	status = करो_proc_get_root(server->client, fhandle, info);
	अगर (status && server->nfs_client->cl_rpcclient != server->client)
		status = करो_proc_get_root(server->nfs_client->cl_rpcclient, fhandle, info);
	वापस status;
पूर्ण

/*
 * One function क्रम each procedure in the NFS protocol.
 */
अटल पूर्णांक
nfs3_proc_getattr(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label,
		काष्ठा inode *inode)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_GETATTR],
		.rpc_argp	= fhandle,
		.rpc_resp	= fattr,
	पूर्ण;
	पूर्णांक	status;
	अचिन्हित लघु task_flags = 0;

	/* Is this is an attribute revalidation, subject to softreval? */
	अगर (inode && (server->flags & NFS_MOUNT_SOFTREVAL))
		task_flags |= RPC_TASK_TIMEOUT;

	dprपूर्णांकk("NFS call  getattr\n");
	nfs_fattr_init(fattr);
	status = rpc_call_sync(server->client, &msg, task_flags);
	dprपूर्णांकk("NFS reply getattr: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_setattr(काष्ठा dentry *dentry, काष्ठा nfs_fattr *fattr,
			काष्ठा iattr *sattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा nfs3_sattrargs	arg = अणु
		.fh		= NFS_FH(inode),
		.sattr		= sattr,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_SETATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= fattr,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("NFS call  setattr\n");
	अगर (sattr->ia_valid & ATTR_खाता)
		msg.rpc_cred = nfs_file_cred(sattr->ia_file);
	nfs_fattr_init(fattr);
	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	अगर (status == 0) अणु
		nfs_setattr_update_inode(inode, sattr, fattr);
		अगर (NFS_I(inode)->cache_validity & NFS_INO_INVALID_ACL)
			nfs_zap_acl_cache(inode);
	पूर्ण
	dprपूर्णांकk("NFS reply setattr: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
__nfs3_proc_lookup(काष्ठा inode *dir, स्थिर अक्षर *name, माप_प्रकार len,
		   काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr,
		   अचिन्हित लघु task_flags)
अणु
	काष्ठा nfs3_diropargs	arg = अणु
		.fh		= NFS_FH(dir),
		.name		= name,
		.len		= len
	पूर्ण;
	काष्ठा nfs3_diropres	res = अणु
		.fh		= fhandle,
		.fattr		= fattr
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_LOOKUP],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक			status;

	res.dir_attr = nfs_alloc_fattr();
	अगर (res.dir_attr == शून्य)
		वापस -ENOMEM;

	nfs_fattr_init(fattr);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, task_flags);
	nfs_refresh_inode(dir, res.dir_attr);
	अगर (status >= 0 && !(fattr->valid & NFS_ATTR_FATTR)) अणु
		msg.rpc_proc = &nfs3_procedures[NFS3PROC_GETATTR];
		msg.rpc_argp = fhandle;
		msg.rpc_resp = fattr;
		status = rpc_call_sync(NFS_CLIENT(dir), &msg, task_flags);
	पूर्ण
	nfs_मुक्त_fattr(res.dir_attr);
	dprपूर्णांकk("NFS reply lookup: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
		 काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr,
		 काष्ठा nfs4_label *label)
अणु
	अचिन्हित लघु task_flags = 0;

	/* Is this is an attribute revalidation, subject to softreval? */
	अगर (nfs_lookup_is_soft_revalidate(dentry))
		task_flags |= RPC_TASK_TIMEOUT;

	dprपूर्णांकk("NFS call  lookup %pd2\n", dentry);
	वापस __nfs3_proc_lookup(dir, dentry->d_name.name,
				  dentry->d_name.len, fhandle, fattr,
				  task_flags);
पूर्ण

अटल पूर्णांक nfs3_proc_lookupp(काष्ठा inode *inode, काष्ठा nfs_fh *fhandle,
			     काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label)
अणु
	स्थिर अक्षर करोtकरोt[] = "..";
	स्थिर माप_प्रकार len = म_माप(करोtकरोt);
	अचिन्हित लघु task_flags = 0;

	अगर (NFS_SERVER(inode)->flags & NFS_MOUNT_SOFTREVAL)
		task_flags |= RPC_TASK_TIMEOUT;

	वापस __nfs3_proc_lookup(inode, करोtकरोt, len, fhandle, fattr,
				  task_flags);
पूर्ण

अटल पूर्णांक nfs3_proc_access(काष्ठा inode *inode, काष्ठा nfs_access_entry *entry)
अणु
	काष्ठा nfs3_accessargs	arg = अणु
		.fh		= NFS_FH(inode),
		.access		= entry->mask,
	पूर्ण;
	काष्ठा nfs3_accessres	res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_ACCESS],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
		.rpc_cred	= entry->cred,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  access\n");
	res.fattr = nfs_alloc_fattr();
	अगर (res.fattr == शून्य)
		जाओ out;

	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	nfs_refresh_inode(inode, res.fattr);
	अगर (status == 0)
		nfs_access_set_mask(entry, res.access);
	nfs_मुक्त_fattr(res.fattr);
out:
	dprपूर्णांकk("NFS reply access: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs3_proc_पढ़ोlink(काष्ठा inode *inode, काष्ठा page *page,
		अचिन्हित पूर्णांक pgbase, अचिन्हित पूर्णांक pglen)
अणु
	काष्ठा nfs_fattr	*fattr;
	काष्ठा nfs3_पढ़ोlinkargs args = अणु
		.fh		= NFS_FH(inode),
		.pgbase		= pgbase,
		.pglen		= pglen,
		.pages		= &page
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_READLINK],
		.rpc_argp	= &args,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  readlink\n");
	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य)
		जाओ out;
	msg.rpc_resp = fattr;

	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	nfs_refresh_inode(inode, fattr);
	nfs_मुक्त_fattr(fattr);
out:
	dprपूर्णांकk("NFS reply readlink: %d\n", status);
	वापस status;
पूर्ण

काष्ठा nfs3_createdata अणु
	काष्ठा rpc_message msg;
	जोड़ अणु
		काष्ठा nfs3_createargs create;
		काष्ठा nfs3_सूची_गढ़ोargs सूची_गढ़ो;
		काष्ठा nfs3_symlinkargs symlink;
		काष्ठा nfs3_mknodargs mknod;
	पूर्ण arg;
	काष्ठा nfs3_diropres res;
	काष्ठा nfs_fh fh;
	काष्ठा nfs_fattr fattr;
	काष्ठा nfs_fattr dir_attr;
पूर्ण;

अटल काष्ठा nfs3_createdata *nfs3_alloc_createdata(व्योम)
अणु
	काष्ठा nfs3_createdata *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (data != शून्य) अणु
		data->msg.rpc_argp = &data->arg;
		data->msg.rpc_resp = &data->res;
		data->res.fh = &data->fh;
		data->res.fattr = &data->fattr;
		data->res.dir_attr = &data->dir_attr;
		nfs_fattr_init(data->res.fattr);
		nfs_fattr_init(data->res.dir_attr);
	पूर्ण
	वापस data;
पूर्ण

अटल काष्ठा dentry *
nfs3_करो_create(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा nfs3_createdata *data)
अणु
	पूर्णांक status;

	status = rpc_call_sync(NFS_CLIENT(dir), &data->msg, 0);
	nfs_post_op_update_inode(dir, data->res.dir_attr);
	अगर (status != 0)
		वापस ERR_PTR(status);

	वापस nfs_add_or_obtain(dentry, data->res.fh, data->res.fattr, शून्य);
पूर्ण

अटल व्योम nfs3_मुक्त_createdata(काष्ठा nfs3_createdata *data)
अणु
	kमुक्त(data);
पूर्ण

/*
 * Create a regular file.
 */
अटल पूर्णांक
nfs3_proc_create(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr,
		 पूर्णांक flags)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	काष्ठा nfs3_createdata *data;
	काष्ठा dentry *d_alias;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  create %pd\n", dentry);

	data = nfs3_alloc_createdata();
	अगर (data == शून्य)
		जाओ out;

	data->msg.rpc_proc = &nfs3_procedures[NFS3PROC_CREATE];
	data->arg.create.fh = NFS_FH(dir);
	data->arg.create.name = dentry->d_name.name;
	data->arg.create.len = dentry->d_name.len;
	data->arg.create.sattr = sattr;

	data->arg.create.createmode = NFS3_CREATE_UNCHECKED;
	अगर (flags & O_EXCL) अणु
		data->arg.create.createmode  = NFS3_CREATE_EXCLUSIVE;
		data->arg.create.verअगरier[0] = cpu_to_be32(jअगरfies);
		data->arg.create.verअगरier[1] = cpu_to_be32(current->pid);
	पूर्ण

	status = posix_acl_create(dir, &sattr->ia_mode, &शेष_acl, &acl);
	अगर (status)
		जाओ out;

	क्रम (;;) अणु
		d_alias = nfs3_करो_create(dir, dentry, data);
		status = PTR_ERR_OR_ZERO(d_alias);

		अगर (status != -ENOTSUPP)
			अवरोध;
		/* If the server करोesn't support the exclusive creation
		 * semantics, try again with simple 'guarded' mode. */
		चयन (data->arg.create.createmode) अणु
			हाल NFS3_CREATE_EXCLUSIVE:
				data->arg.create.createmode = NFS3_CREATE_GUARDED;
				अवरोध;

			हाल NFS3_CREATE_GUARDED:
				data->arg.create.createmode = NFS3_CREATE_UNCHECKED;
				अवरोध;

			हाल NFS3_CREATE_UNCHECKED:
				जाओ out;
		पूर्ण
		nfs_fattr_init(data->res.dir_attr);
		nfs_fattr_init(data->res.fattr);
	पूर्ण

	अगर (status != 0)
		जाओ out_release_acls;

	अगर (d_alias)
		dentry = d_alias;

	/* When we created the file with exclusive semantics, make
	 * sure we set the attributes afterwards. */
	अगर (data->arg.create.createmode == NFS3_CREATE_EXCLUSIVE) अणु
		dprपूर्णांकk("NFS call  setattr (post-create)\n");

		अगर (!(sattr->ia_valid & ATTR_ATIME_SET))
			sattr->ia_valid |= ATTR_ATIME;
		अगर (!(sattr->ia_valid & ATTR_MTIME_SET))
			sattr->ia_valid |= ATTR_MTIME;

		/* Note: we could use a guarded setattr here, but I'm
		 * not sure this buys us anything (and I'd have
		 * to revamp the NFSv3 XDR code) */
		status = nfs3_proc_setattr(dentry, data->res.fattr, sattr);
		nfs_post_op_update_inode(d_inode(dentry), data->res.fattr);
		dprपूर्णांकk("NFS reply setattr (post-create): %d\n", status);
		अगर (status != 0)
			जाओ out_dput;
	पूर्ण

	status = nfs3_proc_setacls(d_inode(dentry), acl, शेष_acl);

out_dput:
	dput(d_alias);
out_release_acls:
	posix_acl_release(acl);
	posix_acl_release(शेष_acl);
out:
	nfs3_मुक्त_createdata(data);
	dprपूर्णांकk("NFS reply create: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा nfs_हटाओargs arg = अणु
		.fh = NFS_FH(dir),
		.name = dentry->d_name,
	पूर्ण;
	काष्ठा nfs_हटाओres res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs3_procedures[NFS3PROC_REMOVE],
		.rpc_argp = &arg,
		.rpc_resp = &res,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  remove %pd2\n", dentry);
	res.dir_attr = nfs_alloc_fattr();
	अगर (res.dir_attr == शून्य)
		जाओ out;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_post_op_update_inode(dir, res.dir_attr);
	nfs_मुक्त_fattr(res.dir_attr);
out:
	dprपूर्णांकk("NFS reply remove: %d\n", status);
	वापस status;
पूर्ण

अटल व्योम
nfs3_proc_unlink_setup(काष्ठा rpc_message *msg,
		काष्ठा dentry *dentry,
		काष्ठा inode *inode)
अणु
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_REMOVE];
पूर्ण

अटल व्योम nfs3_proc_unlink_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_unlinkdata *data)
अणु
	rpc_call_start(task);
पूर्ण

अटल पूर्णांक
nfs3_proc_unlink_करोne(काष्ठा rpc_task *task, काष्ठा inode *dir)
अणु
	काष्ठा nfs_हटाओres *res;
	अगर (nfs3_async_handle_jukebox(task, dir))
		वापस 0;
	res = task->tk_msg.rpc_resp;
	nfs_post_op_update_inode(dir, res->dir_attr);
	वापस 1;
पूर्ण

अटल व्योम
nfs3_proc_नाम_setup(काष्ठा rpc_message *msg,
		काष्ठा dentry *old_dentry,
		काष्ठा dentry *new_dentry)
अणु
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_RENAME];
पूर्ण

अटल व्योम nfs3_proc_नाम_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_नामdata *data)
अणु
	rpc_call_start(task);
पूर्ण

अटल पूर्णांक
nfs3_proc_नाम_करोne(काष्ठा rpc_task *task, काष्ठा inode *old_dir,
		      काष्ठा inode *new_dir)
अणु
	काष्ठा nfs_नामres *res;

	अगर (nfs3_async_handle_jukebox(task, old_dir))
		वापस 0;
	res = task->tk_msg.rpc_resp;

	nfs_post_op_update_inode(old_dir, res->old_fattr);
	nfs_post_op_update_inode(new_dir, res->new_fattr);
	वापस 1;
पूर्ण

अटल पूर्णांक
nfs3_proc_link(काष्ठा inode *inode, काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs3_linkargs	arg = अणु
		.fromfh		= NFS_FH(inode),
		.tofh		= NFS_FH(dir),
		.toname		= name->name,
		.tolen		= name->len
	पूर्ण;
	काष्ठा nfs3_linkres	res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_LINK],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  link %s\n", name->name);
	res.fattr = nfs_alloc_fattr();
	res.dir_attr = nfs_alloc_fattr();
	अगर (res.fattr == शून्य || res.dir_attr == शून्य)
		जाओ out;

	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	nfs_post_op_update_inode(dir, res.dir_attr);
	nfs_post_op_update_inode(inode, res.fattr);
out:
	nfs_मुक्त_fattr(res.dir_attr);
	nfs_मुक्त_fattr(res.fattr);
	dprपूर्णांकk("NFS reply link: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा page *page,
		  अचिन्हित पूर्णांक len, काष्ठा iattr *sattr)
अणु
	काष्ठा nfs3_createdata *data;
	काष्ठा dentry *d_alias;
	पूर्णांक status = -ENOMEM;

	अगर (len > NFS3_MAXPATHLEN)
		वापस -ENAMETOOLONG;

	dprपूर्णांकk("NFS call  symlink %pd\n", dentry);

	data = nfs3_alloc_createdata();
	अगर (data == शून्य)
		जाओ out;
	data->msg.rpc_proc = &nfs3_procedures[NFS3PROC_SYMLINK];
	data->arg.symlink.fromfh = NFS_FH(dir);
	data->arg.symlink.fromname = dentry->d_name.name;
	data->arg.symlink.fromlen = dentry->d_name.len;
	data->arg.symlink.pages = &page;
	data->arg.symlink.pathlen = len;
	data->arg.symlink.sattr = sattr;

	d_alias = nfs3_करो_create(dir, dentry, data);
	status = PTR_ERR_OR_ZERO(d_alias);

	अगर (status == 0)
		dput(d_alias);

	nfs3_मुक्त_createdata(data);
out:
	dprपूर्णांकk("NFS reply symlink: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	काष्ठा nfs3_createdata *data;
	काष्ठा dentry *d_alias;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  mkdir %pd\n", dentry);

	data = nfs3_alloc_createdata();
	अगर (data == शून्य)
		जाओ out;

	status = posix_acl_create(dir, &sattr->ia_mode, &शेष_acl, &acl);
	अगर (status)
		जाओ out;

	data->msg.rpc_proc = &nfs3_procedures[NFS3PROC_MKसूची];
	data->arg.सूची_गढ़ो.fh = NFS_FH(dir);
	data->arg.सूची_गढ़ो.name = dentry->d_name.name;
	data->arg.सूची_गढ़ो.len = dentry->d_name.len;
	data->arg.सूची_गढ़ो.sattr = sattr;

	d_alias = nfs3_करो_create(dir, dentry, data);
	status = PTR_ERR_OR_ZERO(d_alias);

	अगर (status != 0)
		जाओ out_release_acls;

	अगर (d_alias)
		dentry = d_alias;

	status = nfs3_proc_setacls(d_inode(dentry), acl, शेष_acl);

	dput(d_alias);
out_release_acls:
	posix_acl_release(acl);
	posix_acl_release(शेष_acl);
out:
	nfs3_मुक्त_createdata(data);
	dprपूर्णांकk("NFS reply mkdir: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_सूची_हटाओ(काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs_fattr	*dir_attr;
	काष्ठा nfs3_diropargs	arg = अणु
		.fh		= NFS_FH(dir),
		.name		= name->name,
		.len		= name->len
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_RMसूची],
		.rpc_argp	= &arg,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  rmdir %s\n", name->name);
	dir_attr = nfs_alloc_fattr();
	अगर (dir_attr == शून्य)
		जाओ out;

	msg.rpc_resp = dir_attr;
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_post_op_update_inode(dir, dir_attr);
	nfs_मुक्त_fattr(dir_attr);
out:
	dprपूर्णांकk("NFS reply rmdir: %d\n", status);
	वापस status;
पूर्ण

/*
 * The READसूची implementation is somewhat hackish - we pass the user buffer
 * to the encode function, which installs it in the receive iovec.
 * The decode function itself करोesn't perक्रमm any decoding, it just makes
 * sure the reply is syntactically correct.
 *
 * Also note that this implementation handles both plain सूची_पढ़ो and
 * सूची_पढ़ोplus.
 */
अटल पूर्णांक nfs3_proc_सूची_पढ़ो(काष्ठा nfs_सूची_पढ़ो_arg *nr_arg,
			     काष्ठा nfs_सूची_पढ़ो_res *nr_res)
अणु
	काष्ठा inode		*dir = d_inode(nr_arg->dentry);
	काष्ठा nfs3_सूची_पढ़ोargs	arg = अणु
		.fh		= NFS_FH(dir),
		.cookie		= nr_arg->cookie,
		.plus		= nr_arg->plus,
		.count		= nr_arg->page_len,
		.pages		= nr_arg->pages
	पूर्ण;
	काष्ठा nfs3_सूची_पढ़ोres	res = अणु
		.verf		= nr_res->verf,
		.plus		= nr_arg->plus,
	पूर्ण;
	काष्ठा rpc_message	msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_READसूची],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
		.rpc_cred	= nr_arg->cred,
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	अगर (nr_arg->plus)
		msg.rpc_proc = &nfs3_procedures[NFS3PROC_READसूचीPLUS];
	अगर (arg.cookie)
		स_नकल(arg.verf, nr_arg->verf, माप(arg.verf));

	dprपूर्णांकk("NFS call  readdir%s %llu\n", nr_arg->plus ? "plus" : "",
		(अचिन्हित दीर्घ दीर्घ)nr_arg->cookie);

	res.dir_attr = nfs_alloc_fattr();
	अगर (res.dir_attr == शून्य)
		जाओ out;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);

	nfs_invalidate_aसमय(dir);
	nfs_refresh_inode(dir, res.dir_attr);

	nfs_मुक्त_fattr(res.dir_attr);
out:
	dprपूर्णांकk("NFS reply readdir%s: %d\n", nr_arg->plus ? "plus" : "",
		status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr,
		dev_t rdev)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	काष्ठा nfs3_createdata *data;
	काष्ठा dentry *d_alias;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  mknod %pd %u:%u\n", dentry,
			MAJOR(rdev), MINOR(rdev));

	data = nfs3_alloc_createdata();
	अगर (data == शून्य)
		जाओ out;

	status = posix_acl_create(dir, &sattr->ia_mode, &शेष_acl, &acl);
	अगर (status)
		जाओ out;

	data->msg.rpc_proc = &nfs3_procedures[NFS3PROC_MKNOD];
	data->arg.mknod.fh = NFS_FH(dir);
	data->arg.mknod.name = dentry->d_name.name;
	data->arg.mknod.len = dentry->d_name.len;
	data->arg.mknod.sattr = sattr;
	data->arg.mknod.rdev = rdev;

	चयन (sattr->ia_mode & S_IFMT) अणु
	हाल S_IFBLK:
		data->arg.mknod.type = NF3BLK;
		अवरोध;
	हाल S_IFCHR:
		data->arg.mknod.type = NF3CHR;
		अवरोध;
	हाल S_IFIFO:
		data->arg.mknod.type = NF3FIFO;
		अवरोध;
	हाल S_IFSOCK:
		data->arg.mknod.type = NF3SOCK;
		अवरोध;
	शेष:
		status = -EINVAL;
		जाओ out;
	पूर्ण

	d_alias = nfs3_करो_create(dir, dentry, data);
	status = PTR_ERR_OR_ZERO(d_alias);
	अगर (status != 0)
		जाओ out_release_acls;

	अगर (d_alias)
		dentry = d_alias;

	status = nfs3_proc_setacls(d_inode(dentry), acl, शेष_acl);

	dput(d_alias);
out_release_acls:
	posix_acl_release(acl);
	posix_acl_release(शेष_acl);
out:
	nfs3_मुक्त_createdata(data);
	dprपूर्णांकk("NFS reply mknod: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_statfs(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		 काष्ठा nfs_fsstat *stat)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_FSSTAT],
		.rpc_argp	= fhandle,
		.rpc_resp	= stat,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("NFS call  fsstat\n");
	nfs_fattr_init(stat->fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprपूर्णांकk("NFS reply fsstat: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
करो_proc_fsinfo(काष्ठा rpc_clnt *client, काष्ठा nfs_fh *fhandle,
		 काष्ठा nfs_fsinfo *info)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_FSINFO],
		.rpc_argp	= fhandle,
		.rpc_resp	= info,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("NFS call  fsinfo\n");
	nfs_fattr_init(info->fattr);
	status = rpc_call_sync(client, &msg, 0);
	dprपूर्णांकk("NFS reply fsinfo: %d\n", status);
	वापस status;
पूर्ण

/*
 * Bare-bones access to fsinfo: this is क्रम nfs_get_root/nfs_get_sb via
 * nfs_create_server
 */
अटल पूर्णांक
nfs3_proc_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		   काष्ठा nfs_fsinfo *info)
अणु
	पूर्णांक	status;

	status = करो_proc_fsinfo(server->client, fhandle, info);
	अगर (status && server->nfs_client->cl_rpcclient != server->client)
		status = करो_proc_fsinfo(server->nfs_client->cl_rpcclient, fhandle, info);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs3_proc_pathconf(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		   काष्ठा nfs_pathconf *info)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs3_procedures[NFS3PROC_PATHCONF],
		.rpc_argp	= fhandle,
		.rpc_resp	= info,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("NFS call  pathconf\n");
	nfs_fattr_init(info->fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprपूर्णांकk("NFS reply pathconf: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs3_पढ़ो_करोne(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा inode *inode = hdr->inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);

	अगर (hdr->pgio_करोne_cb != शून्य)
		वापस hdr->pgio_करोne_cb(task, hdr);

	अगर (nfs3_async_handle_jukebox(task, inode))
		वापस -EAGAIN;

	अगर (task->tk_status >= 0 && !server->पढ़ो_hdrsize)
		cmpxchg(&server->पढ़ो_hdrsize, 0, hdr->res.replen);

	nfs_invalidate_aसमय(inode);
	nfs_refresh_inode(inode, &hdr->fattr);
	वापस 0;
पूर्ण

अटल व्योम nfs3_proc_पढ़ो_setup(काष्ठा nfs_pgio_header *hdr,
				 काष्ठा rpc_message *msg)
अणु
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_READ];
	hdr->args.replen = NFS_SERVER(hdr->inode)->पढ़ो_hdrsize;
पूर्ण

अटल पूर्णांक nfs3_proc_pgio_rpc_prepare(काष्ठा rpc_task *task,
				      काष्ठा nfs_pgio_header *hdr)
अणु
	rpc_call_start(task);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs3_ग_लिखो_करोne(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा inode *inode = hdr->inode;

	अगर (hdr->pgio_करोne_cb != शून्य)
		वापस hdr->pgio_करोne_cb(task, hdr);

	अगर (nfs3_async_handle_jukebox(task, inode))
		वापस -EAGAIN;
	अगर (task->tk_status >= 0)
		nfs_ग_लिखोback_update_inode(hdr);
	वापस 0;
पूर्ण

अटल व्योम nfs3_proc_ग_लिखो_setup(काष्ठा nfs_pgio_header *hdr,
				  काष्ठा rpc_message *msg,
				  काष्ठा rpc_clnt **clnt)
अणु
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_WRITE];
पूर्ण

अटल व्योम nfs3_proc_commit_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data)
अणु
	rpc_call_start(task);
पूर्ण

अटल पूर्णांक nfs3_commit_करोne(काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data)
अणु
	अगर (data->commit_करोne_cb != शून्य)
		वापस data->commit_करोne_cb(task, data);

	अगर (nfs3_async_handle_jukebox(task, data->inode))
		वापस -EAGAIN;
	nfs_refresh_inode(data->inode, data->res.fattr);
	वापस 0;
पूर्ण

अटल व्योम nfs3_proc_commit_setup(काष्ठा nfs_commit_data *data, काष्ठा rpc_message *msg,
				   काष्ठा rpc_clnt **clnt)
अणु
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_COMMIT];
पूर्ण

अटल व्योम nfs3_nlm_alloc_call(व्योम *data)
अणु
	काष्ठा nfs_lock_context *l_ctx = data;
	अगर (l_ctx && test_bit(NFS_CONTEXT_UNLOCK, &l_ctx->खोलो_context->flags)) अणु
		get_nfs_खोलो_context(l_ctx->खोलो_context);
		nfs_get_lock_context(l_ctx->खोलो_context);
	पूर्ण
पूर्ण

अटल bool nfs3_nlm_unlock_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nfs_lock_context *l_ctx = data;
	अगर (l_ctx && test_bit(NFS_CONTEXT_UNLOCK, &l_ctx->खोलो_context->flags))
		वापस nfs_async_iocounter_रुको(task, l_ctx);
	वापस false;

पूर्ण

अटल व्योम nfs3_nlm_release_call(व्योम *data)
अणु
	काष्ठा nfs_lock_context *l_ctx = data;
	काष्ठा nfs_खोलो_context *ctx;
	अगर (l_ctx && test_bit(NFS_CONTEXT_UNLOCK, &l_ctx->खोलो_context->flags)) अणु
		ctx = l_ctx->खोलो_context;
		nfs_put_lock_context(l_ctx);
		put_nfs_खोलो_context(ctx);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nlmclnt_operations nlmclnt_fl_बंद_lock_ops = अणु
	.nlmclnt_alloc_call = nfs3_nlm_alloc_call,
	.nlmclnt_unlock_prepare = nfs3_nlm_unlock_prepare,
	.nlmclnt_release_call = nfs3_nlm_release_call,
पूर्ण;

अटल पूर्णांक
nfs3_proc_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा nfs_lock_context *l_ctx = शून्य;
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(filp);
	पूर्णांक status;

	अगर (fl->fl_flags & FL_CLOSE) अणु
		l_ctx = nfs_get_lock_context(ctx);
		अगर (IS_ERR(l_ctx))
			l_ctx = शून्य;
		अन्यथा
			set_bit(NFS_CONTEXT_UNLOCK, &ctx->flags);
	पूर्ण

	status = nlmclnt_proc(NFS_SERVER(inode)->nlm_host, cmd, fl, l_ctx);

	अगर (l_ctx)
		nfs_put_lock_context(l_ctx);

	वापस status;
पूर्ण

अटल पूर्णांक nfs3_have_delegation(काष्ठा inode *inode, भ_शेषe_t flags)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations nfs3_dir_inode_operations = अणु
	.create		= nfs_create,
	.lookup		= nfs_lookup,
	.link		= nfs_link,
	.unlink		= nfs_unlink,
	.symlink	= nfs_symlink,
	.सूची_गढ़ो		= nfs_सूची_गढ़ो,
	.सूची_हटाओ		= nfs_सूची_हटाओ,
	.mknod		= nfs_mknod,
	.नाम		= nfs_नाम,
	.permission	= nfs_permission,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
#अगर_घोषित CONFIG_NFS_V3_ACL
	.listxattr	= nfs3_listxattr,
	.get_acl	= nfs3_get_acl,
	.set_acl	= nfs3_set_acl,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा inode_operations nfs3_file_inode_operations = अणु
	.permission	= nfs_permission,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
#अगर_घोषित CONFIG_NFS_V3_ACL
	.listxattr	= nfs3_listxattr,
	.get_acl	= nfs3_get_acl,
	.set_acl	= nfs3_set_acl,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा nfs_rpc_ops nfs_v3_clientops = अणु
	.version	= 3,			/* protocol version */
	.dentry_ops	= &nfs_dentry_operations,
	.dir_inode_ops	= &nfs3_dir_inode_operations,
	.file_inode_ops	= &nfs3_file_inode_operations,
	.file_ops	= &nfs_file_operations,
	.nlmclnt_ops	= &nlmclnt_fl_बंद_lock_ops,
	.getroot	= nfs3_proc_get_root,
	.submount	= nfs_submount,
	.try_get_tree	= nfs_try_get_tree,
	.getattr	= nfs3_proc_getattr,
	.setattr	= nfs3_proc_setattr,
	.lookup		= nfs3_proc_lookup,
	.lookupp	= nfs3_proc_lookupp,
	.access		= nfs3_proc_access,
	.पढ़ोlink	= nfs3_proc_पढ़ोlink,
	.create		= nfs3_proc_create,
	.हटाओ		= nfs3_proc_हटाओ,
	.unlink_setup	= nfs3_proc_unlink_setup,
	.unlink_rpc_prepare = nfs3_proc_unlink_rpc_prepare,
	.unlink_करोne	= nfs3_proc_unlink_करोne,
	.नाम_setup	= nfs3_proc_नाम_setup,
	.नाम_rpc_prepare = nfs3_proc_नाम_rpc_prepare,
	.नाम_करोne	= nfs3_proc_नाम_करोne,
	.link		= nfs3_proc_link,
	.symlink	= nfs3_proc_symlink,
	.सूची_गढ़ो		= nfs3_proc_सूची_गढ़ो,
	.सूची_हटाओ		= nfs3_proc_सूची_हटाओ,
	.सूची_पढ़ो	= nfs3_proc_सूची_पढ़ो,
	.mknod		= nfs3_proc_mknod,
	.statfs		= nfs3_proc_statfs,
	.fsinfo		= nfs3_proc_fsinfo,
	.pathconf	= nfs3_proc_pathconf,
	.decode_dirent	= nfs3_decode_dirent,
	.pgio_rpc_prepare = nfs3_proc_pgio_rpc_prepare,
	.पढ़ो_setup	= nfs3_proc_पढ़ो_setup,
	.पढ़ो_करोne	= nfs3_पढ़ो_करोne,
	.ग_लिखो_setup	= nfs3_proc_ग_लिखो_setup,
	.ग_लिखो_करोne	= nfs3_ग_लिखो_करोne,
	.commit_setup	= nfs3_proc_commit_setup,
	.commit_rpc_prepare = nfs3_proc_commit_rpc_prepare,
	.commit_करोne	= nfs3_commit_करोne,
	.lock		= nfs3_proc_lock,
	.clear_acl_cache = क्रमget_all_cached_acls,
	.बंद_context	= nfs_बंद_context,
	.have_delegation = nfs3_have_delegation,
	.alloc_client	= nfs_alloc_client,
	.init_client	= nfs_init_client,
	.मुक्त_client	= nfs_मुक्त_client,
	.create_server	= nfs3_create_server,
	.clone_server	= nfs3_clone_server,
पूर्ण;
