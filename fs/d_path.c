<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/prefetch.h>
#समावेश "mount.h"

अटल पूर्णांक prepend(अक्षर **buffer, पूर्णांक *buflen, स्थिर अक्षर *str, पूर्णांक namelen)
अणु
	*buflen -= namelen;
	अगर (*buflen < 0)
		वापस -ENAMETOOLONG;
	*buffer -= namelen;
	स_नकल(*buffer, str, namelen);
	वापस 0;
पूर्ण

/**
 * prepend_name - prepend a pathname in front of current buffer poपूर्णांकer
 * @buffer: buffer poपूर्णांकer
 * @buflen: allocated length of the buffer
 * @name:   name string and length qstr काष्ठाure
 *
 * With RCU path tracing, it may race with d_move(). Use READ_ONCE() to
 * make sure that either the old or the new name poपूर्णांकer and length are
 * fetched. However, there may be mismatch between length and poपूर्णांकer.
 * The length cannot be trusted, we need to copy it byte-by-byte until
 * the length is reached or a null byte is found. It also prepends "/" at
 * the beginning of the name. The sequence number check at the caller will
 * retry it again when a d_move() करोes happen. So any garbage in the buffer
 * due to mismatched poपूर्णांकer and length will be discarded.
 *
 * Load acquire is needed to make sure that we see that terminating NUL.
 */
अटल पूर्णांक prepend_name(अक्षर **buffer, पूर्णांक *buflen, स्थिर काष्ठा qstr *name)
अणु
	स्थिर अक्षर *dname = smp_load_acquire(&name->name); /* ^^^ */
	u32 dlen = READ_ONCE(name->len);
	अक्षर *p;

	*buflen -= dlen + 1;
	अगर (*buflen < 0)
		वापस -ENAMETOOLONG;
	p = *buffer -= dlen + 1;
	*p++ = '/';
	जबतक (dlen--) अणु
		अक्षर c = *dname++;
		अगर (!c)
			अवरोध;
		*p++ = c;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * prepend_path - Prepend path string to a buffer
 * @path: the dentry/vfsmount to report
 * @root: root vfsmnt/dentry
 * @buffer: poपूर्णांकer to the end of the buffer
 * @buflen: poपूर्णांकer to buffer length
 *
 * The function will first try to ग_लिखो out the pathname without taking any
 * lock other than the RCU पढ़ो lock to make sure that dentries won't go away.
 * It only checks the sequence number of the global नाम_lock as any change
 * in the dentry's d_seq will be preceded by changes in the नाम_lock
 * sequence number. If the sequence number had been changed, it will restart
 * the whole pathname back-tracing sequence again by taking the नाम_lock.
 * In this हाल, there is no need to take the RCU पढ़ो lock as the recursive
 * parent poपूर्णांकer references will keep the dentry chain alive as दीर्घ as no
 * नाम operation is perक्रमmed.
 */
अटल पूर्णांक prepend_path(स्थिर काष्ठा path *path,
			स्थिर काष्ठा path *root,
			अक्षर **buffer, पूर्णांक *buflen)
अणु
	काष्ठा dentry *dentry;
	काष्ठा vfsmount *vfsmnt;
	काष्ठा mount *mnt;
	पूर्णांक error = 0;
	अचिन्हित seq, m_seq = 0;
	अक्षर *bptr;
	पूर्णांक blen;

	rcu_पढ़ो_lock();
restart_mnt:
	पढ़ो_seqbegin_or_lock(&mount_lock, &m_seq);
	seq = 0;
	rcu_पढ़ो_lock();
