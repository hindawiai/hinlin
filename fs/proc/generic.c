<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * proc/fs/generic.c --- generic routines क्रम the proc-fs
 *
 * This file contains generic proc-fs routines क्रम handling
 * directories and files.
 * 
 * Copyright (C) 1991, 1992 Linus Torvalds.
 * Copyright (C) 1997 Theoकरोre Ts'o
 */

#समावेश <linux/cache.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समय.स>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/mount.h>
#समावेश <linux/init.h>
#समावेश <linux/idr.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>

#समावेश "internal.h"

अटल DEFINE_RWLOCK(proc_subdir_lock);

काष्ठा kmem_cache *proc_dir_entry_cache __ro_after_init;

व्योम pde_मुक्त(काष्ठा proc_dir_entry *pde)
अणु
	अगर (S_ISLNK(pde->mode))
		kमुक्त(pde->data);
	अगर (pde->name != pde->अंतरभूत_name)
		kमुक्त(pde->name);
	kmem_cache_मुक्त(proc_dir_entry_cache, pde);
पूर्ण

अटल पूर्णांक proc_match(स्थिर अक्षर *name, काष्ठा proc_dir_entry *de, अचिन्हित पूर्णांक len)
अणु
	अगर (len < de->namelen)
		वापस -1;
	अगर (len > de->namelen)
		वापस 1;

	वापस स_भेद(name, de->name, len);
पूर्ण

अटल काष्ठा proc_dir_entry *pde_subdir_first(काष्ठा proc_dir_entry *dir)
अणु
	वापस rb_entry_safe(rb_first(&dir->subdir), काष्ठा proc_dir_entry,
			     subdir_node);
पूर्ण

अटल काष्ठा proc_dir_entry *pde_subdir_next(काष्ठा proc_dir_entry *dir)
अणु
	वापस rb_entry_safe(rb_next(&dir->subdir_node), काष्ठा proc_dir_entry,
			     subdir_node);
पूर्ण

अटल काष्ठा proc_dir_entry *pde_subdir_find(काष्ठा proc_dir_entry *dir,
					      स्थिर अक्षर *name,
					      अचिन्हित पूर्णांक len)
अणु
	काष्ठा rb_node *node = dir->subdir.rb_node;

	जबतक (node) अणु
		काष्ठा proc_dir_entry *de = rb_entry(node,
						     काष्ठा proc_dir_entry,
						     subdir_node);
		पूर्णांक result = proc_match(name, de, len);

		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस de;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool pde_subdir_insert(काष्ठा proc_dir_entry *dir,
			      काष्ठा proc_dir_entry *de)
अणु
	काष्ठा rb_root *root = &dir->subdir;
	काष्ठा rb_node **new = &root->rb_node, *parent = शून्य;

	/* Figure out where to put new node */
	जबतक (*new) अणु
		काष्ठा proc_dir_entry *this = rb_entry(*new,
						       काष्ठा proc_dir_entry,
						       subdir_node);
		पूर्णांक result = proc_match(de->name, this, de->namelen);

		parent = *new;
		अगर (result < 0)
			new = &(*new)->rb_left;
		अन्यथा अगर (result > 0)
			new = &(*new)->rb_right;
		अन्यथा
			वापस false;
	पूर्ण

	/* Add new node and rebalance tree. */
	rb_link_node(&de->subdir_node, parent, new);
	rb_insert_color(&de->subdir_node, root);
	वापस true;
पूर्ण

