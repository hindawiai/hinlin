<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * /proc/sys support
 */
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/poll.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/security.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/namei.h>
#समावेश <linux/mm.h>
#समावेश <linux/uपन.स>
#समावेश <linux/module.h>
#समावेश <linux/bpf-cgroup.h>
#समावेश <linux/mount.h>
#समावेश "internal.h"

अटल स्थिर काष्ठा dentry_operations proc_sys_dentry_operations;
अटल स्थिर काष्ठा file_operations proc_sys_file_operations;
अटल स्थिर काष्ठा inode_operations proc_sys_inode_operations;
अटल स्थिर काष्ठा file_operations proc_sys_dir_file_operations;
अटल स्थिर काष्ठा inode_operations proc_sys_dir_operations;

/* shared स्थिरants to be used in various sysctls */
स्थिर पूर्णांक sysctl_vals[] = अणु 0, 1, पूर्णांक_उच्च पूर्ण;
EXPORT_SYMBOL(sysctl_vals);

/* Support क्रम permanently empty directories */

काष्ठा ctl_table sysctl_mount_poपूर्णांक[] = अणु
	अणु पूर्ण
पूर्ण;

अटल bool is_empty_dir(काष्ठा ctl_table_header *head)
अणु
	वापस head->ctl_table[0].child == sysctl_mount_poपूर्णांक;
पूर्ण

अटल व्योम set_empty_dir(काष्ठा ctl_dir *dir)
अणु
	dir->header.ctl_table[0].child = sysctl_mount_poपूर्णांक;
पूर्ण

अटल व्योम clear_empty_dir(काष्ठा ctl_dir *dir)

अणु
	dir->header.ctl_table[0].child = शून्य;
पूर्ण

व्योम proc_sys_poll_notअगरy(काष्ठा ctl_table_poll *poll)
अणु
	अगर (!poll)
		वापस;

	atomic_inc(&poll->event);
	wake_up_पूर्णांकerruptible(&poll->रुको);
पूर्ण

अटल काष्ठा ctl_table root_table[] = अणु
	अणु
		.procname = "",
		.mode = S_IFसूची|S_IRUGO|S_IXUGO,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
अटल काष्ठा ctl_table_root sysctl_table_root = अणु
	.शेष_set.सूची.सeader = अणु
		अणुअणु.count = 1,
		  .nreg = 1,
		  .ctl_table = root_table पूर्णपूर्ण,
		.ctl_table_arg = root_table,
		.root = &sysctl_table_root,
		.set = &sysctl_table_root.शेष_set,
	पूर्ण,
पूर्ण;

अटल DEFINE_SPINLOCK(sysctl_lock);

अटल व्योम drop_sysctl_table(काष्ठा ctl_table_header *header);
अटल पूर्णांक sysctl_follow_link(काष्ठा ctl_table_header **phead,
	काष्ठा ctl_table **pentry);
अटल पूर्णांक insert_links(काष्ठा ctl_table_header *head);
अटल व्योम put_links(काष्ठा ctl_table_header *header);

अटल व्योम sysctl_prपूर्णांक_dir(काष्ठा ctl_dir *dir)
अणु
	अगर (dir->header.parent)
		sysctl_prपूर्णांक_dir(dir->header.parent);
	pr_cont("%s/", dir->header.ctl_table[0].procname);
पूर्ण

अटल पूर्णांक namecmp(स्थिर अक्षर *name1, पूर्णांक len1, स्थिर अक्षर *name2, पूर्णांक len2)
अणु
	पूर्णांक cmp;

	cmp = स_भेद(name1, name2, min(len1, len2));
	अगर (cmp == 0)
		cmp = len1 - len2;
	वापस cmp;
पूर्ण

