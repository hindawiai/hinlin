<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/nfs/proc.c
 *
 *  Copyright (C) 1992, 1993, 1994  Rick Sladkey
 *
 *  OS-independent nfs remote procedure call functions
 *
 *  Tuned by Alan Cox <A.Cox@swansea.ac.uk> क्रम >3K buffers
 *  so at last we can have decent(ish) throughput off a 
 *  Sun server.
 *
 *  Coding optimized and cleaned up by Florian La Roche.
 *  Note: Error वापसs are optimized क्रम NFS_OK, which isn't translated via
 *  nfs_stat_to_त्रुटि_सं(), but happens to be alपढ़ोy the right वापस code.
 *
 *  Also, the code currently करोesn't check the size of the packet, when
 *  it decodes the packet.
 *
 *  Feel मुक्त to fix it and mail me the dअगरfs अगर it worries you.
 *
 *  Completely rewritten to support the new RPC call पूर्णांकerface;
 *  rewrote and moved the entire XDR stuff to xdr.c
 *  --Olaf Kirch June 1996
 *
 *  The code below initializes all स्वतः variables explicitly, otherwise
 *  it will fail to work as a module (gcc generates a स_रखो call क्रम an
 *  incomplete काष्ठा).
 */

#समावेश <linux/types.h>
#समावेश <linux/param.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs2.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_page.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/मुक्तzer.h>
#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_PROC

/*
 * Bare-bones access to getattr: this is क्रम nfs_पढ़ो_super.
 */
अटल पूर्णांक
nfs_proc_get_root(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		  काष्ठा nfs_fsinfo *info)
अणु
	काष्ठा nfs_fattr *fattr = info->fattr;
	काष्ठा nfs2_fsstat fsinfo;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_GETATTR],
		.rpc_argp	= fhandle,
		.rpc_resp	= fattr,
	पूर्ण;
	पूर्णांक status;

	dprपूर्णांकk("%s: call getattr\n", __func__);
	nfs_fattr_init(fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	/* Retry with शेष authentication अगर dअगरferent */
	अगर (status && server->nfs_client->cl_rpcclient != server->client)
		status = rpc_call_sync(server->nfs_client->cl_rpcclient, &msg, 0);
	dprपूर्णांकk("%s: reply getattr: %d\n", __func__, status);
	अगर (status)
		वापस status;
	dprपूर्णांकk("%s: call statfs\n", __func__);
	msg.rpc_proc = &nfs_procedures[NFSPROC_STATFS];
	msg.rpc_resp = &fsinfo;
	status = rpc_call_sync(server->client, &msg, 0);
	/* Retry with शेष authentication अगर dअगरferent */
	अगर (status && server->nfs_client->cl_rpcclient != server->client)
		status = rpc_call_sync(server->nfs_client->cl_rpcclient, &msg, 0);
	dprपूर्णांकk("%s: reply statfs: %d\n", __func__, status);
	अगर (status)
		वापस status;
	info->rपंचांगax  = NFS_MAXDATA;
	info->rtpref = fsinfo.tsize;
	info->rपंचांगult = fsinfo.bsize;
	info->wपंचांगax  = NFS_MAXDATA;
	info->wtpref = fsinfo.tsize;
	info->wपंचांगult = fsinfo.bsize;
	info->dtpref = fsinfo.tsize;
	info->maxfilesize = 0x7FFFFFFF;
	info->lease_समय = 0;
	info->change_attr_type = NFS4_CHANGE_TYPE_IS_TIME_METADATA;
	वापस 0;
पूर्ण

/*
 * One function क्रम each procedure in the NFS protocol.
 */
अटल पूर्णांक
nfs_proc_getattr(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		काष्ठा nfs_fattr *fattr, काष्ठा nfs4_label *label,
		काष्ठा inode *inode)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_GETATTR],
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
nfs_proc_setattr(काष्ठा dentry *dentry, काष्ठा nfs_fattr *fattr,
		 काष्ठा iattr *sattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा nfs_sattrargs	arg = अणु 
		.fh	= NFS_FH(inode),
		.sattr	= sattr
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_SETATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= fattr,
	पूर्ण;
	पूर्णांक	status;

	/* Mask out the non-modebit related stuff from attr->ia_mode */
	sattr->ia_mode &= S_IALLUGO;

	dprपूर्णांकk("NFS call  setattr\n");
	अगर (sattr->ia_valid & ATTR_खाता)
		msg.rpc_cred = nfs_file_cred(sattr->ia_file);
	nfs_fattr_init(fattr);
	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	अगर (status == 0)
		nfs_setattr_update_inode(inode, sattr, fattr);
	dprपूर्णांकk("NFS reply setattr: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
		काष्ठा nfs_fh *fhandle, काष्ठा nfs_fattr *fattr,
		काष्ठा nfs4_label *label)
अणु
	काष्ठा nfs_diropargs	arg = अणु
		.fh		= NFS_FH(dir),
		.name		= dentry->d_name.name,
		.len		= dentry->d_name.len
	पूर्ण;
	काष्ठा nfs_diropok	res = अणु
		.fh		= fhandle,
		.fattr		= fattr
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_LOOKUP],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक			status;
	अचिन्हित लघु task_flags = 0;

	/* Is this is an attribute revalidation, subject to softreval? */
	अगर (nfs_lookup_is_soft_revalidate(dentry))
		task_flags |= RPC_TASK_TIMEOUT;

	dprपूर्णांकk("NFS call  lookup %pd2\n", dentry);
	nfs_fattr_init(fattr);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, task_flags);
	dprपूर्णांकk("NFS reply lookup: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक nfs_proc_पढ़ोlink(काष्ठा inode *inode, काष्ठा page *page,
		अचिन्हित पूर्णांक pgbase, अचिन्हित पूर्णांक pglen)
