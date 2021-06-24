<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cache.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/pid_namespace.h>
#समावेश "internal.h"

/*
 * /proc/self:
 */
अटल स्थिर अक्षर *proc_self_get_link(काष्ठा dentry *dentry,
				      काष्ठा inode *inode,
				      काष्ठा delayed_call *करोne)
अणु
	काष्ठा pid_namespace *ns = proc_pid_ns(inode->i_sb);
	pid_t tgid = task_tgid_nr_ns(current, ns);
	अक्षर *name;

	अगर (!tgid)
		वापस ERR_PTR(-ENOENT);
	/* max length of अचिन्हित पूर्णांक in decimal + शून्य term */
	name = kदो_स्मृति(10 + 1, dentry ? GFP_KERNEL : GFP_ATOMIC);
	अगर (unlikely(!name))
		वापस dentry ? ERR_PTR(-ENOMEM) : ERR_PTR(-ECHILD);
	प्र_लिखो(name, "%u", tgid);
	set_delayed_call(करोne, kमुक्त_link, name);
	वापस name;
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_self_inode_operations = अणु
	.get_link	= proc_self_get_link,
पूर्ण;

अटल अचिन्हित self_inum __ro_after_init;

पूर्णांक proc_setup_self(काष्ठा super_block *s)
अणु
	काष्ठा inode *root_inode = d_inode(s->s_root);
	काष्ठा proc_fs_info *fs_info = proc_sb_info(s);
	काष्ठा dentry *self;
	पूर्णांक ret = -ENOMEM;

	inode_lock(root_inode);
	self = d_alloc_name(s->s_root, "self");
	अगर (self) अणु
		काष्ठा inode *inode = new_inode(s);
		अगर (inode) अणु
			inode->i_ino = self_inum;
			inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
			inode->i_mode = S_IFLNK | S_IRWXUGO;
			inode->i_uid = GLOBAL_ROOT_UID;
			inode->i_gid = GLOBAL_ROOT_GID;
			inode->i_op = &proc_self_inode_operations;
			d_add(self, inode);
			ret = 0;
		पूर्ण अन्यथा अणु
			dput(self);
		पूर्ण
	पूर्ण
	inode_unlock(root_inode);

	अगर (ret)
		pr_err("proc_fill_super: can't allocate /proc/self\n");
	अन्यथा
		fs_info->proc_self = self;

	वापस ret;
पूर्ण

व्योम __init proc_self_init(व्योम)
अणु
	proc_alloc_inum(&self_inum);
पूर्ण
