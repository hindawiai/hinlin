<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Directory notअगरications क्रम Linux.
 *
 * Copyright (C) 2000,2001,2002 Stephen Rothwell
 *
 * Copyright (C) 2009 Eric Paris <Red Hat Inc>
 * dnotअगरy was largly rewritten to use the new fsnotअगरy infraकाष्ठाure
 */
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/init.h>
#समावेश <linux/security.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fsnotअगरy_backend.h>

पूर्णांक dir_notअगरy_enable __पढ़ो_mostly = 1;

अटल काष्ठा kmem_cache *dnotअगरy_काष्ठा_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *dnotअगरy_mark_cache __पढ़ो_mostly;
अटल काष्ठा fsnotअगरy_group *dnotअगरy_group __पढ़ो_mostly;

/*
 * dnotअगरy will attach one of these to each inode (i_fsnotअगरy_marks) which
 * is being watched by dnotअगरy.  If multiple userspace applications are watching
 * the same directory with dnotअगरy their inक्रमmation is chained in dn
 */
काष्ठा dnotअगरy_mark अणु
	काष्ठा fsnotअगरy_mark fsn_mark;
	काष्ठा dnotअगरy_काष्ठा *dn;
पूर्ण;

/*
 * When a process starts or stops watching an inode the set of events which
 * dnotअगरy cares about क्रम that inode may change.  This function runs the
 * list of everything receiving dnotअगरy events about this directory and calculates
 * the set of all those events.  After it updates what dnotअगरy is पूर्णांकerested in
 * it calls the fsnotअगरy function so it can update the set of all events relevant
 * to this inode.
 */
अटल व्योम dnotअगरy_recalc_inode_mask(काष्ठा fsnotअगरy_mark *fsn_mark)
अणु
	__u32 new_mask = 0;
	काष्ठा dnotअगरy_काष्ठा *dn;
	काष्ठा dnotअगरy_mark *dn_mark  = container_of(fsn_mark,
						     काष्ठा dnotअगरy_mark,
						     fsn_mark);

	निश्चित_spin_locked(&fsn_mark->lock);

	क्रम (dn = dn_mark->dn; dn != शून्य; dn = dn->dn_next)
		new_mask |= (dn->dn_mask & ~FS_DN_MULTISHOT);
	अगर (fsn_mark->mask == new_mask)
		वापस;
	fsn_mark->mask = new_mask;

	fsnotअगरy_recalc_mask(fsn_mark->connector);
पूर्ण

/*
 * Mains fsnotअगरy call where events are delivered to dnotअगरy.
 * Find the dnotअगरy mark on the relevant inode, run the list of dnotअगरy काष्ठाs
 * on that mark and determine which of them has expressed पूर्णांकerest in receiving
 * events of this type.  When found send the correct process and संकेत and
 * destroy the dnotअगरy काष्ठा अगर it was not रेजिस्टरed to receive multiple
 * events.
 */
अटल पूर्णांक dnotअगरy_handle_event(काष्ठा fsnotअगरy_mark *inode_mark, u32 mask,
				काष्ठा inode *inode, काष्ठा inode *dir,
				स्थिर काष्ठा qstr *name, u32 cookie)
अणु
	काष्ठा dnotअगरy_mark *dn_mark;
	काष्ठा dnotअगरy_काष्ठा *dn;
	काष्ठा dnotअगरy_काष्ठा **prev;
	काष्ठा fown_काष्ठा *fown;
	__u32 test_mask = mask & ~FS_EVENT_ON_CHILD;

	/* not a dir, dnotअगरy करोesn't care */
	अगर (!dir && !(mask & FS_ISसूची))
		वापस 0;

	dn_mark = container_of(inode_mark, काष्ठा dnotअगरy_mark, fsn_mark);

	spin_lock(&inode_mark->lock);
	prev = &dn_mark->dn;
	जबतक ((dn = *prev) != शून्य) अणु
		अगर ((dn->dn_mask & test_mask) == 0) अणु
			prev = &dn->dn_next;
			जारी;
		पूर्ण
		fown = &dn->dn_filp->f_owner;
		send_sigio(fown, dn->dn_fd, POLL_MSG);
		अगर (dn->dn_mask & FS_DN_MULTISHOT)
			prev = &dn->dn_next;
		अन्यथा अणु
			*prev = dn->dn_next;
			kmem_cache_मुक्त(dnotअगरy_काष्ठा_cache, dn);
			dnotअगरy_recalc_inode_mask(inode_mark);
		पूर्ण
	पूर्ण

	spin_unlock(&inode_mark->lock);

	वापस 0;
