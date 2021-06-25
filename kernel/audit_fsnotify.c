<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* audit_fsnotअगरy.c -- tracking inodes
 *
 * Copyright 2003-2009,2014-2015 Red Hat, Inc.
 * Copyright 2005 Hewlett-Packard Development Company, L.P.
 * Copyright 2005 IBM Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/audit.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/namei.h>
#समावेश <linux/netlink.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश "audit.h"

/*
 * this mark lives on the parent directory of the inode in question.
 * but dev, ino, and path are about the child
 */
काष्ठा audit_fsnotअगरy_mark अणु
	dev_t dev;		/* associated superblock device */
	अचिन्हित दीर्घ ino;	/* associated inode number */
	अक्षर *path;		/* insertion path */
	काष्ठा fsnotअगरy_mark mark; /* fsnotअगरy mark on the inode */
	काष्ठा audit_krule *rule;
पूर्ण;

/* fsnotअगरy handle. */
अटल काष्ठा fsnotअगरy_group *audit_fsnotअगरy_group;

/* fsnotअगरy events we care about. */
#घोषणा AUDIT_FS_EVENTS (FS_MOVE | FS_CREATE | FS_DELETE | FS_DELETE_SELF |\
			 FS_MOVE_SELF)

अटल व्योम audit_fsnotअगरy_mark_मुक्त(काष्ठा audit_fsnotअगरy_mark *audit_mark)
अणु
	kमुक्त(audit_mark->path);
	kमुक्त(audit_mark);
पूर्ण

अटल व्योम audit_fsnotअगरy_मुक्त_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा audit_fsnotअगरy_mark *audit_mark;

	audit_mark = container_of(mark, काष्ठा audit_fsnotअगरy_mark, mark);
	audit_fsnotअगरy_mark_मुक्त(audit_mark);
पूर्ण

अक्षर *audit_mark_path(काष्ठा audit_fsnotअगरy_mark *mark)
अणु
	वापस mark->path;
पूर्ण

पूर्णांक audit_mark_compare(काष्ठा audit_fsnotअगरy_mark *mark, अचिन्हित दीर्घ ino, dev_t dev)
अणु
	अगर (mark->ino == AUDIT_INO_UNSET)
		वापस 0;
	वापस (mark->ino == ino) && (mark->dev == dev);
पूर्ण

अटल व्योम audit_update_mark(काष्ठा audit_fsnotअगरy_mark *audit_mark,
			     स्थिर काष्ठा inode *inode)
अणु
	audit_mark->dev = inode ? inode->i_sb->s_dev : AUDIT_DEV_UNSET;
	audit_mark->ino = inode ? inode->i_ino : AUDIT_INO_UNSET;
पूर्ण

काष्ठा audit_fsnotअगरy_mark *audit_alloc_mark(काष्ठा audit_krule *krule, अक्षर *pathname, पूर्णांक len)
अणु
	काष्ठा audit_fsnotअगरy_mark *audit_mark;
	काष्ठा path path;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	पूर्णांक ret;

	अगर (pathname[0] != '/' || pathname[len-1] == '/')
		वापस ERR_PTR(-EINVAL);

	dentry = kern_path_locked(pathname, &path);
	अगर (IS_ERR(dentry))
		वापस ERR_CAST(dentry); /* वापसing an error */
	inode = path.dentry->d_inode;
	inode_unlock(inode);

	audit_mark = kzalloc(माप(*audit_mark), GFP_KERNEL);
	अगर (unlikely(!audit_mark)) अणु
		audit_mark = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	fsnotअगरy_init_mark(&audit_mark->mark, audit_fsnotअगरy_group);
	audit_mark->mark.mask = AUDIT_FS_EVENTS;
	audit_mark->path = pathname;
	audit_update_mark(audit_mark, dentry->d_inode);
	audit_mark->rule = krule;

	ret = fsnotअगरy_add_inode_mark(&audit_mark->mark, inode, true);
	अगर (ret < 0) अणु
		fsnotअगरy_put_mark(&audit_mark->mark);
		audit_mark = ERR_PTR(ret);
	पूर्ण