/* Called under sysctl_lock */
अटल काष्ठा ctl_table *find_entry(काष्ठा ctl_table_header **phead,
	काष्ठा ctl_dir *dir, स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table *entry;
	काष्ठा rb_node *node = dir->root.rb_node;

	जबतक (node)
	अणु
		काष्ठा ctl_node *ctl_node;
		स्थिर अक्षर *procname;
		पूर्णांक cmp;

		ctl_node = rb_entry(node, काष्ठा ctl_node, node);
		head = ctl_node->header;
		entry = &head->ctl_table[ctl_node - head->node];
		procname = entry->procname;

		cmp = namecmp(name, namelen, procname, म_माप(procname));
		अगर (cmp < 0)
			node = node->rb_left;
		अन्यथा अगर (cmp > 0)
			node = node->rb_right;
		अन्यथा अणु
			*phead = head;
			वापस entry;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक insert_entry(काष्ठा ctl_table_header *head, काष्ठा ctl_table *entry)
अणु
	काष्ठा rb_node *node = &head->node[entry - head->ctl_table].node;
	काष्ठा rb_node **p = &head->parent->root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	स्थिर अक्षर *name = entry->procname;
	पूर्णांक namelen = म_माप(name);

	जबतक (*p) अणु
		काष्ठा ctl_table_header *parent_head;
		काष्ठा ctl_table *parent_entry;
		काष्ठा ctl_node *parent_node;
		स्थिर अक्षर *parent_name;
		पूर्णांक cmp;

		parent = *p;
		parent_node = rb_entry(parent, काष्ठा ctl_node, node);
		parent_head = parent_node->header;
		parent_entry = &parent_head->ctl_table[parent_node - parent_head->node];
		parent_name = parent_entry->procname;

		cmp = namecmp(name, namelen, parent_name, म_माप(parent_name));
		अगर (cmp < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &(*p)->rb_right;
		अन्यथा अणु
			pr_err("sysctl duplicate entry: ");
			sysctl_prपूर्णांक_dir(head->parent);
			pr_cont("/%s\n", entry->procname);
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	rb_link_node(node, parent, p);
	rb_insert_color(node, &head->parent->root);
	वापस 0;
पूर्ण

अटल व्योम erase_entry(काष्ठा ctl_table_header *head, काष्ठा ctl_table *entry)
अणु
	काष्ठा rb_node *node = &head->node[entry - head->ctl_table].node;

	rb_erase(node, &head->parent->root);
पूर्ण

अटल व्योम init_header(काष्ठा ctl_table_header *head,
	काष्ठा ctl_table_root *root, काष्ठा ctl_table_set *set,
	काष्ठा ctl_node *node, काष्ठा ctl_table *table)
अणु
	head->ctl_table = table;
	head->ctl_table_arg = table;
	head->used = 0;
	head->count = 1;
	head->nreg = 1;
	head->unरेजिस्टरing = शून्य;
	head->root = root;
	head->set = set;
	head->parent = शून्य;
	head->node = node;
	INIT_HLIST_HEAD(&head->inodes);
	अगर (node) अणु
		काष्ठा ctl_table *entry;
		क्रम (entry = table; entry->procname; entry++, node++)
			node->header = head;
	पूर्ण
पूर्ण

अटल व्योम erase_header(काष्ठा ctl_table_header *head)
अणु
	काष्ठा ctl_table *entry;
	क्रम (entry = head->ctl_table; entry->procname; entry++)
		erase_entry(head, entry);
पूर्ण

अटल पूर्णांक insert_header(काष्ठा ctl_dir *dir, काष्ठा ctl_table_header *header)
अणु
	काष्ठा ctl_table *entry;
	पूर्णांक err;

	/* Is this a permanently empty directory? */
	अगर (is_empty_dir(&dir->header))
		वापस -EROFS;

	/* Am I creating a permanently empty directory? */
	अगर (header->ctl_table == sysctl_mount_poपूर्णांक) अणु
		अगर (!RB_EMPTY_ROOT(&dir->root))
			वापस -EINVAL;
		set_empty_dir(dir);
	पूर्ण

	dir->header.nreg++;
	header->parent = dir;
	err = insert_links(header);
	अगर (err)
		जाओ fail_links;
	क्रम (entry = header->ctl_table; entry->procname; entry++) अणु
		err = insert_entry(header, entry);
		अगर (err)
			जाओ fail;
	पूर्ण
	वापस 0;
fail:
	erase_header(header);
	put_links(header);
fail_links:
	अगर (header->ctl_table == sysctl_mount_poपूर्णांक)
		clear_empty_dir(dir);
	header->parent = शून्य;
	drop_sysctl_table(&dir->header);
	वापस err;
पूर्ण

/* called under sysctl_lock */
अटल पूर्णांक use_table(काष्ठा ctl_table_header *p)
अणु
	अगर (unlikely(p->unरेजिस्टरing))
		वापस 0;
	p->used++;
	वापस 1;
पूर्ण

/* called under sysctl_lock */
अटल व्योम unuse_table(काष्ठा ctl_table_header *p)
अणु
	अगर (!--p->used)
		अगर (unlikely(p->unरेजिस्टरing))
			complete(p->unरेजिस्टरing);
पूर्ण

अटल व्योम proc_sys_invalidate_dcache(काष्ठा ctl_table_header *head)
अणु
	proc_invalidate_siblings_dcache(&head->inodes, &sysctl_lock);
पूर्ण

/* called under sysctl_lock, will reacquire अगर has to रुको */
अटल व्योम start_unरेजिस्टरing(काष्ठा ctl_table_header *p)
अणु
	/*
	 * अगर p->used is 0, nobody will ever touch that entry again;
	 * we'll eliminate all paths to it beक्रमe dropping sysctl_lock
	 */
	अगर (unlikely(p->used)) अणु
		काष्ठा completion रुको;
		init_completion(&रुको);
		p->unरेजिस्टरing = &रुको;
		spin_unlock(&sysctl_lock);
		रुको_क्रम_completion(&रुको);
	पूर्ण अन्यथा अणु
		/* anything non-शून्य; we'll never dereference it */
		p->unरेजिस्टरing = ERR_PTR(-EINVAL);
		spin_unlock(&sysctl_lock);
	पूर्ण
	/*
	 * Invalidate dentries क्रम unरेजिस्टरed sysctls: namespaced sysctls
	 * can have duplicate names and contaminate dcache very badly.
	 */
	proc_sys_invalidate_dcache(p);
	/*
	 * करो not हटाओ from the list until nobody holds it; walking the
	 * list in करो_sysctl() relies on that.
	 */
	spin_lock(&sysctl_lock);
	erase_header(p);
पूर्ण

अटल काष्ठा ctl_table_header *sysctl_head_grab(काष्ठा ctl_table_header *head)
अणु
	BUG_ON(!head);
	spin_lock(&sysctl_lock);
	अगर (!use_table(head))
		head = ERR_PTR(-ENOENT);
	spin_unlock(&sysctl_lock);
	वापस head;
पूर्ण

अटल व्योम sysctl_head_finish(काष्ठा ctl_table_header *head)
अणु
	अगर (!head)
		वापस;
	spin_lock(&sysctl_lock);
	unuse_table(head);
	spin_unlock(&sysctl_lock);
पूर्ण

अटल काष्ठा ctl_table_set *
lookup_header_set(काष्ठा ctl_table_root *root)
अणु
	काष्ठा ctl_table_set *set = &root->शेष_set;
	अगर (root->lookup)
		set = root->lookup(root);
	वापस set;
पूर्ण

अटल काष्ठा ctl_table *lookup_entry(काष्ठा ctl_table_header **phead,
				      काष्ठा ctl_dir *dir,
				      स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table *entry;

	spin_lock(&sysctl_lock);
	entry = find_entry(&head, dir, name, namelen);
	अगर (entry && use_table(head))
		*phead = head;
	अन्यथा
		entry = शून्य;
	spin_unlock(&sysctl_lock);
	वापस entry;
पूर्ण

अटल काष्ठा ctl_node *first_usable_entry(काष्ठा rb_node *node)
अणु
	काष्ठा ctl_node *ctl_node;

	क्रम (;node; node = rb_next(node)) अणु
		ctl_node = rb_entry(node, काष्ठा ctl_node, node);
		अगर (use_table(ctl_node->header))
			वापस ctl_node;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम first_entry(काष्ठा ctl_dir *dir,
	काष्ठा ctl_table_header **phead, काष्ठा ctl_table **pentry)
अणु
	काष्ठा ctl_table_header *head = शून्य;
	काष्ठा ctl_table *entry = शून्य;
	काष्ठा ctl_node *ctl_node;

	spin_lock(&sysctl_lock);
	ctl_node = first_usable_entry(rb_first(&dir->root));
	spin_unlock(&sysctl_lock);
	अगर (ctl_node) अणु
		head = ctl_node->header;
		entry = &head->ctl_table[ctl_node - head->node];
	पूर्ण
	*phead = head;
	*pentry = entry;
पूर्ण

अटल व्योम next_entry(काष्ठा ctl_table_header **phead, काष्ठा ctl_table **pentry)
अणु
	काष्ठा ctl_table_header *head = *phead;
	काष्ठा ctl_table *entry = *pentry;
	काष्ठा ctl_node *ctl_node = &head->node[entry - head->ctl_table];

	spin_lock(&sysctl_lock);
	unuse_table(head);

	ctl_node = first_usable_entry(rb_next(&ctl_node->node));
	spin_unlock(&sysctl_lock);
	head = शून्य;
	अगर (ctl_node) अणु
		head = ctl_node->header;
		entry = &head->ctl_table[ctl_node - head->node];
	पूर्ण
	*phead = head;
	*pentry = entry;
पूर्ण

/*
 * sysctl_perm करोes NOT grant the superuser all rights स्वतःmatically, because
 * some sysctl variables are पढ़ोonly even to root.
 */

अटल पूर्णांक test_perm(पूर्णांक mode, पूर्णांक op)
अणु
	अगर (uid_eq(current_euid(), GLOBAL_ROOT_UID))
		mode >>= 6;
	अन्यथा अगर (in_egroup_p(GLOBAL_ROOT_GID))
		mode >>= 3;
	अगर ((op & ~mode & (MAY_READ|MAY_WRITE|MAY_EXEC)) == 0)
		वापस 0;
	वापस -EACCES;
पूर्ण

अटल पूर्णांक sysctl_perm(काष्ठा ctl_table_header *head, काष्ठा ctl_table *table, पूर्णांक op)
अणु
	काष्ठा ctl_table_root *root = head->root;
	पूर्णांक mode;

	अगर (root->permissions)
		mode = root->permissions(head, table);
	अन्यथा
		mode = table->mode;

	वापस test_perm(mode, op);
पूर्ण

अटल काष्ठा inode *proc_sys_make_inode(काष्ठा super_block *sb,
		काष्ठा ctl_table_header *head, काष्ठा ctl_table *table)
अणु
	काष्ठा ctl_table_root *root = head->root;
	काष्ठा inode *inode;
	काष्ठा proc_inode *ei;

	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	inode->i_ino = get_next_ino();

	ei = PROC_I(inode);

	spin_lock(&sysctl_lock);
	अगर (unlikely(head->unरेजिस्टरing)) अणु
		spin_unlock(&sysctl_lock);
		iput(inode);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	ei->sysctl = head;
	ei->sysctl_entry = table;
	hlist_add_head_rcu(&ei->sibling_inodes, &head->inodes);
	head->count++;
	spin_unlock(&sysctl_lock);

	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_mode = table->mode;
	अगर (!S_ISसूची(table->mode)) अणु
		inode->i_mode |= S_IFREG;
		inode->i_op = &proc_sys_inode_operations;
		inode->i_fop = &proc_sys_file_operations;
	पूर्ण अन्यथा अणु
		inode->i_mode |= S_IFसूची;
		inode->i_op = &proc_sys_dir_operations;
		inode->i_fop = &proc_sys_dir_file_operations;
		अगर (is_empty_dir(head))
			make_empty_dir_inode(inode);
	पूर्ण

	अगर (root->set_ownership)
		root->set_ownership(head, table, &inode->i_uid, &inode->i_gid);
	अन्यथा अणु
		inode->i_uid = GLOBAL_ROOT_UID;
		inode->i_gid = GLOBAL_ROOT_GID;
	पूर्ण

	वापस inode;
पूर्ण

व्योम proc_sys_evict_inode(काष्ठा inode *inode, काष्ठा ctl_table_header *head)
अणु
	spin_lock(&sysctl_lock);
	hlist_del_init_rcu(&PROC_I(inode)->sibling_inodes);
	अगर (!--head->count)
		kमुक्त_rcu(head, rcu);
	spin_unlock(&sysctl_lock);
पूर्ण

अटल काष्ठा ctl_table_header *grab_header(काष्ठा inode *inode)
अणु
	काष्ठा ctl_table_header *head = PROC_I(inode)->sysctl;
	अगर (!head)
		head = &sysctl_table_root.शेष_set.सूची.सeader;
	वापस sysctl_head_grab(head);
पूर्ण

अटल काष्ठा dentry *proc_sys_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ctl_table_header *head = grab_header(dir);
	काष्ठा ctl_table_header *h = शून्य;
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	काष्ठा ctl_table *p;
	काष्ठा inode *inode;
	काष्ठा dentry *err = ERR_PTR(-ENOENT);
	काष्ठा ctl_dir *ctl_dir;
	पूर्णांक ret;

	अगर (IS_ERR(head))
		वापस ERR_CAST(head);

	ctl_dir = container_of(head, काष्ठा ctl_dir, header);

	p = lookup_entry(&h, ctl_dir, name->name, name->len);
	अगर (!p)
		जाओ out;

	अगर (S_ISLNK(p->mode)) अणु
		ret = sysctl_follow_link(&h, &p);
		err = ERR_PTR(ret);
		अगर (ret)
			जाओ out;
	पूर्ण

	inode = proc_sys_make_inode(dir->i_sb, h ? h : head, p);
	अगर (IS_ERR(inode)) अणु
		err = ERR_CAST(inode);
		जाओ out;
	पूर्ण

	d_set_d_op(dentry, &proc_sys_dentry_operations);
	err = d_splice_alias(inode, dentry);

out:
	अगर (h)
		sysctl_head_finish(h);
	sysctl_head_finish(head);
	वापस err;
पूर्ण

अटल sमाप_प्रकार proc_sys_call_handler(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		पूर्णांक ग_लिखो)
अणु
	काष्ठा inode *inode = file_inode(iocb->ki_filp);
	काष्ठा ctl_table_header *head = grab_header(inode);
	काष्ठा ctl_table *table = PROC_I(inode)->sysctl_entry;
	माप_प्रकार count = iov_iter_count(iter);
	अक्षर *kbuf;
	sमाप_प्रकार error;

	अगर (IS_ERR(head))
		वापस PTR_ERR(head);

	/*
	 * At this poपूर्णांक we know that the sysctl was not unरेजिस्टरed
	 * and won't be until we finish.
	 */
	error = -EPERM;
	अगर (sysctl_perm(head, table, ग_लिखो ? MAY_WRITE : MAY_READ))
		जाओ out;

	/* अगर that can happen at all, it should be -EINVAL, not -EISसूची */
	error = -EINVAL;
	अगर (!table->proc_handler)
		जाओ out;

	/* करोn't even try अगर the size is too large */
	error = -ENOMEM;
	अगर (count >= KMALLOC_MAX_SIZE)
		जाओ out;
	kbuf = kvzalloc(count + 1, GFP_KERNEL);
	अगर (!kbuf)
		जाओ out;

	अगर (ग_लिखो) अणु
		error = -EFAULT;
		अगर (!copy_from_iter_full(kbuf, count, iter))
			जाओ out_मुक्त_buf;
		kbuf[count] = '\0';
	पूर्ण

	error = BPF_CGROUP_RUN_PROG_SYSCTL(head, table, ग_लिखो, &kbuf, &count,
					   &iocb->ki_pos);
	अगर (error)
		जाओ out_मुक्त_buf;

	/* careful: calling conventions are nasty here */
	error = table->proc_handler(table, ग_लिखो, kbuf, &count, &iocb->ki_pos);
	अगर (error)
		जाओ out_मुक्त_buf;

	अगर (!ग_लिखो) अणु
		error = -EFAULT;
		अगर (copy_to_iter(kbuf, count, iter) < count)
			जाओ out_मुक्त_buf;
	पूर्ण

	error = count;
out_मुक्त_buf:
	kvमुक्त(kbuf);
out:
	sysctl_head_finish(head);

	वापस error;
पूर्ण

अटल sमाप_प्रकार proc_sys_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	वापस proc_sys_call_handler(iocb, iter, 0);
पूर्ण

अटल sमाप_प्रकार proc_sys_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	वापस proc_sys_call_handler(iocb, iter, 1);
पूर्ण

अटल पूर्णांक proc_sys_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा ctl_table_header *head = grab_header(inode);
	काष्ठा ctl_table *table = PROC_I(inode)->sysctl_entry;

	/* sysctl was unरेजिस्टरed */
	अगर (IS_ERR(head))
		वापस PTR_ERR(head);

	अगर (table->poll)
		filp->निजी_data = proc_sys_poll_event(table->poll);

	sysctl_head_finish(head);

	वापस 0;
पूर्ण

अटल __poll_t proc_sys_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा ctl_table_header *head = grab_header(inode);
	काष्ठा ctl_table *table = PROC_I(inode)->sysctl_entry;
	__poll_t ret = DEFAULT_POLLMASK;
	अचिन्हित दीर्घ event;

	/* sysctl was unरेजिस्टरed */
	अगर (IS_ERR(head))
		वापस EPOLLERR | EPOLLHUP;

	अगर (!table->proc_handler)
		जाओ out;

	अगर (!table->poll)
		जाओ out;

	event = (अचिन्हित दीर्घ)filp->निजी_data;
	poll_रुको(filp, &table->poll->रुको, रुको);

	अगर (event != atomic_पढ़ो(&table->poll->event)) अणु
		filp->निजी_data = proc_sys_poll_event(table->poll);
		ret = EPOLLIN | EPOLLRDNORM | EPOLLERR | EPOLLPRI;
	पूर्ण

out:
	sysctl_head_finish(head);

	वापस ret;
पूर्ण

अटल bool proc_sys_fill_cache(काष्ठा file *file,
				काष्ठा dir_context *ctx,
				काष्ठा ctl_table_header *head,
				काष्ठा ctl_table *table)
अणु
	काष्ठा dentry *child, *dir = file->f_path.dentry;
	काष्ठा inode *inode;
	काष्ठा qstr qname;
	ino_t ino = 0;
	अचिन्हित type = DT_UNKNOWN;

	qname.name = table->procname;
	qname.len  = म_माप(table->procname);
	qname.hash = full_name_hash(dir, qname.name, qname.len);

	child = d_lookup(dir, &qname);
	अगर (!child) अणु
		DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
		child = d_alloc_parallel(dir, &qname, &wq);
		अगर (IS_ERR(child))
			वापस false;
		अगर (d_in_lookup(child)) अणु
			काष्ठा dentry *res;
			inode = proc_sys_make_inode(dir->d_sb, head, table);
			अगर (IS_ERR(inode)) अणु
				d_lookup_करोne(child);
				dput(child);
				वापस false;
			पूर्ण
			d_set_d_op(child, &proc_sys_dentry_operations);
			res = d_splice_alias(inode, child);
			d_lookup_करोne(child);
			अगर (unlikely(res)) अणु
				अगर (IS_ERR(res)) अणु
					dput(child);
					वापस false;
				पूर्ण
				dput(child);
				child = res;
			पूर्ण
		पूर्ण
	पूर्ण
	inode = d_inode(child);
	ino  = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(child);
	वापस dir_emit(ctx, qname.name, qname.len, ino, type);
पूर्ण

अटल bool proc_sys_link_fill_cache(काष्ठा file *file,
				    काष्ठा dir_context *ctx,
				    काष्ठा ctl_table_header *head,
				    काष्ठा ctl_table *table)
अणु
	bool ret = true;

	head = sysctl_head_grab(head);
	अगर (IS_ERR(head))
		वापस false;

	/* It is not an error अगर we can not follow the link ignore it */
	अगर (sysctl_follow_link(&head, &table))
		जाओ out;

	ret = proc_sys_fill_cache(file, ctx, head, table);
out:
	sysctl_head_finish(head);
	वापस ret;
पूर्ण

अटल पूर्णांक scan(काष्ठा ctl_table_header *head, काष्ठा ctl_table *table,
		अचिन्हित दीर्घ *pos, काष्ठा file *file,
		काष्ठा dir_context *ctx)
अणु
	bool res;

	अगर ((*pos)++ < ctx->pos)
		वापस true;

	अगर (unlikely(S_ISLNK(table->mode)))
		res = proc_sys_link_fill_cache(file, ctx, head, table);
	अन्यथा
		res = proc_sys_fill_cache(file, ctx, head, table);

	अगर (res)
		ctx->pos = *pos;

	वापस res;
पूर्ण

अटल पूर्णांक proc_sys_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा ctl_table_header *head = grab_header(file_inode(file));
	काष्ठा ctl_table_header *h = शून्य;
	काष्ठा ctl_table *entry;
	काष्ठा ctl_dir *ctl_dir;
	अचिन्हित दीर्घ pos;

	अगर (IS_ERR(head))
		वापस PTR_ERR(head);

	ctl_dir = container_of(head, काष्ठा ctl_dir, header);

	अगर (!dir_emit_करोts(file, ctx))
		जाओ out;

	pos = 2;

	क्रम (first_entry(ctl_dir, &h, &entry); h; next_entry(&h, &entry)) अणु
		अगर (!scan(h, entry, &pos, file, ctx)) अणु
			sysctl_head_finish(h);
			अवरोध;
		पूर्ण
	पूर्ण
out:
	sysctl_head_finish(head);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_sys_permission(काष्ठा user_namespace *mnt_userns,
			       काष्ठा inode *inode, पूर्णांक mask)
अणु
	/*
	 * sysctl entries that are not ग_लिखोable,
	 * are _NOT_ ग_लिखोable, capabilities or not.
	 */
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table *table;
	पूर्णांक error;

	/* Executable files are not allowed under /proc/sys/ */
	अगर ((mask & MAY_EXEC) && S_ISREG(inode->i_mode))
		वापस -EACCES;

	head = grab_header(inode);
	अगर (IS_ERR(head))
		वापस PTR_ERR(head);

	table = PROC_I(inode)->sysctl_entry;
	अगर (!table) /* global root - r-xr-xr-x */
		error = mask & MAY_WRITE ? -EACCES : 0;
	अन्यथा /* Use the permissions on the sysctl table entry */
		error = sysctl_perm(head, table, mask & ~MAY_NOT_BLOCK);

	sysctl_head_finish(head);
	वापस error;
पूर्ण

अटल पूर्णांक proc_sys_setattr(काष्ठा user_namespace *mnt_userns,
			    काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	अगर (attr->ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID))
		वापस -EPERM;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक proc_sys_getattr(काष्ठा user_namespace *mnt_userns,
			    स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			    u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा ctl_table_header *head = grab_header(inode);
	काष्ठा ctl_table *table = PROC_I(inode)->sysctl_entry;

	अगर (IS_ERR(head))
		वापस PTR_ERR(head);

	generic_fillattr(&init_user_ns, inode, stat);
	अगर (table)
		stat->mode = (stat->mode & S_IFMT) | table->mode;

	sysctl_head_finish(head);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations proc_sys_file_operations = अणु
	.खोलो		= proc_sys_खोलो,
	.poll		= proc_sys_poll,
	.पढ़ो_iter	= proc_sys_पढ़ो,
	.ग_लिखो_iter	= proc_sys_ग_लिखो,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations proc_sys_dir_file_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= proc_sys_सूची_पढ़ो,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा inode_operations proc_sys_inode_operations = अणु
	.permission	= proc_sys_permission,
	.setattr	= proc_sys_setattr,
	.getattr	= proc_sys_getattr,
पूर्ण;

अटल स्थिर काष्ठा inode_operations proc_sys_dir_operations = अणु
	.lookup		= proc_sys_lookup,
	.permission	= proc_sys_permission,
	.setattr	= proc_sys_setattr,
	.getattr	= proc_sys_getattr,
पूर्ण;

अटल पूर्णांक proc_sys_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;
	वापस !PROC_I(d_inode(dentry))->sysctl->unरेजिस्टरing;
पूर्ण

अटल पूर्णांक proc_sys_delete(स्थिर काष्ठा dentry *dentry)
अणु
	वापस !!PROC_I(d_inode(dentry))->sysctl->unरेजिस्टरing;
पूर्ण

अटल पूर्णांक sysctl_is_seen(काष्ठा ctl_table_header *p)
अणु
	काष्ठा ctl_table_set *set = p->set;
	पूर्णांक res;
	spin_lock(&sysctl_lock);
	अगर (p->unरेजिस्टरing)
		res = 0;
	अन्यथा अगर (!set->is_seen)
		res = 1;
	अन्यथा
		res = set->is_seen(set);
	spin_unlock(&sysctl_lock);
	वापस res;
पूर्ण

अटल पूर्णांक proc_sys_compare(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा ctl_table_header *head;
	काष्ठा inode *inode;

	/* Although proc करोesn't have negative dentries, rcu-walk means
	 * that inode here can be शून्य */
	/* AV: can it, indeed? */
	inode = d_inode_rcu(dentry);
	अगर (!inode)
		वापस 1;
	अगर (name->len != len)
		वापस 1;
	अगर (स_भेद(name->name, str, len))
		वापस 1;
	head = rcu_dereference(PROC_I(inode)->sysctl);
	वापस !head || !sysctl_is_seen(head);
पूर्ण

अटल स्थिर काष्ठा dentry_operations proc_sys_dentry_operations = अणु
	.d_revalidate	= proc_sys_revalidate,
	.d_delete	= proc_sys_delete,
	.d_compare	= proc_sys_compare,
पूर्ण;

अटल काष्ठा ctl_dir *find_subdir(काष्ठा ctl_dir *dir,
				   स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table *entry;

	entry = find_entry(&head, dir, name, namelen);
	अगर (!entry)
		वापस ERR_PTR(-ENOENT);
	अगर (!S_ISसूची(entry->mode))
		वापस ERR_PTR(-ENOTसूची);
	वापस container_of(head, काष्ठा ctl_dir, header);
पूर्ण

अटल काष्ठा ctl_dir *new_dir(काष्ठा ctl_table_set *set,
			       स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा ctl_table *table;
	काष्ठा ctl_dir *new;
	काष्ठा ctl_node *node;
	अक्षर *new_name;

	new = kzalloc(माप(*new) + माप(काष्ठा ctl_node) +
		      माप(काष्ठा ctl_table)*2 +  namelen + 1,
		      GFP_KERNEL);
	अगर (!new)
		वापस शून्य;

	node = (काष्ठा ctl_node *)(new + 1);
	table = (काष्ठा ctl_table *)(node + 1);
	new_name = (अक्षर *)(table + 2);
	स_नकल(new_name, name, namelen);
	new_name[namelen] = '\0';
	table[0].procname = new_name;
	table[0].mode = S_IFसूची|S_IRUGO|S_IXUGO;
	init_header(&new->header, set->सूची.सeader.root, set, node, table);

	वापस new;
पूर्ण

/**
 * get_subdir - find or create a subdir with the specअगरied name.
 * @dir:  Directory to create the subdirectory in
 * @name: The name of the subdirectory to find or create
 * @namelen: The length of name
 *
 * Takes a directory with an elevated reference count so we know that
 * अगर we drop the lock the directory will not go away.  Upon success
 * the reference is moved from @dir to the वापसed subdirectory.
 * Upon error an error code is वापसed and the reference on @dir is
 * simply dropped.
 */
अटल काष्ठा ctl_dir *get_subdir(काष्ठा ctl_dir *dir,
				  स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा ctl_table_set *set = dir->header.set;
	काष्ठा ctl_dir *subdir, *new = शून्य;
	पूर्णांक err;

	spin_lock(&sysctl_lock);
	subdir = find_subdir(dir, name, namelen);
	अगर (!IS_ERR(subdir))
		जाओ found;
	अगर (PTR_ERR(subdir) != -ENOENT)
		जाओ failed;

	spin_unlock(&sysctl_lock);
	new = new_dir(set, name, namelen);
	spin_lock(&sysctl_lock);
	subdir = ERR_PTR(-ENOMEM);
	अगर (!new)
		जाओ failed;

	/* Was the subdir added जबतक we dropped the lock? */
	subdir = find_subdir(dir, name, namelen);
	अगर (!IS_ERR(subdir))
		जाओ found;
	अगर (PTR_ERR(subdir) != -ENOENT)
		जाओ failed;

	/* Nope.  Use the our freshly made directory entry. */
	err = insert_header(dir, &new->header);
	subdir = ERR_PTR(err);
	अगर (err)
		जाओ failed;
	subdir = new;
found:
	subdir->header.nreg++;
failed:
	अगर (IS_ERR(subdir)) अणु
		pr_err("sysctl could not get directory: ");
		sysctl_prपूर्णांक_dir(dir);
		pr_cont("/%*.*s %ld\n",
			namelen, namelen, name, PTR_ERR(subdir));
	पूर्ण
	drop_sysctl_table(&dir->header);
	अगर (new)
		drop_sysctl_table(&new->header);
	spin_unlock(&sysctl_lock);
	वापस subdir;
पूर्ण

अटल काष्ठा ctl_dir *xlate_dir(काष्ठा ctl_table_set *set, काष्ठा ctl_dir *dir)
अणु
	काष्ठा ctl_dir *parent;
	स्थिर अक्षर *procname;
	अगर (!dir->header.parent)
		वापस &set->dir;
	parent = xlate_dir(set, dir->header.parent);
	अगर (IS_ERR(parent))
		वापस parent;
	procname = dir->header.ctl_table[0].procname;
	वापस find_subdir(parent, procname, म_माप(procname));
पूर्ण

अटल पूर्णांक sysctl_follow_link(काष्ठा ctl_table_header **phead,
	काष्ठा ctl_table **pentry)
अणु
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table_root *root;
	काष्ठा ctl_table_set *set;
	काष्ठा ctl_table *entry;
	काष्ठा ctl_dir *dir;
	पूर्णांक ret;

	ret = 0;
	spin_lock(&sysctl_lock);
	root = (*pentry)->data;
	set = lookup_header_set(root);
	dir = xlate_dir(set, (*phead)->parent);
	अगर (IS_ERR(dir))
		ret = PTR_ERR(dir);
	अन्यथा अणु
		स्थिर अक्षर *procname = (*pentry)->procname;
		head = शून्य;
		entry = find_entry(&head, dir, procname, म_माप(procname));
		ret = -ENOENT;
		अगर (entry && use_table(head)) अणु
			unuse_table(*phead);
			*phead = head;
			*pentry = entry;
			ret = 0;
		पूर्ण
	पूर्ण

	spin_unlock(&sysctl_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sysctl_err(स्थिर अक्षर *path, काष्ठा ctl_table *table, अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("sysctl table check failed: %s/%s %pV\n",
	       path, table->procname, &vaf);

	बहु_पूर्ण(args);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sysctl_check_table_array(स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	पूर्णांक err = 0;

	अगर ((table->proc_handler == proc_करोuपूर्णांकvec) ||
	    (table->proc_handler == proc_करोuपूर्णांकvec_minmax)) अणु
		अगर (table->maxlen != माप(अचिन्हित पूर्णांक))
			err |= sysctl_err(path, table, "array not allowed");
	पूर्ण

	अगर (table->proc_handler == proc_करोu8vec_minmax) अणु
		अगर (table->maxlen != माप(u8))
			err |= sysctl_err(path, table, "array not allowed");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sysctl_check_table(स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	पूर्णांक err = 0;
	क्रम (; table->procname; table++) अणु
		अगर (table->child)
			err |= sysctl_err(path, table, "Not a file");

		अगर ((table->proc_handler == proc_करोstring) ||
		    (table->proc_handler == proc_करोपूर्णांकvec) ||
		    (table->proc_handler == proc_करोuपूर्णांकvec) ||
		    (table->proc_handler == proc_करोuपूर्णांकvec_minmax) ||
		    (table->proc_handler == proc_करोपूर्णांकvec_minmax) ||
		    (table->proc_handler == proc_करोu8vec_minmax) ||
		    (table->proc_handler == proc_करोपूर्णांकvec_jअगरfies) ||
		    (table->proc_handler == proc_करोपूर्णांकvec_userhz_jअगरfies) ||
		    (table->proc_handler == proc_करोपूर्णांकvec_ms_jअगरfies) ||
		    (table->proc_handler == proc_करोuदीर्घvec_minmax) ||
		    (table->proc_handler == proc_करोuदीर्घvec_ms_jअगरfies_minmax)) अणु
			अगर (!table->data)
				err |= sysctl_err(path, table, "No data");
			अगर (!table->maxlen)
				err |= sysctl_err(path, table, "No maxlen");
			अन्यथा
				err |= sysctl_check_table_array(path, table);
		पूर्ण
		अगर (!table->proc_handler)
			err |= sysctl_err(path, table, "No proc_handler");

		अगर ((table->mode & (S_IRUGO|S_IWUGO)) != table->mode)
			err |= sysctl_err(path, table, "bogus .mode 0%o",
				table->mode);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा ctl_table_header *new_links(काष्ठा ctl_dir *dir, काष्ठा ctl_table *table,
	काष्ठा ctl_table_root *link_root)
अणु
	काष्ठा ctl_table *link_table, *entry, *link;
	काष्ठा ctl_table_header *links;
	काष्ठा ctl_node *node;
	अक्षर *link_name;
	पूर्णांक nr_entries, name_bytes;

	name_bytes = 0;
	nr_entries = 0;
	क्रम (entry = table; entry->procname; entry++) अणु
		nr_entries++;
		name_bytes += म_माप(entry->procname) + 1;
	पूर्ण

	links = kzalloc(माप(काष्ठा ctl_table_header) +
			माप(काष्ठा ctl_node)*nr_entries +
			माप(काष्ठा ctl_table)*(nr_entries + 1) +
			name_bytes,
			GFP_KERNEL);

	अगर (!links)
		वापस शून्य;

	node = (काष्ठा ctl_node *)(links + 1);
	link_table = (काष्ठा ctl_table *)(node + nr_entries);
	link_name = (अक्षर *)&link_table[nr_entries + 1];

	क्रम (link = link_table, entry = table; entry->procname; link++, entry++) अणु
		पूर्णांक len = म_माप(entry->procname) + 1;
		स_नकल(link_name, entry->procname, len);
		link->procname = link_name;
		link->mode = S_IFLNK|S_IRWXUGO;
		link->data = link_root;
		link_name += len;
	पूर्ण
	init_header(links, dir->header.root, dir->header.set, node, link_table);
	links->nreg = nr_entries;

	वापस links;
पूर्ण

अटल bool get_links(काष्ठा ctl_dir *dir,
	काष्ठा ctl_table *table, काष्ठा ctl_table_root *link_root)
अणु
	काष्ठा ctl_table_header *head;
	काष्ठा ctl_table *entry, *link;

	/* Are there links available क्रम every entry in table? */
	क्रम (entry = table; entry->procname; entry++) अणु
		स्थिर अक्षर *procname = entry->procname;
		link = find_entry(&head, dir, procname, म_माप(procname));
		अगर (!link)
			वापस false;
		अगर (S_ISसूची(link->mode) && S_ISसूची(entry->mode))
			जारी;
		अगर (S_ISLNK(link->mode) && (link->data == link_root))
			जारी;
		वापस false;
	पूर्ण

	/* The checks passed.  Increase the registration count on the links */
	क्रम (entry = table; entry->procname; entry++) अणु
		स्थिर अक्षर *procname = entry->procname;
		link = find_entry(&head, dir, procname, म_माप(procname));
		head->nreg++;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक insert_links(काष्ठा ctl_table_header *head)
अणु
	काष्ठा ctl_table_set *root_set = &sysctl_table_root.शेष_set;
	काष्ठा ctl_dir *core_parent = शून्य;
	काष्ठा ctl_table_header *links;
	पूर्णांक err;

	अगर (head->set == root_set)
		वापस 0;

	core_parent = xlate_dir(root_set, head->parent);
	अगर (IS_ERR(core_parent))
		वापस 0;

	अगर (get_links(core_parent, head->ctl_table, head->root))
		वापस 0;

	core_parent->header.nreg++;
	spin_unlock(&sysctl_lock);

	links = new_links(core_parent, head->ctl_table, head->root);

	spin_lock(&sysctl_lock);
	err = -ENOMEM;
	अगर (!links)
		जाओ out;

	err = 0;
	अगर (get_links(core_parent, head->ctl_table, head->root)) अणु
		kमुक्त(links);
		जाओ out;
	पूर्ण

	err = insert_header(core_parent, links);
	अगर (err)
		kमुक्त(links);
out:
	drop_sysctl_table(&core_parent->header);
	वापस err;
पूर्ण

/**
 * __रेजिस्टर_sysctl_table - रेजिस्टर a leaf sysctl table
 * @set: Sysctl tree to रेजिस्टर on
 * @path: The path to the directory the sysctl table is in.
 * @table: the top-level table काष्ठाure
 *
 * Register a sysctl table hierarchy. @table should be a filled in ctl_table
 * array. A completely 0 filled entry terminates the table.
 *
 * The members of the &काष्ठा ctl_table काष्ठाure are used as follows:
 *
 * procname - the name of the sysctl file under /proc/sys. Set to %शून्य to not
 *            enter a sysctl file
 *
 * data - a poपूर्णांकer to data क्रम use by proc_handler
 *
 * maxlen - the maximum size in bytes of the data
 *
 * mode - the file permissions क्रम the /proc/sys file
 *
 * child - must be %शून्य.
 *
 * proc_handler - the text handler routine (described below)
 *
 * extra1, extra2 - extra poपूर्णांकers usable by the proc handler routines
 *
 * Leaf nodes in the sysctl tree will be represented by a single file
 * under /proc; non-leaf nodes will be represented by directories.
 *
 * There must be a proc_handler routine क्रम any terminal nodes.
 * Several शेष handlers are available to cover common हालs -
 *
 * proc_करोstring(), proc_करोपूर्णांकvec(), proc_करोपूर्णांकvec_jअगरfies(),
 * proc_करोपूर्णांकvec_userhz_jअगरfies(), proc_करोपूर्णांकvec_minmax(),
 * proc_करोuदीर्घvec_ms_jअगरfies_minmax(), proc_करोuदीर्घvec_minmax()
 *
 * It is the handler's job to पढ़ो the input buffer from user memory
 * and process it. The handler should वापस 0 on success.
 *
 * This routine वापसs %शून्य on a failure to रेजिस्टर, and a poपूर्णांकer
 * to the table header on success.
 */
काष्ठा ctl_table_header *__रेजिस्टर_sysctl_table(
	काष्ठा ctl_table_set *set,
	स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	काष्ठा ctl_table_root *root = set->सूची.सeader.root;
	काष्ठा ctl_table_header *header;
	स्थिर अक्षर *name, *nextname;
	काष्ठा ctl_dir *dir;
	काष्ठा ctl_table *entry;
	काष्ठा ctl_node *node;
	पूर्णांक nr_entries = 0;

	क्रम (entry = table; entry->procname; entry++)
		nr_entries++;

	header = kzalloc(माप(काष्ठा ctl_table_header) +
			 माप(काष्ठा ctl_node)*nr_entries, GFP_KERNEL);
	अगर (!header)
		वापस शून्य;

	node = (काष्ठा ctl_node *)(header + 1);
	init_header(header, root, set, node, table);
	अगर (sysctl_check_table(path, table))
		जाओ fail;

	spin_lock(&sysctl_lock);
	dir = &set->dir;
	/* Reference moved करोwn the diretory tree get_subdir */
	dir->header.nreg++;
	spin_unlock(&sysctl_lock);

	/* Find the directory क्रम the ctl_table */
	क्रम (name = path; name; name = nextname) अणु
		पूर्णांक namelen;
		nextname = म_अक्षर(name, '/');
		अगर (nextname) अणु
			namelen = nextname - name;
			nextname++;
		पूर्ण अन्यथा अणु
			namelen = म_माप(name);
		पूर्ण
		अगर (namelen == 0)
			जारी;

		dir = get_subdir(dir, name, namelen);
		अगर (IS_ERR(dir))
			जाओ fail;
	पूर्ण

	spin_lock(&sysctl_lock);
	अगर (insert_header(dir, header))
		जाओ fail_put_dir_locked;

	drop_sysctl_table(&dir->header);
	spin_unlock(&sysctl_lock);

	वापस header;

fail_put_dir_locked:
	drop_sysctl_table(&dir->header);
	spin_unlock(&sysctl_lock);
fail:
	kमुक्त(header);
	dump_stack();
	वापस शून्य;
पूर्ण

/**
 * रेजिस्टर_sysctl - रेजिस्टर a sysctl table
 * @path: The path to the directory the sysctl table is in.
 * @table: the table काष्ठाure
 *
 * Register a sysctl table. @table should be a filled in ctl_table
 * array. A completely 0 filled entry terminates the table.
 *
 * See __रेजिस्टर_sysctl_table क्रम more details.
 */
काष्ठा ctl_table_header *रेजिस्टर_sysctl(स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	वापस __रेजिस्टर_sysctl_table(&sysctl_table_root.शेष_set,
					path, table);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_sysctl);

अटल अक्षर *append_path(स्थिर अक्षर *path, अक्षर *pos, स्थिर अक्षर *name)
अणु
	पूर्णांक namelen;
	namelen = म_माप(name);
	अगर (((pos - path) + namelen + 2) >= PATH_MAX)
		वापस शून्य;
	स_नकल(pos, name, namelen);
	pos[namelen] = '/';
	pos[namelen + 1] = '\0';
	pos += namelen + 1;
	वापस pos;
पूर्ण

अटल पूर्णांक count_subheaders(काष्ठा ctl_table *table)
अणु
	पूर्णांक has_files = 0;
	पूर्णांक nr_subheaders = 0;
	काष्ठा ctl_table *entry;

	/* special हाल: no directory and empty directory */
	अगर (!table || !table->procname)
		वापस 1;

	क्रम (entry = table; entry->procname; entry++) अणु
		अगर (entry->child)
			nr_subheaders += count_subheaders(entry->child);
		अन्यथा
			has_files = 1;
	पूर्ण
	वापस nr_subheaders + has_files;
पूर्ण

अटल पूर्णांक रेजिस्टर_leaf_sysctl_tables(स्थिर अक्षर *path, अक्षर *pos,
	काष्ठा ctl_table_header ***subheader, काष्ठा ctl_table_set *set,
	काष्ठा ctl_table *table)
अणु
	काष्ठा ctl_table *ctl_table_arg = शून्य;
	काष्ठा ctl_table *entry, *files;
	पूर्णांक nr_files = 0;
	पूर्णांक nr_dirs = 0;
	पूर्णांक err = -ENOMEM;

	क्रम (entry = table; entry->procname; entry++) अणु
		अगर (entry->child)
			nr_dirs++;
		अन्यथा
			nr_files++;
	पूर्ण

	files = table;
	/* If there are mixed files and directories we need a new table */
	अगर (nr_dirs && nr_files) अणु
		काष्ठा ctl_table *new;
		files = kसुस्मृति(nr_files + 1, माप(काष्ठा ctl_table),
				GFP_KERNEL);
		अगर (!files)
			जाओ out;

		ctl_table_arg = files;
		क्रम (new = files, entry = table; entry->procname; entry++) अणु
			अगर (entry->child)
				जारी;
			*new = *entry;
			new++;
		पूर्ण
	पूर्ण

	/* Register everything except a directory full of subdirectories */
	अगर (nr_files || !nr_dirs) अणु
		काष्ठा ctl_table_header *header;
		header = __रेजिस्टर_sysctl_table(set, path, files);
		अगर (!header) अणु
			kमुक्त(ctl_table_arg);
			जाओ out;
		पूर्ण

		/* Remember अगर we need to मुक्त the file table */
		header->ctl_table_arg = ctl_table_arg;
		**subheader = header;
		(*subheader)++;
	पूर्ण

	/* Recurse पूर्णांकo the subdirectories. */
	क्रम (entry = table; entry->procname; entry++) अणु
		अक्षर *child_pos;

		अगर (!entry->child)
			जारी;

		err = -ENAMETOOLONG;
		child_pos = append_path(path, pos, entry->procname);
		अगर (!child_pos)
			जाओ out;

		err = रेजिस्टर_leaf_sysctl_tables(path, child_pos, subheader,
						  set, entry->child);
		pos[0] = '\0';
		अगर (err)
			जाओ out;
	पूर्ण
	err = 0;
out:
	/* On failure our caller will unरेजिस्टर all रेजिस्टरed subheaders */
	वापस err;
पूर्ण

/**
 * __रेजिस्टर_sysctl_paths - रेजिस्टर a sysctl table hierarchy
 * @set: Sysctl tree to रेजिस्टर on
 * @path: The path to the directory the sysctl table is in.
 * @table: the top-level table काष्ठाure
 *
 * Register a sysctl table hierarchy. @table should be a filled in ctl_table
 * array. A completely 0 filled entry terminates the table.
 *
 * See __रेजिस्टर_sysctl_table क्रम more details.
 */
काष्ठा ctl_table_header *__रेजिस्टर_sysctl_paths(
	काष्ठा ctl_table_set *set,
	स्थिर काष्ठा ctl_path *path, काष्ठा ctl_table *table)
अणु
	काष्ठा ctl_table *ctl_table_arg = table;
	पूर्णांक nr_subheaders = count_subheaders(table);
	काष्ठा ctl_table_header *header = शून्य, **subheaders, **subheader;
	स्थिर काष्ठा ctl_path *component;
	अक्षर *new_path, *pos;

	pos = new_path = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (!new_path)
		वापस शून्य;

	pos[0] = '\0';
	क्रम (component = path; component->procname; component++) अणु
		pos = append_path(new_path, pos, component->procname);
		अगर (!pos)
			जाओ out;
	पूर्ण
	जबतक (table->procname && table->child && !table[1].procname) अणु
		pos = append_path(new_path, pos, table->procname);
		अगर (!pos)
			जाओ out;
		table = table->child;
	पूर्ण
	अगर (nr_subheaders == 1) अणु
		header = __रेजिस्टर_sysctl_table(set, new_path, table);
		अगर (header)
			header->ctl_table_arg = ctl_table_arg;
	पूर्ण अन्यथा अणु
		header = kzalloc(माप(*header) +
				 माप(*subheaders)*nr_subheaders, GFP_KERNEL);
		अगर (!header)
			जाओ out;

		subheaders = (काष्ठा ctl_table_header **) (header + 1);
		subheader = subheaders;
		header->ctl_table_arg = ctl_table_arg;

		अगर (रेजिस्टर_leaf_sysctl_tables(new_path, pos, &subheader,
						set, table))
			जाओ err_रेजिस्टर_leaves;
	पूर्ण

out:
	kमुक्त(new_path);
	वापस header;

err_रेजिस्टर_leaves:
	जबतक (subheader > subheaders) अणु
		काष्ठा ctl_table_header *subh = *(--subheader);
		काष्ठा ctl_table *table = subh->ctl_table_arg;
		unरेजिस्टर_sysctl_table(subh);
		kमुक्त(table);
	पूर्ण
	kमुक्त(header);
	header = शून्य;
	जाओ out;
पूर्ण

/**
 * रेजिस्टर_sysctl_paths - रेजिस्टर a sysctl table hierarchy
 * @path: The path to the directory the sysctl table is in.
 * @table: the top-level table काष्ठाure
 *
 * Register a sysctl table hierarchy. @table should be a filled in ctl_table
 * array. A completely 0 filled entry terminates the table.
 *
 * See __रेजिस्टर_sysctl_paths क्रम more details.
 */
काष्ठा ctl_table_header *रेजिस्टर_sysctl_paths(स्थिर काष्ठा ctl_path *path,
						काष्ठा ctl_table *table)
अणु
	वापस __रेजिस्टर_sysctl_paths(&sysctl_table_root.शेष_set,
					path, table);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_sysctl_paths);

/**
 * रेजिस्टर_sysctl_table - रेजिस्टर a sysctl table hierarchy
 * @table: the top-level table काष्ठाure
 *
 * Register a sysctl table hierarchy. @table should be a filled in ctl_table
 * array. A completely 0 filled entry terminates the table.
 *
 * See रेजिस्टर_sysctl_paths क्रम more details.
 */
काष्ठा ctl_table_header *रेजिस्टर_sysctl_table(काष्ठा ctl_table *table)
अणु
	अटल स्थिर काष्ठा ctl_path null_path[] = अणु अणुपूर्ण पूर्ण;

	वापस रेजिस्टर_sysctl_paths(null_path, table);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_sysctl_table);

अटल व्योम put_links(काष्ठा ctl_table_header *header)
अणु
	काष्ठा ctl_table_set *root_set = &sysctl_table_root.शेष_set;
	काष्ठा ctl_table_root *root = header->root;
	काष्ठा ctl_dir *parent = header->parent;
	काष्ठा ctl_dir *core_parent;
	काष्ठा ctl_table *entry;

	अगर (header->set == root_set)
		वापस;

	core_parent = xlate_dir(root_set, parent);
	अगर (IS_ERR(core_parent))
		वापस;

	क्रम (entry = header->ctl_table; entry->procname; entry++) अणु
		काष्ठा ctl_table_header *link_head;
		काष्ठा ctl_table *link;
		स्थिर अक्षर *name = entry->procname;

		link = find_entry(&link_head, core_parent, name, म_माप(name));
		अगर (link &&
		    ((S_ISसूची(link->mode) && S_ISसूची(entry->mode)) ||
		     (S_ISLNK(link->mode) && (link->data == root)))) अणु
			drop_sysctl_table(link_head);
		पूर्ण
		अन्यथा अणु
			pr_err("sysctl link missing during unregister: ");
			sysctl_prपूर्णांक_dir(parent);
			pr_cont("/%s\n", name);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम drop_sysctl_table(काष्ठा ctl_table_header *header)
अणु
	काष्ठा ctl_dir *parent = header->parent;

	अगर (--header->nreg)
		वापस;

	अगर (parent) अणु
		put_links(header);
		start_unरेजिस्टरing(header);
	पूर्ण

	अगर (!--header->count)
		kमुक्त_rcu(header, rcu);

	अगर (parent)
		drop_sysctl_table(&parent->header);
पूर्ण

/**
 * unरेजिस्टर_sysctl_table - unरेजिस्टर a sysctl table hierarchy
 * @header: the header वापसed from रेजिस्टर_sysctl_table
 *
 * Unरेजिस्टरs the sysctl table and all children. proc entries may not
 * actually be हटाओd until they are no दीर्घer used by anyone.
 */
व्योम unरेजिस्टर_sysctl_table(काष्ठा ctl_table_header * header)
अणु
	पूर्णांक nr_subheaders;
	might_sleep();

	अगर (header == शून्य)
		वापस;

	nr_subheaders = count_subheaders(header->ctl_table_arg);
	अगर (unlikely(nr_subheaders > 1)) अणु
		काष्ठा ctl_table_header **subheaders;
		पूर्णांक i;

		subheaders = (काष्ठा ctl_table_header **)(header + 1);
		क्रम (i = nr_subheaders -1; i >= 0; i--) अणु
			काष्ठा ctl_table_header *subh = subheaders[i];
			काष्ठा ctl_table *table = subh->ctl_table_arg;
			unरेजिस्टर_sysctl_table(subh);
			kमुक्त(table);
		पूर्ण
		kमुक्त(header);
		वापस;
	पूर्ण

	spin_lock(&sysctl_lock);
	drop_sysctl_table(header);
	spin_unlock(&sysctl_lock);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_sysctl_table);

व्योम setup_sysctl_set(काष्ठा ctl_table_set *set,
	काष्ठा ctl_table_root *root,
	पूर्णांक (*is_seen)(काष्ठा ctl_table_set *))
अणु
	स_रखो(set, 0, माप(*set));
	set->is_seen = is_seen;
	init_header(&set->सूची.सeader, root, set, शून्य, root_table);
पूर्ण

व्योम retire_sysctl_set(काष्ठा ctl_table_set *set)
अणु
	WARN_ON(!RB_EMPTY_ROOT(&set->dir.root));
पूर्ण

पूर्णांक __init proc_sys_init(व्योम)
अणु
	काष्ठा proc_dir_entry *proc_sys_root;

	proc_sys_root = proc_सूची_गढ़ो("sys", शून्य);
	proc_sys_root->proc_iops = &proc_sys_dir_operations;
	proc_sys_root->proc_dir_ops = &proc_sys_dir_file_operations;
	proc_sys_root->nlink = 0;

	वापस sysctl_init();
पूर्ण

काष्ठा sysctl_alias अणु
	स्थिर अक्षर *kernel_param;
	स्थिर अक्षर *sysctl_param;
पूर्ण;

/*
 * Historically some settings had both sysctl and a command line parameter.
 * With the generic sysctl. parameter support, we can handle them at a single
 * place and only keep the historical name क्रम compatibility. This is not meant
 * to add bअक्रम new aliases. When adding existing aliases, consider whether
 * the possibly dअगरferent moment of changing the value (e.g. from early_param
 * to the moment करो_sysctl_args() is called) is an issue क्रम the specअगरic
 * parameter.
 */
अटल स्थिर काष्ठा sysctl_alias sysctl_aliases[] = अणु
	अणु"hardlockup_all_cpu_backtrace",	"kernel.hardlockup_all_cpu_backtrace" पूर्ण,
	अणु"hung_task_panic",			"kernel.hung_task_panic" पूर्ण,
	अणु"numa_zonelist_order",			"vm.numa_zonelist_order" पूर्ण,
	अणु"softlockup_all_cpu_backtrace",	"kernel.softlockup_all_cpu_backtrace" पूर्ण,
	अणु"softlockup_panic",			"kernel.softlockup_panic" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर अक्षर *sysctl_find_alias(अक्षर *param)
अणु
	स्थिर काष्ठा sysctl_alias *alias;

	क्रम (alias = &sysctl_aliases[0]; alias->kernel_param != शून्य; alias++) अणु
		अगर (म_भेद(alias->kernel_param, param) == 0)
			वापस alias->sysctl_param;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Set sysctl value passed on kernel command line. */
अटल पूर्णांक process_sysctl_arg(अक्षर *param, अक्षर *val,
			       स्थिर अक्षर *unused, व्योम *arg)
अणु
	अक्षर *path;
	काष्ठा vfsmount **proc_mnt = arg;
	काष्ठा file_प्रणाली_type *proc_fs_type;
	काष्ठा file *file;
	पूर्णांक len;
	पूर्णांक err;
	loff_t pos = 0;
	sमाप_प्रकार wret;

	अगर (म_भेदन(param, "sysctl", माप("sysctl") - 1) == 0) अणु
		param += माप("sysctl") - 1;

		अगर (param[0] != '/' && param[0] != '.')
			वापस 0;

		param++;
	पूर्ण अन्यथा अणु
		param = (अक्षर *) sysctl_find_alias(param);
		अगर (!param)
			वापस 0;
	पूर्ण

	अगर (!val)
		वापस -EINVAL;
	len = म_माप(val);
	अगर (len == 0)
		वापस -EINVAL;

	/*
	 * To set sysctl options, we use a temporary mount of proc, look up the
	 * respective sys/ file and ग_लिखो to it. To aव्योम mounting it when no
	 * options were given, we mount it only when the first sysctl option is
	 * found. Why not a persistent mount? There are problems with a
	 * persistent mount of proc in that it क्रमces userspace not to use any
	 * proc mount options.
	 */
	अगर (!*proc_mnt) अणु
		proc_fs_type = get_fs_type("proc");
		अगर (!proc_fs_type) अणु
			pr_err("Failed to find procfs to set sysctl from command line\n");
			वापस 0;
		पूर्ण
		*proc_mnt = kern_mount(proc_fs_type);
		put_fileप्रणाली(proc_fs_type);
		अगर (IS_ERR(*proc_mnt)) अणु
			pr_err("Failed to mount procfs to set sysctl from command line\n");
			वापस 0;
		पूर्ण
	पूर्ण

	path = kaप्र_लिखो(GFP_KERNEL, "sys/%s", param);
	अगर (!path)
		panic("%s: Failed to allocate path for %s\n", __func__, param);
	strreplace(path, '.', '/');

	file = file_खोलो_root((*proc_mnt)->mnt_root, *proc_mnt, path, O_WRONLY, 0);
	अगर (IS_ERR(file)) अणु
		err = PTR_ERR(file);
		अगर (err == -ENOENT)
			pr_err("Failed to set sysctl parameter '%s=%s': parameter not found\n",
				param, val);
		अन्यथा अगर (err == -EACCES)
			pr_err("Failed to set sysctl parameter '%s=%s': permission denied (read-only?)\n",
				param, val);
		अन्यथा
			pr_err("Error %pe opening proc file to set sysctl parameter '%s=%s'\n",
				file, param, val);
		जाओ out;
	पूर्ण
	wret = kernel_ग_लिखो(file, val, len, &pos);
	अगर (wret < 0) अणु
		err = wret;
		अगर (err == -EINVAL)
			pr_err("Failed to set sysctl parameter '%s=%s': invalid value\n",
				param, val);
		अन्यथा
			pr_err("Error %pe writing to proc file to set sysctl parameter '%s=%s'\n",
				ERR_PTR(err), param, val);
	पूर्ण अन्यथा अगर (wret != len) अणु
		pr_err("Wrote only %zd bytes of %d writing to proc file %s to set sysctl parameter '%s=%s\n",
			wret, len, path, param, val);
	पूर्ण

	err = filp_बंद(file, शून्य);
	अगर (err)
		pr_err("Error %pe closing proc file to set sysctl parameter '%s=%s\n",
			ERR_PTR(err), param, val);
out:
	kमुक्त(path);
	वापस 0;
पूर्ण

व्योम करो_sysctl_args(व्योम)
अणु
	अक्षर *command_line;
	काष्ठा vfsmount *proc_mnt = शून्य;

	command_line = kstrdup(saved_command_line, GFP_KERNEL);
	अगर (!command_line)
		panic("%s: Failed to allocate copy of command line\n", __func__);

	parse_args("Setting sysctl args", command_line,
		   शून्य, 0, -1, -1, &proc_mnt, process_sysctl_arg);

	अगर (proc_mnt)
		kern_unmount(proc_mnt);

	kमुक्त(command_line);
पूर्ण