पूर्ण

अटल व्योम dnotअगरy_मुक्त_mark(काष्ठा fsnotअगरy_mark *fsn_mark)
अणु
	काष्ठा dnotअगरy_mark *dn_mark = container_of(fsn_mark,
						    काष्ठा dnotअगरy_mark,
						    fsn_mark);

	BUG_ON(dn_mark->dn);

	kmem_cache_मुक्त(dnotअगरy_mark_cache, dn_mark);
पूर्ण

अटल स्थिर काष्ठा fsnotअगरy_ops dnotअगरy_fsnotअगरy_ops = अणु
	.handle_inode_event = dnotअगरy_handle_event,
	.मुक्त_mark = dnotअगरy_मुक्त_mark,
पूर्ण;

/*
 * Called every समय a file is बंदd.  Looks first क्रम a dnotअगरy mark on the
 * inode.  If one is found run all of the ->dn काष्ठाures attached to that
 * mark क्रम one relevant to this process closing the file and हटाओ that
 * dnotअगरy_काष्ठा.  If that was the last dnotअगरy_काष्ठा also हटाओ the
 * fsnotअगरy_mark.
 */
व्योम dnotअगरy_flush(काष्ठा file *filp, fl_owner_t id)
अणु
	काष्ठा fsnotअगरy_mark *fsn_mark;
	काष्ठा dnotअगरy_mark *dn_mark;
	काष्ठा dnotअगरy_काष्ठा *dn;
	काष्ठा dnotअगरy_काष्ठा **prev;
	काष्ठा inode *inode;
	bool मुक्त = false;

	inode = file_inode(filp);
	अगर (!S_ISसूची(inode->i_mode))
		वापस;

	fsn_mark = fsnotअगरy_find_mark(&inode->i_fsnotअगरy_marks, dnotअगरy_group);
	अगर (!fsn_mark)
		वापस;
	dn_mark = container_of(fsn_mark, काष्ठा dnotअगरy_mark, fsn_mark);

	mutex_lock(&dnotअगरy_group->mark_mutex);

	spin_lock(&fsn_mark->lock);
	prev = &dn_mark->dn;
	जबतक ((dn = *prev) != शून्य) अणु
		अगर ((dn->dn_owner == id) && (dn->dn_filp == filp)) अणु
			*prev = dn->dn_next;
			kmem_cache_मुक्त(dnotअगरy_काष्ठा_cache, dn);
			dnotअगरy_recalc_inode_mask(fsn_mark);
			अवरोध;
		पूर्ण
		prev = &dn->dn_next;
	पूर्ण

	spin_unlock(&fsn_mark->lock);

	/* nothing अन्यथा could have found us thanks to the dnotअगरy_groups
	   mark_mutex */
	अगर (dn_mark->dn == शून्य) अणु
		fsnotअगरy_detach_mark(fsn_mark);
		मुक्त = true;
	पूर्ण

	mutex_unlock(&dnotअगरy_group->mark_mutex);

	अगर (मुक्त)
		fsnotअगरy_मुक्त_mark(fsn_mark);
	fsnotअगरy_put_mark(fsn_mark);
पूर्ण

/* this conversion is करोne only at watch creation */
अटल __u32 convert_arg(अचिन्हित दीर्घ arg)
अणु
	__u32 new_mask = FS_EVENT_ON_CHILD;

	अगर (arg & DN_MULTISHOT)
		new_mask |= FS_DN_MULTISHOT;
	अगर (arg & DN_DELETE)
		new_mask |= (FS_DELETE | FS_MOVED_FROM);
	अगर (arg & DN_MODIFY)
		new_mask |= FS_MODIFY;
	अगर (arg & DN_ACCESS)
		new_mask |= FS_ACCESS;
	अगर (arg & DN_ATTRIB)
		new_mask |= FS_ATTRIB;
	अगर (arg & DN_RENAME)
		new_mask |= FS_DN_RENAME;
	अगर (arg & DN_CREATE)
		new_mask |= (FS_CREATE | FS_MOVED_TO);

	वापस new_mask;