out:
	dput(dentry);
	path_put(&path);
	वापस audit_mark;
पूर्ण

अटल व्योम audit_mark_log_rule_change(काष्ठा audit_fsnotअगरy_mark *audit_mark, अक्षर *op)
अणु
	काष्ठा audit_buffer *ab;
	काष्ठा audit_krule *rule = audit_mark->rule;

	अगर (!audit_enabled)
		वापस;
	ab = audit_log_start(audit_context(), GFP_NOFS, AUDIT_CONFIG_CHANGE);
	अगर (unlikely(!ab))
		वापस;
	audit_log_session_info(ab);
	audit_log_क्रमmat(ab, " op=%s path=", op);
	audit_log_untrustedstring(ab, audit_mark->path);
	audit_log_key(ab, rule->filterkey);
	audit_log_क्रमmat(ab, " list=%d res=1", rule->listnr);
	audit_log_end(ab);
पूर्ण

व्योम audit_हटाओ_mark(काष्ठा audit_fsnotअगरy_mark *audit_mark)
अणु
	fsnotअगरy_destroy_mark(&audit_mark->mark, audit_fsnotअगरy_group);
	fsnotअगरy_put_mark(&audit_mark->mark);
पूर्ण

व्योम audit_हटाओ_mark_rule(काष्ठा audit_krule *krule)
अणु
	काष्ठा audit_fsnotअगरy_mark *mark = krule->exe;

	audit_हटाओ_mark(mark);
पूर्ण

अटल व्योम audit_स्वतःहटाओ_mark_rule(काष्ठा audit_fsnotअगरy_mark *audit_mark)
अणु
	काष्ठा audit_krule *rule = audit_mark->rule;
	काष्ठा audit_entry *entry = container_of(rule, काष्ठा audit_entry, rule);

	audit_mark_log_rule_change(audit_mark, "autoremove_rule");
	audit_del_rule(entry);
पूर्ण

/* Update mark data in audit rules based on fsnotअगरy events. */
अटल पूर्णांक audit_mark_handle_event(काष्ठा fsnotअगरy_mark *inode_mark, u32 mask,
				   काष्ठा inode *inode, काष्ठा inode *dir,
				   स्थिर काष्ठा qstr *dname, u32 cookie)
अणु
	काष्ठा audit_fsnotअगरy_mark *audit_mark;

	audit_mark = container_of(inode_mark, काष्ठा audit_fsnotअगरy_mark, mark);

	अगर (WARN_ON_ONCE(inode_mark->group != audit_fsnotअगरy_group) ||
	    WARN_ON_ONCE(!inode))
		वापस 0;

	अगर (mask & (FS_CREATE|FS_MOVED_TO|FS_DELETE|FS_MOVED_FROM)) अणु
		अगर (audit_compare_dname_path(dname, audit_mark->path, AUDIT_NAME_FULL))
			वापस 0;
		audit_update_mark(audit_mark, inode);
	पूर्ण अन्यथा अगर (mask & (FS_DELETE_SELF|FS_UNMOUNT|FS_MOVE_SELF)) अणु
		audit_स्वतःहटाओ_mark_rule(audit_mark);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsnotअगरy_ops audit_mark_fsnotअगरy_ops = अणु
	.handle_inode_event = audit_mark_handle_event,
	.मुक्त_mark = audit_fsnotअगरy_मुक्त_mark,
पूर्ण;

अटल पूर्णांक __init audit_fsnotअगरy_init(व्योम)
अणु
	audit_fsnotअगरy_group = fsnotअगरy_alloc_group(&audit_mark_fsnotअगरy_ops);
	अगर (IS_ERR(audit_fsnotअगरy_group)) अणु
		audit_fsnotअगरy_group = शून्य;
		audit_panic("cannot create audit fsnotify group");
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(audit_fsnotअगरy_init);
