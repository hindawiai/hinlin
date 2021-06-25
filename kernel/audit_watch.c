<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* audit_watch.c -- watching inodes
 *
 * Copyright 2003-2009 Red Hat, Inc.
 * Copyright 2005 Hewlett-Packard Development Company, L.P.
 * Copyright 2005 IBM Corporation
 */

#समावेश <linux/file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/audit.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/namei.h>
#समावेश <linux/netlink.h>
#समावेश <linux/refcount.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश "audit.h"

/*
 * Reference counting:
 *
 * audit_parent: lअगरeसमय is from audit_init_parent() to receipt of an FS_IGNORED
 * 	event.  Each audit_watch holds a reference to its associated parent.
 *
 * audit_watch: अगर added to lists, lअगरeसमय is from audit_init_watch() to
 * 	audit_हटाओ_watch().  Additionally, an audit_watch may exist
 * 	temporarily to assist in searching existing filter data.  Each
 * 	audit_krule holds a reference to its associated watch.
 */

काष्ठा audit_watch अणु
	refcount_t		count;	/* reference count */
	dev_t			dev;	/* associated superblock device */
	अक्षर			*path;	/* insertion path */
	अचिन्हित दीर्घ		ino;	/* associated inode number */
	काष्ठा audit_parent	*parent; /* associated parent */
	काष्ठा list_head	wlist;	/* entry in parent->watches list */
	काष्ठा list_head	rules;	/* anchor क्रम krule->rlist */
पूर्ण;

काष्ठा audit_parent अणु
	काष्ठा list_head	watches; /* anchor क्रम audit_watch->wlist */
	काष्ठा fsnotअगरy_mark mark; /* fsnotअगरy mark on the inode */
पूर्ण;

/* fsnotअगरy handle. */
अटल काष्ठा fsnotअगरy_group *audit_watch_group;

/* fsnotअगरy events we care about. */
#घोषणा AUDIT_FS_WATCH (FS_MOVE | FS_CREATE | FS_DELETE | FS_DELETE_SELF |\
			FS_MOVE_SELF | FS_UNMOUNT)

अटल व्योम audit_मुक्त_parent(काष्ठा audit_parent *parent)
अणु
	WARN_ON(!list_empty(&parent->watches));
	kमुक्त(parent);
पूर्ण

अटल व्योम audit_watch_मुक्त_mark(काष्ठा fsnotअगरy_mark *entry)
अणु
	काष्ठा audit_parent *parent;

	parent = container_of(entry, काष्ठा audit_parent, mark);
	audit_मुक्त_parent(parent);
पूर्ण

अटल व्योम audit_get_parent(काष्ठा audit_parent *parent)
अणु
	अगर (likely(parent))
		fsnotअगरy_get_mark(&parent->mark);
पूर्ण

अटल व्योम audit_put_parent(काष्ठा audit_parent *parent)
अणु
	अगर (likely(parent))
		fsnotअगरy_put_mark(&parent->mark);
पूर्ण

/*
 * Find and वापस the audit_parent on the given inode.  If found a reference
 * is taken on this parent.
 */
अटल अंतरभूत काष्ठा audit_parent *audit_find_parent(काष्ठा inode *inode)
अणु
	काष्ठा audit_parent *parent = शून्य;
	काष्ठा fsnotअगरy_mark *entry;

	entry = fsnotअगरy_find_mark(&inode->i_fsnotअगरy_marks, audit_watch_group);
	अगर (entry)
		parent = container_of(entry, काष्ठा audit_parent, mark);

	वापस parent;
पूर्ण

व्योम audit_get_watch(काष्ठा audit_watch *watch)
अणु
	refcount_inc(&watch->count);
पूर्ण

व्योम audit_put_watch(काष्ठा audit_watch *watch)
अणु
	अगर (refcount_dec_and_test(&watch->count)) अणु
		WARN_ON(watch->parent);
		WARN_ON(!list_empty(&watch->rules));
		kमुक्त(watch->path);
		kमुक्त(watch);
	पूर्ण