पूर्ण

/*
 * If multiple processes watch the same inode with dnotअगरy there is only one
 * dnotअगरy mark in inode->i_fsnotअगरy_marks but we chain a dnotअगरy_काष्ठा
 * onto that mark.  This function either attaches the new dnotअगरy_काष्ठा onto
 * that list, or it |= the mask onto an existing dnofiy_काष्ठा.
 */
अटल पूर्णांक attach_dn(काष्ठा dnotअगरy_काष्ठा *dn, काष्ठा dnotअगरy_mark *dn_mark,
		     fl_owner_t id, पूर्णांक fd, काष्ठा file *filp, __u32 mask)
अणु
	काष्ठा dnotअगरy_काष्ठा *odn;

	odn = dn_mark->dn;
	जबतक (odn != शून्य) अणु
		/* adding more events to existing dnofiy_काष्ठा? */
		अगर ((odn->dn_owner == id) && (odn->dn_filp == filp)) अणु
			odn->dn_fd = fd;
			odn->dn_mask |= mask;
			वापस -EEXIST;
		पूर्ण
		odn = odn->dn_next;
	पूर्ण

	dn->dn_mask = mask;
	dn->dn_fd = fd;
	dn->dn_filp = filp;
	dn->dn_owner = id;
	dn->dn_next = dn_mark->dn;
	dn_mark->dn = dn;

	वापस 0;
पूर्ण

/*
 * When a process calls fcntl to attach a dnotअगरy watch to a directory it ends
 * up here.  Allocate both a mark क्रम fsnotअगरy to add and a dnotअगरy_काष्ठा to be
 * attached to the fsnotअगरy_mark.
 */
