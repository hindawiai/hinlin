<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/sunrpc/rpc_pipe.c
 *
 * Userland/kernel पूर्णांकerface क्रम rpcauth_gss.
 * Code shamelessly plagiarized from fs/nfsd/nfsctl.c
 * and fs/sysfs/inode.c
 *
 * Copyright (c) 2002, Trond Myklebust <trond.myklebust@fys.uio.no>
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/namei.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/utsname.h>

#समावेश <यंत्र/ioctls.h>
#समावेश <linux/poll.h>
#समावेश <linux/रुको.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/notअगरier.h>

#समावेश "netns.h"
#समावेश "sunrpc.h"

#घोषणा RPCDBG_FACILITY RPCDBG_DEBUG

#घोषणा NET_NAME(net)	((net == &init_net) ? " (init_net)" : "")

अटल काष्ठा file_प्रणाली_type rpc_pipe_fs_type;
अटल स्थिर काष्ठा rpc_pipe_ops gssd_dummy_pipe_ops;

अटल काष्ठा kmem_cache *rpc_inode_cachep __पढ़ो_mostly;

#घोषणा RPC_UPCALL_TIMEOUT (30*HZ)

अटल BLOCKING_NOTIFIER_HEAD(rpc_pipefs_notअगरier_list);

पूर्णांक rpc_pipefs_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&rpc_pipefs_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_pipefs_notअगरier_रेजिस्टर);

व्योम rpc_pipefs_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&rpc_pipefs_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_pipefs_notअगरier_unरेजिस्टर);

अटल व्योम rpc_purge_list(रुको_queue_head_t *रुकोq, काष्ठा list_head *head,
		व्योम (*destroy_msg)(काष्ठा rpc_pipe_msg *), पूर्णांक err)
अणु
	काष्ठा rpc_pipe_msg *msg;

	अगर (list_empty(head))
		वापस;
	करो अणु
		msg = list_entry(head->next, काष्ठा rpc_pipe_msg, list);
		list_del_init(&msg->list);
		msg->त्रुटि_सं = err;
		destroy_msg(msg);
	पूर्ण जबतक (!list_empty(head));

	अगर (रुकोq)
		wake_up(रुकोq);
पूर्ण

अटल व्योम
rpc_समयout_upcall_queue(काष्ठा work_काष्ठा *work)
अणु
	LIST_HEAD(मुक्त_list);
	काष्ठा rpc_pipe *pipe =
		container_of(work, काष्ठा rpc_pipe, queue_समयout.work);
	व्योम (*destroy_msg)(काष्ठा rpc_pipe_msg *);
	काष्ठा dentry *dentry;

	spin_lock(&pipe->lock);
	destroy_msg = pipe->ops->destroy_msg;
	अगर (pipe->nपढ़ोers == 0) अणु
		list_splice_init(&pipe->pipe, &मुक्त_list);
		pipe->pipelen = 0;
	पूर्ण
	dentry = dget(pipe->dentry);
	spin_unlock(&pipe->lock);
	rpc_purge_list(dentry ? &RPC_I(d_inode(dentry))->रुकोq : शून्य,
			&मुक्त_list, destroy_msg, -ETIMEDOUT);
	dput(dentry);
पूर्ण

sमाप_प्रकार rpc_pipe_generic_upcall(काष्ठा file *filp, काष्ठा rpc_pipe_msg *msg,
				अक्षर __user *dst, माप_प्रकार buflen)
अणु
	अक्षर *data = (अक्षर *)msg->data + msg->copied;
	माप_प्रकार mlen = min(msg->len - msg->copied, buflen);
	अचिन्हित दीर्घ left;

	left = copy_to_user(dst, data, mlen);
	अगर (left == mlen) अणु
		msg->त्रुटि_सं = -EFAULT;
		वापस -EFAULT;
	पूर्ण

	mlen -= left;
	msg->copied += mlen;
	msg->त्रुटि_सं = 0;
	वापस mlen;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_pipe_generic_upcall);

/**
 * rpc_queue_upcall - queue an upcall message to userspace
 * @pipe: upcall pipe on which to queue given message
 * @msg: message to queue
 *
 * Call with an @inode created by rpc_mkpipe() to queue an upcall.
 * A userspace process may then later पढ़ो the upcall by perक्रमming a
 * पढ़ो on an खोलो file क्रम this inode.  It is up to the caller to
 * initialize the fields of @msg (other than @msg->list) appropriately.
 */
पूर्णांक
rpc_queue_upcall(काष्ठा rpc_pipe *pipe, काष्ठा rpc_pipe_msg *msg)
अणु
	पूर्णांक res = -EPIPE;
	काष्ठा dentry *dentry;

	spin_lock(&pipe->lock);
	अगर (pipe->nपढ़ोers) अणु
		list_add_tail(&msg->list, &pipe->pipe);
		pipe->pipelen += msg->len;
		res = 0;
	पूर्ण अन्यथा अगर (pipe->flags & RPC_PIPE_WAIT_FOR_OPEN) अणु
		अगर (list_empty(&pipe->pipe))
			queue_delayed_work(rpciod_workqueue,
					&pipe->queue_समयout,
					RPC_UPCALL_TIMEOUT);
		list_add_tail(&msg->list, &pipe->pipe);
		pipe->pipelen += msg->len;
		res = 0;
	पूर्ण
	dentry = dget(pipe->dentry);
	spin_unlock(&pipe->lock);
	अगर (dentry) अणु
		wake_up(&RPC_I(d_inode(dentry))->रुकोq);
		dput(dentry);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_queue_upcall);

अटल अंतरभूत व्योम
rpc_inode_setowner(काष्ठा inode *inode, व्योम *निजी)
अणु
	RPC_I(inode)->निजी = निजी;
पूर्ण

अटल व्योम
rpc_बंद_pipes(काष्ठा inode *inode)
अणु
	काष्ठा rpc_pipe *pipe = RPC_I(inode)->pipe;
	पूर्णांक need_release;
	LIST_HEAD(मुक्त_list);

	inode_lock(inode);
	spin_lock(&pipe->lock);
	need_release = pipe->nपढ़ोers != 0 || pipe->nग_लिखोrs != 0;
	pipe->nपढ़ोers = 0;
	list_splice_init(&pipe->in_upcall, &मुक्त_list);
	list_splice_init(&pipe->pipe, &मुक्त_list);
	pipe->pipelen = 0;
	pipe->dentry = शून्य;
	spin_unlock(&pipe->lock);
	rpc_purge_list(&RPC_I(inode)->रुकोq, &मुक्त_list, pipe->ops->destroy_msg, -EPIPE);
	pipe->nग_लिखोrs = 0;
	अगर (need_release && pipe->ops->release_pipe)
		pipe->ops->release_pipe(inode);
	cancel_delayed_work_sync(&pipe->queue_समयout);
	rpc_inode_setowner(inode, शून्य);
	RPC_I(inode)->pipe = शून्य;
	inode_unlock(inode);
