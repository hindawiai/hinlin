<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/locks.c
 *
 *  Provide support क्रम fcntl()'s F_GETLK, F_SETLK, and F_SETLKW calls.
 *  Doug Evans (dje@spअगरf.uucp), August 07, 1992
 *
 *  Deadlock detection added.
 *  FIXME: one thing isn't handled yet:
 *	- mandatory locks (requires lots of changes अन्यथाwhere)
 *  Kelly Carmichael (kelly@[142.24.8.65]), September 17, 1994.
 *
 *  Miscellaneous edits, and a total reग_लिखो of posix_lock_file() code.
 *  Kai Petzke (wpp@marie.physik.tu-berlin.de), 1994
 *
 *  Converted file_lock_table to a linked list from an array, which eliminates
 *  the limits on how many active file locks are खोलो.
 *  Chad Page (pageone@netcom.com), November 27, 1994
 *
 *  Removed dependency on file descriptors. dup()'ed file descriptors now
 *  get the same locks as the original file descriptors, and a बंद() on
 *  any file descriptor हटाओs ALL the locks on the file क्रम the current
 *  process. Since locks still depend on the process id, locks are inherited
 *  after an exec() but not after a विभाजन(). This agrees with POSIX, and both
 *  BSD and SVR4 practice.
 *  Andy Walker (andy@lysaker.kvaerner.no), February 14, 1995
 *
 *  Scrapped मुक्त list which is redundant now that we allocate locks
 *  dynamically with kदो_स्मृति()/kमुक्त().
 *  Andy Walker (andy@lysaker.kvaerner.no), February 21, 1995
 *
 *  Implemented two lock personalities - FL_FLOCK and FL_POSIX.
 *
 *  FL_POSIX locks are created with calls to fcntl() and lockf() through the
 *  fcntl() प्रणाली call. They have the semantics described above.
 *
 *  FL_FLOCK locks are created with calls to flock(), through the flock()
 *  प्रणाली call, which is new. Old C libraries implement flock() via fcntl()
 *  and will जारी to use the old, broken implementation.
 *
 *  FL_FLOCK locks follow the 4.4 BSD flock() semantics. They are associated
 *  with a file poपूर्णांकer (filp). As a result they can be shared by a parent
 *  process and its children after a विभाजन(). They are हटाओd when the last
 *  file descriptor referring to the file poपूर्णांकer is बंदd (unless explicitly
 *  unlocked).
 *
 *  FL_FLOCK locks never deadlock, an existing lock is always हटाओd beक्रमe
 *  upgrading from shared to exclusive (or vice versa). When this happens
 *  any processes blocked by the current lock are woken up and allowed to
 *  run beक्रमe the new lock is applied.
 *  Andy Walker (andy@lysaker.kvaerner.no), June 09, 1995
 *
 *  Removed some race conditions in flock_lock_file(), marked other possible
 *  races. Just grep क्रम FIXME to see them.
 *  Dmitry Gorodchanin (pgmdsg@ibi.com), February 09, 1996.
 *
 *  Addressed Dmitry's concerns. Deadlock checking no दीर्घer recursive.
 *  Lock allocation changed to GFP_ATOMIC as we can't afक्रमd to sleep
 *  once we've checked क्रम blocking and deadlocking.
 *  Andy Walker (andy@lysaker.kvaerner.no), April 03, 1996.
 *
 *  Initial implementation of mandatory locks. SunOS turned out to be
 *  a rotten model, so I implemented the "obvious" semantics.
 *  See 'Documentation/filesystems/mandatory-locking.rst' क्रम details.
 *  Andy Walker (andy@lysaker.kvaerner.no), April 06, 1996.
 *
 *  Don't allow mandatory locks on mmap()'ed files. Added simple functions to
 *  check अगर a file has mandatory locks, used by mmap(), खोलो() and creat() to
 *  see अगर प्रणाली call should be rejected. Ref. HP-UX/SunOS/Solaris Reference
 *  Manual, Section 2.
 *  Andy Walker (andy@lysaker.kvaerner.no), April 09, 1996.
 *
 *  Tidied up block list handling. Added '/proc/locks' पूर्णांकerface.
 *  Andy Walker (andy@lysaker.kvaerner.no), April 24, 1996.
 *
 *  Fixed deadlock condition क्रम pathological code that mixes calls to
 *  flock() and fcntl().
 *  Andy Walker (andy@lysaker.kvaerner.no), April 29, 1996.
 *
 *  Allow only one type of locking scheme (FL_POSIX or FL_FLOCK) to be in use
 *  क्रम a given file at a समय. Changed the CONFIG_LOCK_MANDATORY scheme to
 *  guarantee sensible behaviour in the हाल where file प्रणाली modules might
 *  be compiled with dअगरferent options than the kernel itself.
 *  Andy Walker (andy@lysaker.kvaerner.no), May 15, 1996.
 *
 *  Added a couple of missing wake_up() calls. Thanks to Thomas Meckel
 *  (Thomas.Meckel@mni.fh-giessen.de) क्रम spotting this.
 *  Andy Walker (andy@lysaker.kvaerner.no), May 15, 1996.
 *
 *  Changed FL_POSIX locks to use the block list in the same way as FL_FLOCK
 *  locks. Changed process synchronisation to aव्योम dereferencing locks that
 *  have alपढ़ोy been मुक्तd.
 *  Andy Walker (andy@lysaker.kvaerner.no), Sep 21, 1996.
 *
 *  Made the block list a circular list to minimise searching in the list.
 *  Andy Walker (andy@lysaker.kvaerner.no), Sep 25, 1996.
 *
 *  Made mandatory locking a mount option. Default is not to allow mandatory
 *  locking.
 *  Andy Walker (andy@lysaker.kvaerner.no), Oct 04, 1996.
 *
 *  Some adaptations क्रम NFS support.
 *  Olaf Kirch (okir@monad.swb.de), Dec 1996,
 *
 *  Fixed /proc/locks पूर्णांकerface so that we can't overrun the buffer we are handed.
 *  Andy Walker (andy@lysaker.kvaerner.no), May 12, 1997.
 *
 *  Use slab allocator instead of kदो_स्मृति/kमुक्त.
 *  Use generic list implementation from <linux/list.h>.
 *  Sped up posix_locks_deadlock by only considering blocked locks.
 *  Matthew Wilcox <willy@debian.org>, March, 2000.
 *
 *  Leases and LOCK_MAND
 *  Matthew Wilcox <willy@debian.org>, June, 2000.
 *  Stephen Rothwell <sfr@canb.auug.org.au>, June, 2000.
 *
 * Locking conflicts and dependencies:
 * If multiple thपढ़ोs attempt to lock the same byte (or flock the same file)
 * only one can be granted the lock, and other must रुको their turn.
 * The first lock has been "applied" or "granted", the others are "waiting"
 * and are "blocked" by the "applied" lock..
 *
 * Waiting and applied locks are all kept in trees whose properties are:
 *
 *	- the root of a tree may be an applied or रुकोing lock.
 *	- every other node in the tree is a रुकोing lock that
 *	  conflicts with every ancestor of that node.
 *
 * Every such tree begins lअगरe as a रुकोing singleton which obviously
 * satisfies the above properties.
 *
 * The only ways we modअगरy trees preserve these properties:
 *
 *	1. We may add a new leaf node, but only after first verअगरying that it
 *	   conflicts with all of its ancestors.
 *	2. We may हटाओ the root of a tree, creating a new singleton
 *	   tree from the root and N new trees rooted in the immediate
 *	   children.
 *	3. If the root of a tree is not currently an applied lock, we may
 *	   apply it (अगर possible).
 *	4. We may upgrade the root of the tree (either extend its range,
 *	   or upgrade its entire range from पढ़ो to ग_लिखो).
 *
 * When an applied lock is modअगरied in a way that reduces or करोwngrades any
 * part of its range, we हटाओ all its children (2 above).  This particularly
 * happens when a lock is unlocked.
 *
 * For each of those child trees we "wake up" the thपढ़ो which is
 * रुकोing क्रम the lock so it can जारी handling as follows: अगर the
 * root of the tree applies, we करो so (3).  If it करोesn't, it must
 * conflict with some applied lock.  We हटाओ (wake up) all of its children
 * (2), and add it is a new leaf to the tree rooted in the applied
 * lock (1).  We then repeat the process recursively with those
 * children.
 *
 */

#समावेश <linux/capability.h>
#समावेश <linux/file.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/security.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/समय.स>
#समावेश <linux/rcupdate.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/percpu.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/filelock.h>

#समावेश <linux/uaccess.h>

#घोषणा IS_POSIX(fl)	(fl->fl_flags & FL_POSIX)
#घोषणा IS_FLOCK(fl)	(fl->fl_flags & FL_FLOCK)
#घोषणा IS_LEASE(fl)	(fl->fl_flags & (FL_LEASE|FL_DELEG|FL_LAYOUT))
#घोषणा IS_OFDLCK(fl)	(fl->fl_flags & FL_OFDLCK)
#घोषणा IS_REMOTELCK(fl)	(fl->fl_pid <= 0)

अटल bool lease_अवरोधing(काष्ठा file_lock *fl)
अणु
	वापस fl->fl_flags & (FL_UNLOCK_PENDING | FL_DOWNGRADE_PENDING);
पूर्ण

अटल पूर्णांक target_leasetype(काष्ठा file_lock *fl)
अणु
	अगर (fl->fl_flags & FL_UNLOCK_PENDING)
		वापस F_UNLCK;
	अगर (fl->fl_flags & FL_DOWNGRADE_PENDING)
		वापस F_RDLCK;
	वापस fl->fl_type;
पूर्ण

पूर्णांक leases_enable = 1;
पूर्णांक lease_अवरोध_समय = 45;

/*
 * The global file_lock_list is only used क्रम displaying /proc/locks, so we
 * keep a list on each CPU, with each list रक्षित by its own spinlock.
 * Global serialization is करोne using file_rwsem.
 *
 * Note that alterations to the list also require that the relevant flc_lock is
 * held.
 */
काष्ठा file_lock_list_काष्ठा अणु
	spinlock_t		lock;
	काष्ठा hlist_head	hlist;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा file_lock_list_काष्ठा, file_lock_list);
DEFINE_STATIC_PERCPU_RWSEM(file_rwsem);


/*
 * The blocked_hash is used to find POSIX lock loops क्रम deadlock detection.
 * It is रक्षित by blocked_lock_lock.
 *
 * We hash locks by lockowner in order to optimize searching क्रम the lock a
 * particular lockowner is रुकोing on.
 *
 * FIXME: make this value scale via some heuristic? We generally will want more
 * buckets when we have more lockowners holding locks, but that's a little
 * dअगरficult to determine without knowing what the workload will look like.
 */
#घोषणा BLOCKED_HASH_BITS	7
अटल DEFINE_HASHTABLE(blocked_hash, BLOCKED_HASH_BITS);

/*
 * This lock protects the blocked_hash. Generally, अगर you're accessing it, you
 * want to be holding this lock.
 *
 * In addition, it also protects the fl->fl_blocked_requests list, and the
 * fl->fl_blocker poपूर्णांकer क्रम file_lock काष्ठाures that are acting as lock
 * requests (in contrast to those that are acting as records of acquired locks).
 *
 * Note that when we acquire this lock in order to change the above fields,
 * we often hold the flc_lock as well. In certain हालs, when पढ़ोing the fields
 * रक्षित by this lock, we can skip acquiring it अगरf we alपढ़ोy hold the
 * flc_lock.
 */
अटल DEFINE_SPINLOCK(blocked_lock_lock);

अटल काष्ठा kmem_cache *flctx_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *filelock_cache __पढ़ो_mostly;