पूर्ण

अटल व्योम audit_हटाओ_watch(काष्ठा audit_watch *watch)
अणु
	list_del(&watch->wlist);
	audit_put_parent(watch->parent);
	watch->parent = शून्य;
	audit_put_watch(watch); /* match initial get */
पूर्ण

अक्षर *audit_watch_path(काष्ठा audit_watch *watch)
अणु
	वापस watch->path;
पूर्ण

पूर्णांक audit_watch_compare(काष्ठा audit_watch *watch, अचिन्हित दीर्घ ino, dev_t dev)
अणु
	वापस (watch->ino != AUDIT_INO_UNSET) &&
		(watch->ino == ino) &&
		(watch->dev == dev);
पूर्ण

/* Initialize a parent watch entry. */
अटल काष्ठा audit_parent *audit_init_parent(काष्ठा path *path)
अणु
	काष्ठा inode *inode = d_backing_inode(path->dentry);
	काष्ठा audit_parent *parent;
	पूर्णांक ret;

	parent = kzalloc(माप(*parent), GFP_KERNEL);
	अगर (unlikely(!parent))
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&parent->watches);

	fsnotअगरy_init_mark(&parent->mark, audit_watch_group);
	parent->mark.mask = AUDIT_FS_WATCH;
	ret = fsnotअगरy_add_inode_mark(&parent->mark, inode, 0);
	अगर (ret < 0) अणु
		audit_मुक्त_parent(parent);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस parent;
पूर्ण

/* Initialize a watch entry. */
अटल काष्ठा audit_watch *audit_init_watch(अक्षर *path)
अणु
	काष्ठा audit_watch *watch;

	watch = kzalloc(माप(*watch), GFP_KERNEL);
	अगर (unlikely(!watch))
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&watch->rules);
	refcount_set(&watch->count, 1);
	watch->path = path;
	watch->dev = AUDIT_DEV_UNSET;
	watch->ino = AUDIT_INO_UNSET;

	वापस watch;
पूर्ण

/* Translate a watch string to kernel representation. */
पूर्णांक audit_to_watch(काष्ठा audit_krule *krule, अक्षर *path, पूर्णांक len, u32 op)
अणु
	काष्ठा audit_watch *watch;

	अगर (!audit_watch_group)
		वापस -EOPNOTSUPP;

	अगर (path[0] != '/' || path[len-1] == '/' ||
	    krule->listnr != AUDIT_FILTER_EXIT ||
	    op != Audit_equal ||
	    krule->inode_f || krule->watch || krule->tree)
		वापस -EINVAL;

	watch = audit_init_watch(path);
	अगर (IS_ERR(watch))
		वापस PTR_ERR(watch);

	krule->watch = watch;

	वापस 0;
पूर्ण

/* Duplicate the given audit watch.  The new watch's rules list is initialized
 * to an empty list and wlist is undefined. */
अटल काष्ठा audit_watch *audit_dupe_watch(काष्ठा audit_watch *old)
अणु
	अक्षर *path;
	काष्ठा audit_watch *new;

	path = kstrdup(old->path, GFP_KERNEL);
	अगर (unlikely(!path))
		वापस ERR_PTR(-ENOMEM);

	new = audit_init_watch(path);
	अगर (IS_ERR(new)) अणु
		kमुक्त(path);
		जाओ out;
	पूर्ण

	new->dev = old->dev;
	new->ino = old->ino;
	audit_get_parent(old->parent);
	new->parent = old->parent;

out:
	वापस new;
पूर्ण