पूर्ण

अटल काष्ठा inode *
rpc_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा rpc_inode *rpci;
	rpci = kmem_cache_alloc(rpc_inode_cachep, GFP_KERNEL);
	अगर (!rpci)
		वापस शून्य;
	वापस &rpci->vfs_inode;
पूर्ण

अटल व्योम
rpc_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(rpc_inode_cachep, RPC_I(inode));
पूर्ण

अटल पूर्णांक
rpc_pipe_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpc_pipe *pipe;
	पूर्णांक first_खोलो;
	पूर्णांक res = -ENXIO;

	inode_lock(inode);
	pipe = RPC_I(inode)->pipe;
	अगर (pipe == शून्य)
		जाओ out;
	first_खोलो = pipe->nपढ़ोers == 0 && pipe->nग_लिखोrs == 0;
	अगर (first_खोलो && pipe->ops->खोलो_pipe) अणु
		res = pipe->ops->खोलो_pipe(inode);
		अगर (res)
			जाओ out;
	पूर्ण
	अगर (filp->f_mode & FMODE_READ)
		pipe->nपढ़ोers++;
	अगर (filp->f_mode & FMODE_WRITE)
		pipe->nग_लिखोrs++;
	res = 0;
out:
	inode_unlock(inode);
	वापस res;
पूर्ण

अटल पूर्णांक
rpc_pipe_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpc_pipe *pipe;
	काष्ठा rpc_pipe_msg *msg;
	पूर्णांक last_बंद;

	inode_lock(inode);
	pipe = RPC_I(inode)->pipe;
	अगर (pipe == शून्य)
		जाओ out;
	msg = filp->निजी_data;
	अगर (msg != शून्य) अणु
		spin_lock(&pipe->lock);
		msg->त्रुटि_सं = -EAGAIN;
		list_del_init(&msg->list);
		spin_unlock(&pipe->lock);
		pipe->ops->destroy_msg(msg);
	पूर्ण
	अगर (filp->f_mode & FMODE_WRITE)
		pipe->nग_लिखोrs --;
	अगर (filp->f_mode & FMODE_READ) अणु
		pipe->nपढ़ोers --;
		अगर (pipe->nपढ़ोers == 0) अणु
			LIST_HEAD(मुक्त_list);
			spin_lock(&pipe->lock);
			list_splice_init(&pipe->pipe, &मुक्त_list);
			pipe->pipelen = 0;
			spin_unlock(&pipe->lock);
			rpc_purge_list(&RPC_I(inode)->रुकोq, &मुक्त_list,
					pipe->ops->destroy_msg, -EAGAIN);
		पूर्ण
	पूर्ण
	last_बंद = pipe->nग_लिखोrs == 0 && pipe->nपढ़ोers == 0;
	अगर (last_बंद && pipe->ops->release_pipe)
		pipe->ops->release_pipe(inode);
out:
	inode_unlock(inode);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
rpc_pipe_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा rpc_pipe *pipe;
	काष्ठा rpc_pipe_msg *msg;
	पूर्णांक res = 0;

	inode_lock(inode);
	pipe = RPC_I(inode)->pipe;
	अगर (pipe == शून्य) अणु
		res = -EPIPE;
		जाओ out_unlock;
	पूर्ण
	msg = filp->निजी_data;
	अगर (msg == शून्य) अणु
		spin_lock(&pipe->lock);
		अगर (!list_empty(&pipe->pipe)) अणु
			msg = list_entry(pipe->pipe.next,
					काष्ठा rpc_pipe_msg,
					list);
			list_move(&msg->list, &pipe->in_upcall);
			pipe->pipelen -= msg->len;
			filp->निजी_data = msg;
			msg->copied = 0;
		पूर्ण
		spin_unlock(&pipe->lock);
		अगर (msg == शून्य)
			जाओ out_unlock;
	पूर्ण
	/* NOTE: it is up to the callback to update msg->copied */
	res = pipe->ops->upcall(filp, msg, buf, len);
	अगर (res < 0 || msg->len == msg->copied) अणु
		filp->निजी_data = शून्य;
		spin_lock(&pipe->lock);
		list_del_init(&msg->list);
		spin_unlock(&pipe->lock);
		pipe->ops->destroy_msg(msg);
	पूर्ण
out_unlock:
	inode_unlock(inode);
	वापस res;
पूर्ण

अटल sमाप_प्रकार
rpc_pipe_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक res;

	inode_lock(inode);
	res = -EPIPE;
	अगर (RPC_I(inode)->pipe != शून्य)
		res = RPC_I(inode)->pipe->ops->करोwncall(filp, buf, len);
	inode_unlock(inode);
	वापस res;
पूर्ण

अटल __poll_t
rpc_pipe_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा rpc_inode *rpci = RPC_I(inode);
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;

	poll_रुको(filp, &rpci->रुकोq, रुको);

	inode_lock(inode);
	अगर (rpci->pipe == शून्य)
		mask |= EPOLLERR | EPOLLHUP;
	अन्यथा अगर (filp->निजी_data || !list_empty(&rpci->pipe->pipe))
		mask |= EPOLLIN | EPOLLRDNORM;
	inode_unlock(inode);
	वापस mask;
पूर्ण

अटल दीर्घ
rpc_pipe_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा rpc_pipe *pipe;
	पूर्णांक len;

	चयन (cmd) अणु
	हाल FIONREAD:
		inode_lock(inode);
		pipe = RPC_I(inode)->pipe;
		अगर (pipe == शून्य) अणु
			inode_unlock(inode);
			वापस -EPIPE;
		पूर्ण
		spin_lock(&pipe->lock);
		len = pipe->pipelen;
		अगर (filp->निजी_data) अणु
			काष्ठा rpc_pipe_msg *msg;
			msg = filp->निजी_data;
			len += msg->len - msg->copied;
		पूर्ण
		spin_unlock(&pipe->lock);
		inode_unlock(inode);
		वापस put_user(len, (पूर्णांक __user *)arg);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations rpc_pipe_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= rpc_pipe_पढ़ो,
	.ग_लिखो		= rpc_pipe_ग_लिखो,
	.poll		= rpc_pipe_poll,
	.unlocked_ioctl	= rpc_pipe_ioctl,
	.खोलो		= rpc_pipe_खोलो,
	.release	= rpc_pipe_release,
