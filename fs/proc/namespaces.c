<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/proc_fs.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/namei.h>
#समावेश <linux/file.h>
#समावेश <linux/utsname.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश "internal.h"


अटल स्थिर काष्ठा proc_ns_operations *ns_entries[] = अणु
#अगर_घोषित CONFIG_NET_NS
	&netns_operations,
#पूर्ण_अगर
#अगर_घोषित CONFIG_UTS_NS
	&utsns_operations,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPC_NS
	&ipcns_operations,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PID_NS
	&pidns_operations,
	&pidns_क्रम_children_operations,
#पूर्ण_अगर
#अगर_घोषित CONFIG_USER_NS
	&userns_operations,
#पूर्ण_अगर
	&mntns_operations,
#अगर_घोषित CONFIG_CGROUPS
	&cgroupns_operations,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TIME_NS
	&समयns_operations,
	&समयns_क्रम_children_operations,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर अक्षर *proc_ns_get_link(काष्ठा dentry *dentry,
				    काष्ठा inode *inode,
				    काष्ठा delayed_call *करोne)
अणु
	स्थिर काष्ठा proc_ns_operations *ns_ops = PROC_I(inode)->ns_ops;
	काष्ठा task_काष्ठा *task;
	काष्ठा path ns_path;
	पूर्णांक error = -EACCES;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	task = get_proc_task(inode);
	अगर (!task)
		वापस ERR_PTR(-EACCES);

	अगर (!ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS))
		जाओ out;

	error = ns_get_path(&ns_path, task, ns_ops);
	अगर (error)
		जाओ out;

	error = nd_jump_link(&ns_path);
out:
	put_task_काष्ठा(task);
	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक proc_ns_पढ़ोlink(काष्ठा dentry *dentry, अक्षर __user *buffer, पूर्णांक buflen)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	स्थिर काष्ठा proc_ns_operations *ns_ops = PROC_I(inode)->ns_ops;
	काष्ठा task_काष्ठा *task;
	अक्षर name[50];
	पूर्णांक res = -EACCES;

	task = get_proc_task(inode);
	अगर (!task)
		वापस res;

	अगर (ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS)) अणु
		res = ns_get_name(name, माप(name), task, ns_ops);
		अगर (res >= 0)
			res = पढ़ोlink_copy(buffer, buflen, name);
	पूर्ण
	put_task_काष्ठा(task);
	वापस res;
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_ns_link_inode_operations = अणु
	.पढ़ोlink	= proc_ns_पढ़ोlink,
	.get_link	= proc_ns_get_link,
	.setattr	= proc_setattr,
पूर्ण;

अटल काष्ठा dentry *proc_ns_instantiate(काष्ठा dentry *dentry,
	काष्ठा task_काष्ठा *task, स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा proc_ns_operations *ns_ops = ptr;
	काष्ठा inode *inode;
	काष्ठा proc_inode *ei;

	inode = proc_pid_make_inode(dentry->d_sb, task, S_IFLNK | S_IRWXUGO);
	अगर (!inode)
		वापस ERR_PTR(-ENOENT);

	ei = PROC_I(inode);
	inode->i_op = &proc_ns_link_inode_operations;
	ei->ns_ops = ns_ops;
	pid_update_inode(task, inode);

	d_set_d_op(dentry, &pid_dentry_operations);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक proc_ns_dir_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(file_inode(file));
	स्थिर काष्ठा proc_ns_operations **entry, **last;

	अगर (!task)
		वापस -ENOENT;

	अगर (!dir_emit_करोts(file, ctx))
		जाओ out;
	अगर (ctx->pos >= 2 + ARRAY_SIZE(ns_entries))
		जाओ out;
	entry = ns_entries + (ctx->pos - 2);
	last = &ns_entries[ARRAY_SIZE(ns_entries) - 1];
	जबतक (entry <= last) अणु
		स्थिर काष्ठा proc_ns_operations *ops = *entry;
		अगर (!proc_fill_cache(file, ctx, ops->name, म_माप(ops->name),
				     proc_ns_instantiate, task, ops))
			अवरोध;
		ctx->pos++;
		entry++;
	पूर्ण
out:
	put_task_काष्ठा(task);
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations proc_ns_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_ns_dir_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल काष्ठा dentry *proc_ns_dir_lookup(काष्ठा inode *dir,
				काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *task = get_proc_task(dir);
	स्थिर काष्ठा proc_ns_operations **entry, **last;
	अचिन्हित पूर्णांक len = dentry->d_name.len;
	काष्ठा dentry *res = ERR_PTR(-ENOENT);

	अगर (!task)
		जाओ out_no_task;

	last = &ns_entries[ARRAY_SIZE(ns_entries)];
	क्रम (entry = ns_entries; entry < last; entry++) अणु
		अगर (म_माप((*entry)->name) != len)
			जारी;
		अगर (!स_भेद(dentry->d_name.name, (*entry)->name, len))
			अवरोध;
	पूर्ण
	अगर (entry == last)
		जाओ out;

	res = proc_ns_instantiate(dentry, task, *entry);
out:
	put_task_काष्ठा(task);
out_no_task:
	वापस res;
पूर्ण

स्थिर काष्ठा inode_operations proc_ns_dir_inode_operations = अणु
	.lookup		= proc_ns_dir_lookup,
	.getattr	= pid_getattr,
	.setattr	= proc_setattr,
पूर्ण;
