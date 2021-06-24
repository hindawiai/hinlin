<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cache.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/pid_namespace.h>
#समावेश "internal.h"

/*
 * /proc/thपढ़ो_self:
 */
अटल स्थिर अक्षर *proc_thपढ़ो_self_get_link(काष्ठा dentry *dentry,
					     काष्ठा inode *inode,
					     काष्ठा delayed_call *करोne)
अणु
	काष्ठा pid_namespace *ns = proc_pid_ns(inode->i_sb);
	pid_t tgid = task_tgid_nr_ns(current, ns);
	pid_t pid = task_pid_nr_ns(current, ns);
	अक्षर *name;

	अगर (!pid)
		वापस ERR_PTR(-ENOENT);
	name = kदो_स्मृति(10 + 6 + 10 + 1, dentry ? GFP_KERNEL : GFP_ATOMIC);
	अगर (unlikely(!name))
		वापस dentry ? ERR_PTR(-ENOMEM) : ERR_PTR(-ECHILD);
	प्र_लिखो(name, "%u/task/%u", tgid, pid);
	set_delayed_call(करोne, kमुक्त_link, name);
	वापस name;
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_thपढ़ो_self_inode_operations = अणु
	.get_link	= proc_thपढ़ो_self_get_link,
पूर्ण;

अटल अचिन्हित thपढ़ो_self_inum __ro_after_init;

पूर्णांक proc_setup_thपढ़ो_self(काष्ठा super_block *s)
अणु
	काष्ठा inode *root_inode = d_inode(s->s_root);
	काष्ठा proc_fs_info *fs_info = proc_sb_info(s);
	काष्ठा dentry *thपढ़ो_self;
	पूर्णांक ret = -ENOMEM;

	inode_lock(root_inode);
	thपढ़ो_self = d_alloc_name(s->s_root, "thread-self");
	अगर (thपढ़ो_self) अणु
		काष्ठा inode *inode = new_inode(s);
		अगर (inode) अणु
			inode->i_ino = thपढ़ो_self_inum;
			inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
			inode->i_mode = S_IFLNK | S_IRWXUGO;
			inode->i_uid = GLOBAL_ROOT_UID;
			inode->i_gid = GLOBAL_ROOT_GID;
			inode->i_op = &proc_thपढ़ो_self_inode_operations;
			d_add(thपढ़ो_self, inode);
			ret = 0;
		पूर्ण अन्यथा अणु
			dput(thपढ़ो_self);
		पूर्ण
	पूर्ण
	inode_unlock(root_inode);

	अगर (ret)
		pr_err("proc_fill_super: can't allocate /proc/thread-self\n");
	अन्यथा
		fs_info->proc_thपढ़ो_self = thपढ़ो_self;

	वापस ret;
पूर्ण

व्योम __init proc_thपढ़ो_self_init(व्योम)
अणु
	proc_alloc_inum(&thपढ़ो_self_inum);
पूर्ण