अटल व्योम audit_watch_log_rule_change(काष्ठा audit_krule *r, काष्ठा audit_watch *w, अक्षर *op)
अणु
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled)
		वापस;
	ab = audit_log_start(audit_context(), GFP_NOFS, AUDIT_CONFIG_CHANGE);
	अगर (!ab)
		वापस;
	audit_log_session_info(ab);
	audit_log_क्रमmat(ab, "op=%s path=", op);
	audit_log_untrustedstring(ab, w->path);
	audit_log_key(ab, r->filterkey);
	audit_log_क्रमmat(ab, " list=%d res=1", r->listnr);
	audit_log_end(ab);
पूर्ण

/* Update inode info in audit rules based on fileप्रणाली event. */
अटल व्योम audit_update_watch(काष्ठा audit_parent *parent,
			       स्थिर काष्ठा qstr *dname, dev_t dev,
			       अचिन्हित दीर्घ ino, अचिन्हित invalidating)
अणु
	काष्ठा audit_watch *owatch, *nwatch, *nextw;
	काष्ठा audit_krule *r, *nextr;
	काष्ठा audit_entry *oentry, *nentry;

	mutex_lock(&audit_filter_mutex);
	/* Run all of the watches on this parent looking क्रम the one that
	 * matches the given dname */
	list_क्रम_each_entry_safe(owatch, nextw, &parent->watches, wlist) अणु
		अगर (audit_compare_dname_path(dname, owatch->path,
					     AUDIT_NAME_FULL))
			जारी;

		/* If the update involves invalidating rules, करो the inode-based
		 * filtering now, so we करोn't omit records. */
		अगर (invalidating && !audit_dummy_context())
			audit_filter_inodes(current, audit_context());

		/* updating ino will likely change which audit_hash_list we
		 * are on so we need a new watch क्रम the new list */
		nwatch = audit_dupe_watch(owatch);
		अगर (IS_ERR(nwatch)) अणु
			mutex_unlock(&audit_filter_mutex);
			audit_panic("error updating watch, skipping");
			वापस;
		पूर्ण
		nwatch->dev = dev;
		nwatch->ino = ino;

		list_क्रम_each_entry_safe(r, nextr, &owatch->rules, rlist) अणु

			oentry = container_of(r, काष्ठा audit_entry, rule);
			list_del(&oentry->rule.rlist);
			list_del_rcu(&oentry->list);

			nentry = audit_dupe_rule(&oentry->rule);
			अगर (IS_ERR(nentry)) अणु
				list_del(&oentry->rule.list);
				audit_panic("error updating watch, removing");
			पूर्ण अन्यथा अणु
				पूर्णांक h = audit_hash_ino((u32)ino);

				/*
				 * nentry->rule.watch == oentry->rule.watch so
				 * we must drop that reference and set it to our
				 * new watch.
				 */
				audit_put_watch(nentry->rule.watch);
				audit_get_watch(nwatch);
				nentry->rule.watch = nwatch;
				list_add(&nentry->rule.rlist, &nwatch->rules);
				list_add_rcu(&nentry->list, &audit_inode_hash[h]);
				list_replace(&oentry->rule.list,
					     &nentry->rule.list);
			पूर्ण
			अगर (oentry->rule.exe)
				audit_हटाओ_mark(oentry->rule.exe);

			call_rcu(&oentry->rcu, audit_मुक्त_rule_rcu);
		पूर्ण

		audit_हटाओ_watch(owatch);
		जाओ add_watch_to_parent; /* event applies to a single watch */
	पूर्ण
	mutex_unlock(&audit_filter_mutex);
	वापस;

add_watch_to_parent:
	list_add(&nwatch->wlist, &parent->watches);
	mutex_unlock(&audit_filter_mutex);
	वापस;
पूर्ण