पूर्ण;

अटल पूर्णांक
rpc_show_info(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा rpc_clnt *clnt = m->निजी;

	rcu_पढ़ो_lock();
	seq_म_लिखो(m, "RPC server: %s\n",
			rcu_dereference(clnt->cl_xprt)->servername);
	seq_म_लिखो(m, "service: %s (%d) version %d\n", clnt->cl_program->name,
			clnt->cl_prog, clnt->cl_vers);
	seq_म_लिखो(m, "address: %s\n", rpc_peeraddr2str(clnt, RPC_DISPLAY_ADDR));
	seq_म_लिखो(m, "protocol: %s\n", rpc_peeraddr2str(clnt, RPC_DISPLAY_PROTO));
	seq_म_लिखो(m, "port: %s\n", rpc_peeraddr2str(clnt, RPC_DISPLAY_PORT));
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक
rpc_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा rpc_clnt *clnt = शून्य;
	पूर्णांक ret = single_खोलो(file, rpc_show_info, शून्य);

	अगर (!ret) अणु
		काष्ठा seq_file *m = file->निजी_data;

		spin_lock(&file->f_path.dentry->d_lock);
		अगर (!d_unhashed(file->f_path.dentry))
			clnt = RPC_I(inode)->निजी;
		अगर (clnt != शून्य && atomic_inc_not_zero(&clnt->cl_count)) अणु
			spin_unlock(&file->f_path.dentry->d_lock);
			m->निजी = clnt;
		पूर्ण अन्यथा अणु
			spin_unlock(&file->f_path.dentry->d_lock);
			single_release(inode, file);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
rpc_info_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	काष्ठा rpc_clnt *clnt = (काष्ठा rpc_clnt *)m->निजी;

	अगर (clnt)
		rpc_release_client(clnt);
	वापस single_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations rpc_info_operations = अणु
	.owner		= THIS_MODULE,
	.खोलो		= rpc_info_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= rpc_info_release,
पूर्ण;


/*
 * Description of fs contents.
 */
काष्ठा rpc_filelist अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा file_operations *i_fop;
	umode_t mode;
पूर्ण;

अटल काष्ठा inode *
rpc_get_inode(काष्ठा super_block *sb, umode_t mode)
अणु
	काष्ठा inode *inode = new_inode(sb);
	अगर (!inode)
		वापस शून्य;
	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	चयन (mode & S_IFMT) अणु
	हाल S_IFसूची:
		inode->i_fop = &simple_dir_operations;
		inode->i_op = &simple_dir_inode_operations;
		inc_nlink(inode);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस inode;
पूर्ण

अटल पूर्णांक __rpc_create_common(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       umode_t mode,
			       स्थिर काष्ठा file_operations *i_fop,
			       व्योम *निजी)
अणु
	काष्ठा inode *inode;

	d_drop(dentry);
	inode = rpc_get_inode(dir->i_sb, mode);
	अगर (!inode)
		जाओ out_err;
	inode->i_ino = iunique(dir->i_sb, 100);
	अगर (i_fop)
		inode->i_fop = i_fop;
	अगर (निजी)
		rpc_inode_setowner(inode, निजी);
	d_add(dentry, inode);
	वापस 0;
out_err:
	prपूर्णांकk(KERN_WARNING "%s: %s failed to allocate inode for dentry %pd\n",
			__खाता__, __func__, dentry);
	dput(dentry);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक __rpc_create(काष्ठा inode *dir, काष्ठा dentry *dentry,
			umode_t mode,
			स्थिर काष्ठा file_operations *i_fop,
			व्योम *निजी)
अणु
	पूर्णांक err;

	err = __rpc_create_common(dir, dentry, S_IFREG | mode, i_fop, निजी);
	अगर (err)
		वापस err;
	fsnotअगरy_create(dir, dentry);
	वापस 0;
पूर्ण

अटल पूर्णांक __rpc_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry,
		       umode_t mode,
		       स्थिर काष्ठा file_operations *i_fop,
		       व्योम *निजी)
अणु
	पूर्णांक err;

	err = __rpc_create_common(dir, dentry, S_IFसूची | mode, i_fop, निजी);
	अगर (err)
		वापस err;
	inc_nlink(dir);
	fsnotअगरy_सूची_गढ़ो(dir, dentry);
	वापस 0;
पूर्ण

अटल व्योम
init_pipe(काष्ठा rpc_pipe *pipe)
अणु
	pipe->nपढ़ोers = 0;
	pipe->nग_लिखोrs = 0;
	INIT_LIST_HEAD(&pipe->in_upcall);
	INIT_LIST_HEAD(&pipe->in_करोwncall);
	INIT_LIST_HEAD(&pipe->pipe);
	pipe->pipelen = 0;
	INIT_DELAYED_WORK(&pipe->queue_समयout,
			    rpc_समयout_upcall_queue);
	pipe->ops = शून्य;
	spin_lock_init(&pipe->lock);
	pipe->dentry = शून्य;
पूर्ण

व्योम rpc_destroy_pipe_data(काष्ठा rpc_pipe *pipe)
अणु
	kमुक्त(pipe);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_destroy_pipe_data);

काष्ठा rpc_pipe *rpc_mkpipe_data(स्थिर काष्ठा rpc_pipe_ops *ops, पूर्णांक flags)
अणु
	काष्ठा rpc_pipe *pipe;

	pipe = kzalloc(माप(काष्ठा rpc_pipe), GFP_KERNEL);
	अगर (!pipe)
		वापस ERR_PTR(-ENOMEM);
	init_pipe(pipe);
	pipe->ops = ops;
	pipe->flags = flags;
	वापस pipe;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_mkpipe_data);