restart:
	bptr = *buffer;
	blen = *buflen;
	error = 0;
	dentry = path->dentry;
	vfsmnt = path->mnt;
	mnt = real_mount(vfsmnt);
	पढ़ो_seqbegin_or_lock(&नाम_lock, &seq);
	जबतक (dentry != root->dentry || vfsmnt != root->mnt) अणु
		काष्ठा dentry * parent;

		अगर (dentry == vfsmnt->mnt_root || IS_ROOT(dentry)) अणु
			काष्ठा mount *parent = READ_ONCE(mnt->mnt_parent);
			काष्ठा mnt_namespace *mnt_ns;

			/* Escaped? */
			अगर (dentry != vfsmnt->mnt_root) अणु
				bptr = *buffer;
				blen = *buflen;
				error = 3;
				अवरोध;
			पूर्ण
			/* Global root? */
			अगर (mnt != parent) अणु
				dentry = READ_ONCE(mnt->mnt_mountpoपूर्णांक);
				mnt = parent;
				vfsmnt = &mnt->mnt;
				जारी;
			पूर्ण
			mnt_ns = READ_ONCE(mnt->mnt_ns);
			/* खोलो-coded is_mounted() to use local mnt_ns */
			अगर (!IS_ERR_OR_शून्य(mnt_ns) && !is_anon_ns(mnt_ns))
				error = 1;	// असलolute root
			अन्यथा
				error = 2;	// detached or not attached yet
			अवरोध;
		पूर्ण
		parent = dentry->d_parent;
		prefetch(parent);
		error = prepend_name(&bptr, &blen, &dentry->d_name);
		अगर (error)
			अवरोध;

		dentry = parent;
	पूर्ण
	अगर (!(seq & 1))
		rcu_पढ़ो_unlock();
	अगर (need_seqretry(&नाम_lock, seq)) अणु
		seq = 1;
		जाओ restart;
	पूर्ण
	करोne_seqretry(&नाम_lock, seq);

	अगर (!(m_seq & 1))
		rcu_पढ़ो_unlock();
	अगर (need_seqretry(&mount_lock, m_seq)) अणु
		m_seq = 1;
		जाओ restart_mnt;
	पूर्ण
	करोne_seqretry(&mount_lock, m_seq);

	अगर (error >= 0 && bptr == *buffer) अणु
		अगर (--blen < 0)
			error = -ENAMETOOLONG;
		अन्यथा
			*--bptr = '/';
	पूर्ण
	*buffer = bptr;
	*buflen = blen;
	वापस error;
पूर्ण

/**
 * __d_path - वापस the path of a dentry
 * @path: the dentry/vfsmount to report
 * @root: root vfsmnt/dentry
 * @buf: buffer to वापस value in
 * @buflen: buffer length
 *
 * Convert a dentry पूर्णांकo an ASCII path name.
 *
 * Returns a poपूर्णांकer पूर्णांकo the buffer or an error code अगर the
 * path was too दीर्घ.
 *
 * "buflen" should be positive.
 *
 * If the path is not reachable from the supplied root, वापस %शून्य.
 */
अक्षर *__d_path(स्थिर काष्ठा path *path,
	       स्थिर काष्ठा path *root,
	       अक्षर *buf, पूर्णांक buflen)
अणु
	अक्षर *res = buf + buflen;
	पूर्णांक error;

	prepend(&res, &buflen, "\0", 1);
	error = prepend_path(path, root, &res, &buflen);

	अगर (error < 0)
		वापस ERR_PTR(error);
	अगर (error > 0)
		वापस शून्य;
	वापस res;
पूर्ण

अक्षर *d_असलolute_path(स्थिर काष्ठा path *path,
	       अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा path root = अणुपूर्ण;
	अक्षर *res = buf + buflen;
	पूर्णांक error;

	prepend(&res, &buflen, "\0", 1);
	error = prepend_path(path, &root, &res, &buflen);

	अगर (error > 1)
		error = -EINVAL;
	अगर (error < 0)
		वापस ERR_PTR(error);
	वापस res;
पूर्ण

/*
 * same as __d_path but appends "(deleted)" क्रम unlinked files.
 */
अटल पूर्णांक path_with_deleted(स्थिर काष्ठा path *path,
			     स्थिर काष्ठा path *root,
			     अक्षर **buf, पूर्णांक *buflen)
अणु
	prepend(buf, buflen, "\0", 1);
	अगर (d_unlinked(path->dentry)) अणु
		पूर्णांक error = prepend(buf, buflen, " (deleted)", 10);
		अगर (error)
			वापस error;
	पूर्ण

	वापस prepend_path(path, root, buf, buflen);
पूर्ण

अटल पूर्णांक prepend_unreachable(अक्षर **buffer, पूर्णांक *buflen)
अणु
	वापस prepend(buffer, buflen, "(unreachable)", 13);
पूर्ण

अटल व्योम get_fs_root_rcu(काष्ठा fs_काष्ठा *fs, काष्ठा path *root)
अणु
	अचिन्हित seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&fs->seq);
		*root = fs->root;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&fs->seq, seq));