अटल काष्ठा file_lock_context *
locks_get_lock_context(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा file_lock_context *ctx;

	/* paired with cmpxchg() below */
	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (likely(ctx) || type == F_UNLCK)
		जाओ out;

	ctx = kmem_cache_alloc(flctx_cache, GFP_KERNEL);
	अगर (!ctx)
		जाओ out;

	spin_lock_init(&ctx->flc_lock);
	INIT_LIST_HEAD(&ctx->flc_flock);
	INIT_LIST_HEAD(&ctx->flc_posix);
	INIT_LIST_HEAD(&ctx->flc_lease);

	/*
	 * Assign the poपूर्णांकer अगर it's not alपढ़ोy asचिन्हित. If it is, then
	 * मुक्त the context we just allocated.
	 */
	अगर (cmpxchg(&inode->i_flctx, शून्य, ctx)) अणु
		kmem_cache_मुक्त(flctx_cache, ctx);
		ctx = smp_load_acquire(&inode->i_flctx);
	पूर्ण
out:
	trace_locks_get_lock_context(inode, type, ctx);
	वापस ctx;
पूर्ण

अटल व्योम
locks_dump_ctx_list(काष्ठा list_head *list, अक्षर *list_type)
अणु
	काष्ठा file_lock *fl;

	list_क्रम_each_entry(fl, list, fl_list) अणु
		pr_warn("%s: fl_owner=%p fl_flags=0x%x fl_type=0x%x fl_pid=%u\n", list_type, fl->fl_owner, fl->fl_flags, fl->fl_type, fl->fl_pid);
	पूर्ण
पूर्ण

अटल व्योम
locks_check_ctx_lists(काष्ठा inode *inode)
अणु
	काष्ठा file_lock_context *ctx = inode->i_flctx;

	अगर (unlikely(!list_empty(&ctx->flc_flock) ||
		     !list_empty(&ctx->flc_posix) ||
		     !list_empty(&ctx->flc_lease))) अणु
		pr_warn("Leaked locks on dev=0x%x:0x%x ino=0x%lx:\n",
			MAJOR(inode->i_sb->s_dev), MINOR(inode->i_sb->s_dev),
			inode->i_ino);
		locks_dump_ctx_list(&ctx->flc_flock, "FLOCK");
		locks_dump_ctx_list(&ctx->flc_posix, "POSIX");
		locks_dump_ctx_list(&ctx->flc_lease, "LEASE");
	पूर्ण
पूर्ण

अटल व्योम
locks_check_ctx_file_list(काष्ठा file *filp, काष्ठा list_head *list,
				अक्षर *list_type)
अणु
	काष्ठा file_lock *fl;
	काष्ठा inode *inode = locks_inode(filp);

	list_क्रम_each_entry(fl, list, fl_list)
		अगर (fl->fl_file == filp)
			pr_warn("Leaked %s lock on dev=0x%x:0x%x ino=0x%lx "
				" fl_owner=%p fl_flags=0x%x fl_type=0x%x fl_pid=%u\n",
				list_type, MAJOR(inode->i_sb->s_dev),
				MINOR(inode->i_sb->s_dev), inode->i_ino,
				fl->fl_owner, fl->fl_flags, fl->fl_type, fl->fl_pid);
पूर्ण

व्योम
locks_मुक्त_lock_context(काष्ठा inode *inode)
अणु
	काष्ठा file_lock_context *ctx = inode->i_flctx;

	अगर (unlikely(ctx)) अणु
		locks_check_ctx_lists(inode);
		kmem_cache_मुक्त(flctx_cache, ctx);
	पूर्ण
पूर्ण

अटल व्योम locks_init_lock_heads(काष्ठा file_lock *fl)
अणु
	INIT_HLIST_NODE(&fl->fl_link);
	INIT_LIST_HEAD(&fl->fl_list);
	INIT_LIST_HEAD(&fl->fl_blocked_requests);
	INIT_LIST_HEAD(&fl->fl_blocked_member);
	init_रुकोqueue_head(&fl->fl_रुको);
पूर्ण

/* Allocate an empty lock काष्ठाure. */
काष्ठा file_lock *locks_alloc_lock(व्योम)
अणु
	काष्ठा file_lock *fl = kmem_cache_zalloc(filelock_cache, GFP_KERNEL);

	अगर (fl)
		locks_init_lock_heads(fl);

	वापस fl;
पूर्ण
EXPORT_SYMBOL_GPL(locks_alloc_lock);

व्योम locks_release_निजी(काष्ठा file_lock *fl)
अणु
	BUG_ON(रुकोqueue_active(&fl->fl_रुको));
	BUG_ON(!list_empty(&fl->fl_list));
	BUG_ON(!list_empty(&fl->fl_blocked_requests));
	BUG_ON(!list_empty(&fl->fl_blocked_member));
	BUG_ON(!hlist_unhashed(&fl->fl_link));

	अगर (fl->fl_ops) अणु
		अगर (fl->fl_ops->fl_release_निजी)
			fl->fl_ops->fl_release_निजी(fl);
		fl->fl_ops = शून्य;
	पूर्ण

	अगर (fl->fl_lmops) अणु
		अगर (fl->fl_lmops->lm_put_owner) अणु
			fl->fl_lmops->lm_put_owner(fl->fl_owner);
			fl->fl_owner = शून्य;
		पूर्ण
		fl->fl_lmops = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(locks_release_निजी);

/* Free a lock which is not in use. */
व्योम locks_मुक्त_lock(काष्ठा file_lock *fl)
अणु
	locks_release_निजी(fl);
	kmem_cache_मुक्त(filelock_cache, fl);
पूर्ण
EXPORT_SYMBOL(locks_मुक्त_lock);

अटल व्योम
locks_dispose_list(काष्ठा list_head *dispose)
अणु
	काष्ठा file_lock *fl;

	जबतक (!list_empty(dispose)) अणु
		fl = list_first_entry(dispose, काष्ठा file_lock, fl_list);
		list_del_init(&fl->fl_list);
		locks_मुक्त_lock(fl);
	पूर्ण
पूर्ण

व्योम locks_init_lock(काष्ठा file_lock *fl)
अणु
	स_रखो(fl, 0, माप(काष्ठा file_lock));
	locks_init_lock_heads(fl);
पूर्ण
EXPORT_SYMBOL(locks_init_lock);

/*
 * Initialize a new lock from an existing file_lock काष्ठाure.
 */
व्योम locks_copy_conflock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	new->fl_owner = fl->fl_owner;
	new->fl_pid = fl->fl_pid;
	new->fl_file = शून्य;
	new->fl_flags = fl->fl_flags;
	new->fl_type = fl->fl_type;
	new->fl_start = fl->fl_start;
	new->fl_end = fl->fl_end;
	new->fl_lmops = fl->fl_lmops;
	new->fl_ops = शून्य;

	अगर (fl->fl_lmops) अणु
		अगर (fl->fl_lmops->lm_get_owner)
			fl->fl_lmops->lm_get_owner(fl->fl_owner);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(locks_copy_conflock);

व्योम locks_copy_lock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	/* "new" must be a freshly-initialized lock */
	WARN_ON_ONCE(new->fl_ops);

	locks_copy_conflock(new, fl);

	new->fl_file = fl->fl_file;
	new->fl_ops = fl->fl_ops;

	अगर (fl->fl_ops) अणु
		अगर (fl->fl_ops->fl_copy_lock)
			fl->fl_ops->fl_copy_lock(new, fl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(locks_copy_lock);

अटल व्योम locks_move_blocks(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	काष्ठा file_lock *f;

	/*
	 * As ctx->flc_lock is held, new requests cannot be added to
	 * ->fl_blocked_requests, so we करोn't need a lock to check अगर it
	 * is empty.
	 */
	अगर (list_empty(&fl->fl_blocked_requests))
		वापस;
	spin_lock(&blocked_lock_lock);
	list_splice_init(&fl->fl_blocked_requests, &new->fl_blocked_requests);
	list_क्रम_each_entry(f, &new->fl_blocked_requests, fl_blocked_member)
		f->fl_blocker = new;
	spin_unlock(&blocked_lock_lock);
पूर्ण

अटल अंतरभूत पूर्णांक flock_translate_cmd(पूर्णांक cmd) अणु
	अगर (cmd & LOCK_MAND)
		वापस cmd & (LOCK_MAND | LOCK_RW);
	चयन (cmd) अणु
	हाल LOCK_SH:
		वापस F_RDLCK;
	हाल LOCK_EX:
		वापस F_WRLCK;
	हाल LOCK_UN:
		वापस F_UNLCK;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* Fill in a file_lock काष्ठाure with an appropriate FLOCK lock. */
अटल काष्ठा file_lock *
flock_make_lock(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	पूर्णांक type = flock_translate_cmd(cmd);

	अगर (type < 0)
		वापस ERR_PTR(type);

	अगर (fl == शून्य) अणु
		fl = locks_alloc_lock();
		अगर (fl == शून्य)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण अन्यथा अणु
		locks_init_lock(fl);
	पूर्ण

	fl->fl_file = filp;
	fl->fl_owner = filp;
	fl->fl_pid = current->tgid;
	fl->fl_flags = FL_FLOCK;
	fl->fl_type = type;
	fl->fl_end = OFFSET_MAX;

	वापस fl;
पूर्ण

अटल पूर्णांक assign_type(काष्ठा file_lock *fl, दीर्घ type)
अणु
	चयन (type) अणु
	हाल F_RDLCK:
	हाल F_WRLCK:
	हाल F_UNLCK:
		fl->fl_type = type;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक flock64_to_posix_lock(काष्ठा file *filp, काष्ठा file_lock *fl,
				 काष्ठा flock64 *l)
अणु
	चयन (l->l_whence) अणु
	हाल शुरू_से:
		fl->fl_start = 0;
		अवरोध;
	हाल प्रस्तुत_से:
		fl->fl_start = filp->f_pos;
		अवरोध;
	हाल अंत_से:
		fl->fl_start = i_size_पढ़ो(file_inode(filp));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (l->l_start > OFFSET_MAX - fl->fl_start)
		वापस -EOVERFLOW;
	fl->fl_start += l->l_start;
	अगर (fl->fl_start < 0)
		वापस -EINVAL;

	/* POSIX-1996 leaves the हाल l->l_len < 0 undefined;
	   POSIX-2001 defines it. */
	अगर (l->l_len > 0) अणु
		अगर (l->l_len - 1 > OFFSET_MAX - fl->fl_start)
			वापस -EOVERFLOW;
		fl->fl_end = fl->fl_start + (l->l_len - 1);

	पूर्ण अन्यथा अगर (l->l_len < 0) अणु
		अगर (fl->fl_start + l->l_len < 0)
			वापस -EINVAL;
		fl->fl_end = fl->fl_start - 1;
		fl->fl_start += l->l_len;
	पूर्ण अन्यथा
		fl->fl_end = OFFSET_MAX;

	fl->fl_owner = current->files;
	fl->fl_pid = current->tgid;
	fl->fl_file = filp;
	fl->fl_flags = FL_POSIX;
	fl->fl_ops = शून्य;
	fl->fl_lmops = शून्य;

	वापस assign_type(fl, l->l_type);
पूर्ण

/* Verअगरy a "struct flock" and copy it to a "struct file_lock" as a POSIX
 * style lock.
 */
अटल पूर्णांक flock_to_posix_lock(काष्ठा file *filp, काष्ठा file_lock *fl,
			       काष्ठा flock *l)
अणु
	काष्ठा flock64 ll = अणु
		.l_type = l->l_type,
		.l_whence = l->l_whence,
		.l_start = l->l_start,
		.l_len = l->l_len,
	पूर्ण;

	वापस flock64_to_posix_lock(filp, fl, &ll);
पूर्ण

/* शेष lease lock manager operations */
अटल bool
lease_अवरोध_callback(काष्ठा file_lock *fl)
अणु
	समाप्त_fasync(&fl->fl_fasync, SIGIO, POLL_MSG);
	वापस false;
पूर्ण

अटल व्योम
lease_setup(काष्ठा file_lock *fl, व्योम **priv)
अणु
	काष्ठा file *filp = fl->fl_file;
	काष्ठा fasync_काष्ठा *fa = *priv;

	/*
	 * fasync_insert_entry() वापसs the old entry अगर any. If there was no
	 * old entry, then it used "priv" and inserted it पूर्णांकo the fasync list.
	 * Clear the poपूर्णांकer to indicate that it shouldn't be मुक्तd.
	 */
	अगर (!fasync_insert_entry(fa->fa_fd, filp, &fl->fl_fasync, fa))
		*priv = शून्य;

	__f_setown(filp, task_pid(current), PIDTYPE_TGID, 0);
पूर्ण

अटल स्थिर काष्ठा lock_manager_operations lease_manager_ops = अणु
	.lm_अवरोध = lease_अवरोध_callback,
	.lm_change = lease_modअगरy,
	.lm_setup = lease_setup,
पूर्ण;

/*
 * Initialize a lease, use the शेष lock manager operations
 */
अटल पूर्णांक lease_init(काष्ठा file *filp, दीर्घ type, काष्ठा file_lock *fl)
अणु
	अगर (assign_type(fl, type) != 0)
		वापस -EINVAL;

	fl->fl_owner = filp;
	fl->fl_pid = current->tgid;

	fl->fl_file = filp;
	fl->fl_flags = FL_LEASE;
	fl->fl_start = 0;
	fl->fl_end = OFFSET_MAX;
	fl->fl_ops = शून्य;
	fl->fl_lmops = &lease_manager_ops;
	वापस 0;
पूर्ण

/* Allocate a file_lock initialised to this type of lease */
अटल काष्ठा file_lock *lease_alloc(काष्ठा file *filp, दीर्घ type)
अणु
	काष्ठा file_lock *fl = locks_alloc_lock();
	पूर्णांक error = -ENOMEM;

	अगर (fl == शून्य)
		वापस ERR_PTR(error);

	error = lease_init(filp, type, fl);
	अगर (error) अणु
		locks_मुक्त_lock(fl);
		वापस ERR_PTR(error);
	पूर्ण
	वापस fl;
पूर्ण

/* Check अगर two locks overlap each other.
 */
अटल अंतरभूत पूर्णांक locks_overlap(काष्ठा file_lock *fl1, काष्ठा file_lock *fl2)
अणु
	वापस ((fl1->fl_end >= fl2->fl_start) &&
		(fl2->fl_end >= fl1->fl_start));
पूर्ण

/*
 * Check whether two locks have the same owner.
 */
अटल पूर्णांक posix_same_owner(काष्ठा file_lock *fl1, काष्ठा file_lock *fl2)
अणु
	वापस fl1->fl_owner == fl2->fl_owner;
पूर्ण

/* Must be called with the flc_lock held! */
अटल व्योम locks_insert_global_locks(काष्ठा file_lock *fl)
अणु
	काष्ठा file_lock_list_काष्ठा *fll = this_cpu_ptr(&file_lock_list);

	percpu_rwsem_निश्चित_held(&file_rwsem);

	spin_lock(&fll->lock);
	fl->fl_link_cpu = smp_processor_id();
	hlist_add_head(&fl->fl_link, &fll->hlist);
	spin_unlock(&fll->lock);
पूर्ण

/* Must be called with the flc_lock held! */
अटल व्योम locks_delete_global_locks(काष्ठा file_lock *fl)
अणु
	काष्ठा file_lock_list_काष्ठा *fll;

	percpu_rwsem_निश्चित_held(&file_rwsem);

	/*
	 * Aव्योम taking lock अगर alपढ़ोy unhashed. This is safe since this check
	 * is करोne जबतक holding the flc_lock, and new insertions पूर्णांकo the list
	 * also require that it be held.
	 */
	अगर (hlist_unhashed(&fl->fl_link))
		वापस;

	fll = per_cpu_ptr(&file_lock_list, fl->fl_link_cpu);
	spin_lock(&fll->lock);
	hlist_del_init(&fl->fl_link);
	spin_unlock(&fll->lock);
पूर्ण

अटल अचिन्हित दीर्घ
posix_owner_key(काष्ठा file_lock *fl)
अणु
	वापस (अचिन्हित दीर्घ)fl->fl_owner;
पूर्ण

अटल व्योम locks_insert_global_blocked(काष्ठा file_lock *रुकोer)
अणु
	lockdep_निश्चित_held(&blocked_lock_lock);

	hash_add(blocked_hash, &रुकोer->fl_link, posix_owner_key(रुकोer));
पूर्ण

अटल व्योम locks_delete_global_blocked(काष्ठा file_lock *रुकोer)
अणु
	lockdep_निश्चित_held(&blocked_lock_lock);

	hash_del(&रुकोer->fl_link);
पूर्ण

/* Remove रुकोer from blocker's block list.
 * When blocker ends up poपूर्णांकing to itself then the list is empty.
 *
 * Must be called with blocked_lock_lock held.
 */
अटल व्योम __locks_delete_block(काष्ठा file_lock *रुकोer)
अणु
	locks_delete_global_blocked(रुकोer);
	list_del_init(&रुकोer->fl_blocked_member);
पूर्ण

अटल व्योम __locks_wake_up_blocks(काष्ठा file_lock *blocker)
अणु
	जबतक (!list_empty(&blocker->fl_blocked_requests)) अणु
		काष्ठा file_lock *रुकोer;

		रुकोer = list_first_entry(&blocker->fl_blocked_requests,
					  काष्ठा file_lock, fl_blocked_member);
		__locks_delete_block(रुकोer);
		अगर (रुकोer->fl_lmops && रुकोer->fl_lmops->lm_notअगरy)
			रुकोer->fl_lmops->lm_notअगरy(रुकोer);
		अन्यथा
			wake_up(&रुकोer->fl_रुको);

		/*
		 * The setting of fl_blocker to शून्य marks the "done"
		 * poपूर्णांक in deleting a block. Paired with acquire at the top
		 * of locks_delete_block().
		 */
		smp_store_release(&रुकोer->fl_blocker, शून्य);
	पूर्ण
पूर्ण

/**
 *	locks_delete_block - stop रुकोing क्रम a file lock
 *	@रुकोer: the lock which was रुकोing
 *
 *	lockd/nfsd need to disconnect the lock जबतक working on it.
 */
पूर्णांक locks_delete_block(काष्ठा file_lock *रुकोer)
अणु
	पूर्णांक status = -ENOENT;

	/*
	 * If fl_blocker is शून्य, it won't be set again as this thपढ़ो "owns"
	 * the lock and is the only one that might try to claim the lock.
	 *
	 * We use acquire/release to manage fl_blocker so that we can
	 * optimize away taking the blocked_lock_lock in many हालs.
	 *
	 * The smp_load_acquire guarantees two things:
	 *
	 * 1/ that fl_blocked_requests can be tested locklessly. If something
	 * was recently added to that list it must have been in a locked region
	 * *beक्रमe* the locked region when fl_blocker was set to शून्य.
	 *
	 * 2/ that no other thपढ़ो is accessing 'waiter', so it is safe to मुक्त
	 * it.  __locks_wake_up_blocks is careful not to touch रुकोer after
	 * fl_blocker is released.
	 *
	 * If a lockless check of fl_blocker shows it to be शून्य, we know that
	 * no new locks can be inserted पूर्णांकo its fl_blocked_requests list, and
	 * can aव्योम करोing anything further अगर the list is empty.
	 */
	अगर (!smp_load_acquire(&रुकोer->fl_blocker) &&
	    list_empty(&रुकोer->fl_blocked_requests))
		वापस status;

	spin_lock(&blocked_lock_lock);
	अगर (रुकोer->fl_blocker)
		status = 0;
	__locks_wake_up_blocks(रुकोer);
	__locks_delete_block(रुकोer);

	/*
	 * The setting of fl_blocker to शून्य marks the "done" poपूर्णांक in deleting
	 * a block. Paired with acquire at the top of this function.
	 */
	smp_store_release(&रुकोer->fl_blocker, शून्य);
	spin_unlock(&blocked_lock_lock);
	वापस status;
पूर्ण
EXPORT_SYMBOL(locks_delete_block);

/* Insert रुकोer पूर्णांकo blocker's block list.
 * We use a circular list so that processes can be easily woken up in
 * the order they blocked. The करोcumentation करोesn't require this but
 * it seems like the reasonable thing to करो.
 *
 * Must be called with both the flc_lock and blocked_lock_lock held. The
 * fl_blocked_requests list itself is रक्षित by the blocked_lock_lock,
 * but by ensuring that the flc_lock is also held on insertions we can aव्योम
 * taking the blocked_lock_lock in some हालs when we see that the
 * fl_blocked_requests list is empty.
 *
 * Rather than just adding to the list, we check क्रम conflicts with any existing
 * रुकोers, and add beneath any रुकोer that blocks the new रुकोer.
 * Thus wakeups करोn't happen until needed.
 */
अटल व्योम __locks_insert_block(काष्ठा file_lock *blocker,
				 काष्ठा file_lock *रुकोer,
				 bool conflict(काष्ठा file_lock *,
					       काष्ठा file_lock *))
अणु
	काष्ठा file_lock *fl;
	BUG_ON(!list_empty(&रुकोer->fl_blocked_member));

new_blocker:
	list_क्रम_each_entry(fl, &blocker->fl_blocked_requests, fl_blocked_member)
		अगर (conflict(fl, रुकोer)) अणु
			blocker =  fl;
			जाओ new_blocker;
		पूर्ण
	रुकोer->fl_blocker = blocker;
	list_add_tail(&रुकोer->fl_blocked_member, &blocker->fl_blocked_requests);
	अगर (IS_POSIX(blocker) && !IS_OFDLCK(blocker))
		locks_insert_global_blocked(रुकोer);

	/* The requests in रुकोer->fl_blocked are known to conflict with
	 * रुकोer, but might not conflict with blocker, or the requests
	 * and lock which block it.  So they all need to be woken.
	 */
	__locks_wake_up_blocks(रुकोer);
पूर्ण

/* Must be called with flc_lock held. */
अटल व्योम locks_insert_block(काष्ठा file_lock *blocker,
			       काष्ठा file_lock *रुकोer,
			       bool conflict(काष्ठा file_lock *,
					     काष्ठा file_lock *))
अणु
	spin_lock(&blocked_lock_lock);
	__locks_insert_block(blocker, रुकोer, conflict);
	spin_unlock(&blocked_lock_lock);
पूर्ण

/*
 * Wake up processes blocked रुकोing क्रम blocker.
 *
 * Must be called with the inode->flc_lock held!
 */
अटल व्योम locks_wake_up_blocks(काष्ठा file_lock *blocker)
अणु
	/*
	 * Aव्योम taking global lock अगर list is empty. This is safe since new
	 * blocked requests are only added to the list under the flc_lock, and
	 * the flc_lock is always held here. Note that removal from the
	 * fl_blocked_requests list करोes not require the flc_lock, so we must
	 * recheck list_empty() after acquiring the blocked_lock_lock.
	 */
	अगर (list_empty(&blocker->fl_blocked_requests))
		वापस;

	spin_lock(&blocked_lock_lock);
	__locks_wake_up_blocks(blocker);
	spin_unlock(&blocked_lock_lock);
पूर्ण

अटल व्योम
locks_insert_lock_ctx(काष्ठा file_lock *fl, काष्ठा list_head *beक्रमe)
अणु
	list_add_tail(&fl->fl_list, beक्रमe);
	locks_insert_global_locks(fl);
पूर्ण

अटल व्योम
locks_unlink_lock_ctx(काष्ठा file_lock *fl)
अणु
	locks_delete_global_locks(fl);
	list_del_init(&fl->fl_list);
	locks_wake_up_blocks(fl);
पूर्ण

अटल व्योम
locks_delete_lock_ctx(काष्ठा file_lock *fl, काष्ठा list_head *dispose)
अणु
	locks_unlink_lock_ctx(fl);
	अगर (dispose)
		list_add(&fl->fl_list, dispose);
	अन्यथा
		locks_मुक्त_lock(fl);
पूर्ण

/* Determine अगर lock sys_fl blocks lock caller_fl. Common functionality
 * checks क्रम shared/exclusive status of overlapping locks.
 */
अटल bool locks_conflict(काष्ठा file_lock *caller_fl,
			   काष्ठा file_lock *sys_fl)
अणु
	अगर (sys_fl->fl_type == F_WRLCK)
		वापस true;
	अगर (caller_fl->fl_type == F_WRLCK)
		वापस true;
	वापस false;
पूर्ण

/* Determine अगर lock sys_fl blocks lock caller_fl. POSIX specअगरic
 * checking beक्रमe calling the locks_conflict().
 */
अटल bool posix_locks_conflict(काष्ठा file_lock *caller_fl,
				 काष्ठा file_lock *sys_fl)
अणु
	/* POSIX locks owned by the same process करो not conflict with
	 * each other.
	 */
	अगर (posix_same_owner(caller_fl, sys_fl))
		वापस false;

	/* Check whether they overlap */
	अगर (!locks_overlap(caller_fl, sys_fl))
		वापस false;

	वापस locks_conflict(caller_fl, sys_fl);
पूर्ण

/* Determine अगर lock sys_fl blocks lock caller_fl. FLOCK specअगरic
 * checking beक्रमe calling the locks_conflict().
 */
अटल bool flock_locks_conflict(काष्ठा file_lock *caller_fl,
				 काष्ठा file_lock *sys_fl)
अणु
	/* FLOCK locks referring to the same filp करो not conflict with
	 * each other.
	 */
	अगर (caller_fl->fl_file == sys_fl->fl_file)
		वापस false;
	अगर ((caller_fl->fl_type & LOCK_MAND) || (sys_fl->fl_type & LOCK_MAND))
		वापस false;

	वापस locks_conflict(caller_fl, sys_fl);
पूर्ण

व्योम
posix_test_lock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	काष्ठा file_lock *cfl;
	काष्ठा file_lock_context *ctx;
	काष्ठा inode *inode = locks_inode(filp);

	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (!ctx || list_empty_careful(&ctx->flc_posix)) अणु
		fl->fl_type = F_UNLCK;
		वापस;
	पूर्ण

	spin_lock(&ctx->flc_lock);
	list_क्रम_each_entry(cfl, &ctx->flc_posix, fl_list) अणु
		अगर (posix_locks_conflict(fl, cfl)) अणु
			locks_copy_conflock(fl, cfl);
			जाओ out;
		पूर्ण
	पूर्ण
	fl->fl_type = F_UNLCK;
out:
	spin_unlock(&ctx->flc_lock);
	वापस;
पूर्ण
EXPORT_SYMBOL(posix_test_lock);

/*
 * Deadlock detection:
 *
 * We attempt to detect deadlocks that are due purely to posix file
 * locks.
 *
 * We assume that a task can be रुकोing क्रम at most one lock at a समय.
 * So क्रम any acquired lock, the process holding that lock may be
 * रुकोing on at most one other lock.  That lock in turns may be held by
 * someone रुकोing क्रम at most one other lock.  Given a requested lock
 * caller_fl which is about to रुको क्रम a conflicting lock block_fl, we
 * follow this chain of रुकोers to ensure we are not about to create a
 * cycle.
 *
 * Since we करो this beक्रमe we ever put a process to sleep on a lock, we
 * are ensured that there is never a cycle; that is what guarantees that
 * the जबतक() loop in posix_locks_deadlock() eventually completes.
 *
 * Note: the above assumption may not be true when handling lock
 * requests from a broken NFS client. It may also fail in the presence
 * of tasks (such as posix thपढ़ोs) sharing the same खोलो file table.
 * To handle those हालs, we just bail out after a few iterations.
 *
 * For FL_OFDLCK locks, the owner is the filp, not the files_काष्ठा.
 * Because the owner is not even nominally tied to a thपढ़ो of
 * execution, the deadlock detection below can't reasonably work well. Just
 * skip it क्रम those.
 *
 * In principle, we could करो a more limited deadlock detection on FL_OFDLCK
 * locks that just checks क्रम the हाल where two tasks are attempting to
 * upgrade from पढ़ो to ग_लिखो locks on the same inode.
 */

#घोषणा MAX_DEADLK_ITERATIONS 10

/* Find a lock that the owner of the given block_fl is blocking on. */
अटल काष्ठा file_lock *what_owner_is_रुकोing_क्रम(काष्ठा file_lock *block_fl)
अणु
	काष्ठा file_lock *fl;

	hash_क्रम_each_possible(blocked_hash, fl, fl_link, posix_owner_key(block_fl)) अणु
		अगर (posix_same_owner(fl, block_fl)) अणु
			जबतक (fl->fl_blocker)
				fl = fl->fl_blocker;
			वापस fl;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Must be called with the blocked_lock_lock held! */
अटल पूर्णांक posix_locks_deadlock(काष्ठा file_lock *caller_fl,
				काष्ठा file_lock *block_fl)
अणु
	पूर्णांक i = 0;

	lockdep_निश्चित_held(&blocked_lock_lock);

	/*
	 * This deadlock detector can't reasonably detect deadlocks with
	 * FL_OFDLCK locks, since they aren't owned by a process, per-se.
	 */
	अगर (IS_OFDLCK(caller_fl))
		वापस 0;

	जबतक ((block_fl = what_owner_is_रुकोing_क्रम(block_fl))) अणु
		अगर (i++ > MAX_DEADLK_ITERATIONS)
			वापस 0;
		अगर (posix_same_owner(caller_fl, block_fl))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Try to create a FLOCK lock on filp. We always insert new FLOCK locks
 * after any leases, but beक्रमe any posix locks.
 *
 * Note that अगर called with an FL_EXISTS argument, the caller may determine
 * whether or not a lock was successfully मुक्तd by testing the वापस
 * value क्रम -ENOENT.
 */
अटल पूर्णांक flock_lock_inode(काष्ठा inode *inode, काष्ठा file_lock *request)
अणु
	काष्ठा file_lock *new_fl = शून्य;
	काष्ठा file_lock *fl;
	काष्ठा file_lock_context *ctx;
	पूर्णांक error = 0;
	bool found = false;
	LIST_HEAD(dispose);

	ctx = locks_get_lock_context(inode, request->fl_type);
	अगर (!ctx) अणु
		अगर (request->fl_type != F_UNLCK)
			वापस -ENOMEM;
		वापस (request->fl_flags & FL_EXISTS) ? -ENOENT : 0;
	पूर्ण

	अगर (!(request->fl_flags & FL_ACCESS) && (request->fl_type != F_UNLCK)) अणु
		new_fl = locks_alloc_lock();
		अगर (!new_fl)
			वापस -ENOMEM;
	पूर्ण

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);
	अगर (request->fl_flags & FL_ACCESS)
		जाओ find_conflict;

	list_क्रम_each_entry(fl, &ctx->flc_flock, fl_list) अणु
		अगर (request->fl_file != fl->fl_file)
			जारी;
		अगर (request->fl_type == fl->fl_type)
			जाओ out;
		found = true;
		locks_delete_lock_ctx(fl, &dispose);
		अवरोध;
	पूर्ण

	अगर (request->fl_type == F_UNLCK) अणु
		अगर ((request->fl_flags & FL_EXISTS) && !found)
			error = -ENOENT;
		जाओ out;
	पूर्ण

find_conflict:
	list_क्रम_each_entry(fl, &ctx->flc_flock, fl_list) अणु
		अगर (!flock_locks_conflict(request, fl))
			जारी;
		error = -EAGAIN;
		अगर (!(request->fl_flags & FL_SLEEP))
			जाओ out;
		error = खाता_LOCK_DEFERRED;
		locks_insert_block(fl, request, flock_locks_conflict);
		जाओ out;
	पूर्ण
	अगर (request->fl_flags & FL_ACCESS)
		जाओ out;
	locks_copy_lock(new_fl, request);
	locks_move_blocks(new_fl, request);
	locks_insert_lock_ctx(new_fl, &ctx->flc_flock);
	new_fl = शून्य;
	error = 0;

out:
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);
	अगर (new_fl)
		locks_मुक्त_lock(new_fl);
	locks_dispose_list(&dispose);
	trace_flock_lock_inode(inode, request, error);
	वापस error;
पूर्ण

अटल पूर्णांक posix_lock_inode(काष्ठा inode *inode, काष्ठा file_lock *request,
			    काष्ठा file_lock *conflock)
अणु
	काष्ठा file_lock *fl, *पंचांगp;
	काष्ठा file_lock *new_fl = शून्य;
	काष्ठा file_lock *new_fl2 = शून्य;
	काष्ठा file_lock *left = शून्य;
	काष्ठा file_lock *right = शून्य;
	काष्ठा file_lock_context *ctx;
	पूर्णांक error;
	bool added = false;
	LIST_HEAD(dispose);

	ctx = locks_get_lock_context(inode, request->fl_type);
	अगर (!ctx)
		वापस (request->fl_type == F_UNLCK) ? 0 : -ENOMEM;

	/*
	 * We may need two file_lock काष्ठाures क्रम this operation,
	 * so we get them in advance to aव्योम races.
	 *
	 * In some हालs we can be sure, that no new locks will be needed
	 */
	अगर (!(request->fl_flags & FL_ACCESS) &&
	    (request->fl_type != F_UNLCK ||
	     request->fl_start != 0 || request->fl_end != OFFSET_MAX)) अणु
		new_fl = locks_alloc_lock();
		new_fl2 = locks_alloc_lock();
	पूर्ण

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);
	/*
	 * New lock request. Walk all POSIX locks and look क्रम conflicts. If
	 * there are any, either वापस error or put the request on the
	 * blocker's list of रुकोers and the global blocked_hash.
	 */
	अगर (request->fl_type != F_UNLCK) अणु
		list_क्रम_each_entry(fl, &ctx->flc_posix, fl_list) अणु
			अगर (!posix_locks_conflict(request, fl))
				जारी;
			अगर (conflock)
				locks_copy_conflock(conflock, fl);
			error = -EAGAIN;
			अगर (!(request->fl_flags & FL_SLEEP))
				जाओ out;
			/*
			 * Deadlock detection and insertion पूर्णांकo the blocked
			 * locks list must be करोne जबतक holding the same lock!
			 */
			error = -EDEADLK;
			spin_lock(&blocked_lock_lock);
			/*
			 * Ensure that we करोn't find any locks blocked on this
			 * request during deadlock detection.
			 */
			__locks_wake_up_blocks(request);
			अगर (likely(!posix_locks_deadlock(request, fl))) अणु
				error = खाता_LOCK_DEFERRED;
				__locks_insert_block(fl, request,
						     posix_locks_conflict);
			पूर्ण
			spin_unlock(&blocked_lock_lock);
			जाओ out;
		पूर्ण
	पूर्ण

	/* If we're just looking for a conflict, we're करोne. */
	error = 0;
	अगर (request->fl_flags & FL_ACCESS)
		जाओ out;

	/* Find the first old lock with the same owner as the new lock */
	list_क्रम_each_entry(fl, &ctx->flc_posix, fl_list) अणु
		अगर (posix_same_owner(request, fl))
			अवरोध;
	पूर्ण

	/* Process locks with this owner. */
	list_क्रम_each_entry_safe_from(fl, पंचांगp, &ctx->flc_posix, fl_list) अणु
		अगर (!posix_same_owner(request, fl))
			अवरोध;

		/* Detect adjacent or overlapping regions (अगर same lock type) */
		अगर (request->fl_type == fl->fl_type) अणु
			/* In all comparisons of start vs end, use
			 * "start - 1" rather than "end + 1". If end
			 * is OFFSET_MAX, end + 1 will become negative.
			 */
			अगर (fl->fl_end < request->fl_start - 1)
				जारी;
			/* If the next lock in the list has entirely bigger
			 * addresses than the new one, insert the lock here.
			 */
			अगर (fl->fl_start - 1 > request->fl_end)
				अवरोध;

			/* If we come here, the new and old lock are of the
			 * same type and adjacent or overlapping. Make one
			 * lock yielding from the lower start address of both
			 * locks to the higher end address.
			 */
			अगर (fl->fl_start > request->fl_start)
				fl->fl_start = request->fl_start;
			अन्यथा
				request->fl_start = fl->fl_start;
			अगर (fl->fl_end < request->fl_end)
				fl->fl_end = request->fl_end;
			अन्यथा
				request->fl_end = fl->fl_end;
			अगर (added) अणु
				locks_delete_lock_ctx(fl, &dispose);
				जारी;
			पूर्ण
			request = fl;
			added = true;
		पूर्ण अन्यथा अणु
			/* Processing क्रम dअगरferent lock types is a bit
			 * more complex.
			 */
			अगर (fl->fl_end < request->fl_start)
				जारी;
			अगर (fl->fl_start > request->fl_end)
				अवरोध;
			अगर (request->fl_type == F_UNLCK)
				added = true;
			अगर (fl->fl_start < request->fl_start)
				left = fl;
			/* If the next lock in the list has a higher end
			 * address than the new one, insert the new one here.
			 */
			अगर (fl->fl_end > request->fl_end) अणु
				right = fl;
				अवरोध;
			पूर्ण
			अगर (fl->fl_start >= request->fl_start) अणु
				/* The new lock completely replaces an old
				 * one (This may happen several बार).
				 */
				अगर (added) अणु
					locks_delete_lock_ctx(fl, &dispose);
					जारी;
				पूर्ण
				/*
				 * Replace the old lock with new_fl, and
				 * हटाओ the old one. It's safe to करो the
				 * insert here since we know that we won't be
				 * using new_fl later, and that the lock is
				 * just replacing an existing lock.
				 */
				error = -ENOLCK;
				अगर (!new_fl)
					जाओ out;
				locks_copy_lock(new_fl, request);
				locks_move_blocks(new_fl, request);
				request = new_fl;
				new_fl = शून्य;
				locks_insert_lock_ctx(request, &fl->fl_list);
				locks_delete_lock_ctx(fl, &dispose);
				added = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * The above code only modअगरies existing locks in हाल of merging or
	 * replacing. If new lock(s) need to be inserted all modअगरications are
	 * करोne below this, so it's safe yet to bail out.
	 */
	error = -ENOLCK; /* "no luck" */
	अगर (right && left == right && !new_fl2)
		जाओ out;

	error = 0;
	अगर (!added) अणु
		अगर (request->fl_type == F_UNLCK) अणु
			अगर (request->fl_flags & FL_EXISTS)
				error = -ENOENT;
			जाओ out;
		पूर्ण

		अगर (!new_fl) अणु
			error = -ENOLCK;
			जाओ out;
		पूर्ण
		locks_copy_lock(new_fl, request);
		locks_move_blocks(new_fl, request);
		locks_insert_lock_ctx(new_fl, &fl->fl_list);
		fl = new_fl;
		new_fl = शून्य;
	पूर्ण
	अगर (right) अणु
		अगर (left == right) अणु
			/* The new lock अवरोधs the old one in two pieces,
			 * so we have to use the second new lock.
			 */
			left = new_fl2;
			new_fl2 = शून्य;
			locks_copy_lock(left, right);
			locks_insert_lock_ctx(left, &fl->fl_list);
		पूर्ण
		right->fl_start = request->fl_end + 1;
		locks_wake_up_blocks(right);
	पूर्ण
	अगर (left) अणु
		left->fl_end = request->fl_start - 1;
		locks_wake_up_blocks(left);
	पूर्ण
 out:
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);
	/*
	 * Free any unused locks.
	 */
	अगर (new_fl)
		locks_मुक्त_lock(new_fl);
	अगर (new_fl2)
		locks_मुक्त_lock(new_fl2);
	locks_dispose_list(&dispose);
	trace_posix_lock_inode(inode, request, error);

	वापस error;