अटल पूर्णांक proc_notअगरy_change(काष्ठा user_namespace *mnt_userns,
			      काष्ठा dentry *dentry, काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा proc_dir_entry *de = PDE(inode);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (error)
		वापस error;

	setattr_copy(&init_user_ns, inode, iattr);
	mark_inode_dirty(inode);

	proc_set_user(de, inode->i_uid, inode->i_gid);
	de->mode = inode->i_mode;
	वापस 0;
पूर्ण

अटल पूर्णांक proc_getattr(काष्ठा user_namespace *mnt_userns,
			स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा proc_dir_entry *de = PDE(inode);
	अगर (de) अणु
		nlink_t nlink = READ_ONCE(de->nlink);
		अगर (nlink > 0) अणु
			set_nlink(inode, nlink);
		पूर्ण
	पूर्ण

	generic_fillattr(&init_user_ns, inode, stat);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations proc_file_inode_operations = अणु
	.setattr	= proc_notअगरy_change,
पूर्ण;

/*
 * This function parses a name such as "tty/driver/serial", and
 * वापसs the काष्ठा proc_dir_entry क्रम "/proc/tty/driver", and
 * वापसs "serial" in residual.
 */
अटल पूर्णांक __xlate_proc_name(स्थिर अक्षर *name, काष्ठा proc_dir_entry **ret,
			     स्थिर अक्षर **residual)
अणु
	स्थिर अक्षर     		*cp = name, *next;
	काष्ठा proc_dir_entry	*de;

	de = *ret ?: &proc_root;
	जबतक ((next = म_अक्षर(cp, '/')) != शून्य) अणु
		de = pde_subdir_find(de, cp, next - cp);
		अगर (!de) अणु
			WARN(1, "name '%s'\n", name);
			वापस -ENOENT;
		पूर्ण
		cp = next + 1;
	पूर्ण
	*residual = cp;
	*ret = de;
	वापस 0;
पूर्ण

अटल पूर्णांक xlate_proc_name(स्थिर अक्षर *name, काष्ठा proc_dir_entry **ret,
			   स्थिर अक्षर **residual)
अणु
	पूर्णांक rv;

	पढ़ो_lock(&proc_subdir_lock);
	rv = __xlate_proc_name(name, ret, residual);
	पढ़ो_unlock(&proc_subdir_lock);
	वापस rv;
पूर्ण

अटल DEFINE_IDA(proc_inum_ida);

#घोषणा PROC_DYNAMIC_FIRST 0xF0000000U

/*
 * Return an inode number between PROC_DYNAMIC_FIRST and
 * 0xffffffff, or zero on failure.
 */
पूर्णांक proc_alloc_inum(अचिन्हित पूर्णांक *inum)
अणु
	पूर्णांक i;

	i = ida_simple_get(&proc_inum_ida, 0, अच_पूर्णांक_उच्च - PROC_DYNAMIC_FIRST + 1,
			   GFP_KERNEL);
	अगर (i < 0)
		वापस i;

	*inum = PROC_DYNAMIC_FIRST + (अचिन्हित पूर्णांक)i;
	वापस 0;
पूर्ण

व्योम proc_मुक्त_inum(अचिन्हित पूर्णांक inum)
अणु
	ida_simple_हटाओ(&proc_inum_ida, inum - PROC_DYNAMIC_FIRST);
पूर्ण

अटल पूर्णांक proc_misc_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	अगर (atomic_पढ़ो(&PDE(d_inode(dentry))->in_use) < 0)
		वापस 0; /* revalidate */
	वापस 1;
पूर्ण

अटल पूर्णांक proc_misc_d_delete(स्थिर काष्ठा dentry *dentry)
अणु
	वापस atomic_पढ़ो(&PDE(d_inode(dentry))->in_use) < 0;
पूर्ण

अटल स्थिर काष्ठा dentry_operations proc_misc_dentry_ops = अणु
	.d_revalidate	= proc_misc_d_revalidate,
	.d_delete	= proc_misc_d_delete,
पूर्ण;

/*
 * Don't create negative dentries here, वापस -ENOENT by hand
 * instead.
 */
काष्ठा dentry *proc_lookup_de(काष्ठा inode *dir, काष्ठा dentry *dentry,
			      काष्ठा proc_dir_entry *de)
अणु
	काष्ठा inode *inode;

	पढ़ो_lock(&proc_subdir_lock);
	de = pde_subdir_find(de, dentry->d_name.name, dentry->d_name.len);
	अगर (de) अणु
		pde_get(de);
		पढ़ो_unlock(&proc_subdir_lock);
		inode = proc_get_inode(dir->i_sb, de);
		अगर (!inode)
			वापस ERR_PTR(-ENOMEM);
		d_set_d_op(dentry, de->proc_करोps);
		वापस d_splice_alias(inode, dentry);
	पूर्ण
	पढ़ो_unlock(&proc_subdir_lock);
	वापस ERR_PTR(-ENOENT);
पूर्ण

काष्ठा dentry *proc_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक flags)
अणु
	काष्ठा proc_fs_info *fs_info = proc_sb_info(dir->i_sb);

	अगर (fs_info->piकरोnly == PROC_PIDONLY_ON)
		वापस ERR_PTR(-ENOENT);

	वापस proc_lookup_de(dir, dentry, PDE(dir));
पूर्ण

/*
 * This वापसs non-zero अगर at खातापूर्ण, so that the /proc
 * root directory can use this and check अगर it should
 * जारी with the <pid> entries..
 *
 * Note that the VFS-layer करोesn't care about the वापस
 * value of the सूची_पढ़ो() call, as दीर्घ as it's non-negative
 * क्रम success..
 */
पूर्णांक proc_सूची_पढ़ो_de(काष्ठा file *file, काष्ठा dir_context *ctx,
		    काष्ठा proc_dir_entry *de)
अणु
	पूर्णांक i;

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;

	i = ctx->pos - 2;
	पढ़ो_lock(&proc_subdir_lock);
	de = pde_subdir_first(de);
	क्रम (;;) अणु
		अगर (!de) अणु
			पढ़ो_unlock(&proc_subdir_lock);
			वापस 0;
		पूर्ण
		अगर (!i)
			अवरोध;
		de = pde_subdir_next(de);
		i--;
	पूर्ण

	करो अणु
		काष्ठा proc_dir_entry *next;
		pde_get(de);
		पढ़ो_unlock(&proc_subdir_lock);
		अगर (!dir_emit(ctx, de->name, de->namelen,
			    de->low_ino, de->mode >> 12)) अणु
			pde_put(de);
			वापस 0;
		पूर्ण
		ctx->pos++;
		पढ़ो_lock(&proc_subdir_lock);
		next = pde_subdir_next(de);
		pde_put(de);
		de = next;
	पूर्ण जबतक (de);
	पढ़ो_unlock(&proc_subdir_lock);
	वापस 1;
पूर्ण

पूर्णांक proc_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा proc_fs_info *fs_info = proc_sb_info(inode->i_sb);

	अगर (fs_info->piकरोnly == PROC_PIDONLY_ON)
		वापस 1;

	वापस proc_सूची_पढ़ो_de(file, ctx, PDE(inode));
पूर्ण

/*
 * These are the generic /proc directory operations. They
 * use the in-memory "struct proc_dir_entry" tree to parse
 * the /proc directory.
 */
अटल स्थिर काष्ठा file_operations proc_dir_operations = अणु
	.llseek			= generic_file_llseek,
	.पढ़ो			= generic_पढ़ो_dir,
	.iterate_shared		= proc_सूची_पढ़ो,
पूर्ण;

अटल पूर्णांक proc_net_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations proc_net_dentry_ops = अणु
	.d_revalidate	= proc_net_d_revalidate,
	.d_delete	= always_delete_dentry,
पूर्ण;

/*
 * proc directories can करो almost nothing..
 */
अटल स्थिर काष्ठा inode_operations proc_dir_inode_operations = अणु
	.lookup		= proc_lookup,
	.getattr	= proc_getattr,
	.setattr	= proc_notअगरy_change,
पूर्ण;

/* वापसs the रेजिस्टरed entry, or मुक्तs dp and वापसs शून्य on failure */
काष्ठा proc_dir_entry *proc_रेजिस्टर(काष्ठा proc_dir_entry *dir,
		काष्ठा proc_dir_entry *dp)
अणु
	अगर (proc_alloc_inum(&dp->low_ino))
		जाओ out_मुक्त_entry;

	ग_लिखो_lock(&proc_subdir_lock);
	dp->parent = dir;
	अगर (pde_subdir_insert(dir, dp) == false) अणु
		WARN(1, "proc_dir_entry '%s/%s' already registered\n",
		     dir->name, dp->name);
		ग_लिखो_unlock(&proc_subdir_lock);
		जाओ out_मुक्त_inum;
	पूर्ण
	dir->nlink++;
	ग_लिखो_unlock(&proc_subdir_lock);

	वापस dp;
out_मुक्त_inum:
	proc_मुक्त_inum(dp->low_ino);
out_मुक्त_entry:
	pde_मुक्त(dp);
	वापस शून्य;
पूर्ण

अटल काष्ठा proc_dir_entry *__proc_create(काष्ठा proc_dir_entry **parent,
					  स्थिर अक्षर *name,
					  umode_t mode,
					  nlink_t nlink)
अणु
	काष्ठा proc_dir_entry *ent = शून्य;
	स्थिर अक्षर *fn;
	काष्ठा qstr qstr;

	अगर (xlate_proc_name(name, parent, &fn) != 0)
		जाओ out;
	qstr.name = fn;
	qstr.len = म_माप(fn);
	अगर (qstr.len == 0 || qstr.len >= 256) अणु
		WARN(1, "name len %u\n", qstr.len);
		वापस शून्य;
	पूर्ण
	अगर (qstr.len == 1 && fn[0] == '.') अणु
		WARN(1, "name '.'\n");
		वापस शून्य;
	पूर्ण
	अगर (qstr.len == 2 && fn[0] == '.' && fn[1] == '.') अणु
		WARN(1, "name '..'\n");
		वापस शून्य;
	पूर्ण
	अगर (*parent == &proc_root && name_to_पूर्णांक(&qstr) != ~0U) अणु
		WARN(1, "create '/proc/%s' by hand\n", qstr.name);
		वापस शून्य;
	पूर्ण
	अगर (is_empty_pde(*parent)) अणु
		WARN(1, "attempt to add to permanently empty directory");
		वापस शून्य;
	पूर्ण

	ent = kmem_cache_zalloc(proc_dir_entry_cache, GFP_KERNEL);
	अगर (!ent)
		जाओ out;

	अगर (qstr.len + 1 <= SIZखातापूर्ण_PDE_INLINE_NAME) अणु
		ent->name = ent->अंतरभूत_name;
	पूर्ण अन्यथा अणु
		ent->name = kदो_स्मृति(qstr.len + 1, GFP_KERNEL);
		अगर (!ent->name) अणु
			pde_मुक्त(ent);
			वापस शून्य;
		पूर्ण
	पूर्ण

	स_नकल(ent->name, fn, qstr.len + 1);
	ent->namelen = qstr.len;
	ent->mode = mode;
	ent->nlink = nlink;
	ent->subdir = RB_ROOT;
	refcount_set(&ent->refcnt, 1);
	spin_lock_init(&ent->pde_unload_lock);
	INIT_LIST_HEAD(&ent->pde_खोलोers);
	proc_set_user(ent, (*parent)->uid, (*parent)->gid);

	ent->proc_करोps = &proc_misc_dentry_ops;

out:
	वापस ent;
पूर्ण

काष्ठा proc_dir_entry *proc_symlink(स्थिर अक्षर *name,
		काष्ठा proc_dir_entry *parent, स्थिर अक्षर *dest)
अणु
	काष्ठा proc_dir_entry *ent;

	ent = __proc_create(&parent, name,
			  (S_IFLNK | S_IRUGO | S_IWUGO | S_IXUGO),1);

	अगर (ent) अणु
		ent->data = kदो_स्मृति((ent->size=म_माप(dest))+1, GFP_KERNEL);
		अगर (ent->data) अणु
			म_नकल((अक्षर*)ent->data,dest);
			ent->proc_iops = &proc_link_inode_operations;
			ent = proc_रेजिस्टर(parent, ent);
		पूर्ण अन्यथा अणु
			pde_मुक्त(ent);
			ent = शून्य;
		पूर्ण
	पूर्ण
	वापस ent;
पूर्ण
EXPORT_SYMBOL(proc_symlink);

काष्ठा proc_dir_entry *_proc_सूची_गढ़ो(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, व्योम *data, bool क्रमce_lookup)
अणु
	काष्ठा proc_dir_entry *ent;

	अगर (mode == 0)
		mode = S_IRUGO | S_IXUGO;

	ent = __proc_create(&parent, name, S_IFसूची | mode, 2);
	अगर (ent) अणु
		ent->data = data;
		ent->proc_dir_ops = &proc_dir_operations;
		ent->proc_iops = &proc_dir_inode_operations;
		अगर (क्रमce_lookup) अणु
			pde_क्रमce_lookup(ent);
		पूर्ण
		ent = proc_रेजिस्टर(parent, ent);
	पूर्ण
	वापस ent;
पूर्ण
EXPORT_SYMBOL_GPL(_proc_सूची_गढ़ो);

काष्ठा proc_dir_entry *proc_सूची_गढ़ो_data(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, व्योम *data)
अणु
	वापस _proc_सूची_गढ़ो(name, mode, parent, data, false);
पूर्ण
EXPORT_SYMBOL_GPL(proc_सूची_गढ़ो_data);

काष्ठा proc_dir_entry *proc_सूची_गढ़ो_mode(स्थिर अक्षर *name, umode_t mode,
				       काष्ठा proc_dir_entry *parent)
अणु
	वापस proc_सूची_गढ़ो_data(name, mode, parent, शून्य);
पूर्ण
EXPORT_SYMBOL(proc_सूची_गढ़ो_mode);

काष्ठा proc_dir_entry *proc_सूची_गढ़ो(स्थिर अक्षर *name,
		काष्ठा proc_dir_entry *parent)
अणु
	वापस proc_सूची_गढ़ो_data(name, 0, parent, शून्य);
पूर्ण
EXPORT_SYMBOL(proc_सूची_गढ़ो);

काष्ठा proc_dir_entry *proc_create_mount_poपूर्णांक(स्थिर अक्षर *name)
अणु
	umode_t mode = S_IFसूची | S_IRUGO | S_IXUGO;
	काष्ठा proc_dir_entry *ent, *parent = शून्य;

	ent = __proc_create(&parent, name, mode, 2);
	अगर (ent) अणु
		ent->data = शून्य;
		ent->proc_dir_ops = शून्य;
		ent->proc_iops = शून्य;
		ent = proc_रेजिस्टर(parent, ent);
	पूर्ण
	वापस ent;
पूर्ण
EXPORT_SYMBOL(proc_create_mount_poपूर्णांक);

काष्ठा proc_dir_entry *proc_create_reg(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry **parent, व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	अगर ((mode & S_IFMT) == 0)
		mode |= S_IFREG;
	अगर ((mode & S_IALLUGO) == 0)
		mode |= S_IRUGO;
	अगर (WARN_ON_ONCE(!S_ISREG(mode)))
		वापस शून्य;

	p = __proc_create(parent, name, mode, 1);
	अगर (p) अणु
		p->proc_iops = &proc_file_inode_operations;
		p->data = data;
	पूर्ण
	वापस p;
पूर्ण

अटल अंतरभूत व्योम pde_set_flags(काष्ठा proc_dir_entry *pde)
अणु
	अगर (pde->proc_ops->proc_flags & PROC_ENTRY_PERMANENT)
		pde->flags |= PROC_ENTRY_PERMANENT;
पूर्ण

काष्ठा proc_dir_entry *proc_create_data(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent,
		स्थिर काष्ठा proc_ops *proc_ops, व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	p->proc_ops = proc_ops;
	pde_set_flags(p);
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL(proc_create_data);
 
काष्ठा proc_dir_entry *proc_create(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा proc_dir_entry *parent,
				   स्थिर काष्ठा proc_ops *proc_ops)
अणु
	वापस proc_create_data(name, mode, parent, proc_ops, शून्य);
पूर्ण
EXPORT_SYMBOL(proc_create);

अटल पूर्णांक proc_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_dir_entry *de = PDE(inode);

	अगर (de->state_size)
		वापस seq_खोलो_निजी(file, de->seq_ops, de->state_size);
	वापस seq_खोलो(file, de->seq_ops);
पूर्ण

अटल पूर्णांक proc_seq_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_dir_entry *de = PDE(inode);

	अगर (de->state_size)
		वापस seq_release_निजी(inode, file);
	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा proc_ops proc_seq_ops = अणु
	/* not permanent -- can call पूर्णांकo arbitrary seq_operations */
	.proc_खोलो	= proc_seq_खोलो,
	.proc_पढ़ो_iter	= seq_पढ़ो_iter,
	.proc_lseek	= seq_lseek,
	.proc_release	= proc_seq_release,
पूर्ण;

काष्ठा proc_dir_entry *proc_create_seq_निजी(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent, स्थिर काष्ठा seq_operations *ops,
		अचिन्हित पूर्णांक state_size, व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	p->proc_ops = &proc_seq_ops;
	p->seq_ops = ops;
	p->state_size = state_size;
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL(proc_create_seq_निजी);

अटल पूर्णांक proc_single_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा proc_dir_entry *de = PDE(inode);

	वापस single_खोलो(file, de->single_show, de->data);
पूर्ण

अटल स्थिर काष्ठा proc_ops proc_single_ops = अणु
	/* not permanent -- can call पूर्णांकo arbitrary ->single_show */
	.proc_खोलो	= proc_single_खोलो,
	.proc_पढ़ो_iter = seq_पढ़ो_iter,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
पूर्ण;

काष्ठा proc_dir_entry *proc_create_single_data(स्थिर अक्षर *name, umode_t mode,
		काष्ठा proc_dir_entry *parent,
		पूर्णांक (*show)(काष्ठा seq_file *, व्योम *), व्योम *data)
अणु
	काष्ठा proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	अगर (!p)
		वापस शून्य;
	p->proc_ops = &proc_single_ops;
	p->single_show = show;
	वापस proc_रेजिस्टर(parent, p);
पूर्ण
EXPORT_SYMBOL(proc_create_single_data);

व्योम proc_set_size(काष्ठा proc_dir_entry *de, loff_t size)
अणु
	de->size = size;
पूर्ण
EXPORT_SYMBOL(proc_set_size);

व्योम proc_set_user(काष्ठा proc_dir_entry *de, kuid_t uid, kgid_t gid)
अणु
	de->uid = uid;
	de->gid = gid;
पूर्ण
EXPORT_SYMBOL(proc_set_user);

व्योम pde_put(काष्ठा proc_dir_entry *pde)
अणु
	अगर (refcount_dec_and_test(&pde->refcnt)) अणु
		proc_मुक्त_inum(pde->low_ino);
		pde_मुक्त(pde);
	पूर्ण
पूर्ण

/*
 * Remove a /proc entry and मुक्त it अगर it's not currently in use.
 */
व्योम हटाओ_proc_entry(स्थिर अक्षर *name, काष्ठा proc_dir_entry *parent)
अणु
	काष्ठा proc_dir_entry *de = शून्य;
	स्थिर अक्षर *fn = name;
	अचिन्हित पूर्णांक len;

	ग_लिखो_lock(&proc_subdir_lock);
	अगर (__xlate_proc_name(name, &parent, &fn) != 0) अणु
		ग_लिखो_unlock(&proc_subdir_lock);
		वापस;
	पूर्ण
	len = म_माप(fn);

	de = pde_subdir_find(parent, fn, len);
	अगर (de) अणु
		अगर (unlikely(pde_is_permanent(de))) अणु
			WARN(1, "removing permanent /proc entry '%s'", de->name);
			de = शून्य;
		पूर्ण अन्यथा अणु
			rb_erase(&de->subdir_node, &parent->subdir);
			अगर (S_ISसूची(de->mode))
				parent->nlink--;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&proc_subdir_lock);
	अगर (!de) अणु
		WARN(1, "name '%s'\n", name);
		वापस;
	पूर्ण

	proc_entry_runकरोwn(de);

	WARN(pde_subdir_first(de),
	     "%s: removing non-empty directory '%s/%s', leaking at least '%s'\n",
	     __func__, de->parent->name, de->name, pde_subdir_first(de)->name);
	pde_put(de);
पूर्ण
EXPORT_SYMBOL(हटाओ_proc_entry);

पूर्णांक हटाओ_proc_subtree(स्थिर अक्षर *name, काष्ठा proc_dir_entry *parent)
अणु
	काष्ठा proc_dir_entry *root = शून्य, *de, *next;
	स्थिर अक्षर *fn = name;
	अचिन्हित पूर्णांक len;

	ग_लिखो_lock(&proc_subdir_lock);
	अगर (__xlate_proc_name(name, &parent, &fn) != 0) अणु
		ग_लिखो_unlock(&proc_subdir_lock);
		वापस -ENOENT;
	पूर्ण
	len = म_माप(fn);

	root = pde_subdir_find(parent, fn, len);
	अगर (!root) अणु
		ग_लिखो_unlock(&proc_subdir_lock);
		वापस -ENOENT;
	पूर्ण
	अगर (unlikely(pde_is_permanent(root))) अणु
		ग_लिखो_unlock(&proc_subdir_lock);
		WARN(1, "removing permanent /proc entry '%s/%s'",
			root->parent->name, root->name);
		वापस -EINVAL;
	पूर्ण
	rb_erase(&root->subdir_node, &parent->subdir);

	de = root;
	जबतक (1) अणु
		next = pde_subdir_first(de);
		अगर (next) अणु
			अगर (unlikely(pde_is_permanent(next))) अणु
				ग_लिखो_unlock(&proc_subdir_lock);
				WARN(1, "removing permanent /proc entry '%s/%s'",
					next->parent->name, next->name);
				वापस -EINVAL;
			पूर्ण
			rb_erase(&next->subdir_node, &de->subdir);
			de = next;
			जारी;
		पूर्ण
		next = de->parent;
		अगर (S_ISसूची(de->mode))
			next->nlink--;
		ग_लिखो_unlock(&proc_subdir_lock);

		proc_entry_runकरोwn(de);
		अगर (de == root)
			अवरोध;
		pde_put(de);

		ग_लिखो_lock(&proc_subdir_lock);
		de = next;
	पूर्ण
	pde_put(root);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(हटाओ_proc_subtree);

व्योम *proc_get_parent_data(स्थिर काष्ठा inode *inode)
अणु
	काष्ठा proc_dir_entry *de = PDE(inode);
	वापस de->parent->data;
पूर्ण
EXPORT_SYMBOL_GPL(proc_get_parent_data);

व्योम proc_हटाओ(काष्ठा proc_dir_entry *de)
अणु
	अगर (de)
		हटाओ_proc_subtree(de->name, de->parent);
पूर्ण
EXPORT_SYMBOL(proc_हटाओ);

व्योम *PDE_DATA(स्थिर काष्ठा inode *inode)
अणु
	वापस __PDE_DATA(inode);
पूर्ण
EXPORT_SYMBOL(PDE_DATA);

/*
 * Pull a user buffer पूर्णांकo memory and pass it to the file's ग_लिखो handler अगर
 * one is supplied.  The ->ग_लिखो() method is permitted to modअगरy the
 * kernel-side buffer.
 */
sमाप_प्रकार proc_simple_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *ubuf, माप_प्रकार size,
			  loff_t *_pos)
अणु
	काष्ठा proc_dir_entry *pde = PDE(file_inode(f));
	अक्षर *buf;
	पूर्णांक ret;

	अगर (!pde->ग_लिखो)
		वापस -EACCES;
	अगर (size == 0 || size > PAGE_SIZE - 1)
		वापस -EINVAL;
	buf = memdup_user_nul(ubuf, size);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);
	ret = pde->ग_लिखो(f, buf, size);
	kमुक्त(buf);
	वापस ret == 0 ? size : ret;
पूर्ण