पूर्ण

/**
 * d_path - वापस the path of a dentry
 * @path: path to report
 * @buf: buffer to वापस value in
 * @buflen: buffer length
 *
 * Convert a dentry पूर्णांकo an ASCII path name. If the entry has been deleted
 * the string " (deleted)" is appended. Note that this is ambiguous.
 *
 * Returns a poपूर्णांकer पूर्णांकo the buffer or an error code अगर the path was
 * too दीर्घ. Note: Callers should use the वापसed poपूर्णांकer, not the passed
 * in buffer, to use the name! The implementation often starts at an offset
 * पूर्णांकo the buffer, and may leave 0 bytes at the start.
 *
 * "buflen" should be positive.
 */
अक्षर *d_path(स्थिर काष्ठा path *path, अक्षर *buf, पूर्णांक buflen)
अणु
	अक्षर *res = buf + buflen;
	काष्ठा path root;
	पूर्णांक error;

	/*
	 * We have various synthetic fileप्रणालीs that never get mounted.  On
	 * these fileप्रणालीs dentries are never used क्रम lookup purposes, and
	 * thus करोn't need to be hashed.  They also don't need a name until a
	 * user wants to identअगरy the object in /proc/pid/fd/.  The little hack
	 * below allows us to generate a name क्रम these objects on demand:
	 *
	 * Some pseuकरो inodes are mountable.  When they are mounted
	 * path->dentry == path->mnt->mnt_root.  In that हाल करोn't call d_dname
	 * and instead have d_path वापस the mounted path.
	 */
	अगर (path->dentry->d_op && path->dentry->d_op->d_dname &&
	    (!IS_ROOT(path->dentry) || path->dentry != path->mnt->mnt_root))
		वापस path->dentry->d_op->d_dname(path->dentry, buf, buflen);

	rcu_पढ़ो_lock();
	get_fs_root_rcu(current->fs, &root);
	error = path_with_deleted(path, &root, &res, &buflen);
	rcu_पढ़ो_unlock();

	अगर (error < 0)
		res = ERR_PTR(error);
	वापस res;
पूर्ण
EXPORT_SYMBOL(d_path);

/*
 * Helper function क्रम dentry_operations.d_dname() members
 */
अक्षर *dynamic_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen,
			स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर temp[64];
	पूर्णांक sz;

	बहु_शुरू(args, fmt);
	sz = vsnम_लिखो(temp, माप(temp), fmt, args) + 1;
	बहु_पूर्ण(args);

	अगर (sz > माप(temp) || sz > buflen)
		वापस ERR_PTR(-ENAMETOOLONG);

	buffer += buflen - sz;
	वापस स_नकल(buffer, temp, sz);
पूर्ण

अक्षर *simple_dname(काष्ठा dentry *dentry, अक्षर *buffer, पूर्णांक buflen)
अणु
	अक्षर *end = buffer + buflen;
	/* these dentries are never नामd, so d_lock is not needed */
	अगर (prepend(&end, &buflen, " (deleted)", 11) ||
	    prepend(&end, &buflen, dentry->d_name.name, dentry->d_name.len) ||
	    prepend(&end, &buflen, "/", 1))  
		end = ERR_PTR(-ENAMETOOLONG);
	वापस end;
पूर्ण

/*
 * Write full pathname from the root of the fileप्रणाली पूर्णांकo the buffer.
 */
अटल अक्षर *__dentry_path(स्थिर काष्ठा dentry *d, अक्षर *buf, पूर्णांक buflen)
अणु
	स्थिर काष्ठा dentry *dentry;
	अक्षर *end, *retval;
	पूर्णांक len, seq = 0;
	पूर्णांक error = 0;

	अगर (buflen < 2)
		जाओ Eदीर्घ;

	rcu_पढ़ो_lock();