पूर्ण

/**
 * posix_lock_file - Apply a POSIX-style lock to a file
 * @filp: The file to apply the lock to
 * @fl: The lock to be applied
 * @conflock: Place to वापस a copy of the conflicting lock, अगर found.
 *
 * Add a POSIX style lock to a file.
 * We merge adjacent & overlapping locks whenever possible.
 * POSIX locks are sorted by owner task, then by starting address
 *
 * Note that अगर called with an FL_EXISTS argument, the caller may determine
 * whether or not a lock was successfully मुक्तd by testing the वापस
 * value क्रम -ENOENT.
 */
पूर्णांक posix_lock_file(काष्ठा file *filp, काष्ठा file_lock *fl,
			काष्ठा file_lock *conflock)
अणु
	वापस posix_lock_inode(locks_inode(filp), fl, conflock);
पूर्ण
EXPORT_SYMBOL(posix_lock_file);

/**
 * posix_lock_inode_रुको - Apply a POSIX-style lock to a file
 * @inode: inode of file to which lock request should be applied
 * @fl: The lock to be applied
 *
 * Apply a POSIX style lock request to an inode.
 */
अटल पूर्णांक posix_lock_inode_रुको(काष्ठा inode *inode, काष्ठा file_lock *fl)
अणु
	पूर्णांक error;
	might_sleep ();
	क्रम (;;) अणु
		error = posix_lock_inode(inode, fl, शून्य);
		अगर (error != खाता_LOCK_DEFERRED)
			अवरोध;
		error = रुको_event_पूर्णांकerruptible(fl->fl_रुको,
					list_empty(&fl->fl_blocked_member));
		अगर (error)
			अवरोध;
	पूर्ण
	locks_delete_block(fl);
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_MANDATORY_खाता_LOCKING
/**
 * locks_mandatory_locked - Check क्रम an active lock
 * @file: the file to check
 *
 * Searches the inode's list of locks to find any POSIX locks which conflict.
 * This function is called from locks_verअगरy_locked() only.
 */