अटल पूर्णांक __rpc_mkpipe_dentry(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       umode_t mode,
			       स्थिर काष्ठा file_operations *i_fop,
			       व्योम *निजी,
			       काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा rpc_inode *rpci;
	पूर्णांक err;

	err = __rpc_create_common(dir, dentry, S_IFIFO | mode, i_fop, निजी);
	अगर (err)
		वापस err;
	rpci = RPC_I(d_inode(dentry));
	rpci->निजी = निजी;
	rpci->pipe = pipe;
	fsnotअगरy_create(dir, dentry);
	वापस 0;
पूर्ण

अटल पूर्णांक __rpc_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;

	dget(dentry);
	ret = simple_सूची_हटाओ(dir, dentry);
	अगर (!ret)
		fsnotअगरy_सूची_हटाओ(dir, dentry);
	d_delete(dentry);
	dput(dentry);
	वापस ret;
पूर्ण

अटल पूर्णांक __rpc_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;

	dget(dentry);
	ret = simple_unlink(dir, dentry);
	अगर (!ret)
		fsnotअगरy_unlink(dir, dentry);
	d_delete(dentry);
	dput(dentry);
	वापस ret;
पूर्ण

अटल पूर्णांक __rpc_rmpipe(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	rpc_बंद_pipes(inode);
	वापस __rpc_unlink(dir, dentry);
पूर्ण

अटल काष्ठा dentry *__rpc_lookup_create_exclusive(काष्ठा dentry *parent,
					  स्थिर अक्षर *name)
अणु
	काष्ठा qstr q = QSTR_INIT(name, म_माप(name));
	काष्ठा dentry *dentry = d_hash_and_lookup(parent, &q);
	अगर (!dentry) अणु
		dentry = d_alloc(parent, &q);
		अगर (!dentry)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण
	अगर (d_really_is_negative(dentry))
		वापस dentry;
	dput(dentry);
	वापस ERR_PTR(-EEXIST);
पूर्ण

/*
 * FIXME: This probably has races.
 */
अटल व्योम __rpc_depopulate(काष्ठा dentry *parent,
			     स्थिर काष्ठा rpc_filelist *files,
			     पूर्णांक start, पूर्णांक eof)
अणु
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा dentry *dentry;
	काष्ठा qstr name;
	पूर्णांक i;

	क्रम (i = start; i < eof; i++) अणु
		name.name = files[i].name;
		name.len = म_माप(files[i].name);
		dentry = d_hash_and_lookup(parent, &name);

		अगर (dentry == शून्य)
			जारी;
		अगर (d_really_is_negative(dentry))
			जाओ next;
		चयन (d_inode(dentry)->i_mode & S_IFMT) अणु
			शेष:
				BUG();
			हाल S_IFREG:
				__rpc_unlink(dir, dentry);
				अवरोध;
			हाल S_IFसूची:
				__rpc_सूची_हटाओ(dir, dentry);
		पूर्ण
next:
		dput(dentry);
	पूर्ण
पूर्ण

अटल व्योम rpc_depopulate(काष्ठा dentry *parent,
			   स्थिर काष्ठा rpc_filelist *files,
			   पूर्णांक start, पूर्णांक eof)
अणु
	काष्ठा inode *dir = d_inode(parent);

	inode_lock_nested(dir, I_MUTEX_CHILD);
	__rpc_depopulate(parent, files, start, eof);
	inode_unlock(dir);
पूर्ण

अटल पूर्णांक rpc_populate(काष्ठा dentry *parent,
			स्थिर काष्ठा rpc_filelist *files,
			पूर्णांक start, पूर्णांक eof,
			व्योम *निजी)
अणु
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा dentry *dentry;
	पूर्णांक i, err;

	inode_lock(dir);
	क्रम (i = start; i < eof; i++) अणु
		dentry = __rpc_lookup_create_exclusive(parent, files[i].name);
		err = PTR_ERR(dentry);
		अगर (IS_ERR(dentry))
			जाओ out_bad;
		चयन (files[i].mode & S_IFMT) अणु
			शेष:
				BUG();
			हाल S_IFREG:
				err = __rpc_create(dir, dentry,
						files[i].mode,
						files[i].i_fop,
						निजी);
				अवरोध;
			हाल S_IFसूची:
				err = __rpc_सूची_गढ़ो(dir, dentry,
						files[i].mode,
						शून्य,
						निजी);
		पूर्ण
		अगर (err != 0)
			जाओ out_bad;
	पूर्ण
	inode_unlock(dir);
	वापस 0;
out_bad:
	__rpc_depopulate(parent, files, start, eof);
	inode_unlock(dir);
	prपूर्णांकk(KERN_WARNING "%s: %s failed to populate directory %pd\n",
			__खाता__, __func__, parent);
	वापस err;
पूर्ण

अटल काष्ठा dentry *rpc_सूची_गढ़ो_populate(काष्ठा dentry *parent,
		स्थिर अक्षर *name, umode_t mode, व्योम *निजी,
		पूर्णांक (*populate)(काष्ठा dentry *, व्योम *), व्योम *args_populate)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *dir = d_inode(parent);
	पूर्णांक error;

	inode_lock_nested(dir, I_MUTEX_PARENT);
	dentry = __rpc_lookup_create_exclusive(parent, name);
	अगर (IS_ERR(dentry))
		जाओ out;
	error = __rpc_सूची_गढ़ो(dir, dentry, mode, शून्य, निजी);
	अगर (error != 0)
		जाओ out_err;
	अगर (populate != शून्य) अणु
		error = populate(dentry, args_populate);
		अगर (error)
			जाओ err_सूची_हटाओ;
	पूर्ण
out:
	inode_unlock(dir);
	वापस dentry;
err_सूची_हटाओ:
	__rpc_सूची_हटाओ(dir, dentry);
out_err:
	dentry = ERR_PTR(error);
	जाओ out;
पूर्ण

अटल पूर्णांक rpc_सूची_हटाओ_depopulate(काष्ठा dentry *dentry,
		व्योम (*depopulate)(काष्ठा dentry *))
अणु
	काष्ठा dentry *parent;
	काष्ठा inode *dir;
	पूर्णांक error;

	parent = dget_parent(dentry);
	dir = d_inode(parent);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	अगर (depopulate != शून्य)
		depopulate(dentry);
	error = __rpc_सूची_हटाओ(dir, dentry);
	inode_unlock(dir);
	dput(parent);
	वापस error;
पूर्ण

/**
 * rpc_mkpipe_dentry - make an rpc_pipefs file क्रम kernel<->userspace
 *		       communication
 * @parent: dentry of directory to create new "pipe" in
 * @name: name of pipe
 * @निजी: निजी data to associate with the pipe, क्रम the caller's use
 * @pipe: &rpc_pipe containing input parameters
 *
 * Data is made available क्रम userspace to पढ़ो by calls to
 * rpc_queue_upcall().  The actual पढ़ोs will result in calls to
 * @ops->upcall, which will be called with the file poपूर्णांकer,
 * message, and userspace buffer to copy to.
 *
 * Writes can come at any समय, and करो not necessarily have to be
 * responses to upcalls.  They will result in calls to @msg->करोwncall.
 *
 * The @निजी argument passed here will be available to all these methods
 * from the file poपूर्णांकer, via RPC_I(file_inode(file))->निजी.
 */
काष्ठा dentry *rpc_mkpipe_dentry(काष्ठा dentry *parent, स्थिर अक्षर *name,
				 व्योम *निजी, काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *dir = d_inode(parent);
	umode_t umode = S_IFIFO | 0600;
	पूर्णांक err;

	अगर (pipe->ops->upcall == शून्य)
		umode &= ~0444;
	अगर (pipe->ops->करोwncall == शून्य)
		umode &= ~0222;

	inode_lock_nested(dir, I_MUTEX_PARENT);
	dentry = __rpc_lookup_create_exclusive(parent, name);
	अगर (IS_ERR(dentry))
		जाओ out;
	err = __rpc_mkpipe_dentry(dir, dentry, umode, &rpc_pipe_fops,
				  निजी, pipe);
	अगर (err)
		जाओ out_err;
out:
	inode_unlock(dir);
	वापस dentry;
out_err:
	dentry = ERR_PTR(err);
	prपूर्णांकk(KERN_WARNING "%s: %s() failed to create pipe %pd/%s (errno = %d)\n",
			__खाता__, __func__, parent, name,
			err);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_mkpipe_dentry);

/**
 * rpc_unlink - हटाओ a pipe
 * @dentry: dentry क्रम the pipe, as वापसed from rpc_mkpipe
 *
 * After this call, lookups will no दीर्घer find the pipe, and any
 * attempts to पढ़ो or ग_लिखो using preexisting खोलोs of the pipe will
 * वापस -EPIPE.
 */
पूर्णांक
rpc_unlink(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;
	काष्ठा inode *dir;
	पूर्णांक error = 0;

	parent = dget_parent(dentry);
	dir = d_inode(parent);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	error = __rpc_rmpipe(dir, dentry);
	inode_unlock(dir);
	dput(parent);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_unlink);

/**
 * rpc_init_pipe_dir_head - initialise a काष्ठा rpc_pipe_dir_head
 * @pdh: poपूर्णांकer to काष्ठा rpc_pipe_dir_head
 */
व्योम rpc_init_pipe_dir_head(काष्ठा rpc_pipe_dir_head *pdh)
अणु
	INIT_LIST_HEAD(&pdh->pdh_entries);
	pdh->pdh_dentry = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_init_pipe_dir_head);

/**
 * rpc_init_pipe_dir_object - initialise a काष्ठा rpc_pipe_dir_object
 * @pकरो: poपूर्णांकer to काष्ठा rpc_pipe_dir_object
 * @pकरो_ops: poपूर्णांकer to स्थिर काष्ठा rpc_pipe_dir_object_ops
 * @pकरो_data: poपूर्णांकer to caller-defined data
 */
व्योम rpc_init_pipe_dir_object(काष्ठा rpc_pipe_dir_object *pकरो,
		स्थिर काष्ठा rpc_pipe_dir_object_ops *pकरो_ops,
		व्योम *pकरो_data)
अणु
	INIT_LIST_HEAD(&pकरो->pकरो_head);
	pकरो->pकरो_ops = pकरो_ops;
	pकरो->pकरो_data = pकरो_data;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_init_pipe_dir_object);