अणु
	काष्ठा nfs_पढ़ोlinkargs	args = अणु
		.fh		= NFS_FH(inode),
		.pgbase		= pgbase,
		.pglen		= pglen,
		.pages		= &page
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_READLINK],
		.rpc_argp	= &args,
	पूर्ण;
	पूर्णांक			status;

	dprपूर्णांकk("NFS call  readlink\n");
	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	dprपूर्णांकk("NFS reply readlink: %d\n", status);
	वापस status;
पूर्ण

काष्ठा nfs_createdata अणु
	काष्ठा nfs_createargs arg;
	काष्ठा nfs_diropok res;
	काष्ठा nfs_fh fhandle;
	काष्ठा nfs_fattr fattr;
पूर्ण;

अटल काष्ठा nfs_createdata *nfs_alloc_createdata(काष्ठा inode *dir,
		काष्ठा dentry *dentry, काष्ठा iattr *sattr)
अणु
	काष्ठा nfs_createdata *data;

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);

	अगर (data != शून्य) अणु
		data->arg.fh = NFS_FH(dir);
		data->arg.name = dentry->d_name.name;
		data->arg.len = dentry->d_name.len;
		data->arg.sattr = sattr;
		nfs_fattr_init(&data->fattr);
		data->fhandle.size = 0;
		data->res.fh = &data->fhandle;
		data->res.fattr = &data->fattr;
	पूर्ण
	वापस data;
पूर्ण;

अटल व्योम nfs_मुक्त_createdata(स्थिर काष्ठा nfs_createdata *data)
अणु
	kमुक्त(data);
पूर्ण

अटल पूर्णांक
nfs_proc_create(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr,
		पूर्णांक flags)
अणु
	काष्ठा nfs_createdata *data;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_CREATE],
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  create %pd\n", dentry);
	data = nfs_alloc_createdata(dir, dentry, sattr);
	अगर (data == शून्य)
		जाओ out;
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_क्रम_revalidate(dir);
	अगर (status == 0)
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, शून्य);
	nfs_मुक्त_createdata(data);
out:
	dprपूर्णांकk("NFS reply create: %d\n", status);
	वापस status;
पूर्ण

/*
 * In NFSv2, mknod is grafted onto the create call.
 */
अटल पूर्णांक
nfs_proc_mknod(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr,
	       dev_t rdev)