पूर्णांक locks_mandatory_locked(काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = locks_inode(file);
	काष्ठा file_lock_context *ctx;
	काष्ठा file_lock *fl;

	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (!ctx || list_empty_careful(&ctx->flc_posix))
		वापस 0;

	/*
	 * Search the lock list क्रम this inode क्रम any POSIX locks.
	 */
	spin_lock(&ctx->flc_lock);
	ret = 0;
	list_क्रम_each_entry(fl, &ctx->flc_posix, fl_list) अणु
		अगर (fl->fl_owner != current->files &&
		    fl->fl_owner != file) अणु
			ret = -EAGAIN;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&ctx->flc_lock);
	वापस ret;
पूर्ण

/**
 * locks_mandatory_area - Check क्रम a conflicting lock
 * @inode:	the file to check
 * @filp:       how the file was खोलोed (अगर it was)
 * @start:	first byte in the file to check
 * @end:	lastbyte in the file to check
 * @type:	%F_WRLCK क्रम a ग_लिखो lock, अन्यथा %F_RDLCK
 *
 * Searches the inode's list of locks to find any POSIX locks which conflict.
 */
पूर्णांक locks_mandatory_area(काष्ठा inode *inode, काष्ठा file *filp, loff_t start,
			 loff_t end, अचिन्हित अक्षर type)
अणु
	काष्ठा file_lock fl;
	पूर्णांक error;
	bool sleep = false;

	locks_init_lock(&fl);
	fl.fl_pid = current->tgid;
	fl.fl_file = filp;
	fl.fl_flags = FL_POSIX | FL_ACCESS;
	अगर (filp && !(filp->f_flags & O_NONBLOCK))
		sleep = true;
	fl.fl_type = type;
	fl.fl_start = start;
	fl.fl_end = end;

	क्रम (;;) अणु
		अगर (filp) अणु
			fl.fl_owner = filp;
			fl.fl_flags &= ~FL_SLEEP;
			error = posix_lock_inode(inode, &fl, शून्य);
			अगर (!error)
				अवरोध;
		पूर्ण

		अगर (sleep)
			fl.fl_flags |= FL_SLEEP;
		fl.fl_owner = current->files;
		error = posix_lock_inode(inode, &fl, शून्य);
		अगर (error != खाता_LOCK_DEFERRED)
			अवरोध;
		error = रुको_event_पूर्णांकerruptible(fl.fl_रुको,
					list_empty(&fl.fl_blocked_member));
		अगर (!error) अणु
			/*
			 * If we've been sleeping someone might have
			 * changed the permissions behind our back.
			 */
			अगर (__mandatory_lock(inode))
				जारी;
		पूर्ण

		अवरोध;
	पूर्ण
	locks_delete_block(&fl);

	वापस error;
पूर्ण
EXPORT_SYMBOL(locks_mandatory_area);
#पूर्ण_अगर /* CONFIG_MANDATORY_खाता_LOCKING */

अटल व्योम lease_clear_pending(काष्ठा file_lock *fl, पूर्णांक arg)
अणु
	चयन (arg) अणु
	हाल F_UNLCK:
		fl->fl_flags &= ~FL_UNLOCK_PENDING;
		fallthrough;
	हाल F_RDLCK:
		fl->fl_flags &= ~FL_DOWNGRADE_PENDING;
	पूर्ण