अटल पूर्णांक
rpc_add_pipe_dir_object_locked(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	पूर्णांक ret = 0;

	अगर (pdh->pdh_dentry)
		ret = pकरो->pकरो_ops->create(pdh->pdh_dentry, pकरो);
	अगर (ret == 0)
		list_add_tail(&pकरो->pकरो_head, &pdh->pdh_entries);
	वापस ret;
पूर्ण

अटल व्योम
rpc_हटाओ_pipe_dir_object_locked(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	अगर (pdh->pdh_dentry)
		pकरो->pकरो_ops->destroy(pdh->pdh_dentry, pकरो);
	list_del_init(&pकरो->pकरो_head);
पूर्ण

/**
 * rpc_add_pipe_dir_object - associate a rpc_pipe_dir_object to a directory
 * @net: poपूर्णांकer to काष्ठा net
 * @pdh: poपूर्णांकer to काष्ठा rpc_pipe_dir_head
 * @pकरो: poपूर्णांकer to काष्ठा rpc_pipe_dir_object
 *
 */
पूर्णांक
rpc_add_pipe_dir_object(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	पूर्णांक ret = 0;

	अगर (list_empty(&pकरो->pकरो_head)) अणु
		काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

		mutex_lock(&sn->pipefs_sb_lock);
		ret = rpc_add_pipe_dir_object_locked(net, pdh, pकरो);
		mutex_unlock(&sn->pipefs_sb_lock);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_add_pipe_dir_object);

/**
 * rpc_हटाओ_pipe_dir_object - हटाओ a rpc_pipe_dir_object from a directory
 * @net: poपूर्णांकer to काष्ठा net
 * @pdh: poपूर्णांकer to काष्ठा rpc_pipe_dir_head
 * @pकरो: poपूर्णांकer to काष्ठा rpc_pipe_dir_object
 *
 */
व्योम
rpc_हटाओ_pipe_dir_object(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		काष्ठा rpc_pipe_dir_object *pकरो)
अणु
	अगर (!list_empty(&pकरो->pकरो_head)) अणु
		काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

		mutex_lock(&sn->pipefs_sb_lock);
		rpc_हटाओ_pipe_dir_object_locked(net, pdh, pकरो);
		mutex_unlock(&sn->pipefs_sb_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rpc_हटाओ_pipe_dir_object);

/**
 * rpc_find_or_alloc_pipe_dir_object
 * @net: poपूर्णांकer to काष्ठा net
 * @pdh: poपूर्णांकer to काष्ठा rpc_pipe_dir_head
 * @match: match काष्ठा rpc_pipe_dir_object to data
 * @alloc: allocate a new काष्ठा rpc_pipe_dir_object
 * @data: user defined data क्रम match() and alloc()
 *
 */
काष्ठा rpc_pipe_dir_object *
rpc_find_or_alloc_pipe_dir_object(काष्ठा net *net,
		काष्ठा rpc_pipe_dir_head *pdh,
		पूर्णांक (*match)(काष्ठा rpc_pipe_dir_object *, व्योम *),
		काष्ठा rpc_pipe_dir_object *(*alloc)(व्योम *),
		व्योम *data)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_pipe_dir_object *pकरो;

	mutex_lock(&sn->pipefs_sb_lock);
	list_क्रम_each_entry(pकरो, &pdh->pdh_entries, pकरो_head) अणु
		अगर (!match(pकरो, data))
			जारी;
		जाओ out;
	पूर्ण
	pकरो = alloc(data);
	अगर (!pकरो)
		जाओ out;
	rpc_add_pipe_dir_object_locked(net, pdh, pकरो);
out:
	mutex_unlock(&sn->pipefs_sb_lock);
	वापस pकरो;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_find_or_alloc_pipe_dir_object);

अटल व्योम
rpc_create_pipe_dir_objects(काष्ठा rpc_pipe_dir_head *pdh)
अणु
	काष्ठा rpc_pipe_dir_object *pकरो;
	काष्ठा dentry *dir = pdh->pdh_dentry;

	list_क्रम_each_entry(pकरो, &pdh->pdh_entries, pकरो_head)
		pकरो->pकरो_ops->create(dir, pकरो);
पूर्ण

अटल व्योम
rpc_destroy_pipe_dir_objects(काष्ठा rpc_pipe_dir_head *pdh)
अणु
	काष्ठा rpc_pipe_dir_object *pकरो;
	काष्ठा dentry *dir = pdh->pdh_dentry;

	list_क्रम_each_entry(pकरो, &pdh->pdh_entries, pकरो_head)
		pकरो->pकरो_ops->destroy(dir, pकरो);
पूर्ण

क्रमागत अणु
	RPCAUTH_info,
	RPCAUTH_खातापूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpc_filelist authfiles[] = अणु
	[RPCAUTH_info] = अणु
		.name = "info",
		.i_fop = &rpc_info_operations,
		.mode = S_IFREG | 0400,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rpc_clntdir_populate(काष्ठा dentry *dentry, व्योम *निजी)
अणु
	वापस rpc_populate(dentry,
			    authfiles, RPCAUTH_info, RPCAUTH_खातापूर्ण,
			    निजी);
पूर्ण

अटल व्योम rpc_clntdir_depopulate(काष्ठा dentry *dentry)
अणु
	rpc_depopulate(dentry, authfiles, RPCAUTH_info, RPCAUTH_खातापूर्ण);
पूर्ण

/**
 * rpc_create_client_dir - Create a new rpc_client directory in rpc_pipefs
 * @dentry: the parent of new directory
 * @name: the name of new directory
 * @rpc_client: rpc client to associate with this directory
 *
 * This creates a directory at the given @path associated with
 * @rpc_clnt, which will contain a file named "info" with some basic
 * inक्रमmation about the client, together with any "pipes" that may
 * later be created using rpc_mkpipe().
 */
काष्ठा dentry *rpc_create_client_dir(काष्ठा dentry *dentry,
				   स्थिर अक्षर *name,
				   काष्ठा rpc_clnt *rpc_client)
अणु
	काष्ठा dentry *ret;

	ret = rpc_सूची_गढ़ो_populate(dentry, name, 0555, शून्य,
				 rpc_clntdir_populate, rpc_client);
	अगर (!IS_ERR(ret)) अणु
		rpc_client->cl_pipedir_objects.pdh_dentry = ret;
		rpc_create_pipe_dir_objects(&rpc_client->cl_pipedir_objects);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * rpc_हटाओ_client_dir - Remove a directory created with rpc_create_client_dir()
 * @rpc_client: rpc_client क्रम the pipe
 */
पूर्णांक rpc_हटाओ_client_dir(काष्ठा rpc_clnt *rpc_client)
अणु
	काष्ठा dentry *dentry = rpc_client->cl_pipedir_objects.pdh_dentry;

	अगर (dentry == शून्य)
		वापस 0;
	rpc_destroy_pipe_dir_objects(&rpc_client->cl_pipedir_objects);
	rpc_client->cl_pipedir_objects.pdh_dentry = शून्य;
	वापस rpc_सूची_हटाओ_depopulate(dentry, rpc_clntdir_depopulate);
पूर्ण

अटल स्थिर काष्ठा rpc_filelist cache_pipefs_files[3] = अणु
	[0] = अणु
		.name = "channel",
		.i_fop = &cache_file_operations_pipefs,
		.mode = S_IFREG | 0600,
	पूर्ण,
	[1] = अणु
		.name = "content",
		.i_fop = &content_file_operations_pipefs,
		.mode = S_IFREG | 0400,
	पूर्ण,
	[2] = अणु
		.name = "flush",
		.i_fop = &cache_flush_operations_pipefs,
		.mode = S_IFREG | 0600,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rpc_cachedir_populate(काष्ठा dentry *dentry, व्योम *निजी)
अणु
	वापस rpc_populate(dentry,
			    cache_pipefs_files, 0, 3,
			    निजी);
पूर्ण

अटल व्योम rpc_cachedir_depopulate(काष्ठा dentry *dentry)
अणु
	rpc_depopulate(dentry, cache_pipefs_files, 0, 3);
पूर्ण

काष्ठा dentry *rpc_create_cache_dir(काष्ठा dentry *parent, स्थिर अक्षर *name,
				    umode_t umode, काष्ठा cache_detail *cd)
अणु
	वापस rpc_सूची_गढ़ो_populate(parent, name, umode, शून्य,
			rpc_cachedir_populate, cd);
पूर्ण

व्योम rpc_हटाओ_cache_dir(काष्ठा dentry *dentry)
अणु
	rpc_सूची_हटाओ_depopulate(dentry, rpc_cachedir_depopulate);
पूर्ण

/*
 * populate the fileप्रणाली
 */
अटल स्थिर काष्ठा super_operations s_ops = अणु
	.alloc_inode	= rpc_alloc_inode,
	.मुक्त_inode	= rpc_मुक्त_inode,
	.statfs		= simple_statfs,
पूर्ण;

#घोषणा RPCAUTH_GSSMAGIC 0x67596969

/*
 * We have a single directory with 1 node in it.
 */
क्रमागत अणु
	RPCAUTH_lockd,
	RPCAUTH_mount,
	RPCAUTH_nfs,
	RPCAUTH_porपंचांगap,
	RPCAUTH_statd,
	RPCAUTH_nfsd4_cb,
	RPCAUTH_cache,
	RPCAUTH_nfsd,
	RPCAUTH_gssd,
	RPCAUTH_Rootखातापूर्ण
पूर्ण;

अटल स्थिर काष्ठा rpc_filelist files[] = अणु
	[RPCAUTH_lockd] = अणु
		.name = "lockd",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_mount] = अणु
		.name = "mount",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_nfs] = अणु
		.name = "nfs",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_porपंचांगap] = अणु
		.name = "portmap",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_statd] = अणु
		.name = "statd",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_nfsd4_cb] = अणु
		.name = "nfsd4_cb",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_cache] = अणु
		.name = "cache",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_nfsd] = अणु
		.name = "nfsd",
		.mode = S_IFसूची | 0555,
	पूर्ण,
	[RPCAUTH_gssd] = अणु
		.name = "gssd",
		.mode = S_IFसूची | 0555,
	पूर्ण,