अणु
	काष्ठा nfs_createdata *data;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_CREATE],
	पूर्ण;
	umode_t mode;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  mknod %pd\n", dentry);

	mode = sattr->ia_mode;
	अगर (S_ISFIFO(mode)) अणु
		sattr->ia_mode = (mode & ~S_IFMT) | S_IFCHR;
		sattr->ia_valid &= ~ATTR_SIZE;
	पूर्ण अन्यथा अगर (S_ISCHR(mode) || S_ISBLK(mode)) अणु
		sattr->ia_valid |= ATTR_SIZE;
		sattr->ia_size = new_encode_dev(rdev);/* get out your barf bag */
	पूर्ण

	data = nfs_alloc_createdata(dir, dentry, sattr);
	अगर (data == शून्य)
		जाओ out;
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_क्रम_revalidate(dir);

	अगर (status == -EINVAL && S_ISFIFO(mode)) अणु
		sattr->ia_mode = mode;
		nfs_fattr_init(data->res.fattr);
		status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	पूर्ण
	अगर (status == 0)
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, शून्य);
	nfs_मुक्त_createdata(data);
out:
	dprपूर्णांकk("NFS reply mknod: %d\n", status);
	वापस status;
पूर्ण
  
अटल पूर्णांक
nfs_proc_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा nfs_हटाओargs arg = अणु
		.fh = NFS_FH(dir),
		.name = dentry->d_name,
	पूर्ण;
	काष्ठा rpc_message msg = अणु 
		.rpc_proc = &nfs_procedures[NFSPROC_REMOVE],
		.rpc_argp = &arg,
	पूर्ण;
	पूर्णांक			status;

	dprपूर्णांकk("NFS call  remove %pd2\n",dentry);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_क्रम_revalidate(dir);

	dprपूर्णांकk("NFS reply remove: %d\n", status);
	वापस status;
पूर्ण

अटल व्योम
nfs_proc_unlink_setup(काष्ठा rpc_message *msg,
		काष्ठा dentry *dentry,
		काष्ठा inode *inode)
अणु
	msg->rpc_proc = &nfs_procedures[NFSPROC_REMOVE];
पूर्ण

अटल व्योम nfs_proc_unlink_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_unlinkdata *data)
अणु
	rpc_call_start(task);
पूर्ण

अटल पूर्णांक nfs_proc_unlink_करोne(काष्ठा rpc_task *task, काष्ठा inode *dir)
अणु
	nfs_mark_क्रम_revalidate(dir);
	वापस 1;
पूर्ण

अटल व्योम
nfs_proc_नाम_setup(काष्ठा rpc_message *msg,
		काष्ठा dentry *old_dentry,
		काष्ठा dentry *new_dentry)
अणु
	msg->rpc_proc = &nfs_procedures[NFSPROC_RENAME];
पूर्ण

अटल व्योम nfs_proc_नाम_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_नामdata *data)
अणु
	rpc_call_start(task);
पूर्ण

अटल पूर्णांक
nfs_proc_नाम_करोne(काष्ठा rpc_task *task, काष्ठा inode *old_dir,
		     काष्ठा inode *new_dir)
अणु
	nfs_mark_क्रम_revalidate(old_dir);
	nfs_mark_क्रम_revalidate(new_dir);
	वापस 1;
पूर्ण

अटल पूर्णांक
nfs_proc_link(काष्ठा inode *inode, काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs_linkargs	arg = अणु
		.fromfh		= NFS_FH(inode),
		.tofh		= NFS_FH(dir),
		.toname		= name->name,
		.tolen		= name->len
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_LINK],
		.rpc_argp	= &arg,
	पूर्ण;
	पूर्णांक			status;

	dprपूर्णांकk("NFS call  link %s\n", name->name);
	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	nfs_mark_क्रम_revalidate(inode);
	nfs_mark_क्रम_revalidate(dir);
	dprपूर्णांकk("NFS reply link: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_symlink(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा page *page,
		 अचिन्हित पूर्णांक len, काष्ठा iattr *sattr)