पूर्ण

/* We alपढ़ोy had a lease on this file; just change its type */
पूर्णांक lease_modअगरy(काष्ठा file_lock *fl, पूर्णांक arg, काष्ठा list_head *dispose)
अणु
	पूर्णांक error = assign_type(fl, arg);

	अगर (error)
		वापस error;
	lease_clear_pending(fl, arg);
	locks_wake_up_blocks(fl);
	अगर (arg == F_UNLCK) अणु
		काष्ठा file *filp = fl->fl_file;

		f_delown(filp);
		filp->f_owner.signum = 0;
		fasync_helper(0, fl->fl_file, 0, &fl->fl_fasync);
		अगर (fl->fl_fasync != शून्य) अणु
			prपूर्णांकk(KERN_ERR "locks_delete_lock: fasync == %p\n", fl->fl_fasync);
			fl->fl_fasync = शून्य;
		पूर्ण
		locks_delete_lock_ctx(fl, dispose);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(lease_modअगरy);

अटल bool past_समय(अचिन्हित दीर्घ then)
अणु
	अगर (!then)
		/* 0 is a special value meaning "this never expires": */
		वापस false;
	वापस समय_after(jअगरfies, then);
पूर्ण

अटल व्योम समय_out_leases(काष्ठा inode *inode, काष्ठा list_head *dispose)
अणु
	काष्ठा file_lock_context *ctx = inode->i_flctx;
	काष्ठा file_lock *fl, *पंचांगp;

	lockdep_निश्चित_held(&ctx->flc_lock);

	list_क्रम_each_entry_safe(fl, पंचांगp, &ctx->flc_lease, fl_list) अणु
		trace_समय_out_leases(inode, fl);
		अगर (past_समय(fl->fl_करोwngrade_समय))
			lease_modअगरy(fl, F_RDLCK, dispose);
		अगर (past_समय(fl->fl_अवरोध_समय))
			lease_modअगरy(fl, F_UNLCK, dispose);
	पूर्ण
पूर्ण

अटल bool leases_conflict(काष्ठा file_lock *lease, काष्ठा file_lock *अवरोधer)
अणु
	bool rc;

	अगर (lease->fl_lmops->lm_अवरोधer_owns_lease
			&& lease->fl_lmops->lm_अवरोधer_owns_lease(lease))
		वापस false;
	अगर ((अवरोधer->fl_flags & FL_LAYOUT) != (lease->fl_flags & FL_LAYOUT)) अणु
		rc = false;
		जाओ trace;
	पूर्ण
	अगर ((अवरोधer->fl_flags & FL_DELEG) && (lease->fl_flags & FL_LEASE)) अणु
		rc = false;
		जाओ trace;
	पूर्ण

	rc = locks_conflict(अवरोधer, lease);
trace:
	trace_leases_conflict(rc, lease, अवरोधer);
	वापस rc;
पूर्ण

अटल bool
any_leases_conflict(काष्ठा inode *inode, काष्ठा file_lock *अवरोधer)
अणु
	काष्ठा file_lock_context *ctx = inode->i_flctx;
	काष्ठा file_lock *fl;

	lockdep_निश्चित_held(&ctx->flc_lock);

	list_क्रम_each_entry(fl, &ctx->flc_lease, fl_list) अणु
		अगर (leases_conflict(fl, अवरोधer))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 *	__अवरोध_lease	-	revoke all outstanding leases on file
 *	@inode: the inode of the file to वापस
 *	@mode: O_RDONLY: अवरोध only ग_लिखो leases; O_WRONLY or O_RDWR:
 *	    अवरोध all leases
 *	@type: FL_LEASE: अवरोध leases and delegations; FL_DELEG: अवरोध
 *	    only delegations
 *
 *	अवरोध_lease (अंतरभूतd क्रम speed) has checked there alपढ़ोy is at least
 *	some kind of lock (maybe a lease) on this file.  Leases are broken on
 *	a call to खोलो() or truncate().  This function can sleep unless you
 *	specअगरied %O_NONBLOCK to your खोलो().
 */
पूर्णांक __अवरोध_lease(काष्ठा inode *inode, अचिन्हित पूर्णांक mode, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक error = 0;
	काष्ठा file_lock_context *ctx;
	काष्ठा file_lock *new_fl, *fl, *पंचांगp;
	अचिन्हित दीर्घ अवरोध_समय;
	पूर्णांक want_ग_लिखो = (mode & O_ACCMODE) != O_RDONLY;
	LIST_HEAD(dispose);

	new_fl = lease_alloc(शून्य, want_ग_लिखो ? F_WRLCK : F_RDLCK);
	अगर (IS_ERR(new_fl))
		वापस PTR_ERR(new_fl);
	new_fl->fl_flags = type;

	/* typically we will check that ctx is non-शून्य beक्रमe calling */
	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (!ctx) अणु
		WARN_ON_ONCE(1);
		जाओ मुक्त_lock;
	पूर्ण

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);

	समय_out_leases(inode, &dispose);

	अगर (!any_leases_conflict(inode, new_fl))
		जाओ out;

	अवरोध_समय = 0;
	अगर (lease_अवरोध_समय > 0) अणु
		अवरोध_समय = jअगरfies + lease_अवरोध_समय * HZ;
		अगर (अवरोध_समय == 0)
			अवरोध_समय++;	/* so that 0 means no अवरोध समय */
	पूर्ण

	list_क्रम_each_entry_safe(fl, पंचांगp, &ctx->flc_lease, fl_list) अणु
		अगर (!leases_conflict(fl, new_fl))
			जारी;
		अगर (want_ग_लिखो) अणु
			अगर (fl->fl_flags & FL_UNLOCK_PENDING)
				जारी;
			fl->fl_flags |= FL_UNLOCK_PENDING;
			fl->fl_अवरोध_समय = अवरोध_समय;
		पूर्ण अन्यथा अणु
			अगर (lease_अवरोधing(fl))
				जारी;
			fl->fl_flags |= FL_DOWNGRADE_PENDING;
			fl->fl_करोwngrade_समय = अवरोध_समय;
		पूर्ण
		अगर (fl->fl_lmops->lm_अवरोध(fl))
			locks_delete_lock_ctx(fl, &dispose);
	पूर्ण

	अगर (list_empty(&ctx->flc_lease))
		जाओ out;

	अगर (mode & O_NONBLOCK) अणु
		trace_अवरोध_lease_noblock(inode, new_fl);
		error = -EWOULDBLOCK;
		जाओ out;
	पूर्ण

restart:
	fl = list_first_entry(&ctx->flc_lease, काष्ठा file_lock, fl_list);
	अवरोध_समय = fl->fl_अवरोध_समय;
	अगर (अवरोध_समय != 0)
		अवरोध_समय -= jअगरfies;
	अगर (अवरोध_समय == 0)
		अवरोध_समय++;
	locks_insert_block(fl, new_fl, leases_conflict);
	trace_अवरोध_lease_block(inode, new_fl);
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);

	locks_dispose_list(&dispose);
	error = रुको_event_पूर्णांकerruptible_समयout(new_fl->fl_रुको,
					list_empty(&new_fl->fl_blocked_member),
					अवरोध_समय);

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);
	trace_अवरोध_lease_unblock(inode, new_fl);
	locks_delete_block(new_fl);
	अगर (error >= 0) अणु
		/*
		 * Wait क्रम the next conflicting lease that has not been
		 * broken yet
		 */
		अगर (error == 0)
			समय_out_leases(inode, &dispose);
		अगर (any_leases_conflict(inode, new_fl))
			जाओ restart;
		error = 0;
	पूर्ण
out:
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);
	locks_dispose_list(&dispose);
मुक्त_lock:
	locks_मुक्त_lock(new_fl);
	वापस error;
पूर्ण
EXPORT_SYMBOL(__अवरोध_lease);

/**
 *	lease_get_mसमय - update modअगरied समय of an inode with exclusive lease
 *	@inode: the inode
 *      @समय:  poपूर्णांकer to a बारpec which contains the last modअगरied समय
 *
 * This is to क्रमce NFS clients to flush their caches क्रम files with
 * exclusive leases.  The justअगरication is that अगर someone has an
 * exclusive lease, then they could be modअगरying it.
 */
व्योम lease_get_mसमय(काष्ठा inode *inode, काष्ठा बारpec64 *समय)
अणु
	bool has_lease = false;
	काष्ठा file_lock_context *ctx;
	काष्ठा file_lock *fl;

	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (ctx && !list_empty_careful(&ctx->flc_lease)) अणु
		spin_lock(&ctx->flc_lock);
		fl = list_first_entry_or_null(&ctx->flc_lease,
					      काष्ठा file_lock, fl_list);
		अगर (fl && (fl->fl_type == F_WRLCK))
			has_lease = true;
		spin_unlock(&ctx->flc_lock);
	पूर्ण

	अगर (has_lease)
		*समय = current_समय(inode);
पूर्ण
EXPORT_SYMBOL(lease_get_mसमय);

/**
 *	fcntl_getlease - Enquire what lease is currently active
 *	@filp: the file
 *
 *	The value वापसed by this function will be one of
 *	(अगर no lease अवरोध is pending):
 *
 *	%F_RDLCK to indicate a shared lease is held.
 *
 *	%F_WRLCK to indicate an exclusive lease is held.
 *
 *	%F_UNLCK to indicate no lease is held.
 *
 *	(अगर a lease अवरोध is pending):
 *
 *	%F_RDLCK to indicate an exclusive lease needs to be
 *		changed to a shared lease (or हटाओd).
 *
 *	%F_UNLCK to indicate the lease needs to be हटाओd.
 *
 *	XXX: sfr & willy disagree over whether F_INPROGRESS
 *	should be वापसed to userspace.
 */
पूर्णांक fcntl_getlease(काष्ठा file *filp)
अणु
	काष्ठा file_lock *fl;
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file_lock_context *ctx;
	पूर्णांक type = F_UNLCK;
	LIST_HEAD(dispose);

	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (ctx && !list_empty_careful(&ctx->flc_lease)) अणु
		percpu_करोwn_पढ़ो(&file_rwsem);
		spin_lock(&ctx->flc_lock);
		समय_out_leases(inode, &dispose);
		list_क्रम_each_entry(fl, &ctx->flc_lease, fl_list) अणु
			अगर (fl->fl_file != filp)
				जारी;
			type = target_leasetype(fl);
			अवरोध;
		पूर्ण
		spin_unlock(&ctx->flc_lock);
		percpu_up_पढ़ो(&file_rwsem);

		locks_dispose_list(&dispose);
	पूर्ण
	वापस type;
पूर्ण

/**
 * check_conflicting_खोलो - see अगर the given file poपूर्णांकs to an inode that has
 *			    an existing खोलो that would conflict with the
 *			    desired lease.
 * @filp:	file to check
 * @arg:	type of lease that we're trying to acquire
 * @flags:	current lock flags
 *
 * Check to see अगर there's an existing खोलो fd on this file that would
 * conflict with the lease we're trying to set.
 */
अटल पूर्णांक
check_conflicting_खोलो(काष्ठा file *filp, स्थिर दीर्घ arg, पूर्णांक flags)
अणु
	काष्ठा inode *inode = locks_inode(filp);
	पूर्णांक self_wcount = 0, self_rcount = 0;

	अगर (flags & FL_LAYOUT)
		वापस 0;
	अगर (flags & FL_DELEG)
		/* We leave these checks to the caller */
		वापस 0;

	अगर (arg == F_RDLCK)
		वापस inode_is_खोलो_क्रम_ग_लिखो(inode) ? -EAGAIN : 0;
	अन्यथा अगर (arg != F_WRLCK)
		वापस 0;

	/*
	 * Make sure that only पढ़ो/ग_लिखो count is from lease requestor.
	 * Note that this will result in denying ग_लिखो leases when i_ग_लिखोcount
	 * is negative, which is what we want.  (We shouldn't grant ग_लिखो leases
	 * on files खोलो क्रम execution.)
	 */
	अगर (filp->f_mode & FMODE_WRITE)
		self_wcount = 1;
	अन्यथा अगर (filp->f_mode & FMODE_READ)
		self_rcount = 1;

	अगर (atomic_पढ़ो(&inode->i_ग_लिखोcount) != self_wcount ||
	    atomic_पढ़ो(&inode->i_पढ़ोcount) != self_rcount)
		वापस -EAGAIN;

	वापस 0;
पूर्ण