पूर्णांक fcntl_dirnotअगरy(पूर्णांक fd, काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा dnotअगरy_mark *new_dn_mark, *dn_mark;
	काष्ठा fsnotअगरy_mark *new_fsn_mark, *fsn_mark;
	काष्ठा dnotअगरy_काष्ठा *dn;
	काष्ठा inode *inode;
	fl_owner_t id = current->files;
	काष्ठा file *f;
	पूर्णांक destroy = 0, error = 0;
	__u32 mask;

	/* we use these to tell अगर we need to kमुक्त */
	new_fsn_mark = शून्य;
	dn = शून्य;

	अगर (!dir_notअगरy_enable) अणु
		error = -EINVAL;
		जाओ out_err;
	पूर्ण

	/* a 0 mask means we are explicitly removing the watch */
	अगर ((arg & ~DN_MULTISHOT) == 0) अणु
		dnotअगरy_flush(filp, id);
		error = 0;
		जाओ out_err;
	पूर्ण

	/* dnotअगरy only works on directories */
	inode = file_inode(filp);
	अगर (!S_ISसूची(inode->i_mode)) अणु
		error = -ENOTसूची;
		जाओ out_err;
	पूर्ण

	/*
	 * convert the userspace DN_* "arg" to the पूर्णांकernal FS_*
	 * defined in fsnotअगरy
	 */
	mask = convert_arg(arg);

	error = security_path_notअगरy(&filp->f_path, mask,
			FSNOTIFY_OBJ_TYPE_INODE);
	अगर (error)
		जाओ out_err;

	/* expect most fcntl to add new rather than augment old */
	dn = kmem_cache_alloc(dnotअगरy_काष्ठा_cache, GFP_KERNEL);
	अगर (!dn) अणु
		error = -ENOMEM;
		जाओ out_err;
	पूर्ण

	/* new fsnotअगरy mark, we expect most fcntl calls to add a new mark */
	new_dn_mark = kmem_cache_alloc(dnotअगरy_mark_cache, GFP_KERNEL);
	अगर (!new_dn_mark) अणु
		error = -ENOMEM;
		जाओ out_err;
	पूर्ण

	/* set up the new_fsn_mark and new_dn_mark */
	new_fsn_mark = &new_dn_mark->fsn_mark;
	fsnotअगरy_init_mark(new_fsn_mark, dnotअगरy_group);
	new_fsn_mark->mask = mask;
	new_dn_mark->dn = शून्य;

	/* this is needed to prevent the fcntl/बंद race described below */
	mutex_lock(&dnotअगरy_group->mark_mutex);

	/* add the new_fsn_mark or find an old one. */
	fsn_mark = fsnotअगरy_find_mark(&inode->i_fsnotअगरy_marks, dnotअगरy_group);
	अगर (fsn_mark) अणु
		dn_mark = container_of(fsn_mark, काष्ठा dnotअगरy_mark, fsn_mark);
		spin_lock(&fsn_mark->lock);
	पूर्ण अन्यथा अणु
		error = fsnotअगरy_add_inode_mark_locked(new_fsn_mark, inode, 0);
		अगर (error) अणु
			mutex_unlock(&dnotअगरy_group->mark_mutex);
			जाओ out_err;
		पूर्ण
		spin_lock(&new_fsn_mark->lock);
		fsn_mark = new_fsn_mark;
		dn_mark = new_dn_mark;
		/* we used new_fsn_mark, so करोn't मुक्त it */
		new_fsn_mark = शून्य;
	पूर्ण

	rcu_पढ़ो_lock();
	f = lookup_fd_rcu(fd);
	rcu_पढ़ो_unlock();

	/* अगर (f != filp) means that we lost a race and another task/thपढ़ो
	 * actually बंदd the fd we are still playing with beक्रमe we grabbed
	 * the dnotअगरy_groups mark_mutex and fsn_mark->lock.  Since closing the
	 * fd is the only समय we clean up the marks we need to get our mark
	 * off the list. */
	अगर (f != filp) अणु
		/* अगर we added ourselves, shoot ourselves, it's possible that
		 * the flush actually did shoot this fsn_mark.  That's fine too
		 * since multiple calls to destroy_mark is perfectly safe, अगर
		 * we found a dn_mark alपढ़ोy attached to the inode, just sod
		 * off silently as the flush at बंद समय dealt with it.
		 */
		अगर (dn_mark == new_dn_mark)
			destroy = 1;
		error = 0;
		जाओ out;
	पूर्ण

	__f_setown(filp, task_pid(current), PIDTYPE_TGID, 0);

	error = attach_dn(dn, dn_mark, id, fd, filp, mask);
	/* !error means that we attached the dn to the dn_mark, so करोn't मुक्त it */
	अगर (!error)
		dn = शून्य;
	/* -EEXIST means that we didn't add this new dn and used an old one.
	 * that isn't an error (and the unused dn should be मुक्तd) */
	अन्यथा अगर (error == -EEXIST)
		error = 0;

	dnotअगरy_recalc_inode_mask(fsn_mark);
out:
	spin_unlock(&fsn_mark->lock);

	अगर (destroy)
		fsnotअगरy_detach_mark(fsn_mark);
	mutex_unlock(&dnotअगरy_group->mark_mutex);
	अगर (destroy)
		fsnotअगरy_मुक्त_mark(fsn_mark);
	fsnotअगरy_put_mark(fsn_mark);
out_err:
	अगर (new_fsn_mark)
		fsnotअगरy_put_mark(new_fsn_mark);
	अगर (dn)
		kmem_cache_मुक्त(dnotअगरy_काष्ठा_cache, dn);
	वापस error;
पूर्ण

अटल पूर्णांक __init dnotअगरy_init(व्योम)
अणु
	dnotअगरy_काष्ठा_cache = KMEM_CACHE(dnotअगरy_काष्ठा,
					  SLAB_PANIC|SLAB_ACCOUNT);
	dnotअगरy_mark_cache = KMEM_CACHE(dnotअगरy_mark, SLAB_PANIC|SLAB_ACCOUNT);

	dnotअगरy_group = fsnotअगरy_alloc_group(&dnotअगरy_fsnotअगरy_ops);
	अगर (IS_ERR(dnotअगरy_group))
		panic("unable to allocate fsnotify group for dnotify\n");
	वापस 0;
पूर्ण

module_init(dnotअगरy_init)