/* Remove all watches & rules associated with a parent that is going away. */
अटल व्योम audit_हटाओ_parent_watches(काष्ठा audit_parent *parent)
अणु
	काष्ठा audit_watch *w, *nextw;
	काष्ठा audit_krule *r, *nextr;
	काष्ठा audit_entry *e;

	mutex_lock(&audit_filter_mutex);
	list_क्रम_each_entry_safe(w, nextw, &parent->watches, wlist) अणु
		list_क्रम_each_entry_safe(r, nextr, &w->rules, rlist) अणु
			e = container_of(r, काष्ठा audit_entry, rule);
			audit_watch_log_rule_change(r, w, "remove_rule");
			अगर (e->rule.exe)
				audit_हटाओ_mark(e->rule.exe);
			list_del(&r->rlist);
			list_del(&r->list);
			list_del_rcu(&e->list);
			call_rcu(&e->rcu, audit_मुक्त_rule_rcu);
		पूर्ण
		audit_हटाओ_watch(w);
	पूर्ण
	mutex_unlock(&audit_filter_mutex);

	fsnotअगरy_destroy_mark(&parent->mark, audit_watch_group);
पूर्ण

/* Get path inक्रमmation necessary क्रम adding watches. */
अटल पूर्णांक audit_get_nd(काष्ठा audit_watch *watch, काष्ठा path *parent)
अणु
	काष्ठा dentry *d = kern_path_locked(watch->path, parent);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);
	अगर (d_is_positive(d)) अणु
		/* update watch filter fields */
		watch->dev = d->d_sb->s_dev;
		watch->ino = d_backing_inode(d)->i_ino;
	पूर्ण
	inode_unlock(d_backing_inode(parent->dentry));
	dput(d);
	वापस 0;
पूर्ण

/* Associate the given rule with an existing parent.
 * Caller must hold audit_filter_mutex. */
अटल व्योम audit_add_to_parent(काष्ठा audit_krule *krule,
				काष्ठा audit_parent *parent)
अणु
	काष्ठा audit_watch *w, *watch = krule->watch;
	पूर्णांक watch_found = 0;

	BUG_ON(!mutex_is_locked(&audit_filter_mutex));

	list_क्रम_each_entry(w, &parent->watches, wlist) अणु
		अगर (म_भेद(watch->path, w->path))
			जारी;

		watch_found = 1;

		/* put krule's ref to temporary watch */
		audit_put_watch(watch);

		audit_get_watch(w);
		krule->watch = watch = w;

		audit_put_parent(parent);
		अवरोध;
	पूर्ण

	अगर (!watch_found) अणु
		watch->parent = parent;

		audit_get_watch(watch);
		list_add(&watch->wlist, &parent->watches);
	पूर्ण
	list_add(&krule->rlist, &watch->rules);
पूर्ण

/* Find a matching watch entry, or add this one.
 * Caller must hold audit_filter_mutex. */
पूर्णांक audit_add_watch(काष्ठा audit_krule *krule, काष्ठा list_head **list)
अणु
	काष्ठा audit_watch *watch = krule->watch;
	काष्ठा audit_parent *parent;
	काष्ठा path parent_path;
	पूर्णांक h, ret = 0;

	/*
	 * When we will be calling audit_add_to_parent, krule->watch might have
	 * been updated and watch might have been मुक्तd.
	 * So we need to keep a reference of watch.
	 */
	audit_get_watch(watch);

	mutex_unlock(&audit_filter_mutex);

	/* Aव्योम calling path_lookup under audit_filter_mutex. */
	ret = audit_get_nd(watch, &parent_path);

	/* caller expects mutex locked */
	mutex_lock(&audit_filter_mutex);

	अगर (ret) अणु
		audit_put_watch(watch);
		वापस ret;
	पूर्ण

	/* either find an old parent or attach a new one */
	parent = audit_find_parent(d_backing_inode(parent_path.dentry));
	अगर (!parent) अणु
		parent = audit_init_parent(&parent_path);
		अगर (IS_ERR(parent)) अणु
			ret = PTR_ERR(parent);
			जाओ error;
		पूर्ण
	पूर्ण

	audit_add_to_parent(krule, parent);

	h = audit_hash_ino((u32)watch->ino);
	*list = &audit_inode_hash[h];