अटल पूर्णांक
generic_add_lease(काष्ठा file *filp, दीर्घ arg, काष्ठा file_lock **flp, व्योम **priv)
अणु
	काष्ठा file_lock *fl, *my_fl = शून्य, *lease;
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file_lock_context *ctx;
	bool is_deleg = (*flp)->fl_flags & FL_DELEG;
	पूर्णांक error;
	LIST_HEAD(dispose);

	lease = *flp;
	trace_generic_add_lease(inode, lease);

	/* Note that arg is never F_UNLCK here */
	ctx = locks_get_lock_context(inode, arg);
	अगर (!ctx)
		वापस -ENOMEM;

	/*
	 * In the delegation हाल we need mutual exclusion with
	 * a number of operations that take the i_mutex.  We trylock
	 * because delegations are an optional optimization, and अगर
	 * there's some chance of a conflict--we'd rather not
	 * bother, maybe that's a sign this just isn't a good file to
	 * hand out a delegation on.
	 */
	अगर (is_deleg && !inode_trylock(inode))
		वापस -EAGAIN;

	अगर (is_deleg && arg == F_WRLCK) अणु
		/* Write delegations are not currently supported: */
		inode_unlock(inode);
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);
	समय_out_leases(inode, &dispose);
	error = check_conflicting_खोलो(filp, arg, lease->fl_flags);
	अगर (error)
		जाओ out;

	/*
	 * At this poपूर्णांक, we know that अगर there is an exclusive
	 * lease on this file, then we hold it on this filp
	 * (otherwise our खोलो of this file would have blocked).
	 * And अगर we are trying to acquire an exclusive lease,
	 * then the file is not खोलो by anyone (including us)
	 * except क्रम this filp.
	 */
	error = -EAGAIN;
	list_क्रम_each_entry(fl, &ctx->flc_lease, fl_list) अणु
		अगर (fl->fl_file == filp &&
		    fl->fl_owner == lease->fl_owner) अणु
			my_fl = fl;
			जारी;
		पूर्ण

		/*
		 * No exclusive leases अगर someone अन्यथा has a lease on
		 * this file:
		 */
		अगर (arg == F_WRLCK)
			जाओ out;
		/*
		 * Modअगरying our existing lease is OK, but no getting a
		 * new lease अगर someone अन्यथा is खोलोing क्रम ग_लिखो:
		 */
		अगर (fl->fl_flags & FL_UNLOCK_PENDING)
			जाओ out;
	पूर्ण

	अगर (my_fl != शून्य) अणु
		lease = my_fl;
		error = lease->fl_lmops->lm_change(lease, arg, &dispose);
		अगर (error)
			जाओ out;
		जाओ out_setup;
	पूर्ण

	error = -EINVAL;
	अगर (!leases_enable)
		जाओ out;

	locks_insert_lock_ctx(lease, &ctx->flc_lease);
	/*
	 * The check in अवरोध_lease() is lockless. It's possible क्रम another
	 * खोलो to race in after we did the earlier check क्रम a conflicting
	 * खोलो but beक्रमe the lease was inserted. Check again क्रम a
	 * conflicting खोलो and cancel the lease अगर there is one.
	 *
	 * We also add a barrier here to ensure that the insertion of the lock
	 * precedes these checks.
	 */
	smp_mb();
	error = check_conflicting_खोलो(filp, arg, lease->fl_flags);
	अगर (error) अणु
		locks_unlink_lock_ctx(lease);
		जाओ out;
	पूर्ण

out_setup:
	अगर (lease->fl_lmops->lm_setup)
		lease->fl_lmops->lm_setup(lease, priv);
out:
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);
	locks_dispose_list(&dispose);
	अगर (is_deleg)
		inode_unlock(inode);
	अगर (!error && !my_fl)
		*flp = शून्य;
	वापस error;
पूर्ण

अटल पूर्णांक generic_delete_lease(काष्ठा file *filp, व्योम *owner)
अणु
	पूर्णांक error = -EAGAIN;
	काष्ठा file_lock *fl, *victim = शून्य;
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file_lock_context *ctx;
	LIST_HEAD(dispose);

	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (!ctx) अणु
		trace_generic_delete_lease(inode, शून्य);
		वापस error;
	पूर्ण

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);
	list_क्रम_each_entry(fl, &ctx->flc_lease, fl_list) अणु
		अगर (fl->fl_file == filp &&
		    fl->fl_owner == owner) अणु
			victim = fl;
			अवरोध;
		पूर्ण
	पूर्ण
	trace_generic_delete_lease(inode, victim);
	अगर (victim)
		error = fl->fl_lmops->lm_change(victim, F_UNLCK, &dispose);
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);
	locks_dispose_list(&dispose);
	वापस error;
पूर्ण

/**
 *	generic_setlease	-	sets a lease on an खोलो file
 *	@filp:	file poपूर्णांकer
 *	@arg:	type of lease to obtain
 *	@flp:	input - file_lock to use, output - file_lock inserted
 *	@priv:	निजी data क्रम lm_setup (may be शून्य अगर lm_setup
 *		करोesn't require it)
 *
 *	The (input) flp->fl_lmops->lm_अवरोध function is required
 *	by अवरोध_lease().
 */
पूर्णांक generic_setlease(काष्ठा file *filp, दीर्घ arg, काष्ठा file_lock **flp,
			व्योम **priv)
अणु
	काष्ठा inode *inode = locks_inode(filp);
	पूर्णांक error;

	अगर ((!uid_eq(current_fsuid(), inode->i_uid)) && !capable(CAP_LEASE))
		वापस -EACCES;
	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;
	error = security_file_lock(filp, arg);
	अगर (error)
		वापस error;

	चयन (arg) अणु
	हाल F_UNLCK:
		वापस generic_delete_lease(filp, *priv);
	हाल F_RDLCK:
	हाल F_WRLCK:
		अगर (!(*flp)->fl_lmops->lm_अवरोध) अणु
			WARN_ON_ONCE(1);
			वापस -ENOLCK;
		पूर्ण

		वापस generic_add_lease(filp, arg, flp, priv);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(generic_setlease);

#अगर IS_ENABLED(CONFIG_SRCU)
/*
 * Kernel subप्रणालीs can रेजिस्टर to be notअगरied on any attempt to set
 * a new lease with the lease_notअगरier_chain. This is used by (e.g.) nfsd
 * to बंद files that it may have cached when there is an attempt to set a
 * conflicting lease.
 */
अटल काष्ठा srcu_notअगरier_head lease_notअगरier_chain;

अटल अंतरभूत व्योम
lease_notअगरier_chain_init(व्योम)
अणु
	srcu_init_notअगरier_head(&lease_notअगरier_chain);
पूर्ण

अटल अंतरभूत व्योम
setlease_notअगरier(दीर्घ arg, काष्ठा file_lock *lease)
अणु
	अगर (arg != F_UNLCK)
		srcu_notअगरier_call_chain(&lease_notअगरier_chain, arg, lease);
पूर्ण

