<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * debugfs पूर्णांकerface क्रम sunrpc
 *
 * (c) 2014 Jeff Layton <jlayton@primarydata.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश "netns.h"

अटल काष्ठा dentry *topdir;
अटल काष्ठा dentry *rpc_clnt_dir;
अटल काष्ठा dentry *rpc_xprt_dir;

अचिन्हित पूर्णांक rpc_inject_disconnect;

अटल पूर्णांक
tasks_show(काष्ठा seq_file *f, व्योम *v)
अणु
	u32 xid = 0;
	काष्ठा rpc_task *task = v;
	काष्ठा rpc_clnt *clnt = task->tk_client;
	स्थिर अक्षर *rpc_रुकोq = "none";

	अगर (RPC_IS_QUEUED(task))
		rpc_रुकोq = rpc_qname(task->tk_रुकोqueue);

	अगर (task->tk_rqstp)
		xid = be32_to_cpu(task->tk_rqstp->rq_xid);

	seq_म_लिखो(f, "%5u %04x %6d 0x%x 0x%x %8ld %ps %sv%u %s a:%ps q:%s\n",
		task->tk_pid, task->tk_flags, task->tk_status,
		clnt->cl_clid, xid, rpc_task_समयout(task), task->tk_ops,
		clnt->cl_program->name, clnt->cl_vers, rpc_proc_name(task),
		task->tk_action, rpc_रुकोq);
	वापस 0;
पूर्ण

अटल व्योम *
tasks_start(काष्ठा seq_file *f, loff_t *ppos)
	__acquires(&clnt->cl_lock)
अणु
	काष्ठा rpc_clnt *clnt = f->निजी;
	loff_t pos = *ppos;
	काष्ठा rpc_task *task;

	spin_lock(&clnt->cl_lock);
	list_क्रम_each_entry(task, &clnt->cl_tasks, tk_task)
		अगर (pos-- == 0)
			वापस task;
	वापस शून्य;
पूर्ण

अटल व्योम *
tasks_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	काष्ठा rpc_clnt *clnt = f->निजी;
	काष्ठा rpc_task *task = v;
	काष्ठा list_head *next = task->tk_task.next;

	++*pos;

	/* If there's another task on list, वापस it */
	अगर (next == &clnt->cl_tasks)
		वापस शून्य;
	वापस list_entry(next, काष्ठा rpc_task, tk_task);
पूर्ण

अटल व्योम
tasks_stop(काष्ठा seq_file *f, व्योम *v)
	__releases(&clnt->cl_lock)
