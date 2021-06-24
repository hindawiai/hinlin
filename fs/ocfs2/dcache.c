<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dcache.c
 *
 * dentry cache handling code
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/namei.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dcache.h"
#समावेश "dlmglue.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "ocfs2_trace.h"

व्योम ocfs2_dentry_attach_gen(काष्ठा dentry *dentry)
अणु
	अचिन्हित दीर्घ gen =
		OCFS2_I(d_inode(dentry->d_parent))->ip_dir_lock_gen;
	BUG_ON(d_inode(dentry));
	dentry->d_fsdata = (व्योम *)gen;
पूर्ण


अटल पूर्णांक ocfs2_dentry_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	पूर्णांक ret = 0;    /* अगर all अन्यथा fails, just वापस false */
	काष्ठा ocfs2_super *osb;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(dentry);
	osb = OCFS2_SB(dentry->d_sb);

	trace_ocfs2_dentry_revalidate(dentry, dentry->d_name.len,
				      dentry->d_name.name);

	/* For a negative dentry -
	 * check the generation number of the parent and compare with the
	 * one stored in the inode.
	 */
	अगर (inode == शून्य) अणु
		अचिन्हित दीर्घ gen = (अचिन्हित दीर्घ) dentry->d_fsdata;
		अचिन्हित दीर्घ pgen;
		spin_lock(&dentry->d_lock);
		pgen = OCFS2_I(d_inode(dentry->d_parent))->ip_dir_lock_gen;
		spin_unlock(&dentry->d_lock);
		trace_ocfs2_dentry_revalidate_negative(dentry->d_name.len,
						       dentry->d_name.name,
						       pgen, gen);
		अगर (gen != pgen)
			जाओ bail;
		जाओ valid;
	पूर्ण

	BUG_ON(!osb);

	अगर (inode == osb->root_inode || is_bad_inode(inode))
		जाओ bail;

	spin_lock(&OCFS2_I(inode)->ip_lock);
	/* did we or someone अन्यथा delete this inode? */
	अगर (OCFS2_I(inode)->ip_flags & OCFS2_INODE_DELETED) अणु
		spin_unlock(&OCFS2_I(inode)->ip_lock);
		trace_ocfs2_dentry_revalidate_delete(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		जाओ bail;
	पूर्ण
	spin_unlock(&OCFS2_I(inode)->ip_lock);

	/*
	 * We करोn't need a cluster lock to test this because once an
	 * inode nlink hits zero, it never goes back.
	 */
	अगर (inode->i_nlink == 0) अणु
		trace_ocfs2_dentry_revalidate_orphaned(
			(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			S_ISसूची(inode->i_mode));
		जाओ bail;
	पूर्ण

	/*
	 * If the last lookup failed to create dentry lock, let us
	 * reकरो it.
	 */
	अगर (!dentry->d_fsdata) अणु
		trace_ocfs2_dentry_revalidate_nofsdata(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		जाओ bail;
	पूर्ण

valid:
	ret = 1;

bail:
	trace_ocfs2_dentry_revalidate_ret(ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_match_dentry(काष्ठा dentry *dentry,
			      u64 parent_blkno,
			      पूर्णांक skip_unhashed)
अणु
	काष्ठा inode *parent;

	/*
	 * ocfs2_lookup() करोes a d_splice_alias() _beक्रमe_ attaching
	 * to the lock data, so we skip those here, otherwise
	 * ocfs2_dentry_attach_lock() will get its original dentry
	 * back.
	 */
	अगर (!dentry->d_fsdata)
		वापस 0;

	अगर (!dentry->d_parent)
		वापस 0;

	अगर (skip_unhashed && d_unhashed(dentry))
		वापस 0;

	parent = d_inode(dentry->d_parent);
	/* Negative parent dentry? */
	अगर (!parent)
		वापस 0;

	/* Name is in a dअगरferent directory. */
	अगर (OCFS2_I(parent)->ip_blkno != parent_blkno)
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Walk the inode alias list, and find a dentry which has a given
 * parent. ocfs2_dentry_attach_lock() wants to find _any_ alias as it
 * is looking क्रम a dentry_lock reference. The करोwnconvert thपढ़ो is
 * looking to unhash aliases, so we allow it to skip any that alपढ़ोy
 * have that property.
 */
काष्ठा dentry *ocfs2_find_local_alias(काष्ठा inode *inode,
				      u64 parent_blkno,
				      पूर्णांक skip_unhashed)
अणु
	काष्ठा dentry *dentry;

	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(dentry, &inode->i_dentry, d_u.d_alias) अणु
		spin_lock(&dentry->d_lock);
		अगर (ocfs2_match_dentry(dentry, parent_blkno, skip_unhashed)) अणु
			trace_ocfs2_find_local_alias(dentry->d_name.len,
						     dentry->d_name.name);

			dget_dlock(dentry);
			spin_unlock(&dentry->d_lock);
			spin_unlock(&inode->i_lock);
			वापस dentry;
		पूर्ण
		spin_unlock(&dentry->d_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस शून्य;
पूर्ण

DEFINE_SPINLOCK(dentry_attach_lock);

/*
 * Attach this dentry to a cluster lock.
 *
 * Dentry locks cover all links in a given directory to a particular
 * inode. We करो this so that ocfs2 can build a lock name which all
 * nodes in the cluster can agree on at all बार. Shoving full names
 * in the cluster lock won't work due to size restrictions. Covering
 * links inside of a directory is a good compromise because it still
 * allows us to use the parent directory lock to synchronize
 * operations.
 *
 * Call this function with the parent dir semaphore and the parent dir
 * cluster lock held.
 *
 * The dir semaphore will protect us from having to worry about
 * concurrent processes on our node trying to attach a lock at the
 * same समय.
 *
 * The dir cluster lock (held at either PR or EX mode) protects us
 * from unlink and नाम on other nodes.
 *
 * A dput() can happen asynchronously due to pruning, so we cover
 * attaching and detaching the dentry lock with a
 * dentry_attach_lock.
 *
 * A node which has करोne lookup on a name retains a रक्षित पढ़ो
 * lock until final dput. If the user requests and unlink or नाम,
 * the रक्षित पढ़ो is upgraded to an exclusive lock. Other nodes
 * who have seen the dentry will then be inक्रमmed that they need to
 * करोwngrade their lock, which will involve d_delete on the
 * dentry. This happens in ocfs2_dentry_convert_worker().
 */
पूर्णांक ocfs2_dentry_attach_lock(काष्ठा dentry *dentry,
			     काष्ठा inode *inode,
			     u64 parent_blkno)
अणु
	पूर्णांक ret;
	काष्ठा dentry *alias;
	काष्ठा ocfs2_dentry_lock *dl = dentry->d_fsdata;

	trace_ocfs2_dentry_attach_lock(dentry->d_name.len, dentry->d_name.name,
				       (अचिन्हित दीर्घ दीर्घ)parent_blkno, dl);

	/*
	 * Negative dentry. We ignore these क्रम now.
	 *
	 * XXX: Could we can improve ocfs2_dentry_revalidate() by
	 * tracking these?
	 */
	अगर (!inode)
		वापस 0;

	अगर (d_really_is_negative(dentry) && dentry->d_fsdata) अणु
		/* Converting a negative dentry to positive
		   Clear dentry->d_fsdata */
		dentry->d_fsdata = dl = शून्य;
	पूर्ण

	अगर (dl) अणु
		mlog_bug_on_msg(dl->dl_parent_blkno != parent_blkno,
				" \"%pd\": old parent: %llu, new: %llu\n",
				dentry,
				(अचिन्हित दीर्घ दीर्घ)parent_blkno,
				(अचिन्हित दीर्घ दीर्घ)dl->dl_parent_blkno);
		वापस 0;
	पूर्ण

	alias = ocfs2_find_local_alias(inode, parent_blkno, 0);
	अगर (alias) अणु
		/*
		 * Great, an alias exists, which means we must have a
		 * dentry lock alपढ़ोy. We can just grab the lock off
		 * the alias and add it to the list.
		 *
		 * We're depending here on the fact that this dentry
		 * was found and exists in the dcache and so must have
		 * a reference to the dentry_lock because we can't
		 * race creates. Final dput() cannot happen on it
		 * since we have it pinned, so our reference is safe.
		 */
		dl = alias->d_fsdata;
		mlog_bug_on_msg(!dl, "parent %llu, ino %llu\n",
				(अचिन्हित दीर्घ दीर्घ)parent_blkno,
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

		mlog_bug_on_msg(dl->dl_parent_blkno != parent_blkno,
				" \"%pd\": old parent: %llu, new: %llu\n",
				dentry,
				(अचिन्हित दीर्घ दीर्घ)parent_blkno,
				(अचिन्हित दीर्घ दीर्घ)dl->dl_parent_blkno);

		trace_ocfs2_dentry_attach_lock_found(dl->dl_lockres.l_name,
				(अचिन्हित दीर्घ दीर्घ)parent_blkno,
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

		जाओ out_attach;
	पूर्ण

	/*
	 * There are no other aliases
	 */
	dl = kदो_स्मृति(माप(*dl), GFP_NOFS);
	अगर (!dl) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	dl->dl_count = 0;
	/*
	 * Does this have to happen below, क्रम all attaches, in हाल
	 * the काष्ठा inode माला_लो blown away by the करोwnconvert thपढ़ो?
	 */
	dl->dl_inode = igrab(inode);
	dl->dl_parent_blkno = parent_blkno;
	ocfs2_dentry_lock_res_init(dl, parent_blkno, inode);

out_attach:
	spin_lock(&dentry_attach_lock);
	अगर (unlikely(dentry->d_fsdata && !alias)) अणु
		/* d_fsdata is set by a racing thपढ़ो which is करोing
		 * the same thing as this thपढ़ो is करोing. Leave the racing
		 * thपढ़ो going ahead and we वापस here.
		 */
		spin_unlock(&dentry_attach_lock);
		iput(dl->dl_inode);
		ocfs2_lock_res_मुक्त(&dl->dl_lockres);
		kमुक्त(dl);
		वापस 0;
	पूर्ण

	dentry->d_fsdata = dl;
	dl->dl_count++;
	spin_unlock(&dentry_attach_lock);

	/*
	 * This actually माला_लो us our PRMODE level lock. From now on,
	 * we'll have a notअगरication अगर one of these names is
	 * destroyed on another node.
	 */
	ret = ocfs2_dentry_lock(dentry, 0);
	अगर (!ret)
		ocfs2_dentry_unlock(dentry, 0);
	अन्यथा
		mlog_त्रुटि_सं(ret);

	/*
	 * In हाल of error, manually मुक्त the allocation and करो the iput().
	 * We need to करो this because error here means no d_instantiate(),
	 * which means iput() will not be called during dput(dentry).
	 */
	अगर (ret < 0 && !alias) अणु
		ocfs2_lock_res_मुक्त(&dl->dl_lockres);
		BUG_ON(dl->dl_count != 1);
		spin_lock(&dentry_attach_lock);
		dentry->d_fsdata = शून्य;
		spin_unlock(&dentry_attach_lock);
		kमुक्त(dl);
		iput(inode);
	पूर्ण

	dput(alias);

	वापस ret;
पूर्ण

/*
 * ocfs2_dentry_iput() and मित्रs.
 *
 * At this poपूर्णांक, our particular dentry is detached from the inodes
 * alias list, so there's no way that the locking code can find it.
 *
 * The पूर्णांकeresting stuff happens when we determine that our lock needs
 * to go away because this is the last subdir alias in the
 * प्रणाली. This function needs to handle a couple things:
 *
 * 1) Synchronizing lock shutकरोwn with the करोwnconvert thपढ़ोs. This
 *    is alपढ़ोy handled क्रम us via the lockres release drop function
 *    called in ocfs2_release_dentry_lock()
 *
 * 2) A race may occur when we're करोing our lock shutकरोwn and
 *    another process wants to create a new dentry lock. Right now we
 *    let them race, which means that क्रम a very लघु जबतक, this
 *    node might have two locks on a lock resource. This should be a
 *    problem though because one of them is in the process of being
 *    thrown out.
 */
अटल व्योम ocfs2_drop_dentry_lock(काष्ठा ocfs2_super *osb,
				   काष्ठा ocfs2_dentry_lock *dl)
अणु
	iput(dl->dl_inode);
	ocfs2_simple_drop_lockres(osb, &dl->dl_lockres);
	ocfs2_lock_res_मुक्त(&dl->dl_lockres);
	kमुक्त(dl);
पूर्ण

व्योम ocfs2_dentry_lock_put(काष्ठा ocfs2_super *osb,
			   काष्ठा ocfs2_dentry_lock *dl)
अणु
	पूर्णांक unlock = 0;

	BUG_ON(dl->dl_count == 0);

	spin_lock(&dentry_attach_lock);
	dl->dl_count--;
	unlock = !dl->dl_count;
	spin_unlock(&dentry_attach_lock);

	अगर (unlock)
		ocfs2_drop_dentry_lock(osb, dl);
पूर्ण

अटल व्योम ocfs2_dentry_iput(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_dentry_lock *dl = dentry->d_fsdata;

	अगर (!dl) अणु
		/*
		 * No dentry lock is ok अगर we're disconnected or
		 * unhashed.
		 */
		अगर (!(dentry->d_flags & DCACHE_DISCONNECTED) &&
		    !d_unhashed(dentry)) अणु
			अचिन्हित दीर्घ दीर्घ ino = 0ULL;
			अगर (inode)
				ino = (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno;
			mlog(ML_ERROR, "Dentry is missing cluster lock. "
			     "inode: %llu, d_flags: 0x%x, d_name: %pd\n",
			     ino, dentry->d_flags, dentry);
		पूर्ण

		जाओ out;
	पूर्ण

	mlog_bug_on_msg(dl->dl_count == 0, "dentry: %pd, count: %u\n",
			dentry, dl->dl_count);

	ocfs2_dentry_lock_put(OCFS2_SB(dentry->d_sb), dl);

out:
	iput(inode);
पूर्ण

/*
 * d_move(), but keep the locks in sync.
 *
 * When we are करोne, "dentry" will have the parent dir and name of
 * "target", which will be thrown away.
 *
 * We manually update the lock of "dentry" अगर need be.
 *
 * "target" करोesn't have it's dentry lock touched - we allow the later
 * dput() to handle this क्रम us.
 *
 * This is called during ocfs2_नाम(), जबतक holding parent
 * directory locks. The dentries have alपढ़ोy been deleted on other
 * nodes via ocfs2_remote_dentry_delete().
 *
 * Normally, the VFS handles the d_move() क्रम the file प्रणाली, after
 * the ->नाम() callback. OCFS2 wants to handle this पूर्णांकernally, so
 * the new lock can be created atomically with respect to the cluster.
 */
व्योम ocfs2_dentry_move(काष्ठा dentry *dentry, काष्ठा dentry *target,
		       काष्ठा inode *old_dir, काष्ठा inode *new_dir)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(old_dir->i_sb);
	काष्ठा inode *inode = d_inode(dentry);

	/*
	 * Move within the same directory, so the actual lock info won't
	 * change.
	 *
	 * XXX: Is there any advantage to dropping the lock here?
	 */
	अगर (old_dir == new_dir)
		जाओ out_move;

	ocfs2_dentry_lock_put(osb, dentry->d_fsdata);

	dentry->d_fsdata = शून्य;
	ret = ocfs2_dentry_attach_lock(dentry, inode, OCFS2_I(new_dir)->ip_blkno);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out_move:
	d_move(dentry, target);
पूर्ण

स्थिर काष्ठा dentry_operations ocfs2_dentry_ops = अणु
	.d_revalidate		= ocfs2_dentry_revalidate,
	.d_iput			= ocfs2_dentry_iput,
पूर्ण;