पूर्णांक lease_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस srcu_notअगरier_chain_रेजिस्टर(&lease_notअगरier_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(lease_रेजिस्टर_notअगरier);

व्योम lease_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	srcu_notअगरier_chain_unरेजिस्टर(&lease_notअगरier_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(lease_unरेजिस्टर_notअगरier);

#अन्यथा /* !IS_ENABLED(CONFIG_SRCU) */
अटल अंतरभूत व्योम
lease_notअगरier_chain_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम
setlease_notअगरier(दीर्घ arg, काष्ठा file_lock *lease)
अणु
पूर्ण

पूर्णांक lease_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lease_रेजिस्टर_notअगरier);

व्योम lease_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(lease_unरेजिस्टर_notअगरier);

#पूर्ण_अगर /* IS_ENABLED(CONFIG_SRCU) */

/**
 * vfs_setlease        -       sets a lease on an खोलो file
 * @filp:	file poपूर्णांकer
 * @arg:	type of lease to obtain
 * @lease:	file_lock to use when adding a lease
 * @priv:	निजी info क्रम lm_setup when adding a lease (may be
 *		शून्य अगर lm_setup करोesn't require it)
 *
 * Call this to establish a lease on the file. The "lease" argument is not
 * used क्रम F_UNLCK requests and may be शून्य. For commands that set or alter
 * an existing lease, the ``(*lease)->fl_lmops->lm_अवरोध`` operation must be
 * set; अगर not, this function will वापस -ENOLCK (and generate a scary-looking
 * stack trace).
 *
 * The "priv" poपूर्णांकer is passed directly to the lm_setup function as-is. It
 * may be शून्य अगर the lm_setup operation करोesn't require it.
 */
पूर्णांक
vfs_setlease(काष्ठा file *filp, दीर्घ arg, काष्ठा file_lock **lease, व्योम **priv)
अणु
	अगर (lease)
		setlease_notअगरier(arg, *lease);
	अगर (filp->f_op->setlease)
		वापस filp->f_op->setlease(filp, arg, lease, priv);
	अन्यथा
		वापस generic_setlease(filp, arg, lease, priv);
पूर्ण
EXPORT_SYMBOL_GPL(vfs_setlease);

अटल पूर्णांक करो_fcntl_add_lease(अचिन्हित पूर्णांक fd, काष्ठा file *filp, दीर्घ arg)
अणु
	काष्ठा file_lock *fl;
	काष्ठा fasync_काष्ठा *new;
	पूर्णांक error;

	fl = lease_alloc(filp, arg);
	अगर (IS_ERR(fl))
		वापस PTR_ERR(fl);

	new = fasync_alloc();
	अगर (!new) अणु
		locks_मुक्त_lock(fl);
		वापस -ENOMEM;
	पूर्ण
	new->fa_fd = fd;

	error = vfs_setlease(filp, arg, &fl, (व्योम **)&new);
	अगर (fl)
		locks_मुक्त_lock(fl);
	अगर (new)
		fasync_मुक्त(new);
	वापस error;
पूर्ण

/**
 *	fcntl_setlease	-	sets a lease on an खोलो file
 *	@fd: खोलो file descriptor
 *	@filp: file poपूर्णांकer
 *	@arg: type of lease to obtain
 *
 *	Call this fcntl to establish a lease on the file.
 *	Note that you also need to call %F_SETSIG to
 *	receive a संकेत when the lease is broken.
 */
पूर्णांक fcntl_setlease(अचिन्हित पूर्णांक fd, काष्ठा file *filp, दीर्घ arg)
अणु
	अगर (arg == F_UNLCK)
		वापस vfs_setlease(filp, F_UNLCK, शून्य, (व्योम **)&filp);
	वापस करो_fcntl_add_lease(fd, filp, arg);
पूर्ण

/**
 * flock_lock_inode_रुको - Apply a FLOCK-style lock to a file
 * @inode: inode of the file to apply to
 * @fl: The lock to be applied
 *
 * Apply a FLOCK style lock request to an inode.
 */
अटल पूर्णांक flock_lock_inode_रुको(काष्ठा inode *inode, काष्ठा file_lock *fl)
अणु
	पूर्णांक error;
	might_sleep();
	क्रम (;;) अणु
		error = flock_lock_inode(inode, fl);
		अगर (error != खाता_LOCK_DEFERRED)
			अवरोध;
		error = रुको_event_पूर्णांकerruptible(fl->fl_रुको,
				list_empty(&fl->fl_blocked_member));
		अगर (error)
			अवरोध;
	पूर्ण
	locks_delete_block(fl);
	वापस error;
पूर्ण

/**
 * locks_lock_inode_रुको - Apply a lock to an inode
 * @inode: inode of the file to apply to
 * @fl: The lock to be applied
 *
 * Apply a POSIX or FLOCK style lock request to an inode.
 */
पूर्णांक locks_lock_inode_रुको(काष्ठा inode *inode, काष्ठा file_lock *fl)
अणु
	पूर्णांक res = 0;
	चयन (fl->fl_flags & (FL_POSIX|FL_FLOCK)) अणु
		हाल FL_POSIX:
			res = posix_lock_inode_रुको(inode, fl);
			अवरोध;
		हाल FL_FLOCK:
			res = flock_lock_inode_रुको(inode, fl);
			अवरोध;
		शेष:
			BUG();
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(locks_lock_inode_रुको);

/**
 *	sys_flock: - flock() प्रणाली call.
 *	@fd: the file descriptor to lock.
 *	@cmd: the type of lock to apply.
 *
 *	Apply a %FL_FLOCK style lock to an खोलो file descriptor.
 *	The @cmd can be one of:
 *
 *	- %LOCK_SH -- a shared lock.
 *	- %LOCK_EX -- an exclusive lock.
 *	- %LOCK_UN -- हटाओ an existing lock.
 *	- %LOCK_MAND -- a 'mandatory' flock.
 *	  This exists to emulate Winकरोws Share Modes.
 *
 *	%LOCK_MAND can be combined with %LOCK_READ or %LOCK_WRITE to allow other
 *	processes पढ़ो and ग_लिखो access respectively.
 */
SYSCALL_DEFINE2(flock, अचिन्हित पूर्णांक, fd, अचिन्हित पूर्णांक, cmd)
अणु
	काष्ठा fd f = fdget(fd);
	काष्ठा file_lock *lock;
	पूर्णांक can_sleep, unlock;
	पूर्णांक error;

	error = -EBADF;
	अगर (!f.file)
		जाओ out;

	can_sleep = !(cmd & LOCK_NB);
	cmd &= ~LOCK_NB;
	unlock = (cmd == LOCK_UN);

	अगर (!unlock && !(cmd & LOCK_MAND) &&
	    !(f.file->f_mode & (FMODE_READ|FMODE_WRITE)))
		जाओ out_putf;

	lock = flock_make_lock(f.file, cmd, शून्य);
	अगर (IS_ERR(lock)) अणु
		error = PTR_ERR(lock);
		जाओ out_putf;
	पूर्ण

	अगर (can_sleep)
		lock->fl_flags |= FL_SLEEP;

	error = security_file_lock(f.file, lock->fl_type);
	अगर (error)
		जाओ out_मुक्त;

	अगर (f.file->f_op->flock)
		error = f.file->f_op->flock(f.file,
					  (can_sleep) ? F_SETLKW : F_SETLK,
					  lock);
	अन्यथा
		error = locks_lock_file_रुको(f.file, lock);

 out_मुक्त:
	locks_मुक्त_lock(lock);

 out_putf:
	fdput(f);
 out:
	वापस error;
पूर्ण

/**
 * vfs_test_lock - test file byte range lock
 * @filp: The file to test lock क्रम
 * @fl: The lock to test; also used to hold result
 *
 * Returns -ERRNO on failure.  Indicates presence of conflicting lock by
 * setting conf->fl_type to something other than F_UNLCK.
 */
पूर्णांक vfs_test_lock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	अगर (filp->f_op->lock)
		वापस filp->f_op->lock(filp, F_GETLK, fl);
	posix_test_lock(filp, fl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_test_lock);

/**
 * locks_translate_pid - translate a file_lock's fl_pid number पूर्णांकo a namespace
 * @fl: The file_lock who's fl_pid should be translated
 * @ns: The namespace पूर्णांकo which the pid should be translated
 *
 * Used to tranlate a fl_pid पूर्णांकo a namespace भव pid number
 */
अटल pid_t locks_translate_pid(काष्ठा file_lock *fl, काष्ठा pid_namespace *ns)
अणु
	pid_t vnr;
	काष्ठा pid *pid;

	अगर (IS_OFDLCK(fl))
		वापस -1;
	अगर (IS_REMOTELCK(fl))
		वापस fl->fl_pid;
	/*
	 * If the flock owner process is dead and its pid has been alपढ़ोy
	 * मुक्तd, the translation below won't work, but we still want to show
	 * flock owner pid number in init pidns.
	 */
	अगर (ns == &init_pid_ns)
		वापस (pid_t)fl->fl_pid;

	rcu_पढ़ो_lock();
	pid = find_pid_ns(fl->fl_pid, &init_pid_ns);
	vnr = pid_nr_ns(pid, ns);
	rcu_पढ़ो_unlock();
	वापस vnr;
पूर्ण

अटल पूर्णांक posix_lock_to_flock(काष्ठा flock *flock, काष्ठा file_lock *fl)
अणु
	flock->l_pid = locks_translate_pid(fl, task_active_pid_ns(current));
#अगर BITS_PER_LONG == 32
	/*
	 * Make sure we can represent the posix lock via
	 * legacy 32bit flock.
	 */
	अगर (fl->fl_start > OFFT_OFFSET_MAX)
		वापस -EOVERFLOW;
	अगर (fl->fl_end != OFFSET_MAX && fl->fl_end > OFFT_OFFSET_MAX)
		वापस -EOVERFLOW;
#पूर्ण_अगर
	flock->l_start = fl->fl_start;
	flock->l_len = fl->fl_end == OFFSET_MAX ? 0 :
		fl->fl_end - fl->fl_start + 1;
	flock->l_whence = 0;
	flock->l_type = fl->fl_type;
	वापस 0;
पूर्ण

#अगर BITS_PER_LONG == 32
अटल व्योम posix_lock_to_flock64(काष्ठा flock64 *flock, काष्ठा file_lock *fl)
अणु
	flock->l_pid = locks_translate_pid(fl, task_active_pid_ns(current));
	flock->l_start = fl->fl_start;
	flock->l_len = fl->fl_end == OFFSET_MAX ? 0 :
		fl->fl_end - fl->fl_start + 1;
	flock->l_whence = 0;
	flock->l_type = fl->fl_type;
पूर्ण
#पूर्ण_अगर

/* Report the first existing lock that would conflict with l.
 * This implements the F_GETLK command of fcntl().
 */
पूर्णांक fcntl_getlk(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, काष्ठा flock *flock)
अणु
	काष्ठा file_lock *fl;
	पूर्णांक error;

	fl = locks_alloc_lock();
	अगर (fl == शून्य)
		वापस -ENOMEM;
	error = -EINVAL;
	अगर (flock->l_type != F_RDLCK && flock->l_type != F_WRLCK)
		जाओ out;

	error = flock_to_posix_lock(filp, fl, flock);
	अगर (error)
		जाओ out;

	अगर (cmd == F_OFD_GETLK) अणु
		error = -EINVAL;
		अगर (flock->l_pid != 0)
			जाओ out;

		fl->fl_flags |= FL_OFDLCK;
		fl->fl_owner = filp;
	पूर्ण

	error = vfs_test_lock(filp, fl);
	अगर (error)
		जाओ out;

	flock->l_type = fl->fl_type;
	अगर (fl->fl_type != F_UNLCK) अणु
		error = posix_lock_to_flock(flock, fl);
		अगर (error)
			जाओ out;
	पूर्ण
out:
	locks_मुक्त_lock(fl);
	वापस error;
पूर्ण

/**
 * vfs_lock_file - file byte range lock
 * @filp: The file to apply the lock to
 * @cmd: type of locking operation (F_SETLK, F_GETLK, etc.)
 * @fl: The lock to be applied
 * @conf: Place to वापस a copy of the conflicting lock, अगर found.
 *
 * A caller that करोesn't care about the conflicting lock may pass शून्य
 * as the final argument.
 *
 * If the fileप्रणाली defines a निजी ->lock() method, then @conf will
 * be left unchanged; so a caller that cares should initialize it to
 * some acceptable शेष.
 *
 * To aव्योम blocking kernel daemons, such as lockd, that need to acquire POSIX
 * locks, the ->lock() पूर्णांकerface may वापस asynchronously, beक्रमe the lock has
 * been granted or denied by the underlying fileप्रणाली, अगर (and only अगर)
 * lm_grant is set. Callers expecting ->lock() to वापस asynchronously
 * will only use F_SETLK, not F_SETLKW; they will set FL_SLEEP अगर (and only अगर)
 * the request is क्रम a blocking lock. When ->lock() करोes वापस asynchronously,
 * it must वापस खाता_LOCK_DEFERRED, and call ->lm_grant() when the lock
 * request completes.
 * If the request is क्रम non-blocking lock the file प्रणाली should वापस
 * खाता_LOCK_DEFERRED then try to get the lock and call the callback routine
 * with the result. If the request समयd out the callback routine will वापस a
 * nonzero वापस code and the file प्रणाली should release the lock. The file
 * प्रणाली is also responsible to keep a corresponding posix lock when it
 * grants a lock so the VFS can find out which locks are locally held and करो
 * the correct lock cleanup when required.
 * The underlying fileप्रणाली must not drop the kernel lock or call
 * ->lm_grant() beक्रमe वापसing to the caller with a खाता_LOCK_DEFERRED
 * वापस code.
 */
पूर्णांक vfs_lock_file(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, काष्ठा file_lock *fl, काष्ठा file_lock *conf)
अणु
	अगर (filp->f_op->lock)
		वापस filp->f_op->lock(filp, cmd, fl);
	अन्यथा
		वापस posix_lock_file(filp, fl, conf);
पूर्ण
EXPORT_SYMBOL_GPL(vfs_lock_file);

अटल पूर्णांक करो_lock_file_रुको(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			     काष्ठा file_lock *fl)
अणु
	पूर्णांक error;

	error = security_file_lock(filp, fl->fl_type);
	अगर (error)
		वापस error;

	क्रम (;;) अणु
		error = vfs_lock_file(filp, cmd, fl, शून्य);
		अगर (error != खाता_LOCK_DEFERRED)
			अवरोध;
		error = रुको_event_पूर्णांकerruptible(fl->fl_रुको,
					list_empty(&fl->fl_blocked_member));
		अगर (error)
			अवरोध;
	पूर्ण
	locks_delete_block(fl);

	वापस error;
पूर्ण

/* Ensure that fl->fl_file has compatible f_mode क्रम F_SETLK calls */
अटल पूर्णांक
check_भ_शेषe_क्रम_setlk(काष्ठा file_lock *fl)
अणु
	चयन (fl->fl_type) अणु
	हाल F_RDLCK:
		अगर (!(fl->fl_file->f_mode & FMODE_READ))
			वापस -EBADF;
		अवरोध;
	हाल F_WRLCK:
		अगर (!(fl->fl_file->f_mode & FMODE_WRITE))
			वापस -EBADF;
	पूर्ण
	वापस 0;
पूर्ण

/* Apply the lock described by l to an खोलो file descriptor.
 * This implements both the F_SETLK and F_SETLKW commands of fcntl().
 */
पूर्णांक fcntl_setlk(अचिन्हित पूर्णांक fd, काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
		काष्ठा flock *flock)
अणु
	काष्ठा file_lock *file_lock = locks_alloc_lock();
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file *f;
	पूर्णांक error;

	अगर (file_lock == शून्य)
		वापस -ENOLCK;

	/* Don't allow mandatory locks on files that may be memory mapped
	 * and shared.
	 */
	अगर (mandatory_lock(inode) && mapping_writably_mapped(filp->f_mapping)) अणु
		error = -EAGAIN;
		जाओ out;
	पूर्ण

	error = flock_to_posix_lock(filp, file_lock, flock);
	अगर (error)
		जाओ out;

	error = check_भ_शेषe_क्रम_setlk(file_lock);
	अगर (error)
		जाओ out;

	/*
	 * If the cmd is requesting file-निजी locks, then set the
	 * FL_OFDLCK flag and override the owner.
	 */
	चयन (cmd) अणु
	हाल F_OFD_SETLK:
		error = -EINVAL;
		अगर (flock->l_pid != 0)
			जाओ out;

		cmd = F_SETLK;
		file_lock->fl_flags |= FL_OFDLCK;
		file_lock->fl_owner = filp;
		अवरोध;
	हाल F_OFD_SETLKW:
		error = -EINVAL;
		अगर (flock->l_pid != 0)
			जाओ out;

		cmd = F_SETLKW;
		file_lock->fl_flags |= FL_OFDLCK;
		file_lock->fl_owner = filp;
		fallthrough;
	हाल F_SETLKW:
		file_lock->fl_flags |= FL_SLEEP;
	पूर्ण

	error = करो_lock_file_रुको(filp, cmd, file_lock);

	/*
	 * Attempt to detect a बंद/fcntl race and recover by releasing the
	 * lock that was just acquired. There is no need to करो that when we're
	 * unlocking though, or क्रम OFD locks.
	 */
	अगर (!error && file_lock->fl_type != F_UNLCK &&
	    !(file_lock->fl_flags & FL_OFDLCK)) अणु
		काष्ठा files_काष्ठा *files = current->files;
		/*
		 * We need that spin_lock here - it prevents reordering between
		 * update of i_flctx->flc_posix and check क्रम it करोne in
		 * बंद(). rcu_पढ़ो_lock() wouldn't करो.
		 */
		spin_lock(&files->file_lock);
		f = files_lookup_fd_locked(files, fd);
		spin_unlock(&files->file_lock);
		अगर (f != filp) अणु
			file_lock->fl_type = F_UNLCK;
			error = करो_lock_file_रुको(filp, cmd, file_lock);
			WARN_ON_ONCE(error);
			error = -EBADF;
		पूर्ण
	पूर्ण
out:
	trace_fcntl_setlk(inode, file_lock, error);
	locks_मुक्त_lock(file_lock);
	वापस error;
पूर्ण

#अगर BITS_PER_LONG == 32
/* Report the first existing lock that would conflict with l.
 * This implements the F_GETLK command of fcntl().
 */
पूर्णांक fcntl_getlk64(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, काष्ठा flock64 *flock)
अणु
	काष्ठा file_lock *fl;
	पूर्णांक error;

	fl = locks_alloc_lock();
	अगर (fl == शून्य)
		वापस -ENOMEM;

	error = -EINVAL;
	अगर (flock->l_type != F_RDLCK && flock->l_type != F_WRLCK)
		जाओ out;

	error = flock64_to_posix_lock(filp, fl, flock);
	अगर (error)
		जाओ out;

	अगर (cmd == F_OFD_GETLK) अणु
		error = -EINVAL;
		अगर (flock->l_pid != 0)
			जाओ out;

		cmd = F_GETLK64;
		fl->fl_flags |= FL_OFDLCK;
		fl->fl_owner = filp;
	पूर्ण

	error = vfs_test_lock(filp, fl);
	अगर (error)
		जाओ out;

	flock->l_type = fl->fl_type;
	अगर (fl->fl_type != F_UNLCK)
		posix_lock_to_flock64(flock, fl);

out:
	locks_मुक्त_lock(fl);
	वापस error;
पूर्ण

/* Apply the lock described by l to an खोलो file descriptor.
 * This implements both the F_SETLK and F_SETLKW commands of fcntl().
 */
पूर्णांक fcntl_setlk64(अचिन्हित पूर्णांक fd, काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
		काष्ठा flock64 *flock)
अणु
	काष्ठा file_lock *file_lock = locks_alloc_lock();
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file *f;
	पूर्णांक error;

	अगर (file_lock == शून्य)
		वापस -ENOLCK;

	/* Don't allow mandatory locks on files that may be memory mapped
	 * and shared.
	 */
	अगर (mandatory_lock(inode) && mapping_writably_mapped(filp->f_mapping)) अणु
		error = -EAGAIN;
		जाओ out;
	पूर्ण

	error = flock64_to_posix_lock(filp, file_lock, flock);
	अगर (error)
		जाओ out;

	error = check_भ_शेषe_क्रम_setlk(file_lock);
	अगर (error)
		जाओ out;

	/*
	 * If the cmd is requesting file-निजी locks, then set the
	 * FL_OFDLCK flag and override the owner.
	 */
	चयन (cmd) अणु
	हाल F_OFD_SETLK:
		error = -EINVAL;
		अगर (flock->l_pid != 0)
			जाओ out;

		cmd = F_SETLK64;
		file_lock->fl_flags |= FL_OFDLCK;
		file_lock->fl_owner = filp;
		अवरोध;
	हाल F_OFD_SETLKW:
		error = -EINVAL;
		अगर (flock->l_pid != 0)
			जाओ out;

		cmd = F_SETLKW64;
		file_lock->fl_flags |= FL_OFDLCK;
		file_lock->fl_owner = filp;
		fallthrough;
	हाल F_SETLKW64:
		file_lock->fl_flags |= FL_SLEEP;
	पूर्ण

	error = करो_lock_file_रुको(filp, cmd, file_lock);

	/*
	 * Attempt to detect a बंद/fcntl race and recover by releasing the
	 * lock that was just acquired. There is no need to करो that when we're
	 * unlocking though, or क्रम OFD locks.
	 */
	अगर (!error && file_lock->fl_type != F_UNLCK &&
	    !(file_lock->fl_flags & FL_OFDLCK)) अणु
		काष्ठा files_काष्ठा *files = current->files;
		/*
		 * We need that spin_lock here - it prevents reordering between
		 * update of i_flctx->flc_posix and check क्रम it करोne in
		 * बंद(). rcu_पढ़ो_lock() wouldn't करो.
		 */
		spin_lock(&files->file_lock);
		f = files_lookup_fd_locked(files, fd);
		spin_unlock(&files->file_lock);
		अगर (f != filp) अणु
			file_lock->fl_type = F_UNLCK;
			error = करो_lock_file_रुको(filp, cmd, file_lock);
			WARN_ON_ONCE(error);
			error = -EBADF;
		पूर्ण
	पूर्ण
out:
	locks_मुक्त_lock(file_lock);
	वापस error;
पूर्ण
#पूर्ण_अगर /* BITS_PER_LONG == 32 */

/*
 * This function is called when the file is being हटाओd
 * from the task's fd array.  POSIX locks beदीर्घing to this task
 * are deleted at this समय.
 */
व्योम locks_हटाओ_posix(काष्ठा file *filp, fl_owner_t owner)
अणु
	पूर्णांक error;
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file_lock lock;
	काष्ठा file_lock_context *ctx;

	/*
	 * If there are no locks held on this file, we करोn't need to call
	 * posix_lock_file().  Another process could be setting a lock on this
	 * file at the same समय, but we wouldn't हटाओ that lock anyway.
	 */
	ctx =  smp_load_acquire(&inode->i_flctx);
	अगर (!ctx || list_empty(&ctx->flc_posix))
		वापस;

	locks_init_lock(&lock);
	lock.fl_type = F_UNLCK;
	lock.fl_flags = FL_POSIX | FL_CLOSE;
	lock.fl_start = 0;
	lock.fl_end = OFFSET_MAX;
	lock.fl_owner = owner;
	lock.fl_pid = current->tgid;
	lock.fl_file = filp;
	lock.fl_ops = शून्य;
	lock.fl_lmops = शून्य;

	error = vfs_lock_file(filp, F_SETLK, &lock, शून्य);

	अगर (lock.fl_ops && lock.fl_ops->fl_release_निजी)
		lock.fl_ops->fl_release_निजी(&lock);
	trace_locks_हटाओ_posix(inode, &lock, error);
पूर्ण
EXPORT_SYMBOL(locks_हटाओ_posix);

/* The i_flctx must be valid when calling पूर्णांकo here */
अटल व्योम
locks_हटाओ_flock(काष्ठा file *filp, काष्ठा file_lock_context *flctx)
अणु
	काष्ठा file_lock fl;
	काष्ठा inode *inode = locks_inode(filp);

	अगर (list_empty(&flctx->flc_flock))
		वापस;

	flock_make_lock(filp, LOCK_UN, &fl);
	fl.fl_flags |= FL_CLOSE;

	अगर (filp->f_op->flock)
		filp->f_op->flock(filp, F_SETLKW, &fl);
	अन्यथा
		flock_lock_inode(inode, &fl);

	अगर (fl.fl_ops && fl.fl_ops->fl_release_निजी)
		fl.fl_ops->fl_release_निजी(&fl);
पूर्ण

/* The i_flctx must be valid when calling पूर्णांकo here */
अटल व्योम
locks_हटाओ_lease(काष्ठा file *filp, काष्ठा file_lock_context *ctx)
अणु
	काष्ठा file_lock *fl, *पंचांगp;
	LIST_HEAD(dispose);

	अगर (list_empty(&ctx->flc_lease))
		वापस;

	percpu_करोwn_पढ़ो(&file_rwsem);
	spin_lock(&ctx->flc_lock);
	list_क्रम_each_entry_safe(fl, पंचांगp, &ctx->flc_lease, fl_list)
		अगर (filp == fl->fl_file)
			lease_modअगरy(fl, F_UNLCK, &dispose);
	spin_unlock(&ctx->flc_lock);
	percpu_up_पढ़ो(&file_rwsem);

	locks_dispose_list(&dispose);
पूर्ण

/*
 * This function is called on the last बंद of an खोलो file.
 */
व्योम locks_हटाओ_file(काष्ठा file *filp)
अणु
	काष्ठा file_lock_context *ctx;

	ctx = smp_load_acquire(&locks_inode(filp)->i_flctx);
	अगर (!ctx)
		वापस;

	/* हटाओ any OFD locks */
	locks_हटाओ_posix(filp, filp);

	/* हटाओ flock locks */
	locks_हटाओ_flock(filp, ctx);

	/* हटाओ any leases */
	locks_हटाओ_lease(filp, ctx);

	spin_lock(&ctx->flc_lock);
	locks_check_ctx_file_list(filp, &ctx->flc_posix, "POSIX");
	locks_check_ctx_file_list(filp, &ctx->flc_flock, "FLOCK");
	locks_check_ctx_file_list(filp, &ctx->flc_lease, "LEASE");
	spin_unlock(&ctx->flc_lock);
पूर्ण

/**
 * vfs_cancel_lock - file byte range unblock lock
 * @filp: The file to apply the unblock to
 * @fl: The lock to be unblocked
 *
 * Used by lock managers to cancel blocked requests
 */
पूर्णांक vfs_cancel_lock(काष्ठा file *filp, काष्ठा file_lock *fl)
अणु
	अगर (filp->f_op->lock)
		वापस filp->f_op->lock(filp, F_CANCELLK, fl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_cancel_lock);

#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>

काष्ठा locks_iterator अणु
	पूर्णांक	li_cpu;
	loff_t	li_pos;
पूर्ण;

अटल व्योम lock_get_status(काष्ठा seq_file *f, काष्ठा file_lock *fl,
			    loff_t id, अक्षर *pfx, पूर्णांक repeat)
अणु
	काष्ठा inode *inode = शून्य;
	अचिन्हित पूर्णांक fl_pid;
	काष्ठा pid_namespace *proc_pidns = proc_pid_ns(file_inode(f->file)->i_sb);

	fl_pid = locks_translate_pid(fl, proc_pidns);
	/*
	 * If lock owner is dead (and pid is मुक्तd) or not visible in current
	 * pidns, zero is shown as a pid value. Check lock info from
	 * init_pid_ns to get saved lock pid value.
	 */

	अगर (fl->fl_file != शून्य)
		inode = locks_inode(fl->fl_file);

	seq_म_लिखो(f, "%lld: ", id);

	अगर (repeat)
		seq_म_लिखो(f, "%*s", repeat - 1 + (पूर्णांक)म_माप(pfx), pfx);

	अगर (IS_POSIX(fl)) अणु
		अगर (fl->fl_flags & FL_ACCESS)
			seq_माला_दो(f, "ACCESS");
		अन्यथा अगर (IS_OFDLCK(fl))
			seq_माला_दो(f, "OFDLCK");
		अन्यथा
			seq_माला_दो(f, "POSIX ");

		seq_म_लिखो(f, " %s ",
			     (inode == शून्य) ? "*NOINODE*" :
			     mandatory_lock(inode) ? "MANDATORY" : "ADVISORY ");
	पूर्ण अन्यथा अगर (IS_FLOCK(fl)) अणु
		अगर (fl->fl_type & LOCK_MAND) अणु
			seq_माला_दो(f, "FLOCK  MSNFS     ");
		पूर्ण अन्यथा अणु
			seq_माला_दो(f, "FLOCK  ADVISORY  ");
		पूर्ण
	पूर्ण अन्यथा अगर (IS_LEASE(fl)) अणु
		अगर (fl->fl_flags & FL_DELEG)
			seq_माला_दो(f, "DELEG  ");
		अन्यथा
			seq_माला_दो(f, "LEASE  ");

		अगर (lease_अवरोधing(fl))
			seq_माला_दो(f, "BREAKING  ");
		अन्यथा अगर (fl->fl_file)
			seq_माला_दो(f, "ACTIVE    ");
		अन्यथा
			seq_माला_दो(f, "BREAKER   ");
	पूर्ण अन्यथा अणु
		seq_माला_दो(f, "UNKNOWN UNKNOWN  ");
	पूर्ण
	अगर (fl->fl_type & LOCK_MAND) अणु
		seq_म_लिखो(f, "%s ",
			       (fl->fl_type & LOCK_READ)
			       ? (fl->fl_type & LOCK_WRITE) ? "RW   " : "READ "
			       : (fl->fl_type & LOCK_WRITE) ? "WRITE" : "NONE ");
	पूर्ण अन्यथा अणु
		पूर्णांक type = IS_LEASE(fl) ? target_leasetype(fl) : fl->fl_type;

		seq_म_लिखो(f, "%s ", (type == F_WRLCK) ? "WRITE" :
				     (type == F_RDLCK) ? "READ" : "UNLCK");
	पूर्ण
	अगर (inode) अणु
		/* userspace relies on this representation of dev_t */
		seq_म_लिखो(f, "%d %02x:%02x:%lu ", fl_pid,
				MAJOR(inode->i_sb->s_dev),
				MINOR(inode->i_sb->s_dev), inode->i_ino);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(f, "%d <none>:0 ", fl_pid);
	पूर्ण
	अगर (IS_POSIX(fl)) अणु
		अगर (fl->fl_end == OFFSET_MAX)
			seq_म_लिखो(f, "%Ld EOF\n", fl->fl_start);
		अन्यथा
			seq_म_लिखो(f, "%Ld %Ld\n", fl->fl_start, fl->fl_end);
	पूर्ण अन्यथा अणु
		seq_माला_दो(f, "0 EOF\n");
	पूर्ण
पूर्ण

अटल काष्ठा file_lock *get_next_blocked_member(काष्ठा file_lock *node)
अणु
	काष्ठा file_lock *पंचांगp;

	/* शून्य node or root node */
	अगर (node == शून्य || node->fl_blocker == शून्य)
		वापस शून्य;

	/* Next member in the linked list could be itself */
	पंचांगp = list_next_entry(node, fl_blocked_member);
	अगर (list_entry_is_head(पंचांगp, &node->fl_blocker->fl_blocked_requests, fl_blocked_member)
		|| पंचांगp == node) अणु
		वापस शून्य;
	पूर्ण

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक locks_show(काष्ठा seq_file *f, व्योम *v)
अणु
	काष्ठा locks_iterator *iter = f->निजी;
	काष्ठा file_lock *cur, *पंचांगp;
	काष्ठा pid_namespace *proc_pidns = proc_pid_ns(file_inode(f->file)->i_sb);
	पूर्णांक level = 0;

	cur = hlist_entry(v, काष्ठा file_lock, fl_link);

	अगर (locks_translate_pid(cur, proc_pidns) == 0)
		वापस 0;

	/* View this crossed linked list as a binary tree, the first member of fl_blocked_requests
	 * is the left child of current node, the next silibing in fl_blocked_member is the
	 * right child, we can alse get the parent of current node from fl_blocker, so this
	 * question becomes traversal of a binary tree
	 */
	जबतक (cur != शून्य) अणु
		अगर (level)
			lock_get_status(f, cur, iter->li_pos, "-> ", level);
		अन्यथा
			lock_get_status(f, cur, iter->li_pos, "", level);

		अगर (!list_empty(&cur->fl_blocked_requests)) अणु
			/* Turn left */
			cur = list_first_entry_or_null(&cur->fl_blocked_requests,
				काष्ठा file_lock, fl_blocked_member);
			level++;
		पूर्ण अन्यथा अणु
			/* Turn right */
			पंचांगp = get_next_blocked_member(cur);
			/* Fall back to parent node */
			जबतक (पंचांगp == शून्य && cur->fl_blocker != शून्य) अणु
				cur = cur->fl_blocker;
				level--;
				पंचांगp = get_next_blocked_member(cur);
			पूर्ण
			cur = पंचांगp;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __show_fd_locks(काष्ठा seq_file *f,
			काष्ठा list_head *head, पूर्णांक *id,
			काष्ठा file *filp, काष्ठा files_काष्ठा *files)
अणु
	काष्ठा file_lock *fl;

	list_क्रम_each_entry(fl, head, fl_list) अणु

		अगर (filp != fl->fl_file)
			जारी;
		अगर (fl->fl_owner != files &&
		    fl->fl_owner != filp)
			जारी;

		(*id)++;
		seq_माला_दो(f, "lock:\t");
		lock_get_status(f, fl, *id, "", 0);
	पूर्ण
पूर्ण

व्योम show_fd_locks(काष्ठा seq_file *f,
		  काष्ठा file *filp, काष्ठा files_काष्ठा *files)
अणु
	काष्ठा inode *inode = locks_inode(filp);
	काष्ठा file_lock_context *ctx;
	पूर्णांक id = 0;

	ctx = smp_load_acquire(&inode->i_flctx);
	अगर (!ctx)
		वापस;

	spin_lock(&ctx->flc_lock);
	__show_fd_locks(f, &ctx->flc_flock, &id, filp, files);
	__show_fd_locks(f, &ctx->flc_posix, &id, filp, files);
	__show_fd_locks(f, &ctx->flc_lease, &id, filp, files);
	spin_unlock(&ctx->flc_lock);
पूर्ण

अटल व्योम *locks_start(काष्ठा seq_file *f, loff_t *pos)
	__acquires(&blocked_lock_lock)
अणु
	काष्ठा locks_iterator *iter = f->निजी;

	iter->li_pos = *pos + 1;
	percpu_करोwn_ग_लिखो(&file_rwsem);
	spin_lock(&blocked_lock_lock);
	वापस seq_hlist_start_percpu(&file_lock_list.hlist, &iter->li_cpu, *pos);
पूर्ण

अटल व्योम *locks_next(काष्ठा seq_file *f, व्योम *v, loff_t *pos)
अणु
	काष्ठा locks_iterator *iter = f->निजी;

	++iter->li_pos;
	वापस seq_hlist_next_percpu(v, &file_lock_list.hlist, &iter->li_cpu, pos);
पूर्ण

अटल व्योम locks_stop(काष्ठा seq_file *f, व्योम *v)
	__releases(&blocked_lock_lock)
अणु
	spin_unlock(&blocked_lock_lock);
	percpu_up_ग_लिखो(&file_rwsem);
पूर्ण

अटल स्थिर काष्ठा seq_operations locks_seq_operations = अणु
	.start	= locks_start,
	.next	= locks_next,
	.stop	= locks_stop,
	.show	= locks_show,
पूर्ण;

अटल पूर्णांक __init proc_locks_init(व्योम)
अणु
	proc_create_seq_निजी("locks", 0, शून्य, &locks_seq_operations,
			माप(काष्ठा locks_iterator), शून्य);
	वापस 0;
पूर्ण
fs_initcall(proc_locks_init);
#पूर्ण_अगर

अटल पूर्णांक __init filelock_init(व्योम)
अणु
	पूर्णांक i;

	flctx_cache = kmem_cache_create("file_lock_ctx",
			माप(काष्ठा file_lock_context), 0, SLAB_PANIC, शून्य);

	filelock_cache = kmem_cache_create("file_lock_cache",
			माप(काष्ठा file_lock), 0, SLAB_PANIC, शून्य);

	क्रम_each_possible_cpu(i) अणु
		काष्ठा file_lock_list_काष्ठा *fll = per_cpu_ptr(&file_lock_list, i);

		spin_lock_init(&fll->lock);
		INIT_HLIST_HEAD(&fll->hlist);
	पूर्ण

	lease_notअगरier_chain_init();
	वापस 0;
पूर्ण
core_initcall(filelock_init);