अणु
	काष्ठा rpc_clnt *clnt = f->निजी;
	spin_unlock(&clnt->cl_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations tasks_seq_operations = अणु
	.start	= tasks_start,
	.next	= tasks_next,
	.stop	= tasks_stop,
	.show	= tasks_show,
पूर्ण;

अटल पूर्णांक tasks_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret = seq_खोलो(filp, &tasks_seq_operations);
	अगर (!ret) अणु
		काष्ठा seq_file *seq = filp->निजी_data;
		काष्ठा rpc_clnt *clnt = seq->निजी = inode->i_निजी;

		अगर (!atomic_inc_not_zero(&clnt->cl_count)) अणु
			seq_release(inode, filp);
			ret = -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
tasks_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा seq_file *seq = filp->निजी_data;
	काष्ठा rpc_clnt *clnt = seq->निजी;

	rpc_release_client(clnt);
	वापस seq_release(inode, filp);
पूर्ण

अटल स्थिर काष्ठा file_operations tasks_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= tasks_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= tasks_release,
पूर्ण;

अटल पूर्णांक करो_xprt_debugfs(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt *xprt, व्योम *numv)
अणु
	पूर्णांक len;
	अक्षर name[24]; /* enough क्रम "../../rpc_xprt/ + 8 hex digits + शून्य */
	अक्षर link[9]; /* enough क्रम 8 hex digits + शून्य */
	पूर्णांक *nump = numv;

	अगर (IS_ERR_OR_शून्य(xprt->debugfs))
		वापस 0;
	len = snम_लिखो(name, माप(name), "../../rpc_xprt/%s",
		       xprt->debugfs->d_name.name);
	अगर (len >= माप(name))
		वापस -1;
	अगर (*nump == 0)
		म_नकल(link, "xprt");
	अन्यथा अणु
		len = snम_लिखो(link, माप(link), "xprt%d", *nump);
		अगर (len >= माप(link))
			वापस -1;
	पूर्ण
	debugfs_create_symlink(link, clnt->cl_debugfs, name);
	(*nump)++;
	वापस 0;
पूर्ण

व्योम
rpc_clnt_debugfs_रेजिस्टर(काष्ठा rpc_clnt *clnt)
अणु
	पूर्णांक len;
	अक्षर name[9]; /* enough क्रम 8 hex digits + शून्य */
	पूर्णांक xprtnum = 0;

	len = snम_लिखो(name, माप(name), "%x", clnt->cl_clid);
	अगर (len >= माप(name))
		वापस;

	/* make the per-client dir */
	clnt->cl_debugfs = debugfs_create_dir(name, rpc_clnt_dir);

	/* make tasks file */
	debugfs_create_file("tasks", S_IFREG | 0400, clnt->cl_debugfs, clnt,
			    &tasks_fops);

	rpc_clnt_iterate_क्रम_each_xprt(clnt, करो_xprt_debugfs, &xprtnum);
पूर्ण

व्योम
rpc_clnt_debugfs_unरेजिस्टर(काष्ठा rpc_clnt *clnt)
अणु
	debugfs_हटाओ_recursive(clnt->cl_debugfs);
	clnt->cl_debugfs = शून्य;
पूर्ण

अटल पूर्णांक
xprt_info_show(काष्ठा seq_file *f, व्योम *v)
अणु
	काष्ठा rpc_xprt *xprt = f->निजी;

	seq_म_लिखो(f, "netid: %s\n", xprt->address_strings[RPC_DISPLAY_NETID]);
	seq_म_लिखो(f, "addr:  %s\n", xprt->address_strings[RPC_DISPLAY_ADDR]);
	seq_म_लिखो(f, "port:  %s\n", xprt->address_strings[RPC_DISPLAY_PORT]);
	seq_म_लिखो(f, "state: 0x%lx\n", xprt->state);
	वापस 0;
पूर्ण

अटल पूर्णांक
xprt_info_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक ret;
	काष्ठा rpc_xprt *xprt = inode->i_निजी;

	ret = single_खोलो(filp, xprt_info_show, xprt);

	अगर (!ret) अणु
		अगर (!xprt_get(xprt)) अणु
			single_release(inode, filp);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
xprt_info_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpc_xprt *xprt = inode->i_निजी;

	xprt_put(xprt);
	वापस single_release(inode, filp);
पूर्ण

अटल स्थिर काष्ठा file_operations xprt_info_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= xprt_info_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= xprt_info_release,
पूर्ण;

व्योम
rpc_xprt_debugfs_रेजिस्टर(काष्ठा rpc_xprt *xprt)
अणु
	पूर्णांक len, id;
	अटल atomic_t	cur_id;
	अक्षर		name[9]; /* 8 hex digits + शून्य term */

	id = (अचिन्हित पूर्णांक)atomic_inc_वापस(&cur_id);

	len = snम_लिखो(name, माप(name), "%x", id);
	अगर (len >= माप(name))
		वापस;

	/* make the per-client dir */
	xprt->debugfs = debugfs_create_dir(name, rpc_xprt_dir);

	/* make tasks file */
	debugfs_create_file("info", S_IFREG | 0400, xprt->debugfs, xprt,
			    &xprt_info_fops);

	atomic_set(&xprt->inject_disconnect, rpc_inject_disconnect);
पूर्ण

व्योम
rpc_xprt_debugfs_unरेजिस्टर(काष्ठा rpc_xprt *xprt)
अणु
	debugfs_हटाओ_recursive(xprt->debugfs);
	xprt->debugfs = शून्य;
पूर्ण

अटल पूर्णांक
fault_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	filp->निजी_data = kदो_स्मृति(128, GFP_KERNEL);
	अगर (!filp->निजी_data)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक
fault_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	kमुक्त(filp->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
fault_disconnect_पढ़ो(काष्ठा file *filp, अक्षर __user *user_buf,
		      माप_प्रकार len, loff_t *offset)
अणु
	अक्षर *buffer = (अक्षर *)filp->निजी_data;
	माप_प्रकार size;

	size = प्र_लिखो(buffer, "%u\n", rpc_inject_disconnect);
	वापस simple_पढ़ो_from_buffer(user_buf, len, offset, buffer, size);
पूर्ण

अटल sमाप_प्रकार
fault_disconnect_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *user_buf,
		       माप_प्रकार len, loff_t *offset)
अणु
	अक्षर buffer[16];

	अगर (len >= माप(buffer))
		len = माप(buffer) - 1;
	अगर (copy_from_user(buffer, user_buf, len))
		वापस -EFAULT;
	buffer[len] = '\0';
	अगर (kstrtouपूर्णांक(buffer, 10, &rpc_inject_disconnect))
		वापस -EINVAL;
	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations fault_disconnect_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= fault_खोलो,
	.पढ़ो		= fault_disconnect_पढ़ो,
	.ग_लिखो		= fault_disconnect_ग_लिखो,
	.release	= fault_release,
पूर्ण;

व्योम __निकास
sunrpc_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(topdir);
	topdir = शून्य;
	rpc_clnt_dir = शून्य;
	rpc_xprt_dir = शून्य;
पूर्ण

व्योम __init
sunrpc_debugfs_init(व्योम)
अणु
	काष्ठा dentry *rpc_fault_dir;

	topdir = debugfs_create_dir("sunrpc", शून्य);

	rpc_clnt_dir = debugfs_create_dir("rpc_clnt", topdir);

	rpc_xprt_dir = debugfs_create_dir("rpc_xprt", topdir);

	rpc_fault_dir = debugfs_create_dir("inject_fault", topdir);

	debugfs_create_file("disconnect", S_IFREG | 0400, rpc_fault_dir, शून्य,
			    &fault_disconnect_fops);
पूर्ण