अणु
	काष्ठा nfs_fh *fh;
	काष्ठा nfs_fattr *fattr;
	काष्ठा nfs_symlinkargs	arg = अणु
		.fromfh		= NFS_FH(dir),
		.fromname	= dentry->d_name.name,
		.fromlen	= dentry->d_name.len,
		.pages		= &page,
		.pathlen	= len,
		.sattr		= sattr
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_SYMLINK],
		.rpc_argp	= &arg,
	पूर्ण;
	पूर्णांक status = -ENAMETOOLONG;

	dprपूर्णांकk("NFS call  symlink %pd\n", dentry);

	अगर (len > NFS2_MAXPATHLEN)
		जाओ out;

	fh = nfs_alloc_fhandle();
	fattr = nfs_alloc_fattr();
	status = -ENOMEM;
	अगर (fh == शून्य || fattr == शून्य)
		जाओ out_मुक्त;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_क्रम_revalidate(dir);

	/*
	 * V2 SYMLINK requests करोn't वापस any attributes.  Setting the
	 * filehandle size to zero indicates to nfs_instantiate that it
	 * should fill in the data with a LOOKUP call on the wire.
	 */
	अगर (status == 0)
		status = nfs_instantiate(dentry, fh, fattr, शून्य);

out_मुक्त:
	nfs_मुक्त_fattr(fattr);
	nfs_मुक्त_fhandle(fh);
out:
	dprपूर्णांकk("NFS reply symlink: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, काष्ठा iattr *sattr)
अणु
	काष्ठा nfs_createdata *data;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_MKसूची],
	पूर्ण;
	पूर्णांक status = -ENOMEM;

	dprपूर्णांकk("NFS call  mkdir %pd\n", dentry);
	data = nfs_alloc_createdata(dir, dentry, sattr);
	अगर (data == शून्य)
		जाओ out;
	msg.rpc_argp = &data->arg;
	msg.rpc_resp = &data->res;

	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_क्रम_revalidate(dir);
	अगर (status == 0)
		status = nfs_instantiate(dentry, data->res.fh, data->res.fattr, शून्य);
	nfs_मुक्त_createdata(data);
out:
	dprपूर्णांकk("NFS reply mkdir: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_सूची_हटाओ(काष्ठा inode *dir, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा nfs_diropargs	arg = अणु
		.fh		= NFS_FH(dir),
		.name		= name->name,
		.len		= name->len
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_RMसूची],
		.rpc_argp	= &arg,
	पूर्ण;
	पूर्णांक			status;

	dprपूर्णांकk("NFS call  rmdir %s\n", name->name);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nfs_mark_क्रम_revalidate(dir);
	dprपूर्णांकk("NFS reply rmdir: %d\n", status);
	वापस status;
पूर्ण

/*
 * The READसूची implementation is somewhat hackish - we pass a temporary
 * buffer to the encode function, which installs it in the receive
 * the receive iovec. The decode function just parses the reply to make
 * sure it is syntactically correct; the entries itself are decoded
 * from nfs_सूची_पढ़ो by calling the decode_entry function directly.
 */
अटल पूर्णांक nfs_proc_सूची_पढ़ो(काष्ठा nfs_सूची_पढ़ो_arg *nr_arg,
			    काष्ठा nfs_सूची_पढ़ो_res *nr_res)
अणु
	काष्ठा inode		*dir = d_inode(nr_arg->dentry);
	काष्ठा nfs_सूची_पढ़ोargs	arg = अणु
		.fh		= NFS_FH(dir),
		.cookie		= nr_arg->cookie,
		.count		= nr_arg->page_len,
		.pages		= nr_arg->pages,
	पूर्ण;
	काष्ठा rpc_message	msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_READसूची],
		.rpc_argp	= &arg,
		.rpc_cred	= nr_arg->cred,
	पूर्ण;
	पूर्णांक			status;

	dprपूर्णांकk("NFS call  readdir %llu\n", (अचिन्हित दीर्घ दीर्घ)nr_arg->cookie);
	status = rpc_call_sync(NFS_CLIENT(dir), &msg, 0);
	nr_res->verf[0] = nr_res->verf[1] = 0;

	nfs_invalidate_aसमय(dir);

	dprपूर्णांकk("NFS reply readdir: %d\n", status);
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_statfs(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
			काष्ठा nfs_fsstat *stat)
