<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/proc/net.c
 *
 *  Copyright (C) 2007
 *
 *  Author: Eric Biederman <ebiederm@xmission.com>
 *
 *  proc net directory handling functions
 */

#समावेश <linux/uaccess.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mount.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/uidgid.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/seq_file.h>

#समावेश "internal.h"

अटल अंतरभूत काष्ठा net *PDE_NET(काष्ठा proc_dir_entry *pde)
अणु
	वापस pde->parent->data;
पूर्ण

अटल काष्ठा net *get_proc_net(स्थिर काष्ठा inode *inode)
अणु
	वापस maybe_get_net(PDE_NET(PDE(inode)));
पूर्ण

अटल पूर्णांक seq_खोलो_net(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक state_size = PDE(inode)->state_size;
	काष्ठा seq_net_निजी *p;
	काष्ठा net *net;

	WARN_ON_ONCE(state_size < माप(*p));

	अगर (file->f_mode & FMODE_WRITE && !PDE(inode)->ग_लिखो)
		वापस -EACCES;

	net = get_proc_net(inode);
	अगर (!net)
		वापस -ENXIO;

	p = __seq_खोलो_निजी(file, PDE(inode)->seq_ops, state_size);
	अगर (!p) अणु
		put_net(net);
		वापस -ENOMEM;
	पूर्ण
#अगर_घोषित CONFIG_NET_NS
	p->net = net;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक seq_release_net(काष्ठा inode *ino, काष्ठा file *f)
अणु
	काष्ठा seq_file *seq = f->निजी_data;

	put_net(seq_file_net(seq));
	seq_release_निजी(ino, f);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा proc_ops proc_net_seq_ops = अणु
	.proc_खोलो	= seq_खोलो_net,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= proc_simple_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= seq_release_net,
पूर्ण;

पूर्णांक bpf_iter_init_seq_net(व्योम *priv_data, काष्ठा bpf_iter_aux_info *aux)
अणु
#अगर_घोषित CONFIG_NET_NS
	काष्ठा seq_net_निजी *p = priv_data;

	p->net = get_net(current->nsproxy->net_ns);
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम bpf_iter_fini_seq_net(व्योम *priv_data)
अणु
#अगर_घोषित CONFIG_NET_NS
	काष्ठा seq_net_निजी *p = priv_data;

	put_net(p->net);
#पूर्ण_अगर
पूर्ण

काष्ठा proc_dir_entry *proc_create_net_data(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, स्थिर काष्ठा seq_operations *ops,
		अचिन्हित पूर्णांक state_size, व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	pde_क्रमce_lookup(p);
	p->proc_ops = &proc_net_seq_ops;
	p->seq_ops = ops;
	p->state_size = state_size;
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL_GPL(proc_create_net_data);

/**
 * proc_create_net_data_ग_लिखो - Create a writable net_ns-specअगरic proc file
 * @name: The name of the file.
 * @mode: The file's access mode.
 * @parent: The parent directory in which to create.
 * @ops: The seq_file ops with which to पढ़ो the file.
 * @ग_लिखो: The ग_लिखो method with which to 'modify' the file.
 * @data: Data क्रम retrieval by PDE_DATA().
 *
 * Create a network namespaced proc file in the @parent directory with the
 * specअगरied @name and @mode that allows पढ़ोing of a file that displays a
 * series of elements and also provides क्रम the file accepting ग_लिखोs that have
 * some arbitrary effect.
 *
 * The functions in the @ops table are used to iterate over items to be
 * presented and extract the पढ़ोable content using the seq_file पूर्णांकerface.
 *
 * The @ग_लिखो function is called with the data copied पूर्णांकo a kernel space
 * scratch buffer and has a NUL appended क्रम convenience.  The buffer may be
 * modअगरied by the @ग_लिखो function.  @ग_लिखो should वापस 0 on success.
 *
 * The @data value is accessible from the @show and @ग_लिखो functions by calling
 * PDE_DATA() on the file inode.  The network namespace must be accessed by
 * calling seq_file_net() on the seq_file काष्ठा.
 */
काष्ठा proc_dir_entry *proc_create_net_data_ग_लिखो(स्थिर अक्षर *name, umode_t mode,
						  काष्ठा proc_dir_entry *parent,
						  स्थिर काष्ठा seq_operations *ops,
						  proc_ग_लिखो_t ग_लिखो,
						  अचिन्हित पूर्णांक state_size, व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	pde_क्रमce_lookup(p);
	p->proc_ops = &proc_net_seq_ops;
	p->seq_ops = ops;
	p->state_size = state_size;
	p->ग_लिखो = ग_लिखो;
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL_GPL(proc_create_net_data_ग_लिखो);

अटल पूर्णांक single_खोलो_net(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_dir_entry *de = PDE(inode);
	काष्ठा net *net;
	पूर्णांक err;

	net = get_proc_net(inode);
	अगर (!net)
		वापस -ENXIO;

	err = single_खोलो(file, de->single_show, net);
	अगर (err)
		put_net(net);
	वापस err;
पूर्ण

अटल पूर्णांक single_release_net(काष्ठा inode *ino, काष्ठा file *f)
अणु
	काष्ठा seq_file *seq = f->निजी_data;
	put_net(seq->निजी);
	वापस single_release(ino, f);
पूर्ण

अटल स्थिर काष्ठा proc_ops proc_net_single_ops = अणु
	.proc_खोलो	= single_खोलो_net,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_ग_लिखो	= proc_simple_ग_लिखो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release_net,
पूर्ण;

काष्ठा proc_dir_entry *proc_create_net_single(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent,
		पूर्णांक (*show)(काष्ठा seq_file *, व्योम *), व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	pde_क्रमce_lookup(p);
	p->proc_ops = &proc_net_single_ops;
	p->single_show = show;
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL_GPL(proc_create_net_single);

/**
 * proc_create_net_single_ग_लिखो - Create a writable net_ns-specअगरic proc file
 * @name: The name of the file.
 * @mode: The file's access mode.
 * @parent: The parent directory in which to create.
 * @show: The seqfile show method with which to पढ़ो the file.
 * @ग_लिखो: The ग_लिखो method with which to 'modify' the file.
 * @data: Data क्रम retrieval by PDE_DATA().
 *
 * Create a network-namespaced proc file in the @parent directory with the
 * specअगरied @name and @mode that allows पढ़ोing of a file that displays a
 * single element rather than a series and also provides क्रम the file accepting
 * ग_लिखोs that have some arbitrary effect.
 *
 * The @show function is called to extract the पढ़ोable content via the
 * seq_file पूर्णांकerface.
 *
 * The @ग_लिखो function is called with the data copied पूर्णांकo a kernel space
 * scratch buffer and has a NUL appended क्रम convenience.  The buffer may be
 * modअगरied by the @ग_लिखो function.  @ग_लिखो should वापस 0 on success.
 *
 * The @data value is accessible from the @show and @ग_लिखो functions by calling
 * PDE_DATA() on the file inode.  The network namespace must be accessed by
 * calling seq_file_single_net() on the seq_file काष्ठा.
 */
काष्ठा proc_dir_entry *proc_create_net_single_ग_लिखो(स्थिर अक्षर *name, umode_t mode,
						    काष्ठा proc_dir_entry *parent,
						    पूर्णांक (*show)(काष्ठा seq_file *, व्योम *),
						    proc_ग_लिखो_t ग_लिखो,
						    व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	pde_क्रमce_lookup(p);
	p->proc_ops = &proc_net_single_ops;
	p->single_show = show;
	p->ग_लिखो = ग_लिखो;
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL_GPL(proc_create_net_single_ग_लिखो);

अटल काष्ठा net *get_proc_task_net(काष्ठा inode *dir)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा nsproxy *ns;
	काष्ठा net *net = शून्य;

	rcu_पढ़ो_lock();
	task = pid_task(proc_pid(dir), PIDTYPE_PID);
	अगर (task != शून्य) अणु
		task_lock(task);
		ns = task->nsproxy;
		अगर (ns != शून्य)
			net = get_net(ns->net_ns);
		task_unlock(task);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस net;
पूर्ण

अटल काष्ठा dentry *proc_tgid_net_lookup(काष्ठा inode *dir,
		काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *de;
	काष्ठा net *net;

	de = ERR_PTR(-ENOENT);
	net = get_proc_task_net(dir);
	अगर (net != शून्य) अणु
		de = proc_lookup_de(dir, dentry, net->proc_net);
		put_net(net);
	पूर्ण
	वापस de;
पूर्ण

अटल पूर्णांक proc_tgid_net_getattr(काष्ठा user_namespace *mnt_userns,
				 स्थिर काष्ठा path *path, काष्ठा kstat *stat,
				 u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा net *net;

	net = get_proc_task_net(inode);

	generic_fillattr(&init_user_ns, inode, stat);

	अगर (net != शून्य) अणु
		stat->nlink = net->proc_net->nlink;
		put_net(net);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations proc_net_inode_operations = अणु
	.lookup		= proc_tgid_net_lookup,
	.getattr	= proc_tgid_net_getattr,
पूर्ण;

अटल पूर्णांक proc_tgid_net_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक ret;
	काष्ठा net *net;

	ret = -EINVAL;
	net = get_proc_task_net(file_inode(file));
	अगर (net != शून्य) अणु
		ret = proc_सूची_पढ़ो_de(file, ctx, net->proc_net);
		put_net(net);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations proc_net_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_tgid_net_सूची_पढ़ो,
पूर्ण;

अटल __net_init पूर्णांक proc_net_ns_init(काष्ठा net *net)
अणु
	काष्ठा proc_dir_entry *netd, *net_statd;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक err;

	err = -ENOMEM;
	netd = kmem_cache_zalloc(proc_dir_entry_cache, GFP_KERNEL);
	अगर (!netd)
		जाओ out;

	netd->subdir = RB_ROOT;
	netd->data = net;
	netd->nlink = 2;
	netd->namelen = 3;
	netd->parent = &proc_root;
	netd->name = netd->अंतरभूत_name;
	स_नकल(netd->name, "net", 4);

	uid = make_kuid(net->user_ns, 0);
	अगर (!uid_valid(uid))
		uid = netd->uid;

	gid = make_kgid(net->user_ns, 0);
	अगर (!gid_valid(gid))
		gid = netd->gid;

	proc_set_user(netd, uid, gid);

	err = -EEXIST;
	net_statd = proc_net_सूची_गढ़ो(net, "stat", netd);
	अगर (!net_statd)
		जाओ मुक्त_net;

	net->proc_net = netd;
	net->proc_net_stat = net_statd;
	वापस 0;

मुक्त_net:
	pde_मुक्त(netd);
out:
	वापस err;
पूर्ण

अटल __net_निकास व्योम proc_net_ns_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("stat", net->proc_net);
	pde_मुक्त(net->proc_net);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata proc_net_ns_ops = अणु
	.init = proc_net_ns_init,
	.निकास = proc_net_ns_निकास,
पूर्ण;

पूर्णांक __init proc_net_init(व्योम)
अणु
	proc_symlink("net", शून्य, "self/net");

	वापस रेजिस्टर_pernet_subsys(&proc_net_ns_ops);
पूर्ण