पूर्ण;

/*
 * This call can be used only in RPC pipefs mount notअगरication hooks.
 */
काष्ठा dentry *rpc_d_lookup_sb(स्थिर काष्ठा super_block *sb,
			       स्थिर अचिन्हित अक्षर *dir_name)
अणु
	काष्ठा qstr dir = QSTR_INIT(dir_name, म_माप(dir_name));
	वापस d_hash_and_lookup(sb->s_root, &dir);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_d_lookup_sb);

पूर्णांक rpc_pipefs_init_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	sn->gssd_dummy = rpc_mkpipe_data(&gssd_dummy_pipe_ops, 0);
	अगर (IS_ERR(sn->gssd_dummy))
		वापस PTR_ERR(sn->gssd_dummy);

	mutex_init(&sn->pipefs_sb_lock);
	sn->pipe_version = -1;
	वापस 0;
पूर्ण

व्योम rpc_pipefs_निकास_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	rpc_destroy_pipe_data(sn->gssd_dummy);
पूर्ण

/*
 * This call will be used क्रम per network namespace operations calls.
 * Note: Function will be वापसed with pipefs_sb_lock taken अगर superblock was
 * found. This lock have to be released by rpc_put_sb_net() when all operations
 * will be completed.
 */
काष्ठा super_block *rpc_get_sb_net(स्थिर काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	mutex_lock(&sn->pipefs_sb_lock);
	अगर (sn->pipefs_sb)
		वापस sn->pipefs_sb;
	mutex_unlock(&sn->pipefs_sb_lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_get_sb_net);

व्योम rpc_put_sb_net(स्थिर काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	WARN_ON(sn->pipefs_sb == शून्य);
	mutex_unlock(&sn->pipefs_sb_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_put_sb_net);

अटल स्थिर काष्ठा rpc_filelist gssd_dummy_clnt_dir[] = अणु
	[0] = अणु
		.name = "clntXX",
		.mode = S_IFसूची | 0555,
	पूर्ण,
पूर्ण;

अटल sमाप_प्रकार
dummy_करोwncall(काष्ठा file *filp, स्थिर अक्षर __user *src, माप_प्रकार len)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा rpc_pipe_ops gssd_dummy_pipe_ops = अणु
	.upcall		= rpc_pipe_generic_upcall,
	.करोwncall	= dummy_करोwncall,
पूर्ण;

/*
 * Here we present a bogus "info" file to keep rpc.gssd happy. We करोn't expect
 * that it will ever use this info to handle an upcall, but rpc.gssd expects
 * that this file will be there and have a certain क्रमmat.
 */
अटल पूर्णांक
rpc_dummy_info_show(काष्ठा seq_file *m, व्योम *v)
अणु
	seq_म_लिखो(m, "RPC server: %s\n", utsname()->nodename);
	seq_म_लिखो(m, "service: foo (1) version 0\n");
	seq_म_लिखो(m, "address: 127.0.0.1\n");
	seq_म_लिखो(m, "protocol: tcp\n");
	seq_म_लिखो(m, "port: 0\n");
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(rpc_dummy_info);

अटल स्थिर काष्ठा rpc_filelist gssd_dummy_info_file[] = अणु
	[0] = अणु
		.name = "info",
		.i_fop = &rpc_dummy_info_fops,
		.mode = S_IFREG | 0400,
	पूर्ण,
पूर्ण;

/**
 * rpc_gssd_dummy_populate - create a dummy gssd pipe
 * @root:	root of the rpc_pipefs fileप्रणाली
 * @pipe_data:	pipe data created when netns is initialized
 *
 * Create a dummy set of directories and a pipe that gssd can hold खोलो to
 * indicate that it is up and running.
 */
अटल काष्ठा dentry *
rpc_gssd_dummy_populate(काष्ठा dentry *root, काष्ठा rpc_pipe *pipe_data)
अणु
	पूर्णांक ret = 0;
	काष्ठा dentry *gssd_dentry;
	काष्ठा dentry *clnt_dentry = शून्य;
	काष्ठा dentry *pipe_dentry = शून्य;
	काष्ठा qstr q = QSTR_INIT(files[RPCAUTH_gssd].name,
				  म_माप(files[RPCAUTH_gssd].name));

	/* We should never get this far अगर "gssd" करोesn't exist */
	gssd_dentry = d_hash_and_lookup(root, &q);
	अगर (!gssd_dentry)
		वापस ERR_PTR(-ENOENT);

	ret = rpc_populate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1, शून्य);
	अगर (ret) अणु
		pipe_dentry = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	q.name = gssd_dummy_clnt_dir[0].name;
	q.len = म_माप(gssd_dummy_clnt_dir[0].name);
	clnt_dentry = d_hash_and_lookup(gssd_dentry, &q);
	अगर (!clnt_dentry) अणु
		__rpc_depopulate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1);
		pipe_dentry = ERR_PTR(-ENOENT);
		जाओ out;
	पूर्ण

	ret = rpc_populate(clnt_dentry, gssd_dummy_info_file, 0, 1, शून्य);
	अगर (ret) अणु
		__rpc_depopulate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1);
		pipe_dentry = ERR_PTR(ret);
		जाओ out;
	पूर्ण

	pipe_dentry = rpc_mkpipe_dentry(clnt_dentry, "gssd", शून्य, pipe_data);
	अगर (IS_ERR(pipe_dentry)) अणु
		__rpc_depopulate(clnt_dentry, gssd_dummy_info_file, 0, 1);
		__rpc_depopulate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1);
	पूर्ण