restart:
	dentry = d;
	end = buf + buflen;
	len = buflen;
	prepend(&end, &len, "\0", 1);
	/* Get '/' right */
	retval = end-1;
	*retval = '/';
	पढ़ो_seqbegin_or_lock(&नाम_lock, &seq);
	जबतक (!IS_ROOT(dentry)) अणु
		स्थिर काष्ठा dentry *parent = dentry->d_parent;

		prefetch(parent);
		error = prepend_name(&end, &len, &dentry->d_name);
		अगर (error)
			अवरोध;

		retval = end;
		dentry = parent;
	पूर्ण
	अगर (!(seq & 1))
		rcu_पढ़ो_unlock();
	अगर (need_seqretry(&नाम_lock, seq)) अणु
		seq = 1;
		जाओ restart;
	पूर्ण
	करोne_seqretry(&नाम_lock, seq);
	अगर (error)
		जाओ Eदीर्घ;
	वापस retval;
Eदीर्घ:
	वापस ERR_PTR(-ENAMETOOLONG);
पूर्ण

अक्षर *dentry_path_raw(स्थिर काष्ठा dentry *dentry, अक्षर *buf, पूर्णांक buflen)
अणु
	वापस __dentry_path(dentry, buf, buflen);
पूर्ण
EXPORT_SYMBOL(dentry_path_raw);

अक्षर *dentry_path(स्थिर काष्ठा dentry *dentry, अक्षर *buf, पूर्णांक buflen)
अणु
	अक्षर *p = शून्य;
	अक्षर *retval;

	अगर (d_unlinked(dentry)) अणु
		p = buf + buflen;
		अगर (prepend(&p, &buflen, "//deleted", 10) != 0)
			जाओ Eदीर्घ;
		buflen++;
	पूर्ण
	retval = __dentry_path(dentry, buf, buflen);
	अगर (!IS_ERR(retval) && p)
		*p = '/';	/* restore '/' overriden with '\0' */
	वापस retval;
Eदीर्घ:
	वापस ERR_PTR(-ENAMETOOLONG);
पूर्ण

अटल व्योम get_fs_root_and_pwd_rcu(काष्ठा fs_काष्ठा *fs, काष्ठा path *root,
				    काष्ठा path *pwd)
अणु
	अचिन्हित seq;

	करो अणु
		seq = पढ़ो_seqcount_begin(&fs->seq);
		*root = fs->root;
		*pwd = fs->pwd;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&fs->seq, seq));
पूर्ण

/*
 * NOTE! The user-level library version वापसs a
 * अक्षरacter poपूर्णांकer. The kernel प्रणाली call just
 * वापसs the length of the buffer filled (which
 * includes the ending '\0' अक्षरacter), or a negative
 * error value. So libc would करो something like
 *
 *	अक्षर *अ_लोwd(अक्षर * buf, माप_प्रकार size)
 *	अणु
 *		पूर्णांक retval;
 *
 *		retval = sys_अ_लोwd(buf, size);
 *		अगर (retval >= 0)
 *			वापस buf;
 *		त्रुटि_सं = -retval;
 *		वापस शून्य;
 *	पूर्ण
 */
SYSCALL_DEFINE2(अ_लोwd, अक्षर __user *, buf, अचिन्हित दीर्घ, size)
अणु
	पूर्णांक error;
	काष्ठा path pwd, root;
	अक्षर *page = __getname();

	अगर (!page)
		वापस -ENOMEM;

	rcu_पढ़ो_lock();
	get_fs_root_and_pwd_rcu(current->fs, &root, &pwd);

	error = -ENOENT;
	अगर (!d_unlinked(pwd.dentry)) अणु
		अचिन्हित दीर्घ len;
		अक्षर *cwd = page + PATH_MAX;
		पूर्णांक buflen = PATH_MAX;

		prepend(&cwd, &buflen, "\0", 1);
		error = prepend_path(&pwd, &root, &cwd, &buflen);
		rcu_पढ़ो_unlock();

		अगर (error < 0)
			जाओ out;

		/* Unreachable from current root */
		अगर (error > 0) अणु
			error = prepend_unreachable(&cwd, &buflen);
			अगर (error)
				जाओ out;
		पूर्ण

		error = -दुस्फल;
		len = PATH_MAX + page - cwd;
		अगर (len <= size) अणु
			error = len;
			अगर (copy_to_user(buf, cwd, len))
				error = -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
	पूर्ण

out:
	__putname(page);
	वापस error;
पूर्ण