अणु
	काष्ठा nfs2_fsstat fsinfo;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_STATFS],
		.rpc_argp	= fhandle,
		.rpc_resp	= &fsinfo,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("NFS call  statfs\n");
	nfs_fattr_init(stat->fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprपूर्णांकk("NFS reply statfs: %d\n", status);
	अगर (status)
		जाओ out;
	stat->tbytes = (u64)fsinfo.blocks * fsinfo.bsize;
	stat->fbytes = (u64)fsinfo.bमुक्त  * fsinfo.bsize;
	stat->abytes = (u64)fsinfo.bavail * fsinfo.bsize;
	stat->tfiles = 0;
	stat->ffiles = 0;
	stat->afiles = 0;
out:
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
			काष्ठा nfs_fsinfo *info)
अणु
	काष्ठा nfs2_fsstat fsinfo;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs_procedures[NFSPROC_STATFS],
		.rpc_argp	= fhandle,
		.rpc_resp	= &fsinfo,
	पूर्ण;
	पूर्णांक	status;

	dprपूर्णांकk("NFS call  fsinfo\n");
	nfs_fattr_init(info->fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprपूर्णांकk("NFS reply fsinfo: %d\n", status);
	अगर (status)
		जाओ out;
	info->rपंचांगax  = NFS_MAXDATA;
	info->rtpref = fsinfo.tsize;
	info->rपंचांगult = fsinfo.bsize;
	info->wपंचांगax  = NFS_MAXDATA;
	info->wtpref = fsinfo.tsize;
	info->wपंचांगult = fsinfo.bsize;
	info->dtpref = fsinfo.tsize;
	info->maxfilesize = 0x7FFFFFFF;
	info->lease_समय = 0;
out:
	वापस status;
पूर्ण

अटल पूर्णांक
nfs_proc_pathconf(काष्ठा nfs_server *server, काष्ठा nfs_fh *fhandle,
		  काष्ठा nfs_pathconf *info)
अणु
	info->max_link = 0;
	info->max_namelen = NFS2_MAXNAMLEN;
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_पढ़ो_करोne(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	काष्ठा inode *inode = hdr->inode;

	nfs_invalidate_aसमय(inode);
	अगर (task->tk_status >= 0) अणु
		nfs_refresh_inode(inode, hdr->res.fattr);
		/* Emulate the eof flag, which isn't normally needed in NFSv2
		 * as it is guaranteed to always वापस the file attributes
		 */
		अगर ((hdr->res.count == 0 && hdr->args.count > 0) ||
		    hdr->args.offset + hdr->res.count >= hdr->res.fattr->size)
			hdr->res.eof = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nfs_proc_पढ़ो_setup(काष्ठा nfs_pgio_header *hdr,
				काष्ठा rpc_message *msg)
अणु
	msg->rpc_proc = &nfs_procedures[NFSPROC_READ];
पूर्ण

अटल पूर्णांक nfs_proc_pgio_rpc_prepare(काष्ठा rpc_task *task,
				     काष्ठा nfs_pgio_header *hdr)
अणु
	rpc_call_start(task);
	वापस 0;
पूर्ण

अटल पूर्णांक nfs_ग_लिखो_करोne(काष्ठा rpc_task *task, काष्ठा nfs_pgio_header *hdr)
अणु
	अगर (task->tk_status >= 0) अणु
		hdr->res.count = hdr->args.count;
		nfs_ग_लिखोback_update_inode(hdr);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nfs_proc_ग_लिखो_setup(काष्ठा nfs_pgio_header *hdr,
				 काष्ठा rpc_message *msg,
				 काष्ठा rpc_clnt **clnt)
अणु
	/* Note: NFSv2 ignores @stable and always uses NFS_खाता_SYNC */
	hdr->args.stable = NFS_खाता_SYNC;
	msg->rpc_proc = &nfs_procedures[NFSPROC_WRITE];
पूर्ण

अटल व्योम nfs_proc_commit_rpc_prepare(काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data)
अणु
	BUG();
पूर्ण

अटल व्योम
nfs_proc_commit_setup(काष्ठा nfs_commit_data *data, काष्ठा rpc_message *msg,
			काष्ठा rpc_clnt **clnt)
अणु
	BUG();
पूर्ण

अटल पूर्णांक
nfs_proc_lock(काष्ठा file *filp, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = file_inode(filp);

	वापस nlmclnt_proc(NFS_SERVER(inode)->nlm_host, cmd, fl, शून्य);
पूर्ण

/* Helper functions क्रम NFS lock bounds checking */
#घोषणा NFS_LOCK32_OFFSET_MAX ((__s32)0x7fffffffUL)
अटल पूर्णांक nfs_lock_check_bounds(स्थिर काष्ठा file_lock *fl)
अणु
	__s32 start, end;

	start = (__s32)fl->fl_start;
	अगर ((loff_t)start != fl->fl_start)
		जाओ out_einval;

	अगर (fl->fl_end != OFFSET_MAX) अणु
		end = (__s32)fl->fl_end;
		अगर ((loff_t)end != fl->fl_end)
			जाओ out_einval;
	पूर्ण अन्यथा
		end = NFS_LOCK32_OFFSET_MAX;

	अगर (start < 0 || start > end)
		जाओ out_einval;
	वापस 0;
out_einval:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nfs_have_delegation(काष्ठा inode *inode, भ_शेषe_t flags)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations nfs_dir_inode_operations = अणु
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
पूर्ण;

अटल स्थिर काष्ठा inode_operations nfs_file_inode_operations = अणु
	.permission	= nfs_permission,
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
पूर्ण;

स्थिर काष्ठा nfs_rpc_ops nfs_v2_clientops = अणु
	.version	= 2,		       /* protocol version */
	.dentry_ops	= &nfs_dentry_operations,
	.dir_inode_ops	= &nfs_dir_inode_operations,
	.file_inode_ops	= &nfs_file_inode_operations,
	.file_ops	= &nfs_file_operations,
	.getroot	= nfs_proc_get_root,
	.submount	= nfs_submount,
	.try_get_tree	= nfs_try_get_tree,
	.getattr	= nfs_proc_getattr,
	.setattr	= nfs_proc_setattr,
	.lookup		= nfs_proc_lookup,
	.access		= शून्य,		       /* access */
	.पढ़ोlink	= nfs_proc_पढ़ोlink,
	.create		= nfs_proc_create,
	.हटाओ		= nfs_proc_हटाओ,
	.unlink_setup	= nfs_proc_unlink_setup,
	.unlink_rpc_prepare = nfs_proc_unlink_rpc_prepare,
	.unlink_करोne	= nfs_proc_unlink_करोne,
	.नाम_setup	= nfs_proc_नाम_setup,
	.नाम_rpc_prepare = nfs_proc_नाम_rpc_prepare,
	.नाम_करोne	= nfs_proc_नाम_करोne,
	.link		= nfs_proc_link,
	.symlink	= nfs_proc_symlink,
	.सूची_गढ़ो		= nfs_proc_सूची_गढ़ो,
	.सूची_हटाओ		= nfs_proc_सूची_हटाओ,
	.सूची_पढ़ो	= nfs_proc_सूची_पढ़ो,
	.mknod		= nfs_proc_mknod,
	.statfs		= nfs_proc_statfs,
	.fsinfo		= nfs_proc_fsinfo,
	.pathconf	= nfs_proc_pathconf,
	.decode_dirent	= nfs2_decode_dirent,
	.pgio_rpc_prepare = nfs_proc_pgio_rpc_prepare,
	.पढ़ो_setup	= nfs_proc_पढ़ो_setup,
	.पढ़ो_करोne	= nfs_पढ़ो_करोne,
	.ग_लिखो_setup	= nfs_proc_ग_लिखो_setup,
	.ग_लिखो_करोne	= nfs_ग_लिखो_करोne,
	.commit_setup	= nfs_proc_commit_setup,
	.commit_rpc_prepare = nfs_proc_commit_rpc_prepare,
	.lock		= nfs_proc_lock,
	.lock_check_bounds = nfs_lock_check_bounds,
	.बंद_context	= nfs_बंद_context,
	.have_delegation = nfs_have_delegation,
	.alloc_client	= nfs_alloc_client,
	.init_client	= nfs_init_client,
	.मुक्त_client	= nfs_मुक्त_client,
	.create_server	= nfs_create_server,
	.clone_server	= nfs_clone_server,
पूर्ण;