out:
	dput(clnt_dentry);
	dput(gssd_dentry);
	वापस pipe_dentry;
पूर्ण

अटल व्योम
rpc_gssd_dummy_depopulate(काष्ठा dentry *pipe_dentry)
अणु
	काष्ठा dentry *clnt_dir = pipe_dentry->d_parent;
	काष्ठा dentry *gssd_dir = clnt_dir->d_parent;

	dget(pipe_dentry);
	__rpc_rmpipe(d_inode(clnt_dir), pipe_dentry);
	__rpc_depopulate(clnt_dir, gssd_dummy_info_file, 0, 1);
	__rpc_depopulate(gssd_dir, gssd_dummy_clnt_dir, 0, 1);
	dput(pipe_dentry);
पूर्ण

अटल पूर्णांक
rpc_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *root, *gssd_dentry;
	काष्ठा net *net = sb->s_fs_info;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	पूर्णांक err;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = RPCAUTH_GSSMAGIC;
	sb->s_op = &s_ops;
	sb->s_d_op = &simple_dentry_operations;
	sb->s_समय_gran = 1;

	inode = rpc_get_inode(sb, S_IFसूची | 0555);
	sb->s_root = root = d_make_root(inode);
	अगर (!root)
		वापस -ENOMEM;
	अगर (rpc_populate(root, files, RPCAUTH_lockd, RPCAUTH_Rootखातापूर्ण, शून्य))
		वापस -ENOMEM;

	gssd_dentry = rpc_gssd_dummy_populate(root, sn->gssd_dummy);
	अगर (IS_ERR(gssd_dentry)) अणु
		__rpc_depopulate(root, files, RPCAUTH_lockd, RPCAUTH_Rootखातापूर्ण);
		वापस PTR_ERR(gssd_dentry);
	पूर्ण

	dprपूर्णांकk("RPC:       sending pipefs MOUNT notification for net %x%s\n",
		net->ns.inum, NET_NAME(net));
	mutex_lock(&sn->pipefs_sb_lock);
	sn->pipefs_sb = sb;
	err = blocking_notअगरier_call_chain(&rpc_pipefs_notअगरier_list,
					   RPC_PIPEFS_MOUNT,
					   sb);
	अगर (err)
		जाओ err_depopulate;
	mutex_unlock(&sn->pipefs_sb_lock);
	वापस 0;