error:
	path_put(&parent_path);
	audit_put_watch(watch);
	वापस ret;
पूर्ण

व्योम audit_हटाओ_watch_rule(काष्ठा audit_krule *krule)
अणु
	काष्ठा audit_watch *watch = krule->watch;
	काष्ठा audit_parent *parent = watch->parent;

	list_del(&krule->rlist);

	अगर (list_empty(&watch->rules)) अणु
		/*
		 * audit_हटाओ_watch() drops our reference to 'parent' which
		 * can get मुक्तd. Grab our own reference to be safe.
		 */
		audit_get_parent(parent);
		audit_हटाओ_watch(watch);
		अगर (list_empty(&parent->watches))
			fsnotअगरy_destroy_mark(&parent->mark, audit_watch_group);
		audit_put_parent(parent);
	पूर्ण
पूर्ण

/* Update watch data in audit rules based on fsnotअगरy events. */
अटल पूर्णांक audit_watch_handle_event(काष्ठा fsnotअगरy_mark *inode_mark, u32 mask,
				    काष्ठा inode *inode, काष्ठा inode *dir,
				    स्थिर काष्ठा qstr *dname, u32 cookie)
अणु
	काष्ठा audit_parent *parent;

	parent = container_of(inode_mark, काष्ठा audit_parent, mark);

	अगर (WARN_ON_ONCE(inode_mark->group != audit_watch_group) ||
	    WARN_ON_ONCE(!inode))
		वापस 0;

	अगर (mask & (FS_CREATE|FS_MOVED_TO) && inode)
		audit_update_watch(parent, dname, inode->i_sb->s_dev, inode->i_ino, 0);
	अन्यथा अगर (mask & (FS_DELETE|FS_MOVED_FROM))
		audit_update_watch(parent, dname, AUDIT_DEV_UNSET, AUDIT_INO_UNSET, 1);
	अन्यथा अगर (mask & (FS_DELETE_SELF|FS_UNMOUNT|FS_MOVE_SELF))
		audit_हटाओ_parent_watches(parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsnotअगरy_ops audit_watch_fsnotअगरy_ops = अणु
	.handle_inode_event =	audit_watch_handle_event,
	.मुक्त_mark =		audit_watch_मुक्त_mark,
पूर्ण;

अटल पूर्णांक __init audit_watch_init(व्योम)
अणु
	audit_watch_group = fsnotअगरy_alloc_group(&audit_watch_fsnotअगरy_ops);
	अगर (IS_ERR(audit_watch_group)) अणु
		audit_watch_group = शून्य;
		audit_panic("cannot create audit fsnotify group");
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(audit_watch_init);

पूर्णांक audit_dupe_exe(काष्ठा audit_krule *new, काष्ठा audit_krule *old)
अणु
	काष्ठा audit_fsnotअगरy_mark *audit_mark;
	अक्षर *pathname;

	pathname = kstrdup(audit_mark_path(old->exe), GFP_KERNEL);
	अगर (!pathname)
		वापस -ENOMEM;

	audit_mark = audit_alloc_mark(new, pathname, म_माप(pathname));
	अगर (IS_ERR(audit_mark)) अणु
		kमुक्त(pathname);
		वापस PTR_ERR(audit_mark);
	पूर्ण
	new->exe = audit_mark;

	वापस 0;
पूर्ण

पूर्णांक audit_exe_compare(काष्ठा task_काष्ठा *tsk, काष्ठा audit_fsnotअगरy_mark *mark)
अणु
	काष्ठा file *exe_file;
	अचिन्हित दीर्घ ino;
	dev_t dev;

	exe_file = get_task_exe_file(tsk);
	अगर (!exe_file)
		वापस 0;
	ino = file_inode(exe_file)->i_ino;
	dev = file_inode(exe_file)->i_sb->s_dev;
	fput(exe_file);
	वापस audit_mark_compare(mark, ino, dev);
पूर्ण