err_depopulate:
	rpc_gssd_dummy_depopulate(gssd_dentry);
	blocking_notअगरier_call_chain(&rpc_pipefs_notअगरier_list,
					   RPC_PIPEFS_UMOUNT,
					   sb);
	sn->pipefs_sb = शून्य;
	__rpc_depopulate(root, files, RPCAUTH_lockd, RPCAUTH_Rootखातापूर्ण);
	mutex_unlock(&sn->pipefs_sb_lock);
	वापस err;
पूर्ण

bool
gssd_running(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_pipe *pipe = sn->gssd_dummy;

	वापस pipe->nपढ़ोers || pipe->nग_लिखोrs;
पूर्ण
EXPORT_SYMBOL_GPL(gssd_running);

अटल पूर्णांक rpc_fs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_keyed(fc, rpc_fill_super, get_net(fc->net_ns));
पूर्ण

अटल व्योम rpc_fs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	अगर (fc->s_fs_info)
		put_net(fc->s_fs_info);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations rpc_fs_context_ops = अणु
	.मुक्त		= rpc_fs_मुक्त_fc,
	.get_tree	= rpc_fs_get_tree,
पूर्ण;

अटल पूर्णांक rpc_init_fs_context(काष्ठा fs_context *fc)
अणु
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(fc->net_ns->user_ns);
	fc->ops = &rpc_fs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम rpc_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा net *net = sb->s_fs_info;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	mutex_lock(&sn->pipefs_sb_lock);
	अगर (sn->pipefs_sb != sb) अणु
		mutex_unlock(&sn->pipefs_sb_lock);
		जाओ out;
	पूर्ण
	sn->pipefs_sb = शून्य;
	dprपूर्णांकk("RPC:       sending pipefs UMOUNT notification for net %x%s\n",
		net->ns.inum, NET_NAME(net));
	blocking_notअगरier_call_chain(&rpc_pipefs_notअगरier_list,
					   RPC_PIPEFS_UMOUNT,
					   sb);
	mutex_unlock(&sn->pipefs_sb_lock);
out:
	समाप्त_litter_super(sb);
	put_net(net);
पूर्ण

अटल काष्ठा file_प्रणाली_type rpc_pipe_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "rpc_pipefs",
	.init_fs_context = rpc_init_fs_context,
	.समाप्त_sb	= rpc_समाप्त_sb,
पूर्ण;
MODULE_ALIAS_FS("rpc_pipefs");
MODULE_ALIAS("rpc_pipefs");

अटल व्योम
init_once(व्योम *foo)
अणु
	काष्ठा rpc_inode *rpci = (काष्ठा rpc_inode *) foo;

	inode_init_once(&rpci->vfs_inode);
	rpci->निजी = शून्य;
	rpci->pipe = शून्य;
	init_रुकोqueue_head(&rpci->रुकोq);
पूर्ण

पूर्णांक रेजिस्टर_rpc_pipefs(व्योम)
अणु
	पूर्णांक err;

	rpc_inode_cachep = kmem_cache_create("rpc_inode_cache",
				माप(काष्ठा rpc_inode),
				0, (SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
				init_once);
	अगर (!rpc_inode_cachep)
		वापस -ENOMEM;
	err = rpc_clients_notअगरier_रेजिस्टर();
	अगर (err)
		जाओ err_notअगरier;
	err = रेजिस्टर_fileप्रणाली(&rpc_pipe_fs_type);
	अगर (err)
		जाओ err_रेजिस्टर;
	वापस 0;

err_रेजिस्टर:
	rpc_clients_notअगरier_unरेजिस्टर();
err_notअगरier:
	kmem_cache_destroy(rpc_inode_cachep);
	वापस err;
पूर्ण

व्योम unरेजिस्टर_rpc_pipefs(व्योम)
अणु
	rpc_clients_notअगरier_unरेजिस्टर();
	unरेजिस्टर_fileप्रणाली(&rpc_pipe_fs_type);
	kmem_cache_destroy(rpc_inode_cachep);
पूर्ण
